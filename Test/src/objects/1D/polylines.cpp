//canvas
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Objects/1D/Arrow.hpp"
#include "Canvas/inc/Objects/1D/Polyline.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

namespace examples
{
	namespace objects
	{
		void polylines(canvas::Scene* scene)
		{
			//data
			const float w = 1.00e-01f;
			const float h = 1.00e-01f;
			const float t = 1.00e-02f;
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
				polyline->arrow(i)->width(2.50e-03f);
				polyline->arrow(i)->height(2.50e-03f);
			}
			//scene
			scene->add_object(polyline);
		}
	}
}