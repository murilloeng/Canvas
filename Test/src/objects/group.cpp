//canvas
#include "Canvas/inc/Objects/Group.hpp"
#include "Canvas/inc/Light/Ambient.hpp"
#include "Canvas/inc/Light/Direction.hpp"
#include "Canvas/inc/Objects/1D/Line.hpp"
#include "Canvas/inc/Objects/1D/Arrow.hpp"
#include "Canvas/inc/Objects/3D/Cylinder.hpp"

//test
#include "Canvas/Test/inc/examples.hpp"

static const float a = 1.00;
static const float b = 0.50;
static const uint32_t nc = 40;
static canvas::objects::Line* axes[3];
static canvas::objects::Arrow* arrow[3];
static canvas::objects::Cylinder chunk[nc];

void examples::objects::group(canvas::Scene* scene)
{
	//data
	axes[0] = new canvas::objects::Line;
	axes[1] = new canvas::objects::Line;
	axes[2] = new canvas::objects::Line;
	arrow[0] = new canvas::objects::Arrow;
	arrow[1] = new canvas::objects::Arrow;
	arrow[2] = new canvas::objects::Arrow;
	canvas::objects::Group* group = new canvas::objects::Group;
	//chunks
	for(uint32_t i = 0; i < nc; i++)
	{
		const float t1 = float(i + 0) / nc;
		const float t2 = float(i + 1) / nc;
		const float x1 = 3 * t1 * (1 - t1) * (1 - t1) * a + t1 * t1 * (3 - 2 * t1);
		const float x2 = 3 * t2 * (1 - t2) * (1 - t2) * a + t2 * t2 * (3 - 2 * t2);
		const float y1 = 3 * t1 * (1 - t1) * (1 - t1) * a + 3 * t1 * t1 * (1 - t1) * b;
		const float y2 = 3 * t2 * (1 - t2) * (1 - t2) * a + 3 * t2 * t2 * (1 - t2) * b;
		chunk[i].stroke(false);
		chunk[i].radius(0, y1);
		chunk[i].radius(1, y2);
		chunk[i].height(x2 - x1);
		chunk[i].color_fill({0, 0, 1});
		chunk[i].apply_matrix(canvas::mat4());
		chunk[i].shift({0, 0, (x2 + x1) / 2});
	}
	//lines
	axes[0]->point(0, {0, 0, 0});
	axes[1]->point(0, {0, 0, 0});
	axes[2]->point(0, {0, 0, 0});
	axes[0]->point(1, {1, 0, 0});
	axes[1]->point(1, {0, 1, 0});
	axes[2]->point(1, {0, 0, 1});
	axes[0]->color_stroke({0, 0, 0.0f});
	axes[1]->color_stroke({0, 0, 0.0f});
	axes[2]->color_stroke({0, 0, 0.0f});
	//arrows
	arrow[0]->width(0.05f);
	arrow[1]->width(0.05f);
	arrow[2]->width(0.05f);
	arrow[0]->height(0.05f);
	arrow[1]->height(0.05f);
	arrow[2]->height(0.05f);
	arrow[0]->path(axes[0]);
	arrow[1]->path(axes[1]);
	arrow[2]->path(axes[2]);
	arrow[0]->parameter(1.0f);
	arrow[1]->parameter(1.0f);
	arrow[2]->parameter(1.0f);
	arrow[0]->color_stroke({0, 0, 0});
	arrow[1]->color_stroke({0, 0, 0});
	arrow[2]->color_stroke({0, 0, 0});
	//group
	for(uint32_t i = 0; i < nc; i++)
	{
		group->objects().push_back(chunk + i);
	}
	group->rotate({float(M_PI) / 4, 0, 0});
	//light
	glLineWidth(2.0);
	scene->background({1, 1, 1});
	scene->light().add_direction();
	scene->light().ambient()->color({0.3f, 0.3f, 0.3f});
	scene->light().direction(0)->color({0.7f, 0.7f, 0.7f});
	scene->light().direction(0)->direction({0.0f, 1.0f, 0.0f});
	scene->light().update_shaders();
	//scene
	scene->add_object(group);
	scene->add_object(axes[0]);
	scene->add_object(axes[1]);
	scene->add_object(axes[2]);
	scene->add_object(arrow[0]);
	scene->add_object(arrow[1]);
	scene->add_object(arrow[2]);
}