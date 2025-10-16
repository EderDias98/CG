#include <GL/glut.h>
#define TAMANHO_JANELA 500

float gX = 0.25f, gY = 0.25f;
int mousePressionado = 0;
float offsetX = 0, offsetY = 0;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
        glVertex3f(gX, gY, 0);
        glVertex3f(gX + 0.5, gY, 0);
        glVertex3f(gX + 0.5, gY + 0.5, 0);
        glVertex3f(gX, gY + 0.5, 0);
    glEnd();
    glutSwapBuffers();
}

void mouseClick(int button, int state, int x, int y) {
    y = TAMANHO_JANELA - y;
    float normX = (float)x / TAMANHO_JANELA;
    float normY = (float)y / TAMANHO_JANELA;

    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            if (normX >= gX && normX <= gX + 0.5 &&
                normY >= gY && normY <= gY + 0.5) {
                mousePressionado = 1;
                offsetX = normX - gX;
                offsetY = normY - gY;
            }
        } else if (state == GLUT_UP) {
            mousePressionado = 0;
        }
    }
}

void mouseMove(int x, int y) {
    if (mousePressionado) {
        y = TAMANHO_JANELA - y;
        float normX = (float)x / TAMANHO_JANELA;
        float normY = (float)y / TAMANHO_JANELA;

        gX = normX - offsetX;
        gY = normY - offsetY;

        // Limites para manter dentro da janela
        if (gX < 0) gX = 0;
        if (gY < 0) gY = 0;
        if (gX > 0.5) gX = 0.5;
        if (gY > 0.5) gY = 0.5;

        glutPostRedisplay();
    }
}

void init(void) {
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, -1, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(TAMANHO_JANELA, TAMANHO_JANELA);
    glutCreateWindow("Arrastar quadrado");

    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMove);

    glutMainLoop();
    return 0;
}
