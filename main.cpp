//#include<iostream>
//#include<glad/glad.h>
//#include<GLFW/glfw3.h>
//
//int main()
//{
//	return 0;
//}

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

int main() {
    glm::mat4 matrix = glm::mat4(1.0f);
    matrix = glm::rotate(matrix, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    std::cout << "GLM is working!" << std::endl;
    return 0;
}
