#pragma once

//std
#include <vector>

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

			virtual void dot_color(const Color&);
			virtual void dot_color(const Color&, unsigned);

			virtual void fill_color(const Color&);
			virtual void fill_color(const Color&, unsigned);

			virtual void stroke_color(const Color&);
			virtual void stroke_color(const Color&, unsigned);

			//name
			const char* name(void) const;
			static const char* name(objects::type);

			//type
			virtual objects::type type(void) const = 0;

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
			virtual unsigned vbo_size(void) const = 0;
			virtual unsigned ibo_size(unsigned) const = 0;

			//buffers
			virtual void buffers_index(unsigned&, unsigned[]);
			virtual void buffers_data(vertices::Vertex*, unsigned**) const = 0;

			//data
			bool m_dot;
			bool m_fill;
			bool m_stroke;

			mat4 m_affine;

			unsigned m_vbo_index;
			unsigned m_ibo_index[3];

			std::vector<Color> m_dot_colors;
			std::vector<Color> m_fill_colors;
			std::vector<Color> m_stroke_colors;

			//friends
			friend class Scene;
			friend class Group;
		};
	}
}