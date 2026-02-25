#version 460 core

out vec4 vertex_color;

layout(std430, binding = 0) buffer Curve
{
	vec4 color;
	uint count;
	float thickness;
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

vec2 quad_points[] = {vec2(-1, -1), vec2(+1, -1), vec2(+1, +1), vec2(-1, +1)};

vec2 normal(vec2 p0, vec2 p1)
{
	return vec2(0, 0);
}
vec2 normal(vec2 p0, vec2 p1, vec2 p2)
{
	return vec2(0, 0);
}
vec2 normal(uint index)
{
	//data
	const mat2 N = mat2(0, 1, -1, 0);
	//normal
	if(index == 0)
	{
		return N * normalize(positions[index + 1] - positions[index]);
	}
	else if(index + 1 == count)
	{
		return N * normalize(positions[index] - positions[index - 1]);
	}
	else
	{
		const vec2 n1 = N * normalize(positions[index] - positions[index - 1]);
		const vec2 n2 = N * normalize(positions[index + 1] - positions[index]);
		return length(n1 + n2) < 1e-5 ? n1 : normalize(n1 + n2);
	}
}

void main(void)
{
	//data
	vertex_color = color;
	const float w = width;
	const float h = height;
	const float m = min(w, h);
	//NDC points positions
	const vec2 n1 = vec2(m / w, m / h) * positions[gl_InstanceID + 0];
	const vec2 n2 = vec2(m / w, m / h) * positions[gl_InstanceID + 1];
	//screen points positions
	const vec2 p1 = (n1 + 1) / 2 * vec2(width, height);
	const vec2 p2 = (n2 + 1) / 2 * vec2(width, height);
	//normal directions
	const vec2 v1 = normal(gl_InstanceID + 0);
	const vec2 v2 = normal(gl_InstanceID + 1);
	//screen vertex position
	const float t = (quad_points[gl_VertexID].x + 1) / 2;
	const vec2 pv = mix(p1, p2, t) + quad_points[gl_VertexID].y * thickness / 2 * mix(v1, v2, t);
	//NDC vertex position
	const vec2 nv = 2 * pv * vec2(1 / width, 1 / height) - 1;
	//clip vertex position
	gl_Position = vec4(nv, -1, 1);
}