#include "Fonte.h"
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <GLFW/glfw3.h>

Fonte::Fonte(string nome, int larguraCaract, int alturaCaract)
{
	alturaCaracter = alturaCaract;
	larguraCaracter = larguraCaract;
	base = new Imagem;
	base->carregarImagem(nome);
	for (int y = base->getHeight() - alturaCaracter; y >= 0; y -= alturaCaracter) {
		for (int x = 0; x < base->getWidth(); x += larguraCaracter) {
			Imagem *c = new Imagem(larguraCaracter, alturaCaracter, base->getChannels());
			base->subimage(c, x, y);
			caracteres.push_back(c);
		}
	}
}

void Fonte::escrever(string texto, int sx, int sy) {
	int basex = sx;
	int basey = sy;
	for (int s = 0; s < texto.length(); s++) {
		glRasterPos2i(basex, basey);
		glDrawPixels(larguraCaracter, alturaCaracter, GL_BGRA_EXT, GL_UNSIGNED_BYTE,
			caracteres[(int)texto[s]]->getPixels());
		basex += 1;
	}
}

Imagem *Fonte::getCaracter(int i) {
	return caracteres[i];
}
Fonte::~Fonte()
{
}