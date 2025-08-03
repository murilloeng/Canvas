//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Objects/1D/Arrow.hpp"
#include "Canvas/Canvas/inc/Objects/1D/Polyline.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

void examples::objects::polylines(canvas::Scene* scene)
{
	//data
	const float w = 1.00e-01f;
	const float h = 1.00e-01f;
	const float t = 1.00e-02f;
	canvas::objects::Polyline* polyline;
	//spline
	polyline = new canvas::objects::Polyline;
	polyline->vertices().push_back({-w / 2, -h / 2 - t, 0});
	polyline->vertices().push_back({+w / 2, -h / 2 - t, 0});
	polyline->vertices().push_back({+w / 2, -h / 2, 0});
	polyline->vertices().push_back({+t / 2, -h / 2, 0});
	polyline->vertices().push_back({+t / 2, +h / 2, 0});
	polyline->vertices().push_back({+w / 2, +h / 2, 0});
	polyline->vertices().push_back({+w / 2, +h / 2 + t, 0});
	polyline->vertices().push_back({-w / 2, +h / 2 + t, 0});
	polyline->vertices().push_back({-w / 2, +h / 2, 0});
	polyline->vertices().push_back({-t / 2, +h / 2, 0});
	polyline->vertices().push_back({-t / 2, -h / 2, 0});
	polyline->vertices().push_back({-w / 2, -h / 2, 0});
	polyline->vertices().push_back({-w / 2, -h / 2 - t, 0});
	//arrows
	for(uint32_t i = 0; i < 12; i++)
	{
		canvas::objects::Arrow* arrow = new canvas::objects::Arrow;
		arrow->path(polyline);
		arrow->width(2.50e-03f);
		arrow->height(2.50e-03f);
		arrow->parameter(i + 0.5f);
		scene->add_object(arrow);
	}
	//scene
	scene->add_object(polyline);
}