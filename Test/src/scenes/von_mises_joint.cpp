//std
#include <chrono>

//canvas
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Objects/1D/Line.hpp"

//test
#include "Canvas/Test/inc/examples.hpp"
#include "Canvas/Test/inc/managers/GLFW.hpp"

//static data
static canvas::Scene* scene;
static const float B = 1.00f;
static const float H = 1.00f;
static const float R = 0.10f;
static std::chrono::steady_clock::time_point t0;

//scene
static void scene_setup(void)
{
	//data
	const float B = 1.00f;
	const float H = 1.00f;
	const float R = 0.10f;
	//objects
	canvas::objects::Line* link = new canvas::objects::Line;
	canvas::objects::Line* bar_1 = new canvas::objects::Line;
	canvas::objects::Line* bar_2 = new canvas::objects::Line;
	//positions
	link->point(0, canvas::vec3(-R, H, 0));
	link->point(1, canvas::vec3(+R, H, 0));
	bar_1->point(1, canvas::vec3(-R, H, 0));
	bar_2->point(1, canvas::vec3(+R, H, 0));
	bar_1->point(0, canvas::vec3(-B - R, 0, 0));
	bar_2->point(0, canvas::vec3(+B + R, 0, 0));
	//colors
	link->color_stroke(canvas::Color(0, 1, 0));
	bar_1->color_stroke(canvas::Color(0, 0, 1));
	bar_2->color_stroke(canvas::Color(0, 0, 1));
	//scene
	scene->add_object(link);
	scene->add_object(bar_1);
	scene->add_object(bar_2);
}
static void scene_update(void)
{
	//data
	using namespace std::chrono;
	const float L = sqrtf(B * B + H * H);
	const steady_clock::time_point tn = steady_clock::now();
	canvas::objects::Line* link = (canvas::objects::Line*) scene->object(0);
	canvas::objects::Line* bar_1 = (canvas::objects::Line*) scene->object(1);
	canvas::objects::Line* bar_2 = (canvas::objects::Line*) scene->object(2);
	//state
	const float q = duration_cast<microseconds>(tn - t0).count() / 2e5f;
	const float p2 = R * sinf(q);
	const float p1 = B + R - R * cosf(q);
	const float u1 = p2 * sqrtf(L * L - p1 * p1 - p2 * p2) / sqrtf(p1 * p1 + p2 * p2);
	const float u2 = p1 * sqrtf(L * L - p1 * p1 - p2 * p2) / sqrtf(p1 * p1 + p2 * p2) - H;
	//objects
	link->point(0, canvas::vec3(u1 - R * cosf(q), H + u2 - R * sinf(q), 0));
	link->point(1, canvas::vec3(u1 + R * cosf(q), H + u2 + R * sinf(q), 0));
	bar_1->point(1, canvas::vec3(u1 - R * cosf(q), H + u2 - R * sinf(q), 0));
	bar_2->point(1, canvas::vec3(u1 + R * cosf(q), H + u2 + R * sinf(q), 0));
	//scene
	scene->update(false);
}

void examples::scenes::von_mises_joint(int argc, char** argv)
{
	//data
	GLFW app(argc, argv, "shd/");
	app.callback_idle(scene_update);
	//scene
	scene = app.scene();
	scene_setup();
	//update
	scene->update(true);
	scene->camera().bound();
	scene->camera().apply();
	scene->camera().update();
	t0 = std::chrono::high_resolution_clock::now();
	//start
	app.start();
}