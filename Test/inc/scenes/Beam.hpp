#pragma once

//canvas
#include "Canvas/inc/Math/vec3.hpp"
#include "Canvas/inc/Objects/Geometry.hpp"

class Beam : public canvas::objects::Geometry
{
public:
	//constructors
	Beam(void);

	//destructor
	~Beam(void);

	//data
	float height(float);
	float height(void) const;

	float thickness(float);
	float thickness(void) const;

	canvas::vec3 node(uint32_t) const;
	canvas::vec3 node(uint32_t, canvas::vec3);

	canvas::vec3 major_axis(void) const;
	canvas::vec3 major_axis(canvas::vec3);

protected:
	//buffers
	void vbo_fill_data(void) const;
	void ibo_fill_data(void) const;
	void vbo_stroke_data(void) const;
	void ibo_stroke_data(void) const;

	void buffers_size(void) override;
	void buffers_data(void) const override;

	//data
	float m_height;
	float m_thickness;
	canvas::vec3 m_nodes[2];
	canvas::vec3 m_major_axis;
	const static uint32_t m_nc = 40;
};