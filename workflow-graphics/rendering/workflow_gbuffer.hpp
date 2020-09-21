#pragma once

#include "../../references/directx-wrapper/directx12-wrapper/descriptors/root_signature.hpp"
#include "../../references/directx-wrapper/directx12-wrapper/pipelines/pipeline_state.hpp"
#include "../../references/directx-wrapper/directx12-wrapper/shaders/shader_creator.hpp"
#include "../../references/directx-wrapper/directx12-wrapper/resources/texture2d.hpp"

#include "../cores/workflow_status.hpp"

#include <unordered_map>
#include <vector>
#include <string>

using namespace wrapper;

namespace workflows::rendering {

	using namespace cores;

	/*
	 * GBufferWorkflow is StatusWorkflow, it has status that config the input format and output format.
	 * For input format, it will config the input property from vertex buffer and constant buffer
	 * A input property has a name and can come from vertex buffer or constant buffer
	 * For output format, it will config the output property.
	 * A output property is an expression of input property
	 *
	 * When GBufferWorkflow finished the config, it will generate the shader and pipeline.
	 *
	 * For input of GBufferWorkflow, it will has four main components :
	 *	- draw calls component, tell the workflow how to invoke the draw calls
	 *	- transform component, the transform matrix of instance
	 *	- array of user defined data 
	 * All components are independent for the better memory layout.
	 *
	 * Format of user defined data :
	 *	- some floats, uints and so on.
	 *	- some uints that indicate which texture will use
	 * Each sub component of user defined data is corresponding to a input property
	 *
	 * The packed rule of user defined data is same as
	 * https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-packing-rules 
	 *
	 * Type Limit of input property and output property
	 * For input property, the type should be uint32, float, float2, float3, float4 and some base type.
	 *
	 * Special Input Property :
	 *	- Position : From Vertex Buffer indicate the position of vertex
	 *	- Texcoord : From Vertex Buffer indicate the texcoord of vertex
	 *	- Normal : From Vertex Buffer indicate the normal of vertex
	 *
	 * Special Output Property :
	 * - Identity : instance index, uint type.
	 * - Depth : depth value, float type(only output to depth buffer).
	 *
	 * A GBufferWorkflow must have Position Input Property.
	 *
	 * the output property will output.
	 */

	enum class GBufferWorkflowBaseType : uint32 {
		float4, float3, float2, float1,
		uint4, uint3, uint2, uint1
	};

	DXGI_FORMAT to_dxgi_format(const GBufferWorkflowBaseType& type);

	std::string to_string(const GBufferWorkflowBaseType& type);
	
	/*
	 * GBufferWorkflowOutputMapping will mapping a property to a texture
	 * The begin property means the first channel we will use(0, 1, 2, 3)
	 * The element of property(1, 2, 3, 4) + begin should not grater than 4.
	 * The which property means which texture the property will output
	 */
	struct GBufferWorkflowOutputMapping {
		uint32 begin = 0;
		uint32 which = 0;
	};

	struct GBufferWorkflowOutputConfig {
		std::unordered_map<std::string, GBufferWorkflowOutputMapping> mappings;

		std::vector<GBufferWorkflowBaseType> formats;

		GBufferWorkflowBaseType depth_format;
	};

	struct GBufferWorkflowInputVertex {
		GBufferWorkflowBaseType type = GBufferWorkflowBaseType::float3;

		std::string name;

		uint32 slot = 0;
	};

	struct GBufferWorkflowInputBuffer {
		GBufferWorkflowBaseType type = GBufferWorkflowBaseType::float3;

		std::string name;
	};

	struct GBufferWorkflowInputConfig {
		std::vector<GBufferWorkflowInputVertex> property_from_vertex;
		std::vector<GBufferWorkflowInputBuffer> property_from_buffer;
	};

	struct GBufferWorkflowStatus {
		directx12::device device;
		
		GBufferWorkflowOutputConfig output;
		GBufferWorkflowInputConfig input;

		bool enable_depth = true;
	};

	struct GBufferWorkflowOutput {

	};

	struct GBufferWorkflowDrawCall {
		uint32 instance_count = 0;

		uint32 index_location = 0;
		uint32 index_count = 0;
	};

	/*
	 * The draw_calls indicate the draw commands we will run(it supports one draw call more instances)
	 * and the instance id from 0 to the sum of GBufferWorkflowDrawCall::instance_count
	 *
	 * transform is the buffer of array of matrix(float4x4) and we use instance_id as index
	 * data is the user defined data structure(the layout of it we had introduced).
	 */
	struct GBufferWorkflowInput {
		std::vector<GBufferWorkflowDrawCall> draw_calls;
		
		std::vector<directx12::buffer> vertex_buffers;
		
		std::vector<directx12::texture2d> outputs;

		directx12::texture2d depth;

		directx12::buffer index_buffer;
		directx12::buffer transform;
		directx12::buffer data;
		
		uint32 slot = 0;
	};

	using GBWStatus = GBufferWorkflowStatus;
	using GBWOutput = GBufferWorkflowOutput;
	using GBWInput = GBufferWorkflowInput;

	class GBufferWorkflow final : public StatusWorkflow<GBWInput, GBWOutput, GBWStatus> {
	public:
		explicit GBufferWorkflow(const GBufferWorkflowStatus& status);

		~GBufferWorkflow() = default;

		output_type start(const input_type& input) override;
	private:
		static std::string initialize_shaders_for_workflow(const GBufferWorkflowStatus& status);
		
		GBufferWorkflowStatus mStatus;
		
		directx12::root_signature_info mRootSignatureInfo;
		directx12::root_signature mRootSignature;

		directx12::input_assembly_info mInputAssemblyInfo;
		directx12::rasterization_info mRasterizationInfo;
		directx12::depth_stencil_info mDepthStencilInfo;
		directx12::blend_info mBlendInfo;

		directx12::shader_code mVertShader;
		directx12::shader_code mFragShader;
		
		directx12::graphics_pipeline_info mGraphicsPipelineInfo;
		directx12::pipeline_state mGraphicsPipeline;
	};

	inline DXGI_FORMAT to_dxgi_format(const GBufferWorkflowBaseType& type)
	{
		switch (type) {
		case GBufferWorkflowBaseType::float1: return DXGI_FORMAT_R32_FLOAT;
		case GBufferWorkflowBaseType::float2: return DXGI_FORMAT_R32G32_FLOAT;
		case GBufferWorkflowBaseType::float3: return DXGI_FORMAT_R32G32B32_FLOAT;
		case GBufferWorkflowBaseType::float4: return DXGI_FORMAT_R32G32B32A32_FLOAT;
		case GBufferWorkflowBaseType::uint1: return DXGI_FORMAT_R32_UINT;
		case GBufferWorkflowBaseType::uint2: return DXGI_FORMAT_R32G32_UINT;
		case GBufferWorkflowBaseType::uint3: return DXGI_FORMAT_R32G32B32_UINT;
		case GBufferWorkflowBaseType::uint4: return DXGI_FORMAT_R32G32B32A32_UINT;
		default: return DXGI_FORMAT_UNKNOWN;
		}
	}

	inline std::string to_string(const GBufferWorkflowBaseType& type)
	{
		switch (type) {
		case GBufferWorkflowBaseType::float1: return "float";
		case GBufferWorkflowBaseType::float2: return "float2";
		case GBufferWorkflowBaseType::float3: return "float3";
		case GBufferWorkflowBaseType::float4: return "float4";
		case GBufferWorkflowBaseType::uint1: return "uint";
		case GBufferWorkflowBaseType::uint2: return "uint2";
		case GBufferWorkflowBaseType::uint3: return "uint3";
		case GBufferWorkflowBaseType::uint4: return "uint4";
		default: return "";
		}
	}

	inline GBufferWorkflow::GBufferWorkflow(const GBufferWorkflowStatus& status) : mStatus(status)
	{
		mRootSignatureInfo
			.add_shader_resource_view("user_defined_data", 0, 0)
			.add_shader_resource_view("transforms", 1, 0);
		
		mRootSignature = directx12::root_signature::create(mStatus.device, mRootSignatureInfo);
		
		for (const auto& input_property : mStatus.input.property_from_vertex) {
			mInputAssemblyInfo.add_input_element(
				input_property.name, to_dxgi_format(input_property.type), 
				input_property.slot);
		}

		const auto shader = initialize_shaders_for_workflow(mStatus);

		printf("%s\n", shader.c_str());
		
		mVertShader = directx12::shader_code::create_from_source(shader, "vs_main", "vs_5_1");
		mFragShader = directx12::shader_code::create_from_source(shader, "ps_main", "ps_5_1");
		
		mRasterizationInfo
			.set_fill_mode(D3D12_FILL_MODE_SOLID)
			.set_cull_mode(D3D12_CULL_MODE_NONE);

		mDepthStencilInfo.set_depth_enable(mStatus.enable_depth);

		std::vector<DXGI_FORMAT> formats(mStatus.output.formats.size());

		for (size_t index = 0; index < mStatus.output.formats.size(); index++)
			formats[index] = to_dxgi_format(mStatus.output.formats[index]);
		
		mGraphicsPipelineInfo
			.set_format(formats, to_dxgi_format(mStatus.output.depth_format))
			.set_primitive_type(D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE)
			.set_root_signature(mRootSignature)
			.set_input_assembly(mInputAssemblyInfo)
			.set_rasterization(mRasterizationInfo)
			.set_depth_stencil(mDepthStencilInfo)
			.set_blend(mBlendInfo);

		mGraphicsPipeline = directx12::pipeline_state::create(mStatus.device, mGraphicsPipelineInfo);
	}

	inline StatusWorkflow<GBufferWorkflowInput, GBufferWorkflowOutput, GBufferWorkflowStatus>::output_type
		GBufferWorkflow::start(const input_type& input)
	{
		return {};
	}

	inline std::string GBufferWorkflow::initialize_shaders_for_workflow(const GBufferWorkflowStatus& status)
	{
		directx12::shader_creator creator;

		creator.define_structure({ {"", "matrix","float4x4"} }, "Transform");
		
		std::vector<directx12::shader_variable> user_defined_data;
		std::vector<directx12::shader_variable> vs_output;
		std::vector<directx12::shader_variable> fs_output;
		std::vector<directx12::shader_variable> vs_input;

		for (const auto& property : status.input.property_from_buffer) 
			user_defined_data.push_back({ "", property.name, to_string(property.type) });

		for (const auto& property : status.input.property_from_vertex) {
			vs_output.push_back({ property.name, property.name, to_string(property.type) });
			vs_input.push_back({ property.name, property.name, to_string(property.type) });
		}
		vs_output.push_back({ "SV_Position", "sv_position", "float4" });
		vs_output.push_back({ "SV_InstanceID", "instance_id", "uint" });

		for (size_t index = 0; index < status.output.formats.size(); index++)
			fs_output.push_back({
				"SV_Target" + std::to_string(index),
				"color" + std::to_string(index),
				to_string(status.output.formats[index])
			});

		creator.define_structure(user_defined_data, "UserDefinedData");
		creator.define_structure(vs_output, "VSOutput");
		creator.define_structure(fs_output, "FSOutput");
		creator.define_structure(vs_input, "VSInput");

		creator.define_constant_buffer("UserDefinedData", "user_defined_data", 0, 0);
		creator.define_structured_buffer("Transform", "transforms", 1, 0);

		creator.begin_function({ {"", "input", "VSInput"} }, "VSOutput", "vs_main");
		creator.define_variable("VSOutput", "output");
		
		creator.end_function();

		creator.begin_function({ {"", "input", "VSOutput"} }, "FSOutput", "fs_main");
		creator.end_function();
		
		return creator.source();
	}

}
