#pragma once
#include <iostream>
using namespace std;

class Imagem
{
public:
	Imagem(int w, int h, int canais);
	Imagem();
	~Imagem();

	void setPixel(unsigned char *rgb, int x, int y);
	unsigned char* getPixel(int x, int y);
	int getWidth();
	int getHeight();
	int getChannels();
	unsigned char* getPixels();
	void carregarImagem(string nomeArquivo);
	void subimage(Imagem *dest, int srcX, int srcY);
	void plotar(Imagem *i, int x, int y);
private:
	unsigned char *pixels;
	int width;
	int height;
	int channels;
	int incrementarX(int xAtual, int larguraImagem);
	int incrementarY(int xAtual, int alturaImagem);
};
