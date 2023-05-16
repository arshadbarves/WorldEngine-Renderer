#include "Mesh.h"

namespace WorldEngine
{
	Mesh::Mesh()
	{
		// Initialize Mesh
		VAO = 0;
		VBO = 0;
		IBO = 0;
		indexCount = 0;
	}
	Mesh::~Mesh()
	{
		// Delete Mesh
		ClearMesh();
	}
	void Mesh::CreateMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices)
	{
		indexCount = numOfIndices;

		// Create Vertex Array Object
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		// Create Index Buffer Object
		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);

		// Create Vertex Buffer Object
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);

		// Set Vertex Attribute Pointer
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, 0);
		glEnableVertexAttribArray(0);

		// Set Texture Attribute Pointer
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, (void*)(sizeof(vertices[0]) * 3));
		glEnableVertexAttribArray(1);

		// Set Normal Attribute Pointer
		/*glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 5));
		glEnableVertexAttribArray(2);*/

		// Unbind Index Buffer Object
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// Unbind Vertex Buffer Object
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Unbind Vertex Array Object
		glBindVertexArray(0);
	}
	void Mesh::RenderMesh()
	{
		// Bind Vertex Array Object
		glBindVertexArray(VAO);
		// Bind Index Buffer Object
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		// Draw Elements
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
		// Unbind Index Buffer Object
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		// Unbind Vertex Array Object
		glBindVertexArray(0);
	}
	void Mesh::ClearMesh()
	{
		// Delete Vertex Array Object
		if (VAO != 0)
		{
			glDeleteVertexArrays(1, &VAO);
			VAO = 0;
		}
		// Delete Vertex Buffer Object
		if (VBO != 0)
		{
			glDeleteBuffers(1, &VBO);
			VBO = 0;
		}
		// Delete Index Buffer Object
		if (IBO != 0)
		{
			glDeleteBuffers(1, &IBO);
			IBO = 0;
		}
		indexCount = 0;
	}
};
