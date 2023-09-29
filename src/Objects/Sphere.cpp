//std
#include <cmath>

//canvas
#include "inc/Vertices/Model.hpp"

#include "inc/Objects/Type.hpp"
#include "inc/Objects/Sphere.hpp"

//static data
const float a = 0.525731112119133606f;
const float b = 0.850650808352039932f;
static const unsigned base_edges[30][2] = {
	{0,  1}, {0,  4}, {0,  6}, {0,  9}, {0, 11}, {1,  4}, 
	{1,  6}, {1,  8}, {1, 10}, {2,  3}, {2,  5}, {2,  7}, 
	{2,  9}, {2, 11}, {3,  5}, {3,  7}, {3,  8}, {3, 10}, 
	{4,  5}, {4,  8}, {4,  9}, {5,  8}, {5,  9}, {6,  7},
	{6, 10}, {6, 11}, {7, 10}, {7, 11}, {8, 10}, {9, 11}
};
static const unsigned base_faces[20][3] = {
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
		Sphere::Sphere(void) : 
			m_center{0, 0, 0}, m_radius(1.0f), m_draw_color{0, 0, 0, 0}, m_fill_color{0, 0, 0, 0}
		{
			return;
		}

		//destructor
		Sphere::~Sphere(void)
		{
			return;
		}

		//data
		vec3 Sphere::center(void) const
		{
			return m_center;
		}
		vec3 Sphere::center(vec3 center)
		{
			return m_center = center;
		}

		float Sphere::radius(void) const
		{
			return m_radius;
		}
		float Sphere::radius(float radius)
		{
			return m_radius = radius;
		}

		Color Sphere::draw_color(void) const
		{
			return m_draw_color;
		}
		Color Sphere::draw_color(Color draw_color)
		{
			return m_draw_color = draw_color;
		}

		Color Sphere::fill_color(void) const
		{
			return m_fill_color;
		}
		Color Sphere::fill_color(Color fill_color)
		{
			return m_fill_color = fill_color;
		}

		unsigned Sphere::mesh(void)
		{
			return m_mesh;
		}
		unsigned Sphere::mesh(unsigned mesh)
		{
			return m_mesh = mesh;
		}

		//type
		objects::type Sphere::type(void) const
		{
			return objects::type::sphere;
		}

		//buffers
		unsigned Sphere::vbo_size(void) const
		{
			const unsigned nm = m_mesh;
			const unsigned nv = 12 + (nm - 1) * 30 + (nm - 1) * (nm - 2) * 10;
			return 
				nv * m_draw + 
				nv * m_fill;
		}
		unsigned Sphere::ibo_size(unsigned index) const
		{
			const unsigned nm = m_mesh;
			const unsigned nf = nm * nm * 20;
			const unsigned ne = nm * 30 + 3 * nm * (nm - 1) * 10;
			return 
				ne * (index == 1) * m_draw + 
				nf * (index == 2) * m_fill;
		}

		//index
		unsigned Sphere::vertex_index_edge(unsigned edge, unsigned index) const
		{
			return 
				index == 0 ? base_edges[edge][0] : 
				index == m_mesh ? base_edges[edge][1] : 
				12 + (m_mesh - 1) * edge + index - 1;
		}
		unsigned Sphere::vertex_index_face(unsigned face, unsigned index_1, unsigned index_2) const
		{

		}

		//draw
		void Sphere::ibo_draw_data(unsigned** ibo_data) const
		{
			//data
			unsigned* ibo_ptr = ibo_data[1] + m_ibo_index[1];
			//edges
			for(unsigned i = 0; i < 30; i++)
			{
				for(unsigned j = 0; j < m_mesh; j++)
				{
					ibo_ptr[0] = m_vbo_index + (j + 0) % m_mesh == 0 ? base_edges[i][0] : 12 + (m_mesh - 1) * i + j - 1;
					ibo_ptr[1] = m_vbo_index + (j + 1) % m_mesh == 0 ? base_edges[i][1] : 12 + (m_mesh - 1) * i + j + 0;
					ibo_ptr += 2;
				}
			}
			//faces
			for(unsigned i = 0; i < 20; i++)
			{
				
			}
			
		}
		void Sphere::ibo_fill_data(unsigned** ibo_data) const
		{
			//data
			const unsigned vbo_index = m_vbo_index + 12;
			unsigned* ibo_ptr = ibo_data[2] + m_ibo_index[2];
			//triangles
			for(unsigned i = 0; i < 20; i++)
			{
				ibo_ptr[3 * i + 0] = vbo_index + base_faces[i][0];
				ibo_ptr[3 * i + 1] = vbo_index + base_faces[i][1];
				ibo_ptr[3 * i + 2] = vbo_index + base_faces[i][2];
			}
		}
		void Sphere::vbo_draw_data(vertices::Vertex* vbo_data) const
		{
			//data
			const unsigned nv = vbo_size();
			vertices::Model* vbo_ptr = (vertices::Model*) vbo_data + m_vbo_index;
			//color
			for(unsigned i = 0; i < nv; i++)
			{
				(vbo_ptr + i)->m_color = m_draw_color;
			}
			//positions
			vbo_edges_data(vbo_ptr);
			vbo_faces_data(vbo_ptr);
			vbo_vertices_data(vbo_ptr);
		}
		void Sphere::vbo_fill_data(vertices::Vertex* vbo_data) const
		{
			//data
			const unsigned nv = vbo_size();
			vertices::Model* vbo_ptr = (vertices::Model*) vbo_data + m_vbo_index + nv;
			//color
			for(unsigned i = 0; i < nv; i++)
			{
				(vbo_ptr + i)->m_color = m_fill_color;
			}
			//positions
			vbo_edges_data(vbo_ptr);
			vbo_faces_data(vbo_ptr);
			vbo_vertices_data(vbo_ptr);
		}
		void Sphere::vbo_edges_data(vertices::Vertex* vbo_data) const
		{
			//data
			vertices::Model* vbo_ptr = (vertices::Model*) vbo_data + m_vbo_index + 12;
			//edges
			for(unsigned i = 0; i < 30; i++)
			{
				//positions
				const vec3 x1 = base_vertices[base_edges[i][0]];
				const vec3 x2 = base_vertices[base_edges[i][1]];
				//vertices
				for(unsigned j = 1; j < m_mesh; j++)
				{
					const float s = float(j) / m_mesh;
					(vbo_ptr + 12 + (m_mesh - 1) * i + j)->m_position = m_center + m_radius * (x1 + s * (x2 - x1)).unit();
				}
			}
		}
		void Sphere::vbo_faces_data(vertices::Vertex* vbo_data) const
		{
			//data
			unsigned counter = 0;
			const float l = 2 * a / m_mesh;
			const float h = sqrtf(3) / 2 * l;
			vertices::Model* vbo_ptr = (vertices::Model*) vbo_data + m_vbo_index + 12 + 30 * (m_mesh - 1);
			//faces
			for(unsigned i = 0; i < 20; i++)
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
				for(unsigned j = 0; j < m_mesh - 2; j++)
				{
					for(unsigned k = 0; k < m_mesh - 2 - j; k++)
					{
						const float c2 = (j + 1) * h;
						const float c1 = (k + 1) * l + (j + 1) * l / 2;
						(vbo_ptr + counter)->m_position = m_center + m_radius * (x1 + c1 * s1 + c2 * s2).unit();
						counter++;
					}
				}
			}
		}
		void Sphere::vbo_vertices_data(vertices::Vertex* vbo_data) const
		{
			//data
			vertices::Model* vbo_ptr = (vertices::Model*) vbo_data + m_vbo_index;
			//vertices
			for(unsigned i = 0; i < 12; i++)
			{
				(vbo_ptr + i)->m_position = m_center + m_radius * vec3(base_vertices[i]);
			}
		}
		void Sphere::buffers_data(vertices::Vertex* vbo_data, unsigned** ibo_data) const
		{
			//vbo data
			if(m_draw) vbo_draw_data(vbo_data);
			if(m_fill) vbo_fill_data(vbo_data);
			//ibo data
			if(m_draw) ibo_draw_data(ibo_data);
			if(m_fill) ibo_fill_data(ibo_data);
		}

		//static
		unsigned Sphere::m_mesh = 1;
	}
}