//std
#include <cmath>
#include <cstdlib>

//test
#include "Canvas/Test/inc/examples.hpp"
#include "Canvas/Test/inc/managers/Glut.hpp"

int main(int argc, char** argv)
{
	//data
	Glut app(argc, argv, "shd/");
	//scene
	examples::objects::spheres(app.scene());
	app.scene()->update(true);
	app.scene()->camera().bound();
	app.scene()->camera().apply();
	app.scene()->camera().update();
	//start
	app.start();
	//return
	return EXIT_SUCCESS;
}
