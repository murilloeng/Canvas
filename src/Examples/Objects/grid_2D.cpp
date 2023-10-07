//canvas
#include "inc/Scene/Scene.hpp"
#include "inc/Objects/Type.hpp"
#include "inc/Objects/Surfaces/Grid_2D.hpp"

//examples
#include "inc/Examples/examples.hpp"

namespace examples
{
	namespace objects
	{
		void grid_2D(canvas::Scene* scene)
		{
			//data
			const unsigned n = 10;
			const float s = 1.0f / n;
			//objects
			for(unsigned i = 0; i < n; i++)
			{
				for(unsigned j = 0; j < n; j++)
				{
					const float x1 = 2 * j * s - 1 + s;
					const float x2 = 2 * i * s - 1 + s;
					scene->add_object(canvas::objects::type::grid_2D);
					((canvas::objects::Grid_2D*) scene->object(n * i + j))->scale(0.5 * s);
					((canvas::objects::Grid_2D*) scene->object(n * i + j))->shift({x1, x2, 0});
					((canvas::objects::Grid_2D*) scene->object(n * i + j))->color_fill({0, 0, 1});
					((canvas::objects::Grid_2D*) scene->object(n * i + j))->color_stroke({1, 1, 1});
				}
			}
		}
	}
}