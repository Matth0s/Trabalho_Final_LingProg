# ifndef MENU_H
# define MENU_H

#include "Carteira.h"

class Menu
{
	public:
		static void		exibirBemVindo(void);
		static void		exibirMenuPrincipal(void);
		static void		exibirSubMenu(string codigoAcao);

		static void		opcao0(Carteira& carteira);
		static void		opcao1(Carteira& carteira);
		static void		opcao2(Carteira& carteira);
		static Acao*	opcao3(Carteira& carteira);
		static void		opcao4(Carteira& carteira);
		static void		opcao5(Carteira& carteira);
		static void		opcao6(Carteira& carteira);
		static void		opcao7(Carteira& carteira);
		static void		opcao8(Carteira& carteira);

		static void		encerrarPrograma(void);
		static void		comandoInvalido(void);
};

# endif
