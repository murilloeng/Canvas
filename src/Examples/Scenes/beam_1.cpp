//canvas
#include "inc/Examples/examples.hpp"
#include "inc/Examples/defs/Beam.hpp"
#include "inc/Objects/Curves/Arc.hpp"
#include "inc/Objects/Curves/Line.hpp"
#include "inc/Objects/Curves/Arrow.hpp"
#include "inc/Examples/defs/Support_1.hpp"
#include "inc/Examples/defs/Support_2.hpp"
#include "inc/Examples/defs/Support_3.hpp"

namespace examples
{
	namespace scenes
	{
		void beam_1(canvas::Scene* scene)
		{
			//objects
			Beam* beam = new Beam(6.00f, 0.60f);
			Support_1* support_1 = new Support_1(0.60f);
			Support_2* support_2 = new Support_2(0.60f);
			Support_3* support_3 = new Support_3(1.50f, 0.30f);
			canvas::objects::Arc* moment_1 = new canvas::objects::Arc;
			canvas::objects::Line* force_1 = new canvas::objects::Line;
			//supports
			support_1->shift({3.00f, 0.00f, 0.10f});
			support_2->shift({6.00f, 0.00f, 0.10f});
			support_3->shift({0.00f, 0.00f, 0.10f});
			//forces
			force_1->add_arrow(0.00f, true);
			force_1->arrow(0)->sense(false);
			force_1->arrow(0)->width(0.10f);
			force_1->arrow(0)->height(0.10f);
			force_1->point(0, {4.50f, 0.00f, 0.00f});
			force_1->point(1, {4.50f, 0.60f, 0.00f});
			force_1->color_stroke({1.00f, 0.00f, 0.00f});
			//moments
			moment_1->fill(false);
			moment_1->radius(0.40f);
			moment_1->angle(0, -M_PI_2);
			moment_1->angle(1, +M_PI_2);
			moment_1->add_arrow(1.00f, true);
			moment_1->arrow(0)->width(0.10f);
			moment_1->arrow(0)->height(0.10f);
			moment_1->center({1.50f, 0.00f, 0.10f});
			moment_1->color_stroke({1.00f, 0.00f, 0.00f});
			//scene
			scene->add_object(beam);
			scene->add_object(force_1);
			scene->add_object(moment_1);
			scene->add_object(support_1);
			scene->add_object(support_2);
			scene->add_object(support_3);
			scene->background({1, 1, 1, 1});
		}
	}
}