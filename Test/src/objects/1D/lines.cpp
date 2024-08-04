//canvas
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Objects/1D/Line.hpp"
#include "Canvas/inc/Objects/1D/Arrow.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

namespace examples
{
	namespace objects
	{
		void lines(canvas::Scene* scene)
		{
			//data
			float s = 0.90f;
			const uint32_t n = 5;
			const float x1[] = {-1, +1, +1, -1};
			const float x2[] = {-1, -1, +1, +1};
			//objects
			for(uint32_t i = 0; i < n; i++)
			{
				for(uint32_t j = 0; j < 4; j++)
				{
					//objects
					canvas::objects::Line* line = new canvas::objects::Line;
					canvas::objects::Arrow* arrow = new canvas::objects::Arrow;
					//scene
					scene->add_object(line);
					scene->add_object(arrow);
					//line
					line->point(0, {s * x1[(j + 0) % 4], s * x2[(j + 0) % 4], 0});
					line->point(1, {s * x1[(j + 1) % 4], s * x2[(j + 1) % 4], 0});
					//arrow
					arrow->path(line);
					arrow->width(s / 10);
					arrow->height(s / 10);
					arrow->parameter(0.50f);
				}
				s /= 2;
			}
		}
	}
}