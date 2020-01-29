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
		ShaderProgram shaders("gl_05.vert", "gl_05.frag");

		unsigned int verticesSize, indicesSize;
		GLuint* indicesMyObject = myObjectIndices(indicesSize);
		GLfloat* verticesMyObject = myObjectVertices(verticesSize);

		Object whyItDoesNotWorkFFS = Object("grass.png", 2.0f, 2.0f, 2.0f, 1.0f, 0.0f, 0.0f, verticesMyObject, indicesMyObject, verticesSize, indicesSize);

		Camera camera = Camera(position, horizontalAngle, verticalAngle, initialFoV, speed, mouseSpeed);
		// main event loop
		do
		{
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);


			camera.computeMatricesFromInputs();
			glfwPollEvents();
			glClearColor(0.2f, 0.7f, 0.9f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			shaders.Use();

			whyItDoesNotWorkFFS.draw(shaders.get_programID(), camera, WIDTH, HEIGHT);


			glfwSwapBuffers(window);

			glClear(GL_DEPTH_BUFFER_BIT);

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





GLfloat* myObjectVertices(unsigned int& size) {
	static GLfloat vertices[] = {
			 0.5f,  0.5f,  -0.5f,		0.0f, 0.0f, 0.0f,	1.0f,  0.0f,	//0
			-0.5f,  0.5f,  -0.5f,		0.0f, 0.0f, 0.0f,	0.0f,  0.0f,	//1
			-0.5f, -0.5f,  -0.5f,		0.0f, 0.0f, 0.0f,	0.0f,  1.0f,	//2
			0.5f, -0.5f,  -0.5f,		0.0f, 0.0f, 0.0f,	1.0f,  1.0f,	//3
			-0.5f, -0.5f,  0.5f,		0.0f, 0.0f, -1.0f,	0.0f,  0.0f,	//4
			-0.5f,  0.5f,  0.5f,		0.0f, 0.0f, -1.0f,	0.0f,  1.0f,	//5
			0.5f,  0.5f,  0.5f,			0.0f, 0.0f, -1.0f,	1.0f,  1.0f,	//6
			0.5f, -0.5f,  0.5f,			0.0f, 0.0f, -1.0f,	1.0f,  0.0f,	//7
			-0.5f, -0.5f,  -0.5f,		0.0f, 1.0f, 0.0f,	0.0f,  0.0f,	//8
			-0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,	0.0f,  1.0f,	//9
			0.5f, -0.5f,  0.5f,			0.0f, 1.0f, 0.0f,	1.0f,  1.0f,	//10
			0.5f, -0.5f,  -0.5f,		0.0f, 1.0f, 0.0f,	1.0f,  0.0f,	//11
			-0.5f,  0.5f,  0.5f,		0.0f, -1.0f, 0.0f,	0.0f,  0.0f,	//12
			-0.5f,  0.5f,  -0.5f,		0.0f, -1.0f, 0.0f,	0.0f,  1.0f,	//13
			0.5f,  0.5f,  -0.5f,		0.0f, -1.0f, 0.0f,	1.0f,  1.0f,	//14
			0.5f,  0.5f,  0.5f,			0.0f, -1.0f, 0.0f,	1.0f,  0.0f,	//15
			-0.5f, -0.5f,  -0.5f,		1.0f, 0.0f, 0.0f,	0.0f,  0.0f,	//16
			-0.5f,  0.5f,  -0.5f,		1.0f, 0.0f, 0.0f,	0.0f,  1.0f,	//17
			-0.5f,  0.5f,  0.5f,		1.0f, 0.0f, 0.0f,	1.0f,  1.0f,	//19
			-0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 0.0f,	1.0f,  0.0f,	//18
			0.5f, -0.5f,  -0.5f,		-1.0f, 0.0f, 0.0f,	1.0f,  0.0f,	//20
			0.5f, -0.5f,  0.5f,			-1.0f, 0.0f, 0.0f,	0.0f,  0.0f,	//21
			0.5f,  0.5f,  0.5f,			-1.0f, 0.0f, 0.0f,	0.0f,  1.0f,	//22
			0.5f,  0.5f,  -0.5f,		-1.0f, 0.0f, 0.0f,	1.0f,  1.0f		//23
	};
	size = sizeof(vertices);
	return vertices;
}

GLuint* myObjectIndices(unsigned int& size) {
	static GLuint indices[] = {
	0,1,2,
	0,2,3,
	4,5,6,
	4,6,7,
	8,9,10,
	8,10,11,
	12,13,14,
	12,14,15,
	16,17,18,
	16,18,19,
	20,21,22,
	20,22,23
	};
	size = sizeof(indices);
	return indices;
}

GLfloat* groundVertices(unsigned int& size) {
	static GLfloat vertices[] = {
		// coordinates			// color				// texture			//normals
		6.0f, 0.0f,  6.0f,		1.0f, 0.0f, 0.0f,		20.0f,  0.0f,	0.0f, 1.0f, 0.0f,
	   -6.0f, 0.0f,  6.0f,		0.0f, 1.0f, 0.0f,		0.0f,  0.0f,	0.0f, 1.0f, 0.0f,
	   -6.0f, 0.0f, -6.0f,		0.0f, 0.0f, 1.0f,		0.0f,  20.0f,	0.0f, 1.0f, 0.0f,
		6.0f, 0.0f, -6.0f,		1.0f, 0.0f, 1.0f,		20.0f, 20.0f,	0.0f, 1.0f, 0.0f
	};

	size = sizeof(vertices);
	return vertices;
}

GLuint* groundIndices(unsigned int& size) {
	static GLuint indices[] = {
		0, 1, 2,
		0, 2, 3
	};
	size = sizeof(indices);
	return indices;
}