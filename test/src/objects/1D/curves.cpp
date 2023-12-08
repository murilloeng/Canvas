//std
#include <cmath>

//canvas
#include "Canvas/lib/inc/Scene/Scene.hpp"
#include "Canvas/lib/inc/Objects/1D/Curve.hpp"
#include "Canvas/lib/inc/Objects/1D/Arrow.hpp"

//examples
#include "Canvas/test/inc/examples.hpp"

namespace examples
{
	namespace objects
	{
		void curves(canvas::Scene* scene)
		{
			//data
			const float r = 1.0f;
			const unsigned nt = 5;
			const unsigned nm = 200;
			//curve
			canvas::objects::Curve* curve = new canvas::objects::Curve;
			curve->position([r] (float s){ 
				const float v1 = r * cosf(2 * nt * M_PI * s);
				const float v2 = r * sinf(2 * nt * M_PI * s);
				return canvas::vec3(v1, v2, s);
			});
			curve->gradient([r] (float s){ 
				const float v1 = -2 * nt * M_PI * r * sinf(2 * nt * M_PI * s);
				const float v2 = +2 * nt * M_PI * r * cosf(2 * nt * M_PI * s);
				return canvas::vec3(v1, v2, 1);
			});
			curve->hessian([r] (float s){ 
				const float v1 = -4 * nt * nt * M_PI * M_PI * r * cosf(2 * nt * M_PI * s);
				const float v2 = -4 * nt * nt * M_PI * M_PI * r * sinf(2 * nt * M_PI * s);
				return canvas::vec3(v1, v2, 0);
			});
			curve->mesh(nm);
			scene->add_object(curve);
		}
	}
}