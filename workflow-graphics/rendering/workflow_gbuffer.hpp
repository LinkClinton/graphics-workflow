#pragma once

#include "../../references/directx-wrapper/directx12-wrapper/resources/texture2d.hpp"

#include "../cores/workflow_status.hpp"

#include <unordered_map>
#include <variant>
#include <vector>
#include <string>
#include <tuple>

using namespace wrapper;

namespace workflows::rendering {

	using namespace cores;

	/*
	 * GBufferWorkflow is StatusWorkflow, it has status that config the input format and output format.
	 * For input format, it will config the input property from vertex buffer, constant buffer and texture
	 * A input property has a name and can come from vertex buffer, constant buffer or texture
	 * For output format, it will config the output property.
	 * A output property is an expression of input property
	 *
	 * When GBufferWorkflow finished the config, it will generate the shader and pipeline.
	 *
	 * For input of GBufferWorkflow, it will has four main components :
	 *	- draw calls component, tell the workflow how to invoke the draw calls
	 *	- transform component, the transform matrix of instance
	 *	- array of user defined data, the first part is the data of constant buffer, the second part is texture index.
	 *	- array of texture
	 * All components are independent for the better memory layout.
	 *
	 * Format of user defined data :
	 *	- some floats, uints and so on.
	 *	- some uints that indicate which texture will use
	 * Each sub component of user defined data is corresponding to a input property
	 *
	 * Packed rule of user defined data : 
	 *
	 *
	 * Type Limit of input property and output property
	 * For input property, the type should be uint32, float, float2, float3, float4 and some base type.
	 * For texture property, the type of property is the format of texture
	 *
	 * Special Input Property :
	 *	- Position : From Vertex Buffer indicate the position of vertex
	 *	- Texcoord : From Vertex Buffer indicate the texcoord of vertex
	 *	- Normal : From Vertex Buffer indicate the normal of vertex
	 *
	 * A GBufferWorkflow must have Position Input Property.
	 *
	 * The output format should indicate the number of textures and which texture and channel
	 * the output property will output.
	 */

	enum class GBufferWorkflowBaseType : uint32 {
		float4, float3, float2, float1,
		uint4, uint3, uint2, uint1
	};

	enum class GBufferWorkflowInputPropertyType : uint32 {
		vertex, buffer, texture
	};

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
	};

	struct GBufferWorkflowInputTexture {
		std::string name;

		uint32 channel_begin = 0;
		uint32 channel_end = 0;
		uint32 which = 0;
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
		std::vector<GBufferWorkflowInputTexture> property_from_texture;
		std::vector<GBufferWorkflowInputVertex> property_from_vertex;
		std::vector<GBufferWorkflowInputBuffer> property_from_buffer;

		std::vector<GBufferWorkflowBaseType> formats;
	};

	struct GBufferWorkflowStatus {
		GBufferWorkflowOutputConfig output;
		GBufferWorkflowInputConfig input;
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
		
		std::vector<directx12::texture2d> textures;
		std::vector<directx12::texture2d> outputs;

		directx12::buffer index_buffer;
		directx12::buffer transform;
		directx12::buffer data;
		
		uint32 slot = 0;
	};
}
