#pragma once

//canvas
#include "inc/Math/vec3.hpp"
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
			vec3 center(void) const;
			vec3 center(const vec3&);

			float radius(float);
			float radius(void) const;

			static unsigned mesh(void);
			static unsigned mesh(unsigned);

			//type
			objects::type type(void) const override;

		private:
			//buffers
			unsigned vbo_size(void) const override;
			unsigned ibo_size(unsigned) const override;

			//edges
			unsigned edge_index(unsigned, unsigned, bool&) const;

			//vertices
			unsigned vertex_index(unsigned, unsigned) const;
			unsigned vertex_index(unsigned, unsigned, unsigned) const;

			//draw
			void ibo_fill_data(unsigned**) const;
			void ibo_stroke_data(unsigned**) const;
			void vbo_fill_data(vertices::Vertex*) const;
			void vbo_stroke_data(vertices::Vertex*) const;
			
			void vbo_edges_data(vertices::Vertex*) const;
			void vbo_faces_data(vertices::Vertex*) const;
			void vbo_vertices_data(vertices::Vertex*) const;

			void buffers_data(vertices::Vertex*, unsigned**) const override;

			//data
			vec3 m_center;
			float m_radius;
			static unsigned m_mesh;
		};
	}
}