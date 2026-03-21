#pragma once

//canvas
#include "Canvas/inc/Cameras/Camera.hpp"

#include "Canvas/inc/Animations/Animation.hpp"

namespace canvas
{
	namespace animations
	{
		namespace cameras
		{
			class Camera : public Animation
			{
			public:
				//constructor
				Camera(canvas::cameras::Camera*);

				//destructor
				~Camera(void);

			protected:
				//data
				canvas::cameras::Camera* m_camera;
			};
		}
	}
}