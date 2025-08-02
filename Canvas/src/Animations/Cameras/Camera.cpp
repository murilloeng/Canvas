//canvas
#include "Canvas/Canvas/inc/Animations/Cameras/Camera.hpp"

namespace canvas
{
	namespace animations
	{
		namespace cameras
		{
			//constructor
			Camera::Camera(canvas::cameras::Camera* camera) : m_camera{camera}
			{
				return;
			}

			//destructor
			Camera::~Camera(void)
			{
				return;
			}
		}
	}
}