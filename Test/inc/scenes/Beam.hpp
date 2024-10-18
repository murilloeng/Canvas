#pragma once

//canvas
#include "Canvas/inc/Objects/Geometry.hpp"

class Beam : public canvas::objects::Geometry
{
public:
	//constructors
	Beam(void);

	//destructor
	~Beam(void);

protected:
	//buffers
	void buffers_size(void) override;
	void buffers_data(void) const override;
};