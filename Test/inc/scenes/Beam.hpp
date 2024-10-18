#pragma once

//canvas
#include "Canvas/inc/Math/vec2.hpp"
#include "Canvas/inc/Objects/Geometry.hpp"

class Beam : public canvas::objects::Geometry
{
public:
	//constructors
	Beam(void);

	//destructor
	~Beam(void);

	//data
	float offset(float);
	float offset(void) const;

	float thickness(float);
	float thickness(void) const;

protected:
	//buffers
	void ibo_fill_data(void);
	void vbo_fill_data(void);
	void ibo_stroke_data(void);
	void vbo_stroke_data(void);
	void buffers_size(void) override;
	void buffers_data(void) const override;

	//data
	float m_offset;
	float m_thickness;
	canvas::vec2 m_nodes;
	const static uint32_t nc = 40;
};