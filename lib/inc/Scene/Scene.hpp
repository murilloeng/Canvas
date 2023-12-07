#pragma once

//std
#include <string>
#include <vector>

//canvas
#include "inc/GPU/Program.hpp"
#include "inc/Scene/Light.hpp"
#include "inc/Scene/Camera.hpp"
#include "inc/Colors/Color.hpp"

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

		float frame_rate(float);
		float frame_rate(void) const;

		Light& light(void);
		const Light& light(void) const;

		Camera& camera(void);
		const Camera& camera(void) const;

		void clear_fonts(void);
		void add_font(const char*);
		Font* font(unsigned) const;
		const std::vector<Font*>& fonts(void) const;

		void clear_images(void);
		void add_image(const char*);
		Image* image(unsigned) const;
		const std::vector<Image*>& images(void) const;

		void clear_latex(void);
		void add_latex(const char*);
		Latex* latex(unsigned) const;
		const std::vector<Latex*>& latex(void) const;

		void clear_objects(bool);
		void add_object(objects::Object*);
		objects::Object* object(unsigned) const;
		const std::vector<objects::Object*>& objects(void) const;

		//buffers
		unsigned vbo_size(unsigned) const;
		unsigned ibo_size(unsigned) const;
		vertices::Vertex* vertex(unsigned, unsigned) const;

		//update
		void draw(void);
		void update(bool);

	protected:
		//draw
		void draw_text(void);
		void draw_model(void);
		void draw_image(void);
		void draw_equation(void);

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

		//buffers
		void buffers_data(void);
		void buffers_transfer(void);

		//data
		Light m_light;
		Camera m_camera;

		float m_frame_rate;
		unsigned m_vao_id[3];
		unsigned m_vbo_id[3];
		unsigned m_ibo_id[6];
		unsigned m_vbo_size[3];
		unsigned m_ibo_size[6];
		unsigned* m_ibo_data[6];
		unsigned m_texture_id[6];
		vertices::Vertex* m_vbo_data[3];

		Color m_background;
		Program m_programs[4];

		std::string m_shaders_dir;
		std::vector<Font*> m_fonts;
		std::vector<Latex*> m_latex;
		std::vector<Image*> m_images;
		std::vector<objects::Object*> m_objects;

		//friends
		friend class Camera;
	};
}