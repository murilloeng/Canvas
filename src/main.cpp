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
#include "inc/Scene/Scene.hpp"

#include "inc/Objects/Arc.hpp"
#include "inc/Objects/Cube.hpp"
#include "inc/Objects/Type.hpp"
#include "inc/Objects/Line.hpp"
#include "inc/Objects/Quad.hpp"
#include "inc/Objects/Path.hpp"
#include "inc/Objects/Point.hpp"
#include "inc/Objects/Circle.hpp"
#include "inc/Objects/Sphere.hpp"
#include "inc/Objects/Grid_2D.hpp"
#include "inc/Objects/Grid_3D.hpp"
#include "inc/Objects/Triangle.hpp"
#include "inc/Objects/Cylinder.hpp"

//static data
static canvas::Scene* scene;
static std::chrono::steady_clock::time_point t1, t2;

//examples
void example_1(void)
{
	//objects
	scene->add_object(canvas::objects::type::line);
	scene->add_object(canvas::objects::type::line);
	scene->add_object(canvas::objects::type::line);
	scene->add_object(canvas::objects::type::point);
	scene->add_object(canvas::objects::type::point);
	scene->add_object(canvas::objects::type::point);
	scene->add_object(canvas::objects::type::point);
	scene->add_object(canvas::objects::type::point);
	scene->add_object(canvas::objects::type::point);
	scene->add_object(canvas::objects::type::triangle);
	scene->add_object(canvas::objects::type::triangle);
	scene->add_object(canvas::objects::type::triangle);
	//lines
	((canvas::objects::Line*) scene->object(0))->stroke_color({1, 1, 1});
	((canvas::objects::Line*) scene->object(1))->stroke_color({1, 1, 1});
	((canvas::objects::Line*) scene->object(2))->stroke_color({1, 1, 1});
	((canvas::objects::Line*) scene->object(0))->position(0, {-1.0, -1.0, +0.0});
	((canvas::objects::Line*) scene->object(0))->position(1, {+1.0, -1.0, +0.0});
	((canvas::objects::Line*) scene->object(1))->position(0, {+1.0, -1.0, +0.0});
	((canvas::objects::Line*) scene->object(1))->position(1, {+0.0, +1.0, +0.0});
	((canvas::objects::Line*) scene->object(2))->position(0, {+0.0, +1.0, +0.0});
	((canvas::objects::Line*) scene->object(2))->position(1, {-1.0, -1.0, +0.0});
	//points
	((canvas::objects::Point*) scene->object(3))->dot_color({1, 0, 1});
	((canvas::objects::Point*) scene->object(4))->dot_color({1, 0, 1});
	((canvas::objects::Point*) scene->object(5))->dot_color({1, 0, 1});
	((canvas::objects::Point*) scene->object(6))->dot_color({1, 0, 1});
	((canvas::objects::Point*) scene->object(7))->dot_color({1, 0, 1});
	((canvas::objects::Point*) scene->object(8))->dot_color({1, 0, 1});
	((canvas::objects::Point*) scene->object(3))->position({-1.0, -1.0, +0.0});
	((canvas::objects::Point*) scene->object(4))->position({+0.0, -1.0, +0.0});
	((canvas::objects::Point*) scene->object(5))->position({+1.0, -1.0, +0.0});
	((canvas::objects::Point*) scene->object(6))->position({-0.5, +0.0, +0.0});
	((canvas::objects::Point*) scene->object(7))->position({+0.5, +0.0, +0.0});
	((canvas::objects::Point*) scene->object(8))->position({+0.0, +1.0, +0.0});
	//triangles
	((canvas::objects::Triangle*) scene->object( 9))->fill_color({1, 0, 0});
	((canvas::objects::Triangle*) scene->object(10))->fill_color({0, 1, 0});
	((canvas::objects::Triangle*) scene->object(11))->fill_color({0, 0, 1});
	((canvas::objects::Triangle*) scene->object( 9))->position(0, {-1.0, -1.0, +0.0});
	((canvas::objects::Triangle*) scene->object( 9))->position(1, {+0.0, -1.0, +0.0});
	((canvas::objects::Triangle*) scene->object( 9))->position(2, {-0.5, +0.0, +0.0});
	((canvas::objects::Triangle*) scene->object(10))->position(0, {+0.0, -1.0, +0.0});
	((canvas::objects::Triangle*) scene->object(10))->position(1, {+1.0, -1.0, +0.0});
	((canvas::objects::Triangle*) scene->object(10))->position(2, {+0.5, +0.0, +0.0});
	((canvas::objects::Triangle*) scene->object(11))->position(0, {-0.5, +0.0, +0.0});
	((canvas::objects::Triangle*) scene->object(11))->position(1, {+0.5, +0.0, +0.0});
	((canvas::objects::Triangle*) scene->object(11))->position(2, {-0.0, +1.0, +0.0});
}
void example_2(void)
{
	//data
	const unsigned n = 10;
	const float r = 1.0f / n;
	//objects
	for(unsigned i = 0; i < n; i++)
	{
		for(unsigned j = 0; j < n; j++)
		{
			scene->add_object(canvas::objects::type::circle);
			((canvas::objects::Circle*) scene->object(n * i + j))->radius(0.9 * r);
			((canvas::objects::Circle*) scene->object(n * i + j))->fill_color({0, 0, 1});
			((canvas::objects::Circle*) scene->object(n * i + j))->stroke_color({1, 1, 1});
			((canvas::objects::Circle*) scene->object(n * i + j))->shift({2 * r * j + r - 1, 2 * r * i + r - 1, 0});
		}
	}
}
void example_3(void)
{
	//data
	const unsigned n = 10;
	const float r = 1.0f / n;
	//objects
	for(unsigned i = 0; i < n; i++)
	{
		for(unsigned j = 0; j < n; j++)
		{
			scene->add_object(canvas::objects::type::arc);
			((canvas::objects::Arc*) scene->object(n * i + j))->radius(r);
			((canvas::objects::Arc*) scene->object(n * i + j))->angle(0, 0);
			((canvas::objects::Arc*) scene->object(n * i + j))->fill_color({0, 0, 1});
			((canvas::objects::Arc*) scene->object(n * i + j))->stroke_color({1, 1, 1});
			((canvas::objects::Arc*) scene->object(n * i + j))->angle(1, 2 * M_PI * float(n * i + j) / n / n);
			((canvas::objects::Arc*) scene->object(n * i + j))->shift({2 * r * j + r - 1, 2 * r * i + r - 1, 0});
		}
	}
}
void example_4(void)
{
	//data
	const unsigned n = 40;
	const float s = 2.0f / n;
	//objects
	for(unsigned i = 0; i < n; i++)
	{
		for(unsigned j = 0; j < n; j++)
		{
			scene->add_object(canvas::objects::type::quad);
			((canvas::objects::Quad*) scene->object(n * i + j))->fill_color({0, 0, 1});
			((canvas::objects::Quad*) scene->object(n * i + j))->stroke_color({1, 1, 1});
			((canvas::objects::Quad*) scene->object(n * i + j))->position(0, {(j + 0) * s - 1, (i + 0) * s - 1, 0});
			((canvas::objects::Quad*) scene->object(n * i + j))->position(1, {(j + 1) * s - 1, (i + 0) * s - 1, 0});
			((canvas::objects::Quad*) scene->object(n * i + j))->position(2, {(j + 1) * s - 1, (i + 1) * s - 1, 0});
			((canvas::objects::Quad*) scene->object(n * i + j))->position(3, {(j + 0) * s - 1, (i + 1) * s - 1, 0});
		}
	}
}
void example_5(void)
{
	//data
	const unsigned n = 10;
	const float s = 1.0f / n;
	//objects
	for(unsigned i = 0; i < n; i++)
	{
		for(unsigned j = 0; j < n; j++)
		{
			const float x1 = 2 * j * s - 1 + s;
			const float x2 = 2 * i * s - 1 + s;
			scene->add_object(canvas::objects::type::cube);
			((canvas::objects::Cube*) scene->object(n * i + j))->scale(s / 2);
			((canvas::objects::Cube*) scene->object(n * i + j))->shift({x1, x2, 0});
			((canvas::objects::Cube*) scene->object(n * i + j))->stroke_color({1, 1, 1});
			((canvas::objects::Cube*) scene->object(n * i + j))->fill_color({0, 0, 1, 0.5});
		}
	}
}
void example_6(void)
{
	//data
	const unsigned n = 10;
	const float s = 1.0f / n;
	//objects
	for(unsigned i = 0; i < n; i++)
	{
		for(unsigned j = 0; j < n; j++)
		{
			const float x1 = 2 * j * s - 1 + s;
			const float x2 = 2 * i * s - 1 + s;
			scene->add_object(canvas::objects::type::cylinder);
			((canvas::objects::Cylinder*) scene->object(n * i + j))->scale(s / 2);
			((canvas::objects::Cylinder*) scene->object(n * i + j))->shift({x1, x2, 0});
			((canvas::objects::Cylinder*) scene->object(n * i + j))->fill_color({0, 0, 1});
			((canvas::objects::Cylinder*) scene->object(n * i + j))->stroke_color({1, 1, 1});
		}
	}
}
void example_7(void)
{
	//data
	const unsigned n = 10;
	const float s = 1.0f / n;
	//objects
	for(unsigned i = 0; i < n; i++)
	{
		for(unsigned j = 0; j < n; j++)
		{
			const float x1 = 2 * j * s - 1 + s;
			const float x2 = 2 * i * s - 1 + s;
			scene->add_object(canvas::objects::type::sphere);
			((canvas::objects::Sphere*) scene->object(n * i + j))->scale(s);
			((canvas::objects::Sphere*) scene->object(n * i + j))->shift({x1, x2, 0});
			((canvas::objects::Sphere*) scene->object(n * i + j))->fill_color({0, 0, 1});
			((canvas::objects::Sphere*) scene->object(n * i + j))->stroke_color({1, 1, 1});
		}
	}
}
void example_8(void)
{
	//data
	const unsigned n = 10;
	const float s = 1.0f / n;
	//objects
	for(unsigned i = 0; i < n; i++)
	{
		for(unsigned j = 0; j < n; j++)
		{
			const float x1 = 2 * j * s - 1 + s;
			const float x2 = 2 * i * s - 1 + s;
			scene->add_object(canvas::objects::type::grid_2D);
			((canvas::objects::Grid_2D*) scene->object(n * i + j))->scale(0.5 * s);
			((canvas::objects::Grid_2D*) scene->object(n * i + j))->shift({x1, x2, 0});
			((canvas::objects::Grid_2D*) scene->object(n * i + j))->fill_color({0, 0, 1});
			((canvas::objects::Grid_2D*) scene->object(n * i + j))->stroke_color({1, 1, 1});
		}
	}
}
void example_9(void)
{
	//data
	const unsigned n = 10;
	const float s = 1.0f / n;
	//objects
	for(unsigned i = 0; i < n; i++)
	{
		for(unsigned j = 0; j < n; j++)
		{
			const float x1 = 2 * j * s - 1 + s;
			const float x2 = 2 * i * s - 1 + s;
			scene->add_object(canvas::objects::type::grid_3D);
			((canvas::objects::Grid_3D*) scene->object(n * i + j))->scale(0.5 * s);
			((canvas::objects::Grid_3D*) scene->object(n * i + j))->shift({x1, x2, 0});
			((canvas::objects::Grid_3D*) scene->object(n * i + j))->fill_color({0, 0, 1});
			((canvas::objects::Grid_3D*) scene->object(n * i + j))->stroke_color({1, 1, 1});
		}
	}
}
void example_10(void)
{
	//data
	const float w = 1.00e-01;
	const float h = 1.00e-01;
	const float t = 1.00e-02;
	//objects
	scene->add_object(canvas::objects::type::path);
	scene->object(0)->scale(9);
	((canvas::objects::Path*) scene->object(0))->add_point({-w / 2, -h / 2 - t, 0});
	((canvas::objects::Path*) scene->object(0))->add_point({+w / 2, -h / 2 - t, 0});
	((canvas::objects::Path*) scene->object(0))->add_point({+w / 2, -h / 2, 0});
	((canvas::objects::Path*) scene->object(0))->add_point({+t / 2, -h / 2, 0});
	((canvas::objects::Path*) scene->object(0))->add_point({+t / 2, +h / 2, 0});
	((canvas::objects::Path*) scene->object(0))->add_point({+w / 2, +h / 2, 0});
	((canvas::objects::Path*) scene->object(0))->add_point({+w / 2, +h / 2 + t, 0});
	((canvas::objects::Path*) scene->object(0))->add_point({-w / 2, +h / 2 + t, 0});
	((canvas::objects::Path*) scene->object(0))->add_point({-w / 2, +h / 2, 0});
	((canvas::objects::Path*) scene->object(0))->add_point({-t / 2, +h / 2, 0});
	((canvas::objects::Path*) scene->object(0))->add_point({-t / 2, -h / 2, 0});
	((canvas::objects::Path*) scene->object(0))->add_point({-w / 2, -h / 2, 0});
	((canvas::objects::Path*) scene->object(0))->add_point({-w / 2, -h / 2 - t, 0});
}

//setup
void setup(void)
{
	//create
	scene = new canvas::Scene;
	t1 = std::chrono::high_resolution_clock::now();
	//example
	example_7();
	//update
	scene->update();
}
void cleanup(void)
{
	//delete
	delete scene;
}

//callbacks
static void callback_idle(void)
{
	for(canvas::objects::Object* object : scene->objects())
	{
		object->apply_affine(canvas::mat4::rotation({0, 4e-2, 0}), false);
	}
	scene->update();
	glutPostRedisplay();
}
static void callback_mouse(int button, int state, int x1, int x2)
{
	scene->callback_mouse(button, state, x1, x2);
	glutPostRedisplay();
}
static void callback_motion(int x1, int x2)
{
	scene->callback_motion(x1, x2);
	glutPostRedisplay();
}
static void callback_display(void)
{
	//draw
	scene->draw();
	//swap
	glutSwapBuffers();
}
static void callback_reshape(int width, int height)
{
	//canvas
	scene->callback_reshape(width, height);
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
		scene->callback_keyboard(key, x1, x2);
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