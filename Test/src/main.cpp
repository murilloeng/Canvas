//std
#include <cmath>
#include <cstdlib>

//canvas
#include "Canvas/inc/Windows/Glut.hpp"
#include "Canvas/Test/inc/examples.hpp"
#include "Canvas/inc/Objects/Object.hpp"

//data
static float t = 0;
static canvas::Scene* scene;
static unsigned index_light = 0;

//callbacks
static void callback_idle(void)
{
	//data
	return;
	const unsigned fr = 60;
	//objects
	for(canvas::objects::Object* object : scene->objects())
	{
		object->rotate({0, float(M_PI) / fr, 0}, false);
	}
	scene->update(true);
	//light
	if(index_light == 1)
	{
		t += 2 * float(M_PI) / fr;
		scene->light().position({0, 0, sinf(t) + 1});
		scene->light().update_shaders();
	}
	if(index_light == 2)
	{
		const canvas::vec3 xl = scene->light().position();
		scene->light().position(canvas::vec3(0, float(M_PI) / fr, 0).quaternion().rotate(xl));
		scene->light().update_shaders();
	}
}

int main(int argc, char** argv)
{
	//data
	canvas::windows::Glut app(argc, argv, "shd/");
	//scene
	scene = app.scene();
	examples::objects::spheres(scene);
	scene->update(true);
	scene->camera().bound();
	scene->camera().apply();
	scene->camera().update();
	//callbacks
	app.callback_idle(callback_idle);
	//start
	app.start();
	//return
	return EXIT_SUCCESS;
}
