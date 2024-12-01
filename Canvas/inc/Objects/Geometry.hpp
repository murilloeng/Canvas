#pragma once

//canvas
#include "Canvas/Canvas/inc/Colors/Color.hpp"
#include "Canvas/Canvas/inc/Objects/Object.hpp"

namespace canvas
{
	class Scene;
}

namespace canvas
{
	namespace objects
	{
		class Geometry : public Object
		{
		public:
			//constructors
			Geometry(void);

			//destructor
			virtual ~Geometry(void);

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

		protected:
			//data
			bool m_dot;
			bool m_fill;
			bool m_stroke;

			Color m_color_dot;
			Color m_color_fill;
			Color m_color_stroke;
		};
	}
}