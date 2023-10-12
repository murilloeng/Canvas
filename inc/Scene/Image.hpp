#pragma once

//std
#include <string>

namespace canvas
{
	class Scene;
}

namespace canvas
{
	class Image
	{
	public:
		//constructors
		Image(void);

		//destructor
		~Image(void);

		//load
		void load(void);

		//data
		unsigned m_width;
		unsigned m_height;
		unsigned m_offset;
		std::string m_path;
		unsigned char* m_data;

		//friends
		friend class Scene;
	};
}