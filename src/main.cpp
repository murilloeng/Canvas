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
#include "inc/Objects/Object.hpp"

//examples
#include "inc/Examples/examples.hpp"

//static data
static canvas::Scene* scene;

//setup
void setup(void)
{
	//create
	scene = new canvas::Scene;
	//example
	examples::objects::splines(scene);
	// examples::scenes::beam_1(scene);
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
		object->rotate({0, 4e-2, 0}, false);
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