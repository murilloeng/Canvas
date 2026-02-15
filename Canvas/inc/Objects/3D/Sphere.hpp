#pragma once

//std
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Objects/Model3D.hpp"

namespace canvas
{
	namespace objects
	{
		class Sphere : public Model3D
		{
		public:
			//constructors
			Sphere(void);

			//destructor
			~Sphere(void);

			//data
			static uint32_t mesh(void);
			static uint32_t mesh(uint32_t);

		protected:
			//edges
			uint32_t edge_index(uint32_t, uint32_t, bool&) const;

			//vertices
			uint32_t vertex_index(uint32_t, uint32_t) const;
			uint32_t vertex_index(uint32_t, uint32_t, uint32_t) const;

			//buffers data
			void ibo_edges_data(uint32_t*) const;
			void ibo_faces_data(uint32_t*) const;
			void vbo_edges_data(vertices::Model3D*) const;
			void vbo_faces_data(vertices::Model3D*) const;
			void vbo_vertices_data(vertices::Model3D*) const;

			//draw
			void setup(void) override;
			void draw(void) const override;

			//data
			static uint32_t m_mesh;
		};
	}
}