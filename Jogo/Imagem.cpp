#include "Imagem.h"
#include <fstream>
#include <string>
#include <sstream>

Imagem::~Imagem()
{
}

Imagem::Imagem(int w, int h, int canais) {
	width = w;
	height = h;
	channels = canais;
	pixels = new unsigned char[w*h*channels];
}

Imagem::Imagem() {
}

void Imagem::setPixel(unsigned char *rgb, int x, int y) {
	for (int i = 0; i < channels; i++)
		pixels[i + x*channels + y*width*channels] = rgb[i];
}
unsigned char* Imagem::getPixel(int x, int y) {
	unsigned char *rgb = new unsigned char[channels];
	for (int i = 0; i < channels; i++)
		rgb[i] = pixels[i + x*channels + y*width*channels];
	return rgb;
}
int Imagem::getWidth() { return width; }
int Imagem::getHeight() { return height; }
int Imagem::getChannels() { return channels; }
unsigned char* Imagem::getPixels() { return pixels; }
//
//void Imagem::carregarImagem(string nomeArquivo) {
//	std::ifstream arq(nomeArquivo);
//	char conteudoLinha[256];
//	char tipoArquivo[256];
//	int larguraImagem = 0;
//	int alturaImagem = 0;
//	int maxValue = 0;
//	int contagemLinha = 1;
//	int contadorInterno = 1;
//	int r, g, b, a;
//	int xAtual = 0, yAtual = 0;
//
//	if (arq) {
//		while (!arq.eof()) {
//			if (contagemLinha == 1) {
//				arq >> tipoArquivo;
//				contagemLinha++;
//			}
//			else {
//
//				arq >> conteudoLinha;
//				if (conteudoLinha[0] != '#') {
//					if (contagemLinha == 2) {
//						width = atoi(conteudoLinha);
//					}
//					else if (contagemLinha == 3) {
//						height = atoi(conteudoLinha);
//					}
//					else if (contagemLinha == 4) {
//						maxValue = atoi(conteudoLinha);
//					}
//					else {
//						if (contadorInterno == 1) {
//							a = atoi(conteudoLinha);
//							contadorInterno++;
//						}
//						else if (contadorInterno == 2) {
//							r = atoi(conteudoLinha);
//							contadorInterno++;
//						}
//						else if (contadorInterno == 3) {
//							g = atoi(conteudoLinha);
//							contadorInterno++;
//						}
//						else {
//							b = atoi(conteudoLinha);
//							contadorInterno = 1;
//
//							setPixel(new unsigned char[4]{ (unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a }, xAtual, yAtual);
//
//							xAtual = incrementarX(xAtual, larguraImagem);
//							yAtual = incrementarY(yAtual, alturaImagem);
//						}
//
//					}
//					contagemLinha++;
//				}
//			}
//		}
//		arq.close();
//	}
//}

void Imagem::carregarImagem(string s) {
	ifstream arquivo(s);
	string tipo;
	int etapa = 0;
	arquivo >> tipo;
	if (tipo == "P7") {
		int max = 0;
		channels = 4;
		string linha;
		do {
			getline(arquivo, linha);
		} while (linha[0] == '#' || linha.size() == 0);

		while (linha.size() != 0) {
			switch (etapa) {
			case 0: {
				istringstream temp(linha);
				temp >> width >> height;
				pixels = new unsigned char[width*height * 4];
				etapa = 1;
			}
					break;
			case 1: {
				getline(arquivo, linha);
				istringstream temp(linha);
				temp >> max;
				etapa = 2;
			}
					break;
			case 2:
			{

				for (int y = height - 1; y >= 0; y--) {
					for (int x = 0; x < width; x++) {
						int px[4];
						arquivo >> px[0] >> px[1] >> px[2] >> px[3];
						unsigned char px2[4];
						px2[0] = (unsigned char)px[0];
						px2[1] = (unsigned char)px[1];
						px2[2] = (unsigned char)px[2];
						px2[3] = (unsigned char)px[3];
						setPixel(px2, x, y);
					}
				}
				etapa = 3;
			}
			break;
			case 3:
				linha = "";
				break;
			}
		}

		arquivo.close();
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
			unsigned char * px = this->getPixel(x + srcX, y + srcY);
			dest->setPixel(px, x, y);
		}
	}
}

void Imagem::plotar(Imagem *img, int x, int y) {
	for (int i = 0; i < img->getWidth(); i++) {
		for (int j = 0; j < img->getHeight(); j++) {
			unsigned char *nc = img->getPixel(i, j);
			this->setPixel(nc, x + i, y + j);
		}
	}
}