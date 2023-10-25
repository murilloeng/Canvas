//std
#include <cstdio>
#include <cstdlib>

//os
#ifdef _WIN32
#include <Windows.h>
#endif

//ext
#include "ext/inc/GL/glew.h"
#include "ext/inc/GL/freeglut.h"

//canvas
#include "inc/Scene/Scene.hpp"
#include "inc/Managers/Glut.hpp"
#include "inc/Objects/Object.hpp"

//examples
#include "inc/examples.hpp"

canvas::Glut* app;

static void callback_idle(void)
{
	const canvas::vec3 xc(0, 0, 3);
	const canvas::vec3 xl = app->scene()->light().position();
	for(canvas::objects::Object* object : app->scene()->objects())
	{
		// object->rotate({0, 1e-3, 0}, false);
	}
	app->scene()->update();
	app->scene()->light().position(xc + canvas::vec3(0, 1e-3, 0).quaternion().rotate(xl - xc));
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	//glut
	app = new canvas::Glut(argc, argv, "../lib/shd/");
	//setup
	// examples::scenes::tensegrity_chair(app->scene());
	examples::objects::cubes(app->scene());
	app->scene()->update();
	app->scene()->bound();
	//callbacks
	glutIdleFunc(callback_idle);
	//start
	app->start();
	//delete
	delete app;
	//return
	return EXIT_SUCCESS;
}