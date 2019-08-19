#include <iostream>

#include <glew/glew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <SFML/Graphics/Image.hpp>

#include "Shader.hpp"
#include "Camera.hpp"

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

	// data
#pragma region Model Data

	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

#pragma endregion


	glViewport(0, 0, 800, 600); // lower left

	Shader* testShader = new Shader("GLSL/vertexSource.vert", "GLSL/fragmentSource.frag");

	/* ����VAO���� */
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);		// ��һ�����������ɶ��ٸ�VAO���ڶ������������ɵ�ID����������
	glBindVertexArray(VAO);

	/* ����VBO���� */
	unsigned int VBO;
	glGenBuffers(1, &VBO);			// ��һ�����������ɶ��ٸ�VBO���ڶ������������ɵ�ID����������
	glBindBuffer(GL_ARRAY_BUFFER, VBO);		// ��һ��������Ҫ��Array Buffer���ڶ��������ǰ��ĸ�VBO

	/* ���������û����ݰ󶨵�buffer */
	// ��һ�������ǰ󶨵�˭���ڶ����������ݶ���Bytes�������������Ǿ�������飬���ĸ��������Կ���δ���
	// GL_STATIC_DRAW �����Ĵ���ʽ���ݼ�������仯
	// GL_DYNAMIC_DRAW ��������ʽ������һ�㾭���䶯
	// GL_STREAM_DRAW �������������ÿ�λ��ƶ����
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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

	sf::Image image1;
	image1.loadFromFile("./resource/container.jpg");
	image1.flipVertically();
	
	int width = image1.getSize().x;
	int height = image1.getSize().y;
	const unsigned char* data = image1.getPixelsPtr();
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	// end - texture

	// texture B
	unsigned int texBufferB;
	glGenTextures(1, &texBufferB);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texBufferB);

	sf::Image image2;
	image2.loadFromFile("./resource/face.png");
	image2.flipVertically();
	
	width = image2.getSize().x;
	height = image2.getSize().y;
	data = image2.getPixelsPtr();
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	// end - texture B

	/* ʹ��Shader */
	testShader->use();
	testShader->setInt("ourTexture", 0);
	testShader->setInt("ourFace", 3);

	window.setActive();

	// Camera
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::radians(-15.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));

	glm::mat4 view = camera.getViewMatrix();

	glm::mat4 projection(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600, 0.1f, 100.0f);

	//testShader->setMat4fv("model", model);
	testShader->setMat4fv("view", view);
	testShader->setMat4fv("projection", projection);
	
	glEnable(GL_DEPTH_TEST);
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
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		sf::Time elapsed = clock.getElapsedTime();
		float greenValue = (sin(elapsed.asSeconds()) / 2.0f) + 0.5f;

		testShader->setFloat("fragIn", greenValue);
		// ����ͼ��
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle) * elapsed.asSeconds(), glm::vec3(1.0f, 0.3f, 0.5f));
			testShader->setMat4fv("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		window.display();
	}
	// �ͷ���Դ

	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);

	return EXIT_SUCCESS;
}
