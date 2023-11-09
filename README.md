# Canvas

<!-- markdownlint-disable MD010 MD024 MD033 -->

Canvas is a C++ library for creating 2D and 3D scenes and scientific drawings. It aims at begin as simple to use as possible, while providing a comprehensive control of the code. The library is based on modern OpenGL 4.6 and can be integrated with any window system that provides an OpenGL context. Default managers for GLUT and QT are added for convenience.

A python binding, allowing for the library to be called and used via python scripts, is planned for the near future.

Author: Murillo Vinicius Bento Santana

Contact: [murillo.bento-santana@univ-amu.fr](mailto:murillo.bento-santana@univ-amu.fr)

## Setup

### Setup in Windows

The MSVC C++ compiler is used for building and debugging. Be sure to have it [installed](https://visualstudio.microsoft.com/vs/community/) and [available](https://learn.microsoft.com/en-us/visualstudio/ide/reference/command-prompt-powershell?view=vs-2022) in the path. All used external libraries are packed with the code.

Generate an executable (make.exe) that will be used to build the code: `win\make.bat`

### Setup in Unix

The [GNU C++](https://gcc.gnu.org/) compiler and the [GNU Make](https://www.gnu.org/software/make/) tool are used for the build. The [GNU GDB](https://www.sourceware.org/gdb/) debugger is used to debug the code. Be sure to have them installed by running the following commands:

`sudo apt-get install g++`

`sudo apt-get install gdb`

`sudo apt-get install make`

## Build and Run

Build the debug version of the code: `make`

Run the debug version of the code: `make run`

Clean the debug version of the code: `make clean`

To build, run or clean the release version, simply add the option `m=r` to the make commands above.

## Debug

### Debug in Windows

Debug the code: `make debug`

### Debug in Unix

Debug the code: `gdb ./dist/debug/test.out`

## Objects

A number of pre-defined objects (listed below) are defined for convenience. The user has also the possibility of creating its own objects, derived of the base class `canvas::objects::Object`. Objects can also be grouped via the base class `canvas::objects::Group`.

| 0D:   | 1D:      | 2D:      | 3D:      | Textures: |
|-------|----------|----------|----------|-----------|
| Point | Arc      | Quad     | Cube     | Text      |
|       | Line     | Circle   | Sphere   | Latex     |
|       | Curve    | Grid 2D  | Cylinder | Image     |
|       | Arrow    | Grid 3D  |          |           |
|       | Spline   | Polygon  |          |           |
|       | Polyline | Surface  |          |           |
|       |          | Triangle |          |           |

## Textures

### Text

Text can be added to the scene via the class `canvas::objects::Text`. Text support is made available via the [freetype library](http://freetype.org/). Fonts are loaded from true type font files (`.ttf`). In windows, these files are usually located under `C:\Windows\Fonts`, while on Unix they are usually located under `/usr/share/fonts`.

### Latex

Latex can be added to the scene via the class `canvas::objects::Latex`. Latex support is made available via the `pdflatex TeX compiler` distributed by the [MiKTeX package](https://miktex.org/). Make sure to have it installed and available in the path before using the Latex class.

### Images

Images can be added to the scene via the class `canvas::objects::Image`. Image support is made available via the [stb library](https://github.com/nothings/stb). Screenshots can also be converted to images via the `canvas::Scene` class.

## Examples

### 0D

<details>
	<summary>Points</summary>
	<img src="test/data/tutorial/0D/points.png" height="600"/>

	//canvas
	#include "inc/Scene/Scene.hpp"
	#include "inc/Objects/0D/Point.hpp"

	//examples
	#include "inc/examples.hpp"

	void points(canvas::Scene* scene)
	{
		//data
		const unsigned n = 10;
		const float r = 1.0f / n;
		//objects
		for(unsigned i = 0; i < n; i++)
		{
			for(unsigned j = 0; j < n; j++)
			{
				const float x1 = 2 * r * j + r - 1;
				const float x2 = 2 * r * i + r - 1;
				scene->add_object(new canvas::objects::Point);
				((canvas::objects::Point*) scene->object(n * i + j))->position({x1, x2, 0});
			}
		}
	}
</details>

### 1D

<details>
	<summary>Arcs</summary>
	<img src="test/data/tutorial/1D/arcs.png" height="600"/>

	//std
	#include <cmath>

	//canvas
	#include "inc/Scene/Scene.hpp"
	#include "inc/Objects/1D/Arc.hpp"
	#include "inc/Objects/1D/Arrow.hpp"

	//examples
	#include "inc/examples.hpp"

	void arcs(canvas::Scene* scene)
	{
		//data
		const unsigned n = 10;
		const float r = 1.0f / n;
		//objects
		for(unsigned i = 0; i < n; i++)
		{
			for(unsigned j = 0; j < n; j++)
			{
				scene->add_object(new canvas::objects::Arc);
				((canvas::objects::Arc*) scene->object(n * i + j))->radius(r);
				((canvas::objects::Arc*) scene->object(n * i + j))->angle(0, 0);
				((canvas::objects::Arc*) scene->object(n * i + j))->add_arrow(0.5, true);
				((canvas::objects::Arc*) scene->object(n * i + j))->color_fill({0, 0, 1});
				((canvas::objects::Arc*) scene->object(n * i + j))->color_stroke({1, 1, 1});
				((canvas::objects::Arc*) scene->object(n * i + j))->arrow(0)->width(r / 5);
				((canvas::objects::Arc*) scene->object(n * i + j))->arrow(0)->height(r / 5);
				((canvas::objects::Arc*) scene->object(n * i + j))->angle(1, 2 * M_PI * float(n * i + j) / n / n);
				((canvas::objects::Arc*) scene->object(n * i + j))->shift({2 * r * j + r - 1, 2 * r * i + r - 1, 0});
			}
		}
	}
</details>

<details>
	<summary>Lines</summary>
	<img src="test/data/tutorial/1D/lines.png" height="600"/>

	//canvas
	#include "inc/Scene/Scene.hpp"
	#include "inc/Objects/1D/Line.hpp"
	#include "inc/Objects/1D/Arrow.hpp"

	//examples
	#include "inc/examples.hpp"

	void lines(canvas::Scene* scene)
	{
		//data
		float s = 0.90f;
		const unsigned n = 5;
		const float x1[] = {-1, +1, +1, -1};
		const float x2[] = {-1, -1, +1, +1};
		//objects
		for(unsigned i = 0; i < n; i++)
		{
			for(unsigned j = 0; j < 4; j++)
			{
				scene->add_object(new canvas::objects::Line);
				((canvas::objects::Line*) scene->object(4 * i + j))->add_arrow(0.50f, true);
				((canvas::objects::Line*) scene->object(4 * i + j))->arrow(0)->width(s / 10);
				((canvas::objects::Line*) scene->object(4 * i + j))->arrow(0)->height(s / 10);
				((canvas::objects::Line*) scene->object(4 * i + j))->point(0, {s * x1[(j + 0) % 4], s * x2[(j + 0) % 4], 0});
				((canvas::objects::Line*) scene->object(4 * i + j))->point(1, {s * x1[(j + 1) % 4], s * x2[(j + 1) % 4], 0});
			}
			s /= 2;
		}
	}
</details>

<details>
	<summary>Arrows</summary>
	<img src="test/data/tutorial/1D/arrows.png" height="600"/>

	//canvas
	#include "inc/Scene/Scene.hpp"
	#include "inc/Objects/1D/Line.hpp"
	#include "inc/Objects/1D/Arrow.hpp"

	//examples
	#include "inc/examples.hpp"

	void arrows(canvas::Scene* scene)
	{
		//objects
		canvas::objects::Line* a1 = new canvas::objects::Line;
		canvas::objects::Line* a2 = new canvas::objects::Line;
		canvas::objects::Line* a3 = new canvas::objects::Line;
		//setup
		a1->add_arrow(1, true);
		a2->add_arrow(1, true);
		a3->add_arrow(1, true);
		a1->point(0, {0, 0, 0});
		a1->point(1, {1, 0, 0});
		a2->point(0, {0, 0, 0});
		a2->point(1, {0, 1, 0});
		a3->point(0, {0, 0, 0});
		a3->point(1, {0, 0, 1});
		a1->color_stroke({1, 0, 0});
		a2->color_stroke({0, 1, 0});
		a3->color_stroke({0, 0, 1});
		//scene
		scene->add_object(a1);
		scene->add_object(a2);
		scene->add_object(a3);
	}
</details>

<details>
	<summary>Curves</summary>
	<img src="test/data/tutorial/1D/curves.png" height="600"/>

	//std
	#include <cmath>

	//canvas
	#include "inc/Scene/Scene.hpp"
	#include "inc/Objects/1D/Curve.hpp"
	#include "inc/Objects/1D/Arrow.hpp"

	//examples
	#include "inc/examples.hpp"

	void curves(canvas::Scene* scene)
	{
		//data
		const float r = 1.0f;
		const unsigned nt = 5;
		const unsigned nm = 200;
		//curve
		canvas::objects::Curve* curve = new canvas::objects::Curve;
		curve->position([r] (float s){ 
			const float v1 = r * cosf(2 * nt * M_PI * s);
			const float v2 = r * sinf(2 * nt * M_PI * s);
			return canvas::vec3(v1, v2, s);
		});
		curve->gradient([r] (float s){ 
			const float v1 = -2 * nt * M_PI * r * sinf(2 * nt * M_PI * s);
			const float v2 = +2 * nt * M_PI * r * cosf(2 * nt * M_PI * s);
			return canvas::vec3(v1, v2, 1);
		});
		curve->hessian([r] (float s){ 
			const float v1 = -4 * nt * nt * M_PI * M_PI * r * cosf(2 * nt * M_PI * s);
			const float v2 = -4 * nt * nt * M_PI * M_PI * r * sinf(2 * nt * M_PI * s);
			return canvas::vec3(v1, v2, 0);
		});
		curve->mesh(nm);
		scene->add_object(curve);
	}
</details>

<details>
	<summary>Splines</summary>
	<img src="test/data/tutorial/1D/splines.png" height="600"/>

	//canvas
	#include "inc/Scene/Scene.hpp"
	#include "inc/Objects/1D/Arrow.hpp"
	#include "inc/Objects/1D/Spline.hpp"

	//examples
	#include "inc/examples.hpp"

	void splines(canvas::Scene* scene)
	{
		//data
		const float r = 9.00e-01;
		const float s = 5.00e-01;
		canvas::objects::Spline* spline = new canvas::objects::Spline;
		//spline
		spline->mesh(100);
		spline->point(0, {+r, 0, 0});
		spline->point(1, {0, +r, 0});
		spline->add_point({-r, 0, 0});
		spline->add_point({0, -r, 0});
		spline->add_point({+r, 0, 0});
		spline->add_arrow(0.50f, true);
		spline->add_arrow(1.50f, true);
		spline->add_arrow(2.50f, true);
		spline->add_arrow(3.50f, true);
		spline->arrow(0)->width(0.10f);
		spline->arrow(1)->width(0.10f);
		spline->arrow(2)->width(0.10f);
		spline->arrow(3)->width(0.10f);
		spline->arrow(0)->height(0.10f);
		spline->arrow(1)->height(0.10f);
		spline->arrow(2)->height(0.10f);
		spline->arrow(3)->height(0.10f);
		spline->control(0, 1, {+r, +s, 0});
		spline->control(1, 0, {+s, +r, 0});
		spline->control(1, 1, {-s, +r, 0});
		spline->control(2, 0, {-r, +s, 0});
		spline->control(2, 1, {-r, -s, 0});
		spline->control(3, 0, {-s, -r, 0});
		spline->control(3, 1, {+s, -r, 0});
		spline->control(4, 0, {+r, -s, 0});
		//scene
		scene->add_object(spline);
	}
</details>

<details>
	<summary>Polylines</summary>
	<img src="test/data/tutorial/1D/polylines.png" height="600"/>

	//canvas
	#include "inc/Scene/Scene.hpp"
	#include "inc/Objects/1D/Arrow.hpp"
	#include "inc/Objects/1D/Polyline.hpp"

	//examples
	#include "inc/examples.hpp"

	void polylines(canvas::Scene* scene)
	{
		//data
		const float w = 1.00e-01;
		const float h = 1.00e-01;
		const float t = 1.00e-02;
		canvas::objects::Polyline* polyline;
		//spline
		polyline = new canvas::objects::Polyline;
		polyline->points().push_back({-w / 2, -h / 2 - t, 0});
		polyline->points().push_back({+w / 2, -h / 2 - t, 0});
		polyline->points().push_back({+w / 2, -h / 2, 0});
		polyline->points().push_back({+t / 2, -h / 2, 0});
		polyline->points().push_back({+t / 2, +h / 2, 0});
		polyline->points().push_back({+w / 2, +h / 2, 0});
		polyline->points().push_back({+w / 2, +h / 2 + t, 0});
		polyline->points().push_back({-w / 2, +h / 2 + t, 0});
		polyline->points().push_back({-w / 2, +h / 2, 0});
		polyline->points().push_back({-t / 2, +h / 2, 0});
		polyline->points().push_back({-t / 2, -h / 2, 0});
		polyline->points().push_back({-w / 2, -h / 2, 0});
		polyline->points().push_back({-w / 2, -h / 2 - t, 0});
		//arrows
		for(unsigned i = 0; i < 12; i++)
		{
			polyline->add_arrow(i + 0.5f, true);
			polyline->arrow(i)->width(2.50e-03);
			polyline->arrow(i)->height(2.50e-03);
		}
		//scene
		scene->add_object(polyline);
	}
</details>

### 2D

<details>
	<summary>Quads</summary>
	<img src="test/data/tutorial/2D/quads.png" height="600"/>

	//canvas
	#include "inc/Scene/Scene.hpp"
	#include "inc/Objects/2D/Quad.hpp"

	//examples
	#include "inc/examples.hpp"

	void quads(canvas::Scene* scene)
	{
		//data
		const unsigned n = 40;
		const float s = 2.0f / n;
		//objects
		for(unsigned i = 0; i < n; i++)
		{
			for(unsigned j = 0; j < n; j++)
			{
				scene->add_object(new canvas::objects::Quad);
				((canvas::objects::Quad*) scene->object(n * i + j))->color_fill({0, 0, 1});
				((canvas::objects::Quad*) scene->object(n * i + j))->color_stroke({1, 1, 1});
				((canvas::objects::Quad*) scene->object(n * i + j))->point(0, {(j + 0) * s - 1, (i + 0) * s - 1, 0});
				((canvas::objects::Quad*) scene->object(n * i + j))->point(1, {(j + 1) * s - 1, (i + 0) * s - 1, 0});
				((canvas::objects::Quad*) scene->object(n * i + j))->point(2, {(j + 1) * s - 1, (i + 1) * s - 1, 0});
				((canvas::objects::Quad*) scene->object(n * i + j))->point(3, {(j + 0) * s - 1, (i + 1) * s - 1, 0});
			}
		}
	}
</details>

<details>
	<summary>Circles</summary>
	<img src="test/data/tutorial/2D/circles.png" height="600"/>

	//canvas
	#include "inc/Scene/Scene.hpp"
	#include "inc/Objects/2D/Circle.hpp"

	//examples
	#include "inc/examples.hpp"

	void circles(canvas::Scene* scene)
	{
		//data
		const unsigned n = 10;
		const float r = 1.0f / n;
		//objects
		for(unsigned i = 0; i < n; i++)
		{
			for(unsigned j = 0; j < n; j++)
			{
				scene->add_object(new canvas::objects::Circle);
				((canvas::objects::Circle*) scene->object(n * i + j))->radius(0.9 * r);
				((canvas::objects::Circle*) scene->object(n * i + j))->color_fill({0, 0, 1});
				((canvas::objects::Circle*) scene->object(n * i + j))->color_stroke({1, 1, 1});
				((canvas::objects::Circle*) scene->object(n * i + j))->shift({2 * r * j + r - 1, 2 * r * i + r - 1, 0});
			}
		}
	}
</details>

<details>
	<summary>Grids 2D</summary>
	<img src="test/data/tutorial/2D/grid_2D.png" height="600"/>

	//canvas
	#include "inc/Scene/Scene.hpp"
	#include "inc/Objects/2D/Grid_2D.hpp"

	//examples
	#include "inc/examples.hpp"

	void grid_2D(canvas::Scene* scene)
	{
		//data
		const unsigned n = 10;
		const float s = 1.0f / n;
		//objects
		for(unsigned i = 0; i < n; i++)
		{
			for(unsigned j = 0; j < n; j++)
			{
				const float x1 = 2 * j * s - 1 + s;
				const float x2 = 2 * i * s - 1 + s;
				scene->add_object(new canvas::objects::Grid_2D);
				((canvas::objects::Grid_2D*) scene->object(n * i + j))->scale(0.5 * s);
				((canvas::objects::Grid_2D*) scene->object(n * i + j))->shift({x1, x2, 0});
				((canvas::objects::Grid_2D*) scene->object(n * i + j))->color_fill({0, 0, 1});
				((canvas::objects::Grid_2D*) scene->object(n * i + j))->color_stroke({1, 1, 1});
			}
		}
	}
</details>

<details>
	<summary>Grids 3D</summary>
	<img src="test/data/tutorial/2D/grid_3D.png" height="600"/>

	//canvas
	#include "inc/Scene/Scene.hpp"
	#include "inc/Objects/2D/Grid_3D.hpp"

	//examples
	#include "inc/examples.hpp"

	void grid_3D(canvas::Scene* scene)
	{
		//data
		const unsigned n = 10;
		const float s = 1.0f / n;
		//objects
		for(unsigned i = 0; i < n; i++)
		{
			for(unsigned j = 0; j < n; j++)
			{
				const float x1 = 2 * j * s - 1 + s;
				const float x2 = 2 * i * s - 1 + s;
				scene->add_object(new canvas::objects::Grid_3D);
				((canvas::objects::Grid_3D*) scene->object(n * i + j))->scale(0.5 * s);
				((canvas::objects::Grid_3D*) scene->object(n * i + j))->shift({x1, x2, 0});
				((canvas::objects::Grid_3D*) scene->object(n * i + j))->color_fill({0, 0, 1});
				((canvas::objects::Grid_3D*) scene->object(n * i + j))->color_stroke({1, 1, 1});
			}
		}
	}
</details>

<details>
	<summary>Surfaces</summary>
	<img src="test/data/tutorial/2D/surfaces.png" height="600"/>

	//canvas
	#include "inc/Scene/Scene.hpp"
	#include "inc/Objects/2D/Surface.hpp"

	//examples
	#include "inc/examples.hpp"

	void surfaces(canvas::Scene* scene)
	{
		//data
		canvas::objects::Surface* surface = new canvas::objects::Surface;
		//surface
		surface->mesh(0, 100);
		surface->mesh(1, 100);
		surface->domain(0, 0, -1);
		surface->domain(0, 1, +1);
		surface->domain(1, 0, -1);
		surface->domain(1, 1, +1);
		surface->color_fill({0, 0, 1});
		surface->position([] (float s1, float s2) { 
			const float r = 4 * M_PI * sqrtf(s1 * s1 + s2 * s2);
			return canvas::vec3(s1, s2, fabsf(r) < 1e-5 ? 1 : sinf(r) / r); 
		});
		//light
		scene->light().position({0, 0, 2});
		scene->light().update_shaders();
		//scene
		scene->add_object(surface);
	}
</details>

<details>
	<summary>Polygons</summary>
	<img src="test/data/tutorial/2D/polygons.png" height="600"/>

	//canvas
	#include "inc/Scene/Scene.hpp"
	#include "inc/Objects/2D/Polygon.hpp"

	//examples
	#include "inc/examples.hpp"

	void polygons(canvas::Scene* scene)
	{
		//data
		canvas::objects::Polygon* polygon = new canvas::objects::Polygon;
		//polygon
		polygon->loops().push_back( 4);
		polygon->loops().push_back( 8);
		polygon->loops().push_back(12);
		polygon->loops().push_back(16);
		polygon->loops().push_back(20);
		polygon->color_fill({0, 0, 1});
		polygon->points().push_back({-3, -3});
		polygon->points().push_back({+3, -3});
		polygon->points().push_back({+3, +3});
		polygon->points().push_back({-3, +3});
		polygon->points().push_back({-2, -2});
		polygon->points().push_back({-2, -1});
		polygon->points().push_back({-1, -1});
		polygon->points().push_back({-1, -2});
		polygon->points().push_back({+1, -2});
		polygon->points().push_back({+1, -1});
		polygon->points().push_back({+2, -1});
		polygon->points().push_back({+2, -2});
		polygon->points().push_back({+1, +1});
		polygon->points().push_back({+1, +2});
		polygon->points().push_back({+2, +2});
		polygon->points().push_back({+2, +1});
		polygon->points().push_back({-2, +1});
		polygon->points().push_back({-2, +2});
		polygon->points().push_back({-1, +2});
		polygon->points().push_back({-1, +1});
		//scene
		scene->add_object(polygon);
	}
</details>

<details>
	<summary>Triangles</summary>
	<img src="test/data/tutorial/2D/triangles.png" height="600"/>

	//canvas
	#include "inc/Scene/Scene.hpp"
	#include "inc/Objects/2D/Triangle.hpp"

	//examples
	#include "inc/examples.hpp"

	void triangles(canvas::Scene* scene)
	{
		//data
		const unsigned n = 10;
		const float r = 1.0f / n;
		//objects
		for(unsigned i = 0; i < n; i++)
		{
			for(unsigned j = 0; j < n; j++)
			{
				scene->add_object(new canvas::objects::Triangle);
				((canvas::objects::Triangle*) scene->object(n * i + j))->scale(r);
				((canvas::objects::Triangle*) scene->object(n * i + j))->color_fill({0, 0, 1});
				((canvas::objects::Triangle*) scene->object(n * i + j))->point(0, {-1, -1, 0});
				((canvas::objects::Triangle*) scene->object(n * i + j))->point(1, {+1, -1, 0});
				((canvas::objects::Triangle*) scene->object(n * i + j))->point(2, {+0, +1, 0});
				((canvas::objects::Triangle*) scene->object(n * i + j))->shift({2 * r * j + r - 1, 2 * r * i + r - 1, 0});
			}
		}
	}
</details>

### 3D

<details>
	<summary>Cubes</summary>
	<img src="test/data/tutorial/3D/cubes.png" height="600"/>

	//canvas
	#include "inc/Scene/Scene.hpp"
	#include "inc/Objects/3D/Cube.hpp"

	//examples
	#include "inc/examples.hpp"

	void cubes(canvas::Scene* scene)
	{
		//data
		const unsigned n = 10;
		const float s = 1.0f / n;
		//objects
		for(unsigned i = 0; i < n; i++)
		{
			for(unsigned j = 0; j < n; j++)
			{
				const float x1 = 2 * j * s - 1 + s;
				const float x2 = 2 * i * s - 1 + s;
				scene->add_object(new canvas::objects::Cube);
				((canvas::objects::Cube*) scene->object(n * i + j))->scale(s);
				((canvas::objects::Cube*) scene->object(n * i + j))->shift({x1, x2, 0});
				((canvas::objects::Cube*) scene->object(n * i + j))->color_fill({0.0f, 0.0f, 1.0f});
				((canvas::objects::Cube*) scene->object(n * i + j))->color_stroke({1.0f, 1.0f, 1.0f});
			}
		}
	}
</details>

<details>
	<summary>Spheres</summary>
	<img src="test/data/tutorial/3D/spheres.png" height="600"/>

	//canvas
	#include "inc/Scene/Scene.hpp"
	#include "inc/Objects/3D/Sphere.hpp"

	//examples
	#include "inc/examples.hpp"

	void spheres(canvas::Scene* scene)
	{
		//data
		const unsigned n = 10;
		const float s = 1.0f / n;
		//objects
		for(unsigned i = 0; i < n; i++)
		{
			for(unsigned j = 0; j < n; j++)
			{
				const float x1 = 2 * j * s - 1 + s;
				const float x2 = 2 * i * s - 1 + s;
				scene->add_object(new canvas::objects::Sphere);
				((canvas::objects::Sphere*) scene->object(n * i + j))->scale(s);
				((canvas::objects::Sphere*) scene->object(n * i + j))->shift({x1, x2, 0});
				((canvas::objects::Sphere*) scene->object(n * i + j))->color_fill({0.0f, 0.0f, 1.0f});
				((canvas::objects::Sphere*) scene->object(n * i + j))->color_stroke({1.0f, 1.0f, 1.0f});
			}
		}
	}
</details>

<details>
	<summary>Cylinders</summary>
	<img src="test/data/tutorial/3D/cylinders.png" height="600"/>

	//canvas
	#include "inc/Scene/Scene.hpp"
	#include "inc/Objects/3D/Cylinder.hpp"

	//examples
	#include "inc/examples.hpp"

	void cylinders(canvas::Scene* scene)
	{
		//data
		const unsigned n = 10;
		const float s = 1.0f / n;
		//objects
		for(unsigned i = 0; i < n; i++)
		{
			for(unsigned j = 0; j < n; j++)
			{
				const float x1 = 2 * j * s - 1 + s;
				const float x2 = 2 * i * s - 1 + s;
				scene->add_object(new canvas::objects::Cylinder);
				((canvas::objects::Cylinder*) scene->object(n * i + j))->scale(s / 2);
				((canvas::objects::Cylinder*) scene->object(n * i + j))->shift({x1, x2, 0});
				((canvas::objects::Cylinder*) scene->object(n * i + j))->color_fill({0.0f, 0.0f, 1.0f});
				((canvas::objects::Cylinder*) scene->object(n * i + j))->color_stroke({1.0f, 1.0f, 1.0f});
			}
		}
	}
</details>

### Textures

<details>
	<summary>Text</summary>
	<img src="test/data/tutorial/Images/text.png" height="600"/>

	//canvas
	#include "inc/Scene/Scene.hpp"
	#include "inc/Objects/2D/Quad.hpp"
	#include "inc/Objects/Image/Text.hpp"

	//examples
	#include "inc/examples.hpp"

	//static
	static const float x[] = {-1, -1, +1, -1, +1, +1, -1, +1};
	static const char* c[] = {"A", "B", "C", "D", "E", "F", "G", "H"};
	static const char* a[] = {"NE", "NW", "SW", "SE", "SW", "SE", "NE", "NW"};

	void text(canvas::Scene* scene)
	{
		//fonts
		scene->add_font("times");
		//objects
		canvas::objects::Quad* quad;
		canvas::objects::Text* text[9];
		for(unsigned i = 0; i < 9; i++)
		{
			scene->add_object(text[i] = new canvas::objects::Text);
		}
		scene->add_object(quad = new canvas::objects::Quad);
		//quad
		quad->fill(false);
		quad->point(0, {-1, -1, 0});
		quad->point(1, {+1, -1, 0});
		quad->point(2, {+1, +1, 0});
		quad->point(3, {-1, +1, 0});
		//text
		text[4]->size(0.2f);
		text[4]->anchor("CC");
		text[4]->position({0, 0, 0});
		text[4]->color_fill({0, 1, 0});
		for(unsigned i = 0; i < 4; i++)
		{
			text[i + 0]->size(0.2f);
			text[i + 5]->size(0.2f);
			text[i + 0]->text(c[i + 0]);
			text[i + 5]->text(c[i + 4]);
			text[i + 0]->anchor(a[i + 0]);
			text[i + 5]->anchor(a[i + 4]);
			text[i + 0]->color_fill({0, 0, 1});
			text[i + 5]->color_fill({1, 0, 0});
			text[i + 0]->position({x[2 * i + 0], x[2 * i + 1], 0});
			text[i + 5]->position({x[2 * i + 0], x[2 * i + 1], 0});
		}
		text[4]->text("this is a\nmulti-\vline\ntext\twith tab");
	}
</details>

<details>
	<summary>Latex</summary>
	<img src="test/data/tutorial/Images/latex.png" height="600"/>

	//canvas
	#include "inc/Scene/Scene.hpp"
	#include "inc/Objects/Image/Latex.hpp"

	//examples
	#include "inc/examples.hpp"

	void latex(canvas::Scene* scene)
	{
		//data
		char source[200];
		canvas::objects::Latex* latex;
		//images
		for(unsigned i = 0; i < 12; i++)
		{
			sprintf(source, "$ \\int_{0}^{L} %c_{%d} dx $", i + 65, i);
			scene->add_latex(source);
		}
		//objects
		for(unsigned i = 0; i < 4; i++)
		{
			for(unsigned j = 0; j < 3; j++)
			{
				latex = new canvas::objects::Latex;
				latex->size(0.15);
				latex->anchor("SW");
				latex->index(3 * i + j);
				latex->shift({2 * float(i) / 4 - 1, 2 * float(j) / 3 - 1, 0});
				scene->add_object(latex);
			}
		}
	}
</details>

<details>
	<summary>Images</summary>
	<img src="test/data/tutorial/Images/images.png" height="600"/>

	//canvas
	#include "inc/Scene/Scene.hpp"
	#include "inc/Objects/Image/Image.hpp"

	//examples
	#include "inc/examples.hpp"

	void images(canvas::Scene* scene)
	{
		//data
		char path[200];
		const unsigned ni = 10;
		canvas::objects::Image* image;
		//images
		for(unsigned i = 0; i < 12; i++)
		{
			sprintf(path, "data/images/wizard-%d.png", i % ni);
			scene->add_image(path);
		}
		//objects
		for(unsigned i = 0; i < 4; i++)
		{
			for(unsigned j = 0; j < 3; j++)
			{
				image = new canvas::objects::Image;
				image->size(0.5);
				image->anchor("CC");
				image->index(3 * i + j);
				image->shift({(2 * float(i) + 1) / 4 - 1, (2 * float(j) + 1) / 3 - 1, 0});
				scene->add_object(image);
			}
		}
	}
</details>
