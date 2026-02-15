#pragma once

//std
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Objects/Model3D.hpp"

namespace canvas
{
	namespace objects
	{
		class Cylinder : public Model3D
		{
		public:
			//constructors
			Cylinder(void);

			//destructor
			~Cylinder(void);

			//data
			static uint32_t mesh(void);
			static uint32_t mesh(uint32_t);

		protected:
			//buffers data
			void ibo_edges_data(uint32_t*) const;
			void ibo_faces_data(uint32_t*) const;
			void vbo_edges_data(vertices::Model3D*) const;
			void vbo_faces_data(vertices::Model3D*) const;

			//draw
			void setup(void) override;
			void draw(void) const override;

			//data
			static uint32_t m_mesh;
		};
	}
}