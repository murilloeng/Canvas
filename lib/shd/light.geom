#version 460 core

in vec4 vertex_color[];

out vec4 geometry_color;
out vec3 geometry_normal;
out vec3 geometry_position;

uniform mat4 camera_matrix;
uniform vec3 camera_position;

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

void main(void)
{
	//normal
	vec3 x0 = gl_in[0].gl_Position.xyz;
	vec3 x1 = gl_in[1].gl_Position.xyz;
	vec3 x2 = gl_in[2].gl_Position.xyz;
	geometry_normal = normalize(cross(x1 - x0, x2 - x0));
	//vertex 1
	geometry_position = x0;
	geometry_color = vertex_color[0];
	gl_Position = camera_matrix * vec4(x0, 1);
	EmitVertex();
	//vertex 2
	geometry_position = x1;
	geometry_color = vertex_color[1];
	gl_Position = camera_matrix * vec4(x1, 1);
	EmitVertex();
	//vertex 3
	geometry_position = x2;
	geometry_color = vertex_color[2];
	gl_Position = camera_matrix * vec4(x2, 1);
	EmitVertex();
	//triangle
	EndPrimitive();
}