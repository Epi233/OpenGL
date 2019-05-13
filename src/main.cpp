
#define GLEW_STATIC

#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main() {

	float vertices[] = {
		//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	stbi_set_flip_vertically_on_load(true);
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "XXX", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// init glew

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to create GLEW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 600); // lower left
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	Shader* testShader = new Shader("./src/vertexSource.vert", "./src/fragmentSource.frag");

	/* 产生VAO，绑定 */
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);		// 第一个参数是生成多少个VAO，第二个参数是生成的ID返还到哪里
	glBindVertexArray(VAO);

	/* 产生VBO，绑定 */
	unsigned int VBO;
	glGenBuffers(1, &VBO);			// 第一个参数是生成多少个VAO，第二个参数是生成的ID返还到哪里
	glBindBuffer(GL_ARRAY_BUFFER, VBO);		// 第一个参数是要绑定Array Buffer，第二个参数是绑定哪个VBO

	/* 接下来将用户数据绑定到buffer */
	// 第一个参数是绑定到谁，第二个参数数据多少Bytes，第三个参数是具体的数组，第四个参数是显卡如何处理
	// GL_STATIC_DRAW 这样的处理方式数据几乎不会变化
	// GL_DYNAMIC_DRAW 这样处理方式的数据一般经常变动
	// GL_STREAM_DRAW 这种情况下数据每次绘制都会变
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	

	/* 产生EBO，绑定 */
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	/* 链接顶点属性 */
	// 第一个参数从第几个开始绘制， 第二个参数尺寸是多少， 第三个参数是什么类型
	// 第四个参数是要不要归一化到±1之间，第五个参数为每笔数据之间的间隔是多少，第六个参数为第一笔数据的偏移量是多少
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));

	/* 打开定点属性 */
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
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
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
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	// end - texture B


	/* 使用Shader */
	testShader->use();
	testShader->setInt("ourTexture", 0);
	testShader->setInt("ourFace", 3);


	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;

		testShader->setFloat("fragIn", greenValue);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
