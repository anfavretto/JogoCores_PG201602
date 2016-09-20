#pragma once
namespace Jogo {
	class Cor
	{
		float R;
		float G;
		float B;
	public:
		Cor(float r, float g, float b);

		float ObterR();
		float ObterG();
		float ObterB();
		bool EhProximo(Cor corBase);
		bool EhPreto();
	};

	class Retangulo
	{
		Cor* cor;
		bool visivel;
	public:
		Retangulo(float r, float g, float b);

		bool EstaVisivel();
		void AlterarVisibilidade(bool novaVisibilidade);
		Cor* ObterCor();
	};

}