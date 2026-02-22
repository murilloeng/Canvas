#pragma once

//Canvas
#include "Canvas/Canvas/inc/Buffers/VAO.hpp"
#include "Canvas/Canvas/inc/Buffers/VBO.hpp"
#include "Canvas/Canvas/inc/Buffers/IBO.hpp"
#include "Canvas/Canvas/inc/Colors/Color.hpp"
#include "Canvas/Canvas/inc/Objects/Object.hpp"
#include "Canvas/Canvas/inc/Shaders/Shader.hpp"
#include "Canvas/Canvas/inc/Vertices/Line2D.hpp"
#include "Canvas/Canvas/inc/Vertices/Text2D.hpp"
#include "Canvas/Canvas/inc/Objects/Graph/Axis.hpp"

namespace canvas
{
	namespace objects
	{
		class Graph;
	}
}

namespace canvas
{
	namespace objects
	{
		namespace graphs
		{
			class Frame : public Object
			{
			private:
				//constructor
				Frame(const Graph*);
	
				//destructor
				~Frame(void);

			public:
				//data
				Axis& axis(uint32_t);

				Color color(void) const;
				Color color(const Color&);

				uint32_t thickness(uint32_t);
				uint32_t thickness(void) const;

			private:
				//compute
				void compute_offset(void);

				//draw
				void setup(void) override;
				void draw(void) const override;

				//text
				float text_width(float, float) const;
				float text_width(float, std::string) const;

				float text_height(float, float) const;
				float text_height(float, std::string) const;

				//bufers
				// void ibo_data_frame(uint32_t*) const;
				void vbo_data_frame(vertices::Line2D*) const;
				
				void ibo_data_ticks(uint32_t*) const;
				void vbo_data_ticks_vertical(vertices::Text2D*&) const;
				void vbo_data_ticks_horizontal(vertices::Text2D*&) const;

				//data
				Color m_color;
				Axis m_axis[2];
				float m_offset[4];
				uint32_t m_thickness;
				const Graph* m_graph;
				buffers::VAO m_vaos[2];
				buffers::VBO m_vbos[2];
				buffers::IBO m_ibos[2];
				shaders::Shader m_shaders[2];
	
				//friends
				friend class objects::Graph;
			};
		}
	}
}