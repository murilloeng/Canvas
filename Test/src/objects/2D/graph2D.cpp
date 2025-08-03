//std
#include <cmath>

//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Objects/Graph/Graph2D.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

void examples::objects::graph2D(canvas::Scene* scene)
{
	//data
	const uint32_t np = 40;
	float* x11 = (float*) alloca(np * sizeof(float));
	float* x12 = (float*) alloca(np * sizeof(float));
	float* x21 = (float*) alloca(np * sizeof(float));
	float* x22 = (float*) alloca(np * sizeof(float));
	canvas::objects::graphs::Curve2D* c1 = new canvas::objects::graphs::Curve2D;
	canvas::objects::graphs::Curve2D* c2 = new canvas::objects::graphs::Curve2D;
	canvas::objects::graphs::Graph2D* graph = new canvas::objects::graphs::Graph2D;
	//curves
	for(uint32_t i = 0; i < np; i++)
	{
		x11[i] = x21[i] = 2 * float(M_PI) * i / (np - 1);
		x12[i] = 2 * cosf(x11[i]);
		x22[i] = 2 * sinf(x21[i]);
	}
	c1->lines(true);
	c2->lines(true);
	c1->points(true);
	c2->points(true);
	c1->data(np, x11, x12);
	c2->data(np, x21, x22);
	c1->points_color({1, 0, 0});
	c2->points_color({0, 0, 1});
	c1->lines_color({0, 1, 0});
	c2->lines_color({1, 1, 0});
	//scene
	scene->add_font("times");
	//graph
	graph->range(0, 0, +0.0f);
	graph->range(0, 1, +7.0f);
	graph->range(1, 0, -1.0f);
	graph->range(1, 1, +1.0f);
	graph->curves().push_back(c1);
	graph->curves().push_back(c2);
	//objects
	scene->add_object(graph);
}