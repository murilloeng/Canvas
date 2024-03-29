//canvas
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Objects/1D/Arrow.hpp"
#include "Canvas/inc/Objects/1D/Spline.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

namespace examples
{
	namespace objects
	{
		void splines(canvas::Scene* scene)
		{
			//data
			const float r = 9.00e-01f;
			const float s = 5.00e-01f;
			canvas::objects::Spline* spline = new canvas::objects::Spline;
			//spline
			spline->mesh(100);
			spline->point(0, {+r, 0, 0});
			spline->point(1, {0, +r, 0});
			spline->add_point({-r, 0, 0});
			spline->add_point({0, -r, 0});
			spline->add_point({+r, 0, 0});
			spline->add_arrow(0.50f, true);
			spline->add_arrow(1.50f, true);
			spline->add_arrow(2.50f, true);
			spline->add_arrow(3.50f, true);
			spline->arrow(0)->width(0.10f);
			spline->arrow(1)->width(0.10f);
			spline->arrow(2)->width(0.10f);
			spline->arrow(3)->width(0.10f);
			spline->arrow(0)->height(0.10f);
			spline->arrow(1)->height(0.10f);
			spline->arrow(2)->height(0.10f);
			spline->arrow(3)->height(0.10f);
			spline->control(0, 1, {+r, +s, 0});
			spline->control(1, 0, {+s, +r, 0});
			spline->control(1, 1, {-s, +r, 0});
			spline->control(2, 0, {-r, +s, 0});
			spline->control(2, 1, {-r, -s, 0});
			spline->control(3, 0, {-s, -r, 0});
			spline->control(3, 1, {+s, -r, 0});
			spline->control(4, 0, {+r, -s, 0});
			//scene
			scene->add_object(spline);
		}
	}
}