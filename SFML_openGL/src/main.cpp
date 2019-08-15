#include <iostream>

#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Shader.hpp"

int main()
{
	// ��ʼ��Window����
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;

	const unsigned int WIDTH = 800;
	const unsigned int HEIGHT = 600;
	const sf::String TITLE = "Modern OpenGL";
	sf::Window window(sf::VideoMode(WIDTH, HEIGHT, 32), TITLE,
		sf::Style::Titlebar | sf::Style::Close, settings);

	// ��ʼ��GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	// ��������
	float vertices[] =
	{
		//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
	};

	unsigned int indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	stbi_set_flip_vertically_on_load(true);

	glViewport(0, 0, 800, 600); // lower left

	Shader* testShader = new Shader("GLSL/vertexSource.vert", "GLSL/fragmentSource.frag");

	/* ����VAO���� */
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);		// ��һ�����������ɶ��ٸ�VAO���ڶ������������ɵ�ID����������
	glBindVertexArray(VAO);

	/* ����VBO���� */
	unsigned int VBO;
	glGenBuffers(1, &VBO);			// ��һ�����������ɶ��ٸ�VAO���ڶ������������ɵ�ID����������
	glBindBuffer(GL_ARRAY_BUFFER, VBO);		// ��һ��������Ҫ��Array Buffer���ڶ��������ǰ��ĸ�VBO

	/* ���������û����ݰ󶨵�buffer */
	// ��һ�������ǰ󶨵�˭���ڶ����������ݶ���Bytes�������������Ǿ�������飬���ĸ��������Կ���δ���
	// GL_STATIC_DRAW �����Ĵ���ʽ���ݼ�������仯
	// GL_DYNAMIC_DRAW ��������ʽ������һ�㾭���䶯
	// GL_STREAM_DRAW �������������ÿ�λ��ƶ����
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/* ����EBO���� */
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	/* ���Ӷ������� */
	// ��һ�������ӵڼ�����ʼ���ƣ� �ڶ��������ߴ��Ƕ��٣� ������������ʲô����
	// ���ĸ�������Ҫ��Ҫ��һ������1֮�䣬���������Ϊÿ������֮��ļ���Ƕ��٣�����������Ϊ��һ�����ݵ�ƫ�����Ƕ���
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));

	/* �򿪶������� */
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// texture 1
	unsigned int texBuffer;
	glGenTextures(1, &texBuffer);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texBuffer);

	int width, height, numChannel;
	unsigned char* data = stbi_load("./resource/container.jpg", &width, &height, &numChannel, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	// end - texture

	// texture B
	unsigned int texBufferB;
	glGenTextures(1, &texBufferB);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texBufferB);
	data = stbi_load("./resource/face.png", &width, &height, &numChannel, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	// end - texture B

	/* ʹ��Shader */
	testShader->use();
	testShader->setInt("ourTexture", 0);
	testShader->setInt("ourFace", 3);

	window.setActive();

	// ���Whileѭ����SFML�Ĺ̶�ģʽ�������¼�����
	sf::Clock clock;
	clock.restart();
	while (window.isOpen())
	{
		// �ڲ�Whileѭ�����ڴ����¼���Ӧ
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		sf::Time elapsed = clock.getElapsedTime();
		float greenValue = (sin(elapsed.asSeconds()) / 2.0f) + 0.5f;

		testShader->setFloat("fragIn", greenValue);
		// ����ͼ��
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)0);

		window.display();
	}
	// �ͷ���Դ

	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);

	return EXIT_SUCCESS;
}
