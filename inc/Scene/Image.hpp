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
		uint32_t width(void) const;
		uint32_t height(void) const;
		std::string path(void) const;
		std::string path(std::string);

		//load
		void load(void);

		//coordinates
		void coordinates(float*) const;

	protected:
		//data
		bool m_status;
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_offset;
		std::string m_path;
		uint8_t* m_data;
		static uint32_t m_total_width;
		static uint32_t m_total_height;

		//friends
		friend class Scene;
	};
}