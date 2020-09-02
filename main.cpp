#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <iostream>
#include "math.h"

const int width_window = 640;
const int height_window = 480;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
int main(void)
{
	GLFWwindow *window = nullptr;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width_window, height_window, "Hello World", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// callbacks here
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(-50, -50, width, height);
	// glOrtho(0, 1, 0, 1, -1.0, 1.0);
	const float aspect_ratio = (float)width/(float)height;
	glOrtho(-1, 1, -1 / aspect_ratio, 1 / aspect_ratio, -1.0, 1.0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClearColor(0.0f, 0.5f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//TODO: draw here
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.5, 0.0, 0.0);
		// center of polygonized circle
		glVertex2f(0.0, 0.0);

		const int num_triangles = 1000;
		const float dtheta = 2.0 * 3.141592	/ (float)num_triangles;
		const float radius = 0.5;

		float theta = 0.0;
		for (int i = 0; i <=num_triangles; i++, theta += dtheta)
		{
			const float x = radius * cos(theta);
			const float y = radius * sin(theta);
			glVertex2f(x, y);
		}

		glEnd();
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	return 0;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		std::cout << "button clicked" << std::endl;
	}
}