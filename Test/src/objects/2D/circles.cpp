//canvas
#include "inc/Scene/Scene.hpp"
#include "inc/Objects/2D/Circle.hpp"

//examples
#include "inc/examples.hpp"

namespace examples
{
	namespace objects
	{
		void circles(canvas::Scene* scene)
		{
			//data
			const unsigned n = 10;
			const float r = 1.0f / n;
			//objects
			for(unsigned i = 0; i < n; i++)
			{
				for(unsigned j = 0; j < n; j++)
				{
					scene->add_object(new canvas::objects::Circle);
					((canvas::objects::Circle*) scene->object(n * i + j))->radius(0.9f * r);
					((canvas::objects::Circle*) scene->object(n * i + j))->color_fill({0, 0, 1});
					((canvas::objects::Circle*) scene->object(n * i + j))->color_stroke({1, 1, 1});
					((canvas::objects::Circle*) scene->object(n * i + j))->shift({2 * r * j + r - 1, 2 * r * i + r - 1, 0});
				}
			}
		}
	}
}