//canvas
#include "inc/Scene/Scene.hpp"
#include "inc/Objects/Type.hpp"
#include "inc/Objects/Path.hpp"

//examples
#include "inc/Examples/examples.hpp"

namespace examples
{
	namespace objects
	{
		void paths(canvas::Scene* scene)
		{
			//data
			const float w = 1.00e-01;
			const float h = 1.00e-01;
			const float t = 1.00e-02;
			//scene
			scene->add_object(canvas::objects::type::path);
			//objects
			scene->object(0)->scale(9);
			((canvas::objects::Path*) scene->object(0))->add_point({-w / 2, -h / 2 - t, 0});
			((canvas::objects::Path*) scene->object(0))->add_point({+w / 2, -h / 2 - t, 0});
			((canvas::objects::Path*) scene->object(0))->add_point({+w / 2, -h / 2, 0});
			((canvas::objects::Path*) scene->object(0))->add_point({+t / 2, -h / 2, 0});
			((canvas::objects::Path*) scene->object(0))->add_point({+t / 2, +h / 2, 0});
			((canvas::objects::Path*) scene->object(0))->add_point({+w / 2, +h / 2, 0});
			((canvas::objects::Path*) scene->object(0))->add_point({+w / 2, +h / 2 + t, 0});
			((canvas::objects::Path*) scene->object(0))->add_point({-w / 2, +h / 2 + t, 0});
			((canvas::objects::Path*) scene->object(0))->add_point({-w / 2, +h / 2, 0});
			((canvas::objects::Path*) scene->object(0))->add_point({-t / 2, +h / 2, 0});
			((canvas::objects::Path*) scene->object(0))->add_point({-t / 2, -h / 2, 0});
			((canvas::objects::Path*) scene->object(0))->add_point({-w / 2, -h / 2, 0});
			((canvas::objects::Path*) scene->object(0))->add_point({-w / 2, -h / 2 - t, 0});
		}
	}
}