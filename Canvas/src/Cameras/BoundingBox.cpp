//std
#include <cmath>
#include <cfloat>
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Buffers/VBO.hpp"
#include "Canvas/Canvas/inc/Cameras/BoundingBox.hpp"

namespace canvas
{
	namespace cameras
	{
		//constructor
		BoundingBox::BoundingBox(void) : 
			m_min{-FLT_MAX, -FLT_MAX, -FLT_MAX}, 
			m_max{+FLT_MAX, +FLT_MAX, +FLT_MAX}
		{
			return;
		}

		//destructor
		BoundingBox::~BoundingBox(void)
		{
			return;
		}

		//print
		void BoundingBox::print(void) const
		{
			printf("Min: %+.2e %+.2e %+.2e\n", m_min[0], m_min[1], m_min[2]);
			printf("Max: %+.2e %+.2e %+.2e\n", m_max[0], m_max[1], m_max[2]);
		}

		//data
		const float* BoundingBox::min(void) const
		{
			return m_min;
		}
		const float* BoundingBox::max(void) const
		{
			return m_max;
		}

		//status
		bool BoundingBox::status(void) const
		{
			bool test = true;
			for(const float& x : m_min) test = test && x != -FLT_MAX;
			for(const float& x : m_max) test = test && x != +FLT_MAX;
			return test;
		}

		//compute
		void BoundingBox::reset(void)
		{
			for(float& x : m_min) x = -FLT_MAX;
			for(float& x : m_max) x = +FLT_MAX;
		}
		void BoundingBox::repair(void)
		{
			if(!status())
			{
				for(float& x : m_min) x = -1;
				for(float& x : m_max) x = +1;
			}
			if((vec3(m_max) - vec3(m_min)).norm() == 0)
			{
				for(float& x : m_min) x -= 1;
				for(float& x : m_max) x += 1;
			}
		}
		void BoundingBox::compute(const Scene* scene, bool reset, bool repair)
		{
			if(reset) this->reset();
			for(const buffers::VBO* vbo : scene->vbos())
			{
				//data
				const char* data = vbo->data();
				const uint32_t vs = vbo->vertex_size();
				const uint32_t vc = vbo->vertex_count();
				//insert
				for(uint32_t i = 0; i < vc; i++)
				{
					insert_vertex((const float*) data);
					data += vs;
				}
			}
			if(repair) this->repair();
		}
		void BoundingBox::insert_vertex(const float* vertex)
		{
			for(uint32_t i = 0; i < 3; i++)
			{
				if(m_min[i] == -FLT_MAX || m_min[i] > vertex[i]) m_min[i] = vertex[i];
				if(m_max[i] == +FLT_MAX || m_max[i] < vertex[i]) m_max[i] = vertex[i];
			}
		}

		//combine
		void BoundingBox::combine(const BoundingBox& box)
		{
			for(uint32_t i = 0; i < 3; i++)
			{
				m_min[i] = fminf(m_min[i], box.m_min[i]);
				m_max[i] = fmaxf(m_max[i], box.m_max[i]);
			}
		}
		BoundingBox BoundingBox::combine(const BoundingBox& box_1, const BoundingBox& box_2)
		{
			//combine
			BoundingBox box;
			for(uint32_t i = 0; i < 3; i++)
			{
				box.m_min[i] = fminf(box_1.m_min[i], box_2.m_min[i]);
				box.m_max[i] = fmaxf(box_1.m_max[i], box_2.m_max[i]);
			}
			//return
			return box;
		}
	}
}