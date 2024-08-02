//std
#include <cmath>
#include <cstdlib>

//canvas
#include "Canvas/inc/Windows/Glut.hpp"
#include "Canvas/Test/inc/examples.hpp"

//data
static canvas::Scene* scene;

int main(int argc, char** argv)
{
	//data
	canvas::windows::Glut app(argc, argv, "shd/");
	//scene
	scene = app.scene();
	examples::objects::polygons(scene);
	scene->update(true);
	scene->camera().bound();
	scene->camera().apply();
	scene->camera().update();
	//start
	app.start();

	//return
	return EXIT_SUCCESS;
}
