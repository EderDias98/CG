#include <GL/glut.h>
#include <stdio.h>

// -----------------------------------------------
// VARIÁVEIS GLOBAIS
// -----------------------------------------------

// Posição do quadrado
float gX = 0.0f, gY = 0.0f;

// Estado das teclas (pressionada = 1, solta = 0)
int keyStatus[256] = {0};

// Controle de arraste com o mouse
int dragging = 0;           // 1 se o quadrado estiver sendo arrastado
float clickOffsetX = 0.0f;  // diferença entre o clique e a origem do quadrado
float clickOffsetY = 0.0f;

// Tamanho fixo da janela
const int windowWidth = 500;
const int windowHeight = 500;

// -----------------------------------------------
// FUNÇÃO DE DESENHO
// -----------------------------------------------
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Define cor branca
    glColor3f(1.0f, 1.0f, 1.0f);

    // Desenha o quadrado nas posições deslocadas por gX, gY
    glBegin(GL_QUADS);
        glVertex2f(0.25f + gX, 0.25f + gY);
        glVertex2f(0.75f + gX, 0.25f + gY);
        glVertex2f(0.75f + gX, 0.75f + gY);
        glVertex2f(0.25f + gX, 0.75f + gY);
    glEnd();

    glFlush();
}

// -----------------------------------------------
// TECLADO – pressionar e soltar
// -----------------------------------------------
void keyPress(unsigned char key, int x, int y) {
    keyStatus[(int)key] = 1;  // marca tecla como pressionada
}

void keyUp(unsigned char key, int x, int y) {
    keyStatus[(int)key] = 0;  // marca tecla como solta
}

// -----------------------------------------------
// MOUSE – clique e movimento
// -----------------------------------------------
void mouse(int button, int state, int x, int y) {
    // Converte pixel -> coordenadas normalizadas (0 a 1)
    float xNorm = (float)x / windowWidth;
    float yNorm = 1.0f - ((float)y / windowHeight); // inverte o eixo Y

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Verifica se o clique foi dentro do quadrado
        if (xNorm >= 0.25f + gX && xNorm <= 0.75f + gX &&
            yNorm >= 0.25f + gY && yNorm <= 0.75f + gY) {
            
            dragging = 1; // começa arraste
            // Calcula o deslocamento entre o clique e a origem do quadrado
            clickOffsetX = xNorm - gX;
            clickOffsetY = yNorm - gY;
        }
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        dragging = 0; // solta o arraste
    }
}

// Função chamada quando o mouse se move com botão pressionado
void motion(int x, int y) {
    if (dragging) {
        float xNorm = (float)x / windowWidth;
        float yNorm = 1.0f - ((float)y / windowHeight);

        // Atualiza a posição do quadrado mantendo o offset do clique
        gX = xNorm - clickOffsetX;
        gY = yNorm - clickOffsetY;

        glutPostRedisplay();
    }
}

// -----------------------------------------------
// FUNÇÃO IDLE – movimentação contínua do teclado
// -----------------------------------------------
void idle(void) {
    float speed = 0.001f; // velocidade de movimento

    if (keyStatus['a']) gX -= speed;
    if (keyStatus['d']) gX += speed;
    if (keyStatus['w']) gY += speed;
    if (keyStatus['s']) gY -= speed;

    glutPostRedisplay(); // redesenha continuamente
}

// -----------------------------------------------
// INICIALIZAÇÃO DO OPENGL
// -----------------------------------------------
void init() {
    // Define cor de fundo (preto)
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Projeção ortográfica 2D (0,0) no canto inferior esquerdo
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);
}

// -----------------------------------------------
// FUNÇÃO PRINCIPAL
// -----------------------------------------------
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Quadrado Interativo - Teclado e Mouse");

    init();

    // Registra as funções de callback
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyUp);
    glutIdleFunc(idle);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutMainLoop();
    return 0;
}

