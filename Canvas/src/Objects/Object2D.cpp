//Canvas
#include "Canvas/Canvas/inc/Objects/Object2D.hpp"

namespace canvas
{
	namespace objects
	{
		//constructor
		Object2D::Object2D(void) : m_has_model_matrix{false}
		{
			return;
		}
		
		//destructor
		Object2D::~Object2D(void)
		{
			return;
		}

		//data
		mat3 Object2D::model_matrix(void) const
		{
			return m_model_matrix;
		}
		mat3 Object2D::model_matrix(mat3 model_matrix)
		{
			m_has_model_matrix = true;
			return m_model_matrix = model_matrix;
		}
		mat3 Object2D::apply_matrix(mat3 affine, bool left)
		{
			m_has_model_matrix = true;
			return m_model_matrix = left ? affine * m_model_matrix : m_model_matrix * affine;
		}

		//transformations
		void Object2D::reset(void)
		{
			m_model_matrix.clear();
			m_has_model_matrix = false;
		}
		void Object2D::scale(float s)
		{
			m_has_model_matrix = true;
			m_model_matrix = mat3::scaling(s) * m_model_matrix;
		}
		void Object2D::scale(const vec2& s, bool left)
		{
			m_has_model_matrix = true;
			const mat3 A = mat3::scaling(s);
			m_model_matrix = left ? A * m_model_matrix : m_model_matrix * A;
		}
		void Object2D::shift(const vec2& x , bool left)
		{
			m_has_model_matrix = true;
			const mat3 A = mat3::shifting(x);
			m_model_matrix = left ? A * m_model_matrix : m_model_matrix * A;
		}
		void Object2D::rotate(float t, bool left)
		{
			m_has_model_matrix = true;
			const mat3 A = mat3::rotation(t);
			m_model_matrix = left ? A * m_model_matrix : m_model_matrix * A;
		}
	}
}