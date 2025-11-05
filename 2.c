#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

// Pontos de controle
float ctrlpoints[4][3] = {
    {0.1, 0.1, 0.0},
    {0.3, 0.8, 0.0},
    {0.7, 0.2, 0.0},
    {0.9, 0.9, 0.0}
};

// Variáveis globais
int selectedPoint = -1;
const float pickRadius = 0.05f;
int numSegments = 30;

// Inicialização da cena
void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
    glEnable(GL_MAP1_VERTEX_3);
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);
}

// Desenho da curva e dos pontos
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= numSegments; i++)
        glEvalCoord1f((GLfloat)i / (GLfloat)numSegments);
    glEnd();

    // Desenha pontos de controle
    glPointSize(8.0);
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < 4; i++)
        glVertex3fv(&ctrlpoints[i][0]);
    glEnd();

    glFlush();
}

// Controle de clique do mouse
void mouse(int button, int state, int x, int y) {
    float fx = (float)x / glutGet(GLUT_WINDOW_WIDTH);
    float fy = 1.0f - ((float)y / glutGet(GLUT_WINDOW_HEIGHT));

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        for (int i = 0; i < 4; i++) {
            float dx = fx - ctrlpoints[i][0];
            float dy = fy - ctrlpoints[i][1];
            float dist = sqrt(dx*dx + dy*dy);
            if (dist < pickRadius) {
                selectedPoint = i;
                break;
            }
        }
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        selectedPoint = -1;
    }
}

// Arraste do ponto selecionado
void motion(int x, int y) {
    if (selectedPoint != -1) {
        float fx = (float)x / glutGet(GLUT_WINDOW_WIDTH);
        float fy = 1.0f - ((float)y / glutGet(GLUT_WINDOW_HEIGHT));

        ctrlpoints[selectedPoint][0] = fx;
        ctrlpoints[selectedPoint][1] = fy;

        glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
        glutPostRedisplay();
    }
}

// Teclado: + e - para ajustar resolução
void keyPress(unsigned char key, int x, int y) {
    if (key == '+') {
        if (numSegments < 100) numSegments++;
    }
    else if (key == '-') {
        if (numSegments > 2) numSegments--;
    }

    glutPostRedisplay();
}

// Função principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Spline Interativa - Lab 2");

    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyPress);

    glutMainLoop();
    return 0;
}

