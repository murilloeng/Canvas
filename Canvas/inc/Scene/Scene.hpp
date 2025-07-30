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

#include "Canvas/Canvas/inc/Textures/Texture.hpp"

#include "Canvas/Canvas/inc/Commands/Command.hpp"

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

		//vaos
		void add_vao(buffers::VAO*);
		buffers::VAO* vao(uint32_t) const;

		//buffers
		void add_vbo(VBO*);
		void add_ibo(IBO*);
		VBO* vbo(uint32_t) const;
		IBO* ibo(uint32_t) const;
		vertices::Text2D* vbo_data_text_2D(void) const;
		vertices::Text3D* vbo_data_text_3D(void) const;
		vertices::Model2D* vbo_data_model_2D(void) const;
		vertices::Model3D* vbo_data_model_3D(void) const;
		vertices::Image2D* vbo_data_image_2D(void) const;
		vertices::Image3D* vbo_data_image_3D(void) const;

		//shaders
		void add_shader(shaders::Shader*);
		shaders::Shader* shader(uint32_t) const;

		//textures
		Texture& texture(uint32_t);
		std::vector<Texture>& textures(void);
		const Texture& texture(uint32_t) const;
		const std::vector<Texture>& textures(void) const;

		//commands
		void add_command(commands::Command*);
		commands::Command* command(uint32_t) const;

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

		//buffers
		void buffers_data(void);

		//data
		Color m_background;
		camera::Camera m_camera;
		lights::Lights m_lights;
		std::vector<VBO*> m_vbos;
		std::vector<IBO*> m_ibos;
		std::vector<Texture> m_textures;
		std::vector<buffers::VAO*> m_vaos;
		std::vector<buffers::Buffer*> m_ubos;
		std::vector<shaders::Shader*> m_shaders;
		std::vector<commands::Command*> m_commands;

		FT_Library m_ft_library;
		std::string m_shaders_dir;
		std::vector<Latex*> m_latex;
		std::vector<Image*> m_images;
		std::vector<fonts::Font*> m_fonts;
		std::vector<objects::Object*> m_objects;

		//friends
		friend class fonts::Font;
		friend class camera::Camera;
		friend class lights::Lights;
		friend class objects::Object;
	};
}