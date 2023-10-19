//canvas
#include "inc/Objects/1D/Path.hpp"
#include "inc/Objects/1D/Curve.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Path::Path(void)
		{
			return;
		}

		//destructor
		Path::~Path(void)
		{
			return;
		}

		//arrows
		void Path::add_curve(Curve* curve)
		{
			m_objects.push_back(curve);
		}
		void Path::remove_curve(unsigned index)
		{
			unsigned counter = 0;
			for(unsigned i = 0; i < m_objects.size(); i++)
			{
				if(dynamic_cast<const Curve*>(m_objects[i]))
				{
					if(counter == index)
					{
						delete m_objects[i];
						m_objects.erase(m_objects.begin() + i);
					}
					counter++;
				}
			}
		}
		unsigned Path::curves(void) const
		{
			unsigned counter = 0;
			for(const Object* object : m_objects)
			{
				if(dynamic_cast<const Curve*>(object))
				{
					counter++;
				}
			}
			return counter;
		}
		Curve* Path::curve(unsigned index) const
		{
			unsigned counter = 0;
			for(Object* object : m_objects)
			{
				if(dynamic_cast<Curve*>(object))
				{
					if(counter != index)
					{
						counter++;
					}
					else
					{
						return (Curve*) object;
					}
				}
			}
			return nullptr;
		}
	}
}