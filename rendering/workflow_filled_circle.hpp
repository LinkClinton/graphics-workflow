#pragma once

#include <directx12-wrapper/descriptors/descriptor_heap.hpp>
#include <directx12-wrapper/descriptors/root_signature.hpp>
#include <directx12-wrapper/pipelines/pipeline_state.hpp>
#include <directx12-wrapper/resources/texture2d.hpp>
#include <directx12-wrapper/enums/pixel_format.hpp>

#include "../resources/workflow_shaders_file.hpp"
#include "../cores/workflow_status.hpp"

#include <vector>

namespace workflows::rendering {

	using namespace cores;

	struct FilledCircleWorkflowDrawCall {
		vector2 position = vector2(0);
		vector4 color = vector4(0, 0, 0, 1);
		
		float radius = 1;

		FilledCircleWorkflowDrawCall() = default;
	};

	struct FilledCircleWorkflowStatus {
		wrapper::directx12::pixel_format format;
		wrapper::directx12::device device;

		uint32 triangles = 36;
		
		FilledCircleWorkflowStatus() = default;
	};

	struct FilledCircleWorkflowInput {
		std::vector<FilledCircleWorkflowDrawCall> circles;

		wrapper::directx12::cpu_descriptor_handle render_target_view;
		wrapper::directx12::graphics_command_list command_list;
		
		matrix4x4 view_matrix = matrix4x4(1);

		vector2 min = vector2(0);
		vector2 max = vector2(0);
		
		FilledCircleWorkflowInput() = default;
	};

	struct FilledCircleWorkflowOutput {
		FilledCircleWorkflowOutput() = default;
	};

	using FCWStatus = FilledCircleWorkflowStatus;
	using FCWInput = FilledCircleWorkflowInput;
	using FCWOutput = FilledCircleWorkflowOutput;

	class FilledCircleWorkflow final : public StatusWorkflow<FCWInput, FCWOutput, FCWStatus> {
	public:
		FilledCircleWorkflow(const FilledCircleWorkflowStatus& status);

		~FilledCircleWorkflow() = default;

		output_type start(const input_type& input) override;
	private:
		FilledCircleWorkflowStatus mStatus;
		
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

		wrapper::directx12::buffer mVtxBuffer;
		wrapper::directx12::buffer mIdxBuffer;

		wrapper::directx12::buffer mTransforms;
		wrapper::directx12::buffer mColors;
	};

	inline FilledCircleWorkflow::FilledCircleWorkflow(const FilledCircleWorkflowStatus& status) :
		mStatus(status)
	{
		assert(mStatus.triangles >= 4);
		
		mRootSignatureInfo.
			add_shader_resource_view("transforms", 0, 0).
			add_shader_resource_view("colors", 1, 0).
			add_constants("view_matrix", 0, 1, 16);

		mRootSignature = wrapper::directx12::root_signature::create(mStatus.device, mRootSignatureInfo);

		mVertShader = wrapper::directx12::shader_code::create(shaders::workflow_filled_circle_vert_shader);
		mFragShader = wrapper::directx12::shader_code::create(shaders::workflow_filled_circle_frag_shader);

		mInputAssemblyInfo.add_input_element("POSITION", DXGI_FORMAT_R32G32B32_FLOAT);
		
		mRasterizationInfo
			.set_fill_mode(D3D12_FILL_MODE_SOLID)
			.set_cull_mode(D3D12_CULL_MODE_NONE);

		mDepthStencilInfo.set_depth_enable(false);

		mGraphicsPipelineInfo
			.set_primitive_type(D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE)
			.set_root_signature(mRootSignature)
			.set_vert_shader(mVertShader)
			.set_frag_shader(mFragShader)
			.set_input_assembly(mInputAssemblyInfo)
			.set_rasterization(mRasterizationInfo)
			.set_depth_stencil(mDepthStencilInfo)
			.set_blend(mBlendInfo)
			.set_format({ mStatus.format });

		mGraphicsPipeline = wrapper::directx12::pipeline_state::create(mStatus.device, mGraphicsPipelineInfo);

		std::vector<vector3> positions;
		std::vector<uint32> indices;

		positions.push_back(vector3(0, 0, 0));
		positions.push_back(vector3(1, 0, 0));

		const float step = 2 * glm::pi<float>() / mStatus.triangles;

		float theta = 0;
		
		for (uint32 index = 0; index < mStatus.triangles - 1; index++) {
			theta += step;

			positions.push_back(vector3(std::cos(theta), std::sin(theta), 0));
		}

		for (uint32 index = 0; index < mStatus.triangles; index++) {
			indices.push_back(0);
			indices.push_back(index + 1);
			indices.push_back(((index + 1) % mStatus.triangles) + 1);
		}

		mVtxBuffer = wrapper::directx12::buffer::create(mStatus.device, wrapper::directx12::resource_info::upload(),
			sizeof(vector3) * positions.size());
		mIdxBuffer = wrapper::directx12::buffer::create(mStatus.device, wrapper::directx12::resource_info::upload(),
			sizeof(uint32) * indices.size());

		mVtxBuffer.copy_from_cpu(positions.data(), mVtxBuffer.size_in_bytes());
		mIdxBuffer.copy_from_cpu(indices.data(), mIdxBuffer.size_in_bytes());
	}

	inline StatusWorkflow<FilledCircleWorkflowInput, FilledCircleWorkflowOutput, FilledCircleWorkflowStatus>::output_type
		FilledCircleWorkflow::start(const input_type& input)
	{
		if (input.circles.empty()) return {};

		if (mTransforms.get() == nullptr || mTransforms.size_in_bytes() < input.circles.size() * sizeof(matrix4x4)) {
			mTransforms = wrapper::directx12::buffer::create(mStatus.device, wrapper::directx12::resource_info::upload(),
				input.circles.size() * sizeof(matrix4x4));
			mColors = wrapper::directx12::buffer::create(mStatus.device, wrapper::directx12::resource_info::upload(),
				input.circles.size() * sizeof(vector4));
		}

		std::vector<matrix4x4> transforms;
		std::vector<vector4> colors;

		for (const auto& circle : input.circles) {
			transforms.push_back(glm::transpose(glm::scale(glm::translate(matrix4x4(1), vector3(circle.position, 0)),
				vector3(circle.radius))));
			colors.push_back(circle.color);
		}

		mTransforms.copy_from_cpu(transforms.data(), transforms.size() * sizeof(matrix4x4));
		mColors.copy_from_cpu(colors.data(), colors.size() * sizeof(vector4));

		const auto& command_list = input.command_list;

		command_list->SetGraphicsRootSignature(mRootSignature.get());
		command_list->SetPipelineState(mGraphicsPipeline.get());

		command_list.set_render_targets({ input.render_target_view });
		command_list.set_vertex_buffers({
			wrapper::directx12::resource_view::vertex_buffer(mVtxBuffer, 3 * 4, mVtxBuffer.size_in_bytes())
			});
		command_list.set_index_buffer(
			wrapper::directx12::resource_view::index_buffer(mIdxBuffer, DXGI_FORMAT_R32_UINT, mIdxBuffer.size_in_bytes()));
		
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

		
		command_list.set_graphics_shader_resource_view(mRootSignatureInfo.index("transforms"), mTransforms);
		command_list.set_graphics_shader_resource_view(mRootSignatureInfo.index("colors"), mColors);
		command_list.set_graphics_constants(
			mRootSignatureInfo.index("view_matrix"),
			&input.view_matrix, 16, 0);

		command_list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		command_list->DrawIndexedInstanced(mStatus.triangles * 3,
			static_cast<UINT>(input.circles.size()), 0, 0, 0);

		return {};
	}
}
