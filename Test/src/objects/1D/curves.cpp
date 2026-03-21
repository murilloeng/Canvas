//std
#include <cmath>

//canvas
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Objects/1D/Curve.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

void examples::objects::curves(canvas::Scene* scene)
{
	//data
	const uint32_t nt = 5;
	const uint32_t nm = 200;
	canvas::objects::Curve* curve = new canvas::objects::Curve;
	//curve
	curve->mesh(nm);
	curve->position([] (float s){
		return canvas::vec3(cosf(2 * nt * float(M_PI) * s), sinf(2 * nt * float(M_PI) * s), s);
	});
	//scene
	scene->add_object(curve);
}