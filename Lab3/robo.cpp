#include "robo.h"
#include <math.h>

void Robo::DesenhaRect(GLint height, GLint width, GLfloat R, GLfloat G, GLfloat B)
{
    // Define a cor do retangulo 
    glColor3f(R, G, B);

    // Desenha o retangulo como um poligono
    glBegin(GL_POLYGON);
        // Vertice inferior esquerdo
        glVertex2f(-width / 2.0, 0.0);
        // Vertice inferior direito
        glVertex2f(width / 2.0, 0.0);
        // Vertice superior direito
        glVertex2f(width / 2.0, height);
        // Vertice superior esquerdo
        glVertex2f(-width / 2.0, height);
    glEnd();

}

void Robo::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{

}

void Robo::DesenhaRoda(GLfloat x, GLfloat y, GLfloat thetaWheel, GLfloat R, GLfloat G, GLfloat B)
{

}

void Robo::DesenhaBraco(GLfloat x, GLfloat y, GLfloat theta1, GLfloat theta2, GLfloat theta3)
{
    // Salva o S.C. atual (que será o do corpo do robô)
    glPushMatrix(); // 

    // 1. ---- Haste 1 (Azul) ----
    
    // Move para a posição inicial do braço (o "ombro")
    glTranslatef(x, y, 0.0); // [cite: 56]
    
    // Rotaciona a primeira haste
    glRotatef(theta1, 0, 0, 1.0); // [cite: 58]
    
    // Desenha a primeira haste (azul)
    // Usamos a mesma função, mas com as dimensões e cor do braço
    DesenhaRect(paddleHeight, paddleWidth, 0.0, 0.0, 1.0); // [cite: 62]

    // 4. ---- Finalização ----
    
    // Restaura o S.C. original (o do corpo do robô)
    glPopMatrix(); //

}

void Robo::DesenhaRobo(GLfloat x, GLfloat y, GLfloat thetaWheel, GLfloat theta1, GLfloat theta2, GLfloat theta3)
{
    glPushMatrix();

    // 1. Move o S.C. para a posição (x,y) do robô
    glTranslatef(x, y, 0.0);

    // 2. Desenha o Corpo do Robô (Caixa Vermelha)
    // A caixa é desenhada na origem do S.C. do Robô
    DesenhaRect(baseHeight, baseWidth, 1.0, 0.0, 0.0); // Vermelho

    // 3. Desenha o Braço (AQUI ESTÁ A CHAVE!)
    // Chamamos DesenhaBraco APÓS desenhar o corpo.
    // Passamos a posição RELATIVA de onde o braço começa
    // (0.0 em X, e baseHeight em Y - ou seja, no topo da caixa)
    DesenhaBraco(0.0, baseHeight, theta1, theta2, theta3);

    // (Aqui virá a DesenhaRoda)

    // 4. Restaura o S.C. do Mundo
    glPopMatrix();

}

void Robo::RodaBraco1(GLfloat inc)
{

}

void Robo::RodaBraco2(GLfloat inc)
{

}

void Robo::RodaBraco3(GLfloat inc)
{

}

void Robo::MoveEmX(GLfloat dx)
{
// A função idle chama isso ao apertar 'a' ou 'd' [cite: 45]
    // Apenas altera o estado (a variável gX) do robô [cite: 47]
    this->gX += dx;
}

//Funcao auxiliar de rotacao
void RotatePoint(GLfloat x, GLfloat y, GLfloat angle, GLfloat &xOut, GLfloat &yOut){

}

Tiro* Robo::Atira()
{

}
