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
#include "inc/Models/Model.hpp"

#include "inc/Objects/Type.hpp"
#include "inc/Objects/Line.hpp"
#include "inc/Objects/Point.hpp"
#include "inc/Objects/Circle.hpp"
#include "inc/Objects/Triangle.hpp"

//static data
canvas::Model* model;

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
	((canvas::objects::Line*) model->object(0))->color(2, canvas::Color(1, 1, 1));
	((canvas::objects::Line*) model->object(1))->color(2, canvas::Color(1, 1, 1));
	((canvas::objects::Line*) model->object(2))->color(2, canvas::Color(1, 1, 1));
	((canvas::objects::Line*) model->object(0))->position(0, canvas::vec3(-1.0, -1.0, +0.0));
	((canvas::objects::Line*) model->object(0))->position(1, canvas::vec3(+1.0, -1.0, +0.0));
	((canvas::objects::Line*) model->object(1))->position(0, canvas::vec3(+1.0, -1.0, +0.0));
	((canvas::objects::Line*) model->object(1))->position(1, canvas::vec3(+0.0, +1.0, +0.0));
	((canvas::objects::Line*) model->object(2))->position(0, canvas::vec3(+0.0, +1.0, +0.0));
	((canvas::objects::Line*) model->object(2))->position(1, canvas::vec3(-1.0, -1.0, +0.0));
	//points
	((canvas::objects::Point*) model->object(3))->color(canvas::Color(1, 0, 1));
	((canvas::objects::Point*) model->object(4))->color(canvas::Color(1, 0, 1));
	((canvas::objects::Point*) model->object(5))->color(canvas::Color(1, 0, 1));
	((canvas::objects::Point*) model->object(6))->color(canvas::Color(1, 0, 1));
	((canvas::objects::Point*) model->object(7))->color(canvas::Color(1, 0, 1));
	((canvas::objects::Point*) model->object(8))->color(canvas::Color(1, 0, 1));
	((canvas::objects::Point*) model->object(3))->position(canvas::vec3(-1.0, -1.0, +0.0));
	((canvas::objects::Point*) model->object(4))->position(canvas::vec3(+0.0, -1.0, +0.0));
	((canvas::objects::Point*) model->object(5))->position(canvas::vec3(+1.0, -1.0, +0.0));
	((canvas::objects::Point*) model->object(6))->position(canvas::vec3(-0.5, +0.0, +0.0));
	((canvas::objects::Point*) model->object(7))->position(canvas::vec3(+0.5, +0.0, +0.0));
	((canvas::objects::Point*) model->object(8))->position(canvas::vec3(+0.0, +1.0, +0.0));
	//triangles
	((canvas::objects::Triangle*) model->object( 9))->fill(true);
	((canvas::objects::Triangle*) model->object(10))->fill(true);
	((canvas::objects::Triangle*) model->object(11))->fill(true);
	((canvas::objects::Triangle*) model->object( 9))->fill_color(3, canvas::Color(1, 0, 0));
	((canvas::objects::Triangle*) model->object(10))->fill_color(3, canvas::Color(0, 1, 0));
	((canvas::objects::Triangle*) model->object(11))->fill_color(3, canvas::Color(0, 0, 1));
	((canvas::objects::Triangle*) model->object( 9))->position(0, canvas::vec3(-1.0, -1.0, +0.0));
	((canvas::objects::Triangle*) model->object( 9))->position(1, canvas::vec3(+0.0, -1.0, +0.0));
	((canvas::objects::Triangle*) model->object( 9))->position(2, canvas::vec3(-0.5, +0.0, +0.0));
	((canvas::objects::Triangle*) model->object(10))->position(0, canvas::vec3(+0.0, -1.0, +0.0));
	((canvas::objects::Triangle*) model->object(10))->position(1, canvas::vec3(+1.0, -1.0, +0.0));
	((canvas::objects::Triangle*) model->object(10))->position(2, canvas::vec3(+0.5, +0.0, +0.0));
	((canvas::objects::Triangle*) model->object(11))->position(0, canvas::vec3(-0.5, +0.0, +0.0));
	((canvas::objects::Triangle*) model->object(11))->position(1, canvas::vec3(+0.5, +0.0, +0.0));
	((canvas::objects::Triangle*) model->object(11))->position(2, canvas::vec3(-0.0, +1.0, +0.0));
}
void example_2(void)
{
	//data
	const unsigned nc = 40;
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
			((canvas::objects::Circle*) model->object(nc * i + j))->draw_color(canvas::Color(1, 1, 1));
			((canvas::objects::Circle*) model->object(nc * i + j))->fill_color(canvas::Color(0, 0, 1));
			((canvas::objects::Circle*) model->object(nc * i + j))->center(canvas::vec3(2 * rc * j + rc - 1, 2 * rc * i + rc - 1, 0));
		}
	}
}

//setup
void setup(void)
{
	//create
	model = new canvas::Model;
	//example
	example_2();
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
	return;
}
static void callback_mouse(int button, int state, int x1, int x2)
{
	return;
}
static void callback_motion(int x1, int x2)
{
	return;
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
	//uniforms
	model->screen(width, height);
	//viewport
	glViewport(0, 0, width, height);
	//update
	glutPostRedisplay();
}
static void callback_keyboard(unsigned char key, int x1, int x2)
{
	if(key == 27)
	{
		glutDestroyWindow(glutGetWindow());
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