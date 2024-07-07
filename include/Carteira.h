# ifndef CARTEIRA_H
# define CARTERIA_H

#include "Externo.h"
#include "Acao.h"
#include <algorithm>

class Carteira
{
	private:
		// this->_selic = stod(Externo::extrair_selic_python());
		double			_selic;
		vector<Acao>	_acoes;

	public:
		Carteira(void);
		~Carteira(void);

		/* Exibe o codigo de todas as ações que estão na carteira */
		void	mostrar(void);
		/* Adiciona uma nova ação na carteira */
		void	adicionar(string codigoAcao);
		/* Busca uma determinada ação na carteira */
		Acao*	buscar(string codigoAcao);
		/* Remove uma ação da carteira */
		void	remover(string codigoAcao);
};

# endif
