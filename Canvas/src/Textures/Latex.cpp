//std
#include <stdexcept>

//stb
#include <stb/stb_image.h>

//canvas
#include "Canvas/Canvas/inc/Textures/Latex.hpp"

//defines
#ifdef _WIN32
#define pdf_delete system("del temp.*")
#define pdf_convert system("magick -density 2000 temp.pdf temp.png")
#else
#define pdf_delete system("rm temp.*")
#define pdf_convert system("convert -density 2000 temp.pdf temp.png")
#endif

static const char* format = "\\documentclass{standalone}\n\n\\begin{document}\n\t%s\n\\end{document}";

namespace canvas
{
	namespace textures
	{
		//constructors
		Latex::Latex(void)
		{
			return;
		}

		//destructor
		Latex::~Latex(void)
		{
			return;
		}

		//data
		std::string Latex::source(void) const
		{
			return m_source;
		}
		std::string Latex::source(std::string source)
		{
			return m_source = source;
		}

		const Texture& Latex::texture(void) const
		{
			return m_texture;
		}

		//load
		void Latex::load(void)
		{
			//file
			uint8_t* data;
			int32_t w, h, c;
			FILE* file = fopen("temp.tex", "w");
			fprintf(file, format, m_source.c_str());
			fclose(file);
			//convert
			if(system("pdflatex -halt-on-error temp.tex"))
			{
				throw std::runtime_error("Latex compilation of " + m_source + " failed!");
			}
			if(pdf_convert)
			{
				throw std::runtime_error("Convertion of " + m_source + " from pdf to png failed!");
			}
			//load
			stbi_set_flip_vertically_on_load(true);
			data = stbi_load("temp.png", &w, &h, &c, 1);
			for(uint32_t i = 0; i < uint32_t(w * h); i++) data[i] = 255 - data[i];
			//check
			if(!data)
			{
				throw std::runtime_error("STBI image loading of temp.png failed!");
			}
			//texture
			m_texture.width(w);
			m_texture.height(h);
			m_texture.format(GL_R8);
			//transfer
			m_texture.allocate();
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			m_texture.transfer(0, 0, w, h, GL_RED, GL_UNSIGNED_BYTE, data);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
			m_texture.generate_mipmaps();
			//cleanup
			if(pdf_delete != 0)
			{
				throw std::runtime_error("Latex pdf file deletion failed!");
			}
		}
	}
}