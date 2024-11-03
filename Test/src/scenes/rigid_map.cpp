//std
#include <cmath>
#include <chrono>

//canvas
#include "Canvas/inc/GPU/Shader.hpp"
#include "Canvas/inc/GPU/Program.hpp"
#include "Canvas/inc/Scene/Scene.hpp"

//test
#include "Canvas/Test/inc/examples.hpp"
#include "Canvas/Test/inc/managers/GLFW.hpp"

//static data
static canvas::Scene* scene;
static canvas::Program program;
static std::chrono::high_resolution_clock::time_point t0;

//scene
static void scene_setup(void)
{
	//shaders
	program.vertex_shader()->path("Test/shd/rigid-map.vert");
	program.fragment_shader()->path("Test/shd/rigid-map.frag");
	//setup
	program.setup();
	//scene
	scene->programs().push_back(&program);
}
static void scene_update(void)
{
	return;
}

void examples::scenes::rigid_map(int argc, char** argv)
{
	//data
	GLFW app(argc, argv, "shd/");
	app.callback_idle(scene_update);
	//scene
	scene = app.scene();
	scene_setup();
	//update
	scene->update(true);
	scene->camera().bound();
	scene->camera().apply();
	scene->camera().update();
	t0 = std::chrono::high_resolution_clock::now();
	//start
	app.start();
	scene->clear_objects(false);
}