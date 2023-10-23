//canvas
#include "inc/Scene/Scene.hpp"
#include "inc/Objects/2D/Triangle.hpp"

//examples
#include "inc/examples.hpp"

namespace examples
{
	namespace objects
	{
		void triangles(canvas::Scene* scene)
		{
			//data
			const unsigned n = 10;
			const float r = 1.0f / n;
			//objects
			for(unsigned i = 0; i < n; i++)
			{
				for(unsigned j = 0; j < n; j++)
				{
					scene->add_object(new canvas::objects::Triangle);
					((canvas::objects::Triangle*) scene->object(n * i + j))->scale(r);
					((canvas::objects::Triangle*) scene->object(n * i + j))->color_fill({0, 0, 1});
					((canvas::objects::Triangle*) scene->object(n * i + j))->point(0, {-1, -1, 0});
					((canvas::objects::Triangle*) scene->object(n * i + j))->point(1, {+1, -1, 0});
					((canvas::objects::Triangle*) scene->object(n * i + j))->point(2, {+0, +1, 0});
					((canvas::objects::Triangle*) scene->object(n * i + j))->shift({2 * r * j + r - 1, 2 * r * i + r - 1, 0});
				}
			}
		}
	}
}