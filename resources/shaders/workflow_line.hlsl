#include "fix_resharper_error.hlsl"

struct vs_output {
	SYSTEM_VALUE(float4, position, SV_POSITION);
	SYSTEM_VALUE(float4, color, COLOR);
};

struct view_matrix {
	float4x4 view;
};

SHADER_CONSTANT_BUFFER_DEFINE(view_matrix, view, b0, space0);

vs_output vs_main(
	SYSTEM_VALUE(float3, position, POSITION),
	SYSTEM_VALUE(float4, color, COLOR))
{
	vs_output output;

	output.position = mul(float4(position, 1), view.view);
	output.color = color;

	return output;
}

SYSTEM_VALUE(float4, ps_main(vs_output input), SV_TARGET)
{
	return input.color;
}