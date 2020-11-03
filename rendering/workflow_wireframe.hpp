#pragma once

#include <directx12-wrapper/descriptors/root_signature.hpp>
#include <directx12-wrapper/pipelines/pipeline_state.hpp>
#include <directx12-wrapper/resources/texture2d.hpp>
#include <directx12-wrapper/enums/pixel_format.hpp>

#include "../resources/workflow_shaders_file.hpp"
#include "../cores/workflow_status.hpp"

#include <vector>

namespace workflows::rendering {

	using namespace cores;
	
	struct WireframeWorkflowDrawCall {
		uint32 vtx_location = 0;
		uint32 idx_location = 0;
		uint32 idx_count = 0;

		uint32 instance_count = 0;

		WireframeWorkflowDrawCall() = default;
	};
	
	struct WireframeWorkflowStatus {
		wrapper::directx12::pixel_format rtv_format;
		wrapper::directx12::pixel_format dsv_format;
		
		wrapper::directx12::device device;

		D3D12_CULL_MODE mode = D3D12_CULL_MODE_NONE;
		
		WireframeWorkflowStatus() = default;
	};
	
	struct WireframeWorkflowInput {
		std::vector<WireframeWorkflowDrawCall> render_calls;

		wrapper::directx12::graphics_command_list command_list;
		
		wrapper::directx12::cpu_descriptor_handle render_target_view;
		wrapper::directx12::cpu_descriptor_handle depth_stencil_view;
		
		wrapper::directx12::buffer positions;
		wrapper::directx12::buffer indices;
		
		wrapper::directx12::buffer transforms;
		wrapper::directx12::buffer colors;

		matrix4x4 view_matrix = matrix4x4(1);
		matrix4x4 proj_matrix = matrix4x4(1);

		vector2 min = vector2(0);
		vector2 max = vector2(0);
	};

	struct WireframeWorkflowOutput {
		
	};

	using WWStatus = WireframeWorkflowStatus;
	using WWOutput = WireframeWorkflowOutput;
	using WWInput = WireframeWorkflowInput;
	
	class WireframeWorkflow final : public StatusWorkflow<WWInput, WWOutput, WWStatus> {
	public:
		WireframeWorkflow(const WireframeWorkflowStatus& status);

		~WireframeWorkflow() = default;

		output_type start(const input_type& input) override;
	private:
		WireframeWorkflowStatus mStatus;

		wrapper::directx12::root_signature_info mRootSignatureInfo;
		wrapper::directx12::root_signature mRootSignature;

		wrapper::directx12::input_assembly_info mInputAssemblyInfo;
		wrapper::directx12::rasterization_info mRasterizationInfo;
		wrapper::directx12::depth_stencil_info mDepthStencilInfo;
		wrapper::directx12::blend_info mBlendInfo;

		wrapper::directx12::graphics_pipeline_info mGraphicsPipelineInfo;
		wrapper::directx12::pipeline_state mGraphicsPipeline;

		wrapper::directx12::shader_code mVertShader;
		wrapper::directx12::shader_code mFragShader;
	};

	inline WireframeWorkflow::WireframeWorkflow(const WireframeWorkflowStatus& status) : mStatus(status)
	{
		mRootSignatureInfo
			.add_shader_resource_view("transforms", 0, 0)
			.add_shader_resource_view("colors", 1, 0)
			.add_constants("config", 0, 1, 33);
		
		mRootSignature = wrapper::directx12::root_signature::create(mStatus.device, mRootSignatureInfo);

		mVertShader = wrapper::directx12::shader_code::create(shaders::workflow_wireframe_vert_shader);
		mFragShader = wrapper::directx12::shader_code::create(shaders::workflow_wireframe_frag_shader);
		
		mInputAssemblyInfo.add_input_element("POSITION", DXGI_FORMAT_R32G32B32_FLOAT, 0);

		mRasterizationInfo
			.set_fill_mode(D3D12_FILL_MODE_WIREFRAME)
			.set_cull_mode(mStatus.mode);

		mGraphicsPipelineInfo
			.set_primitive_type(D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE)
			.set_root_signature(mRootSignature)
			.set_vert_shader(mVertShader)
			.set_frag_shader(mFragShader)
			.set_input_assembly(mInputAssemblyInfo)
			.set_rasterization(mRasterizationInfo)
			.set_depth_stencil(mDepthStencilInfo)
			.set_blend(mBlendInfo)
			.set_format({ mStatus.rtv_format }, mStatus.dsv_format);

		mGraphicsPipeline = wrapper::directx12::pipeline_state::create(mStatus.device, mGraphicsPipelineInfo);
	}

	inline StatusWorkflow<WireframeWorkflowInput, WireframeWorkflowOutput, WireframeWorkflowStatus>::output_type WireframeWorkflow::start(
		const input_type& input)
	{
		if (input.render_calls.empty()) return {};

		const auto& command_list = input.command_list;

		command_list->SetGraphicsRootSignature(mRootSignature.get());
		command_list->SetPipelineState(mGraphicsPipeline.get());

		command_list.set_render_targets({ input.render_target_view }, input.depth_stencil_view);
		command_list.set_vertex_buffers({
			wrapper::directx12::resource_view::vertex_buffer(input.positions, 12, input.positions.size_in_bytes())
			});
		command_list.set_index_buffer(
			wrapper::directx12::resource_view::index_buffer(input.indices, DXGI_FORMAT_R32_UINT, input.indices.size_in_bytes()));

		command_list.set_view_ports({
			{
				input.min.x, input.min.y, input.max.x - input.min.x, input.max.y - input.min.y,
				0, 1
			}
			});

		command_list.set_scissor_rects({
			{
				static_cast<LONG>(input.min.x), static_cast<LONG>(input.min.y),
				static_cast<LONG>(input.max.x), static_cast<LONG>(input.max.y)
			}
			});

		command_list.set_graphics_shader_resource_view(mRootSignatureInfo.index("transforms"), input.transforms);
		command_list.set_graphics_shader_resource_view(mRootSignatureInfo.index("colors"), input.colors);
		
		command_list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		struct shader_config {
			matrix4x4 view_matrix;
			matrix4x4 proj_matrix;
			
			uint32 instance_base;
		};

		shader_config config = {
			input.view_matrix, input.proj_matrix, 0
		};
		
		for (const auto& render_call : input.render_calls) {
			command_list.set_graphics_constants(
				mRootSignatureInfo.index("config"), &config, 33, 0);
			
			command_list->DrawIndexedInstanced(
				render_call.idx_count, 
				render_call.instance_count,
				render_call.idx_location, 
				render_call.vtx_location, 0);

			config.instance_base += render_call.instance_count;
		}

		return {};
	}

}
