#pragma once

//std
#include <vector>

//canvas
#include "Canvas/inc/Objects/Geometry.hpp"

namespace canvas
{
	namespace objects
	{
		class Group : public Geometry
		{
		public:
			//constructors
			Group(void);

			//destructor
			virtual ~Group(void);

			//data
			bool dot(bool) override;
			bool fill(bool) override;
			bool stroke(bool) override;

			Color color_dot(const Color&) override;
			Color color_fill(const Color&) override;
			Color color_stroke(const Color&) override;

		protected:
			//setup
			void setup(void) override;

			//model
			void vbo_model_matrix(vertices::Vertex**) const;
			
			//buffers
			void buffers_size(void) override;
			void buffers_data(vertices::Vertex**, uint32_t**) const override;

			//data
			std::vector<Geometry*> m_geometries;
		};
	}
}