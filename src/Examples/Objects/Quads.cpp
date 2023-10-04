//canvas
#include "inc/Scene/Scene.hpp"
#include "inc/Objects/Type.hpp"
#include "inc/Objects/Quad.hpp"

//examples
#include "inc/Examples/examples.hpp"

namespace examples
{
	namespace objects
	{
		void quads(canvas::Scene* scene)
		{
			//data
			const unsigned n = 40;
			const float s = 2.0f / n;
			//objects
			for(unsigned i = 0; i < n; i++)
			{
				for(unsigned j = 0; j < n; j++)
				{
					scene->add_object(canvas::objects::type::quad);
					((canvas::objects::Quad*) scene->object(n * i + j))->fill_color({0, 0, 1});
					((canvas::objects::Quad*) scene->object(n * i + j))->stroke_color({1, 1, 1});
					((canvas::objects::Quad*) scene->object(n * i + j))->position(0, {(j + 0) * s - 1, (i + 0) * s - 1, 0});
					((canvas::objects::Quad*) scene->object(n * i + j))->position(1, {(j + 1) * s - 1, (i + 0) * s - 1, 0});
					((canvas::objects::Quad*) scene->object(n * i + j))->position(2, {(j + 1) * s - 1, (i + 1) * s - 1, 0});
					((canvas::objects::Quad*) scene->object(n * i + j))->position(3, {(j + 0) * s - 1, (i + 1) * s - 1, 0});
				}
			}
		}
	}
}