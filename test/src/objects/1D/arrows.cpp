//canvas
#include "Canvas/lib/inc/Scene/Scene.hpp"
#include "Canvas/lib/inc/Objects/1D/Line.hpp"
#include "Canvas/lib/inc/Objects/1D/Arrow.hpp"

//examples
#include "Canvas/test/inc/examples.hpp"

namespace examples
{
	namespace objects
	{
		void arrows(canvas::Scene* scene)
		{
			//objects
			canvas::objects::Line* a1 = new canvas::objects::Line;
			canvas::objects::Line* a2 = new canvas::objects::Line;
			canvas::objects::Line* a3 = new canvas::objects::Line;
			//setup
			a1->add_arrow(1, true);
			a2->add_arrow(1, true);
			a3->add_arrow(1, true);
			a1->point(0, {0, 0, 0});
			a1->point(1, {1, 0, 0});
			a2->point(0, {0, 0, 0});
			a2->point(1, {0, 1, 0});
			a3->point(0, {0, 0, 0});
			a3->point(1, {0, 0, 1});
			a1->color_stroke({1, 0, 0});
			a2->color_stroke({0, 1, 0});
			a3->color_stroke({0, 0, 1});
			//scene
			scene->add_object(a1);
			scene->add_object(a2);
			scene->add_object(a3);
		}
	}
}