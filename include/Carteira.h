# ifndef CARTEIRA_H
# define CARTERIA_H

#include "Externo.h"
#include "Acao.h"
#include <algorithm>

class Carteira
{
	private:
		double			_selic;
		vector<Acao>	_acoes;

	public:
		Carteira(void);
		~Carteira(void);

		void	adicionarAcao(string codigoAcao);
		void	mostrarAcoes(void);
		void	removerAcao(string codigoAcao);
};

# endif
