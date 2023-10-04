//canvas
#include "inc/Scene/Scene.hpp"
#include "inc/Objects/Type.hpp"
#include "inc/Objects/Curves/Line.hpp"

//examples
#include "inc/Examples/examples.hpp"

namespace examples
{
	namespace objects
	{
		void lines(canvas::Scene* scene)
		{
			//data
			const unsigned n = 200;
			const float s = 9.50e-01;
			const float x1[] = {-1, +1, +1, -1};
			const float x2[] = {-1, -1, +1, +1};
			//objects
			float s1 = 1, s2 = s;
			for(unsigned i = 0; i < n; i++)
			{
				s1 *= s;
				s2 *= s;
				const unsigned i1 = (i + 0) % 4;
				const unsigned i2 = (i + 1) % 4;
				scene->add_object(canvas::objects::type::line);
				((canvas::objects::Line*) scene->object(i))->point(0, {s1 * x1[i1], s1 * x2[i1], 0});
				((canvas::objects::Line*) scene->object(i))->point(1, {s2 * x1[i2], s2 * x2[i2], 0});
			}
		}
	}
}