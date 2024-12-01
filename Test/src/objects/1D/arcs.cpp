//std
#include <cmath>

//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Objects/1D/Arc.hpp"
#include "Canvas/Canvas/inc/Objects/1D/Arrow.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

namespace examples
{
	namespace objects
	{
		void arcs(canvas::Scene* scene)
		{
			//data
			const uint32_t n = 10;
			const float r = 1.0f / n;
			//objects
			for(uint32_t i = 0; i < n; i++)
			{
				for(uint32_t j = 0; j < n; j++)
				{
					//objects
					canvas::objects::Arc* arc = new canvas::objects::Arc;
					canvas::objects::Arrow* arrow = new canvas::objects::Arrow;
					//arc
					arc->radius(r);
					arc->angle(0, 0);
					arc->color_stroke({1, 1, 1});
					arc->angle(1, 2 * float(M_PI) * (n * i + j) / n / n);
					arc->shift({2 * r * j + r - 1, 2 * r * i + r - 1, 0});
					//arrow
					arrow->path(arc);
					arrow->width(r / 5);
					arrow->height(r / 5);
					arrow->parameter(0.5f);
					//scene
					scene->add_object(arc);
					scene->add_object(arrow);
				}
			}
		}
	}
}