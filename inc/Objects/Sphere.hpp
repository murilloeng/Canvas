#pragma once

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Colors/Color.hpp"
#include "inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		class Sphere : public Object
		{
		public:
			//constructors
			Sphere(void);

			//destructor
			~Sphere(void);

			//data
			vec3 center(vec3);
			vec3 center(void) const;

			float radius(float);
			float radius(void) const;

			Color draw_color(Color);
			Color draw_color(void) const;

			Color fill_color(Color);
			Color fill_color(void) const;

			static unsigned mesh(void);
			static unsigned mesh(unsigned);

			//type
			objects::type type(void) const override;

		private:
			//buffers
			unsigned vbo_size(void) const override;
			unsigned ibo_size(unsigned) const override;

			//index
			unsigned vertex_index_edge(unsigned, unsigned) const;
			unsigned vertex_index_face(unsigned, unsigned, unsigned) const;

			//draw
			void ibo_draw_data(unsigned**) const;
			void ibo_fill_data(unsigned**) const;
			void vbo_draw_data(vertices::Vertex*) const;
			void vbo_fill_data(vertices::Vertex*) const;
			void vbo_edges_data(vertices::Vertex*) const;
			void vbo_faces_data(vertices::Vertex*) const;
			void vbo_vertices_data(vertices::Vertex*) const;
			void buffers_data(vertices::Vertex*, unsigned**) const override;

			//data
			vec3 m_center;
			float m_radius;
			Color m_draw_color;
			Color m_fill_color;
			static unsigned m_mesh;
		};
	}
}