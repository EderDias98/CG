#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define TAMANHO_JANELA 500
#define RAIO 0.2 // Raio para detectar o clique perto dos pontos de controle

// Tamanho da janela
float size = 1.0;  // Agora o intervalo será de 0 a 1, então size deve ser 1.0
float offsetX = 0, offsetY = 0;
// Pontos de controle da Spline no intervalo [0, 1]
GLfloat ctrlpoints[4][3] = {
        { 0.0, 0.0, 0.0}, { 0.2, 0.8, 0.0}, 
        { 0.5, 0.2, 0.0}, { 1.0, 1.0, 0.0}
};

int selected_point = -1; // Índice do ponto selecionado

// Função para inicializar as configurações do OpenGL
void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_MAP1_VERTEX_3);
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Usamos a transformação ortográfica para o intervalo [0, 1]
    glOrtho(0.0, 1.0, 0.0, 1.0, -size, size);
}

// Função de exibição
void display(void) {
    int i;
    glClear(GL_COLOR_BUFFER_BIT);

    // Desenha a curva aproximada por n+1 pontos.
    int n = 30;
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);
    for (i = 0; i <= n; i++) {
        glEvalCoord1f((GLfloat)i / (GLfloat)n);
    }
    glEnd();

    // Desenha os pontos de controle
    glPointSize(10.0);  // Aumentando o tamanho para facilitar a interação
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    for (i = 0; i < 4; i++) {
        glVertex3fv(&ctrlpoints[i][0]);
    }
    glEnd();

    glutSwapBuffers();
}

void mouse_to_opengl_coordinates(int x, int y, float *ox, float *oy) {
    // Converte coordenadas de tela (x, y) para o intervalo [-1, 1] do OpenGL
    *ox =  x  / (float)(TAMANHO_JANELA);
    *oy =  -(y - TAMANHO_JANELA) / (float)(TAMANHO_JANELA );
}


// Função para verificar se o clique do mouse está dentro de um ponto de controle
int is_inside_point(int x, int y) {
    float mouseX, mouseY;
    mouse_to_opengl_coordinates(x, y, &mouseX, &mouseY);

    for (int i = 0; i < 4; i++) {
        float dist = sqrt(pow(mouseX - ctrlpoints[i][0], 2) + pow(mouseY - ctrlpoints[i][1], 2));
        if (dist < RAIO) {
            return i; // Retorna o índice do ponto selecionado
        }
    }

    return -1; // Nenhum ponto selecionado
}

// Função para lidar com o clique do mouse
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        selected_point = is_inside_point(x, y); // Verifica qual ponto foi clicado
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        selected_point = -1; // Desseleciona o ponto
    }
}

// Função para lidar com o movimento do mouse (arrastando o ponto de controle)
void motion(int x, int y) {
    if (selected_point != -1) {
        // Converte a posição do mouse para coordenadas de OpenGL
        float mouseX, mouseY;
        mouse_to_opengl_coordinates(x, y, &mouseX, &mouseY);

        // Atualiza a posição do ponto selecionado
        ctrlpoints[selected_point][0] = mouseX;
        ctrlpoints[selected_point][1] = mouseY;
        glutPostRedisplay(); // Atualiza a tela
    }
}

// Função principal
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(TAMANHO_JANELA, TAMANHO_JANELA);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouse); // Configura a função de mouse
    glutMotionFunc(motion); // Configura a função de movimento do mouse

    glutMainLoop();
    return 0;
}


























































































































































