#pragma once

//std
#include <string>
#include <cstdint>

//Canvas
#include "Canvas/Canvas/inc/Textures/Texture.hpp"

namespace canvas
{
	namespace textures
	{
		class Image
		{
		public:
			//constructors
			Image(void);

			//destructor
			~Image(void);

			//data
			std::string path(void) const;
			std::string path(std::string);

			const Texture& texture(void) const;

			//load
			void load(void);

		protected:
			//data
			Texture m_texture;
			std::string m_path;
		};
	}
}