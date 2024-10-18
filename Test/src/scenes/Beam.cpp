//test
#include "Canvas/test/inc/scenes/Beam.hpp"

//constructor
Beam::Beam(void) : m_offset(0)
{
	return;
}

//destrutor
Beam::~Beam(void)
{
	return;
}

//data
float Beam::offset(void) const
{
	return m_offset;
}
float Beam::offset(float offset)
{
	return m_offset = offset;
}

float Beam::thickness(void) const
{
	return m_thickness;
}
float Beam::thickness(float thickness)
{
	return m_thickness = thickness;
}

//buffers
void Beam::ibo_fill_data(void)
{
	
}
void Beam::vbo_fill_data(void)
{
	
}
void Beam::ibo_stroke_data(void)
{
	
}
void Beam::vbo_stroke_data(void)
{
	
}
void Beam::buffers_size(void)
{
	m_ibo_size[2] = 6 * nc * m_fill;
	m_ibo_size[1] = 4 * (nc + 1) * m_stroke;
	m_vbo_size[0] = 2 * (nc + 1) * (m_fill + m_stroke);
}
void Beam::buffers_data(void) const
{

}