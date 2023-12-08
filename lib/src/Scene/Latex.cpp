//ext
#include "Canvas/ext/inc/stb_image.h"

//canvas
#include "Canvas/lib/inc/Scene/Latex.hpp"

//defines
#ifndef _WIN32
#define pdf_delete system("rm temp.*")
#define pdf_convert system("convert -density 2000 temp.pdf temp.png")
#else
#define pdf_delete system("del temp.*")
#define pdf_convert system("magick convert -density 2000 temp.pdf temp.png")
#endif

static const char* tex_source = "\\documentclass{standalone}\n\n\\begin{document}\n\t%s\n\\end{document}";

namespace canvas
{
	//constructors
	Latex::Latex(const char* source) : m_status(false), m_source(source), m_data(nullptr)
	{
		return;
	}
	
	//destructor
	Latex::~Latex(void)
	{
		if(m_data) stbi_image_free(m_data);
	}

	//data
	unsigned Latex::width(void) const
	{
		return m_width;
	}
	unsigned Latex::height(void) const
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
			fprintf(stderr, "Error: Latex compilation of %s failed!\n", m_source.c_str());
			exit(EXIT_FAILURE);
		}
		if(pdf_convert)
		{
			fprintf(stderr, "Error: Could not convert %s from pdf to png!\n", m_source.c_str());
			exit(EXIT_FAILURE);
		}
		//load
		if(m_data) stbi_image_free(m_data);
		stbi_set_flip_vertically_on_load(true);
		m_data = stbi_load("temp.png", &w, &h, &c, 1);
		for(unsigned i = 0; i < unsigned(w * h); i++) m_data[i] = 255 - m_data[i];
		//check
		if(!m_data)
		{
			fprintf(stderr, "Error: Couldn't load image: temp.png!\n");
			exit(EXIT_FAILURE);
		}
		//setup
		m_width = w;
		m_height = h;
		m_status = true;
		//cleanup
		if(pdf_delete != 0)
		{
			fprintf(stderr, "Error: Couldn't delete pdf file!\n");
			exit(EXIT_FAILURE);
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
	unsigned Latex::m_total_width = 0;
	unsigned Latex::m_total_height = 0;
}