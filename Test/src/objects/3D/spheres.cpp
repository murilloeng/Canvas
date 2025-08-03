//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Objects/3D/Sphere.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

void examples::objects::spheres(canvas::Scene* scene)
{
	//data
	const uint32_t n = 10;
	const float s = 1.0f / n;
	//objects
	for(uint32_t i = 0; i < n; i++)
	{
		for(uint32_t j = 0; j < n; j++)
		{
			const float x1 = 2 * j * s - 1 + s;
			const float x2 = 2 * i * s - 1 + s;
			scene->add_object(new canvas::objects::Sphere);
			((canvas::objects::Sphere*) scene->object(n * i + j))->scale(s);
			((canvas::objects::Sphere*) scene->object(n * i + j))->shift({x1, x2, 0});
			((canvas::objects::Sphere*) scene->object(n * i + j))->color_fill({0.0f, 0.0f, 1.0f});
			((canvas::objects::Sphere*) scene->object(n * i + j))->color_stroke({1.0f, 1.0f, 1.0f});
		}
	}
}