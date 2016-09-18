#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <time.h>
#include "Jogo.h"
#include "Imagem.h"
#include <stdlib.h>
#include <string.h>
#include<fstream>

using namespace Jogo;
using namespace std;

const int TotalRetangulosComprimento = 20;
const int TotalRetangulosAltura = 40;
const int TamanhoJanelaDesenho = 40;
const int TamanhoJanela = 45;
const GLdouble CoordenadaInicial = 0.0;
const GLdouble CoordenadaFinalX = 40.0;
const GLdouble CoordenadaFinalY = 42.0;
const int CanaisRGB = 3;
const GLdouble AlturaRetangulo = 1;
const GLdouble LarguraRetangulo = 2;
const int NumeroMaximoDeJogadas = 4;
const int ValorPontosPrimeiraRodada = 10;
const int ValorPontosSegundaRodada = 5;
const int ValorPontosTerceiraRodada = 2;
const int ValorPontosQuartaRodada = 1;

GLfloat ultimoX = -1.0, ultimoY = -1.0;
int LarguraJanelaPixels = 800;
int AlturaJanelaPixels = 640;
vector<Retangulo> retangulos;
GLdouble AlturaBarraPontuacao;
int JogadasEfetuadas;
int PontosJogador = 0;
Imagem* letras = new Imagem();


void init() {
	//Selecionando a cor para limpar cor de fundo
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glViewport(0, 0, (GLsizei)LarguraJanelaPixels, (GLsizei)AlturaJanelaPixels);

	//Inicializa a visualização
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(CoordenadaInicial, CoordenadaFinalX, CoordenadaFinalY, CoordenadaInicial, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	letras->carregarImagem("C:\\Users\\Aline\\Documents\\Unisinos\\Processamento Gráfico\\Aulas\\Aula 6\\arial.ptm");
}

float ObterComponenteDeCor() {
	return rand() % 256;
}

void reset() {
	JogadasEfetuadas = 0;
	retangulos.clear();
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
	AlturaJanelaPixels = h;
	LarguraJanelaPixels = w;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(CoordenadaInicial, CoordenadaFinalX, CoordenadaFinalY, CoordenadaInicial, -1.0, 1.0);

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

void ExibirPontuacao() {
	char txt[16];
	sprintf_s(txt, "%s%d", "PONTUACAO:", PontosJogador);

	int xDest = 0, yDest = 0;

	Imagem* pontuacaoExibir = new Imagem(800, 30);
	
	for (int i = 0; i < sizeof(txt); i++) {
		switch (txt[i])
		{
		case '0':
			letras->subimage(pontuacaoExibir, 0, 47); break;
		case '1':
			letras->subimage(pontuacaoExibir, 16, 47); break;
		case '2':
			letras->subimage(pontuacaoExibir, 32, 47); break;
		case '3':
			letras->subimage(pontuacaoExibir, 48, 47); break;
		case '4':
			letras->subimage(pontuacaoExibir, 64, 47); break;
		case '5':
			letras->subimage(pontuacaoExibir, 80, 47); break;
		case '6':
			letras->subimage(pontuacaoExibir, 96, 47); break;
		case '7':
			letras->subimage(pontuacaoExibir, 112, 47); break;
		case '8':
			letras->subimage(pontuacaoExibir, 128, 47); break;
		case '9':
			letras->subimage(pontuacaoExibir, 144, 47); break;
		case ':':
			letras->subimage(pontuacaoExibir, 160, 47); break;
		case 'P':
			letras->subimage(pontuacaoExibir, 0, 80); break;
		case 'O':
			letras->subimage(pontuacaoExibir, 176, 47); break;
		case 'N':
			letras->subimage(pontuacaoExibir, 192, 47); break;
		case 'T':
			letras->subimage(pontuacaoExibir, 208, 47); break;
		case 'U':
			letras->subimage(pontuacaoExibir, 224, 47); break;
		case 'A':
			letras->subimage(pontuacaoExibir, 48, 47); break;
		case 'C':
			letras->subimage(pontuacaoExibir, 48, 47); break;
			break;
		default:
			break;
		}
		xDest += 16;
	}
	glDrawPixels(pontuacaoExibir->getWidth(), pontuacaoExibir->getHeight(), GL_BGR_EXT, GL_UNSIGNED_BYTE, pontuacaoExibir->getPixels());

	//glFlush();
}

void TerminarJogo() {
	//GLint x = (10.0 * LarguraJanelaPixels) / TamanhoJanela;
	//GLint y = AlturaJanelaPixels - ((41.0 * AlturaJanelaPixels) / TamanhoJanela);

	/*glColor3f(1.0, 1.0, 1.0);
	glRasterPos2i(15, 15);
	printString("Fim de jogo");
	glFlush();*/
}

int AumentarPontuacao(int pontosRodada) {
	switch (JogadasEfetuadas)
	{
	case 1:
		return pontosRodada + ValorPontosPrimeiraRodada;
	case 2:
		return pontosRodada + ValorPontosSegundaRodada;
	case 3:
		return pontosRodada + ValorPontosTerceiraRodada;
	default:
		return pontosRodada + ValorPontosQuartaRodada;
	}
}

void Jogar(GLubyte* corSelecionadaTela) {
	JogadasEfetuadas++;
	int pontosRodada = 0;

	Cor corSelecionada = Cor(corSelecionadaTela[0], corSelecionadaTela[1], corSelecionadaTela[2]);

	for (vector<Retangulo>::iterator retanguloAtual = retangulos.begin(); retanguloAtual != retangulos.end(); ++retanguloAtual) {
		if (retanguloAtual->EstaVisivel()) {
			Cor* corRetangulo = retanguloAtual->ObterCor();
			bool coresParecidas = corRetangulo->EhProximo(corSelecionada);

			if (coresParecidas) {
				retanguloAtual->AlterarVisibilidade(false);
				pontosRodada = AumentarPontuacao(pontosRodada);
			}
		}
	}
	PontosJogador += pontosRodada;
	ExibirPontuacao();
	if (JogadasEfetuadas == NumeroMaximoDeJogadas) {
		TerminarJogo();
	}
}

void tratarTeclado(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		reset();
	}
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
	if (JogadasEfetuadas < NumeroMaximoDeJogadas) {
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		{
			GLubyte *rgb = ObterCorSelecionada();
			Jogar(rgb);
		}
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

	//Define a função de callback para redimensionar
	glfwSetWindowSizeCallback(window, redimensionar);

	//Define a função de callback para tratar eventos do teclado
	glfwSetKeyCallback(window, tratarTeclado);

	//Define a função de callback para tratar eventos do mouse
	glfwSetMouseButtonCallback(window, tratarMouse);

	//Define a função de callback para tratar posição do mouse
	glfwSetCursorPosCallback(window, tratarPosMouse);


	//Inicializa a camera
	init();

	reset(); // inicializa vetor de retangulos e contagem de jogadas.

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