#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>	

// funkcje pomocnicze
string read_shader_code(const GLchar* shaderPath);
GLuint compile_shader(const GLchar* shaderCode, GLenum shaderType);

class ShaderProgram
{
	GLuint program_id; 	// The program ID
public:
	// Constructor reads and builds the shader
	ShaderProgram(const GLchar* vertexPath, const GLchar* fragmentPath)
	{
		// prepare vertex and fragment shaders
		string vertex_code = read_shader_code(vertexPath);
		GLuint vertex_id = compile_shader(vertex_code.c_str(), GL_VERTEX_SHADER);

		string fragment_code = read_shader_code(fragmentPath);
		GLuint fragment_id = compile_shader(fragment_code.c_str(), GL_FRAGMENT_SHADER);

		// link shader program
		program_id = glCreateProgram();
		glAttachShader(program_id, vertex_id);
		glAttachShader(program_id, fragment_id);
		glLinkProgram(program_id);

		// Print linking errors if any
		GLint success;
		glGetProgramiv(program_id, GL_LINK_STATUS, &success);
		if (!success)
		{
			GLchar infoLog[512];
			glGetProgramInfoLog(program_id, sizeof(infoLog), NULL, infoLog);
			string msg = string("Shader program linking: ") + infoLog;
			throw exception(msg.c_str());
		}

		// Delete the shaders as they're linked into our program now and no longer necessery
		glDeleteShader(vertex_id);
		glDeleteShader(fragment_id);
	}

	// Use the program
	void Use() const
	{
		glUseProgram(get_programID());
	}

	// returns program ID
	GLuint get_programID() const
	{
		return program_id;
	}
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(program_id, name.c_str()), value);
	}
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(program_id, name.c_str()), value);
	}
	void setVec2(const std::string& name, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(program_id, name.c_str()), 1, &value[0]);
	}
	void setVec2(const std::string& name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(program_id, name.c_str()), x, y);
	}
	// ------------------------------------------------------------------------
	void setVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(program_id, name.c_str()), 1, &value[0]);
	}
	void setVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(program_id, name.c_str()), x, y, z);
	}
	void setMat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(program_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	void setTransformMatrix(const std::string& name, glm::mat4 matrix) {
		glUniformMatrix4fv(glGetUniformLocation(program_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
	}
};


// poza klasa
string read_shader_code(const GLchar* shaderPath)
{
	ifstream shader_file;
	shader_file.exceptions(ifstream::badbit);

	shader_file.open(shaderPath);
	stringstream shader_stream;
	shader_stream << shader_file.rdbuf();
	shader_file.close();
	return shader_stream.str();
}

GLuint compile_shader(const GLchar* shaderCode, GLenum shaderType)
{
	GLuint shader_id = glCreateShader(shaderType);
	glShaderSource(shader_id, 1, &shaderCode, NULL);
	glCompileShader(shader_id);

	// Print compile errors if any
	GLint success = 0;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(shader_id, sizeof(infoLog), NULL, infoLog);
		string msg = string("Shader compilation: ") + infoLog;
		throw exception(msg.c_str());
	}
	return shader_id;
}
