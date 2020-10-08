#pragma once

#include <directx12-wrapper/descriptors/descriptor_heap.hpp>
#include <directx12-wrapper/descriptors/root_signature.hpp>
#include <directx12-wrapper/pipelines/pipeline_state.hpp>
#include <directx12-wrapper/resources/texture2d.hpp>
#include <directx12-wrapper/enums/pixel_format.hpp>

#include "../resources/workflow_shaders_file.hpp"
#include "../cores/workflow_status.hpp"

#include <vector>

using namespace wrapper;

namespace workflows::rendering {

	using namespace cores;
	
	struct LineWorkflowDrawCall {
		vector3 begin = vector3(0);
		vector3 end = vector3(0);

		vector4 color = vector4(0, 0, 0, 1);
	};

	struct LineWorkflowStatus {
		directx12::pixel_format format;
		directx12::device device;
	};
	
	struct LineWorkflowInput {
		std::vector<LineWorkflowDrawCall> lines;

		directx12::graphics_command_list command_list;
		directx12::descriptor_heap descriptor_heap;
		directx12::texture2d render_target;

		matrix4x4 view_matrix;
		
		uint32 which = 0;
	};

	struct LineWorkflowOutput {
		directx12::texture2d render_target;
	};

	using LWStatus = LineWorkflowStatus;
	using LWOutput = LineWorkflowOutput;
	using LWInput = LineWorkflowInput;
	
	class LineWorkflow final : public StatusWorkflow<LWInput, LWOutput, LWStatus> {
	public:
		LineWorkflow(const LineWorkflowStatus& status);

		~LineWorkflow() = default;

		output_type start(const input_type& input) override;
	private:
		LineWorkflowStatus mStatus;

		directx12::root_signature_info mRootSignatureInfo;
		directx12::root_signature mRootSignature;

		directx12::input_assembly_info mInputAssemblyInfo;
		directx12::rasterization_info mRasterizationInfo;
		directx12::depth_stencil_info mDepthStencilInfo;
		directx12::blend_info mBlendInfo;

		directx12::graphics_pipeline_info mGraphicsPipelineInfo;
		directx12::pipeline_state mGraphicsPipeline;
		
		directx12::shader_code mVertShader;
		directx12::shader_code mFragShader;

		directx12::buffer mVertexBuffer;
	};

	inline LineWorkflow::LineWorkflow(const LineWorkflowStatus& status) :
		mStatus(status)
	{
		mRootSignatureInfo.add_constants("view_matrix", 0, 0, 16);

		mRootSignature = directx12::root_signature::create(mStatus.device, mRootSignatureInfo);

		mVertShader = directx12::shader_code::create(shaders::workflow_line_vert_shader);
		mFragShader = directx12::shader_code::create(shaders::workflow_line_frag_shader);
		
		mInputAssemblyInfo
			.add_input_element("POSITION", DXGI_FORMAT_R32G32B32_FLOAT)
			.add_input_element("COLOR", DXGI_FORMAT_R32G32B32A32_FLOAT);

		mRasterizationInfo
			.set_fill_mode(D3D12_FILL_MODE_SOLID)
			.set_cull_mode(D3D12_CULL_MODE_NONE);

		mDepthStencilInfo.set_depth_enable(false);

		mGraphicsPipelineInfo
			.set_primitive_type(D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE)
			.set_root_signature(mRootSignature)
			.set_vert_shader(mVertShader)
			.set_frag_shader(mFragShader)
			.set_input_assembly(mInputAssemblyInfo)
			.set_rasterization(mRasterizationInfo)
			.set_depth_stencil(mDepthStencilInfo)
			.set_blend(mBlendInfo)
			.set_format({ mStatus.format });

		mGraphicsPipeline = directx12::pipeline_state::create(mStatus.device, mGraphicsPipelineInfo);

		mVertexBuffer = directx12::buffer();
	}

	inline StatusWorkflow<LineWorkflowInput, LineWorkflowOutput, LineWorkflowStatus>::output_type LineWorkflow::start(
		const input_type& input)
	{
		if (input.lines.empty()) return { input.render_target };
		
		// sizeof vertex = 7 * 4, number of vertex = 2
		const auto size_of_lines = input.lines.size() * 2 * 7 * 4;

		if (mVertexBuffer.size_in_bytes() < size_of_lines) {
			mVertexBuffer = directx12::buffer::create(mStatus.device,
				directx12::resource_info::upload(), size_of_lines);
		}

		struct LineVertex { vector3 position; vector4 color; };

		std::vector<LineVertex> vertices(input.lines.size() * 2);

		for (size_t index = 0; index < input.lines.size(); index++) {
			const auto& line = input.lines[index];
			
			vertices[index * 2 + 0] = { line.begin, line.color };
			vertices[index * 2 + 1] = { line.end, line.color };
		}

		mVertexBuffer.copy_from_cpu(vertices.data(), size_of_lines);

		const auto& command_list = input.command_list;

		command_list->SetGraphicsRootSignature(mRootSignature.get());
		command_list->SetPipelineState(mGraphicsPipeline.get());
		
		command_list.set_render_targets({ input.descriptor_heap.cpu_handle(input.which) });
		command_list.set_vertex_buffers({ 
			directx12::resource_view::vertex_buffer(mVertexBuffer, 7 * 4, size_of_lines)
		});

		command_list.set_view_ports({
			{ 0, 0,
				static_cast<float>(input.render_target.width()),
				static_cast<float>(input.render_target.height()),
				0, 1
			}
		});

		command_list.set_scissor_rects({
			{ 0, 0,
				static_cast<LONG>(input.render_target.width()),
				static_cast<LONG>(input.render_target.height())
			}
		});

		command_list.set_graphics_constants(
			mRootSignatureInfo.index("view_matrix"),
			&input.view_matrix, 16, 0);

		command_list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
		command_list->DrawInstanced(
			static_cast<UINT>(input.lines.size() * 2),
			1, 0, 0);

		return { input.render_target };
	}

}
