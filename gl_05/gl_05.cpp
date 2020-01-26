#define GLEW_STATIC
#include <GL/glew.h>
#include "Camera.h"
#include "shprogram.h"
#include "Object.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
using namespace std;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
GLFWwindow* window;

GLuint LoadMipmapTexture(GLuint texId, const char* fname);
GLfloat* myObjectVertices(unsigned int& size);
GLuint* myObjectIndices(unsigned int& size);

const GLuint WIDTH = 800, HEIGHT = 600;


//camera
glm::vec3 position = glm::vec3(0, 0, 0);
float horizontalAngle = 3.14f;
float verticalAngle = 0.0f;
float initialFoV = 45.0f;
float speed = 3.0f;
float mouseSpeed = 0.005f;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

ostream& operator<<(ostream& os, const glm::mat4& mx)
{
	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
			cout << mx[row][col] << ' ';
		cout << endl;
	}
	return os;
}

int main()
{
	{
		glm::mat4 trans;
		cout << trans << endl;
		trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
		cout << trans << endl;
	}
	if (glfwInit() != GL_TRUE)
	{
		cout << "GLFW initialization failed" << endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	try
	{

		window = glfwCreateWindow(WIDTH, HEIGHT, "GKOM - OpenGL 05", nullptr, nullptr);

		if (window == nullptr)
			throw exception("GLFW window not created");
		glfwMakeContextCurrent(window);
		glfwSetKeyCallback(window, key_callback);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			throw exception("GLEW Initialization failed");

		glViewport(0, 0, WIDTH, HEIGHT);

		GLint nrAttributes;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
		cout << "Max vertex attributes allowed: " << nrAttributes << std::endl;
		glGetIntegerv(GL_MAX_TEXTURE_COORDS, &nrAttributes);
		cout << "Max texture coords allowed: " << nrAttributes << std::endl;

		// Build, compile and link shader program
		ShaderProgram theProgram("gl_05.vert", "gl_05.frag");

		unsigned int verticesSize, indicesSize;
		GLuint* indicesMyObject = myObjectIndices(indicesSize);
		GLfloat* verticesMyObject = myObjectVertices(verticesSize);

		Object whyItDoesNotWorkFFS = Object("grass.png", 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, verticesMyObject, indicesMyObject, verticesSize, indicesSize);

		Camera camera = Camera(position, horizontalAngle, verticalAngle, initialFoV, speed, mouseSpeed);
		// main event loop
		do
		{
			camera.computeMatricesFromInputs();
			glfwPollEvents();
			glClearColor(0.2f, 0.7f, 0.9f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			theProgram.Use();

			whyItDoesNotWorkFFS.draw(theProgram.get_programID(), camera, WIDTH, HEIGHT);

			// Use our shader
			glUseProgram(theProgram.get_programID());

			glfwSwapBuffers(window);

		} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			glfwWindowShouldClose(window) == 0);
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
	glfwTerminate();

	return 0;
}

GLuint LoadMipmapTexture(GLuint texId, const char* fname)
{
	int width, height;
	unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == nullptr)
		throw exception("Failed to load texture file");

	GLuint texture;
	glGenTextures(1, &texture);

	glActiveTexture(texId);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}




GLfloat* myObjectVertices(unsigned int& size) {
	static GLfloat vertices[] = {
			0.25f,  0.5f,  -0.5f,	1.0f, 0.0f, 0.0f,	1.0f,  0.0f,	//0
			-0.75f,  0.5f,  -0.5f,	0.0f, 1.0f, 0.0f,	0.0f,  0.0f,	//1
			-0.25f, -0.5f,  -0.5f,	0.0f, 0.0f, 1.0f,	0.0f,  1.0f,	//2
			0.75f, -0.5f,  -0.5f,	1.0f, 0.0f, 1.0f,	1.0f,  1.0f,	//3
			-0.25f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	0.0f,  0.0f,	//4
			-0.75f,  0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	0.0f,  1.0f,	//5
			0.25f,  0.5f,  0.5f,	1.0f, 0.0f, 0.0f,	1.0f,  1.0f,	//6
			0.75f, -0.5f,  0.5f,	1.0f, 0.0f, 1.0f,	1.0f,  0.0f,	//7
			-0.25f, -0.5f,  -0.5f,	0.0f, 0.0f, 1.0f,	0.0f,  0.0f,	//8
			-0.25f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	0.0f,  1.0f,	//9
			0.75f, -0.5f,  0.5f,	1.0f, 0.0f, 1.0f,	1.0f,  1.0f,	//10
			0.75f, -0.5f,  -0.5f,	1.0f, 0.0f, 1.0f,	1.0f,  0.0f,	//11
			-0.75f,  0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	0.0f,  0.0f,	//12
			-0.75f,  0.5f,  -0.5f,	0.0f, 1.0f, 0.0f,	0.0f,  1.0f,	//13
			0.25f,  0.5f,  -0.5f,	1.0f, 0.0f, 0.0f,	1.0f,  1.0f,	//14
			0.25f,  0.5f,  0.5f,	1.0f, 0.0f, 0.0f,	1.0f,  0.0f,	//15
			-0.25f, -0.5f,  -0.5f,	0.0f, 0.0f, 1.0f,	0.0f,  0.0f,	//16
			-0.75f,  0.5f,  -0.5f,	0.0f, 1.0f, 0.0f,	0.0f,  1.0f,	//17
			-0.25f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	1.0f,  0.0f,	//18
			-0.75f,  0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	1.0f,  1.0f,	//19
			0.75f, -0.5f,  -0.5f,	1.0f, 0.0f, 1.0f,	1.0f,  0.0f,	//20
			0.75f, -0.5f,  0.5f,	1.0f, 0.0f, 1.0f,	0.0f,  0.0f,	//21
			0.25f,  0.5f,  0.5f,	1.0f, 0.0f, 0.0f,	0.0f,  1.0f,	//22
			0.25f,  0.5f,  -0.5f,	1.0f, 0.0f, 0.0f,	1.0f,  1.0f		//23
	};
	size = sizeof(vertices);
	return vertices;
}

GLuint* myObjectIndices(unsigned int& size) {
	static GLuint indices[] = {
	0, 1, 2,
	0, 2, 3
	};
	size = sizeof(indices);
	return indices;
}