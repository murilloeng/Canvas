#pragma once

namespace canvas
{
	namespace vertices
	{
		class Vertex;
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