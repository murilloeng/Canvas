#pragma once

namespace canvas
{
	class Scene;
}

namespace canvas
{
	class Texture
	{
	protected:
		//constructors
		Texture(void);

		//destructor
		~Texture(void);

		//friends
		friend class Scene;
	};
}