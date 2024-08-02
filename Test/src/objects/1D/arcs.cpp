//std
#include <cmath>

//canvas
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Objects/1D/Arc.hpp"
#include "Canvas/inc/Objects/1D/Arrow.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

namespace examples
{
	namespace objects
	{
		void arcs(canvas::Scene* scene)
		{
			//data
			const unsigned n = 10;
			const float r = 1.0f / n;
			//objects
			for(unsigned i = 0; i < n; i++)
			{
				for(unsigned j = 0; j < n; j++)
				{
					scene->add_object(new canvas::objects::Arc);
					((canvas::objects::Arc*) scene->object(n * i + j))->radius(r);
					((canvas::objects::Arc*) scene->object(n * i + j))->angle(0, 0);
					((canvas::objects::Arc*) scene->object(n * i + j))->add_arrow(0.5, true);
					((canvas::objects::Arc*) scene->object(n * i + j))->color_fill({0, 0, 1});
					((canvas::objects::Arc*) scene->object(n * i + j))->color_stroke({1, 1, 1});
					((canvas::objects::Arc*) scene->object(n * i + j))->arrow(0)->width(r / 5);
					((canvas::objects::Arc*) scene->object(n * i + j))->arrow(0)->height(r / 5);
					((canvas::objects::Arc*) scene->object(n * i + j))->angle(1, 2 * float(M_PI) * (n * i + j) / n / n);
					((canvas::objects::Arc*) scene->object(n * i + j))->shift({2 * r * j + r - 1, 2 * r * i + r - 1, 0});
				}
			}
		}
	}
}