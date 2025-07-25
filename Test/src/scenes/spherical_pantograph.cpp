//std
#include <cmath>

//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Objects/3D/Cylinder.hpp"

//test
#include "Canvas/Test/inc/Engine.hpp"
#include "Canvas/Test/inc/examples.hpp"

static void scene_setup(canvas::Scene* scene)
{
	//data
	canvas::objects::Cylinder* cylinders[6];
	const canvas::Color colors[] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
	const canvas::vec3 axial[] = {{0, float(M_PI_2), 0}, {-float(M_PI_2), 0, 0}, {0, 0, 0}};
	//arrows
	for(uint32_t i = 0; i < 3; i++)
	{
		//allocate
		cylinders[i + 0] = new canvas::objects::Cylinder;
		cylinders[i + 3] = new canvas::objects::Cylinder;
		//setup
		cylinders[i + 0]->stroke(false);
		cylinders[i + 3]->stroke(false);
		cylinders[i + 0]->height(1.80f);
		cylinders[i + 3]->height(0.20f);
		cylinders[i + 0]->radius(0, 0.01f);
		cylinders[i + 0]->radius(1, 0.01f);
		cylinders[i + 3]->radius(0, 0.04f);
		cylinders[i + 3]->radius(1, 0.00f);
		cylinders[i + 0]->shift({0, 0, 0.90f});
		cylinders[i + 3]->shift({0, 0, 1.90f});
		cylinders[i + 0]->color_fill(colors[i]);
		cylinders[i + 3]->color_fill(colors[i]);
		cylinders[i + 0]->rotate(axial[i], true);
		cylinders[i + 3]->rotate(axial[i], true);
	}
	//objects
	for(uint32_t i = 0; i < 6; i++) scene->add_object(cylinders[i]);
}

void examples::scenes::spherical_pantograph(int32_t argc, char** argv)
{
	//data
	Engine engine;
	//scene
	scene_setup(engine.scene());
	canvas::Scene* scene = engine.scene();
	//update
	scene->update(true);
	scene->camera().bound();
	scene->camera().apply();
	scene->camera().update();
	//start
	engine.start();
}