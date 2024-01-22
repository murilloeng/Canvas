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
		Image(const char*);

		//destructor
		~Image(void);

		//data
		unsigned width(void) const;
		unsigned height(void) const;
		std::string path(void) const;
		std::string path(std::string);

		//load
		void load(void);

		//coordinates
		void coordinates(float*) const;

	protected:
		//data
		bool m_status;
		unsigned m_width;
		unsigned m_height;
		unsigned m_offset;
		std::string m_path;
		unsigned char* m_data;
		static unsigned m_total_width;
		static unsigned m_total_height;

		//friends
		friend class Scene;
	};
}