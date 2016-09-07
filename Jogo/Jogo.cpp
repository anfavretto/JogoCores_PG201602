#include "Jogo.h"
#include <math.h>


Jogo::Retangulo::Retangulo(float r, float g, float b)
{
	visivel = true;
	cor = new Jogo::Cor(r, g, b);
}

bool Jogo::Retangulo::EstaVisivel() {
	return visivel;
}

void Jogo::Retangulo::AlterarVisibilidade(bool novaVisibilidade) {
	visivel = novaVisibilidade;
}

Jogo::Cor* Jogo::Retangulo::ObterCor() {
	return cor;
}


Jogo::Cor::Cor(float r, float g, float b) {
	R = r;
	G = g;
	B = b;
}

float Jogo::Cor::ObterR() {
	return R;
}
float Jogo::Cor::ObterG() {
	return G;
}
float Jogo::Cor::ObterB() {
	return B;
}
bool Jogo::Cor::EhProximo(Cor corBase) {
	//d = raiz de (R selecionada - R comparando)² + (G selecionada - G comparando)² + (B selecionada - B comparando)²
	float diferencaR = corBase.ObterR() - ObterR();
	float diferencaG = corBase.ObterG() - ObterG();
	float diferencaB = corBase.ObterB() - ObterB();

	float quadradoR = pow(diferencaR, 2.0);
	float quadradoG = pow(diferencaG, 2.0);
	float quadradoB = pow(diferencaB, 2.0);

	float diferencaCores = sqrt(quadradoR + quadradoG + quadradoB);

	float distanciaMax = sqrt(pow((0 - 255), 2) + pow((0 - 255), 2) + pow((0 - 255), 2));

	float distanciaEncontrada = diferencaCores / distanciaMax;

	return distanciaEncontrada <= 0.15;
}