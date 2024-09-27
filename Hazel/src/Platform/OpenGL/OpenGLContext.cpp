#include "hzpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

namespace Hazel {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		HZ_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "Failed to initialize Glad!");

	/*	HZ_CORE_INFO("OpenGL Info:");
		HZ_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		HZ_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		HZ_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));*/
		const GLubyte* vendor = glad_glGetString(GL_VENDOR);
		std::cout << "OpenGL Vendor: " << vendor << std::endl;
		const GLubyte* Renderer = glad_glGetString(GL_RENDERER);
		std::cout << "OpenGL Renderer: " << Renderer << std::endl;
		const GLubyte* Version = glad_glGetString(GL_VERSION);
		std::cout << "OpenGL Version: " << Version << std::endl;

		const char* version = glfwGetVersionString();
		printf("GLFW version: %s\n", version);
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}