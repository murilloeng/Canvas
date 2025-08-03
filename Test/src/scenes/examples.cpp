//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"

//test
#include "Canvas/Test/inc/Engine.hpp"
#include "Canvas/Test/inc/examples.hpp"

//static data
static canvas::Scene* scene;
static uint32_t example_index = 0;

//callabcks
static void callback_key(int32_t key, int32_t, int32_t)
{
	//data
	using namespace examples::objects;
	void (*examples[])(canvas::Scene*) = { 
		points, 
		arcs, lines, arrows, curves, polylines, splines, 
		circles, grid_2D, quads, polygons, triangles, rectangles, 
		cubes, cylinders, spheres, surfaces, 
		group, images, text, latex, palettes, container, graph_2D
	};
	const uint32_t ne = sizeof(examples) / sizeof(void(*)(canvas::Scene*));
	//scene
	if(key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT)
	{
		//index
		if(key == GLFW_KEY_RIGHT) example_index = (example_index + 1) % ne;
		if(key == GLFW_KEY_LEFT) example_index = (example_index ? example_index : ne) - 1;
		//scene
		scene->clear_objects(true);
		examples[example_index](scene);
		//update
		scene->update(true);
		scene->camera().bound();
		scene->camera().update();
	}
}

void examples::scenes::examples(void)
{
	//data
	Engine engine;
	//callbacks
	engine.user_key(callback_key);
	//scene
	scene = engine.scene();
	examples::objects::points(scene);
	//update
	scene->update(true);
	scene->camera().bound();
	scene->camera().update();
	//start
	engine.start();
}