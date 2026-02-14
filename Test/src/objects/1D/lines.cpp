//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Objects/1D/Line.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

void examples::objects::lines(canvas::Scene* scene)
{
	//data
	float s = 0.90f;
	const uint32_t n = 10;
	const float x1[] = {-1, +1, +1, -1};
	const float x2[] = {-1, -1, +1, +1};
	const char* colors[] = {"red", "green", "blue"};
	//objects
	for(uint32_t i = 0; i < n; i++)
	{
		for(uint32_t j = 0; j < 4; j++)
		{
			//objects
			canvas::objects::Line* line = new canvas::objects::Line;
			//scene
			scene->add_object(line);
			//line
			line->color(colors[i % 3]);
			line->position(0, {s * x1[(j + 0) % 4], s * x2[(j + 0) % 4], 0});
			line->position(1, {s * x1[(j + 1) % 4], s * x2[(j + 1) % 4], 0});
		}
		s *= 0.8;
	}
}