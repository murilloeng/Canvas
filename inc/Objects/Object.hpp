#pragma once

//canvas
#include "inc/Math/mat4.hpp"

namespace canvas
{
	class Model;
	namespace vertices
	{
		class Vertex;
	}
	namespace objects
	{
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
			bool draw(bool);
			bool draw(void) const;

			bool fill(bool);
			bool fill(void) const;

			//name
			const char* name(void) const;
			static const char* name(objects::type);

			//type
			virtual objects::type type(void) const = 0;

			//affine
			mat4 affine(mat4);
			mat4 affine(void) const;
			mat4 apply_affine(mat4, bool = true);

		protected:
			//buffers
			virtual unsigned vbo_size(void) const = 0;
			virtual unsigned ibo_size(unsigned) const = 0;

			//draw
			virtual void buffers_data(vertices::Vertex*, unsigned**) const = 0;

			//data
			bool m_draw;
			bool m_fill;
			mat4 m_affine;
			unsigned m_vbo_index;
			unsigned m_ibo_index[3];

			//friends
			friend class Model;
		};
	}
}