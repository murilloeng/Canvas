#version 460 core

layout(std430, binding = 0) buffer Curve
{
	uint count;
	vec2 data[];
};
layout(std140, binding = 1) uniform Screen
{
	float width;
	float height;
};
layout(std140, binding = 2) uniform Points
{
	vec4 points_color;
	uint points_size;
	uint points_skip;
	uint points_type;
	uint points_enabled;
};

void main(void)
{
	//data
	const float w = width;
	const float h = height;
	const float m = min(w, h);
	//position
	gl_PointSize = points_size;
	gl_Position = vec4(vec2(m / w, m / h) * data[points_skip * gl_InstanceID], 0, 1);
}