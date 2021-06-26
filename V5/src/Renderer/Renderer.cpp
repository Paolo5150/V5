#include <Renderer/Renderer.h>
#include <glad/glad.h>
#include <vector>
#include <fstream>
#include <V5/Core/Logger.h>
#include "Renderer/Shader.h"
#include "Renderer/OpenGL/OpenGLShader.h"

using namespace V5Rendering;

std::unique_ptr<Renderer> Renderer::s_Instance;

namespace
{
	unsigned int hctVAO;

}

Renderer& Renderer::Instance()
{
	if (s_Instance == nullptr)
	{
		s_Instance = std::make_unique<Renderer>();
	}

	return *s_Instance;
}

void Renderer::Init()
{
	m_renderAPI = RendererAPI::Create();
	m_renderAPI->Init();

	//TODO: refactor obiously
	Shader::CreateFromSPIRV("Assets\\Shaders\\colorOnly.vert.spv", "Assets\\Shaders\\colorOnly.frag.spv");
	
	//TODO: Refactor, no opengl code here

	std::vector<float> vertices = {
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.0f, 0.5f, -0.5f
	};

	unsigned int hctVBO; // hello colorful triangle vbo
	//glGenBuffers(1, &VBO); // Way to go before openGl 4.5
	//glBindBuffer(GL_ARRAY_BUFFER, VBO); // Binding to openGl context was necessary
	//  replaced with:
	glCreateBuffers(1, &hctVBO);//uses DSA. This is the way.

	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//  replaced with:


	glNamedBufferStorage(hctVBO, sizeof(vertices), vertices.data(), GL_DYNAMIC_STORAGE_BIT);
	//                    ^^^  needed, since there is no context binding.

	//glGenVertexArrays(1, &VAO);
	//glBindVertexArray(VAO);
	//  replaced with:
	glCreateVertexArrays(1, &hctVAO);// This is the way.

	GLuint vaoBindingPoint =0;//A binding point in VAO. See GL_MAX_VERTEX_ATTRIB_BINDINGS
	glVertexArrayVertexBuffer(
		hctVAO,             // vao to bind
		vaoBindingPoint,    // Could be 1, 2... if there were several vbo to source.
		hctVBO,             // VBO to bound at "vaoBindingPoint".
		0,                  // offset of the first element in the buffer hctVBO.
		3 * sizeof(float));   // stride == 3 position floats + 3 color floats.

	glEnableVertexArrayAttrib(hctVAO, 0);// Need to precise vao, as there is no context binding in DSA style
	glVertexArrayAttribFormat(hctVAO, 0, 3, GL_FLOAT, false, 0);// Need to precise vao, as there is no context binding in DSA
	glVertexArrayAttribBinding(hctVAO, 0, vaoBindingPoint);


}

void Renderer::Render()
{
	//Do rendering
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(hctVAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);


}


void Renderer::Shutdown()
{
	m_renderAPI->Shutdown();
}

void Renderer::OnEvent(V5Core::Event& e)
{
	m_renderAPI->OnEvent(e);
}


