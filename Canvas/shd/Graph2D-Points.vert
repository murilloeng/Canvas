#version 460 core

layout(std430, binding = 0) buffer Curve
{
	vec4 color;
	uint count;
	uint thickness;
	vec2 positions[];
};
layout(std140, binding = 2) uniform Frame
{
	vec4 axes;
	vec4 offset;
};
layout(std140, binding = 1) uniform Screen
{
	float width;
	float height;
};

void main(void)
{
	//data
	const float w = width;
	const float h = height;
	const float m = min(w, h);
	//position
	gl_Position = vec4(vec2(m / w, m / h) * positions[gl_InstanceID], 0, 1);
}