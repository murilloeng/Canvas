//canvas
#include "inc/Scene/Scene.hpp"
#include "inc/Objects/Arc.hpp"
#include "inc/Objects/Type.hpp"

//examples
#include "inc/Examples/examples.hpp"

namespace examples
{
	void arcs(canvas::Scene* scene)
	{
		//data
		const unsigned n = 10;
		const float r = 1.0f / n;
		//objects
		for(unsigned i = 0; i < n; i++)
		{
			for(unsigned j = 0; j < n; j++)
			{
				scene->add_object(canvas::objects::type::arc);
				((canvas::objects::Arc*) scene->object(n * i + j))->radius(r);
				((canvas::objects::Arc*) scene->object(n * i + j))->angle(0, 0);
				((canvas::objects::Arc*) scene->object(n * i + j))->fill_color({0, 0, 1});
				((canvas::objects::Arc*) scene->object(n * i + j))->stroke_color({1, 1, 1});
				((canvas::objects::Arc*) scene->object(n * i + j))->angle(1, 2 * M_PI * float(n * i + j) / n / n);
				((canvas::objects::Arc*) scene->object(n * i + j))->shift({2 * r * j + r - 1, 2 * r * i + r - 1, 0});
			}
		}
	}
}