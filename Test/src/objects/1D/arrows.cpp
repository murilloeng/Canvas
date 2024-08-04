//canvas
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Objects/1D/Line.hpp"
#include "Canvas/inc/Objects/1D/Arrow.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

namespace examples
{
	namespace objects
	{
		void arrows(canvas::Scene* scene)
		{
			//objects
			canvas::objects::Line* line_1 = new canvas::objects::Line;
			canvas::objects::Line* line_2 = new canvas::objects::Line;
			canvas::objects::Line* line_3 = new canvas::objects::Line;
			canvas::objects::Arrow* arrow_1 = new canvas::objects::Arrow;
			canvas::objects::Arrow* arrow_2 = new canvas::objects::Arrow;
			canvas::objects::Arrow* arrow_3 = new canvas::objects::Arrow;
			//lines
			line_1->point(0, {0, 0, 0});
			line_1->point(1, {1, 0, 0});
			line_2->point(0, {0, 0, 0});
			line_2->point(1, {0, 1, 0});
			line_3->point(0, {0, 0, 0});
			line_3->point(1, {0, 0, 1});
			line_1->color_stroke({1, 0, 0});
			line_2->color_stroke({0, 1, 0});
			line_3->color_stroke({0, 0, 1});
			//arrows
			arrow_1->path(line_1);
			arrow_2->path(line_2);
			arrow_3->path(line_3);
			arrow_1->parameter(1.0f);
			arrow_2->parameter(1.0f);
			arrow_3->parameter(1.0f);
			//scene
			scene->add_object(line_1);
			scene->add_object(line_2);
			scene->add_object(line_3);
			scene->add_object(arrow_1);
			scene->add_object(arrow_2);
			scene->add_object(arrow_3);
		}
	}
}