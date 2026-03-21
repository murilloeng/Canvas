#pragma once

//canvas
#include "Canvas/inc/Scene/Scene.hpp"

namespace examples
{
	namespace objects
	{
		void arcs(canvas::Scene*);
		void cubes(canvas::Scene*);
		void lines(canvas::Scene*);
		void latex(canvas::Scene*);
		void bezier(canvas::Scene*);
		void curves(canvas::Scene*);
		void points(canvas::Scene*);
		void images(canvas::Scene*);
		void text2D(canvas::Scene*);
		void text3D(canvas::Scene*);
		void graphs(canvas::Scene*);
		void squares(canvas::Scene*);
		void circles(canvas::Scene*);
		void spheres(canvas::Scene*);
		void splines(canvas::Scene*);
		void polygons(canvas::Scene*);
		void surfaces(canvas::Scene*);
		void palettes(canvas::Scene*);
		void polylines(canvas::Scene*);
		void triangles(canvas::Scene*);
		void cylinders(canvas::Scene*);
	}
	namespace scenes
	{
		void examples(void);
		void tensegrity_chair(void);
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