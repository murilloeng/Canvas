#pragma once

namespace canvas
{
	float fn(float, unsigned);
	float dfn(float, unsigned);
	float funt(float, unsigned);
	float cost(float, unsigned);
	float sint(float, unsigned);
	
	float norm(const float*);
	float inner(const float*, const float*);

	float min(const float*, unsigned*, bool);
	float max(const float*, unsigned*, bool);

	void triad(const float*, float*, float*);
	void cross(float*, const float*, const float*);
}