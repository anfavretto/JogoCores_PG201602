#pragma once
class Imagem
{
public:
	Imagem(int w, int h);
	Imagem();
	~Imagem();

	void setPixel(char *rgb, int x, int y);
	char* getPixel(int x, int y);
	int getWidth();
	int getHeight();
	int getChannels();
	unsigned char* getPixels();
	void carregarImagem(char* nomeArquivo);
	void subimage(Imagem *dest, int srcX, int srcY);
	void subimage(Imagem *dest, int srcX, int srcY, int destX, int destY);
private:
	unsigned char *pixels;
	int width;
	int height;
	int channels;
	int incrementarX(int xAtual, int larguraImagem);
	int incrementarY(int xAtual, int alturaImagem);
};
