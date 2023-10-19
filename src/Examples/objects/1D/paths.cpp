//canvas
#include "inc/Scene/Scene.hpp"
#include "inc/Objects/1D/Arc.hpp"
#include "inc/Objects/1D/Line.hpp"
#include "inc/Objects/1D/Path.hpp"
#include "inc/Objects/1D/Arrow.hpp"

//examples
#include "inc/Examples/examples.hpp"

namespace examples
{
	namespace objects
	{
		void paths(canvas::Scene* scene)
		{
			//data
			const float h = 0.2f;
			const float L = 6.0f;
			canvas::objects::Arc* arc_1 = new canvas::objects::Arc;
			canvas::objects::Arc* arc_2 = new canvas::objects::Arc;
			canvas::objects::Path* path = new canvas::objects::Path;
			canvas::objects::Line* line_1 = new canvas::objects::Line;
			canvas::objects::Line* line_2 = new canvas::objects::Line;
			//arcs
			arc_1->radius(h);
			arc_2->radius(h);
			arc_1->center({0, 0, 0});
			arc_2->center({L, 0, 0});
			arc_1->angle(0, +M_PI_2);
			arc_2->angle(0, -M_PI_2);
			arc_2->angle(1, +M_PI_2);
			arc_1->angle(1, +3 * M_PI_2);
			//lines
			line_1->point(0, {0, -h, 0});
			line_1->point(1, {L, -h, 0});
			line_2->point(0, {L, +h, 0});
			line_2->point(1, {0, +h, 0});
			//path
			path->add_curve(arc_1);
			path->add_curve(arc_2);
			path->add_curve(line_1);
			path->add_curve(line_2);
			//scene
			scene->add_object(path);
		}
	}
}