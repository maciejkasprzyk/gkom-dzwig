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
#include "Fence.h"
#include "Fence2.h"
#include "Counterweights.h"

void renderQuad();
void renderCube();
void renderScene(const ShaderProgram& shader);
void draw_colored(ShaderProgram& shader, Camera& camera);
void draw_textured(ShaderProgram& shader, Camera& camera);

unsigned int planeVAO;
float near_plane = -12.0f, far_plane = 11.0f;
float orth = 27.0f;


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
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
		near_plane += 0.1f;
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		near_plane -= 0.1f;
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		far_plane += 0.1f;
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		far_plane -= 0.1f;
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		orth += 0.1f;
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		orth -= 0.1f;




}

void processCraneInteraction(GLFWwindow* window, Crane& crane, float deltaTime, Counterweights& counterweights)
{
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		crane.rotateTop(true, deltaTime);
		counterweights.rotate2(glm::vec3(0.0f, 0.5f, 0.0f) * deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		counterweights.rotate2(glm::vec3(0.0f, -0.5f, 0.0f) * deltaTime);
		crane.rotateTop(false, deltaTime);
	}
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
		glm::vec3 positionVec = glm::vec3(-4, 8, -2);
		float horizontalAngle = 0.785f;
		float verticalAngle = 0.0f;
		float initialFoV = 45.0f;
		float speed = 10.0f;
		float mouseSpeed = 0.005f;
		Camera camera = Camera(window, positionVec, horizontalAngle, verticalAngle, initialFoV, speed, mouseSpeed);

		//shaders
		ShaderProgram textureShaders("texture.vert", "texture.frag");
		ShaderProgram colorShaders("color.vert", "color.frag");
		ShaderProgram simpleDepthShader("shadow.vert", "shadow.frag");
		ShaderProgram debugDepthQuad("debug.vert", "debug.frag");
		// configure depth map FBO
		// -----------------------
		const unsigned int SHADOW_WIDTH = 4096, SHADOW_HEIGHT = 4096;
		unsigned int depthMapFBO;
		glGenFramebuffers(1, &depthMapFBO);
		// create depth texture
		unsigned int depthMap;
		glGenTextures(1, &depthMap);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// attach depth texture as FBO's depth buffer
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);


		// shader configuration
		// --------------------
		debugDepthQuad.use();
		debugDepthQuad.setInt("depthMap", 0);

		
		// set up vertex data (and buffer(s)) and configure vertex attributes
		// ------------------------------------------------------------------
		float planeVertices[] = {
			// positions            // normals         // texcoords
			 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
			-25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
			-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

			 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
			-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
			 25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 10.0f
		};

		// -------------- objects -----------------
	
		// plane VAO
		unsigned int planeVBO;
		glGenVertexArrays(1, &planeVAO);
		glGenBuffers(1, &planeVBO);
		glBindVertexArray(planeVAO);
		glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glBindVertexArray(0);

		// -------------- objects -----------------
		Cube concrete1("betonowy.jpg", 1);
		Cube concrete2("betonowy.jpg", 1);
		Cube concrete3("betonowy.jpg", 1);
		Cube concrete4("betonowy.jpg", 1);
		Cube ground("grass_tex.jpg", 16);
		Cube ground2("gravel.jpg", 4);
		Cube cube(YELLOW);
		CraneBase base;
		Crane crane;
		Forest forest;
		Fence fence;
		Counterweights counterweights;

		auto fence1 = Fence2();
		auto fence3 = Fence2();
		fence1.rotate2(glm::vec3(0.0f, 90.0f, 0.0f));
	

		fence1.move2(glm::vec3(-1.7f, 0.0f, -3.5f));
		fence3.move2(glm::vec3(-2.7f, 0.0f, -4.5f));

		fence1.move2(glm::vec3(12.0f, 0.0f, 15.0f));
		fence3.move2(glm::vec3(12.0f, 0.0f, 15.0f));


		ground.scale(glm::vec3(40.0f, 1.0f, 40.0f));
		ground.move(glm::vec3(0.0f, -0.5f, 0.0f)); // podloga jest dokladnie na y = 0.0
		
		ground2.scale(glm::vec3(12.0f, 1.0f, 12.0f));
		ground2.move(glm::vec3(0.0f, -0.499f, 0.0f));
	
		cube.move(glm::vec3(10.0f, -3.0f, 5.0f));
		
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

		forest.move2(glm::vec3(15.0, 0.0f, 15.0f));

		//skybox
		auto skybox = Skybox();
	
		while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)
		{
			float currentFrame = glfwGetTime();
			deltaTime = (currentFrame - lastFrame) * 60.0f;
			lastFrame = currentFrame;

			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// glDepthFunc(GL_LESS); czy to potrzebne? 
			camera.computeMatricesFromInputs();
			glm::mat4 view = camera.getViewMatrix();
			glm::mat4 projection = camera.getProjectionMatrix();

			processCubeInteraction(window, cube, deltaTime);
			processCraneInteraction(window, crane, deltaTime, counterweights);

			// tutaj koncza sie czynnosci przygotowujace
			// 1. render depth of scene to texture (from light's perspective)
			// --------------------------------------------------------------
	


			glm::vec3 lightPos(2.0f, 4.0f, 1.0f);

			glm::mat4 lightProjection, lightView;
			glm::mat4 lightSpaceMatrix;
			cout << near_plane << " " << far_plane << " " << orth << endl;
			lightProjection = glm::ortho(-orth, orth, -orth, orth, near_plane, far_plane);
			lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
			lightSpaceMatrix = lightProjection * lightView;
			// render scene from light's point of view
			simpleDepthShader.use();
			simpleDepthShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);

			glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
			glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
			glClear(GL_DEPTH_BUFFER_BIT);
			
			auto& shader = simpleDepthShader;
		    ground.draw(shader.get_programID(), camera);
			ground2.draw(shader.get_programID(), camera);
			concrete1.draw(shader.get_programID(), camera);
			concrete2.draw(shader.get_programID(), camera);
			concrete3.draw(shader.get_programID(), camera);
			concrete4.draw(shader.get_programID(), camera);
			forest.draw(shader.get_programID(), camera);
			fence.draw(shader.get_programID(), camera);
			fence1.draw(shader.get_programID(), camera);
			fence3.draw(shader.get_programID(), camera);
			counterweights.draw(shader.get_programID(), camera);
			// kolorwe
			cube.draw(shader.get_programID(), camera);
			crane.draw(shader.get_programID(), camera);
			base.draw(shader.get_programID(), camera);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			// reset viewport
			glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			// skonczylismy renederowac mape cienia
			// 2. render scene as normal using the generated depth/shadow map  
			// --------------------------------------------------------------
			textureShaders.use();
			//textureShaders.setVec3("viewPos", camera.Position); to do swiatla -> niepotrzebne
			textureShaders.setVec3("lightPos", lightPos);
			textureShaders.setMat4("lightSpaceMatrix", lightSpaceMatrix);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, depthMap);
			textureShaders.setMat4("view", view);
			textureShaders.setMat4("projection", projection);
			textureShaders.setInt("shadowMap", 0);

			ground.draw(textureShaders.get_programID(), camera);
			ground2.draw(textureShaders.get_programID(), camera);
			concrete1.draw(textureShaders.get_programID(), camera);
			concrete2.draw(textureShaders.get_programID(), camera);
			concrete3.draw(textureShaders.get_programID(), camera);
			concrete4.draw(textureShaders.get_programID(), camera);
			fence.draw(textureShaders.get_programID(), camera);
			forest.draw(colorShaders.get_programID(), camera);
			fence1.draw(colorShaders.get_programID(), camera);
			fence3.draw(colorShaders.get_programID(), camera);
			counterweights.draw(colorShaders.get_programID(), camera);
			// obiekty z kolorem ------------

			colorShaders.use();
			colorShaders.setVec3("lightPos", lightPos);
			colorShaders.setMat4("lightSpaceMatrix", lightSpaceMatrix);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, depthMap);
			colorShaders.setMat4("view", view);
			colorShaders.setMat4("projection", projection);
			colorShaders.setInt("shadowMap", 0);

			cube.draw(colorShaders.get_programID(), camera);
			crane.draw(colorShaders.get_programID(), camera);
			base.draw(colorShaders.get_programID(), camera);

			skybox.draw(camera.getProjectionMatrix(), camera.getViewMatrix());
			// render Depth map to quad for visual debugging
			// ---------------------------------------------
			debugDepthQuad.use();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, depthMap);
			//renderQuad();

			// koniec
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
/*
void draw_textured(ShaderProgram& shader, Camera& camera) {
	ground.draw(shader.get_programID(), camera);
	concrete1.draw(shader.get_programID(), camera);
	concrete2.draw(shader.get_programID(), camera);
	concrete3.draw(shader.get_programID(), camera);
	concrete4.draw(shader.get_programID(), camera);
	forest.draw(shader.get_programID(), camera);
}

void draw_colored(ShaderProgram& shader, Camera& camera) {
	cube.draw(shader.get_programID(), camera);
	crane.draw(shader.get_programID(), camera);
	base.draw(shader.get_programID(), camera);
}*/

// renderQuad() renders a 1x1 XY quad in NDC
// -----------------------------------------
unsigned int quadVAO = 0;
unsigned int quadVBO;
void renderQuad()
{
	if (quadVAO == 0)
	{
		float quadVertices[] = {
			// positions        // texture Coords
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		// setup plane VAO
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	}
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}


// renders the 3D scene
// --------------------
void renderScene(const ShaderProgram& shader)
{
	// floor
	glm::mat4 model = glm::mat4(1.0f);
	shader.setMat4("model", model);
	glBindVertexArray(planeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	// cubes
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
	model = glm::scale(model, glm::vec3(0.5f));
	shader.setMat4("model", model);
	renderCube();
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
	model = glm::scale(model, glm::vec3(0.5f));
	shader.setMat4("model", model);
	renderCube();
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 2.0));
	model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	model = glm::scale(model, glm::vec3(0.25));
	shader.setMat4("model", model);
	renderCube();
}


// renderCube() renders a 1x1 3D cube in NDC.
// -------------------------------------------------
unsigned int cubeVAO = 0;
unsigned int cubeVBO = 0;
void renderCube()
{
	// initialize (if necessary)
	if (cubeVAO == 0)
	{
		float vertices[] = {
			// back face
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
			 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
			 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
			 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
			-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
			// front face
			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
			 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
			 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
			 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
			-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
			// left face
			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
			-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
			-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
			// right face
			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
			 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
			 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
			// bottom face
			-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
			 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
			 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
			 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
			-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
			-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
			// top face
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
			 1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
			 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
			 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
			-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
		};
		glGenVertexArrays(1, &cubeVAO);
		glGenBuffers(1, &cubeVBO);
		// fill buffer
		glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// link vertex attributes
		glBindVertexArray(cubeVAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	// render Cube
	glBindVertexArray(cubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}