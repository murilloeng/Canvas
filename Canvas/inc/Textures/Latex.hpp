#pragma once

//std
#include <string>

//Canvas
#include "Canvas/Canvas/inc/Textures/Texture.hpp"

namespace canvas
{
	namespace textures
	{
		class Latex
		{
		public:
			//constructors
			Latex(void);

			//destructor
			~Latex(void);

			//data
			std::string source(void) const;
			std::string source(std::string);

			const Texture& texture(void) const;

			//load
			void load(void);

		protected:
			//data
			Texture m_texture;
			std::string m_source;
		};
	}
}