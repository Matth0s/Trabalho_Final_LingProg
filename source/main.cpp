/******************************************************************************/
/*                                                                            */
/*     Autor: Matheus Moreira do Nascimento - 119042060                       */
/*     Trabalho Final                                                         */
/*                                                                            */
/*                        ____ Programa Principal ____                        */
/*                                                                            */
/******************************************************************************/

#include "Menu.h"

void menuDetalhes(Acao* acao)
{
	string comando;

	if (!acao)
		return ;

	while (true) {

		Menu::exibirMenuDetalhes(acao->getCodigo());
		cout << "# Insira o comando: ";
		getline(cin, comando);

		if (!comando.compare("1")) {
			acao->mostarSobreEmpresa();
		} else if (!comando.compare("2")) {
			acao->mostarInfoAcao();
		} else if (!comando.compare("3")) {
			acao->mostrarHistoricoDividendos();
		} else if (!comando.compare("4")) {
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

void menuEstatisticas(Carteira& carteira)
{
	string comando;

	while (true) {

		Menu::exibirMenuEstatisticas();
		cout << "# Insira o comando: ";
		getline(cin, comando);

		if (!comando.compare("1")) {
			carteira.rentabilidade();
		} else if (!comando.compare("2")) {
			carteira.retornoMedio();
		} else if (!comando.compare("3")) {
			carteira.riscoMedio();
		} else if (!comando.compare("4")) {
			carteira.indiceSharpe();
		} else if (!comando.compare("5")) {
			carteira.correlacao();
		} else if (!comando.compare("6")) {
			carteira.carteiraOtima();
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

		if (!comando.compare("1")) {
			Menu::opcao1(carteira);
		} else if (!comando.compare("2")) {
			// Exemplos: PETR4 ITUB4 VALE3 WEGE3 ABEV3 B3SA3 BPAC11 BBDC3 ITSA4 SANB11 ELET3 VIVT3 SUZB3 JBSS3
			Menu::opcao2(carteira);
		} else if (!comando.compare("3")) {
			Menu::opcao3(carteira);
		} else if (!comando.compare("4")) {
			Menu::opcao4(carteira);
		} else if (!comando.compare("5")) {
			menuDetalhes(Menu::opcao5(carteira));
		} else if (!comando.compare("6")) {
			menuEstatisticas(carteira);
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
