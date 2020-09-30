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
	 * For input format, it will config the input property from vertex buffer
	 * A input property has a name and come from vertex buffer
	 * For output format, it will config the output property.
	 * A output property is an expression of input property
	 *
	 * When GBufferWorkflow finished the config, it will generate the shader and pipeline.
	 *
	 * For input of GBufferWorkflow, it will has four main components :
	 *	- draw calls component, tell the workflow how to invoke the draw calls
	 *	- transform component, the transform matrix of instance
	 * All components are independent for the better memory layout.
	 *
	 * Type Limit of input property and output property
	 * For input property, the type should be uint, float1, float2, float3, float4 and some base type.
	 *
	 * Format of Transform Component :
	 * - Transform Matrix4x4 from local space to world space.
	 * - Transform Matrix4x4 from world space to camera space.
	 * - Transform Matrix4x4 from camera space to projection space.
	 *
	 * Input Property Description:
	 *	- Position : indicate the position of vertex, float3 type.
	 *	- Texcoord : indicate the texcoord of vertex, float3 type
	 *	- Normal : indicate the normal of vertex, float3 type
	 *
	 * Output Property Description:
	 * - PositionCameraSpace : position in camera space, float3 type.
	 * - PositionWorldSpace : position in world space, float3 type.
	 * - NormalCameraSpace : normal in camera space, float3 type. (require Normal Input Property)
	 * - NormalWorldSpace : normal in world space, float3 type. (require Normal Input Property)
	 * - Texcoord : texcoord, float3 type (require Texcoord Input Property).
	 * - Depth : depth value, float1 type(only output to depth buffer).
	 * - Identity : instance index, uint1 type.
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

	GBufferWorkflowBaseType get_type_by_name(const std::string& name);
	
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
		std::vector<GBufferWorkflowInputVertex> properties;
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
	 * transform is the buffer of array of Transform Component(float4x4 * 3) and we use instance_id as index
	 */
	struct GBufferWorkflowInput {
		std::vector<GBufferWorkflowDrawCall> draw_calls;
		
		std::vector<directx12::buffer> vertex_buffers;
		
		std::vector<directx12::texture2d> outputs;

		directx12::texture2d depth;

		directx12::buffer index_buffer;
		directx12::buffer transform;
		
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

	inline GBufferWorkflowBaseType get_type_by_name(const std::string& name)
	{
		static std::unordered_map<std::string, GBufferWorkflowBaseType> mapping = {
			{ "PositionCameraSpace", GBufferWorkflowBaseType::float3 },
			{ "PositionWorldSpace", GBufferWorkflowBaseType::float3 },
			{ "Position", GBufferWorkflowBaseType::float3 },
			{ "NormalCameraSpace", GBufferWorkflowBaseType::float3 },
			{ "NormalWorldSpace", GBufferWorkflowBaseType::float3 },
			{ "Normal", GBufferWorkflowBaseType::float3},
			{ "Texcoord", GBufferWorkflowBaseType::float3 },
			{ "Depth", GBufferWorkflowBaseType::float1 },
			{ "Identity", GBufferWorkflowBaseType::uint1 }
		};

		if (mapping.find(name) == mapping.end()) throw "Invalid Name.";

		return mapping.find(name)->second;
	}

	inline GBufferWorkflow::GBufferWorkflow(const GBufferWorkflowStatus& status) : mStatus(status)
	{
		mRootSignatureInfo
			.add_shader_resource_view("user_defined_data", 0, 0)
			.add_shader_resource_view("transforms", 1, 0);
		
		mRootSignature = directx12::root_signature::create(mStatus.device, mRootSignatureInfo);
		
		for (const auto& input_property : mStatus.input.properties) {
			mInputAssemblyInfo.add_input_element(
				input_property.name, to_dxgi_format(input_property.type), 
				input_property.slot);
		}

		const auto shader = initialize_shaders_for_workflow(mStatus);

		printf("%s\n", shader.c_str());
		
		mVertShader = directx12::shader_code::create_from_source(shader, "vs_main", "vs_5_1");
		mFragShader = directx12::shader_code::create_from_source(shader, "fs_main", "ps_5_1");
		
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

		creator.define_structure({
			{ "", "local_to_world","float4x4"},
			{ "", "world_to_camera", "float4x4"},
			{ "", "camera_to_proj", "float4x4"}
		}, "TransformComponent");
		
		std::vector<directx12::shader_variable> vs_output;
		std::vector<directx12::shader_variable> fs_output;
		std::vector<directx12::shader_variable> vs_input;

		for (const auto& property : status.input.properties) 
			vs_input.push_back({ property.name, property.name, to_string(property.type) });

		vs_input.push_back({ "SV_InstanceID", "index", "uint" });
		
		for (const auto& property : status.output.mappings) {
			if (property.first == "Identity") continue;
			
			vs_output.push_back({ property.first, property.first, to_string(get_type_by_name(property.first)) });
		}
			
		vs_output.push_back({ "SV_Position", "sv_position", "float4" });
		vs_output.push_back({ "SV_InstanceID", "index", "uint" });

		for (size_t index = 0; index < status.output.formats.size(); index++)
			fs_output.push_back({
				"SV_Target" + std::to_string(index),
				"color" + std::to_string(index),
				to_string(status.output.formats[index])
			});

		creator.define_structure(vs_output, "VSOutput");
		creator.define_structure(fs_output, "FSOutput");
		creator.define_structure(vs_input, "VSInput");

		creator.define_structured_buffer("TransformComponent", "transforms", 1, 0);

		creator.begin_function({ {"", "input", "VSInput"} }, "VSOutput", "vs_main");
		creator.define_variable("VSOutput", "output");

		creator.add_sentence("output.index = input.index;");

		creator.add_sentence("output.sv_position = mul(float4(input.Position, 1.f), transforms[input.index].local_to_world);");

		if (status.output.mappings.find("PositionWorldSpace") != status.output.mappings.end())
			creator.add_sentence("output.PositionWorldSpace = output.sv_position.xyz;");
		
		creator.add_sentence("output.sv_position = mul(output.sv_position, transforms[input.index].world_to_camera);");

		if (status.output.mappings.find("PositionCameraSpace") != status.output.mappings.end())
			creator.add_sentence("output.PositionCameraSpace = output.sv_position.xyz;");
		
		creator.add_sentence("output.sv_position = mul(output.sv_position, transforms[input.index].camera_to_proj);");

		if (status.output.mappings.find("Texcoord") != status.output.mappings.end())
			creator.add_sentence("output.Texcoord = input.Texcoord;");

		if (status.output.mappings.find("NormalCameraSpace") != status.output.mappings.end() ||
			status.output.mappings.find("NormalWorldSpace") != status.output.mappings.end())
			creator.add_sentence("input.Normal = mul(float4(input.Normal, 1.f), transforms[input.index].local_to_world).xyz;");

		if (status.output.mappings.find("NormalWorldSpace") != status.output.mappings.end())
			creator.add_sentence("output.NormalWorldSpace = input.Normal;");

		if (status.output.mappings.find("NormalCameraSpace") != status.output.mappings.end())
			creator.add_sentence("output.NormalCameraSpace = mul(float4(input.Normal, 1.f), transforms[input.index].world_to_camera).xyz;");

		creator.add_sentence("return output;");
		
		creator.end_function();

		creator.begin_function({ {"", "input", "VSOutput"} }, "FSOutput", "fs_main");
		creator.define_variable("FSOutput", "output");
		
		creator.end_function();
		
		return creator.source();
	}

}
