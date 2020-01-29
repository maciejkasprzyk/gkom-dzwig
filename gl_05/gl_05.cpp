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
#include "Constants.h"
#include "Cube.h"


GLfloat* myObjectVertices(unsigned int& scaleVec);
GLuint* myObjectIndices(unsigned int& scaleVec);


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
		GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "GKOM - OpenGL 05", nullptr, nullptr);
		if (window == nullptr)
			throw exception("GLFW window not created");

		glfwMakeContextCurrent(window);
		glfwSetKeyCallback(window, key_callback);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			throw exception("GLEW Initialization failed");

		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		glEnable(GL_DEPTH_TEST);

		GLint nrAttributes;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
		cout << "Max vertex attributes allowed: " << nrAttributes << std::endl;
		glGetIntegerv(GL_MAX_TEXTURE_COORDS, &nrAttributes);
		cout << "Max texture coords allowed: " << nrAttributes << std::endl;


		// Build, compile and link shader program
		ShaderProgram shaders("gl_05.vert", "gl_05.frag");
		shaders.Use();

		glm::vec3 positionVec = glm::vec3(-10, 2, -10);
		float horizontalAngle = 0.785f;
		float verticalAngle = 0.0f;
		float initialFoV = 45.0f;
		float speed = 3.0f;
		float mouseSpeed = 0.005f;
		Camera camera = Camera(window, positionVec, horizontalAngle, verticalAngle, initialFoV, speed, mouseSpeed);

		// main event loop

		Cube ground("gravel.jpg", 50);
		ground.scale(glm::vec3(100.0f, 0.001f, 100.0f));

		Cube cube("gravel.jpg", 1);
		cube.scale(glm::vec3(2.0f, 3.0f, 1.0f));
		cube.rotate(glm::vec3(45.0f, 3.0f, 1.0f));
		cube.move(glm::vec3(0.0f, 5.0f, 0.0f));

		while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)
		{
			glClearColor(0.2f, 0.7f, 0.9f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			camera.computeMatricesFromInputs();
			glm::mat4 view = camera.getViewMatrix();
			glm::mat4 projection = camera.getProjectionMatrix();
			glUniformMatrix4fv(glGetUniformLocation(shaders.get_programID(), "view"),1, GL_FALSE, &view[0][0]);
			glUniformMatrix4fv(glGetUniformLocation(shaders.get_programID(), "projection"),1, GL_FALSE, &projection[0][0]);
			
			cube.draw(shaders.get_programID(), camera);
			ground.draw(shaders.get_programID(), camera);


			glfwPollEvents();
			glfwSwapBuffers(window);
		} ;
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
	glfwTerminate();

	return 0;
}