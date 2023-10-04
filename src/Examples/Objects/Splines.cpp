//canvas
#include "inc/Scene/Scene.hpp"
#include "inc/Objects/Type.hpp"
#include "inc/Objects/Spline.hpp"

//examples
#include "inc/Examples/examples.hpp"

namespace examples
{
	namespace objects
	{
		void splines(canvas::Scene* scene)
		{
			//data
			const float r = 9.00e-01;
			const float s = 5.00e-01;
			//scene
			scene->add_object(canvas::objects::type::spline);
			//objects
			((canvas::objects::Spline*) scene->object(0))->point(0, {+r, 0, 0});
			((canvas::objects::Spline*) scene->object(0))->point(1, {0, +r, 0});
			((canvas::objects::Spline*) scene->object(0))->add_point({-r, 0, 0});
			((canvas::objects::Spline*) scene->object(0))->add_point({0, -r, 0});
			((canvas::objects::Spline*) scene->object(0))->add_point({+r, 0, 0});
			((canvas::objects::Spline*) scene->object(0))->control(0, 1, {+r, +s, 0});
			((canvas::objects::Spline*) scene->object(0))->control(1, 0, {+s, +r, 0});
			((canvas::objects::Spline*) scene->object(0))->control(1, 1, {-s, +r, 0});
			((canvas::objects::Spline*) scene->object(0))->control(2, 0, {-r, +s, 0});
			((canvas::objects::Spline*) scene->object(0))->control(2, 1, {-r, -s, 0});
			((canvas::objects::Spline*) scene->object(0))->control(3, 0, {-s, -r, 0});
			((canvas::objects::Spline*) scene->object(0))->control(3, 1, {+s, -r, 0});
			((canvas::objects::Spline*) scene->object(0))->control(4, 0, {+r, -s, 0});
		}
	}
}