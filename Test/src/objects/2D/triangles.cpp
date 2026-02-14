//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Objects/2D/Triangle.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

void examples::objects::triangles(canvas::Scene* scene)
{
	//data
	const uint32_t n = 10;
	const float r = 1.0f / n;
	//objects
	for(uint32_t i = 0; i < n; i++)
	{
		for(uint32_t j = 0; j < n; j++)
		{
			scene->add_object(new canvas::objects::Triangle);
			((canvas::objects::Triangle*) scene->object(n * i + j))->scale(r);
			((canvas::objects::Triangle*) scene->object(n * i + j))->color({0, 0, 1});
			((canvas::objects::Triangle*) scene->object(n * i + j))->position(0, {-1, -1, 0});
			((canvas::objects::Triangle*) scene->object(n * i + j))->position(1, {+1, -1, 0});
			((canvas::objects::Triangle*) scene->object(n * i + j))->position(2, {+0, +1, 0});
			((canvas::objects::Triangle*) scene->object(n * i + j))->shift({2 * r * j + r - 1, 2 * r * i + r - 1, 0});
		}
	}
}