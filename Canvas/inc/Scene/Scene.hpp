#pragma once

//std
#include <string>
#include <vector>
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/GPU/VBO.hpp"
#include "Canvas/Canvas/inc/GPU/IBO.hpp"
#include "Canvas/Canvas/inc/GPU/Texture.hpp"
#include "Canvas/Canvas/inc/GPU/Program.hpp"
#include "Canvas/Canvas/inc/Light/Lights.hpp"
#include "Canvas/Canvas/inc/Colors/Color.hpp"
#include "Canvas/Canvas/inc/Scene/Camera.hpp"
#include "Canvas/Canvas/inc/Scene/Command.hpp"

//ext
#include "external/cpp/inc/freetype/freetype.h"

namespace canvas
{
	class Image;
	class Latex;
	namespace objects
	{
		class Object;
	}
	namespace vertices
	{
		class Vertex;
		class Text2D;
		class Text3D;
		class Model2D;
		class Model3D;
		class Image2D;
		class Image3D;
	}
	namespace fonts
	{
		class Font;
	}
}

namespace canvas
{
	class Scene
	{
	public:
		//constructors
		Scene(std::string);

		//destructor
		~Scene(void);

		//data
		Color background(Color);
		Color background(void) const;

		lights::Lights& light(void);
		const lights::Lights& light(void) const;

		camera::Camera& camera(void);
		const camera::Camera& camera(void) const;

		std::vector<Command>& commands(void);
		const std::vector<Command>& commands(void) const;

		void clear_fonts(void);
		void add_font(const char*);
		fonts::Font* font(uint32_t) const;
		const std::vector<fonts::Font*>& fonts(void) const;

		void clear_images(void);
		void add_image(const char*);
		Image* image(uint32_t) const;
		const std::vector<Image*>& images(void) const;

		void clear_latex(void);
		Latex* latex(uint32_t) const;
		uint32_t add_latex(const char*);
		const std::vector<Latex*>& latex(void) const;

		void clear_objects(bool);
		void add_object(objects::Object*);
		objects::Object* object(uint32_t) const;
		const std::vector<objects::Object*>& objects(void) const;

		//buffers
		VBO* vbo(uint32_t);
		IBO* ibo(uint32_t);
		void add_vbo(VBO*);
		void add_ibo(IBO*);
		std::vector<VBO*>& vbos(void);
		std::vector<IBO*>& ibos(void);
		const VBO* vbo(uint32_t) const;
		const IBO* ibo(uint32_t) const;
		const std::vector<VBO*>& vbos(void) const;
		const std::vector<IBO*>& ibos(void) const;
		vertices::Text2D* vbo_data_text_2D(void) const;
		vertices::Text3D* vbo_data_text_3D(void) const;
		vertices::Model2D* vbo_data_model_2D(void) const;
		vertices::Model3D* vbo_data_model_3D(void) const;
		vertices::Image2D* vbo_data_image_2D(void) const;
		vertices::Image3D* vbo_data_image_3D(void) const;

		//programs
		Texture& texture(uint32_t);
		std::vector<Texture>& textures(void);
		const Texture& texture(uint32_t) const;
		const std::vector<Texture>& textures(void) const;

		//programs
		Program* program(uint32_t);
		std::vector<Program*>& programs(void);
		const Program* program(uint32_t) const;
		const std::vector<Program*>& programs(void) const;

		//update
		void draw(void);
		void update(bool);
		void update_on_motion(void);

	protected:
		//setup
		void setup_gl(void);
		void setup_data(void);
		void setup_fonts(void);
		void setup_latex(void);
		void setup_images(void);
		void setup_objects(void);
		void setup_buffers(void);
		void setup_shaders(void);
		void setup_freetype(void);
		void setup_commands(void);

		//buffers
		void buffers_data(void);

		//data
		Color m_background;
		camera::Camera m_camera;
		lights::Lights m_lights;
		std::vector<VBO*> m_vbos;
		std::vector<IBO*> m_ibos;
		std::vector<Texture> m_textures;
		std::vector<Program*> m_programs;

		FT_Library m_ft_library;
		std::string m_shaders_dir;
		std::vector<Latex*> m_latex;
		std::vector<Image*> m_images;
		std::vector<Command> m_commands;
		std::vector<fonts::Font*> m_fonts;
		std::vector<objects::Object*> m_objects;

		//friends
		friend class fonts::Font;
		friend class camera::Camera;
		friend class lights::Lights;
		friend class objects::Object;
	};
}