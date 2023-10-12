//canvas
#include "inc/Examples/examples.hpp"
#include "inc/Objects/1D/Line.hpp"
#include "inc/Objects/3D/Cube.hpp"
#include "inc/Objects/3D/Cylinder.hpp"

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
			canvas::objects::Cube* link_3 = new canvas::objects::Cube;
			canvas::objects::Cube* link_4 = new canvas::objects::Cube;
			canvas::objects::Cube* link_1 = new canvas::objects::Cube;
			canvas::objects::Cube* link_2 = new canvas::objects::Cube;
			canvas::objects::Line* cables = new canvas::objects::Line[nc + 1];
			canvas::objects::Cylinder* rigid_top = new canvas::objects::Cylinder;
			canvas::objects::Cylinder* rigid_base = new canvas::objects::Cylinder;
			//rigid
			rigid_top->height(tr);
			rigid_top->radius(Rr);
			rigid_base->height(tr);
			rigid_base->radius(Rr);
			rigid_top->color_fill({0, 0, 1});
			rigid_base->color_fill({0, 0, 1});
			rigid_base->shift({0, 0, tr / 2});
			rigid_top->shift({0, 0, Ht + 3 * tr / 2});
			//links
			link_3->color_fill({0, 0, 1});
			link_4->color_fill({0, 0, 1});
			link_1->color_fill({0, 0, 1});
			link_2->color_fill({0, 0, 1});
			link_4->sizes({e - tc / 2, tc, tc});
			link_2->sizes({e - tc / 2, tc, tc});
			link_3->sizes({tc, tc, Hr + tc / 2});
			link_1->sizes({tc, tc, Hr + tc / 2});
			link_1->shift({e, 0, Hr / 2 + tc / 4 + tr});
			link_2->shift({e / 2 - tc / 4, 0, Hr + tr});
			link_4->shift({tc / 4 - e / 2, 0, Hr - Hc + tr});
			link_3->shift({-e, 0, tr + Ht - Hr / 2 - tc / 4});
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
			}
			//scene
			scene->add_object(rigid_top);
			scene->add_object(rigid_base);
			scene->add_object(link_3);
			scene->add_object(link_4);
			scene->add_object(link_1);
			scene->add_object(link_2);
			for(unsigned i = 0; i <= nc; i++)
			{
				scene->add_object(cables + i);
			}
		}
	}
}