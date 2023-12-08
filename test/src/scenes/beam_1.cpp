//std
#include <cmath>

//canvas
#include "Canvas/lib/inc/Objects/1D/Line.hpp"
#include "Canvas/lib/inc/Objects/1D/Arrow.hpp"
#include "Canvas/lib/inc/Objects/Image/Text.hpp"

//examples
#include "Canvas/test/inc/examples.hpp"
#include "Canvas/test/inc/defs/Beam.hpp"
#include "Canvas/test/inc/defs/Support_1.hpp"
#include "Canvas/test/inc/defs/Support_2.hpp"
#include "Canvas/test/inc/defs/Support_3.hpp"

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
			canvas::objects::Text* text_1 = new canvas::objects::Text;
			canvas::objects::Text* text_2 = new canvas::objects::Text;
			canvas::objects::Text* text_3 = new canvas::objects::Text;
			canvas::objects::Text* text_4 = new canvas::objects::Text;
			canvas::objects::Line* mark_1 = new canvas::objects::Line;
			canvas::objects::Line* mark_2 = new canvas::objects::Line;
			canvas::objects::Line* force_1 = new canvas::objects::Line;
			canvas::objects::Line* force_2 = new canvas::objects::Line;
			//supports
			support_1->shift({3.00f, 0.00f, 0.01f});
			support_2->shift({6.00f, 0.00f, 0.01f});
			support_3->shift({0.00f, 0.00f, 0.01f});
			//force 1
			force_1->add_arrow(0.00f, true);
			force_1->arrow(0)->sense(false);
			force_1->arrow(0)->width(0.10f);
			force_1->arrow(0)->height(0.10f);
			force_1->point(0, {1.50f, 0.00f, 0.00f});
			force_1->point(1, {1.50f, 0.60f, 0.00f});
			force_1->color_stroke({1.00f, 0.00f, 0.00f});
			//force 2
			force_2->add_arrow(0.00f, true);
			force_2->arrow(0)->sense(false);
			force_2->arrow(0)->width(0.10f);
			force_2->arrow(0)->height(0.10f);
			force_2->point(0, {4.50f, 0.00f, 0.00f});
			force_2->point(1, {4.50f, 0.60f, 0.00f});
			force_2->color_stroke({1.00f, 0.00f, 0.00f});
			//mark 1
			mark_1->add_arrow(0.00f, true);
			mark_1->add_arrow(1.00f, true);
			mark_1->arrow(0)->width(0.00f);
			mark_1->arrow(1)->width(0.00f);
			mark_1->arrow(0)->height(0.10f);
			mark_1->arrow(1)->height(0.10f);
			mark_1->point(0, {0.00f, -0.85f, 0.00f});
			mark_1->point(1, {3.00f, -0.85f, 0.00f});
			mark_1->color_stroke({1.00f, 0.00f, 0.00f});
			//mark 2
			mark_2->add_arrow(0.00f, true);
			mark_2->add_arrow(1.00f, true);
			mark_2->arrow(0)->width(0.00f);
			mark_2->arrow(1)->width(0.00f);
			mark_2->arrow(0)->height(0.10f);
			mark_2->arrow(1)->height(0.10f);
			mark_2->point(0, {3.00f, -0.85f, 0.00f});
			mark_2->point(1, {6.00f, -0.85f, 0.00f});
			mark_2->color_stroke({1.00f, 0.00f, 0.00f});
			//text 1
			text_1->text("L");
			text_1->size(0.40f);
			text_1->anchor("NC");
			text_1->position({1.50f, -0.90f, 0.00f});
			text_1->color_fill({1.00f, 0.00f, 0.00f});
			//text 2
			text_2->text("L");
			text_2->size(0.40f);
			text_2->anchor("NC");
			text_2->position({4.50f, -0.90f, 0.00f});
			text_2->color_fill({1.00f, 0.00f, 0.00f});
			//text 3
			text_3->text("P");
			text_3->size(0.40f);
			text_3->anchor("CE");
			text_3->position({1.50f, 0.60f, 0.00f});
			text_3->color_fill({1.00f, 0.00f, 0.00f});
			//text 4
			text_4->text("P");
			text_4->size(0.40f);
			text_4->anchor("CE");
			text_4->position({4.50f, 0.60f, 0.00f});
			text_4->color_fill({1.00f, 0.00f, 0.00f});
			//fonts
			scene->add_font("Times");
			//scene
			scene->add_object(beam);
			scene->add_object(text_1);
			scene->add_object(text_2);
			scene->add_object(text_3);
			scene->add_object(text_4);
			scene->add_object(mark_1);
			scene->add_object(mark_2);
			scene->add_object(force_1);
			scene->add_object(force_2);
			scene->add_object(support_1);
			scene->add_object(support_2);
			scene->add_object(support_3);
			scene->background({1, 1, 1, 1});
		}
	}
}