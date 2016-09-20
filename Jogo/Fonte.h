#pragma once
#include "Imagem.h"
#include <vector>
using namespace std;

class Fonte
{
public:
	Fonte(string nome, int larguraCaractere, int alturaCaractere);
	~Fonte();

	void escrever(string texto, int x, int y);
	Imagem *getCaracter(int i);
private:
	Imagem *base;
	int alturaCaracter, larguraCaracter;
	vector<Imagem*> caracteres;
};