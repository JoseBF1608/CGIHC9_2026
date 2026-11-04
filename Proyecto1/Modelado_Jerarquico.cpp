#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Shaders
#include "Shader.h"

void Inputs(GLFWwindow* window);


const GLint WIDTH = 1200, HEIGHT = 800;

//For Keyboard
float movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rot = 0.0f;

//For model
float hombro = 0.0f;
float codo = 0.0f;
float mano = 0.0f;
float indice1 = 0.0f;
float indice2 = 0.0f;
float indice3 = 0.0f;
float pulgar1 = 0.0f;
float pulgar2 = 0.0f;
float medio1 = 0.0f;
float medio2 = 0.0f;
float medio3 = 0.0f;
float anular1 = 0.0f;
float anular2 = 0.0f;
float anular3 = 0.0f;
float menique1 = 0.0f;
float menique2 = 0.0f;
float menique3 = 0.0f;

int main() {
    glfwInit();
    //Verificaci?n de compatibilidad
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Modelado jerarquico", nullptr, nullptr);

    int screenWidth, screenHeight;

    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    //Verificaci?n de errores de creacion  ventana
    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    //Verificaci?n de errores de inicializaci?n de glew

    if (GLEW_OK != glewInit()) {
        std::cout << "Failed to initialise GLEW" << std::endl;
        return EXIT_FAILURE;
    }


    // Define las dimensiones del viewport
    glViewport(0, 0, screenWidth, screenHeight);


    // Setup OpenGL options
    glEnable(GL_DEPTH_TEST);

    // enable alpha support
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    // Build and compile our shader program
    Shader ourShader("Shader/core.vs", "Shader/core.frag");


    // Set up vertex data (and buffer(s)) and attribute pointers
    // use with Orthographic Projection




    // use with Perspective Projection
    float vertices[] = {
    -0.5f, -0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,
    0.5f,  0.5f, 0.5f,
    0.5f,  0.5f, 0.5f,
    -0.5f,  0.5f, 0.5f,
    -0.5f, -0.5f, 0.5f,

       -0.5f, -0.5f,-0.5f,
    0.5f, -0.5f,-0.5f,
    0.5f,  0.5f,-0.5f,
    0.5f,  0.5f,-0.5f,
       -0.5f,  0.5f,-0.5f,
       -0.5f, -0.5f,-0.5f,

    0.5f, -0.5f,  0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f,  0.5f,  0.5f,
    0.5f,  -0.5f, 0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    };




    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);

    // Enlazar  Vertex Array Object
    glBindVertexArray(VAO);

    //2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    //Posicion
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);



    glBindBuffer(GL_ARRAY_BUFFER, 0);


    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


    glm::mat4 projection = glm::mat4(1);

    projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
    glm::vec3 color = glm::vec3(0.0f, 0.0f, 1.0f);
    while (!glfwWindowShouldClose(window))
    {

        Inputs(window);
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // Render
        // Clear the colorbuffer
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        ourShader.Use();
        glm::mat4 model = glm::mat4(1);
        glm::mat4 view = glm::mat4(1);
        glm::mat4 modelTemp = glm::mat4(1.0f); //Temp
        glm::mat4 modelTemp2 = glm::mat4(1.0f); //Temp



        //View set up
        view = glm::translate(view, glm::vec3(movX, movY, movZ));
        view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

        GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
        GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");
        GLint uniformColor = ourShader.uniformColor;

        glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));


        glBindVertexArray(VAO);

        //Model

        // hombro
        model = glm::rotate(model, glm::radians(hombro), glm::vec3(0.0f, 0.0, 1.0f)); //hombro
        modelTemp = model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));
        color = glm::vec3(0.0f, 1.0f, 0.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);//A


        //antebrazo
        model = glm::translate(modelTemp, glm::vec3(1.5f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(codo), glm::vec3(0.0f, 1.0, 0.0f));
        modelTemp = model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
        color = glm::vec3(1.0f, 0.0f, 0.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);//A


        //mano
        model = glm::translate(modelTemp, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(mano), glm::vec3(0.0f, 1.0, 0.0f));
        modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        color = glm::vec3(0.0f, 0.0f, 1.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);//A


        //pulgar - falange 1
        modelTemp2 = modelTemp;
        model = glm::translate(modelTemp2, glm::vec3(0.5f, -0.4f, 0.4f));
        model = glm::rotate(model, glm::radians(pulgar1), glm::vec3(0.0f, 0.0f, 1.0f));
        modelTemp2 = model = glm::translate(model, glm::vec3(0.15f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.3f, 0.2f, 0.2f));
        color = glm::vec3(1.0f, 0.0f, 0.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);//A

        //pulgar - falange 2
        model = glm::translate(modelTemp2, glm::vec3(0.15f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(pulgar2), glm::vec3(0.0f, 0.0, 1.0f));
        modelTemp2 = model = glm::translate(model, glm::vec3(0.15f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.3f, 0.2f, 0.2f));
        color = glm::vec3(1.0f, 0.0f, 1.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);//A


        //indice - falange 1
        modelTemp2 = modelTemp;
        model = glm::translate(modelTemp2, glm::vec3(0.5f, 0.4f, 0.4f));
        model = glm::rotate(model, glm::radians(indice1), glm::vec3(0.0f, 0.0, 1.0f));
        modelTemp2 = model = glm::translate(model, glm::vec3(0.2f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.2f));
        color = glm::vec3(1.0f, 0.0f, 0.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);//A

        //indice - falange 2
        model = glm::translate(modelTemp2, glm::vec3(0.2f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(indice2), glm::vec3(0.0f, 0.0, 1.0f));
        modelTemp2 = model = glm::translate(model, glm::vec3(0.2f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.2f));
        color = glm::vec3(1.0f, 0.0f, 1.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);//A

        // indice falange 3
        model = glm::translate(modelTemp2, glm::vec3(0.2f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(indice3), glm::vec3(0.0f, 0.0, 1.0f));
        modelTemp2 = model = glm::translate(model, glm::vec3(0.2f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.2f));
        color = glm::vec3(1.0f, 1.0f, 0.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);//A

        //medio - falange 1
        modelTemp2 = modelTemp;
        model = glm::translate(modelTemp2, glm::vec3(0.5f, 0.4f, 0.15f));
        model = glm::rotate(model, glm::radians(medio1), glm::vec3(0.0f, 0.0, 1.0f));
        modelTemp2 = model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.7f, 0.2f, 0.2f));
        color = glm::vec3(1.0f, 0.0f, 0.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);//A

        //medio - falange 2
        model = glm::translate(modelTemp2, glm::vec3(0.2f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(medio2), glm::vec3(0.0f, 0.0, 1.0f));
        modelTemp2 = model = glm::translate(model, glm::vec3(0.2f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.2f));
        color = glm::vec3(1.0f, 0.0f, 1.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);//A

        //medio - falange 3
        model = glm::translate(modelTemp2, glm::vec3(0.2f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(medio3), glm::vec3(0.0f, 0.0f, 1.0f));
        modelTemp2 = model = glm::translate(model, glm::vec3(0.2f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.2f));
        color = glm::vec3(1.0f, 1.0f, 0.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);//A

        //anular - falange 1
        modelTemp2 = modelTemp;
        model = glm::translate(modelTemp2, glm::vec3(0.5f, 0.4f, -0.15f));
        model = glm::rotate(model, glm::radians(anular1), glm::vec3(0.0f, 0.0, 1.0f));
        modelTemp2 = model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.7f, 0.2f, 0.2f));
        color = glm::vec3(1.0f, 0.0f, 0.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);//A

        //anular - falange 2
        model = glm::translate(modelTemp2, glm::vec3(0.2f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(anular2), glm::vec3(0.0f, 0.0f, 1.0f));
        modelTemp2 = model = glm::translate(model, glm::vec3(0.2f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.2f));
        color = glm::vec3(1.0f, 0.0f, 1.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);//A

        //anular - falange 3
        model = glm::translate(modelTemp2, glm::vec3(0.2f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(anular3), glm::vec3(0.0f, 0.0, 1.0f));
        modelTemp2 = model = glm::translate(model, glm::vec3(0.2f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.2f));
        color = glm::vec3(1.0f, 1.0f, 0.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);//A


        //me?ique - falange 1
        modelTemp2 = modelTemp;
        model = glm::translate(modelTemp2, glm::vec3(0.5f, 0.4f, -0.4f));
        model = glm::rotate(model, glm::radians(menique1), glm::vec3(0.0f, 0.0, 1.0f));
        modelTemp2 = model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.7f, 0.2f, 0.2f));
        color = glm::vec3(1.0f, 0.0f, 0.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);//A

        // me?ique - falange 2
        model = glm::translate(modelTemp2, glm::vec3(0.2f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(menique2), glm::vec3(0.0f, 0.0, 1.0f));
        modelTemp2 = model = glm::translate(model, glm::vec3(0.2f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.2f));
        color = glm::vec3(1.0f, 0.0f, 1.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);//A

        // me?ique - falange 3
        model = glm::translate(modelTemp2, glm::vec3(0.2f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(menique3), glm::vec3(0.0f, 0.0, 1.0f));
        modelTemp2 = model = glm::translate(model, glm::vec3(0.2f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.2f));
        color = glm::vec3(1.0f, 1.0f, 0.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color)); 
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); 
        glDrawArrays(GL_TRIANGLES, 0, 36);//A 


        glBindVertexArray(0);


        // Swap the screen buffers
        glfwSwapBuffers(window);

    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);


    glfwTerminate();
    return EXIT_SUCCESS;
}

void Inputs(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
        movX += 0.08f;
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
        movX -= 0.08f;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        movY += 0.08f;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        movY -= 0.08f;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        movZ -= 0.08f;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        movZ += 0.08f;
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        rot += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        rot -= 0.18f;
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        hombro += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        hombro -= 0.18f;
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
        codo += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
        codo -= 0.18f;
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
        mano += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
        mano -= 0.18f;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        pulgar1 += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        pulgar1 -= 0.18f;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        pulgar2 -= 0.18f;
    if (glfwGetKey(window, GLFW_KEY_SEMICOLON) == GLFW_PRESS)
        pulgar2 += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        indice1 -= 0.18f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        indice1 += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        indice2 -= 0.18f;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        indice2 += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
        indice3 -= 0.18f;
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
        indice3 += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        medio1 -= 0.18f;
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        medio1 += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        medio2 -= 0.18f;
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        medio2 += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        medio3 -= 0.18f;
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
        medio3 += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        anular1 -= 0.18f;
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
        anular1 += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        anular2 -= 0.18f;
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
        anular2 += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
        anular3 -= 0.18f;
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
        anular3 += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
        menique1 -= 0.18f;
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        menique1 += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        menique2 -= 0.18f;
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        menique2 += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        menique3 -= 0.18f;
    if (glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_PRESS)
        menique3 += 0.18f;
}
