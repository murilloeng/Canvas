#version 460 core

out vec4 vertex_color;

layout(location = 2) in vec4 color;
layout(location = 0) in vec3 position_1;
layout(location = 1) in vec3 position_2;
layout(location = 3) in float thickness;

layout(std140, binding = 1) uniform screen { float width, height; };
layout(std140, binding = 0) uniform camera { mat4 view, projection; };

vec2 points[] = {vec2(-1, -1), vec2(+1, -1), vec2(+1, +1), vec2(-1, +1)};

void main(void)
{
	//color
	vertex_color = color;
	//clip points positions
	vec4 c1 = projection * view * vec4(position_1, 1);
	vec4 c2 = projection * view * vec4(position_2, 1);
	//NDC points positions
	vec2 n1 = c1.xy / c1.w;
	vec2 n2 = c2.xy / c2.w;
	//screen points positions
	vec2 p1 = (n1 + 1) / 2 * vec2(width, height);
	vec2 p2 = (n2 + 1) / 2 * vec2(width, height);
	//line directions
	vec2 d1 = normalize(p2 - p1);
	vec2 d2 = vec2(-d1.y, +d1.x);
	//screen vertex position
	float t = (points[gl_VertexID].x + 1) / 2;
	vec2 pv = mix(p1, p2, t) + points[gl_VertexID].y * thickness / 2 * d2;
	//NDC vertex position
	vec2 nv = 2 * pv * vec2(1 / width, 1 / height) - 1;
	//clip vertex position
	float z = mix(c1.z, c2.z, t);
	float w = mix(c1.w, c2.w, t);
	gl_Position = vec4(nv, z, w);
}