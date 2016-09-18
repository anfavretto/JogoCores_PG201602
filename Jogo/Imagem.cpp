#include "Imagem.h"
#include<fstream>

Imagem::~Imagem()
{
}

Imagem::Imagem(int w, int h) {
	width = w;
	height = h;
	pixels = new unsigned char[w*h*channels];
}

Imagem::Imagem() {
}

void Imagem::setPixel(char *rgb, int x, int y) {
	for (int i = 0; i < channels; i++)
		pixels[i + x*channels + y*width*channels] = rgb[i];
}
char* Imagem::getPixel(int x, int y) {
	char *rgb = new char[channels];
	for (int i = 0; i < channels; i++)
		rgb[i] = pixels[i + x*channels + y*width*channels];
	return rgb;
}
int Imagem::getWidth() { return width; }
int Imagem::getHeight() { return height; }
int Imagem::getChannels() { return channels; }
unsigned char* Imagem::getPixels() { return pixels; }

void Imagem::carregarImagem(char* nomeArquivo) {
	std::ifstream arq(nomeArquivo);
	char conteudoLinha[256];
	char tipoArquivo[256];
	int larguraImagem = 0;
	int alturaImagem = 0;
	int maxValue = 0;
	int contagemLinha = 1;
	int contadorInterno = 1;
	int r, g, b, a;
	int xAtual = 0, yAtual = 0;

	if (arq) {
		while (!arq.eof()) {
			if (contagemLinha == 1) {
				arq >> tipoArquivo;
				contagemLinha++;
			}
			else {

				arq >> conteudoLinha;
				if (conteudoLinha[0] != '#') {
					if (contagemLinha == 2) {
						width = atoi(conteudoLinha);
					}
					else if (contagemLinha == 3) {
						height = atoi(conteudoLinha);
					}
					else if (contagemLinha == 4) {
						maxValue = atoi(conteudoLinha);
					}
					else {
						if (contadorInterno == 1) {
							a = atoi(conteudoLinha);
							contadorInterno++;
						}
						else if (contadorInterno == 2) {
							r = atoi(conteudoLinha);
							contadorInterno++;
						}
						else if (contadorInterno == 3) {
							g = atoi(conteudoLinha);
							contadorInterno++;
						}
						else {
							b = atoi(conteudoLinha);
							contadorInterno = 1;

							setPixel(new char[4]{ (char)r, (char)g, (char)b, (char)a }, xAtual, yAtual);

							xAtual = incrementarX(xAtual, larguraImagem);
							yAtual = incrementarY(yAtual, alturaImagem);
						}

					}
					contagemLinha++;
				}
			}
		}
		arq.close();
	}
}

int Imagem::incrementarX(int xAtual, int larguraImagem) {
	if (xAtual < larguraImagem)
		return ++xAtual;
	else
		return 0;
}

int Imagem::incrementarY(int yAtual, int alturaImagem) {
	if (yAtual < alturaImagem)
		return ++yAtual;
	else
		return 0;
}

void Imagem::subimage(Imagem *dest, int srcX, int srcY) {
	for (int x = 0; x < dest->getWidth(); x++) {
		for (int y = 0; y < dest->getHeight(); y++) {
			char * px = getPixel(x + srcX, y + srcY);
			dest->setPixel(px, x, y);
		}
	}
}

void Imagem::subimage(Imagem *dest, int srcX, int srcY, int destX, int destY) {
	char * px = getPixel(srcX, srcY);
	dest->setPixel(px, destX, destY);
}