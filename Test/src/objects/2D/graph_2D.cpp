//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Objects/2D/Graph_2D.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

void examples::objects::graph_2D(canvas::Scene* scene)
{
	//data
	canvas::objects::Graph_2D* graph = new canvas::objects::Graph_2D;
	//graph
	graph->labels_index(0, 0);
	graph->labels_index(1, 1);
	graph->labels_latex(0, false);
	graph->labels_latex(1, false);
	//scene
	scene->add_font("times");
	// scene->add_latex("$ \\gamma_1 $");
	// scene->add_latex("$ \\gamma_2 $");
	//objects
	scene->add_object(graph);
}