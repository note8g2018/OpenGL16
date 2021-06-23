#include "Camera.h"

float Camera::speed_factor = 1.0;

Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform)
{
	// Initializes matrices since otherwise they will be the null matrix
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// Makes camera look in the right direction from the right position
	view = glm::lookAt(Position, Position + Orientation, Up);
	// Adds perspective to the scene
	projection = glm::perspective(glm::radians(FOVdeg), (float) width / height, nearPlane, farPlane);

	// Exports the camera matrix to the Vertex Shader
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}



void Camera::Inputs(GLFWwindow* window, float deltaTime)
{
	float speed = deltaTime * speed_initial * speed_factor;
	// Handles key inputs
	// Camera go Forward
	if(glfwGetKey(window, GLFW_KEY_W)|| glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS)
	{
		Position += speed * Orientation;
	}
	// Camera go to the Left
	if(glfwGetKey(window, GLFW_KEY_A) || glfwGetKey(window, GLFW_KEY_KP_7) == GLFW_PRESS)
	{
		Position += speed * -glm::normalize(glm::cross(Orientation, Up));
	}
	// Camera go Backward
	if(glfwGetKey(window, GLFW_KEY_S) || glfwGetKey(window, GLFW_KEY_KP_5) == GLFW_PRESS)
	{
		Position += speed * -Orientation;
	}
	// Camera go to the Right
	if(glfwGetKey(window, GLFW_KEY_D) || glfwGetKey(window, GLFW_KEY_KP_9) == GLFW_PRESS)
	{
		Position += speed * glm::normalize(glm::cross(Orientation, Up));
	}
	// Camera go UP
	if(glfwGetKey(window, GLFW_KEY_SPACE) || glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS)
	{
		Position += speed * Up;
	}
	// Camera go DWON
	if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) || glfwGetKey(window, GLFW_KEY_KP_1) == GLFW_PRESS)
	{
		Position += speed * -Up;
	}
	// To increase the speed of Movement of the Camera
	if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		//shift_press = true;
		//speed_factor = 50.0f;
	}
	// To return the speed of Movement of the Camera to Normal
	else if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		//shift_press = false;
		//speed_factor = 1.0f;
	}



	// Handles mouse inputs
	if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// Hides mouse cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera from jumping on the first click
		if(firstClick)
		{
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}

		// Stores the coordinates of the cursor
		double mouseX;
		double mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Normalizes and shifts the coordinates of the cursor such that 
		// they begin in the middle of the screen
		// and then "transforms" them into degrees 
		float rotX = sensitivity * (float) (mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float) (mouseX - (width / 2)) / width;

		// Calculates upcoming vertical change in the Orientation
		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		// Decides whether or not the next vertical Orientation is legal or not
		if(abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			Orientation = newOrientation;
		}

		// Rotates the Orientation left and right
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

		// Sets mouse cursor to the middle of the screen so that 
		//it doesn't end up roaming around
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		firstClick = true;
	}
}