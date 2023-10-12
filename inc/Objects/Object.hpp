#pragma once

//canvas
#include "inc/Math/mat4.hpp"
#include "inc/Colors/Color.hpp"

namespace canvas
{
	class Scene;
	namespace vertices
	{
		class Vertex;
	}
	namespace objects
	{
		class Group;
		enum class type : unsigned;
	}
}

namespace canvas
{
	namespace objects
	{
		class Object
		{
		public:
			//constructors
			Object(void);

			//destructor
			virtual ~Object(void);

			//data
			bool dot(void) const;
			virtual bool dot(bool);

			bool fill(void) const;
			virtual bool fill(bool);

			bool stroke(void) const;
			virtual bool stroke(bool);

			Color color_dot(void) const;
			virtual Color color_dot(const Color&);

			Color color_fill(void) const;
			virtual Color color_fill(const Color&);

			Color color_stroke(void) const;
			virtual Color color_stroke(const Color&);

			//affine
			mat4 affine(mat4);
			mat4 affine(void) const;
			mat4 apply_affine(mat4, bool = true);

			void scale(float);
			void scale(const vec3&, bool = true);
			void shift(const vec3&, bool = true);
			void rotate(const vec3&, bool = true);
			void rotate(const quat&, bool = true);
			void rotate(const vec3&, const vec3&, bool = true);
			void rotate(const vec3&, const quat&, bool = true);

		protected:
			//size
			virtual unsigned vbo_size(unsigned) const = 0;
			virtual unsigned ibo_size(unsigned) const = 0;

			//buffers
			virtual void buffers_index(unsigned&, unsigned[]);
			virtual void buffers_data(vertices::Vertex*, unsigned**) const = 0;

			//data
			bool m_dot;
			bool m_fill;
			bool m_stroke;

			mat4 m_affine;

			Color m_color_dot;
			Color m_color_fill;
			Color m_color_stroke;

			unsigned m_vbo_index[3];
			unsigned m_ibo_index[5];

			//friends
			friend class Group;
			friend class canvas::Scene;
		};
	}
}