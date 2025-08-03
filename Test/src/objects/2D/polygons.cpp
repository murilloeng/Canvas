//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Objects/2D/Polygon.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

void examples::objects::polygons(canvas::Scene* scene)
{
	//data
	canvas::objects::Polygon* polygon = new canvas::objects::Polygon;
	//polygon
	polygon->loops().push_back( 0);
	polygon->loops().push_back( 4);
	polygon->loops().push_back( 8);
	polygon->loops().push_back(12);
	polygon->loops().push_back(16);
	polygon->loops().push_back(20);
	polygon->color_fill({0, 0, 1});
	polygon->vertices().push_back({-3, -3});
	polygon->vertices().push_back({+3, -3});
	polygon->vertices().push_back({+3, +3});
	polygon->vertices().push_back({-3, +3});
	polygon->vertices().push_back({-2, -2});
	polygon->vertices().push_back({-2, -1});
	polygon->vertices().push_back({-1, -1});
	polygon->vertices().push_back({-1, -2});
	polygon->vertices().push_back({+1, -2});
	polygon->vertices().push_back({+1, -1});
	polygon->vertices().push_back({+2, -1});
	polygon->vertices().push_back({+2, -2});
	polygon->vertices().push_back({+1, +1});
	polygon->vertices().push_back({+1, +2});
	polygon->vertices().push_back({+2, +2});
	polygon->vertices().push_back({+2, +1});
	polygon->vertices().push_back({-2, +1});
	polygon->vertices().push_back({-2, +2});
	polygon->vertices().push_back({-1, +2});
	polygon->vertices().push_back({-1, +1});
	//scene
	scene->add_object(polygon);
}