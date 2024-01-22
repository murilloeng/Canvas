#pragma once

//canvas
#include "Canvas/inc/Math/vec3.hpp"
#include "Canvas/inc/Vertices/Model.hpp"
#include "Canvas/inc/Objects/Geometry.hpp"

namespace canvas
{
	namespace objects
	{
		class Sphere : public Geometry
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

		protected:
			//buffers
			unsigned vbo_size(unsigned) const override;
			unsigned ibo_size(unsigned) const override;

			//edges
			unsigned edge_index(unsigned, unsigned, bool&) const;

			//vertices
			unsigned vertex_index(unsigned, unsigned) const;
			unsigned vertex_index(unsigned, unsigned, unsigned) const;

			//draw
			void ibo_fill_data(unsigned**) const;
			void ibo_stroke_data(unsigned**) const;
			void vbo_fill_data(vertices::Vertex**) const;
			void vbo_stroke_data(vertices::Vertex**) const;
			
			void vbo_edges_data(vertices::Model*) const;
			void vbo_faces_data(vertices::Model*) const;
			void vbo_vertices_data(vertices::Model*) const;

			void buffers_data(vertices::Vertex**, unsigned**) const override;

			//data
			vec3 m_center;
			float m_radius;
			static unsigned m_mesh;
		};
	}
}