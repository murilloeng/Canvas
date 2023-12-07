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

static float t = 0;
static canvas::Glut* app;
static unsigned index_light = 0;
static unsigned index_example = 0;
typedef void(*test_fun)(canvas::Scene*);

test_fun list[] = {
	//0D
	examples::objects::points,
	//1D
	examples::objects::arcs,
	examples::objects::lines,
	examples::objects::arrows,
	examples::objects::curves,
	examples::objects::splines,
	examples::objects::polylines,
	//2D
	examples::objects::quads,
	examples::objects::circles,
	examples::objects::grid_2D,
	examples::objects::grid_3D,
	examples::objects::polygons,
	examples::objects::surfaces,
	examples::objects::triangles,
	//3D
	examples::objects::cubes,
	examples::objects::spheres,
	examples::objects::cylinders,
	//image
	examples::objects::text,
	examples::objects::latex,
	examples::objects::images,
	//scenes
	examples::scenes::beam_1,
	examples::scenes::tensegrity_chair
};
unsigned idle_index[] = {
	//0D
	0,
	//1D
	1, 1, 1, 1, 1, 1,
	//2D
	1, 1, 1, 1, 1, 0, 1,
	//3D
	1, 1, 1,
	//image
	0, 0, 0,
	//scenes
	0, 0
};

static void callback_idle(void)
{
	//time
	const float fr = app->scene()->frame_rate();
	const std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	//objects
	for(canvas::objects::Object* object : app->scene()->objects())
	{
		object->rotate({0, float(M_PI) / fr, 0}, false);
	}
	app->scene()->update(true);
	//light
	if(index_light == 1)
	{
		t += 2 * float(M_PI) / fr;
		app->scene()->light().position({0, 0, sinf(t) + 1});
		app->scene()->light().update_shaders();
	}
	if(index_light == 2)
	{
		const canvas::vec3 xl = app->scene()->light().position();
		app->scene()->light().position(canvas::vec3(0, float(M_PI) / fr, 0).quaternion().rotate(xl));
		app->scene()->light().update_shaders();
	}
	//draw
	glutPostRedisplay();
	//wait
	const unsigned tf = (unsigned) round(1000 / fr);
	const std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	const unsigned dt = (unsigned) round(std::chrono::duration<float, std::milli>(t2 - t1).count());
	std::this_thread::sleep_for(std::chrono::milliseconds((dt < tf) * (tf - dt)));
}
static void callback_keyboard(unsigned char key, int x1, int x2)
{
	//data
	const unsigned nf = sizeof(list) / sizeof(test_fun);
	//callback
	if(key == 'n')
	{
		//index
		index_example = (index_example + 1) % nf;
		//setup
		t = 0;
		app->scene()->clear_fonts();
		app->scene()->clear_latex();
		app->scene()->clear_images();
		app->scene()->clear_objects();
		app->scene()->background({0, 0, 0});
		app->scene()->light().position({0, 0, +1});
		app->scene()->light().update_shaders();
		app->scene()->camera().rotation(canvas::quat::view_x3());
		//redraw
		list[index_example](app->scene());
		//update
		app->scene()->update(true);
		app->scene()->camera().bound();
		app->scene()->camera().update_shaders();
		//idle
		if(idle_index[index_example] == 0) glutIdleFunc(nullptr);
		else if(idle_index[index_example] == 1) glutIdleFunc(callback_idle);
		//swap
		glutPostRedisplay();
	}
	if(key == '0')
	{
		index_light = 0;
		app->scene()->light().position({0, 0, 1});
		app->scene()->light().update_shaders();
		glutPostRedisplay();
	}
	if(key == '1')
	{
		index_light = 1;
		glutPostRedisplay();
	}
	if(key == '2')
	{
		index_light = 2;
		app->scene()->light().position({0, 0, 1});
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
	list[0](app->scene());
	app->scene()->update(true);
	//callbacks
	glutKeyboardFunc(callback_keyboard);
	//start
	app->start();
	//delete
	delete app;
	//return
	return EXIT_SUCCESS;
}