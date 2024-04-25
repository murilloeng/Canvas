//std
#include <cmath>

//canvas
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Objects/1D/Curve.hpp"
#include "Canvas/inc/Objects/1D/Arrow.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

namespace examples
{
	namespace objects
	{
		void curves(canvas::Scene* scene)
		{
			//data
			const int nt = 5;
			const int nm = 200;
			const float r = 1.0f;
			const float pi = float(M_PI);
			//curve
			canvas::objects::Curve* curve = new canvas::objects::Curve;
			curve->position([r, pi] (float s){
				const float v1 = r * cosf(2 * nt * pi * s);
				const float v2 = r * sinf(2 * nt * pi * s);
				return canvas::vec3(v1, v2, s);
			});
			curve->gradient([r, pi] (float s){
				const float v1 = -2 * nt * pi * r * sinf(2 * nt * pi * s);
				const float v2 = +2 * nt * pi * r * cosf(2 * nt * pi * s);
				return canvas::vec3(v1, v2, 1);
			});
			curve->hessian([r, pi] (float s){
				const float v1 = -4 * nt * nt * pi * pi * r * cosf(2 * nt * pi * s);
				const float v2 = -4 * nt * nt * pi * pi * r * sinf(2 * nt * pi * s);
				return canvas::vec3(v1, v2, 0);
			});
			curve->mesh(nm);
			scene->add_object(curve);
		}
	}
}