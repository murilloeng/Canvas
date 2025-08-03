//std
#include <cmath>

//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Objects/2D/Surface.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

void examples::objects::surfaces(canvas::Scene* scene)
{
	//data
	canvas::objects::Surface* surface = new canvas::objects::Surface;
	//surface
	surface->mesh(0, 100);
	surface->mesh(1, 100);
	surface->domain(0, 0, -1);
	surface->domain(0, 1, +1);
	surface->domain(1, 0, -1);
	surface->domain(1, 1, +1);
	surface->color_fill({0, 0, 1});
	surface->position([] (float s1, float s2) {
		const float r = 4 * float(M_PI) * sqrtf(s1 * s1 + s2 * s2);
		return canvas::vec3(s1, s2, fabsf(r) < 1e-5 ? 1 : sinf(r) / r);
	});
	//scene
	scene->add_object(surface);
}