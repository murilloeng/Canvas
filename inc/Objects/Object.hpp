#pragma once

namespace canvas
{
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

			//name
			const char* name(void) const;
			static const char* name(objects::type);

			//type
			virtual objects::type type(void) const = 0;

			//buffers
			virtual unsigned vbo_size(void) const = 0;
			virtual unsigned ibo_size(unsigned) const = 0;

			//draw
			virtual void draw(vertices::Vertex*, unsigned**) const = 0;

			//data
			unsigned m_vbo_index;
			unsigned m_ibo_index[3];
		};
	}
}