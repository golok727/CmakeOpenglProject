#include <iostream>
#include <stdio.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "shader.h"
#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main()
{
  std::cout << "Radhey Shyam" << std::endl;

  if (!glfwInit())
  {
    std::cout << "Error initializing GLFW" << std::endl;
    return EXIT_FAILURE;
  }
  float innerWidth = 1280.0, innerHeight = 960.0;

  GLFWwindow *window = glfwCreateWindow((int)innerWidth, (int)innerHeight, "Radha", nullptr, nullptr);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cerr << "Error: Glad initialization failed\n";
    glfwDestroyWindow(window);
    glfwTerminate();
    return -1;
  }

  Shader *basicShader = Shader::LoadFromFile("resources/shaders/basic.glsl");
  Texture imageTexture("resources/textures/train.png");

  float vertices[] = {
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left     // aPos, aTexCoord
      0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // bottom right    //
      0.5f, 0.5f, 0.0f, 1.0f, 1.0f,   // top right       //
      -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,  // top left        //
  };
  unsigned int indicies[] = {0, 1, 2, 2, 3, 0};

  GLuint VAO,
      VBO, IBO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glGenBuffers(1, &IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glBindVertexArray(VAO);

  basicShader->use();
  basicShader->setUniform1i("u_ImageTexture", 0);

  glm::vec3 position(0.0, 0.0, 1.0);
  glm::vec3 scale(1.0, 1.0, 1.0);

  float aspect = innerWidth / innerHeight;
  glm::mat4 projectionMatrix = glm::ortho(-1.0f * aspect, 1.0f * aspect, -1.0f, 1.0f, -1.0f, 1.0f);
  glm::mat4 transformMatrix = glm::translate(glm::mat4(1.0f), position) *
                              glm::scale(glm::mat4(1.0), scale);

  basicShader->setUniformMat4("u_Projection", projectionMatrix);
  basicShader->setUniformMat4("u_Transform", transformMatrix);
  imageTexture.use();

  while (!glfwWindowShouldClose(window))
  {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.1, 0.1, 0.1, 1.0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  delete basicShader;
  return EXIT_SUCCESS;
}