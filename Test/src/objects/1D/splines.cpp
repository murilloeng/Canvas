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
			canvas::objects::Arrow* arrow_1 = new canvas::objects::Arrow;
			canvas::objects::Arrow* arrow_2 = new canvas::objects::Arrow;
			canvas::objects::Arrow* arrow_3 = new canvas::objects::Arrow;
			canvas::objects::Arrow* arrow_4 = new canvas::objects::Arrow;
			canvas::objects::Spline* spline = new canvas::objects::Spline;
			//spline
			spline->mesh(100);
			spline->point(0, {+r, 0, 0});
			spline->point(1, {0, +r, 0});
			spline->add_point({-r, 0, 0});
			spline->add_point({0, -r, 0});
			spline->add_point({+r, 0, 0});
			spline->control(0, 1, {+r, +s, 0});
			spline->control(1, 0, {+s, +r, 0});
			spline->control(1, 1, {-s, +r, 0});
			spline->control(2, 0, {-r, +s, 0});
			spline->control(2, 1, {-r, -s, 0});
			spline->control(3, 0, {-s, -r, 0});
			spline->control(3, 1, {+s, -r, 0});
			spline->control(4, 0, {+r, -s, 0});
			//arrows
			arrow_1->path(spline);
			arrow_2->path(spline);
			arrow_3->path(spline);
			arrow_4->path(spline);
			arrow_1->width(0.10f);
			arrow_2->width(0.10f);
			arrow_3->width(0.10f);
			arrow_4->width(0.10f);
			arrow_1->height(0.10f);
			arrow_2->height(0.10f);
			arrow_3->height(0.10f);
			arrow_4->height(0.10f);
			arrow_1->parameter(0.50f);
			arrow_2->parameter(1.50f);
			arrow_3->parameter(2.50f);
			arrow_4->parameter(3.50f);
			//scene
			scene->add_object(spline);
			scene->add_object(arrow_1);
			scene->add_object(arrow_2);
			scene->add_object(arrow_3);
			scene->add_object(arrow_4);
		}
	}
}