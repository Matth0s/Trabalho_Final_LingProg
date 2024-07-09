# ifndef MENU_H
# define MENU_H

#include "Carteira.h"

class Menu
{
	public:
		static void		exibirBemVindo(void);
		static void		exibirMenuPrincipal(void);
		static void		exibirMenuDetalhes(string codigoAcao);
		static void		exibirMenuEstatisticas(void);

		static void		opcao1(Carteira& carteira);
		static void		opcao2(Carteira& carteira);
		static void		opcao3(Carteira& carteira);
		static void		opcao4(Carteira& carteira);
		static Acao*	opcao5(Carteira& carteira);

		static void		encerrarPrograma(void);
		static void		comandoInvalido(void);
};

# endif
