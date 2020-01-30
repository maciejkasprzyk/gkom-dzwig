#define GLEW_STATIC
#include <GL/glew.h>
#include "Camera.h"
#include "Skybox.h"
#include "Leaf.h"
#include "Tree.h"
#include "shprogram.h"
#include "Object.h"
#include "Forest.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
using namespace std;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Constants.h"
#include "Cube.h"
#include "Crane.h"
#include "Cone.h"
#include "CraneBase.h"
#include "TextureHandler.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// cout << key << endl;
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

void processCubeInteraction(GLFWwindow* window, Cube& cube, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		cube.scale(glm::vec3(1.0f, 1.05f * deltaTime, 1.0f));
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		cube.scale(glm::vec3(1.0, 0.9f * deltaTime, 1.0f));
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		cube.rotate(glm::vec3(1.0f * deltaTime, 0.0f, 0.0f));
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		cube.rotate(glm::vec3(-1.0f * deltaTime, 0.0f, 0.0f));
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		cube.move(glm::vec3(0.0f, 0.05f * deltaTime, 0.0f));
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		cube.move(glm::vec3(0.0f, -0.05f * deltaTime, 0.0f));
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		cube.move(glm::vec3(0.0f, -0.05f * deltaTime, 0.0f));

}

void processCraneInteraction(GLFWwindow* window, Crane& crane, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		crane.rotateTop(true, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		crane.rotateTop(false, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		crane.forward(deltaTime);
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		crane.backwards(deltaTime);
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		crane.up(deltaTime);
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		crane.down(deltaTime);
}


int main()
{
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

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
		GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Dzwig", nullptr, nullptr);
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

		// camera setup
		glm::vec3 positionVec = glm::vec3(-3, 2, -3);
		float horizontalAngle = 0.785f;
		float verticalAngle = 0.0f;
		float initialFoV = 45.0f;
		float speed = 3.0f;
		float mouseSpeed = 0.005f;
		Camera camera = Camera(window, positionVec, horizontalAngle, verticalAngle, initialFoV, speed, mouseSpeed);

		//shaders
		ShaderProgram textureShaders("texture.vert", "texture.frag");
		ShaderProgram colorShaders("color.vert", "color.frag");
		ShaderProgram lightningShader("lights.vect", "lights.frag");
		ShaderProgram lampShader("lamp.vect", "lamp.frag");
		// -------------- objects -----------------
		// Ground
		Cube ground("gravel.jpg", 50);
		ground.scale(glm::vec3(100.0f, 1.0f, 100.0f));
		ground.move(glm::vec3(0.0f, -0.5f, 0.0f)); // podloga jest dokladnie na y = 0.0
		Cone cone(GREY);
		cone.move(glm::vec3(0.0f, 3.0f, 0.0f));
		// Cube
		Cube cube(YELLOW);
		cube.move(glm::vec3(10.0f, -3.0f, 5.0f));

		//Counterweights
		Cube concrete1("betonowy.jpg", 1);
		Cube concrete2("betonowy.jpg", 1);
		Cube concrete3("betonowy.jpg", 1);
		Cube concrete4("betonowy.jpg", 1);

		concrete1.scale(glm::vec3(1.3f, 0.2f, 0.4f));
		concrete1.move(glm::vec3(0.0f, 0.2f, 0.5f));

		concrete2.scale(glm::vec3(1.3f, 0.2f, 0.4f));
		concrete2.move(glm::vec3(0.0f, 0.2f, -0.5f));

		concrete3.scale(glm::vec3(1.3f, 0.2f, 0.4f));
		concrete3.move(glm::vec3(0.0f, 0.4f, 0.5f));
		concrete3.rotate2(glm::vec3(0.0f, 90.0f, 0.0f));

		concrete4.scale(glm::vec3(1.3f, 0.2f, 0.4f));
		concrete4.move(glm::vec3(0.0f, 0.4f, -0.5f));
		concrete4.rotate2(glm::vec3(0.0f, 90.0f, 0.0f));

		//Base of crane
		CraneBase base;
		
		// Crane
		Crane crane;

		Tree tree;
		tree.move2(glm::vec3(4.0f, 0.0f, 0.0f));
		//skybox
		auto skybox = Skybox();
		//lights
		auto pointLightPositions = {
			glm::vec3(0.7f,  0.2f,  2.0f),
			glm::vec3(2.3f, -3.3f, -4.0f),
			glm::vec3(-4.0f,  2.0f, -12.0f),
			glm::vec3(0.0f,  0.0f, -3.0f)
		};
		unsigned int diffuseMap = loadTexture("gravel.jpg");
		unsigned int specularMap = loadTexture("gravel.jpg");

		lightningShader.Use();
		lightningShader.setInt("material.diffuse", 0);
		lightningShader.setInt("material.specular", 1);
		auto forest = Forest();
		while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)
		{
			float currentFrame = glfwGetTime();
			deltaTime = (currentFrame - lastFrame) * 60.0f;
			lastFrame = currentFrame;
			std::cout << deltaTime << '\n';

			glClearColor(0.2f, 0.7f, 0.9f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			lightningShader.Use();
			lightningShader.setVec3("viewPos", camera.getPosition());
			lightningShader.setFloat("material.shininess", 32.0f);

			glDepthFunc(GL_LESS);
			camera.computeMatricesFromInputs();
			glm::mat4 view = camera.getViewMatrix();
			glm::mat4 projection = camera.getProjectionMatrix();

			processCubeInteraction(window, cube, deltaTime);
			processCraneInteraction(window, crane, deltaTime);

			textureShaders.Use();
			glUniformMatrix4fv(glGetUniformLocation(textureShaders.get_programID(), "view"),1, GL_FALSE, &view[0][0]);
			glUniformMatrix4fv(glGetUniformLocation(textureShaders.get_programID(), "projection"),1, GL_FALSE, &projection[0][0]);
			ground.draw(textureShaders.get_programID(), camera);
			concrete1.draw(textureShaders.get_programID(), camera);
			concrete2.draw(textureShaders.get_programID(), camera);
			concrete3.draw(textureShaders.get_programID(), camera);
			concrete4.draw(textureShaders.get_programID(), camera);
			forest.draw(colorShaders.get_programID(), camera);

			colorShaders.Use();
			glUniformMatrix4fv(glGetUniformLocation(colorShaders.get_programID(), "view"), 1, GL_FALSE, &view[0][0]);
			glUniformMatrix4fv(glGetUniformLocation(colorShaders.get_programID(), "projection"), 1, GL_FALSE, &projection[0][0]);
			cube.draw(colorShaders.get_programID(), camera);
			crane.draw(colorShaders.get_programID(), camera);
			base.draw(colorShaders.get_programID(), camera);
			skybox.draw(camera.getProjectionMatrix(), camera.getViewMatrix());
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