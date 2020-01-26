#ifndef ObjectHPP
#define ObjectHPP


#include <GL/glew.h>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include <iostream>

using namespace std;
class Object
{
public:
	GLfloat xPosition, yPosition, zPosition;
	GLfloat xRotation, yRotation, zRotation;
	GLuint texture0;
	GLuint VBO, EBO, VAO, indicesCounter;

	Object(string textureName, GLfloat x, GLfloat y, GLfloat z, GLfloat xRotate, GLfloat yRotate, GLfloat zRotate, GLfloat* vertices, GLuint* indices, int verticesSize, int indicesSize) {
		xPosition = x;
		yPosition = y;
		zPosition = z;
		xRotation = xRotate;
		yRotation = yRotate;
		zRotation = zRotate;
			
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

		// Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		// Color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		// TexCoord 
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		// normal 
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(8 * sizeof(GLfloat)));
		glEnableVertexAttribArray(3);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

		// prepare textures 
		GLuint texture;
		glGenTextures(1, &texture);

		// texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Load texture and generate mipmaps
		cout << "Nazwa tekstury: " << textureName.c_str() << endl;
		int width, height;
		unsigned char* image = SOIL_load_image(textureName.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		if (image == nullptr) {
			throw exception("Failed to load texture file");
		}

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

		glGenerateMipmap(GL_TEXTURE_2D);

		SOIL_free_image_data(image);

		glBindTexture(GL_TEXTURE_2D, 0);

		texture0 = texture;

		indicesCounter = indicesSize / (sizeof(GLfloat));
	}

	~Object() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

	void draw(int programId, Camera camera, int screenWidth, int screenHeight) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0);
		glUniform1i(glGetUniformLocation(programId, "Texture0"), 0);

		glm::mat4 projection;
		projection = camera.getProjectionMatrix();

		glm::mat4 view;
		view = camera.getViewMatrix();

		GLint modelLoc = glGetUniformLocation(programId, "model");
		GLint viewLoc = glGetUniformLocation(programId, "view");
		GLint projLoc = glGetUniformLocation(programId, "projection");

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(VAO);

		glm::mat4 model;
		glm::mat4 translation;
		glm::mat4 rotationX;
		glm::mat4 rotationY;
		glm::mat4 rotationZ;
		glm::mat4 constRot;

		translation = glm::translate(translation, glm::vec3(xPosition, yPosition, zPosition));
		rotationX = glm::rotate(rotationX, glm::radians(xRotation), glm::vec3(1.0f, 0.0f, 0.0f));
		rotationY = glm::rotate(rotationY, glm::radians(yRotation), glm::vec3(0.0f, 1.0f, 0.0f));
		rotationZ = glm::rotate(rotationZ, glm::radians(zRotation), glm::vec3(0.0f, 0.0f, 1.0f));
		constRot = glm::rotate(constRot, glm::radians(5.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		model = translation * rotationX * rotationY * rotationZ;

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, indicesCounter, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void rotate(int progid, float anglePS, float FPS, string rotationType)
	{
		if (rotationType == "vertical") {
			this->yRotation += (anglePS / FPS);
			if (this->yRotation > 360.0f)
				this->yRotation -= 360.0f;
		}
		else if (rotationType == "horizontal") {
			this->zRotation += (anglePS / FPS);
			if (this->zRotation > 360.0f)
				this->zRotation -= 360.0f;
		}
	}
};

#endif