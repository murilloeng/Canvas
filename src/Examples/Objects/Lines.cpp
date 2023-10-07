//canvas
#include "inc/Scene/Scene.hpp"
#include "inc/Objects/Type.hpp"
#include "inc/Objects/Curves/Line.hpp"
#include "inc/Objects/Curves/Arrow.hpp"

//examples
#include "inc/Examples/examples.hpp"

namespace examples
{
	namespace objects
	{
		void lines(canvas::Scene* scene)
		{
			//data
			float s = 0.90f;
			const unsigned n = 5;
			canvas::objects::Line* line;
			const float x1[] = {-1, +1, +1, -1};
			const float x2[] = {-1, -1, +1, +1};
			//objects
			for(unsigned i = 0; i < n; i++)
			{
				for(unsigned j = 0; j < 4; j++)
				{
					line = new canvas::objects::Line;
					line->point(0, {s * x1[(j + 0) % 4], s * x2[(j + 0) % 4], 0});
					line->point(1, {s * x1[(j + 1) % 4], s * x2[(j + 1) % 4], 0});
					line->add_arrow(0.50f, true);
					line->arrow(0)->width(s / 10);
					line->arrow(0)->height(s / 10);
					scene->add_object(line);
				}
				s /= 2;
			}
		}
	}
}