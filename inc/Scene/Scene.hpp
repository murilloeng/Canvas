#pragma once

//std
#include <string>
#include <vector>

//canvas
#include "inc/Scene/Camera.hpp"
#include "inc/Colors/Color.hpp"

namespace canvas
{
	class Font;
	class Image;
	namespace objects
	{
		class Object;
	}
	namespace vertices
	{
		class Vertex;
	}
}

namespace canvas
{
	class Scene
	{
	public:
		//constructors
		Scene(void);

		//destructor
		~Scene(void);

		//data
		Color background(Color);
		Color background(void) const;

		Camera& camera(void);
		const Camera& camera(void) const;

		Font* font(unsigned) const;
		void add_font(const char*, unsigned);
		const std::vector<Font*>& fonts(void) const;

		void add_image(const char*);
		Image* image(unsigned) const;
		const std::vector<Image*>& images(void) const;

		void clear_objects(void);
		void add_object(objects::Object*);
		objects::Object* object(unsigned) const;
		const std::vector<objects::Object*>& objects(void) const;

		//update
		void draw(void);
		void bound(void);
		void update(void);

	private:
		//draw
		void draw_text(void);
		void draw_model(void);
		void draw_image(void);

		//setup
		void setup(void);
		void setup_gl(void);
		void setup_vbo(void);
		void setup_ibo(void);
		void setup_images(void);
		void setup_objects(void);
		void setup_buffers(void);
		void setup_shaders(void);
		void setup_textures(void);

		//buffers
		void buffers_data(void);
		void buffers_transfer(void);

		//misc
		static bool load_file(std::string&, const char*);
		static void setup_shader(unsigned&, unsigned, unsigned, const char*);
		static void setup_program(unsigned&, unsigned&, unsigned&, const char*, const char*);

		//data
		Camera m_camera;

		unsigned m_vao_id[3];
		unsigned m_vbo_id[3];
		unsigned m_ibo_id[5];
		unsigned m_vbo_size[3];
		unsigned m_ibo_size[5];
		unsigned* m_ibo_data[5];
		unsigned m_texture_id[2];
		vertices::Vertex* m_vbo_data[3];

		Color m_background;
		unsigned m_program_id[3];
		unsigned m_shaders_vertex_id[3];
		unsigned m_shaders_fragment_id[3];

		std::vector<Font*> m_fonts;
		std::vector<Image*> m_images;
		std::vector<objects::Object*> m_objects;
	};
}