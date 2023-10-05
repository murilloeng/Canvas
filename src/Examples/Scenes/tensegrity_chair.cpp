//canvas
#include "inc/Examples/examples.hpp"
#include "inc/Objects/Curves/Line.hpp"
#include "inc/Objects/Volumes/Cube.hpp"
#include "inc/Objects/Volumes/Cylinder.hpp"

namespace examples
{
	namespace scenes
	{
		void tensegrity_chair(canvas::Scene* scene)
		{
			//data
			const unsigned nc = 5;
			const float e = 5.50e-02;
			const float tr = 4.00e-03;
			const float tc = 1.00e-02;
			const float Rr = 1.00e-01;
			const float Ht = 3.00e-01;
			const float Hc = 1.50e-01;
			const float Hr = (Ht + Hc) / 2;
			//objects
			canvas::objects::Cube* link_top_1 = new canvas::objects::Cube;
			canvas::objects::Cube* link_top_2 = new canvas::objects::Cube;
			canvas::objects::Cube* link_base_1 = new canvas::objects::Cube;
			canvas::objects::Cube* link_base_2 = new canvas::objects::Cube;
			canvas::objects::Line* cables = new canvas::objects::Line[nc + 1];
			canvas::objects::Cylinder* rigid_top = new canvas::objects::Cylinder;
			canvas::objects::Cylinder* rigid_base = new canvas::objects::Cylinder;
			//rigid
			rigid_top->height(tr);
			rigid_top->radius(Rr);
			rigid_base->height(tr);
			rigid_base->radius(Rr);
			rigid_top->fill_color({0, 0, 1});
			rigid_base->fill_color({0, 0, 1});
			rigid_base->shift({0, 0, tr / 2});
			rigid_top->shift({0, 0, Ht + 3 * tr / 2});
			//links
			link_top_1->fill_color({0, 0, 1});
			link_top_2->fill_color({0, 0, 1});
			link_base_1->fill_color({0, 0, 1});
			link_base_2->fill_color({0, 0, 1});
			link_top_2->sizes({e - tc / 2, tc, tc});
			link_top_1->sizes({tc, tc, Hr + tc / 2});
			link_base_2->sizes({e - tc / 2, tc, tc});
			link_base_1->sizes({tc, tc, Hr + tc / 2});
			link_base_1->shift({e, 0, Hr / 2 + tc / 4 + tr});
			link_top_1->shift({-e, 0, tr + Ht - Hr / 2 - tc / 4});
			link_base_2->shift({});
			//cables
			for(unsigned i = 0; i <= nc; i++)
			{
				if(i == nc)
				{
					cables[i].point(0, {0, 0, Ht - Hr});
					cables[i].point(1, {0, 0, Hr - tc / 2});
				}
				else
				{
					cables[i].point(0, {Rr * cosf(2 * M_PI * i / nc), Rr * sinf(2 * M_PI * i / nc), tr});
					cables[i].point(1, {Rr * cosf(2 * M_PI * i / nc), Rr * sinf(2 * M_PI * i / nc), Ht + tr});
				}
				cables[i].stroke_color({0, 1, 0});
			}
			//scene
			scene->add_object(rigid_top);
			scene->add_object(rigid_base);
			scene->add_object(link_top_1);
			scene->add_object(link_top_2);
			scene->add_object(link_base_1);
			scene->add_object(link_base_2);
			for(unsigned i = 0; i <= nc; i++)
			{
				scene->add_object(cables + i);
			}
		}
	}
}