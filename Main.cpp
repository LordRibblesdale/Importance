#include "glad.h"
#include "glfw3.h"

#include <iostream>

const unsigned int WIDTH = 640;
const unsigned int HEIGHT = 480;

void function(GLFWwindow* vindow, int width, int height) {
   //-> chiamata nelle callback di glViewport(0, 0, width, height);
   // glViewport è la matrice che passa da NDP a Screen
   glViewport(0, 0, width, height);
}

void pollInput(GLFWwindow* window) {
   if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, true);
   }
}

// Argument as XML file importer
int main(int argc, char** argv) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE
       glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Cotecchio Game", nullptr, nullptr);
    //(nessuna condivisione con share, nessuna finestra a cui dipendere)

    if (!window) {
       std::cout << "Error INITIALISATION: window cannot be initialised.";
       glfwTerminate();

       return -1;
    }

    glfwMakeContextCurrent(window); // legare contesto di OpenGL alla finestra (struttura di macchina di stato, eseguite operazioni in un contesto)

    // Chiamare determinate callbacks per ogni
    glfwSetWindowSizeCallback(window, function);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
       std::cout << "Error LOADING_GL: libraries cannot be called";
       glfwTerminate();

       return -1;
    }
    // Chiamate di GLAD e di GLFW

    //Creazione di Render Loop (infinito, finisce quando esce dalla finestra)

    while (!glfwWindowShouldClose(window)) { // semmai la finestra dovesse chiudersi
       // Gestione degli input

       glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
       glClear(GL_COLOR_BUFFER_BIT); // In base all'ordine, modifica lo stato del sistema corrente o successivo
       //Necessità di modificare il buffer prima di inviarlo

       // prima, modifica il buffer B (sul successivo)
       glfwSwapBuffers(window);   // Crea multipli frame buffers per aggiornare i pixel, (double buffer, triple buffer, area di memoria per salvare framebuffer attuale e successivo), swap al frame buffer preparatorio)
          // Sostituisce questo buffer con quello successivo, visualizzando quello già riempito
          // Cambia frame buffer su cui lavorare
       glfwPollEvents();
       // Controlla tutti gli eventi in background (qualunque) OBBLIGATORIO
    }

    glfwTerminate();


   return 0;
}
