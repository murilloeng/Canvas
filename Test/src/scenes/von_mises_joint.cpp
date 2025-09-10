//std
#include <cmath>
#include <chrono>

//test
#include "Canvas/Test/inc/Engine.hpp"
#include "Canvas/Test/inc/examples.hpp"
#include "Canvas/Test/inc/scenes/Beam.hpp"

//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"

#include "Canvas/Canvas/inc/Lights/Ambient.hpp"
#include "Canvas/Canvas/inc/Lights/Direction.hpp"

#include "Canvas/Canvas/inc/Objects/1D/Line.hpp"

//static data
static canvas::Scene* scene;
static const float B = 1.00f;
static const float H = 1.00f;
static const float R = 0.10f;
static const float h = 0.10f;
static const float w = 0.02f;
static Beam link, bar_1, bar_2;
static std::chrono::high_resolution_clock::time_point t0;

//scene
static void scene_setup(void)
{
	//positions
	bar_1.height(h);
	bar_2.height(h);
	link.thickness(w);
	link.height(h / 2);
	bar_1.thickness(w);
	bar_2.thickness(w);
	link.node(0, canvas::vec3(-R, H, 0));
	link.node(1, canvas::vec3(+R, H, 0));
	bar_1.node(1, canvas::vec3(-R, H, +w));
	bar_2.node(1, canvas::vec3(+R, H, -w));
	bar_1.node(0, canvas::vec3(-B - R, 0, +w));
	bar_2.node(0, canvas::vec3(+B + R, 0, -w));
	//colors
	scene->background("white");
	link.color_fill(canvas::Color(1, 0, 0));
	bar_1.color_fill(canvas::Color(0, 0, 1));
	bar_2.color_fill(canvas::Color(0, 0, 1));
	//scene
	scene->add_object(&link);
	scene->add_object(&bar_1);
	scene->add_object(&bar_2);
	//light
	scene->light().add_direction();
	scene->light().ambient()->color({0.1f, 0.1f, 0.1f});
	scene->light().direction(0)->color({0.9f, 0.9f, 0.9f});
	scene->light().direction(0)->direction({0.0f, 0.0f, 1.0f});
	scene->light().update_shaders();
}
static void scene_update(void)
{
	//data
	using namespace std::chrono;
	const float L = sqrtf(B * B + H * H);
	const high_resolution_clock::time_point tn = high_resolution_clock::now();
	const float q = duration_cast<microseconds>(tn - t0).count() / 2e5f;
	//state
	const float p2 = R * sinf(q);
	const float p1 = B + R - R * cosf(q);
	const float u1 = p2 * sqrtf(L * L - p1 * p1 - p2 * p2) / sqrtf(p1 * p1 + p2 * p2);
	const float u2 = p1 * sqrtf(L * L - p1 * p1 - p2 * p2) / sqrtf(p1 * p1 + p2 * p2) - H;
	//objects
	link.node(0, canvas::vec3(u1 - R * cosf(q), H + u2 - R * sinf(q), 0));
	link.node(1, canvas::vec3(u1 + R * cosf(q), H + u2 + R * sinf(q), 0));
	bar_1.node(1, canvas::vec3(u1 - R * cosf(q), H + u2 - R * sinf(q), +w));
	bar_2.node(1, canvas::vec3(u1 + R * cosf(q), H + u2 + R * sinf(q), -w));
	//scene
	scene->update(false);
}

void examples::scenes::von_mises_joint(void)
{
	//data
	Engine engine;
	//callbacks
	engine.user_idle(scene_update);
	//scene
	scene = engine.scene();
	scene_setup();
	//update
	scene->update(true);
	scene->camera().bound();
	scene->camera().update();
	t0 = std::chrono::high_resolution_clock::now();
	//start
	engine.start();
	scene->clear_objects(false);
}