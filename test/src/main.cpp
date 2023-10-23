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
	for(canvas::objects::Object* object : app->scene()->objects())
	{
		object->rotate({0, 4e-2, 0}, false);
	}
	app->scene()->update();
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	//glut
	app = new canvas::Glut(argc, argv, "../lib/shd/");
	//setup
	examples::scenes::tensegrity_chair(app->scene());
	// examples::objects::splines(app->scene());
	app->scene()->update();
	app->scene()->bound();
	//callbacks
	// glutIdleFunc(callback_idle);
	//start
	app->start();
	//delete
	delete app;
	//return
	return EXIT_SUCCESS;
}