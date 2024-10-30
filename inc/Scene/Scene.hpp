#pragma once

//std
#include <string>
#include <vector>
#include <cstdint>

//canvas
#include "Canvas/inc/GPU/IBO.hpp"
#include "Canvas/inc/GPU/Program.hpp"
#include "Canvas/inc/Light/Lights.hpp"
#include "Canvas/inc/Colors/Color.hpp"
#include "Canvas/inc/Scene/Camera.hpp"
#include "Canvas/inc/Scene/Command.hpp"

//ext
#include "external/cpp/inc/freetype/freetype.h"

namespace canvas
{
	class Font;
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
		Font* font(uint32_t) const;
		const std::vector<Font*>& fonts(void) const;

		void clear_images(void);
		void add_image(const char*);
		Image* image(uint32_t) const;
		const std::vector<Image*>& images(void) const;

		void clear_latex(void);
		void add_latex(const char*);
		Latex* latex(uint32_t) const;
		const std::vector<Latex*>& latex(void) const;

		void clear_objects(bool);
		void add_object(objects::Object*);
		objects::Object* object(uint32_t) const;
		const std::vector<objects::Object*>& objects(void) const;

		//buffers
		IBO& ibo(uint32_t);
		uint32_t vbo_size(uint32_t) const;
		vertices::Text2D* vbo_data_text_2D(void) const;
		vertices::Text3D* vbo_data_text_3D(void) const;
		vertices::Model2D* vbo_data_model_2D(void) const;
		vertices::Model3D* vbo_data_model_3D(void) const;
		vertices::Image2D* vbo_data_image_2D(void) const;
		vertices::Image3D* vbo_data_image_3D(void) const;

		//update
		void draw(void);
		void update(bool);

		//buffers
		void vbo_transfer(uint32_t) const;

	protected:
		//setup
		void setup_gl(void);
		void setup_vbo(void);
		void setup_ibo(void);
		void setup_fonts(void);
		void setup_latex(void);
		void setup_images(void);
		void setup_objects(void);
		void setup_buffers(void);
		void setup_shaders(void);
		void setup_textures(void);
		void setup_freetype(void);
		void setup_commands(void);
		void setup_buffers_2D(void);
		void setup_buffers_3D(void);

		//buffers
		void buffers_data(void);
		void buffers_transfer(void);

		//data
		IBO m_ibo[12];
		lights::Lights m_lights;
		camera::Camera m_camera;

		uint32_t m_vao_id[6];
		uint32_t m_vbo_id[6];
		uint32_t m_vbo_size[6];
		uint32_t m_texture_id[3];
		vertices::Vertex* m_vbo_data[6];

		Color m_background;
		Program m_programs[7];

		FT_Library m_ft_library;
		std::string m_shaders_dir;
		std::vector<Font*> m_fonts;
		std::vector<Latex*> m_latex;
		std::vector<Image*> m_images;
		std::vector<Command> m_commands;
		std::vector<objects::Object*> m_objects;

		//friends
		friend class Font;
		friend class camera::Camera;
		friend class objects::Object;
	};
}