//std
#include <cmath>

//canvas
#include "Canvas/Canvas/inc/Objects/Group.hpp"
#include "Canvas/Canvas/inc/Objects/1D/Line.hpp"
#include "Canvas/Canvas/inc/Objects/1D/Arrow.hpp"
#include "Canvas/Canvas/inc/Objects/3D/Cylinder.hpp"

//test
#include "Canvas/Test/inc/examples.hpp"

static const float a = 1.00;
static const float b = 0.50;
static const uint32_t nc = 40;
static canvas::objects::Line* axes[3];
static canvas::objects::Arrow* arrow[3];

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
		canvas::objects::Cylinder* chunk = new canvas::objects::Cylinder;
		const float t1 = float(i + 0) / nc;
		const float t2 = float(i + 1) / nc;
		const float x1 = 3 * t1 * (1 - t1) * (1 - t1) * a + t1 * t1 * (3 - 2 * t1);
		const float x2 = 3 * t2 * (1 - t2) * (1 - t2) * a + t2 * t2 * (3 - 2 * t2);
		const float y1 = 3 * t1 * (1 - t1) * (1 - t1) * a + 3 * t1 * t1 * (1 - t1) * b;
		const float y2 = 3 * t2 * (1 - t2) * (1 - t2) * a + 3 * t2 * t2 * (1 - t2) * b;
		chunk->stroke(false);
		chunk->radius(0, y1);
		chunk->radius(1, y2);
		chunk->height(x2 - x1);
		chunk->color_fill({0, 0, 1});
		chunk->apply_matrix(canvas::mat4());
		chunk->shift({0, 0, (x2 + x1) / 2});
		group->objects().push_back(chunk);
	}
	//lines
	axes[0]->point(0, {0, 0, 0});
	axes[1]->point(0, {0, 0, 0});
	axes[2]->point(0, {0, 0, 0});
	axes[0]->point(1, {1, 0, 0});
	axes[1]->point(1, {0, 1, 0});
	axes[2]->point(1, {0, 0, 1});
	axes[0]->color_stroke({1.0f, 1.0f, 1.0f});
	axes[1]->color_stroke({1.0f, 1.0f, 1.0f});
	axes[2]->color_stroke({1.0f, 1.0f, 1.0f});
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
	group->rotate({float(M_PI) / 4, 0, 0});
	//scene
	scene->add_object(group);
	scene->add_object(axes[0]);
	scene->add_object(axes[1]);
	scene->add_object(axes[2]);
	scene->add_object(arrow[0]);
	scene->add_object(arrow[1]);
	scene->add_object(arrow[2]);
}