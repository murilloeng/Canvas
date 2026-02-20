//Canvas
#include "Canvas/Canvas/inc/Objects/Bases/BaseObject3D.hpp"

namespace canvas
{
	namespace objects
	{
		//constructor
		BaseObject3D::BaseObject3D(void) : m_has_model_matrix{false}
		{
			return;
		}
		
		//destructor
		BaseObject3D::~BaseObject3D(void)
		{
			return;
		}

		//data
		mat4 BaseObject3D::model_matrix(void) const
		{
			return m_model_matrix;
		}
		mat4 BaseObject3D::model_matrix(mat4 model_matrix)
		{
			m_has_model_matrix = true;
			return m_model_matrix = model_matrix;
		}
		mat4 BaseObject3D::apply_matrix(mat4 affine, bool left)
		{
			m_has_model_matrix = true;
			return m_model_matrix = left ? affine * m_model_matrix : m_model_matrix * affine;
		}

		//transformations
		void BaseObject3D::reset(void)
		{
			m_model_matrix.clear();
			m_has_model_matrix = false;
		}
		void BaseObject3D::scale(float s)
		{
			m_has_model_matrix = true;
			m_model_matrix = mat4::scaling(s) * m_model_matrix;
		}
		void BaseObject3D::scale(const vec3& s, bool left)
		{
			m_has_model_matrix = true;
			const mat4 A = mat4::scaling(s);
			m_model_matrix = left ? A * m_model_matrix : m_model_matrix * A;
		}
		void BaseObject3D::shift(const vec3& x , bool left)
		{
			m_has_model_matrix = true;
			const mat4 A = mat4::shifting(x);
			m_model_matrix = left ? A * m_model_matrix : m_model_matrix * A;
		}
		void BaseObject3D::rotate(const vec3& t, bool left)
		{
			m_has_model_matrix = true;
			const mat4 A = mat4::rotation(t);
			m_model_matrix = left ? A * m_model_matrix : m_model_matrix * A;
		}
		void BaseObject3D::rotate(const quat& q, bool left)
		{
			m_has_model_matrix = true;
			const mat4 A = mat4::rotation(q);
			m_model_matrix = left ? A * m_model_matrix : m_model_matrix * A;
		}
		void BaseObject3D::rotate(const vec3& x, const vec3& t, bool left)
		{
			m_has_model_matrix = true;
			const mat4 A = mat4::rotation(x, t);
			m_model_matrix = left ? A * m_model_matrix : m_model_matrix * A;
		}
		void BaseObject3D::rotate(const vec3& x, const quat& q, bool left)
		{
			m_has_model_matrix = true;
			const mat4 A = mat4::rotation(x, q);
			m_model_matrix = left ? A * m_model_matrix : m_model_matrix * A;
		}
	}
}