//std
#include <cmath>
#include <chrono>

//canvas
#include "Canvas/inc/GPU/VBO.hpp"
#include "Canvas/inc/GPU/IBO.hpp"
#include "Canvas/inc/GPU/Shader.hpp"
#include "Canvas/inc/GPU/Program.hpp"
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Scene/Command.hpp"
#include "Canvas/inc/Objects/Object.hpp"
#include "Canvas/inc/Vertices/Model2D.hpp"

//test
#include "Canvas/Test/inc/examples.hpp"
#include "Canvas/Test/inc/managers/GLFW.hpp"

//class
class Rigid_Map : public canvas::objects::Object
{
public:
	//constructor
	Rigid_Map(void) { return; }

	//destructor
	~Rigid_Map(void) { return; }

	//buffers
	void buffers_size(void) override
	{
		m_vbo_size[ 6] = 4;
		m_ibo_size[12] = 6;
	}
	void buffers_data(void) const override
	{
		//data
		uint32_t* ibo_ptr = ibo_data(12);
		canvas::vertices::Model2D* vbo_ptr = (canvas::vertices::Model2D*) m_scene->vbo(6)->data() + m_vbo_index[6];
		//vbo data
		vbo_ptr[0].m_position = {-1, -1};
		vbo_ptr[1].m_position = {+1, -1};
		vbo_ptr[2].m_position = {+1, +1};
		vbo_ptr[3].m_position = {-1, +1};
		//ibo ptr
		ibo_ptr[3 * 0 + 0] = m_vbo_index[3] + 0;
		ibo_ptr[3 * 0 + 1] = m_vbo_index[3] + 1;
		ibo_ptr[3 * 0 + 2] = m_vbo_index[3] + 2;
		ibo_ptr[3 * 1 + 0] = m_vbo_index[3] + 0;
		ibo_ptr[3 * 1 + 1] = m_vbo_index[3] + 2;
		ibo_ptr[3 * 1 + 2] = m_vbo_index[3] + 3;
	}
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
	//GPU
	vbo = new canvas::VBO;
	ibo = new canvas::IBO;
	canvas::vertices::Model2D::attributes(vbo->attributes());
	vbo->enable();
	//shaders
	program.vertex_shader()->path("Test/shd/rigid-map.vert");
	program.fragment_shader()->path("Test/shd/rigid-map.frag");
	program.setup();
	//objects
	scene->add_object(&rigid_map);
	//scene
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
	using namespace std::chrono;
	const high_resolution_clock::time_point tn = high_resolution_clock::now();
	const float q = duration_cast<microseconds>(tn - t0).count() / 1.00e6f;
	const float wp = wp_min + fmodf(q, wp_max - wp_min);
	//program
	program.set_uniform("wp", wp);
	program.set_uniform("full", 1U);
	program.set_uniform("wp_min", wp_min);
	program.set_uniform("wp_max", wp_max);
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
	GLFW app(argc, argv, "shd/");
	app.callback_idle(scene_update);
	//scene
	scene = app.scene();
	scene_setup();
	//update
	scene->update(true);
	scene->camera().bound();
	scene->camera().apply();
	scene->camera().update();
	t0 = std::chrono::high_resolution_clock::now();
	//start
	app.start();
	scene_cleanup();
}