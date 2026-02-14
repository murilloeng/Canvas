//std
#include <stdexcept>

//OpenGL
#ifdef _WIN32
#include <windows.h>
#define load_procedure(name) wglGetProcAddress(name)
#endif

#ifdef __linux__
#include <GL/glx.h>
#define load_procedure(name) glXGetProcAddress((const GLubyte*) name)
#endif

//canvas
#include "Canvas/Canvas/inc/API/API.hpp"
#include "Canvas/Canvas/inc/API/Loader.hpp"

static void* load(const char* name)
{
	//load
	void* procedure = (void*) load_procedure(name);
	//check
	if(!procedure)
	{
		char msg[1024];
		sprintf(msg, "Error loading OpenGL function %s!", name);
		throw std::runtime_error(msg);
	}
	//return
	return procedure;
}

static void load_get(void)
{
	glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC) load("glGetBufferParameteriv");
}
static void load_draw(void)
{
	glDrawElementsBaseVertex = (PFNGLDRAWELEMENTSBASEVERTEXPROC) load("glDrawElementsBaseVertex");
}
static void load_buffers(void)
{
	glIsBuffer = (PFNGLISBUFFERPROC) load("glIsBuffer");
	glBindBuffer = (PFNGLBINDBUFFERPROC) load("glBindBuffer");
	glCreateBuffers = (PFNGLCREATEBUFFERSPROC) load("glCreateBuffers");
	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC) load("glDeleteBuffers");
	glBindBufferBase = (PFNGLBINDBUFFERBASEPROC) load("glBindBufferBase");
	glNamedBufferData = (PFNGLNAMEDBUFFERDATAPROC) load("glNamedBufferData");
	glNamedBufferSubData = (PFNGLNAMEDBUFFERSUBDATAPROC) load("glNamedBufferSubData");
}
static void load_shaders(void)
{
	glIsShader = (PFNGLISSHADERPROC) load("glIsShader");
	glGetShaderiv = (PFNGLGETSHADERIVPROC) load("glGetShaderiv");
	glCreateShader = (PFNGLCREATESHADERPROC) load("glCreateShader");
	glDeleteShader = (PFNGLDELETESHADERPROC) load("glDeleteShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC) load("glShaderSource");
	glCompileShader = (PFNGLCOMPILESHADERPROC) load("glCompileShader");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) load("glGetShaderInfoLog");
}
static void load_programs(void)
{
	glIsProgram = (PFNGLISPROGRAMPROC) load("glIsProgram");
	glUseProgram = (PFNGLUSEPROGRAMPROC) load("glUseProgram");
	glLinkProgram = (PFNGLLINKPROGRAMPROC) load("glLinkProgram");
	glAttachShader = (PFNGLATTACHSHADERPROC) load("glAttachShader");
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC) load("glGetProgramiv");
	glCreateProgram = (PFNGLCREATEPROGRAMPROC) load("glCreateProgram");
	glDeleteProgram = (PFNGLDELETEPROGRAMPROC) load("glDeleteProgram");
	glValidateProgram = (PFNGLVALIDATEPROGRAMPROC) load("glValidateProgram");
	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC) load("glGetProgramInfoLog");
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) load("glGetUniformLocation");
}
static void load_textures(void)
{
	glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) load("glGenerateMipmap");
	glCreateTextures = (PFNGLCREATETEXTURESPROC) load("glCreateTextures");
	glBindTextureUnit = (PFNGLBINDTEXTUREUNITPROC) load("glBindTextureUnit");
	glTextureParameteri = (PFNGLTEXTUREPARAMETERIPROC) load("glTextureParameteri");
	glTextureSubImage2D = (PFNGLTEXTURESUBIMAGE2DPROC) load("glTextureSubImage2D");
}
static void load_uniforms(void)
{
	glUniform1f = (PFNGLUNIFORM1FPROC) load("glUniform1f");
	glUniform2f = (PFNGLUNIFORM2FPROC) load("glUniform2f");
	glUniform3f = (PFNGLUNIFORM3FPROC) load("glUniform3f");
	glUniform4f = (PFNGLUNIFORM4FPROC) load("glUniform4f");
	glUniform1i = (PFNGLUNIFORM1IPROC) load("glUniform1i");
	glUniform2i = (PFNGLUNIFORM2IPROC) load("glUniform2i");
	glUniform3i = (PFNGLUNIFORM3IPROC) load("glUniform3i");
	glUniform4i = (PFNGLUNIFORM4IPROC) load("glUniform4i");
	glUniform1ui = (PFNGLUNIFORM1UIPROC) load("glUniform1ui");
	glUniform2ui = (PFNGLUNIFORM2UIPROC) load("glUniform2ui");
	glUniform3ui = (PFNGLUNIFORM3UIPROC) load("glUniform3ui");
	glUniform4ui = (PFNGLUNIFORM4UIPROC) load("glUniform4ui");
	glUniform1fv = (PFNGLUNIFORM1FVPROC) load("glUniform1fv");
	glUniform2fv = (PFNGLUNIFORM2FVPROC) load("glUniform2fv");
	glUniform3fv = (PFNGLUNIFORM3FVPROC) load("glUniform3fv");
	glUniform4fv = (PFNGLUNIFORM4FVPROC) load("glUniform4fv");
	glUniform1iv = (PFNGLUNIFORM1IVPROC) load("glUniform1iv");
	glUniform2iv = (PFNGLUNIFORM2IVPROC) load("glUniform2iv");
	glUniform3iv = (PFNGLUNIFORM3IVPROC) load("glUniform3iv");
	glUniform4iv = (PFNGLUNIFORM4IVPROC) load("glUniform4iv");
	glUniform1uiv = (PFNGLUNIFORM1UIVPROC) load("glUniform1uiv");
	glUniform2uiv = (PFNGLUNIFORM2UIVPROC) load("glUniform2uiv");
	glUniform3uiv = (PFNGLUNIFORM3UIVPROC) load("glUniform3uiv");
	glUniform4uiv = (PFNGLUNIFORM4UIVPROC) load("glUniform4uiv");
	glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC) load("glUniformMatrix2fv");
	glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC) load("glUniformMatrix3fv");
	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC) load("glUniformMatrix4fv");
}
static void load_vertex_arrays(void)
{
	glIsVertexArray = (PFNGLISVERTEXARRAYPROC) load("glIsVertexArray");
	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC) load("glBindVertexArray");
	glCreateVertexArrays = (PFNGLCREATEVERTEXARRAYSPROC) load("glCreateVertexArrays");
	glEnableVertexArrayAttrib = (PFNGLENABLEVERTEXARRAYATTRIBPROC) load("glEnableVertexArrayAttrib");
	glVertexArrayVertexBuffer = (PFNGLVERTEXARRAYVERTEXBUFFERPROC) load("glVertexArrayVertexBuffer");
	glVertexArrayAttribFormat = (PFNGLVERTEXARRAYATTRIBFORMATPROC) load("glVertexArrayAttribFormat");
	glVertexArrayElementBuffer = (PFNGLVERTEXARRAYELEMENTBUFFERPROC) load("glVertexArrayElementBuffer");
	glVertexArrayAttribBinding = (PFNGLVERTEXARRAYATTRIBBINDINGPROC) load("glVertexArrayAttribBinding");
}

namespace canvas
{
	void load_functions(void)
	{
		load_get();
		load_draw();
		load_buffers();
		load_shaders();
		load_programs();
		load_textures();
		load_uniforms();
		load_vertex_arrays();
	}
}