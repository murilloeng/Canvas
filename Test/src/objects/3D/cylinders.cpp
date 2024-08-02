//canvas
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Objects/3D/Cylinder.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

namespace examples
{
	namespace objects
	{
		void cylinders(canvas::Scene* scene)
		{
			//data
			const uint32_t n = 10;
			const float s = 1.0f / n;
			//objects
			for(uint32_t i = 0; i < n; i++)
			{
				for(uint32_t j = 0; j < n; j++)
				{
					const float x1 = 2 * j * s - 1 + s;
					const float x2 = 2 * i * s - 1 + s;
					scene->add_object(new canvas::objects::Cylinder);
					((canvas::objects::Cylinder*) scene->object(n * i + j))->scale(s / 2);
					((canvas::objects::Cylinder*) scene->object(n * i + j))->shift({x1, x2, 0});
					((canvas::objects::Cylinder*) scene->object(n * i + j))->color_fill({0.0f, 0.0f, 1.0f});
					((canvas::objects::Cylinder*) scene->object(n * i + j))->color_stroke({1.0f, 1.0f, 1.0f});
				}
			}
		}
	}
}