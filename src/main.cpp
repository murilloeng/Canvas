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
#include "inc/Canvas/Canvas.hpp"
#include "inc/Objects/Triangle.hpp"

//static data
canvas::Canvas* canvas_obj;

//setup
void setup(void)
{
	//create
	canvas_obj = new canvas::Canvas;
	//objects
	const float color[] = {
		0, 0, 1
	};
	const float positions[] = {
		-1, -1, 0,
		+1, -1, 0,
		+0, +1, 0
	};
	canvas_obj->m_objects.push_back(new canvas::objects::Triangle(canvas_obj));
	memcpy(((canvas::objects::Triangle*) canvas_obj->m_objects[0])->m_colors[0], color, 3 * sizeof(float));
	memcpy(((canvas::objects::Triangle*) canvas_obj->m_objects[0])->m_colors[1], color, 3 * sizeof(float));
	memcpy(((canvas::objects::Triangle*) canvas_obj->m_objects[0])->m_colors[2], color, 3 * sizeof(float));
	memcpy(((canvas::objects::Triangle*) canvas_obj->m_objects[0])->m_positions[0], positions + 0, 3 * sizeof(float));
	memcpy(((canvas::objects::Triangle*) canvas_obj->m_objects[0])->m_positions[1], positions + 3, 3 * sizeof(float));
	memcpy(((canvas::objects::Triangle*) canvas_obj->m_objects[0])->m_positions[2], positions + 6, 3 * sizeof(float));
	//update
	canvas_obj->update();
}
void cleanup(void)
{
	//delete
	delete canvas_obj;
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
	canvas_obj->draw();
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