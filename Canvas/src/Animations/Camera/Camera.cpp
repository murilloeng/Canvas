//canvas
#include "Canvas/Canvas/inc/Animations/Camera/Camera.hpp"

namespace canvas
{
	namespace animations
	{
		namespace camera
		{
			//constructor
			Camera::Camera(cameras::Camera* camera) : m_camera{camera}
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