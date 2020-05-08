#ifndef COTECCHIOGAME_GL_LOADER_H
#define COTECCHIOGAME_GL_LOADER_H

#include "glad.h"
#include "glfw3.h"

#include <iostream>

//TODO clean code!!!
// Impostazione linguaggio GLSL - scrittura direzionalità e tipo di dato
const char* vsSource = "#version 330 core\n"
                       "layout (location = 0) in vec3 position;\n" // Variabile in ingresso di 3 float (vettore), layout da posizione sulla memoria
                       //"out vec3 gl_Position;\n"
                       "void main() {\n"
                       "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
                       "   \n"
                       //"   gl_Position = MVP*position\n"  // Posizione in Clip Space/NDC
                       "}\n\0";
                       //"layout (location = 1) in vec3 normal;\n" // Definiamo più attributi su piu indici
                       //"layout (location = 2) in vec2 uv;\n"
                       //"uniform bool name;\n"   // Valore uniforme, costante per tutti i vertici e/o fragment
                       //"vec3 pos1 = position.xxx"; // Inizializzazione con accesso a variabili position.xyz con x y z generici
                                       // Attributi: dati
const char* fsSource = "#version 330 core\n"
                       "out vec4 fragColor;\n"
                        "void main() {\n"
                        "  fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n" // Colore [0,1] RGBA
                        "  \n"
                        "}\n\0";

float vertices[] {-0.5f, -0.5f, 0.0f,
                  0.5f, -0.5f, 0.0f,
                  0.0f, -0.5f, 0.0f}; //In coordinate NDC da inviare allo shader

                  //Vertex buffer, Element buffer per la topologia
                  // Rappresentazione elemento geometrico è visibile se la normale dell'elemento è diretta verso la camera
                  //    ovvero i vertici sono inseriti in verso antiorario, come vertici (non come valori)

const unsigned int WIDTH = 640;
const unsigned int HEIGHT = 480;

void function(GLFWwindow *vindow, int width, int height) {
   //-> chiamata nelle callback di glViewport(0, 0, width, height);
   // glViewport è la matrice che passa da NDP a Screen
   glViewport(0, 0, width, height);
}

void pollInput(GLFWwindow *window) {
   if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, true);
   }
}
static int initialise() {
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
   glfwSetWindowSizeCallback(window, function);   // Chiamare determinate callbacks per ogni azione

   if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
      std::cout << "Error LOADING_GL: libraries cannot be called";
      glfwTerminate();
      return -1;
   }

   // Creazione dello shader (vertex o fragment)
   // VERTEX SHADER
   // Restituisce GL unsigned int, indice dell'oggetto vertex shader creato dalla GPU
   GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);  // Operazione binaria, invia chiamata sulla scheda grafica
   int report;
   char infoLog[512];
   // Assegnazione codice allo shader (handle, assegnazione stringa di un puntatore
   glShaderSource(vertexShader, 1, &vsSource, nullptr);
   // Compilazione shader
   glCompileShader(vertexShader);

   // Controllo errori di compilazione - controllo di un handle per ottenere informazioni sulla compilazione
   glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &report);

   if (!report) {
      glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);

      std::cout << "Error INFOLOG_COMPILE_VERTEX: " << infoLog << std::endl;
   }

   // FRAGMENT SHADER
   // Restituisce GL unsigned int, indice dell'oggetto vertex shader creato dalla GPU
   GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);  // Operazione binaria, invia chiamata sulla scheda grafica
   // Assegnazione codice allo shader (handle, assegnazione stringa di un puntatore
   glShaderSource(vertexShader, 1, &fsSource, nullptr);
   // Compilazione shader
   glCompileShader(vertexShader);

   // Controllo errori di compilazione - controllo di un handle per ottenere informazioni sulla compilazione
   glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &report);

   if (!report) {
      glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);

      std::cout << "Error INFOLOG_COMPILE_FRAGMENT: " << infoLog << std::endl;
   }

   // Creazione contenitore (program), rappresenta la pipeline di rendering (nel senso delle possibilità programmabili dall'utente)
   GLuint shaderProgram = glCreateProgram();

   // Aggiunta del programma dei vari shader
   glAttachShader(shaderProgram, vertexShader);
   glAttachShader(shaderProgram, fragmentShader);

   // Link del programma, unisce le unità programmabili (shader)
   glLinkProgram(shaderProgram);

   // Controllo del link programma, status
   glGetProgramiv(shaderProgram, GL_LINK_STATUS, &report);

   if (!report) {
      glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);

      std::cout << "Error INFOLOG_LINK_PROGRAM: " << infoLog << std::endl;
   }

   // Pulizia memoria dopo la compilazione e link
   glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader);

   // Generazione del VBO (vertex buffer object), array generico nell'handle specifico
   GLuint vbo; // Entry point all'array
   GLuint vao; // Vertex Array Object, contenitore per inserire array vertici e topologia, usandolo come definizione logica dell'oggetto
   // Esempio un oggettto è dato da un insieme di vertici, elementi (topologia)
   // Semplifica chiamate a runtime
   glGenVertexArrays(1, &vao);
   glGenBuffers(1, &vbo);
   // Chiamata per collegare un tipo di buffer noto agli attributi di vertice, l'indice dell'area di memoria creata va intesa come arraybuffer
   glBindVertexArray(vao); // Bind all'inizio delle operazioni riferite al vertex array obj
   // Binding: ogni chiamata di tipo ARRAY_BUFFER sarà assegnata all'ultimo bind assegnato
   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   // Copia dati nell'array, ora verrà inizializzata, prima era solo definito il punto nella memoria
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Unicamente disegnati senza modificare punti
   // Assegnare attributi a partire da determinati dati, cerca dati nella LOCATION  definita nella GLSL
   // Stride, in termini di byte: size in byte di un gruppo di dati da analizzare
   /* 0        1        2
    * x y z    x y z    x y z
    * Nelle varie posizioni saranno salvate le informazioni
    * Offset di memoria, ovvero punto zona di memoria per leggere i dati, poichè a priori non nota (potrebbero esserci dati in piu da non dover leggere
    * x y z u v  x y ... offset 2
    */
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)nullptr); //(void*)0
   glEnableVertexAttribArray(0);
   glBindBuffer(GL_ARRAY_BUFFER, 0); // Adesso GL_ARRAY_BUFFER saranno ora riferite all'array 0, per evitare di richiamare qualcos'altro
   glBindVertexArray(0);
   // ATTENZIONE a non sovrascrivere, quindi attenzione a sofrascrittura

   // Chiamate di GLAD e di GLFW
   //Creazione di Render Loop (infinito, finisce quando esce dalla finestra)
   while (!glfwWindowShouldClose(window)) { // semmai la finestra dovesse chiudersi
      // Gestione degli input
      // Eseguiti in senso temporale
      pollInput(window);

      glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT); // In base all'ordine, modifica lo stato del sistema corrente o successivo

      glUseProgram(shaderProgram);  // Imposta tutte le chiamate tramite shaderProgram, iniziando la pipeline

      // Caricare vertexArray
      glBindVertexArray(vao);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      //Necessità di modificare il buffer prima di inviarlo
      // prima, modifica il buffer B (sul successivo)
      glfwSwapBuffers(window);   // Crea multipli frame buffers per aggiornare i pixel, (double buffer, triple buffer, area di memoria per salvare framebuffer attuale e successivo), swap al frame buffer preparatorio)
      // Sostituisce questo buffer con quello successivo, visualizzando quello già riempito
      // Cambia frame buffer su cui lavorare
      glfwPollEvents();
      // Controlla tutti gli eventi in background (qualunque) OBBLIGATORIO
   }

   glDeleteBuffers(1, &vbo);
   glDeleteVertexArrays(1, &vao);
   glDeleteProgram(shaderProgram);
   glfwTerminate();

   return 0;
}

#endif //COTECCHIOGAME_GL_LOADER_H
