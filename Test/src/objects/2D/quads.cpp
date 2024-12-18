//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Objects/2D/Quad.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

namespace examples
{
	namespace objects
	{
		void quads(canvas::Scene* scene)
		{
			//data
			const uint32_t n = 40;
			const float s = 2.0f / n;
			//objects
			for(uint32_t i = 0; i < n; i++)
			{
				for(uint32_t j = 0; j < n; j++)
				{
					scene->add_object(new canvas::objects::Quad);
					((canvas::objects::Quad*) scene->object(n * i + j))->color_fill({0, 0, 1});
					((canvas::objects::Quad*) scene->object(n * i + j))->color_stroke({1, 1, 1});
					((canvas::objects::Quad*) scene->object(n * i + j))->point(0, {(j + 0) * s - 1, (i + 0) * s - 1, 0});
					((canvas::objects::Quad*) scene->object(n * i + j))->point(1, {(j + 1) * s - 1, (i + 0) * s - 1, 0});
					((canvas::objects::Quad*) scene->object(n * i + j))->point(2, {(j + 1) * s - 1, (i + 1) * s - 1, 0});
					((canvas::objects::Quad*) scene->object(n * i + j))->point(3, {(j + 0) * s - 1, (i + 1) * s - 1, 0});
				}
			}
		}
	}
}