//std
#include <cmath>

//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Objects/Graph/Curve.hpp"
#include "Canvas/Canvas/inc/Objects/Graph/Graph.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

void examples::objects::graphs(canvas::Scene* scene)
{
	//data
	const uint32_t np = 1000;
	canvas::objects::Graph* graph = new canvas::objects::Graph;
	canvas::objects::graphs::Curve* curve = new canvas::objects::graphs::Curve;
	std::vector<canvas::vec2>& data = curve->data();
	//curve data
	data.resize(np);
	for(uint32_t i = 0; i < np; i++)
	{
		const float x = 2 * float(i) / (np - 1) - 1;
		data[i] = {x, sinf(10 * float(M_PI) * x) * expf(-2 * (x + 1))};
	}
	//curve lines
	curve->lines().width(2);
	curve->lines().dash_type(4);
	curve->lines().dash_size(50);
	curve->lines().color("blue");
	curve->lines().enabled(true);
	//curve points
	curve->points().type(15);
	curve->points().skip(20);
	curve->points().size(10);
	curve->points().color("red");
	curve->points().enabled(true);
	//graph
	graph->curves().push_back(curve);
	graph->frame().axis(0).label("Horizontal label");
	//scene
	scene->add_font("arial");
	scene->add_object(graph);
	glDisable(GL_DEPTH_TEST);
}