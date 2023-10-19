//std
#include <cstdio>
#include <cstdlib>

//os
#ifdef _WIN32
#include <Windows.h>
#endif

//ext
#include "../external/cpp/inc/GL/glew.h"
#include "../external/cpp/inc/GL/freeglut.h"

//canvas
#include "inc/Scene/Scene.hpp"
#include "inc/Managers/Glut.hpp"
#include "inc/Objects/Object.hpp"

//examples
#include "inc/Examples/examples.hpp"

canvas::Glut* app;
typedef void(*scene_fun)(canvas::Scene*);

static scene_fun tests[] = {
	examples::objects::arcs,
	examples::objects::cubes,
	examples::objects::lines,
	examples::objects::quads,
	examples::objects::points,
	examples::objects::circles,
	examples::objects::spheres,
	examples::objects::splines,
	examples::objects::grid_2D,
	examples::objects::grid_3D,
	examples::objects::polylines,
	examples::objects::triangles,
	examples::objects::cylinders
};

static void callback_idle(void)
{
	for(canvas::objects::Object* object : app->scene()->objects())
	{
		object->rotate({0, 4e-2, 0}, false);
	}
	app->scene()->update();
	glutPostRedisplay();
}
static void callback_keyboard(unsigned char key, int x1, int x2)
{
	//data
	static unsigned index = 0;
	const unsigned size = sizeof(tests) / sizeof(scene_fun);
	//callback
	if(key == 'n')
	{
		app->scene()->clear_objects();
		tests[index](app->scene());
		app->scene()->update();
		app->scene()->bound();
		index = (index + 1) % size;
		glutPostRedisplay();
	}
	else
	{
		canvas::Glut::callback_keyboard(key, x1, x2);
	}
}

int main(int argc, char** argv)
{
	//glut
	app = new canvas::Glut(argc, argv);
	//setup
	examples::objects::spheres(app->scene());
	app->scene()->update();
	app->scene()->bound();
	//callbacks
	glutIdleFunc(callback_idle);
	glutKeyboardFunc(callback_keyboard);
	//start
	app->start();
	//delete
	delete app;
	//return
	return EXIT_SUCCESS;
}