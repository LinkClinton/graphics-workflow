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

	struct GeodesicWorkflowDrawCall {
		uint32 vtx_location = 0;
		uint32 vtx_count = 0;
		
		uint32 idx_location = 0;
		uint32 idx_count = 0;

		uint32 instance_count = 0;

		GeodesicWorkflowDrawCall() = default;
	};

	struct GeodesicWorkflowStatus {
		wrapper::directx12::pixel_format rtv_format;
		wrapper::directx12::pixel_format dsv_format;

		wrapper::directx12::device device;

		D3D12_CULL_MODE cull_mode = D3D12_CULL_MODE_BACK;

		GeodesicWorkflowStatus() = default;
	};

	struct GeodesicWorkflowInput {
		std::vector<GeodesicWorkflowDrawCall> render_calls;

		wrapper::directx12::graphics_command_list command_list;

		wrapper::directx12::cpu_descriptor_handle render_target_view;
		wrapper::directx12::cpu_descriptor_handle depth_stencil_view;

		wrapper::directx12::descriptor_heap color_bar;
		
		wrapper::directx12::buffer positions;
		wrapper::directx12::buffer indices;

		wrapper::directx12::buffer transforms;
		wrapper::directx12::buffer distances;

		matrix4x4 view_matrix = matrix4x4(1);
		matrix4x4 proj_matrix = matrix4x4(1);

		vector2 min = vector2(0);
		vector2 max = vector2(0);
	};

	struct GeodesicWorkflowOutput {
		
	};

	using GWStatus = GeodesicWorkflowStatus;
	using GWOutput = GeodesicWorkflowOutput;
	using GWInput = GeodesicWorkflowInput;

	class GeodesicWorkflow final : public StatusWorkflow<GWInput, GWOutput, GWStatus> {
	public:
		GeodesicWorkflow(const GeodesicWorkflowStatus& status);

		~GeodesicWorkflow() = default;

		output_type start(const input_type& input) override;
	private:
		GeodesicWorkflowStatus mStatus;

		wrapper::directx12::root_signature_info mRootSignatureInfo;
		wrapper::directx12::root_signature mRootSignature;

		wrapper::directx12::input_assembly_info mInputAssemblyInfo;
		wrapper::directx12::rasterization_info mRasterizationInfo;
		wrapper::directx12::depth_stencil_info mDepthStencilInfo;
		wrapper::directx12::blend_info mBlendInfo;

		wrapper::directx12::descriptor_table mDescriptorTable;
		
		wrapper::directx12::graphics_pipeline_info mGraphicsPipelineInfo;
		wrapper::directx12::pipeline_state mGraphicsPipeline;

		wrapper::directx12::shader_code mVertShader;
		wrapper::directx12::shader_code mFragShader;
	};

	inline GeodesicWorkflow::GeodesicWorkflow(const GeodesicWorkflowStatus& status) : mStatus(status)
	{
		mDescriptorTable.add_srv_range({ "color_bar" }, 2, 0);

		mRootSignatureInfo
			.add_shader_resource_view("transforms", 0, 0)
			.add_shader_resource_view("distances", 1, 0)
			.add_descriptor_table("color_bar", mDescriptorTable)
			.add_static_sampler("sampler", 3, 0)
			.add_constants("config", 0, 1, 34);

		mRootSignature = wrapper::directx12::root_signature::create(mStatus.device, mRootSignatureInfo);

		mVertShader = wrapper::directx12::shader_code::create(shaders::workflow_geodesic_vert_shader);
		mFragShader = wrapper::directx12::shader_code::create(shaders::workflow_geodesic_frag_shader);

		mInputAssemblyInfo.add_input_element("POSITION", DXGI_FORMAT_R32G32B32_FLOAT, 0);

		mRasterizationInfo
			.set_fill_mode(D3D12_FILL_MODE_SOLID)
			.set_cull_mode(mStatus.cull_mode);

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

	inline StatusWorkflow<GeodesicWorkflowInput, GeodesicWorkflowOutput, GeodesicWorkflowStatus>::output_type GeodesicWorkflow::start(const input_type& input)
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

		command_list.set_descriptor_heaps({ input.color_bar.get() });

		command_list.set_graphics_shader_resource_view(mRootSignatureInfo.index("transforms"), input.transforms);
		command_list.set_graphics_shader_resource_view(mRootSignatureInfo.index("distances"), input.distances);
		command_list.set_graphics_descriptor_table(mRootSignatureInfo.index("color_bar"), input.color_bar.gpu_handle());
		
		command_list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		struct shader_config {
			matrix4x4 view_matrix;
			matrix4x4 proj_matrix;

			uint32 instance_location;
			uint32 distance_location;
		};

		shader_config config = {
			input.view_matrix, input.proj_matrix, 0, 0
		};

		for (const auto& render_call : input.render_calls) {
			command_list.set_graphics_constants(
				mRootSignatureInfo.index("config"), &config, 34, 0);

			command_list->DrawIndexedInstanced(
				render_call.idx_count,
				render_call.instance_count,
				render_call.idx_location,
				render_call.vtx_location, 0);

			config.instance_location += render_call.instance_count;
			config.distance_location += render_call.vtx_count;
		}

		return {};
	}
}
