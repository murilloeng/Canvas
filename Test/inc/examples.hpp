#pragma once

//canvas
#include "Canvas/inc/Scene/Scene.hpp"

namespace examples
{
	namespace objects
	{
		void arcs(canvas::Scene*);
		void text(canvas::Scene*);
		void group(canvas::Scene*);
		void cubes(canvas::Scene*);
		void lines(canvas::Scene*);
		void quads(canvas::Scene*);
		void latex(canvas::Scene*);
		void arrows(canvas::Scene*);
		void curves(canvas::Scene*);
		void points(canvas::Scene*);
		void images(canvas::Scene*);
		void circles(canvas::Scene*);
		void spheres(canvas::Scene*);
		void splines(canvas::Scene*);
		void grid_2D(canvas::Scene*);
		void polygons(canvas::Scene*);
		void surfaces(canvas::Scene*);
		void palettes(canvas::Scene*);
		void polylines(canvas::Scene*);
		void triangles(canvas::Scene*);
		void cylinders(canvas::Scene*);
	}
	namespace scenes
	{
		void examples(int32_t, char**);
		void rigid_map(int32_t, char**);
		void von_mises_joint(int32_t, char**);
		void tensegrity_chair(int32_t, char**);
		void spherical_pantograph(int32_t, char**);
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