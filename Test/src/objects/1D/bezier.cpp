//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Objects/0D/Point.hpp"
#include "Canvas/Canvas/inc/Objects/1D/Bezier.hpp"
#include "Canvas/Canvas/inc/Objects/1D/Polyline.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

void examples::objects::bezier(canvas::Scene* scene)
{
	//data
	canvas::objects::Point* point_1 = new canvas::objects::Point;
	canvas::objects::Point* point_2 = new canvas::objects::Point;
	canvas::objects::Point* point_3 = new canvas::objects::Point;
	canvas::objects::Point* point_4 = new canvas::objects::Point;
	canvas::objects::Point* point_5 = new canvas::objects::Point;
	canvas::objects::Bezier* curve_1 = new canvas::objects::Bezier;
	canvas::objects::Bezier* curve_2 = new canvas::objects::Bezier;
	canvas::objects::Polyline* polyline_1 = new canvas::objects::Polyline;
	canvas::objects::Polyline* polyline_2 = new canvas::objects::Polyline;
	//point 1
	point_1->color_dot("red");
	point_1->position({0, 0, 0});
	//point 2
	point_2->color_dot("red");
	point_2->position({1, 1, 0});
	//point 3
	point_3->color_dot("green");
	point_3->position({1, 0, 0});
	//point 4
	point_4->color_dot("green");
	point_4->position({0, 0.5f, 0});
	//point 5
	point_5->color_dot("green");
	point_5->position({0.5f, 1, 0});
	//polyline 1
	polyline_1->vertices().push_back(point_1->position());
	polyline_1->vertices().push_back(point_3->position());
	polyline_1->vertices().push_back(point_2->position());
	//polyline 2
	polyline_2->vertices().push_back(point_1->position());
	polyline_2->vertices().push_back(point_4->position());
	polyline_2->vertices().push_back(point_5->position());
	polyline_2->vertices().push_back(point_2->position());
	//curve 1
	curve_1->color_stroke("blue");
	curve_1->point(0, point_1->position());
	curve_1->point(1, point_2->position());
	curve_1->control(0, point_3->position());
	curve_1->type(canvas::objects::Bezier::Type::Conic);
	//curve 1
	curve_2->color_stroke("blue");
	curve_2->point(0, point_1->position());
	curve_2->point(1, point_2->position());
	curve_2->control(0, point_4->position());
	curve_2->control(1, point_5->position());
	curve_2->type(canvas::objects::Bezier::Type::Cubic);
	//scene
	scene->add_object(point_1);
	scene->add_object(point_2);
	scene->add_object(point_3);
	scene->add_object(point_4);
	scene->add_object(point_5);
	scene->add_object(curve_1);
	scene->add_object(curve_2);
	scene->add_object(polyline_1);
	scene->add_object(polyline_2);
}