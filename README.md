# Canvas

<!-- markdownlint-disable MD010 MD024 MD033 -->

Canvas is a C++ library for creating scientific drawings. It aims at being as simple to use as possible, while providing a comprehensive control of the code. The library is based on modern OpenGL 4.6 and can be integrated with any window system that provides an OpenGL context.

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

## Internal structure

VBO:
(0) model 3D:
	Position(3f) Color(4f)
(1) image 3D:
	Position(3f) Texture(2f)
(2) text 3D:
	Position(3f) Color(4f) Texture(2f)
(3) model 2D:
	Position(2f) Color(4f)
(4) image 2D:
	Position(2f) Texture (2f)
(5) text 2D:
	Position(2f) Color(4f) Texture (2f)

IBO:
( 0) Type(P) VBO(0) Model 3D
( 1) Type(L) VBO(0) Model 3D
( 2) Type(T) VBO(0) Model 3D
( 3) Type(T) VBO(1) Image 3D
( 4) Type(T) VBO(2) Text 3D
( 5) Type(T) VBO(2) Latex 3D
( 6) Type(P) VBO(3) model 2D
( 7) Type(L) VBO(3) model 2D
( 8) Type(T) VBO(3) model 2D
( 9) Type(T) VBO(4) image 2D
(10) Type(T) VBO(5) text 2D
(11) Type(T) VBO(5) latex 2D

VAO:
( 0) VBO(0) IBO( 0)
( 1) VBO(0) IBO( 1)
( 2) VBO(0) IBO( 2)
( 3) VBO(1) IBO( 3)
( 4) VBO(2) IBO( 4)
( 5) VBO(2) IBO( 5)
( 6) VBO(3) IBO( 6)
( 7) VBO(3) IBO( 7)
( 8) VBO(3) IBO( 8)
( 9) VBO(4) IBO( 9)
(10) VBO(5) IBO(10)
(11) VBO(5) IBO(11)

Textures:
(0) Images
(1) Text
(2) Latex

Programs:
( 0) Model 3D
( 1) Light 3D
( 2) Image 3D
( 3) Text 3D
( 4) Latex 3D
( 5) Model 2D
( 6) Image 2D
( 7) Text 2D
( 8) Latex 2D

Commands:
( 0) Type(P) VAO( 0) Program( 0)
( 1) Type(L) VAO( 1) Program( 0)
( 2) Type(T) VAO( 2) Program( 1)
( 3) Type(T) VAO( 3) Program( 2)
( 4) Type(T) VAO( 4) Program( 3)
( 5) Type(T) VAO( 5) Program( 4)
( 6) Type(P) VAO( 6) Program( 5)
( 7) Type(L) VAO( 7) Program( 5)
( 8) Type(T) VAO( 8) Program( 5)
( 9) Type(T) VAO( 9) Program( 6)
(10) Type(T) VAO(10) Program( 7)
(11) Type(T) VAO(11) Program( 8)
