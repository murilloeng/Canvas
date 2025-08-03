//canvas
#include "Canvas/Canvas/inc/Objects/2D/Rectangle.hpp"

//test
#include "Canvas/Test/inc/examples.hpp"

void examples::objects::rectangles(canvas::Scene* scene)
{
	//data
	const uint32_t n = 2;
	const float r = 1.0f / n;
	//objects
	for(uint32_t i = 0; i < n; i++)
	{
		for(uint32_t j = 0; j < n; j++)
		{
			scene->add_object(new canvas::objects::Rectangle);
			((canvas::objects::Rectangle*) scene->object(i * n + j))->width(r);
			((canvas::objects::Rectangle*) scene->object(i * n + j))->height(r);
			((canvas::objects::Rectangle*) scene->object(i * n + j))->radius(r / 4);
			((canvas::objects::Rectangle*) scene->object(i * n + j))->color_fill({0, 0, 1});
			((canvas::objects::Rectangle*) scene->object(i * n + j))->position({2 * r * j - 1, 2 * r * i - 1, 0});
		}
	}
}