#pragma once

//OpenGL
#ifdef _WIN32
#include <Windows.h>
#include <GL/gl.h>
#include "GL/glext.hpp"
#endif
#include <GL/gl.h>

//get
inline PFNGLGETBUFFERPARAMETERIVPROC glGetBufferParameteriv = nullptr;

//buffers
inline PFNGLISBUFFERPROC glIsBuffer = nullptr;
inline PFNGLBINDBUFFERPROC glBindBuffer = nullptr;
inline PFNGLCREATEBUFFERSPROC glCreateBuffers = nullptr;
inline PFNGLDELETEBUFFERSPROC glDeleteBuffers = nullptr;
inline PFNGLBINDBUFFERBASEPROC glBindBufferBase = nullptr;
inline PFNGLNAMEDBUFFERDATAPROC glNamedBufferData = nullptr;
inline PFNGLNAMEDBUFFERSUBDATAPROC glNamedBufferSubData = nullptr;

//vertex arrays
inline PFNGLISVERTEXARRAYPROC glIsVertexArray = nullptr;
inline PFNGLBINDVERTEXARRAYPROC glBindVertexArray = nullptr;
inline PFNGLCREATEVERTEXARRAYSPROC glCreateVertexArrays = nullptr;
inline PFNGLENABLEVERTEXARRAYATTRIBPROC glEnableVertexArrayAttrib = nullptr;
inline PFNGLVERTEXARRAYVERTEXBUFFERPROC glVertexArrayVertexBuffer = nullptr;
inline PFNGLVERTEXARRAYATTRIBFORMATPROC glVertexArrayAttribFormat = nullptr;
inline PFNGLVERTEXARRAYELEMENTBUFFERPROC glVertexArrayElementBuffer = nullptr;
inline PFNGLVERTEXARRAYATTRIBBINDINGPROC glVertexArrayAttribBinding = nullptr;

//textures
inline PFNGLGENERATEMIPMAPPROC glGenerateMipmap = nullptr;
inline PFNGLCREATETEXTURESPROC glCreateTextures = nullptr;
inline PFNGLBINDTEXTUREUNITPROC glBindTextureUnit = nullptr;
inline PFNGLTEXTUREPARAMETERIPROC glTextureParameteri = nullptr;
inline PFNGLTEXTURESUBIMAGE2DPROC glTextureSubImage2D = nullptr;

//shaders
inline PFNGLISSHADERPROC glIsShader = nullptr;
inline PFNGLGETSHADERIVPROC glGetShaderiv = nullptr;
inline PFNGLCREATESHADERPROC glCreateShader = nullptr;
inline PFNGLDELETESHADERPROC glDeleteShader = nullptr;
inline PFNGLSHADERSOURCEPROC glShaderSource = nullptr;
inline PFNGLCOMPILESHADERPROC glCompileShader = nullptr;
inline PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;

//programs
inline PFNGLISPROGRAMPROC glIsProgram = nullptr;
inline PFNGLUSEPROGRAMPROC glUseProgram = nullptr;
inline PFNGLLINKPROGRAMPROC glLinkProgram = nullptr;
inline PFNGLATTACHSHADERPROC glAttachShader = nullptr;
inline PFNGLGETPROGRAMIVPROC glGetProgramiv = nullptr;
inline PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;
inline PFNGLDELETEPROGRAMPROC glDeleteProgram = nullptr;
inline PFNGLVALIDATEPROGRAMPROC glValidateProgram = nullptr;
inline PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = nullptr;
inline PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = nullptr;

//uniforms
inline PFNGLUNIFORM1FPROC glUniform1f = nullptr;
inline PFNGLUNIFORM2FPROC glUniform2f = nullptr;
inline PFNGLUNIFORM3FPROC glUniform3f = nullptr;
inline PFNGLUNIFORM4FPROC glUniform4f = nullptr;

inline PFNGLUNIFORM1IPROC glUniform1i = nullptr;
inline PFNGLUNIFORM2IPROC glUniform2i = nullptr;
inline PFNGLUNIFORM3IPROC glUniform3i = nullptr;
inline PFNGLUNIFORM4IPROC glUniform4i = nullptr;

inline PFNGLUNIFORM1UIPROC glUniform1ui = nullptr;
inline PFNGLUNIFORM2UIPROC glUniform2ui = nullptr;
inline PFNGLUNIFORM3UIPROC glUniform3ui = nullptr;
inline PFNGLUNIFORM4UIPROC glUniform4ui = nullptr;

inline PFNGLUNIFORM1FVPROC glUniform1fv = nullptr;
inline PFNGLUNIFORM2FVPROC glUniform2fv = nullptr;
inline PFNGLUNIFORM3FVPROC glUniform3fv = nullptr;
inline PFNGLUNIFORM4FVPROC glUniform4fv = nullptr;

inline PFNGLUNIFORM1IVPROC glUniform1iv = nullptr;
inline PFNGLUNIFORM2IVPROC glUniform2iv = nullptr;
inline PFNGLUNIFORM3IVPROC glUniform3iv = nullptr;
inline PFNGLUNIFORM4IVPROC glUniform4iv = nullptr;

inline PFNGLUNIFORM1UIVPROC glUniform1uiv = nullptr;
inline PFNGLUNIFORM2UIVPROC glUniform2uiv = nullptr;
inline PFNGLUNIFORM3UIVPROC glUniform3uiv = nullptr;
inline PFNGLUNIFORM4UIVPROC glUniform4uiv = nullptr;

inline PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv = nullptr;
inline PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv = nullptr;
inline PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = nullptr;