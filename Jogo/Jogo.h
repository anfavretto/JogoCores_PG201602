#pragma once
namespace Jogo {
	class Retangulo
	{
		float R;
		float G;
		float B;
		bool visivel;
	public:
		Retangulo(float r, float g, float b);

		bool EstaVisivel();
		float ObterR();
		float ObterG();
		float ObterB();
	};
}