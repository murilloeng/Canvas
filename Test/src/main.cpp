//std
#include <cmath>
#include <chrono>
#include <cstdlib>

//test
#include "Canvas/inc/Objects/1D/Line.hpp"

#include "Canvas/Test/inc/examples.hpp"
#include "Canvas/Test/inc/Interpreter.hpp"
#include "Canvas/Test/inc/managers/Glut.hpp"

static canvas::Scene* scene;
static uint32_t example_index = 0;
static std::chrono::high_resolution_clock::time_point t0;

static void callback_idle(void)
{
	//data
	using namespace std::chrono;
	const high_resolution_clock::time_point tn = high_resolution_clock::now();
	//state
	const double q = duration_cast<microseconds>(tn - t0).count() / 1e6;
	//scene
	((canvas::objects::Line*) scene->object(0))->point(0, canvas::vec3());

}
static void callback_special(int key, int, int)
{
	//data
	using namespace examples::objects;
	void (*examples[])(canvas::Scene*) = { 
		points, 
		arcs, lines, arrows, curves, polylines, splines, 
		circles, grid_2D, quads, polygons, triangles, 
		cubes, cylinders, spheres, surfaces, 
		images, text, palettes
	};
	const uint32_t ne = sizeof(examples) / sizeof(void(*)(canvas::Scene*));
	//scene
	if(key == (int32_t) Glut::key_left || key == (int32_t) Glut::key_right)
	{
		//index
		if(key == (int32_t) Glut::key_right) example_index = (example_index + 1) % ne;
		if(key == (int32_t) Glut::key_left) example_index = (example_index ? example_index : ne) - 1;
		//scene
		scene->clear_objects(true);
		examples[example_index](scene);
		//update
		scene->update(true);
		scene->camera().bound();
		scene->camera().apply();
		scene->camera().update();
	}
}

int main(int argc, char** argv)
{
	// //data
	// Glut app(argc, argv, "shd/");
	// app.callback_special(callback_special);
	// //scene
	// scene = app.scene();
	// examples::objects::points(scene);
	// //update
	// scene->update(true);
	// scene->camera().bound();
	// scene->camera().apply();
	// scene->camera().update();
	// t0 = std::chrono::high_resolution_clock::now();
	// //start
	// app.start();
	examples::scenes::tensegrity_chair(argc, argv);
	//return
	return EXIT_SUCCESS;
}