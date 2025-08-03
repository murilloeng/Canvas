//canvas
#include "Canvas/Canvas/inc/Objects/2D/Rectangle.hpp"

//test
#include "Canvas/Test/inc/examples.hpp"

void examples::objects::rectangles(canvas::Scene* scene)
{
	//data
	const uint32_t n = 10;
	const float r = 1.0f / n;
	//objects
	for(uint32_t i = 0; i < n; i++)
	{
		for(uint32_t j = 0; j < n; j++)
		{
			scene->add_object(new canvas::objects::Rectangle);
		}
	}
}