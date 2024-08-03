#pragma once

//canvas
#include "Canvas/inc/Math/vec3.hpp"
#include "Canvas/inc/Vertices/Model3D.hpp"
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

			static uint32_t mesh(void);
			static uint32_t mesh(uint32_t);

		protected:
			//edges
			uint32_t edge_index(uint32_t, uint32_t, bool&) const;

			//vertices
			uint32_t vertex_index(uint32_t, uint32_t) const;
			uint32_t vertex_index(uint32_t, uint32_t, uint32_t) const;

			//data
			void ibo_fill_data(uint32_t**) const;
			void ibo_stroke_data(uint32_t**) const;
			void vbo_fill_data(vertices::Vertex**) const;
			void vbo_stroke_data(vertices::Vertex**) const;
			
			void vbo_edges_data(vertices::Model3D*) const;
			void vbo_faces_data(vertices::Model3D*) const;
			void vbo_vertices_data(vertices::Model3D*) const;

			//buffers
			void buffers_size(void) override;
			void buffers_data(vertices::Vertex**, uint32_t**) const override;

			//data
			vec3 m_center;
			float m_radius;
			static uint32_t m_mesh;
		};
	}
}