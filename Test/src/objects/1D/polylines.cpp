//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
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
	//scene
	scene->add_object(polyline);
}