# Canvas

Canvas is a C++ library for creating 2D and 3D scenes and scientific drawings. It aims at begin as simple to use as possible, while providing a comprehensive control of the code. The library is based on modern OpenGL 4.6 and can be integrated with any window system that provides an OpenGL context. Default managers for GLUT and QT are added for convenience.

A python binding, allowing for the library to be called and used via python scripts, is planned for the near future.

Author: Murillo Vinicius Bento Santana

Contact: [murillo.bento-santana@univ-amu.fr](mailto:murillo.bento-santana@univ-amu.fr)

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

Build the release version of the code: `make m=r`

Run the debug version of the code: `make run`

Run the release version of the code: `make run m=r`

Clean the debug version of the code: `make clean`

Clean the release version of the code: `make clean m=r`

## Debug

### Debug in Windows

Debug the code: `make debug`

### Debug in Unix

Debug the code: `gdb ./dist/debug/test.out`

## Examples

[Alt text](https://github.com/murilloeng/Canvas/blob/main/test/data/tutorial/points.gif?raw=true)
