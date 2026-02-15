//canvas
#include "Canvas/Canvas/inc/API/API.hpp"
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Objects/3D/Cube.hpp"
#include "Canvas/Canvas/inc/Vertices/Model3D.hpp"

//static data
static const float positions[] = {
	-1.0f, -1.0f, -1.0f,
	+1.0f, -1.0f, -1.0f,
	+1.0f, +1.0f, -1.0f,
	-1.0f, +1.0f, -1.0f,
	-1.0f, -1.0f, +1.0f,
	+1.0f, -1.0f, +1.0f,
	+1.0f, +1.0f, +1.0f,
	-1.0f, +1.0f, +1.0f
};
static const uint32_t edges[] = {
	0, 1, 1, 2, 2, 3, 3, 0,
	4, 5, 5, 6, 6, 7, 7, 4,
	0, 4, 1, 5, 2, 6, 3, 7
};
static const uint32_t faces[] = {
	0, 2, 1, 0, 3, 2,
	4, 5, 6, 4, 6, 7,
	0, 1, 5, 0, 5, 4,
	1, 2, 6, 1, 6, 5,
	2, 3, 7, 2, 7, 6,
	3, 7, 4, 3, 4, 0
};

namespace canvas
{
	namespace objects
	{
		//constructors
		Cube::Cube(void)
		{
			//setup
			m_vbo.allocate(16);
			m_ibo.allocate(60);
			memcpy(m_ibo.data(), faces, sizeof(faces));
			memcpy(m_ibo.data() + 36, edges, sizeof(edges));
			//transfer
			m_ibo.transfer();
		}

		//destructor
		Cube::~Cube(void)
		{
			return;
		}

		//draw
		void Cube::setup(void)
		{
			//data
			vertices::Model3D* vbo_data = (vertices::Model3D*) m_vbo.data();
			//vbo data
			for(uint32_t i = 0; i < 8; i++)
			{
				vbo_data[i + 0].m_color = m_color_fill;
				vbo_data[i + 8].m_color = m_color_stroke;
				vbo_data[i + 0].m_position = m_model_matrix * vec3(positions + 3 * i);
				vbo_data[i + 8].m_position = m_model_matrix * vec3(positions + 3 * i);
			}
			m_vbo.transfer();
		}
		void Cube::draw(void) const
		{
			m_vao.bind();
			m_shader.bind();
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
			glDrawElementsBaseVertex(GL_LINES, 24, GL_UNSIGNED_INT, (void*) sizeof(faces), 8);
		}
	}
}