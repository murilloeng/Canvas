#pragma once

//canvas
#include "Canvas/Canvas/inc/Colors/Color.hpp"

namespace canvas
{
	namespace objects
	{
		namespace graphs
		{
			class Graph_2D;
		}
	}
}

namespace canvas
{
	namespace objects
	{
		namespace graphs
		{
			class Curve_2D
			{
			public:
				//constructor
				Curve_2D(void);

				//destructor
				~Curve_2D(void);

				//data
				uint32_t samples(uint32_t);
				uint32_t samples(void) const;
				const float* data(uint32_t) const;
				void data(uint32_t, const float*, const float*);

				bool points(bool);
				bool points(void) const;

				float points_size(float);
				float points_size(void) const;

				Color points_color(Color);
				Color points_color(void) const;

				uint32_t points_type(uint32_t);
				uint32_t points_type(void) const;

				bool lines(bool);
				bool lines(void) const;

				Color lines_color(Color);
				Color lines_color(void) const;

				uint32_t lines_type(uint32_t);
				uint32_t lines_type(void) const;

				float lines_thickness(float);
				float lines_thickness(void) const;

				float range(uint32_t) const;
				float range(uint32_t, float);

				void function_1(float(*)(float));
				void function_2(float(*)(float));

				//points
				void point(uint32_t, float&, float&) const;

			protected:
				//data
				float* m_data[2];
				Graph_2D* m_graph;
				uint32_t m_samples;

				bool m_points;
				float m_points_size;
				Color m_points_color;
				uint32_t m_points_type;

				bool m_lines;
				Color m_lines_color;
				uint32_t m_lines_type;
				float m_lines_thickness;

				float m_range[2];
				float (*m_function_1)(float);
				float (*m_function_2)(float);

				//friends
				friend class Graph_2D;
			};
		}
	}
}