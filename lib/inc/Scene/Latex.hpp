#pragma once

//std
#include <string>

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
		unsigned width(void) const;
		unsigned height(void) const;
		std::string source(void) const;
		std::string source(std::string);

		//load
		void load(void);

		//coordinates
		void coordinates(float*) const;

	private:
		//data
		bool m_status;
		unsigned m_width;
		unsigned m_height;
		unsigned m_offset;
		std::string m_source;
		unsigned char* m_data;
		static unsigned m_total_width;
		static unsigned m_total_height;

		//friends
		friend class Scene;
	};
}