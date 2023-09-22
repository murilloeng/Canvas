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
#include "inc/Objects/Triangle.hpp"

//static data
canvas::Model* model;

//setup
void setup(void)
{
	//create
	model = new canvas::Model;
	//objects
	model->add_object(canvas::objects::type::triangle);
	model->add_object(canvas::objects::type::triangle);
	model->add_object(canvas::objects::type::triangle);
	((canvas::objects::Triangle*) model->m_objects[0])->contour(true);
	((canvas::objects::Triangle*) model->m_objects[1])->contour(true);
	((canvas::objects::Triangle*) model->m_objects[2])->contour(true);
	((canvas::objects::Triangle*) model->m_objects[0])->color(3, 1, 0, 0);
	((canvas::objects::Triangle*) model->m_objects[1])->color(3, 0, 1, 0);
	((canvas::objects::Triangle*) model->m_objects[2])->color(3, 0, 0, 1);
	((canvas::objects::Triangle*) model->m_objects[0])->contour_color(1, 1, 1);
	((canvas::objects::Triangle*) model->m_objects[1])->contour_color(1, 1, 1);
	((canvas::objects::Triangle*) model->m_objects[2])->contour_color(1, 1, 1);
	((canvas::objects::Triangle*) model->m_objects[0])->position(0, -1.0, -1.0, 0.0);
	((canvas::objects::Triangle*) model->m_objects[0])->position(1, +0.0, -1.0, 0.0);
	((canvas::objects::Triangle*) model->m_objects[0])->position(2, -0.5, +0.0, 0.0);
	((canvas::objects::Triangle*) model->m_objects[1])->position(0, +0.0, -1.0, 0.0);
	((canvas::objects::Triangle*) model->m_objects[1])->position(1, +1.0, -1.0, 0.0);
	((canvas::objects::Triangle*) model->m_objects[1])->position(2, +0.5, +0.0, 0.0);
	((canvas::objects::Triangle*) model->m_objects[2])->position(0, -0.5, +0.0, 0.0);
	((canvas::objects::Triangle*) model->m_objects[2])->position(1, +0.5, +0.0, 0.0);
	((canvas::objects::Triangle*) model->m_objects[2])->position(2, -0.0, +1.0, 0.0);
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