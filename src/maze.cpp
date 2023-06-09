// OPENGL MAZE GAME.
// Created on Fri 09 Jun 2023 08∶45∶06 AM -03 by Vitor Gabriel da Silva Ruffo.
 
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>

void myInit(void);
void myDisplay(void);
void keyboard(unsigned char key, int x, int y);
void handle_mouse_passive_motion (GLint x, GLint y);
void start_game(double r, double g, double b);
int isMouseInsideRectangle(int mx, int my, int x1, int y1, int x2, int y2);
void drawMaze();
int isMouseInsideRectangle(int mx, int my, int x1, int y1, int x2, int y2);
int isMouseInsideMaze(int mx, int my);
int isGameFinished(int mx, int my);

int main(int argc, char** argv){
    glutInit(&argc, argv); // Inicializa o GLUT e processa qualquer parâmetro passado pela linha de comandos. Deve ser chamada antes de qualquer outra rotina GLUT.
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // Especifica como o vídeo será utilizado, no caso será alocado um buffer e o sistema de cor será RGB.
    glutInitWindowSize (1080, 720); // Especifica as dimensões da janela em pixels.
    glutInitWindowPosition (420, 200); // Especifica a coordenada superior esquerda da janela. Define a localização da janela dentro da tela
    glutCreateWindow ("Maze"); // Cria a janela e devolve um identificador único para a janela. Até que o comando glutMainLoop seja chamado, a janela não será mostrada.
    myInit(); // Rotina que implementa as configurações iniciais do programa.
    glutDisplayFunc(myDisplay); // Chamada para a função de desenho
        // Toda vez que o GLUT determinar que a janela tem de ser desenhada, ele chamará a função aqui determinada.
    
    //keyboard:
    glutKeyboardFunc(keyboard); // Determinam as funções que usaremos para ler o teclado e o mouse respectivamente.
    //mouse:
    glutPassiveMotionFunc(handle_mouse_passive_motion);

    glutMainLoop( ); // É o último comando que chamamos. Ele faz com que todas as janelas criadas sejam mostradas. Uma vez que entramos neste loop, só saímos quando o programa se encerra.
    return 0;
    
}

void myInit(void){
    
    glClearColor(0.0,0.0,0.0,0.0);     // cor de fundo branco
    glColor3f(1.0f, 1.0f, 1.0f);          // Define cor corrente de desenho
    glPointSize(4.0);             // Define o tamanho do ponto: 4 por 4 pixels
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
                                           // janela com resolução de 640 por 480
    gluOrtho2D(0.0, 1080.0, 720.0, 0.0);
    
    glClear(GL_COLOR_BUFFER_BIT); // limpa a janela
    glutSwapBuffers();
    glutWarpPointer(73, 570); //mouse start position

}


void myDisplay(void){
    start_game(0, 0, 0);
}

void keyboard(unsigned char key, int x, int y){
    switch (key) {
        case 27: //termina o programa com a tecla Esc
            exit(0);
            break;
    }
}

void handle_mouse_passive_motion (GLint x, GLint y){
    printf("loc: x:%d; y:%d\n", x, y);
    if(isMouseInsideMaze(x, y) == 0){
        printf("Defeat!\n");
        start_game(1.0, 0.0, 0.0);
        return;
    }else{
        if(isGameFinished(x, y) == 1){
            printf("Victory!\n");
            start_game(0.0, 1.0, 0.0);
        }
        return;
    }
}


void start_game(double r, double g, double b){
    glClearColor(0.0,0.0,0.0,0.0);     // cor de fundo branco
    glClear(GL_COLOR_BUFFER_BIT); // limpa a janela
    

    glClearColor(r,g,b,0.0);     // cor de fundo branco
    glClear(GL_COLOR_BUFFER_BIT); // limpa a janela
    drawMaze();
    glutSwapBuffers();

    for(int i = 0; i<50000; i++)
        glutWarpPointer(73, 570); //mouse start position


    glClearColor(0.0,0.0,0.0,0.0);     // cor de fundo branco
    glClear(GL_COLOR_BUFFER_BIT); // limpa a janela
    drawMaze();
    glutSwapBuffers();
}

void drawMaze(){
    glRecti(100, 50, 150, 670);
    glRecti(50, 550, 100, 600);
    glRecti(150, 50, 550, 100);
    glRecti(600, 50, 980, 100);
    glRecti(930, 50, 980, 670);
    glRecti(980, 250, 1030, 300); //final square...
    glRecti(150, 620, 690, 670);
    glRecti(740, 620, 980, 670);
    glRecti(190, 460, 240, 580);
    glRecti(190, 530, 890, 580);
    glRecti(840, 320, 890, 580);
    glRecti(840, 140, 890, 280);
    glRecti(190, 140, 890, 190);
    glRecti(190, 140, 240, 420);
    glRecti(280, 230, 330, 490);
    glRecti(280, 440, 800, 490);
    glRecti(280, 230, 520, 280);
    glRecti(560, 230, 800, 280);
    glRecti(750, 230, 800, 480);
    glRecti(370, 320, 710, 400);
    glRecti(600, 400, 650, 450);
    glRecti(240, 280, 290, 330);
    glRecti(800, 390, 850, 440);
    glRecti(750, 100, 800, 150);
    glRecti(340, 580, 390, 630);
}

int isMouseInsideRectangle(int mx, int my, int x1, int y1, int x2, int y2){
    bool r1 = mx >= x1 && mx <= x2;
    bool r2 = my >= y1 && my <= y2;
    return (r1 && r2) ? 1:0;
}

int isMouseInsideMaze(int mx, int my){
    int accumulator = 0;
    accumulator += isMouseInsideRectangle(mx, my, 100, 50, 150, 670);
    accumulator += isMouseInsideRectangle(mx, my, 50, 550, 100, 600);
    accumulator += isMouseInsideRectangle(mx, my, 150, 50, 550, 100);
    accumulator += isMouseInsideRectangle(mx, my, 600, 50, 980, 100);
    accumulator += isMouseInsideRectangle(mx, my, 930, 50, 980, 670);
    accumulator += isMouseInsideRectangle(mx, my, 980, 250, 1030, 300); //final square...
    accumulator += isMouseInsideRectangle(mx, my, 150, 620, 690, 670);
    accumulator += isMouseInsideRectangle(mx, my, 740, 620, 980, 670);
    accumulator += isMouseInsideRectangle(mx, my, 190, 460, 240, 580);
    accumulator += isMouseInsideRectangle(mx, my, 190, 530, 890, 580);
    accumulator += isMouseInsideRectangle(mx, my, 840, 320, 890, 580);
    accumulator += isMouseInsideRectangle(mx, my, 840, 140, 890, 280);
    accumulator += isMouseInsideRectangle(mx, my, 190, 140, 890, 190);
    accumulator += isMouseInsideRectangle(mx, my, 190, 140, 240, 420);
    accumulator += isMouseInsideRectangle(mx, my, 280, 230, 330, 490);
    accumulator += isMouseInsideRectangle(mx, my, 280, 440, 800, 490);
    accumulator += isMouseInsideRectangle(mx, my, 280, 230, 520, 280);
    accumulator += isMouseInsideRectangle(mx, my, 560, 230, 800, 280);
    accumulator += isMouseInsideRectangle(mx, my, 750, 230, 800, 480);
    accumulator += isMouseInsideRectangle(mx, my, 370, 320, 710, 400);
    accumulator += isMouseInsideRectangle(mx, my, 600, 400, 650, 450);
    accumulator += isMouseInsideRectangle(mx, my, 240, 280, 290, 330);
    accumulator += isMouseInsideRectangle(mx, my, 800, 390, 850, 440);
    accumulator += isMouseInsideRectangle(mx, my, 750, 100, 800, 150);
    accumulator += isMouseInsideRectangle(mx, my, 340, 580, 390, 630);
    return accumulator;
}

int isGameFinished(int mx, int my){
    return isMouseInsideRectangle(mx, my, 980, 250, 1030, 300); //this is the final square...
}