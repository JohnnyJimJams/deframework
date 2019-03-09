#include "ShaderProgram.h"
#include <GL/gl3w.h> 
#include <stdio.h>

ShaderProgram* ShaderProgram::sm_boundProgram = nullptr;

ShaderProgram::ShaderProgram()
	: m_bound(false),
	m_program(0)
{
}

ShaderProgram::~ShaderProgram()
{
	for (auto shader : m_shaders)
		glDeleteShader(shader.second);
	glDeleteProgram(m_program);
}

void ShaderProgram::Bind()
{
	if (sm_boundProgram != nullptr)
	{
		if (sm_boundProgram != this)
			sm_boundProgram->m_bound = false;
	}

	glUseProgram(m_program);
	m_bound = true;
	sm_boundProgram = this;
}

void ShaderProgram::Unbind()
{
	if (sm_boundProgram == this)
	{
		m_bound = false;
		glUseProgram(0);
		sm_boundProgram = nullptr;
	}
}

void ShaderProgram::CompileFromFile(unsigned int a_type, const char* a_filename)
{
	// open file for text reading
	FILE* file = fopen(a_filename,"rb");
	if (file == nullptr)
	{
		return;
	}

	// get number of bytes in file
	fseek(file, 0, SEEK_END);
	unsigned int length = ftell(file);
	fseek(file, 0, SEEK_SET);

	// allocate buffer and read file contents
	char* buffer = new char[length + 1];
	memset(buffer,0,length + 1);
	fread(buffer, sizeof(char), length, file);
	fclose(file);

	m_shaders[a_type] = glCreateShader(a_type);

	// compile vertex shader and log errors
	glShaderSource(m_shaders[a_type], 1, (const char**)&buffer, 0);
	glCompileShader(m_shaders[a_type]);
	
#ifdef _DEBUG
	//check whether the shader loads fine
	int status = 0;
	glGetShaderiv(m_shaders[a_type], GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) 
	{
		int infoLogLength = 0;		
		glGetShaderiv(m_shaders[a_type], GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog= new char[infoLogLength];

		glGetShaderInfoLog(m_shaders[a_type], infoLogLength, 0, infoLog);
		printf("Shader Log:\n");
		printf(infoLog);
		printf("\n");
		delete[] infoLog;
	}
#endif
}

void ShaderProgram::CompileFromString(unsigned int a_type, const char* a_shader)
{
	m_shaders[a_type] = glCreateShader(a_type);
	glShaderSource(m_shaders[a_type], 1, &a_shader, 0);
	glCompileShader(m_shaders[a_type]);

//#ifdef _DEBUG
	//check whether the shader loads fine
	int status = 0;
	glGetShaderiv(m_shaders[a_type], GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) 
	{
		int infoLogLength = 0;		
		glGetShaderiv(m_shaders[a_type], GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog= new char[infoLogLength];

		glGetShaderInfoLog(m_shaders[a_type], infoLogLength, 0, infoLog);
		printf("Shader Log:\n");
		printf(infoLog);
		printf("\n");
		delete[] infoLog;
	}
//#endif
}

void ShaderProgram::CompileFromStrings(unsigned int a_type, unsigned int a_stringCount, const char** a_shaderStrings)
{
	m_shaders[a_type] = glCreateShader(a_type);
	glShaderSource(m_shaders[a_type], a_stringCount, a_shaderStrings, 0);
	glCompileShader(m_shaders[a_type]);

#ifdef _DEBUG
	//check whether the shader loads fine
	int status = 0;
	glGetShaderiv(m_shaders[a_type], GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) 
	{
		int infoLogLength = 0;		
		glGetShaderiv(m_shaders[a_type], GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog= new char[infoLogLength];

		glGetShaderInfoLog(m_shaders[a_type], infoLogLength, 0, infoLog);
		printf("Shader Log:\n");
		printf(infoLog);
		printf("\n");
		delete[] infoLog;
	}
#endif
}

bool ShaderProgram::LinkProgram()
{
	m_program = glCreateProgram();
	for (auto shader : m_shaders)
		glAttachShader(m_program, shader.second);
	glLinkProgram(m_program);

	//link and check whether the program links fine
	int status = 0;
	glGetProgramiv(m_program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
#ifdef _DEBUG
		int infoLogLength = 0;		
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog= new char[infoLogLength];

		glGetProgramInfoLog(m_program, infoLogLength, 0, infoLog);
		OutputDebugStringA(infoLog);
		printf("Program Log:\n");
		printf(infoLog);
		printf("\n");
		delete[] infoLog;
#endif
		return false;
	}
	return true;
}

int ShaderProgram::GetUniform(const char* a_uniform)
{
	return glGetUniformLocation(m_program, a_uniform);
}