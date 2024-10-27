//std
#include <cmath>

//canvas
#include "Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/inc/Objects/Tessellator.hpp"

//test
#include "Canvas/Test/inc/scenes/Beam.hpp"

//constructor
Beam::Beam(void) : m_height(0), m_thickness(0), m_nodes{{0, 0, 0}, {0, 0, 0}}, m_major_axis{0, 0, 1}
{
	return;
}

//destrutor
Beam::~Beam(void)
{
	return;
}

//data
float Beam::height(void) const
{
	return m_height;
}
float Beam::height(float height)
{
	return m_height = height;
}

float Beam::thickness(void) const
{
	return m_thickness;
}
float Beam::thickness(float thickness)
{
	return m_thickness = thickness;
}

canvas::vec3 Beam::node(uint32_t index) const
{
	return m_nodes[index];
}
canvas::vec3 Beam::node(uint32_t index, canvas::vec3 node)
{
	return m_nodes[index] = node;
}

canvas::vec3 Beam::major_axis(void) const
{
	return m_major_axis;
}
canvas::vec3 Beam::major_axis(canvas::vec3 major_axis)
{
	return m_major_axis = major_axis;
}

//buffers
void Beam::vbo_fill_data(void) const
{
	//data
	const float h = m_height;
	const float w = m_thickness;
	const canvas::vec3 x1 = m_nodes[0];
	const canvas::vec3 x2 = m_nodes[1];
	const canvas::vec3 t3 = m_major_axis;
	const canvas::vec3 t1 = (x2 - x1) / (x2 - x1).norm();
	canvas::vertices::Model3D* vbo_ptr_1 = vbo_data_model_3D() + 0 * (m_nc + 1);
	canvas::vertices::Model3D* vbo_ptr_2 = vbo_data_model_3D() + 1 * (m_nc + 1);
	canvas::vertices::Model3D* vbo_ptr_3 = vbo_data_model_3D() + 2 * (m_nc + 1);
	canvas::vertices::Model3D* vbo_ptr_4 = vbo_data_model_3D() + 3 * (m_nc + 1);
	const canvas::vec3 t2 = t3.cross(t1);
	//shift
	vbo_ptr_1 += 4 * (m_nc + 1) * m_stroke;
	vbo_ptr_2 += 4 * (m_nc + 1) * m_stroke;
	vbo_ptr_3 += 4 * (m_nc + 1) * m_stroke;
	vbo_ptr_4 += 4 * (m_nc + 1) * m_stroke;
	//vbo data
	for(uint32_t i = 0; i <= m_nc; i++)
	{
		vbo_ptr_1[i].m_color = m_color_fill;
		vbo_ptr_2[i].m_color = m_color_fill;
		vbo_ptr_3[i].m_color = m_color_fill;
		vbo_ptr_4[i].m_color = m_color_fill;
		const float q = float(M_PI) * i / m_nc;
		vbo_ptr_1[i].m_position = x1 + h / 2 * (cosf(q) * t2 - sinf(q) * t1) - w / 2 * t3;
		vbo_ptr_2[i].m_position = x2 - h / 2 * (cosf(q) * t2 - sinf(q) * t1) - w / 2 * t3;
		vbo_ptr_3[i].m_position = x1 + h / 2 * (cosf(q) * t2 - sinf(q) * t1) + w / 2 * t3;
		vbo_ptr_4[i].m_position = x2 - h / 2 * (cosf(q) * t2 - sinf(q) * t1) + w / 2 * t3;
	}
}
void Beam::ibo_fill_data(void) const
{
	//data
	uint32_t* ibo_ptr = ibo_data(2);
	const uint32_t nv = 2 * (m_nc + 1);
	uint32_t vbo_index = m_vbo_index[0] + 2 * nv * m_stroke;
	uint32_t* triangles = (uint32_t*) alloca(3 * (nv - 2) * sizeof(uint32_t));
	canvas::vec3* vertices = (canvas::vec3*) alloca(nv * sizeof(canvas::vec3));
	canvas::vertices::Model3D* vbo_ptr = vbo_data_model_3D() + 2 * nv * m_stroke;
	//vertices
	for(uint32_t i = 0; i < nv; i++)
	{
		vertices[i] = vbo_ptr[i].m_position;
	}
	//tessellation
	const uint32_t loops[] = {0, nv};
	canvas::objects::Tessellator(vertices, loops, 1, triangles).tessellate();
	//ibo data
	for(uint32_t i = 0; i < 2 * m_nc; i++)
	{
		ibo_ptr[0 * m_nc + 3 * i + 0] = vbo_index + 0 * nv + triangles[3 * i + 0];
		ibo_ptr[0 * m_nc + 3 * i + 1] = vbo_index + 0 * nv + triangles[3 * i + 2];
		ibo_ptr[0 * m_nc + 3 * i + 2] = vbo_index + 0 * nv + triangles[3 * i + 1];
		ibo_ptr[6 * m_nc + 3 * i + 0] = vbo_index + 1 * nv + triangles[3 * i + 0];
		ibo_ptr[6 * m_nc + 3 * i + 1] = vbo_index + 1 * nv + triangles[3 * i + 1];
		ibo_ptr[6 * m_nc + 3 * i + 2] = vbo_index + 1 * nv + triangles[3 * i + 2];
	}
	for(uint32_t i = 0; i < nv; i++)
	{
		ibo_ptr[12 * m_nc + 6 * i + 0] = vbo_index + 0 * nv + (i + 0) % nv;
		ibo_ptr[12 * m_nc + 6 * i + 1] = vbo_index + 0 * nv + (i + 1) % nv;
		ibo_ptr[12 * m_nc + 6 * i + 2] = vbo_index + 1 * nv + (i + 0) % nv;
		ibo_ptr[12 * m_nc + 6 * i + 3] = vbo_index + 1 * nv + (i + 0) % nv;
		ibo_ptr[12 * m_nc + 6 * i + 4] = vbo_index + 0 * nv + (i + 1) % nv;
		ibo_ptr[12 * m_nc + 6 * i + 5] = vbo_index + 1 * nv + (i + 1) % nv;
	}
}
void Beam::vbo_stroke_data(void) const
{
	//data
	const float h = m_height;
	const float w = m_thickness;
	const canvas::vec3 x1 = m_nodes[0];
	const canvas::vec3 x2 = m_nodes[1];
	const canvas::vec3 t3 = m_major_axis;
	const canvas::vec3 t1 = (x2 - x1) / (x2 - x1).norm();
	canvas::vertices::Model3D* vbo_ptr_1 = vbo_data_model_3D() + 0 * (m_nc + 1);
	canvas::vertices::Model3D* vbo_ptr_2 = vbo_data_model_3D() + 1 * (m_nc + 1);
	canvas::vertices::Model3D* vbo_ptr_3 = vbo_data_model_3D() + 2 * (m_nc + 1);
	canvas::vertices::Model3D* vbo_ptr_4 = vbo_data_model_3D() + 3 * (m_nc + 1);
	const canvas::vec3 t2 = t3.cross(t1);
	//vbo data
	for(uint32_t i = 0; i <= m_nc; i++)
	{
		vbo_ptr_1[i].m_color = m_color_stroke;
		vbo_ptr_2[i].m_color = m_color_stroke;
		vbo_ptr_3[i].m_color = m_color_stroke;
		vbo_ptr_4[i].m_color = m_color_stroke;
		const float q = float(M_PI) * i / m_nc;
		vbo_ptr_1[i].m_position = x1 + h / 2 * (cosf(q) * t2 - sinf(q) * t1) - w / 2 * t3;
		vbo_ptr_2[i].m_position = x2 - h / 2 * (cosf(q) * t2 - sinf(q) * t1) - w / 2 * t3;
		vbo_ptr_3[i].m_position = x1 + h / 2 * (cosf(q) * t2 - sinf(q) * t1) + w / 2 * t3;
		vbo_ptr_4[i].m_position = x2 - h / 2 * (cosf(q) * t2 - sinf(q) * t1) + w / 2 * t3;
	}
}
void Beam::ibo_stroke_data(void) const
{
	//data
	uint32_t* ibo_ptr = ibo_data(1);
	const uint32_t nl = 2 * (m_nc + 1);
	//ibo data
	for(uint32_t i = 0; i < nl; i++)
	{
		ibo_ptr[2 * i + 0 + 0 * nl] = m_vbo_index[0] + (i + 0) % nl + 0 * nl;
		ibo_ptr[2 * i + 1 + 0 * nl] = m_vbo_index[0] + (i + 1) % nl + 0 * nl;
		ibo_ptr[2 * i + 0 + 2 * nl] = m_vbo_index[0] + (i + 0) % nl + 1 * nl;
		ibo_ptr[2 * i + 1 + 2 * nl] = m_vbo_index[0] + (i + 1) % nl + 1 * nl;
	}
}
void Beam::buffers_size(void)
{
	m_ibo_size[1] = 8 * (m_nc + 1) * m_stroke;
	m_ibo_size[2] = 12 * (2 * m_nc + 1) * m_fill;
	m_vbo_size[0] = 4 * (m_nc + 1) * (m_fill + m_stroke);
}
void Beam::buffers_data(void) const
{
	if(m_fill)
	{
		vbo_fill_data();
		ibo_fill_data();
	}
	if(m_stroke)
	{
		vbo_stroke_data();
		ibo_stroke_data();
	}
}