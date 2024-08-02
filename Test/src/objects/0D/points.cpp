//canvas
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Objects/0D/Point.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

namespace examples
{
	namespace objects
	{
		void points(canvas::Scene* scene)
		{
			//data
			const unsigned n = 10;
			const float r = 1.0f / n;
			//objects
			for(unsigned i = 0; i < n; i++)
			{
				for(unsigned j = 0; j < n; j++)
				{
					scene->add_object(new canvas::objects::Point);
					((canvas::objects::Point*) scene->object(n * i + j))->position({2 * r * j + r - 1, 2 * r * i + r - 1, 0});
				}
			}
		}
	}
}