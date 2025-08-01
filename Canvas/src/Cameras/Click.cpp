//std
#include <cmath>

//canvas
#include "Canvas/Canvas/inc/Cameras/Click.hpp"
#include "Canvas/Canvas/inc/Cameras/Camera.hpp"

namespace canvas
{
	namespace cameras
	{
		//constructors
		Click::Click(void) : 
			m_modifiers{0}, m_button{button::none}
		{
			return;
		}
	
		//destructor
		Click::~Click(void)
		{
			return;
		}
	}
}