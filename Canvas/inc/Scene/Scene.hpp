#pragma once

//std
#include <string>
#include <vector>
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Buffers/VAO.hpp"
#include "Canvas/Canvas/inc/Buffers/VBO.hpp"
#include "Canvas/Canvas/inc/Buffers/IBO.hpp"
#include "Canvas/Canvas/inc/Buffers/Buffer.hpp"

#include "Canvas/Canvas/inc/Colors/Color.hpp"

#include "Canvas/Canvas/inc/Lights/Lights.hpp"

#include "Canvas/Canvas/inc/Cameras/Camera.hpp"

#include "Canvas/Canvas/inc/Shaders/Shader.hpp"

#include "Canvas/Canvas/inc/Commands/Command.hpp"

#include "Canvas/Canvas/inc/Textures/Latex.hpp"
#include "Canvas/Canvas/inc/Textures/Image.hpp"
#include "Canvas/Canvas/inc/Textures/Texture.hpp"

//ext
#include "external/cpp/inc/freetype/freetype.h"

namespace canvas
{
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

		//background
		Color background(Color);
		Color background(void) const;

		lights::Lights& light(void);
		const lights::Lights& light(void) const;

		cameras::Camera& camera(void);
		const cameras::Camera& camera(void) const;

		void clear_objects(bool);
		void add_object(objects::Object*);
		objects::Object* object(uint32_t) const;
		const std::vector<objects::Object*>& objects(void) const;

		//vaos
		void add_vao(buffers::VAO*);
		buffers::VAO* vao(uint32_t) const;

		//vbos
		void add_vbo(buffers::VBO*);
		buffers::VBO* vbo(uint32_t) const;
		
		//ibos
		void add_ibo(buffers::IBO*);
		buffers::IBO* ibo(uint32_t) const;

		//ubos
		void add_ubo(buffers::Buffer*);
		buffers::Buffer* ubo(uint32_t) const;

		//shaders
		void add_shader(shaders::Shader*);
		shaders::Shader* shader(uint32_t) const;
		
		//commands
		void add_command(commands::Command*);
		commands::Command* command(uint32_t) const;

		//textures
		void add_texture(textures::Texture*);
		textures::Texture* texture(uint32_t) const;

		//fonts
		void add_font(const char*);
		fonts::Font* font(uint32_t) const;

		//latex
		uint32_t add_latex(const char*);
		textures::Latex* latex(uint32_t) const;

		//images
		void add_image(const char*);
		textures::Image* image(uint32_t) const;

		//update
		void draw(void);
		void update(bool);
		void update_on_motion(void);

	protected:
		//setup
		void setup_vaos(void);
		void setup_vbos(void);
		void setup_ibos(void);
		void setup_ubos(void);
		void setup_data(void);
		void setup_fonts(void);
		void setup_latex(void);
		void setup_OpenGL(void);
		void setup_images(void);
		void setup_objects(void);
		void setup_shaders(void);
		void setup_freetype(void);
		void setup_commands(void);
		void setup_textures(void);

		//setup vaos
		void setup_vao_text_2D(void);
		void setup_vao_text_3D(void);
		void setup_vao_latex_2D(void);
		void setup_vao_latex_3D(void);
		void setup_vao_image_2D(void);
		void setup_vao_image_3D(void);
		void setup_vao_model_2D_lines(void);
		void setup_vao_model_3D_lines(void);
		void setup_vao_model_2D_points(void);
		void setup_vao_model_3D_points(void);
		void setup_vao_model_2D_triangles(void);
		void setup_vao_model_3D_triangles(void);

		//setup shaders
		void setup_shader_light(void);
		void setup_shader_text_2D(void);
		void setup_shader_text_3D(void);
		void setup_shader_model_2D(void);
		void setup_shader_model_3D(void);
		void setup_shader_image_2D(void);
		void setup_shader_image_3D(void);
		void setup_shader_latex_2D(void);
		void setup_shader_latex_3D(void);

		//buffers
		void buffers_data(void);

		//data
		Color m_background;
		std::vector<buffers::VAO*> m_vaos;
		std::vector<buffers::VBO*> m_vbos;
		std::vector<buffers::IBO*> m_ibos;
		std::vector<buffers::Buffer*> m_ubos;
		std::vector<shaders::Shader*> m_shaders;
		std::vector<commands::Command*> m_commands;
		std::vector<textures::Texture*> m_textures;

		FT_Library m_ft_library;
		lights::Lights m_lights;
		cameras::Camera m_camera;
		std::string m_shaders_dir;
		std::vector<fonts::Font*> m_fonts;
		std::vector<textures::Latex*> m_latex;
		std::vector<textures::Image*> m_images;
		std::vector<objects::Object*> m_objects;

		//friends
		friend class fonts::Font;
		friend class cameras::Camera;
		friend class lights::Lights;
		friend class objects::Object;
	};
}