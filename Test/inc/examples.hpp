#pragma once

//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"

namespace examples
{
	namespace objects
	{
		void arcs(canvas::Scene*);			//ok
		void cubes(canvas::Scene*);			//ok
		void lines(canvas::Scene*);			//ok
		void latex(canvas::Scene*);			//todo
		void bezier(canvas::Scene*);		//ok
		void curves(canvas::Scene*);		//ok
		void points(canvas::Scene*);		//ok
		void images(canvas::Scene*);		//ok
		void text2D(canvas::Scene*);		//ok
		void text3D(canvas::Scene*);		//ok
		void squares(canvas::Scene*);		//ok
		void circles(canvas::Scene*);		//ok
		void spheres(canvas::Scene*);		//ok
		void splines(canvas::Scene*);		//ok
		void graph2D(canvas::Scene*);		//todo
		void polygons(canvas::Scene*);		//ok
		void surfaces(canvas::Scene*);		//ok
		void palettes(canvas::Scene*);		//ok
		void polylines(canvas::Scene*);		//ok
		void triangles(canvas::Scene*);		//ok
		void cylinders(canvas::Scene*);		//ok
	}
	namespace scenes
	{
		void examples(void);
		void von_mises_joint(void);
		void tensegrity_chair(void);
		void user_interaction(void);
		void spherical_pantograph(void);
	}
	namespace tessellation
	{
		void convex_cw_3(void);
		void convex_ccw_3(void);
		void non_convex_cw_7(void);
		void non_convex_ccw_4(void);
		void convex_loop_cw_12(void);
		void convex_loop_ccw_8(void);
	}
}