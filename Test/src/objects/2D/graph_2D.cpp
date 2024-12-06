//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Objects/2D/Graph_2D.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

void examples::objects::graph_2D(canvas::Scene* scene)
{
	scene->add_font("times");
	scene->add_object(new canvas::objects::Graph_2D);
}