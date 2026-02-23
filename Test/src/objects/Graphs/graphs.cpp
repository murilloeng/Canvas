//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Objects/Graph/Curve.hpp"
#include "Canvas/Canvas/inc/Objects/Graph/Graph.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

void examples::objects::graphs(canvas::Scene* scene)
{
	//data
	const uint32_t np = 100;
	canvas::objects::Graph* graph = new canvas::objects::Graph;
	canvas::objects::graphs::Curve* curve = new canvas::objects::graphs::Curve;
	std::vector<canvas::vec2>& points = curve->points();
	//curve
	points.resize(np);
	for(uint32_t i = 0; i < np; i++)
	{
		const float x = 2 * float(i) / (np - 1) - 1;
		points[i] = {x, x};
	}
	//graph
	graph->curves().push_back(curve);
	//scene
	scene->add_font("arial");
	scene->add_object(graph);
	glDisable(GL_DEPTH_TEST);
}