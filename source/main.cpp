/******************************************************************************/
/*                                                                            */
/*     Autor: Matheus Moreira do Nascimento - 119042060                       */
/*     Trabalho Final                                                         */
/*                                                                            */
/*                        ____ Programa Principal ____                        */
/*                                                                            */
/******************************************************************************/

#include "Menu.h"

void subMenu(Acao* acao)
{
	string comando;

	if (!acao)
		return ;

	while (true) {

		Menu::exibirSubMenu(acao->getCodigo());
		cout << "# Insira o comando: ";
		getline(cin, comando);

		if (!comando.compare("0")) {
			acao->mostarSobreEmpresa();
		} else if (!comando.compare("1")) {
			acao->mostarInfoAcao();
		} else if (!comando.compare("2")) {
			acao->mostrarHistoricoDividendos();
		} else if (!comando.compare("3")) {
			acao->mostrarHistoricoComercial();
		} else if (!comando.compare("9")) {
			break;
		} else {
			Menu::comandoInvalido();
		}

		cout << "Aperte Enter para continuar...";
		getline(cin, comando);
	}
}

int main(void)
{
	Carteira	carteira;
	string		comando;

	Externo::inicializar();

	Menu::exibirBemVindo();

	while (true) {

		Menu::exibirMenuPrincipal();
		cout << "# Insira o comando: ";
		getline(cin, comando);

		if (!comando.compare("0")) {
			Menu::opcao0(carteira);
		} else if (!comando.compare("1")) {
			// Exemplos: PETR4 VALE3 ITUB4 BBDC4 ABEV3 B3SA3 BBAS3 PETR3 ITSA4 JBSS3
			Menu::opcao1(carteira);
		} else if (!comando.compare("2")) {
			Menu::opcao2(carteira);
		} else if (!comando.compare("3")) {
			subMenu(Menu::opcao3(carteira));
		} else if (!comando.compare("4")) {
			Menu::opcao4(carteira);
		} else if (!comando.compare("5")) {
			Menu::opcao5(carteira);
		} else if (!comando.compare("6")) {
			Menu::opcao6(carteira);
		} else if (!comando.compare("7")) {
			Menu::opcao7(carteira);
		} else if (!comando.compare("8")) {
			Menu::opcao8(carteira);
		} else if (!comando.compare("9")) {
			Menu::encerrarPrograma();
			break;
		} else {
			Menu::comandoInvalido();
		}

		cout << "\nAperte Enter para continuar...";
		getline(cin, comando);
	}

	Externo::finalizar();

	return (0);
}
