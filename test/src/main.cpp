//std
#include <cmath>
#include <thread>
#include <chrono>
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

static canvas::Glut* app;
static unsigned index = 0;
typedef void(*test_fun)(canvas::Scene*);

test_fun list[] = {
	examples::objects::arcs,
	examples::objects::text,
	examples::objects::quads,
	examples::objects::lines,
	examples::objects::cubes,
	examples::objects::latex,
	examples::objects::points,
	examples::objects::arrows,
	examples::objects::curves,
	examples::objects::images,
	examples::objects::splines,
	examples::objects::circles,
	examples::objects::spheres,
	examples::objects::grid_2D,
	examples::objects::grid_3D,
	examples::objects::polygons,
	examples::objects::surfaces,
	examples::objects::polylines,
	examples::objects::triangles,
	examples::objects::cylinders
};

static void callback_idle(void)
{
	//time
	using namespace std::chrono;
	const float fr = app->scene()->frame_rate();
	const high_resolution_clock::time_point t1 = high_resolution_clock::now();
	//objects
	for(canvas::objects::Object* object : app->scene()->objects())
	{
		object->rotate({0, float(M_PI_4) / fr, 0}, false);
	}
	app->scene()->update();
	//draw
	glutPostRedisplay();
	//time
	const high_resolution_clock::time_point t2 = high_resolution_clock::now();
	//wait
	std::this_thread::sleep_for(duration<float, std::milli>(1000 / fr) - duration<float, std::milli>(t2 - t1));
}
static void callback_keyboard(unsigned char key, int x1, int x2)
{
	//data
	const unsigned nf = sizeof(list) / sizeof(test_fun);
	//callback
	if(key == 'n')
	{
		index = (index + 1) % nf;
		app->scene()->clear_objects();
		list[index](app->scene());
		app->scene()->update();
		app->scene()->camera().bound();
		app->scene()->camera().update_shaders();
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
	app = new canvas::Glut(argc, argv, "../lib/shd/");
	//setup
	// examples::objects::spheres(app->scene());
	examples::scenes::beam_1(app->scene());
	app->scene()->update();
	//light
	app->scene()->light().position({0, 0, +1});
	app->scene()->light().update_shaders();
	//callbacks
	// glutIdleFunc(callback_idle);
	glutKeyboardFunc(callback_keyboard);
	//start
	app->start();
	//delete
	delete app;
	//return
	return EXIT_SUCCESS;
}