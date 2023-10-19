//canvas
#include "inc/Examples/examples.hpp"

#include "inc/Objects/1D/Line.hpp"
#include "inc/Objects/3D/Cube.hpp"
#include "inc/Objects/3D/Cylinder.hpp"
#include "inc/Objects/Image/Equation.hpp"

//data
static const unsigned nc = 5;
static const float e = 5.50e-02;
static const float tr = 4.00e-03;
static const float tc = 1.00e-02;
static const float Rr = 1.00e-01;
static const float Ht = 3.00e-01;
static const float Hc = 1.50e-01;
static const float Hr = (Ht + Hc) / 2;

static void rigid(canvas::Scene* scene)
{
	//data
	const canvas::vec3 s2(e - tc / 2, tc, tc);
	const canvas::vec3 s1(tc, tc, Hr + tc / 2);
	const canvas::vec3 x1(e, 0, Hr / 2 + tc / 4 + tr);
	const canvas::vec3 x2(e / 2 - tc / 4, 0, Hr + tr);
	canvas::objects::Cube* links = new canvas::objects::Cube[4];
	canvas::objects::Cylinder* bases = new canvas::objects::Cylinder[2];
	canvas::objects::Object* upper[] = {bases + 1, links + 2, links + 3};
	//bases
	for(unsigned i = 0; i < 2; i++)
	{
		bases[i].radius(Rr);
		bases[i].height(tr);
		bases[i].color_fill({0, 0, 1});
		bases[i].shift({0, 0, tr / 2});
		scene->add_object(bases + i);
	}
	//links
	for(unsigned i = 0; i < 2; i++)
	{
		links[i + 0].color_fill({0, 0, 1});
		links[i + 2].color_fill({0, 0, 1});
		links[i + 0].sizes(i == 0 ? s1 : s2);
		links[i + 2].sizes(i == 0 ? s1 : s2);
		links[i + 0].shift(i == 0 ? x1 : x2);
		links[i + 2].shift(i == 0 ? x1 : x2);
		scene->add_object(links + i + 0);
		scene->add_object(links + i + 2);
	}
	//upper
	for(canvas::objects::Object* object : upper)
	{
		object->rotate({0, 0, tr / 2}, {0, 0, M_PI});
		object->rotate({0, 0, tr / 2}, {M_PI, 0, 0});
		object->shift({0, 0, Ht + tr});
	}
}
static void cables(canvas::Scene* scene)
{
	//data
	canvas::objects::Line* cables = new canvas::objects::Line[nc + 1];
	//cables
	for(unsigned i = 0; i <= nc; i++)
	{
		if(i == nc)
		{
			cables[i].point(0, {0, 0, Hr - tc / 2 + tr});
			cables[i].point(1, {0, 0, Ht - Hr + tc / 2 + tr});
		}
		else
		{
			cables[i].point(0, {Rr * cosf(2 * M_PI * i / nc), Rr * sinf(2 * M_PI * i / nc), tr});
			cables[i].point(1, {Rr * cosf(2 * M_PI * i / nc), Rr * sinf(2 * M_PI * i / nc), Ht + tr});
		}
		cables[i].color_stroke({0, 1, 0});
		scene->add_object(cables + i);
	}
}
static void labels(canvas::Scene* scene)
{
	//equations
	scene->add_equation("$ e $");
	scene->add_equation("$ H_c $");
	scene->add_equation("$ H_t $");
	scene->add_equation("$ H_r $");
	scene->add_equation("$ R_r $");
	//data
	canvas::objects::Equation* labels = new canvas::objects::Equation[5];
	canvas::vec3 x[] = {{e / 2, 0, Hr + tc}, {0, 0, Ht / 2 + tr}, {Rr, 0, Ht / 2 + tr}, {e + tc / 2, 0, Hr / 2}, {0, 0, 0}};
	//labels
	for(unsigned i = 0; i < 5; i++)
	{
		labels[i].index(i);
		labels[i].size(Rr / 8);
		labels[i].position(x[i]);
		labels[i].color_fill({1, 0, 0});
		labels[i].direction(1, {0, 0, 1});
		scene->add_object(labels + i);
	}

}

namespace examples
{
	namespace scenes
	{
		void tensegrity_chair(canvas::Scene* scene)
		{
			rigid(scene);
			cables(scene);
			labels(scene);
		}
	}
}