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
		void	_ajustarPesos(void);
		/* Auxilia na exibição formatada dos dados calculados nas estatisticas. */
		void	_mostrarEstatisticas(string texto, int precisao,
									const vector<double>& estatisticas) const;

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

		void	rentabilidade(void) const;
		void	retornoMedio(void) const;
		void	riscoMedio(void) const;
		void	indiceSharpe(void) const;
		void	correlacao(void) const;
		void	carteiraOtima(void) const;
};

# endif
