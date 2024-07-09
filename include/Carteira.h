# ifndef CARTEIRA_H
# define CARTERIA_H

#include "Externo.h"
#include "Matematica.h"
#include "Acao.h"
#include <algorithm>


class Carteira
{
	private:
		vector<Acao>	_acoes;
		vector<double>	_pesos;

		/* Ajusta os pesos quando ocorre uma alteração nas ações da carteira. */
		void	_ajustarPesos(int idx);
		/* Auxilia na exibição formatada dos dados calculados nas estatisticas. */
		void	_mostrarEstatisticas(string texto, int precisao,
									const vector<double>& estatisticas) const;
		/* Auxilia na exibição formatada da matriz de correlações das ações. */
		void	_mostrarMatrizCorrelacao(const vector<vector<double> >& matriz) const;
		/* Auxilia na exibição formatada dos pesos e estatisticas da Carteira Otima. */
		void	_mostrarCarteriraOtima(const vector<vector<double> >& serieRetornos,
											const vector<double>& serieMedias,
											const vector<double>& serieRentabilidade,
											const vector<double>& pesos,
											const double& melhorSharpe) const;

	public:
		Carteira(void);
		~Carteira(void);

		/* Exibe o codigo de todas as ações que estão na carteira. */
		void	mostrar(void) const;
		/* Adiciona uma nova ação na carteira. */
		void	adicionar(string codigoAcao);
		/* Busca uma determinada ação na carteira. */
		Acao*	buscar(string codigoAcao);
		/* Remove uma ação da carteira. */
		void	remover(string codigoAcao);
		/* Configura o peso de cada ação na carteira. */
		void	setPesos(vector<double> pesos);

		void	rentabilidade(void) const;
		void	retornoMedio(void) const;
		void	riscoMedio(void) const;
		void	indiceSharpe(void) const;
		void	correlacao(void) const;
		void	carteiraOtima(void) const;
};

# endif
