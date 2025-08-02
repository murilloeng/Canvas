#pragma once

//canvas
#include "Canvas/Canvas/inc/Cameras/Camera.hpp"

#include "Canvas/Canvas/inc/Animations/Animation.hpp"

namespace canvas
{
	namespace animations
	{
		namespace camera
		{
			class Camera : public Animation
			{
			public:
				//constructor
				Camera(cameras::Camera*);

				//destructor
				~Camera(void);

			protected:
				//data
				cameras::Camera* m_camera;
			};
		}
	}
}