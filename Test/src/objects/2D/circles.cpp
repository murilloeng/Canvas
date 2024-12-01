//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Objects/2D/Circle.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

namespace examples
{
	namespace objects
	{
		void circles(canvas::Scene* scene)
		{
			//data
			const uint32_t n = 10;
			const float r = 1.0f / n;
			//objects
			for(uint32_t i = 0; i < n; i++)
			{
				for(uint32_t j = 0; j < n; j++)
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