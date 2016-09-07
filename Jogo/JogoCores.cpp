#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <time.h>
#include "Jogo.h"


using namespace Jogo;
using namespace std;

const int TotalRetangulosComprimento = 20;
const int TotalRetangulosAltura = 40;
const int LarguraJanelaPixels = 800;
const int AlturaJanelaPixels = 640;
const int TamanhoJanelaDesenho = 40;
const int TamanhoJanela = 45;
const GLdouble CoordenadaInicial = 0.0;
const GLdouble CoordenadaFinal = 40.0;
const int CanaisRGB = 3;
const GLdouble AlturaRetangulo = 1;
const GLdouble LarguraRetangulo = 2;

GLfloat ultimoX = -1.0, ultimoY = -1.0;
vector<Retangulo> retangulos;
GLdouble AlturaBarraPontuacao;


void init() {
	//Selecionando a cor para limpar cor de fundo
	glClearColor(0.0, 0.0, 0.0, 0.0);

	//Inicializa a visualização
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(CoordenadaInicial, CoordenadaFinal, CoordenadaInicial, CoordenadaFinal, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void drawRect(GLdouble x, GLdouble y, GLdouble w, GLdouble h, float r, float g, float b) {
	glColor3ub(r, g, b);
	glVertex2d(x, y); // ponto esquerda inferior
	glVertex2d(x, y + h); // ponto esquerda superior
	glVertex2d(x + w, y + h);// ponto direita superior
	glVertex2d(x + w, y); // ponto direita inferior
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT);
	int indiceRetanguloAtual = 0;
	
	GLdouble xx; // Canto 0 da tela
	GLdouble yy = 0;
	
	for (int y = 0; y < TotalRetangulosAltura; y++) {
		xx = 0;
		for (int x = 0; x < TotalRetangulosComprimento; x++) {
			Retangulo retanguloAtual = retangulos[indiceRetanguloAtual];

			if (retanguloAtual.EstaVisivel()) {
				glBegin(GL_QUADS);
					Cor *corRetangulo = retanguloAtual.ObterCor();
					drawRect(xx, yy, LarguraRetangulo, AlturaRetangulo, corRetangulo->ObterR(), corRetangulo->ObterG(), corRetangulo->ObterB());
				glEnd();
			}
			indiceRetanguloAtual++;
			xx += LarguraRetangulo; // aumento na largura para desenhar próximo retângulo
		}
		yy += AlturaRetangulo; // aumenta altura base para desenhar próximo retângulo
	}
	AlturaBarraPontuacao = yy;
}

void redimensionar(GLFWwindow *window, int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(CoordenadaInicial, CoordenadaFinal, CoordenadaInicial, CoordenadaFinal, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

GLubyte* ObterCorSelecionada() {
	GLubyte *pixels = new unsigned char[3];
	//Conversão da coordenada para coordenada de tela.
	int xTela = (ultimoX * LarguraJanelaPixels) / TamanhoJanelaDesenho;
	int yTela = (ultimoY * AlturaJanelaPixels) / TamanhoJanelaDesenho;

	glReadPixels(xTela, AlturaJanelaPixels - yTela, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixels);

	GLubyte *rgb = new GLubyte[CanaisRGB];

	rgb[0] = pixels[0];
	rgb[1] = pixels[1];
	rgb[2] = pixels[2];

	return rgb;
}

void Jogar(GLubyte* corSelecionadaTela) {
	Cor corSelecionada = Cor(corSelecionadaTela[0], corSelecionadaTela[1], corSelecionadaTela[2]);
	
	for (vector<Retangulo>::iterator retanguloAtual = retangulos.begin(); retanguloAtual != retangulos.end(); ++retanguloAtual) {
		Cor* corRetangulo = retanguloAtual->ObterCor();
		bool coresParecidas = corRetangulo->EhProximo(corSelecionada);

		if (coresParecidas) {
			retanguloAtual->AlterarVisibilidade(false);
		}
	}
}

void tratarTeclado(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	/*Sem tratamento de teclado ainda.*/
}

static void tratarPosMouse(GLFWwindow* window, double xpos, double ypos)
{	
	float xx = xpos / (float)LarguraJanelaPixels; 
	ultimoX = xx * TamanhoJanelaDesenho;

	float yy = ypos / (float)AlturaJanelaPixels; 
	ultimoY = yy * TamanhoJanelaDesenho; 
}

void tratarMouse(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		GLubyte *rgb = ObterCorSelecionada();
		Jogar(rgb);
	}
}

float ObterComponenteDeCor() {
	return rand() % 256;
}

void reset() {
	float r, g, b;
	srand((unsigned)time(NULL));
	int tamanhoVetorRetangulos = TotalRetangulosAltura * TotalRetangulosComprimento;

	for (int indice = 0; indice < tamanhoVetorRetangulos; indice++) {
		
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
	window = glfwCreateWindow(LarguraJanelaPixels, AlturaJanelaPixels, "Jogo das Cores", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	//Torna a janela o contexto ativo
	glfwMakeContextCurrent(window);

	//Define a função de callback para redimensionar - PROBLEMA DE LEITURA DE COR AO REDIMENSIONAR
	//glfwSetWindowSizeCallback(window, redimensionar);

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