//canvas
#include "Canvas/lib/inc/Scene/Scene.hpp"
#include "Canvas/lib/inc/Objects/1D/Line.hpp"
#include "Canvas/lib/inc/Objects/1D/Arrow.hpp"

//examples
#include "Canvas/test/inc/examples.hpp"

namespace examples
{
	namespace objects
	{
		void lines(canvas::Scene* scene)
		{
			//data
			float s = 0.90f;
			const unsigned n = 5;
			const float x1[] = {-1, +1, +1, -1};
			const float x2[] = {-1, -1, +1, +1};
			//objects
			for(unsigned i = 0; i < n; i++)
			{
				for(unsigned j = 0; j < 4; j++)
				{
					scene->add_object(new canvas::objects::Line);
					((canvas::objects::Line*) scene->object(4 * i + j))->add_arrow(0.50f, true);
					((canvas::objects::Line*) scene->object(4 * i + j))->arrow(0)->width(s / 10);
					((canvas::objects::Line*) scene->object(4 * i + j))->arrow(0)->height(s / 10);
					((canvas::objects::Line*) scene->object(4 * i + j))->point(0, {s * x1[(j + 0) % 4], s * x2[(j + 0) % 4], 0});
					((canvas::objects::Line*) scene->object(4 * i + j))->point(1, {s * x1[(j + 1) % 4], s * x2[(j + 1) % 4], 0});
				}
				s /= 2;
			}
		}
	}
}