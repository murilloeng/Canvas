#version 460 core

out float vertex_length;

layout(std430, binding = 0) buffer Curve
{
	uint count;
	vec3 data[];
};
layout(std140, binding = 1) uniform Screen
{
	float width;
	float height;
};
layout(std140, binding = 2) uniform Lines
{
	vec4 lines_color;
	uint lines_width;
	uint lines_enabled;
	uint lines_dash_size;
	uint lines_dash_type;
};

const mat2 N = mat2(0, 1, -1, 0);
const vec2 quad_points[] = {vec2(-1, -1), vec2(+1, -1), vec2(+1, +1), vec2(-1, +1)};

vec2 normal(uint index)
{
	if(index == 0)
	{
		return N * normalize(data[index + 1].xy - data[index].xy);
	}
	else if(index + 1 == count)
	{
		return N * normalize(data[index].xy - data[index - 1].xy);
	}
	else
	{
		const vec2 n1 = N * normalize(data[index].xy - data[index - 1].xy);
		const vec2 n2 = N * normalize(data[index + 1].xy - data[index].xy);
		return length(n1 + n2) < 1e-5 ? n1 : normalize(n1 + n2);
	}
}

void main(void)
{
	//data
	const float w = width;
	const float h = height;
	const float m = min(w, h);
	//NDC points positions
	const vec2 n1 = vec2(m / w, m / h) * data[gl_InstanceID + 0].xy;
	const vec2 n2 = vec2(m / w, m / h) * data[gl_InstanceID + 1].xy;
	//screen points positions
	const vec2 p1 = (n1 + 1) / 2 * vec2(width, height);
	const vec2 p2 = (n2 + 1) / 2 * vec2(width, height);
	//normal directions
	const vec2 v1 = normal(gl_InstanceID + 0);
	const vec2 v2 = normal(gl_InstanceID + 1);
	//screen vertex position
	const float t = (quad_points[gl_VertexID].x + 1) / 2;
	const vec2 pv = mix(p1, p2, t) + quad_points[gl_VertexID].y * lines_width / 2 * mix(v1, v2, t);
	//NDC vertex position
	vertex_length = data[gl_InstanceID + uint(t)].z;
	const vec2 nv = 2 * pv * vec2(1 / width, 1 / height) - 1;
	//clip vertex position
	gl_Position = vec4(nv, 0, 1);
}