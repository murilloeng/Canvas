//canvas
#include "inc/Scene/Scene.hpp"
#include "inc/Objects/Type.hpp"
#include "inc/Objects/Curves/Arc.hpp"
#include "inc/Objects/Curves/Arrow.hpp"

//examples
#include "inc/Examples/examples.hpp"

namespace examples
{
	namespace objects
	{
		void arcs(canvas::Scene* scene)
		{
			//data
			const unsigned n = 10;
			const float r = 1.0f / n;
			canvas::objects::Arc* arc;
			//objects
			for(unsigned i = 0; i < n; i++)
			{
				for(unsigned j = 0; j < n; j++)
				{
					arc = new canvas::objects::Arc;
					arc->radius(r);
					arc->angle(0, 0);
					arc->add_arrow(0.5, true);
					arc->color_fill({0, 0, 1});
					arc->color_stroke({1, 1, 1});
					arc->arrow(0)->width(r / 5);
					arc->arrow(0)->height(r / 5);
					arc->angle(1, 2 * M_PI * float(n * i + j) / n / n);
					arc->shift({2 * r * j + r - 1, 2 * r * i + r - 1, 0});
					scene->add_object(arc);
				}
			}
		}
	}
}