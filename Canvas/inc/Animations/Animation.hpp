#pragma once

//canvas
#include "Canvas/Canvas/inc/Animations/Easing.hpp"

namespace canvas
{
	class Scene;
}

namespace canvas
{
	namespace animations
	{
		class Animation
		{
		public:
			//constructor
			Animation(void);

			//destructor
			virtual ~Animation(void);

			//data
			bool status(void) const;

			float time_start(float);
			float time_start(void) const;

			float time_durantion(float);
			float time_durantion(void) const;

			Easing& easing(void);
			const Easing& easing(void) const;

			//update
			virtual void setup(void);
			virtual void cleanup(void);
			virtual void animate(float);

		protected:
			//data
			bool m_status;
			Scene* m_scene;
			Easing m_easing;
			float m_time_start;
			float m_time_duration;

			//friends
			friend class canvas::Scene;
		};
	}
}