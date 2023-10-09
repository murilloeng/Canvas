//canvas
#include "inc/Scene/Scene.hpp"
#include "inc/Objects/Curves/Arrow.hpp"
#include "inc/Objects/Curves/Polyline.hpp"

//examples
#include "inc/Examples/examples.hpp"

namespace examples
{
	namespace objects
	{
		void polylines(canvas::Scene* scene)
		{
			//data
			const float w = 1.00e-01;
			const float h = 1.00e-01;
			const float t = 1.00e-02;
			canvas::objects::Polyline* polyline;
			//spline
			polyline = new canvas::objects::Polyline;
			polyline->points().push_back({-w / 2, -h / 2 - t, 0});
			polyline->points().push_back({+w / 2, -h / 2 - t, 0});
			polyline->points().push_back({+w / 2, -h / 2, 0});
			polyline->points().push_back({+t / 2, -h / 2, 0});
			polyline->points().push_back({+t / 2, +h / 2, 0});
			polyline->points().push_back({+w / 2, +h / 2, 0});
			polyline->points().push_back({+w / 2, +h / 2 + t, 0});
			polyline->points().push_back({-w / 2, +h / 2 + t, 0});
			polyline->points().push_back({-w / 2, +h / 2, 0});
			polyline->points().push_back({-t / 2, +h / 2, 0});
			polyline->points().push_back({-t / 2, -h / 2, 0});
			polyline->points().push_back({-w / 2, -h / 2, 0});
			polyline->points().push_back({-w / 2, -h / 2 - t, 0});
			//arrows
			for(unsigned i = 0; i < 12; i++)
			{
				polyline->add_arrow(i + 0.5f, true);
				polyline->arrow(i)->width(2.50e-03);
				polyline->arrow(i)->height(2.50e-03);
			}
			//scene
			scene->add_object(polyline);
		}
	}
}