#pragma once

namespace canvas
{
	float norm(const float*);
	float inner(const float*, const float*);

	float min(const float*, unsigned*, bool);
	float max(const float*, unsigned*, bool);

	void triad(const float*, float*, float*);
	void cross(float*, const float*, const float*);
}