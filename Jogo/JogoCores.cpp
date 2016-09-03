#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Jogo.h"

using namespace Jogo;
using namespace std;


GLfloat xb = 0.25, yb = 0.25;
GLfloat ultimoX = -1.0, ultimoY = -1.0;
GLubyte r, g, b;
vector<Retangulo> retangulos;
vector<Retangulo>::iterator iterador;


void init() {
	r = g = b = 255;

	//Selecionando a cor para limpar cor de fundo
	glClearColor(0.0, 0.0, 0.0, 0.0);

	//Inicializa a visualização
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 40.0, 0.0, 40.0, -1.0, 1.0);
}

void drawRect(float x, float y, float w, float h, float r, float g, float b) {
	glColor3ub(r, g, b);
	glVertex2d(x, y); // ponto esquerda inferior
	glVertex2d(x, y + h); // ponto esquerda superior
	glVertex2d(x + w, y + h);// ponto direita superior
	glVertex2d(x + w, y); // ponto direita inferior
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT);
	int altura = 1;
	int largura = 2;
	int indiceRetanguloAtual = 0;

	float xx; // Canto 0 da tela
	float yy = 0;
	glBegin(GL_QUADS);
	for (int y = 0; y < 40; y++) {
		xx = 0;
		for (int x = 0; x < 20; x++) {
			Retangulo retanguloAtual = retangulos[indiceRetanguloAtual];

			drawRect(xx, yy, largura, altura, retanguloAtual.ObterR(), retanguloAtual.ObterG(), retanguloAtual.ObterB());

			indiceRetanguloAtual++;
			xx += largura; // aumento na largura para desenhar próximo retângulo
		}
		yy += altura; // aumenta altura base para desenhar próximo retângulo
	}
	glEnd();
	glFlush();
}

void tratarTeclado(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)	xb += 0.01;
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)	xb -= 0.01;
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)	yb += 0.01;
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)	yb -= 0.01;
}

static void tratarPosMouse(GLFWwindow* window, double xpos, double ypos)
{
	if (ultimoX == -1.0) ultimoX = xpos;
	if (ultimoY == -1.0) ultimoX = ypos;

	if (xpos - ultimoX > 0) xb += 0.01;
	if (xpos - ultimoX < 0) xb -= 0.01;
	if (ypos - ultimoY > 0) yb -= 0.01;
	if (ypos - ultimoY < 0) yb += 0.01;

	ultimoX = xpos;
	ultimoY = ypos;
}

void tratarMouse(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		r = rand() % 256;
		g = rand() % 256;
		b = rand() % 256;
	}
}

float ObterComponenteDeCor() {
	return rand() % 256;
}

void reset() {
	float r, g, b;

	for (int indice = 0; indice < 800; indice++) {
		r = ObterComponenteDeCor();
		g = ObterComponenteDeCor();
		b = ObterComponenteDeCor();

		Retangulo *novoRetangulo = new Retangulo(r, g, b);
		retangulos.push_back(*novoRetangulo);
	}	
}

int CALLBACK WinMain(
	__in  HINSTANCE hInstance,
	__in  HINSTANCE hPrevInstance,
	__in  LPSTR lpCmdLine,
	__in  int nCmdShow
) {
	GLFWwindow* window;

	//Inicializar a biblioteca
	if (!glfwInit())
		return -1;

	//Criar a a janela
	window = glfwCreateWindow(660, 500, "Jogo das Cores", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	//Torna a janela o contexto ativo
	glfwMakeContextCurrent(window);

	//Define a função de callback para tratar eventos do teclado
	glfwSetKeyCallback(window, tratarTeclado);

	//Define a função de callback para tratar eventos do mouse
	glfwSetMouseButtonCallback(window, tratarMouse);

	//Define a função de callback para tratar posição do mouse
	glfwSetCursorPosCallback(window, tratarPosMouse);


	//Inicializa a camera
	init();

	reset(); // inicializa vetor de retangulos
		
	//Faça o loop até fechar a janela
	while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		render(); // desenha

		//Swap dos buffers
		glfwSwapBuffers(window);

		//Processa eventos
		glfwPollEvents();
	}

	//Encerra
	glfwTerminate();
	return 0;
}