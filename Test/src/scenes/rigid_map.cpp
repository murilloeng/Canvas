//std
#include <cmath>
#include <chrono>

//canvas
#include "Canvas/Canvas/inc/GPU/VBO.hpp"
#include "Canvas/Canvas/inc/GPU/IBO.hpp"
#include "Canvas/Canvas/inc/GPU/Shader.hpp"
#include "Canvas/Canvas/inc/GPU/Program.hpp"
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Scene/Latex.hpp"
#include "Canvas/Canvas/inc/Scene/Command.hpp"
#include "Canvas/Canvas/inc/Objects/Object.hpp"
#include "Canvas/Canvas/inc/Objects/1D/Line.hpp"
#include "Canvas/Canvas/inc/Vertices/Text2D.hpp"
#include "Canvas/Canvas/inc/Vertices/Model2D.hpp"

//test
#include "Canvas/Test/inc/Engine.hpp"
#include "Canvas/Test/inc/examples.hpp"

//class
class Rigid_Map : public canvas::objects::Object
{
public:
	//constructor
	Rigid_Map(void) : m_tics(11), m_labels{"$ \\gamma_1 $", "$ \\gamma_2 $"} { return; }

	//destructor
	~Rigid_Map(void) { return; }

	//buffers
	void buffers_size(void) override
	{
		m_vbo_size[ 6] = 4;
		m_ibo_size[12] = 6;
		m_vbo_size[ 5] = 8;
		m_ibo_size[11] = 12;
		m_vbo_size[ 3] = 4 + 8 * (m_tics - 2);
		m_ibo_size[ 7] = 8 + 8 * (m_tics - 2);
	}
	void buffers_data_user(void) const
	{
		//data
		uint32_t* ibo_ptr = ibo_data(12);
		canvas::vertices::Model2D* vbo_ptr = (canvas::vertices::Model2D*) m_scene->vbo(6)->data() + m_vbo_index[6];
		//vbo data
		vbo_ptr[0].m_position = {-0.88f, -0.88f};
		vbo_ptr[1].m_position = {+0.88f, -0.88f};
		vbo_ptr[2].m_position = {+0.88f, +0.88f};
		vbo_ptr[3].m_position = {-0.88f, +0.88f};
		//ibo data
		ibo_ptr[3 * 0 + 0] = m_vbo_index[6] + 0;
		ibo_ptr[3 * 0 + 1] = m_vbo_index[6] + 1;
		ibo_ptr[3 * 0 + 2] = m_vbo_index[6] + 2;
		ibo_ptr[3 * 1 + 0] = m_vbo_index[6] + 0;
		ibo_ptr[3 * 1 + 1] = m_vbo_index[6] + 2;
		ibo_ptr[3 * 1 + 2] = m_vbo_index[6] + 3;
	}
	void buffers_data_latex(void) const
	{
		//data
		float lc1[4], lc2[4];
		uint32_t* ibo_ptr = ibo_data(11);
		const uint32_t w1 = m_scene->latex(0)->width();
		const uint32_t h1 = m_scene->latex(0)->height();
		canvas::vertices::Text2D* vbo_ptr = vbo_data_text_2D();
		//latex
		m_scene->latex(0)->coordinates(lc1);
		m_scene->latex(1)->coordinates(lc2);
		//vbo data
		vbo_ptr[0].m_color = {1, 1, 1, 1};
		vbo_ptr[1].m_color = {1, 1, 1, 1};
		vbo_ptr[2].m_color = {1, 1, 1, 1};
		vbo_ptr[3].m_color = {1, 1, 1, 1};
		vbo_ptr[4].m_color = {1, 1, 1, 1};
		vbo_ptr[5].m_color = {1, 1, 1, 1};
		vbo_ptr[6].m_color = {1, 1, 1, 1};
		vbo_ptr[7].m_color = {1, 1, 1, 1};
		vbo_ptr[0].m_position = {-0.06f * w1 / h1, -1.00f};
		vbo_ptr[1].m_position = {+0.06f * w1 / h1, -1.00f};
		vbo_ptr[2].m_position = {+0.06f * w1 / h1, -0.88f};
		vbo_ptr[3].m_position = {-0.06f * w1 / h1, -0.88f};
		vbo_ptr[4].m_position = {-0.06f * w1 / h1, -1.00f};
		vbo_ptr[5].m_position = {+0.06f * w1 / h1, -1.00f};
		vbo_ptr[6].m_position = {+0.06f * w1 / h1, -0.88f};
		vbo_ptr[7].m_position = {-0.06f * w1 / h1, -0.88f};
		vbo_ptr[0].m_texture_coordinates = {lc1[0], lc1[2]};
		vbo_ptr[1].m_texture_coordinates = {lc1[1], lc1[2]};
		vbo_ptr[2].m_texture_coordinates = {lc1[1], lc1[3]};
		vbo_ptr[3].m_texture_coordinates = {lc1[0], lc1[3]};
		vbo_ptr[4].m_texture_coordinates = {lc2[0], lc2[2]};
		vbo_ptr[5].m_texture_coordinates = {lc2[1], lc2[2]};
		vbo_ptr[6].m_texture_coordinates = {lc2[1], lc2[3]};
		vbo_ptr[7].m_texture_coordinates = {lc2[0], lc2[3]};
		//ibo data
		ibo_ptr[3 * 0 + 0] = m_vbo_index[5] + 0;
		ibo_ptr[3 * 0 + 1] = m_vbo_index[5] + 1;
		ibo_ptr[3 * 0 + 2] = m_vbo_index[5] + 2;
		ibo_ptr[3 * 1 + 0] = m_vbo_index[5] + 0;
		ibo_ptr[3 * 1 + 1] = m_vbo_index[5] + 2;
		ibo_ptr[3 * 1 + 2] = m_vbo_index[5] + 3;
		ibo_ptr[3 * 2 + 0] = m_vbo_index[5] + 4;
		ibo_ptr[3 * 2 + 1] = m_vbo_index[5] + 5;
		ibo_ptr[3 * 2 + 2] = m_vbo_index[5] + 6;
		ibo_ptr[3 * 3 + 0] = m_vbo_index[5] + 4;
		ibo_ptr[3 * 3 + 1] = m_vbo_index[5] + 6;
		ibo_ptr[3 * 3 + 2] = m_vbo_index[5] + 7;
	}
	void buffers_data_model_2D(void) const
	{
		//data
		uint32_t* ibo_ptr = ibo_data(7);
		canvas::vertices::Model2D* vbo_ptr = vbo_data_model_2D();
		//vbo data
		vbo_ptr[0].m_position = {-0.88f, -0.88f};
		vbo_ptr[1].m_position = {+0.88f, -0.88f};
		vbo_ptr[2].m_position = {+0.88f, +0.88f};
		vbo_ptr[3].m_position = {-0.88f, +0.88f};
		for(uint32_t i = 0; i < 4 + 8 * uint32_t(m_tics - 2); i++)
		{
			vbo_ptr[i].m_color = {1, 1, 1, 1};
		}
		for(uint32_t i = 0; i < uint32_t(m_tics - 2); i++)
		{
			vbo_ptr[4 + 0 * 2 * (m_tics - 2) + 2 * i + 0].m_position = {-0.88f + 2 * 0.88f * (i + 1) / (m_tics - 1), -0.88f};
			vbo_ptr[4 + 0 * 2 * (m_tics - 2) + 2 * i + 1].m_position = {-0.88f + 2 * 0.88f * (i + 1) / (m_tics - 1), -0.83f};
			vbo_ptr[4 + 1 * 2 * (m_tics - 2) + 2 * i + 0].m_position = {+0.88f, -0.88f + 2 * 0.88f * (i + 1) / (m_tics - 1)};
			vbo_ptr[4 + 1 * 2 * (m_tics - 2) + 2 * i + 1].m_position = {+0.83f, -0.88f + 2 * 0.88f * (i + 1) / (m_tics - 1)};
			vbo_ptr[4 + 2 * 2 * (m_tics - 2) + 2 * i + 0].m_position = {-0.88f + 2 * 0.88f * (i + 1) / (m_tics - 1), +0.88f};
			vbo_ptr[4 + 2 * 2 * (m_tics - 2) + 2 * i + 1].m_position = {-0.88f + 2 * 0.88f * (i + 1) / (m_tics - 1), +0.83f};
			vbo_ptr[4 + 3 * 2 * (m_tics - 2) + 2 * i + 0].m_position = {-0.88f, -0.88f + 2 * 0.88f * (i + 1) / (m_tics - 1)};
			vbo_ptr[4 + 3 * 2 * (m_tics - 2) + 2 * i + 1].m_position = {-0.83f, -0.88f + 2 * 0.88f * (i + 1) / (m_tics - 1)};
		}
		//ibo data 2D
		ibo_ptr[2 * 0 + 0] = m_vbo_index[3] + 0;
		ibo_ptr[2 * 0 + 1] = m_vbo_index[3] + 1;
		ibo_ptr[2 * 1 + 0] = m_vbo_index[3] + 1;
		ibo_ptr[2 * 1 + 1] = m_vbo_index[3] + 2;
		ibo_ptr[2 * 2 + 0] = m_vbo_index[3] + 2;
		ibo_ptr[2 * 2 + 1] = m_vbo_index[3] + 3;
		ibo_ptr[2 * 3 + 0] = m_vbo_index[3] + 3;
		ibo_ptr[2 * 3 + 1] = m_vbo_index[3] + 0;
		for(uint32_t i = 0; i < uint32_t(m_tics - 2); i++)
		{
			ibo_ptr[8 + 0 * 2 * (m_tics - 2) + 2 * i + 0] = m_vbo_index[3] + 4 + 0 * 2 * (m_tics - 2) + 2 * i + 0;
			ibo_ptr[8 + 0 * 2 * (m_tics - 2) + 2 * i + 1] = m_vbo_index[3] + 4 + 0 * 2 * (m_tics - 2) + 2 * i + 1;
			ibo_ptr[8 + 1 * 2 * (m_tics - 2) + 2 * i + 0] = m_vbo_index[3] + 4 + 1 * 2 * (m_tics - 2) + 2 * i + 0;
			ibo_ptr[8 + 1 * 2 * (m_tics - 2) + 2 * i + 1] = m_vbo_index[3] + 4 + 1 * 2 * (m_tics - 2) + 2 * i + 1;
			ibo_ptr[8 + 2 * 2 * (m_tics - 2) + 2 * i + 0] = m_vbo_index[3] + 4 + 2 * 2 * (m_tics - 2) + 2 * i + 0;
			ibo_ptr[8 + 2 * 2 * (m_tics - 2) + 2 * i + 1] = m_vbo_index[3] + 4 + 2 * 2 * (m_tics - 2) + 2 * i + 1;
			ibo_ptr[8 + 3 * 2 * (m_tics - 2) + 2 * i + 0] = m_vbo_index[3] + 4 + 3 * 2 * (m_tics - 2) + 2 * i + 0;
			ibo_ptr[8 + 3 * 2 * (m_tics - 2) + 2 * i + 1] = m_vbo_index[3] + 4 + 3 * 2 * (m_tics - 2) + 2 * i + 1;
		}
	}
	void buffers_data(void) const override
	{
		buffers_data_user();
		buffers_data_latex();
		buffers_data_model_2D();
	}

	//data
	uint8_t m_tics;
	char m_labels[2][200];
};

//static data
static canvas::VBO* vbo;
static canvas::IBO* ibo;
static Rigid_Map rigid_map;
static canvas::Scene* scene;
static canvas::Program program;
static std::chrono::high_resolution_clock::time_point t0;

//scene
static void scene_setup(void)
{
	//data
	vbo = new canvas::VBO;
	ibo = new canvas::IBO;
	canvas::vertices::Model2D::attributes(vbo->attributes());
	//font
	scene->add_font("times");
	//latex
	scene->add_latex(rigid_map.m_labels[0]);
	scene->add_latex(rigid_map.m_labels[1]);
	//shaders
	program.vertex_shader()->path("Test/shd/rigid-map.vert");
	program.fragment_shader()->path("Test/shd/rigid-map.frag");
	program.setup();
	//objects
	scene->add_object(&rigid_map);
	//scene
	vbo->enable();
	scene->add_vbo(vbo);
	scene->add_ibo(ibo);
	scene->programs().push_back(&program);
	scene->commands().push_back(canvas::Command(GL_TRIANGLES, 6, 12, UINT32_MAX, 7));
}
static void scene_update(void)
{
	//data
	const float wp_min = 1.40f;
	const float wp_max = 3.00f;
	const float bt_min = 1.00f;
	const float bt_max = 89.0f;
	using namespace std::chrono;
	const high_resolution_clock::time_point tn = high_resolution_clock::now();
	const float q = duration_cast<microseconds>(tn - t0).count() / 1.00e6f;
	const float wp = wp_min + fmodf(q, wp_max - wp_min);
	const float bt = bt_min + fmodf(10 * q, bt_max - bt_min);
	//program
	program.set_uniform("wp", wp);
	program.set_uniform("mode", 0U);
	program.set_uniform("full", 0U);
	program.set_uniform("bt", bt * float(M_PI) / 180);
}
static void scene_cleanup(void)
{
	delete vbo;
	delete ibo;
	scene->clear_objects(false);
}

void examples::scenes::rigid_map(int argc, char** argv)
{
	//data
	Engine engine;
	//callbacks
	// engine.callback_idle(scene_update);
	//scene
	scene = engine.scene();
	scene_setup();
	//update
	scene->update(true);
	scene->camera().bound();
	scene->camera().apply();
	scene->camera().update();
	t0 = std::chrono::high_resolution_clock::now();
	//start
	engine.start();
	scene_cleanup();
}