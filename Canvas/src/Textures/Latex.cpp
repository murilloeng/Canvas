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

static const char* tex_source = "\\documentclass{standalone}\n\n\\begin{document}\n\t%s\n\\end{document}";

namespace canvas
{
	namespace textures
	{
		//constructors
		Latex::Latex(const char* source) : m_status(false), m_data(nullptr), m_source(source)
		{
			return;
		}

		//destructor
		Latex::~Latex(void)
		{
			if(m_data) stbi_image_free(m_data);
		}

		//data
		uint32_t Latex::width(void) const
		{
			return m_width;
		}
		uint32_t Latex::height(void) const
		{
			return m_height;
		}
		std::string Latex::source(void) const
		{
			return m_source;
		}
		std::string Latex::source(std::string source)
		{
			m_status = false;
			return m_source = source;
		}

		//load
		void Latex::load(void)
		{
			//data
			int w, h, c;
			if(m_status) return;
			//file
			FILE* file = fopen("temp.tex", "w");
			fprintf(file, tex_source, m_source.c_str());
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
			if(m_data) stbi_image_free(m_data);
			stbi_set_flip_vertically_on_load(true);
			m_data = stbi_load("temp.png", &w, &h, &c, 1);
			for(uint32_t i = 0; i < uint32_t(w * h); i++) m_data[i] = 255 - m_data[i];
			//check
			if(!m_data)
			{
				throw std::runtime_error("STBI image loading of temp.png failed!");
			}
			//setup
			m_width = w;
			m_height = h;
			m_status = true;
			//cleanup
			if(pdf_delete != 0)
			{
				throw std::runtime_error("Latex pdf file deletion failed!");
			}
		}

		//coordinates
		void Latex::coordinates(float* coordinates) const
		{
			coordinates[2] = 0;
			coordinates[0] = float(m_offset) / m_total_width;
			coordinates[3] = float(m_height) / m_total_height;
			coordinates[1] = float(m_offset + m_width) / m_total_width;
		}

		//static
		uint32_t Latex::m_total_width = 0;
		uint32_t Latex::m_total_height = 0;
	}
}