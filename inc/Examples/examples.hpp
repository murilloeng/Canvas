#pragma once

//canvas
#include "inc/Scene/Scene.hpp"

namespace examples
{
	namespace objects
	{
		void arcs(canvas::Scene*);
		void text(canvas::Scene*);
		void cubes(canvas::Scene*);
		void lines(canvas::Scene*);
		void quads(canvas::Scene*);
		void points(canvas::Scene*);
		void images(canvas::Scene*);
		void circles(canvas::Scene*);
		void spheres(canvas::Scene*);
		void splines(canvas::Scene*);
		void grid_2D(canvas::Scene*);
		void grid_3D(canvas::Scene*);
		void equations(canvas::Scene*);
		void polylines(canvas::Scene*);
		void triangles(canvas::Scene*);
		void cylinders(canvas::Scene*);
	}
	namespace scenes
	{
		void beam_1(canvas::Scene*);
		void tensegrity_chair(canvas::Scene*);
	}
}