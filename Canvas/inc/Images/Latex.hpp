#pragma once

//std
#include <string>
#include <cstdint>

namespace canvas
{
	class Scene;
}

namespace canvas
{
	class Latex
	{
	public:
		//constructors
		Latex(const char*);

		//destructor
		~Latex(void);

		//data
		uint32_t width(void) const;
		uint32_t height(void) const;
		std::string source(void) const;
		std::string source(std::string);

		//load
		void load(void);

		//coordinates
		void coordinates(float*) const;

	protected:
		//data
		bool m_status;
		uint8_t* m_data;
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_offset;
		std::string m_source;
		static uint32_t m_total_width;
		static uint32_t m_total_height;

		//friends
		friend class Scene;
	};
}