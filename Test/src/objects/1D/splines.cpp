//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Objects/1D/Spline.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

void examples::objects::splines(canvas::Scene* scene)
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