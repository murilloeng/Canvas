//canvas
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Objects/2D/Grid_3D.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

namespace examples
{
	namespace objects
	{
		void grid_3D(canvas::Scene* scene)
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
					scene->add_object(new canvas::objects::Grid_3D);
					((canvas::objects::Grid_3D*) scene->object(n * i + j))->scale(0.5 * s);
					((canvas::objects::Grid_3D*) scene->object(n * i + j))->shift({x1, x2, 0});
					((canvas::objects::Grid_3D*) scene->object(n * i + j))->color_fill({0, 0, 1});
					((canvas::objects::Grid_3D*) scene->object(n * i + j))->color_stroke({1, 1, 1});
				}
			}
		}
	}
}