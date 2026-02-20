#pragma once

namespace canvas
{
	class Scene;
}

namespace canvas
{
	namespace objects
	{
		class Object
		{
		public:
			//constructors
			Object(void);

			//destructor
			virtual ~Object(void);

			//data
			Scene* scene(void) const;

		protected:
			//draw
			virtual void setup(void);
			virtual void draw(void) const;

			//update
			virtual void update_on_motion(void) const;

			//data
			Scene* m_scene;

			//friends
			friend class canvas::Scene;
		};
	}
}