/******************************************************************************/
/*                                                                            */
/*     Autor: Matheus Moreira do Nascimento - 119042060                       */
/*     Trabalho Final                                                         */
/*                                                                            */
/*                        ____ Programa Principal ____                        */
/*                                                                            */
/******************************************************************************/

#include "Utils.h"

using namespace std;

void exibirMenuPrincipal(void) {
	cout << endl;
	cout << "|¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨|\n";
	cout << "|    Digite o numero do comando desejado:    |\n";
	cout << "|                                            |\n";
	cout << "|    1 - Teste                               |\n";
	cout << "|    2 - Teste                               |\n";
	cout << "|    3 - Teste                               |\n";
	cout << "|    4 - Teste                               |\n";
	cout << "|    5 - Teste                               |\n";
	cout << "|    6 - Teste                               |\n";
	cout << "|    7 - Teste                               |\n";
	cout << "|    8 - Teste                               |\n";
	cout << "|                                            |\n";
	cout << "|    9 - Encerrar Programa                   |\n";
	cout << "|____________________________________________|"
		 << endl
		 << endl;
}

int main(void) {

	string comando;

	cout << endl;
	cout << " * ¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨ *\n";
	cout << " |       Bem Vindo Programa Principal       |\n";
	cout << " |                                          |\n";
	cout << " |        utilize os codigos do Menu        |\n";
	cout << " |       para interacao com o sistema       |\n";
	cout << " * ________________________________________ *"
		 << endl
		 << endl;

	while (true) {

		exibirMenuPrincipal();
		cout << "# Insira o comando: ";
		getline(cin, comando);

		if (!comando.compare("1")) {
			cout << "Escolha 1" << endl;

		} else if (!comando.compare("2")) {
			cout << "Escolha 2" << endl;

		} else if (!comando.compare("3")) {
			cout << "Escolha 3" << endl;

		} else if (!comando.compare("4")) {
			cout << "Escolha 4" << endl;

		} else if (!comando.compare("5")) {
			cout << "Escolha 5" << endl;

		} else if (!comando.compare("6")) {
			cout << "Escolha 6" << endl;

		} else if (!comando.compare("7")) {
			cout << "Escolha 7" << endl;

		} else if (!comando.compare("8")) {
			cout << "Escolha 8" << endl;

		} else if (!comando.compare("9")) {
			cout << "\n/¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨\\\n";
			cout << "|       Programa Encerrado       |\n";
			cout << "\\________________________________/\n"
				 << endl;
			break;

		} else {
			cout << "\n/¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨\\\n";
			cout << "|     Comando não encontrado     |\n";
			cout << "|         Tente novamente        |\n";
			cout << "\\________________________________/\n"
				 << endl;
		}

		cout << "Aperte Enter para continuar...";
		getline(cin, comando);
	}

	return (0);
}

// # adicionar ação na carteira
// # remover ação da carteira
// # mostrar carteria

// # Sobre ações
// # Info ações
// # Historico Semana Ações
// # Historico Dividendos Ações

// * Calcular Indice Sharpe das Ações na Carteira
// Calcular Rentabilidade de um determinado periodo
// Calcular correlação dos ativos na carteiro
// Calcular REtorno médio ativos e carteira
// Calculçar a volatilidade dos ativos da carteira
