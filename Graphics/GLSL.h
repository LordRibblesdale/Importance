#ifndef GLSL_H
#define GLSL_H

// Impostazione linguaggio GLSL - scrittura direzionalità e tipo di dato
const char* vsSource = "#version 330 core\n"
                       "layout (location = 0) in vec3 position;\n" // Variabile in ingresso di 3 float (vettore), layout da posizione sulla memoria
                       //"out vec3 gl_Position;\n"
                       "void main() {\n"
                       "   gl_Position = vec4(position.x, position.y, position.z, 1.0f);\n"
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
                       "}\n\0";

#endif //GLSL_H
