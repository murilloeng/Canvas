#pragma once

//canvas
#include "Canvas/Canvas/inc/Math/quat.hpp"

#include "Canvas/Canvas/inc/Animations/Camera/Camera.hpp"

namespace canvas
{
	namespace animations
	{
		namespace camera
		{
			class Rotation : public Camera
			{
			public:
				//constructor
				Rotation(cameras::Camera*, quat);

				//destructor
				~Rotation(void);

				//update
				void setup(void) override;
				void cleanup(void) override;
				void animate(float) override;

			private:
				//data
				quat m_q0;
				quat m_qr;
				quat m_qt;
			};
		}
	}
}