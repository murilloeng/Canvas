//std
#include <chrono>
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
#include "inc/Models/Model.hpp"

#include "inc/Objects/Arc.hpp"
#include "inc/Objects/Cube.hpp"
#include "inc/Objects/Type.hpp"
#include "inc/Objects/Line.hpp"
#include "inc/Objects/Quad.hpp"
#include "inc/Objects/Point.hpp"
#include "inc/Objects/Circle.hpp"
#include "inc/Objects/Triangle.hpp"
#include "inc/Objects/Cylinder.hpp"

//static data
static canvas::Model* model;
static std::chrono::steady_clock::time_point t1, t2;

//examples
void example_1(void)
{
	//objects
	model->clear_objects();
	model->add_object(canvas::objects::type::line);
	model->add_object(canvas::objects::type::line);
	model->add_object(canvas::objects::type::line);
	model->add_object(canvas::objects::type::point);
	model->add_object(canvas::objects::type::point);
	model->add_object(canvas::objects::type::point);
	model->add_object(canvas::objects::type::point);
	model->add_object(canvas::objects::type::point);
	model->add_object(canvas::objects::type::point);
	model->add_object(canvas::objects::type::triangle);
	model->add_object(canvas::objects::type::triangle);
	model->add_object(canvas::objects::type::triangle);
	//lines
	((canvas::objects::Line*) model->object(0))->color(2, {1, 1, 1});
	((canvas::objects::Line*) model->object(1))->color(2, {1, 1, 1});
	((canvas::objects::Line*) model->object(2))->color(2, {1, 1, 1});
	((canvas::objects::Line*) model->object(0))->position(0, {-1.0, -1.0, +0.0});
	((canvas::objects::Line*) model->object(0))->position(1, {+1.0, -1.0, +0.0});
	((canvas::objects::Line*) model->object(1))->position(0, {+1.0, -1.0, +0.0});
	((canvas::objects::Line*) model->object(1))->position(1, {+0.0, +1.0, +0.0});
	((canvas::objects::Line*) model->object(2))->position(0, {+0.0, +1.0, +0.0});
	((canvas::objects::Line*) model->object(2))->position(1, {-1.0, -1.0, +0.0});
	//points
	((canvas::objects::Point*) model->object(3))->color({1, 0, 1});
	((canvas::objects::Point*) model->object(4))->color({1, 0, 1});
	((canvas::objects::Point*) model->object(5))->color({1, 0, 1});
	((canvas::objects::Point*) model->object(6))->color({1, 0, 1});
	((canvas::objects::Point*) model->object(7))->color({1, 0, 1});
	((canvas::objects::Point*) model->object(8))->color({1, 0, 1});
	((canvas::objects::Point*) model->object(3))->position({-1.0, -1.0, +0.0});
	((canvas::objects::Point*) model->object(4))->position({+0.0, -1.0, +0.0});
	((canvas::objects::Point*) model->object(5))->position({+1.0, -1.0, +0.0});
	((canvas::objects::Point*) model->object(6))->position({-0.5, +0.0, +0.0});
	((canvas::objects::Point*) model->object(7))->position({+0.5, +0.0, +0.0});
	((canvas::objects::Point*) model->object(8))->position({+0.0, +1.0, +0.0});
	//triangles
	((canvas::objects::Triangle*) model->object( 9))->fill(true);
	((canvas::objects::Triangle*) model->object(10))->fill(true);
	((canvas::objects::Triangle*) model->object(11))->fill(true);
	((canvas::objects::Triangle*) model->object( 9))->fill_color(3, {1, 0, 0});
	((canvas::objects::Triangle*) model->object(10))->fill_color(3, {0, 1, 0});
	((canvas::objects::Triangle*) model->object(11))->fill_color(3, {0, 0, 1});
	((canvas::objects::Triangle*) model->object( 9))->position(0, {-1.0, -1.0, +0.0});
	((canvas::objects::Triangle*) model->object( 9))->position(1, {+0.0, -1.0, +0.0});
	((canvas::objects::Triangle*) model->object( 9))->position(2, {-0.5, +0.0, +0.0});
	((canvas::objects::Triangle*) model->object(10))->position(0, {+0.0, -1.0, +0.0});
	((canvas::objects::Triangle*) model->object(10))->position(1, {+1.0, -1.0, +0.0});
	((canvas::objects::Triangle*) model->object(10))->position(2, {+0.5, +0.0, +0.0});
	((canvas::objects::Triangle*) model->object(11))->position(0, {-0.5, +0.0, +0.0});
	((canvas::objects::Triangle*) model->object(11))->position(1, {+0.5, +0.0, +0.0});
	((canvas::objects::Triangle*) model->object(11))->position(2, {-0.0, +1.0, +0.0});
}
void example_2(void)
{
	//data
	const unsigned nc = 10;
	const float rc = 1.0f / nc;
	//objects
	model->clear_objects();
	for(unsigned i = 0; i < nc; i++)
	{
		for(unsigned j = 0; j < nc; j++)
		{
			model->add_object(canvas::objects::type::circle);
			((canvas::objects::Circle*) model->object(nc * i + j))->draw(true);
			((canvas::objects::Circle*) model->object(nc * i + j))->fill(true);
			((canvas::objects::Circle*) model->object(nc * i + j))->radius(rc);
			((canvas::objects::Circle*) model->object(nc * i + j))->draw_color({1, 1, 1});
			((canvas::objects::Circle*) model->object(nc * i + j))->fill_color({0, 0, 1});
			((canvas::objects::Circle*) model->object(nc * i + j))->center({2 * rc * j + rc - 1, 2 * rc * i + rc - 1, 0});
		}
	}
}
void example_3(void)
{
	//data
	const unsigned nc = 10;
	const float rc = 1.0f / nc;
	//objects
	model->clear_objects();
	for(unsigned i = 0; i < nc; i++)
	{
		for(unsigned j = 0; j < nc; j++)
		{
			model->add_object(canvas::objects::type::arc);
			((canvas::objects::Arc*) model->object(nc * i + j))->draw(true);
			((canvas::objects::Arc*) model->object(nc * i + j))->fill(true);
			((canvas::objects::Arc*) model->object(nc * i + j))->radius(rc);
			((canvas::objects::Arc*) model->object(nc * i + j))->angle(0, 0);
			((canvas::objects::Arc*) model->object(nc * i + j))->draw_color({1, 1, 1});
			((canvas::objects::Arc*) model->object(nc * i + j))->fill_color({0, 0, 1});
			((canvas::objects::Arc*) model->object(nc * i + j))->angle(1, 2 * M_PI * float(nc * i + j) / nc / nc);
			((canvas::objects::Arc*) model->object(nc * i + j))->center({2 * rc * j + rc - 1, 2 * rc * i + rc - 1, 0});
		}
	}
}
void example_4(void)
{
	//data
	const unsigned nq = 40;
	const float sq = 2.0f / nq;
	//objects
	model->clear_objects();
	for(unsigned i = 0; i < nq; i++)
	{
		for(unsigned j = 0; j < nq; j++)
		{
			model->add_object(canvas::objects::type::quad);
			((canvas::objects::Quad*) model->object(nq * i + j))->draw(true);
			((canvas::objects::Quad*) model->object(nq * i + j))->fill(true);
			((canvas::objects::Quad*) model->object(nq * i + j))->draw_color(4, {1, 1, 1});
			((canvas::objects::Quad*) model->object(nq * i + j))->fill_color(4, {0, 0, 1});
			((canvas::objects::Quad*) model->object(nq * i + j))->position(0, {(j + 0) * sq - 1, (i + 0) * sq - 1, 0});
			((canvas::objects::Quad*) model->object(nq * i + j))->position(1, {(j + 1) * sq - 1, (i + 0) * sq - 1, 0});
			((canvas::objects::Quad*) model->object(nq * i + j))->position(2, {(j + 1) * sq - 1, (i + 1) * sq - 1, 0});
			((canvas::objects::Quad*) model->object(nq * i + j))->position(3, {(j + 0) * sq - 1, (i + 1) * sq - 1, 0});
		}
	}
}
void example_5(void)
{
	//data
	const unsigned nc = 10;
	const float sc = 1.0f / nc;
	//objects
	model->clear_objects();
	for(unsigned i = 0; i < nc; i++)
	{
		for(unsigned j = 0; j < nc; j++)
		{
			const float x1 = 2 * j * sc - 1 + sc;
			const float x2 = 2 * i * sc - 1 + sc;
			model->add_object(canvas::objects::type::cube);
			((canvas::objects::Cube*) model->object(nc * i + j))->draw(true);
			((canvas::objects::Cube*) model->object(nc * i + j))->fill(true);
			((canvas::objects::Cube*) model->object(nc * i + j))->draw_color(8, {1, 1, 1});
			((canvas::objects::Cube*) model->object(nc * i + j))->fill_color(8, {0, 0, 1, 0.5});
			((canvas::objects::Cube*) model->object(nc * i + j))->apply_affine(canvas::mat4::scaling(sc / 2));
			((canvas::objects::Cube*) model->object(nc * i + j))->apply_affine(canvas::mat4::translation({x1, x2, 0}));
		}
	}
}
void example_6(void)
{
	//data
	const unsigned nc = 10;
	const float sc = 1.0f / nc;
	//objects
	model->clear_objects();
	for(unsigned i = 0; i < nc; i++)
	{
		for(unsigned j = 0; j < nc; j++)
		{
			const float x1 = 2 * j * sc - 1 + sc;
			const float x2 = 2 * i * sc - 1 + sc;
			model->add_object(canvas::objects::type::cylinder);
			((canvas::objects::Cylinder*) model->object(nc * i + j))->draw(true);
			((canvas::objects::Cylinder*) model->object(nc * i + j))->fill(true);
			((canvas::objects::Cylinder*) model->object(nc * i + j))->draw_color({1, 1, 1});
			((canvas::objects::Cylinder*) model->object(nc * i + j))->fill_color({0, 0, 1});
			((canvas::objects::Cylinder*) model->object(nc * i + j))->apply_affine(canvas::mat4::scaling(sc / 2));
			((canvas::objects::Cylinder*) model->object(nc * i + j))->apply_affine(canvas::mat4::translation({x1, x2, 0}));
		}
	}
}

//setup
void setup(void)
{
	//create
	model = new canvas::Model;
	t1 = std::chrono::high_resolution_clock::now();
	//example
	example_6();
	//update
	model->update();
}
void cleanup(void)
{
	//delete
	delete model;
}

//callbacks
static void callback_idle(void)
{
	const unsigned nc = 10;
	const float sc = 1.0f / nc;
	for(unsigned i = 0; i < nc; i++)
	{
		for(unsigned j = 0; j < nc; j++)
		{
			const float x1 = 2 * j * sc - 1 + sc;
			const float x2 = 2 * i * sc - 1 + sc;
			model->object(j + nc * i)->apply_affine(canvas::mat4::rotation({x1, x2, 0}, {0, 2e-2, 0}));
		}
	}
	model->update();
	glutPostRedisplay();
}
static void callback_mouse(int button, int state, int x1, int x2)
{
	model->callback_mouse(button, state, x1, x2);
	glutPostRedisplay();
}
static void callback_motion(int x1, int x2)
{
	model->callback_motion(x1, x2);
	glutPostRedisplay();
}
static void callback_display(void)
{
	//draw
	model->draw();
	//swap
	glutSwapBuffers();
}
static void callback_reshape(int width, int height)
{
	//canvas
	model->callback_reshape(width, height);
	//update
	glutPostRedisplay();
}
static void callback_keyboard(unsigned char key, int x1, int x2)
{
	if(key == 27)
	{
		glutDestroyWindow(glutGetWindow());
	}
	else
	{
		model->callback_keyboard(key, x1, x2);
	}
}

int main(int argc, char** argv)
{
	//glut
	glutInit(&argc, argv);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(0, 0);
	glutInitContextVersion(4, 6);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	//window
	glutCreateWindow("Canvas");
	//glew
	if(glewInit() != GLEW_OK)
	{
		printf("Error: can't setup glew!\n");
		exit(EXIT_FAILURE);
	}
	//setup
	setup();
	//callbacks
	glutIdleFunc(callback_idle);
	glutMouseFunc(callback_mouse);
	glutMotionFunc(callback_motion);
	glutDisplayFunc(callback_display);
	glutReshapeFunc(callback_reshape);
	glutKeyboardFunc(callback_keyboard);
	//loop
	glutMainLoop();
	//cleanup
	cleanup();
	//return
	return EXIT_SUCCESS;
}