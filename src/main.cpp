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
typedef void(*scene_fun)(canvas::Scene*);

scene_fun tests[] = {
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

//setup
void setup(void)
{
	//create
	scene = new canvas::Scene;
	//example
	examples::objects::polylines(scene);
	// examples::scenes::beam_1(scene);
	//update
	scene->update(true);
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
	scene->update(false);
	glutPostRedisplay();
}
static void callback_mouse(int button, int state, int x1, int x2)
{
	//data
	unsigned glut_buttons[] = {GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON, GLUT_MIDDLE_BUTTON};
	canvas::button canvas_buttons[] = {canvas::button::left, canvas::button::right, canvas::button::middle};
	//callback
	for(unsigned i = 0; i < 3; i++)
	{
		if(glut_buttons[i] == button)
		{
			scene->callback_mouse(canvas_buttons[i], !state, x1, x2);
		}
	}
	glutPostRedisplay();
}
static void callback_wheel(int, int direction, int x1, int x2)
{
	scene->callback_wheel(direction, x1, x2);
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
static void callback_special(int key, int x1, int x2)
{
	//data
	unsigned canvas_mod = 0;
	int glut_mod = glutGetModifiers();
	const unsigned glut_keys[] = {GLUT_KEY_LEFT, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_UP};
	const unsigned glut_modifiers[] = {GLUT_ACTIVE_ALT, GLUT_ACTIVE_CTRL, GLUT_ACTIVE_SHIFT};
	const canvas::key canvas_keys[] = {canvas::key::left, canvas::key::right, canvas::key::down, canvas::key::up};
	const canvas::modifier canvas_modifiers[] = {canvas::modifier::alt, canvas::modifier::ctrl, canvas::modifier::shift};
	//callback
	for(unsigned i = 0; i < 3; i++)
	{
		if(glut_mod & glut_modifiers[i])
		{
			canvas_mod |= 1 << unsigned(canvas_modifiers[i]);
		}
	}
	for(unsigned i = 0; i < 4; i++)
	{
		if(key == glut_keys[i])
		{
			scene->callback_special(canvas_keys[i], canvas_mod, x1, x2);
			glutPostRedisplay();
		}
	}
}
static void callback_keyboard(unsigned char key, int x1, int x2)
{
	//data
	static unsigned index = 0;
	const unsigned size = sizeof(tests) / sizeof(scene_fun);
	//callback
	if(key == 27)
	{
		glutDestroyWindow(glutGetWindow());
	}
	else if(key == 'n')
	{
		index = (index + 1) % size;
		scene->clear_objects();
		scene->background({0, 0, 0});
		tests[index](scene);
		scene->update(true);
		glutPostRedisplay();
	}
	else
	{
		scene->callback_keyboard(key, x1, x2);
		scene->update(false);
		glutPostRedisplay();
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
	glutSpecialFunc(callback_special);
	glutMouseWheelFunc(callback_wheel);
	glutKeyboardFunc(callback_keyboard);
	glutPassiveMotionFunc(callback_motion);
	//loop
	glutMainLoop();
	//cleanup
	cleanup();
	//return
	return EXIT_SUCCESS;
}