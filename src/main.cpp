/*
ZJ Wood CPE 471 Lab 3 base code - I. Dunn class re-write
*/

#include <iostream>
#include <glad/glad.h>

#include "GLSL.h"
#include "Program.h"
#include "MatrixStack.h"
#include "WindowManager.h"

// value_ptr for glm
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Application : public EventCallbacks
{

public:

	WindowManager * windowManager = nullptr;

	// Our shader program
	std::shared_ptr<Program> prog;

	// Contains vertex information for OpenGL
	GLuint VertexArrayID;
    GLuint VertexArrayIDtwo;

	// Data necessary to give our triangle to OpenGL
	GLuint VertexBufferID;

	void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}
    float p2wX(int xp) {
        int width, height;
        glfwGetFramebufferSize(windowManager->getHandle(), &width, &height);
        return ((xp-((float)width)/(float)4)/(((float)width)/4)) *((float)width/(float)height);
    }
    float p2wY(int yp) {
        int width, height;
        glfwGetFramebufferSize(windowManager->getHandle(), &width, &height);
        return -1*(yp-((float)height)/(float)4)/(((float)height)/4);
    }

	// callback for the mouse when clicked move the triangle when helper functions
	// written
	void mouseCallback(GLFWwindow *window, int button, int action, int mods)
	{
		double posX, posY;
		float newPt[2];
		if (action == GLFW_PRESS)
		{
			glfwGetCursorPos(window, &posX, &posY);
			std::cout << "Pos X " << posX <<  " Pos Y " << posY << std::endl;

			//change this to be the points converted to WORLD
			//THIS IS BROKEN< YOU GET TO FIX IT - yay!
            
            
			newPt[0] = p2wX(posX);
			newPt[1] = p2wY(posY);

			std::cout << "converted:" << newPt[0] << " " << newPt[1] << std::endl;
			glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
			//update the vertex array with the updated points
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*6, sizeof(float)*2, newPt);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}

	//if the window is resized, capture the new size and reset the viewport
	void resizeCallback(GLFWwindow *window, int in_width, int in_height)
	{
		//get the window size - may be different then pixels for retina
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
	}

	/*Note that any gl calls must always happen after a GL state is initialized */
	void initGeom()
	{
        GLuint colorbuffer;

		//generate the VAO
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);

		//generate vertex buffer to hand off to OGL
		glGenBuffers(1, &VertexBufferID);
		//set the current state to focus on our vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);

        GLfloat div = 240;
        static GLfloat g_vertex_buffer_data[720];
        GLfloat x;
        GLfloat y;
        
        for (int i = 0; i < 240; i++) {
            if (i % 3 == 0) {
                x = cos((i) * 2 * M_PI / div);
                y = sin((i) * 2 * M_PI / div);
                if (i == 0) {
                    g_vertex_buffer_data[i * 3] = x;
                    g_vertex_buffer_data[i * 3 + 1] = y;
                    g_vertex_buffer_data[i * 3 + 2] = 0.0f;
                }
                else {
                    //get the shared vertex. -6 -5 gets you right pos
                    g_vertex_buffer_data[i * 3] = g_vertex_buffer_data[i * 3 - 6];
                    g_vertex_buffer_data[i * 3 + 1] = g_vertex_buffer_data[i * 3 - 5];
                    g_vertex_buffer_data[i * 3 + 2] = 0.0f;
                }
            }
            else if (i % 3 == 1) {
                x = cos((i + 2) * 2 * M_PI / div);
                y = sin((i + 2) * 2 * M_PI / div);
            }
            else {
                x=0.0f;
                y=0.0f;
            }
            g_vertex_buffer_data[i * 3] = x;
            g_vertex_buffer_data[i * 3 + 1] = y;
            g_vertex_buffer_data[i * 3 + 2] = 0.0f;
            
        }
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_DYNAMIC_DRAW);
        
        //we need to set up the vertex array
        glEnableVertexAttribArray(0);
        //key function to get up how many elements to pull out at a time (3)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
        
        //VertexArrayIDtwo
        //generate the VAO
        glGenVertexArrays(1, &VertexArrayIDtwo);
        glBindVertexArray(VertexArrayIDtwo);
        //actually memcopy the data - only do this once
        
        //we need to set up the vertex array
        glEnableVertexAttribArray(0);
        //key function to get up how many elements to pull out at a time (3)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        
        glBindVertexArray(0);

	}

	//General OGL initialization - set OGL state here
	void init(const std::string& resourceDirectory)
	{
		GLSL::checkVersion();

		// Set background color.
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		// Enable z-buffer test.
		glEnable(GL_DEPTH_TEST);

		// Initialize the GLSL program.
		prog = std::make_shared<Program>();
		prog->setVerbose(true);
		prog->setShaderNames(resourceDirectory + "/simple_vert33.glsl", resourceDirectory + "/simple_frag33.glsl");
		prog->init();
		prog->addUniform("P");
		prog->addUniform("MV");
        prog->addUniform("WINDOWHEIGHT");
        prog->addUniform("WINDOWWIDTH");
        prog->addUniform("time");
		prog->addAttribute("vertPos");
	}


	/****DRAW
	This is the most important function in your program - this is where you
	will actually issue the commands to draw any geometry you have set up to
	draw
	********/
	void render()
	{
		// Get current frame buffer size.
		int width, height;
		glfwGetFramebufferSize(windowManager->getHandle(), &width, &height);
		float aspect = width/(float)height;
		glViewport(0, 0, width, height);

		// Clear framebuffer.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        GLfloat curTime = glfwGetTime();
		// Create the matrix stacks - please leave these alone for now
		auto P = std::make_shared<MatrixStack>();
		auto MV = std::make_shared<MatrixStack>();
		// Apply orthographic projection.
		P->pushMatrix();
		if (width > height)
		{
			P->ortho(-1*aspect, 1*aspect, -1, 1, -2, 100.0f);
		}
		else
		{
			P->ortho(-1, 1, -1*1/aspect, 1*1/aspect, -2, 100.0f);
		}
		MV->pushMatrix();

		// Draw the triangle using GLSL.
		prog->bind();

		//send the matrices to the shaders
		glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, glm::value_ptr(P->topMatrix()));
		glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
        glUniform1i(prog->getUniform("WINDOWHEIGHT"), height);
        glUniform1i(prog->getUniform("WINDOWWIDTH"), width);
        glUniform1f(prog->getUniform("time"), curTime);

		glBindVertexArray(VertexArrayID);
        

		//actually draw from vertex 0, 3 vertices
		glDrawArrays(GL_TRIANGLES, 0, 240);

		glBindVertexArray(0);
        glBindVertexArray(VertexArrayIDtwo);


		prog->unbind();

		// Pop matrix stacks.
		MV->popMatrix();
		P->popMatrix();
        
	}

};

int main(int argc, char **argv)
{
	std::string resourceDir = "../resources"; // Where the resources are loaded from
	if (argc >= 2)
	{
		resourceDir = argv[1];
	}

	Application *application = new Application();

	/* your main will always include a similar set up to establish your window
		and GL context, etc. */
	WindowManager * windowManager = new WindowManager();
	windowManager->init(640, 480);
	windowManager->setEventCallbacks(application);
	application->windowManager = windowManager;

	/* This is the code that will likely change program to program as you
		may need to initialize or set up different data and state */
	// Initialize scene.
	application->init(resourceDir);
	application->initGeom();

	// Loop until the user closes the window.
	while(! glfwWindowShouldClose(windowManager->getHandle()))
	{
		// Render scene.
		application->render();

		// Swap front and back buffers.
		glfwSwapBuffers(windowManager->getHandle());
		// Poll for and process events.
		glfwPollEvents();
	}

	// Quit program.
	windowManager->shutdown();
	return 0;
}
