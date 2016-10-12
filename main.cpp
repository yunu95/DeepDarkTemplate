#define _SCL_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"
#include <cmath>
#include <iostream>
#include <vector>

/*
Below are GLFW Related Modules
*/
const int width = 640;
const int height = 480;

float* pixels = new float[width*height * 3];

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

void drawLine(const int& x0, const int& y0, const int& x1, const int& y1, const float& red, const float& green, const float& blue)
{
	const int i0 = (int)fmin(x0, x1);
	const int i1 = (int)fmax(x0, x1);
	int j0 = y0;
	int j1 = y1;

	if (i0 != x0)
	{
		j0 = y1;
		j1 = y0;
	}
	if (i0 != i1)
		for (int i = i0; i <= i1; i++)
		{
			const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

			drawPixel(i, j, red, green, blue);
		}
	else
		for (int i = j0; i <= j1; i++)
		{
			drawPixel(i0, i, red, green, blue);
		}
}

void drawOnPixelBuffer()
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background

													//for (int i = 0; i<width*height; i++) {
													//	pixels[i * 3 + 0] = 1.0f; // red 
													//	pixels[i * 3 + 1] = 1.0f; // green
													//	pixels[i * 3 + 2] = 1.0f; // blue
													//}

	const int i = rand() % width, j = rand() % height;
	drawPixel(i, j, 0.0f, 0.0f, 0.0f);

	// drawing a line
	//TODO: anti-aliasing
	//const int i0 = 100, i1 = 200;
	//const int j0 = 50, j1 = 80;
	//drawLine(i0, j0, i1, j1, 1.0f, 0.0f, 0.0f);

	//TODO: try moving object
}
/////////////////////////////////////////////////////////////////////////////////////////***************************************************************************************
/*
From now on, the Code related with assignments
*/
// Problem 1
template<typename T>
void print(const T& argument) {
	std::cout << argument << '\n';
}
// Problem 2
template<typename Value>
class Vector2D {
public:
	Value x, y;
	Vector2D(Value x, Value y) : x(x), y(y) {
		//this->x = x;
		//this->y = y;
	}
	Vector2D() {}
};
// Problem 3
class Box // NO PARENT
{
public:
	// some variables
	void draw()
	{
		// draw box here
		drawLine(100, 300, 200, 300, 0, 0, 0);
		drawLine(100, 400, 200, 400, 0, 0, 0);
		drawLine(100, 300, 100, 400, 0, 0, 0);
		drawLine(200, 300, 200, 400, 0, 0, 0);
	}
};
class Circle // NO PARENT
{
public:
	// some variables
	void draw()
	{
		// draw circle here
		for (int i = 0; i <= 360; i++) {
			drawPixel(550 + 50 * cos(i), 150 + 50 * sin(i), 0, 0, 0);
		}
	}
};
class GeometricObjectInterface
{
public:
	virtual void draw() = 0;
};

template<typename T>
class GeometricObject :public GeometricObjectInterface
{
public:
	T shape;
	void draw() {
		shape.draw();
	}
};
// Old codes after this
//***************************************************************************************///////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background
	/////////////////////////////////////////////////////////////////////////////////////////***************************************************************************************
	/*
	From now on, Assignment Related Calls appear
	*/
	//Problem 1
	print(1);
	print(1.123f);
	print("Hello world!");
	// Old codes after this
	//***************************************************************************************///////////////////////////////////////////////////////////////////////////////////////
		/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);

		drawOnPixelBuffer();

		//TODO: RGB struct
		//Make a pixel drawing function
		//Make a line drawing function
		/////////////////////////////////////////////////////////////////////////////////////////***************************************************************************************
		/*
		From now on, Assignment Related Calls appear
		*/
		// Problem 3.
		std::vector<GeometricObjectInterface*> obj_list;
		obj_list.push_back(new GeometricObject<Circle>);
		obj_list.push_back(new GeometricObject<Box>);
		for (auto itr : obj_list)
			itr->draw();
		// Old codes after this
		//***************************************************************************************///////////////////////////////////////////////////////////////////////////////////////
		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}