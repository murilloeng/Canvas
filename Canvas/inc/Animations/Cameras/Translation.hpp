#pragma once

//canvas
#include "Canvas/Canvas/inc/Math/vec3.hpp"

#include "Canvas/Canvas/inc/Animations/Cameras/Camera.hpp"

namespace canvas
{
	namespace animations
	{
		namespace cameras
		{
			class Translation : public Camera
			{
			public:
				//constructor
				Translation(canvas::cameras::Camera*, vec3, float);

				//destructor
				~Translation(void);

				//update
				void setup(void) override;
				void cleanup(void) override;
				void animate(float) override;

			private:
				//data
				vec3 m_x0, m_xt;
				float m_d0, m_dt;
			};
		}
	}
}