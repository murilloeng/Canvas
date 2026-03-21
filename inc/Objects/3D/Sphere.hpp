#pragma once

//std
#include <cstdint>

//canvas
#include "Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/inc/Objects/Bases/BaseModel3D.hpp"

namespace canvas
{
	namespace objects
	{
		class Sphere : public BaseModel3D
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
			void draw(void) override;
			void setup(void) override;
			void update(void) override;

			//data
			static uint32_t m_mesh;
		};
	}
}