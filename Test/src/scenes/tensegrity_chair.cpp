//std
#include <cmath>

//canvas
#include "Canvas/Canvas/inc/Objects/1D/Line.hpp"
#include "Canvas/Canvas/inc/Objects/3D/Cube.hpp"
#include "Canvas/Canvas/inc/Objects/1D/Arrow.hpp"
#include "Canvas/Canvas/inc/Objects/3D/Cylinder.hpp"
#include "Canvas/Canvas/inc/Objects/Image/Latex.hpp"

//examples
#include "Canvas/Test/inc/Engine.hpp"
#include "Canvas/Test/inc/examples.hpp"

//data
static const uint32_t nc = 3;
static const float e = 5.50e-02f;
static const float tr = 4.00e-03f;
static const float tc = 1.00e-02f;
static const float Rr = 1.00e-01f;
static const float Ht = 3.00e-01f;
static const float Hc = 1.50e-01f;
static const float Hr = (Ht + Hc) / 2;

static void rigid(canvas::Scene* scene)
{
	//data
	canvas::objects::Cube* links[4];
	canvas::objects::Cylinder* bases[2];
	const canvas::vec3 s2(e - tc / 2, tc, tc);
	const canvas::vec3 s1(tc, tc, Hr + tc / 2);
	const canvas::vec3 x1(e, 0, Hr / 2 + tc / 4 + tr);
	const canvas::vec3 x2(e / 2 - tc / 4, 0, Hr + tr);
	for(uint32_t i = 0; i < 4; i++) links[i] = new canvas::objects::Cube;
	for(uint32_t i = 0; i < 2; i++) bases[i] = new canvas::objects::Cylinder;
	//bases
	for(uint32_t i = 0; i < 2; i++)
	{
		bases[i]->height(tr);
		bases[i]->radius(0, Rr);
		bases[i]->radius(1, Rr);
		bases[i]->color_fill({0, 0, 1});
		bases[i]->shift({0, 0, tr / 2});
		scene->add_object(bases[i]);
	}
	//links
	for(uint32_t i = 0; i < 2; i++)
	{
		links[i + 0]->color_fill({0, 0, 1});
		links[i + 2]->color_fill({0, 0, 1});
		links[i + 0]->sizes(i == 0 ? s1 : s2);
		links[i + 2]->sizes(i == 0 ? s1 : s2);
		links[i + 0]->shift(i == 0 ? x1 : x2);
		links[i + 2]->shift(i == 0 ? x1 : x2);
		scene->add_object(links[i + 0]);
		scene->add_object(links[i + 2]);
	}
	//upper
	canvas::objects::Object* upper[] = {bases[1], links[2], links[3]};
	for(canvas::objects::Object* object : upper)
	{
		object->rotate({ 0, 0, tr / 2 }, {0, 0, float(M_PI)});
		object->rotate({ 0, 0, tr / 2 }, {float(M_PI), 0, 0});
		object->shift({0, 0, Ht + tr});
	}
}
static void cables(canvas::Scene* scene)
{
	//data
	const float pi = float(M_PI);
	canvas::objects::Line* cables[nc + 1];
	for(uint32_t i = 0; i <= nc; i++) cables[i] = new canvas::objects::Line;
	//cables
	for(uint32_t i = 0; i <= nc; i++)
	{
		if(i == nc)
		{
			cables[i]->point(0, {0, 0, Hr - tc / 2 + tr});
			cables[i]->point(1, {0, 0, Ht - Hr + tc / 2 + tr});
		}
		else
		{
			cables[i]->point(0, {Rr * cosf(2 * pi * i / nc), Rr * sinf(2 * pi * i / nc), tr});
			cables[i]->point(1, {Rr * cosf(2 * pi * i / nc), Rr * sinf(2 * pi * i / nc), Ht + tr});
		}
		cables[i]->color_stroke({0, 1, 0});
		scene->add_object(cables[i]);
	}
}
static void labels(canvas::Scene* scene)
{
	//latex
	scene->add_latex("$ e_r $");
	scene->add_latex("$ H_c $");
	scene->add_latex("$ H_t $");
	scene->add_latex("$ H_r $");
	scene->add_latex("$ R_r $");
	//data
	canvas::objects::Latex* labels[5];
	const canvas::Anchor a[] = {"SC", "CE", "CW", "CW", "NC"};
	for(uint32_t i = 0; i < 5; i++) labels[i] = new canvas::objects::Latex;
	const canvas::vec3 x[] = {
		{e / 2, 0, tr + Hr + 3 * tc / 2},
		{-tc, 0, Ht / 2 + tr},
		{Rr + tc, 0, Ht / 2 + tr},
		{e + 3 * tc / 2, 0, Hr / 2},
		{Rr / 2, 0, -tc}
	};
	//labels
	for(uint32_t i = 0; i < 5; i++)
	{
		labels[i]->index(i);
		labels[i]->size(Rr / 8);
		labels[i]->anchor(a[i]);
		labels[i]->position(x[i]);
		labels[i]->color_fill({1, 0, 0});
		labels[i]->direction(1, {0, 0, 1});
		scene->add_object(labels[i]);
	}
}
static void guides(canvas::Scene* scene)
{
	//data
	canvas::objects::Line* guides[5];
	const canvas::vec3 x[] = {
		{-tc, 0, Hr - tc / 2 + tr}, {-tc, 0, Ht - Hr + tc / 2 + tr},
		{0, 0, tr + Hr + 3 * tc / 2}, {e, 0, tr + Hr + 3 * tc / 2},
		{Rr + tc, 0, tr}, {Rr + tc, 0, tr + Ht},
		{e + 3 * tc / 2, 0, tr}, {e + 3 * tc / 2, 0, tr + Hr},
		{0, 0, -tc}, {Rr, 0, -tc}
	};
	for(uint32_t i = 0; i < 5; i++) guides[i] = new canvas::objects::Line;
	//arrows
	for(uint32_t i = 0; i < 5; i++)
	{
		// guides[i]->add_arrow(1, true);
		// guides[i]->add_arrow(0, false);
		// guides[i]->arrow(0)->height(tc);
		// guides[i]->arrow(1)->height(tc);
		// guides[i]->arrow(0)->width(0.0f);
		// guides[i]->arrow(1)->width(0.0f);
		guides[i]->point(0, x[2 * i + 0]);
		guides[i]->point(1, x[2 * i + 1]);
		guides[i]->color_stroke({1, 0, 0});
		scene->add_object(guides[i]);
	}
}

static void scene_setup(canvas::Scene* scene)
{
	rigid(scene);
	cables(scene);
	labels(scene);
	guides(scene);
	// scene->camera().rotation({float(M_PI_2), 0, 0});
}

void examples::scenes::tensegrity_chair(void)
{
	//data
	Engine engine;
	//scene
	scene_setup(engine.scene());
	canvas::Scene* scene = engine.scene();
	//update
	scene->update(true);
	scene->camera().bound();
	scene->camera().update();
	//start
	engine.start();
}