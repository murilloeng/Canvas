//Canvas
#include "Canvas/Canvas/inc/Fonts/Contour.hpp"

namespace canvas
{
	namespace fonts
	{
		//constructor
		Contour::Contour(void)
		{
			return;
		}

		//destructor
		Contour::~Contour(void)
		{
			for(const Item* item : m_items) delete item;
		}

		//print
		void Contour::print(void) const
		{
			for(const Item* item : m_items) item->print();
		}
	}
}