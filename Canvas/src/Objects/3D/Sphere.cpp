//std
#include <cmath>

//canvas
#include "Canvas/Canvas/inc/API/API.hpp"
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/Canvas/inc/Objects/3D/Sphere.hpp"

//static data
const float a = 0.525731112119133606f;
const float b = 0.850650808352039932f;
static const uint32_t base_edges[30][2] = {
	{0,  1}, {0,  4}, {0,  6}, {0,  9}, {0, 11}, {1,  4},
	{1,  6}, {1,  8}, {1, 10}, {2,  3}, {2,  5}, {2,  7},
	{2,  9}, {2, 11}, {3,  5}, {3,  7}, {3,  8}, {3, 10},
	{4,  5}, {4,  8}, {4,  9}, {5,  8}, {5,  9}, {6,  7},
	{6, 10}, {6, 11}, {7, 10}, {7, 11}, {8, 10}, {9, 11}
};
static const uint32_t base_faces[20][3] = {
	{0,  4,  1}, {0, 9,  4}, {9,  5, 4}, { 4, 5, 8}, {4, 8,  1},
	{8, 10,  1}, {8, 3, 10}, {5,  3, 8}, { 5, 2, 3}, {2, 7,  3},
	{7, 10,  3}, {7, 6, 10}, {7, 11, 6}, {11, 0, 6}, {0, 1,  6},
	{6,  1, 10}, {9, 0, 11}, {9, 11, 2}, { 9, 2, 5}, {7, 2, 11}
};
static const float base_vertices[12][3] =
{
	{-a, 0.0f, +b}, {+a, 0.0f, +b}, {-a, 0.0f, -b}, {+a, 0.0f, -b},
	{0.0f, +b, +a}, {0.0f, +b, -a}, {0.0f, -b, +a}, {0.0f, -b, -a},
	{+b, +a, 0.0f}, {-b, +a, 0.0f}, {+b, -a, 0.0f}, {-b, -a, 0.0f}
};

namespace canvas
{
	namespace objects
	{
		//constructors
		Sphere::Sphere(void) : m_color_fill{"blue"}, m_color_stroke{"white"}
		{
			return;
		}

		//destructor
		Sphere::~Sphere(void)
		{
			return;
		}

		//data
		uint32_t Sphere::mesh(void)
		{
			return m_mesh;
		}
		uint32_t Sphere::mesh(uint32_t mesh)
		{
			return m_mesh = mesh;
		}

		Color Sphere::color_fill(void) const
		{
			return m_color_fill;
		}
		Color Sphere::color_fill(const Color& color_fill)
		{
			return m_color_fill = color_fill;
		}

		Color Sphere::color_stroke(void) const
		{
			return m_color_stroke;
		}
		Color Sphere::color_stroke(const Color& color_stroke)
		{
			return m_color_stroke = color_stroke;
		}

		//edges
		uint32_t Sphere::edge_index(uint32_t face, uint32_t index, bool& inversed) const
		{
			//data
			const uint32_t v1 = base_faces[face][(index + 0) % 3];
			const uint32_t v2 = base_faces[face][(index + 1) % 3];
			//search
			for(uint32_t i = 0; i < 30; i++)
			{
				if(v1 == base_edges[i][0] && v2 == base_edges[i][1])
				{
					inversed = false;
					return i;
				}
				if(v1 == base_edges[i][1] && v2 == base_edges[i][0])
				{
					inversed = true;
					return i;
				}
			}
			return 0;
		}

		//vertices
		uint32_t Sphere::vertex_index(uint32_t edge, uint32_t index) const
		{
			if(index == 0)
			{
				return base_edges[edge][0];
			}
			else if(index == m_mesh)
			{
				return base_edges[edge][1];
			}
			else
			{
				return 12 + (m_mesh - 1) * edge + index - 1;
			}
		}
		uint32_t Sphere::vertex_index(uint32_t face, uint32_t index_1, uint32_t index_2) const
		{
			//data
			bool i0 = true, i1 = true, i2 = true;
			const uint32_t e0 = edge_index(face, 0, i0);
			const uint32_t e1 = edge_index(face, 1, i1);
			const uint32_t e2 = edge_index(face, 2, i2);
			//search
			if(index_2 == 0)
			{
				return vertex_index(e0, !i0 ? index_1 : m_mesh - index_1);
			}
			else if(index_1 == 0)
			{
				return vertex_index(e2, !i2 ? m_mesh - index_2 : index_2);
			}
			else if(index_1 == m_mesh - index_2)
			{
				return vertex_index(e1, !i1 ? index_2 : m_mesh - index_2);
			}
			else
			{
				return
					12 + (m_mesh - 1) * 30 + (m_mesh - 1) * (m_mesh - 2) / 2 * face +
					(index_2 - 1) * m_mesh - (index_2 + 2) * (index_2 - 1) / 2 + index_1 - 1;
			}
		}

		//buffers data
		void Sphere::ibo_edges_data(uint32_t* ibo_ptr) const
		{
			for(uint32_t i = 0; i < 30; i++)
			{
				for(uint32_t j = 0; j < m_mesh; j++)
				{
					ibo_ptr[0] = vertex_index(i, j + 0);
					ibo_ptr[1] = vertex_index(i, j + 1);
					ibo_ptr += 2;
				}
			}
			for(uint32_t i = 0; i < 20; i++)
			{
				for(uint32_t j = 0; j + 1 < m_mesh; j++)
				{
					for(uint32_t k = 1; k + j < m_mesh; k++)
					{
						ibo_ptr[0] = vertex_index(i, k + 0, j + 0);
						ibo_ptr[1] = vertex_index(i, k - 1, j + 1);
						ibo_ptr[2] = vertex_index(i, k + 0, j + 0);
						ibo_ptr[3] = vertex_index(i, k + 0, j + 1);
						ibo_ptr[4] = vertex_index(i, k - 1, j + 1);
						ibo_ptr[5] = vertex_index(i, k + 0, j + 1);
						ibo_ptr += 6;
					}
				}
			}
		}
		void Sphere::ibo_faces_data(uint32_t* ibo_ptr) const
		{
			for(uint32_t i = 0; i < 20; i++)
			{
				for(uint32_t j = 0; j < m_mesh; j++)
				{
					ibo_ptr[0] = vertex_index(i, 0, j + 0);
					ibo_ptr[1] = vertex_index(i, 0, j + 1);
					ibo_ptr[2] = vertex_index(i, 1, j + 0);
					ibo_ptr += 3;
					for(uint32_t k = 0; k + j + 1 < m_mesh; k++)
					{
						ibo_ptr[0] = vertex_index(i, k + 1, j + 0);
						ibo_ptr[1] = vertex_index(i, k + 0, j + 1);
						ibo_ptr[2] = vertex_index(i, k + 1, j + 1);
						ibo_ptr[3] = vertex_index(i, k + 1, j + 0);
						ibo_ptr[4] = vertex_index(i, k + 1, j + 1);
						ibo_ptr[5] = vertex_index(i, k + 2, j + 0);
						ibo_ptr += 6;
					}
				}
			}
		}
		void Sphere::vbo_edges_data(vertices::Model3D* vbo_data) const
		{
			//data
			vertices::Model3D* vbo_ptr = (vertices::Model3D*) vbo_data + 12;
			//edges
			for(uint32_t i = 0; i < 30; i++)
			{
				//positions
				const vec3 x1 = base_vertices[base_edges[i][0]];
				const vec3 x2 = base_vertices[base_edges[i][1]];
				//vertices
				for(uint32_t j = 1; j < m_mesh; j++)
				{
					const float s = float(j) / m_mesh;
					vbo_ptr[j - 1].m_position = m_model_matrix * (x1 + s * (x2 - x1)).unit();
				}
				//offset
				vbo_ptr += m_mesh - 1;
			}
		}
		void Sphere::vbo_faces_data(vertices::Model3D* vbo_data) const
		{
			//data
			const float l = 2 * a / m_mesh;
			const float h = sqrtf(3) / 2 * l;
			vertices::Model3D* vbo_ptr = (vertices::Model3D*) vbo_data + 12 + 30 * (m_mesh - 1);
			//faces
			for(uint32_t i = 0; i < 20; i++)
			{
				//positions
				const vec3 x1 = base_vertices[base_faces[i][0]];
				const vec3 x2 = base_vertices[base_faces[i][1]];
				const vec3 x3 = base_vertices[base_faces[i][2]];
				//directions
				const vec3 s1 = (x2 - x1).unit();
				const vec3 s3 = s1.cross(x3 - x1).unit();
				const vec3 s2 = s3.cross(s1);
				//vertices
				for(uint32_t j = 0; j + 2 < m_mesh; j++)
				{
					for(uint32_t k = 0; k + j + 2 < m_mesh; k++)
					{
						const float c2 = (j + 1) * h;
						const float c1 = (k + 1) * l + (j + 1) * l / 2;
						vbo_ptr->m_position = m_model_matrix * (x1 + c1 * s1 + c2 * s2).unit();
						vbo_ptr++;
					}
				}
			}
		}
		void Sphere::vbo_vertices_data(vertices::Model3D* vbo_data) const
		{
			//data
			vertices::Model3D* vbo_ptr = (vertices::Model3D*) vbo_data;
			//vertices
			for(uint32_t i = 0; i < 12; i++)
			{
				(vbo_ptr + i)->m_position = m_model_matrix * vec3(base_vertices[i]);
			}
		}

		//buffers
		void Sphere::setup(void)
		{
			//data
			const uint32_t nt = 20 * m_mesh * m_mesh;
			const uint32_t nl = 30 * m_mesh * m_mesh;
			const uint32_t nv = 2 + 10 * m_mesh * m_mesh;
			//allocate
			m_vbo.allocate(2 * nv);
			m_ibo.allocate(2 * nl + 3 * nt);
			uint32_t* ibo_ptr = m_ibo.data();
			vertices::Model3D* vbo_ptr = (vertices::Model3D*) m_vbo.data();
			//vbo data
			for(uint32_t i = 0; i < nv; i++)
			{
				(vbo_ptr + i)->m_color = m_color_fill;
				(vbo_ptr + nv + i)->m_color = m_color_stroke;
			}
			vbo_edges_data(vbo_ptr);
			vbo_faces_data(vbo_ptr);
			vbo_vertices_data(vbo_ptr);
			vbo_edges_data(vbo_ptr + nv);
			vbo_faces_data(vbo_ptr + nv);
			vbo_vertices_data(vbo_ptr + nv);
			//ibo data
			ibo_faces_data(ibo_ptr);
			ibo_edges_data(ibo_ptr + 3 * nt);
			//transfer
			m_ibo.transfer();
			m_vbo.transfer();
		}
		void Sphere::draw(void) const
		{
			m_vao.bind();
			m_shader.bind();
			const uint32_t nt = 60 * m_mesh * m_mesh;
			const uint32_t nv = 2 + 10 * m_mesh * m_mesh;
			glDrawElements(GL_TRIANGLES, 60 * m_mesh * m_mesh, GL_UNSIGNED_INT, nullptr);
			glDrawElementsBaseVertex(GL_LINES, 60 * m_mesh * m_mesh, GL_UNSIGNED_INT, (void*) (nt * sizeof(uint32_t)), nv);
		}

		//static
		uint32_t Sphere::m_mesh = 4;
	}
}