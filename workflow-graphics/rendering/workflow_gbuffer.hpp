#pragma once

#include "../cores/workflow_status.hpp"

#include <variant>
#include <vector>
#include <string>
#include <tuple>

namespace workflows::rendering {

	using namespace cores;

	/*
	 * GBufferWorkflow is StatusWorkflow, it will has status that config the input format and output format.
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
	
	
}
