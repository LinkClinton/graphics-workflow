#include "fix_resharper_error.hlsl"

struct vs_output {
	SYSTEM_VALUE(float4, position, SV_POSITION);
	SYSTEM_VALUE(float4, color, COLOR);
	SYSTEM_VALUE(uint, identity, Identity);
};

struct shader_config {
	float4x4 view_matrix;
	float4x4 proj_matrix;
	
	uint instance_location;
	uint distance_location;
};

struct shader_transforms {
	float4x4 local_to_world;
};

struct shader_distances {
	float distance;
};

SHADER_STRUCTURED_BUFFER_DEFINE(shader_transforms, transforms, t0, space0);
SHADER_STRUCTURED_BUFFER_DEFINE(shader_distances, distances, t1, space0);
SHADER_RESOURCE_DEFINE(Texture2D, color_bar, t2, space0);
SHADER_RESOURCE_DEFINE(SamplerState, sampler0, s3, space0);

SHADER_CONSTANT_BUFFER_DEFINE(shader_config, config, b0, space1);

vs_output vs_main(
	SYSTEM_VALUE(float3, position, POSITION),
	SYSTEM_VALUE(uint, identity, SV_InstanceID),
	SYSTEM_VALUE(uint, vertex, SV_VertexID))
{
	vs_output output;

	output.identity = config.instance_location + identity;
	output.position = mul(float4(position, 1), transforms[output.identity].local_to_world);
	output.position = mul(output.position, config.view_matrix);
	output.position = mul(output.position, config.proj_matrix);
	output.color = color_bar.SampleLevel(sampler0, float2(distances[config.distance_location + vertex].distance, 0.5f), 0);
	
	return output;
}

SYSTEM_VALUE(float4, ps_main(vs_output input), SV_TARGET)
{
	return input.color;
}