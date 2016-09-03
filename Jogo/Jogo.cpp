#include "Jogo.h"


Jogo::Retangulo::Retangulo(float r, float g, float b)
{
	visivel = true;
	R = r;
	G = g;
	B = b;
}

bool Jogo::Retangulo::EstaVisivel() {
	return visivel;
}

float Jogo::Retangulo::ObterR() {
	return R;
}

float Jogo::Retangulo::ObterG() {
	return G;
}

float Jogo::Retangulo::ObterB() {
	return B;
}