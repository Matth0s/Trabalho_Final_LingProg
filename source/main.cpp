/******************************************************************************/
/*                                                                            */
/*     Autor: Matheus Moreira do Nascimento - 119042060                       */
/*     Trabalho Final                                                         */
/*                                                                            */
/*                        ____ Programa Principal ____                        */
/*                                                                            */
/******************************************************************************/

#include "Carteira.h"

using namespace std;

void exibirSubMenu(string codigoAcao);
void subMenu(Acao* acao);

void exibirMenuPrincipal(void) {
	cout << endl;
	cout << "|¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨|\n";
	cout << "|    Digite o numero do comando desejado:    |\n";
	cout << "|                                            |\n";
	cout << "|    0 - Mostrar Acao                        |\n";
	cout << "|    1 - Adicionar Acao                      |\n";
	cout << "|    2 - Remover Acao                        |\n";
	cout << "|    3 - Ver Mais                            |\n";
	cout << "|    4 - Indice Sharpe dos Ativos            |\n";
	cout << "|    5 - Rentabilidade por Periodo           |\n";
	cout << "|    6 - Correlacao dos Ativos               |\n";
	cout << "|    7 - Retorno Medio dos Ativos            |\n";
	cout << "|    8 - Carteira Otima                      |\n";
	cout << "|                                            |\n";
	cout << "|    9 - Encerrar Programa                   |\n";
	cout << "|____________________________________________|"
		 << endl
		 << endl;
}

int main(void) {

	Carteira	carteria;
	string		comando;
	string		subComando;

	cout << endl;
	cout << " * ¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨ *\n";
	cout << " |       Bem Vindo Programa Principal       |\n";
	cout << " |                                          |\n";
	cout << " |        utilize os codigos do Menu        |\n";
	cout << " |       para interacao com o sistema       |\n";
	cout << " * ________________________________________ *"
		 << endl
		 << endl;

	Externo::inicializar();
	while (true) {

		exibirMenuPrincipal();
		cout << "# Insira o comando: ";
		getline(cin, comando);

		if (!comando.compare("0")) {
			carteria.mostrar();

		} else if (!comando.compare("1")) {
			// Exemplos: PETR4 VALE3 ITUB4 BBDC4 ABEV3 B3SA3 BBAS3 PETR3 ITSA4 JBSS3
			cout << "# Insira os codigos das ações: ";
			getline(cin, subComando);

			stringstream codigosAcoes(subComando);
			while (codigosAcoes.good()) {
				codigosAcoes >> subComando;
				if (subComando.compare("\n") != 0) {
					cout << endl;
					carteria.adicionar(subComando);
				}
			}

		} else if (!comando.compare("2")) {
			cout << "# Insira os codigos das ações: ";
			getline(cin, subComando);

			stringstream codigosAcoes(subComando);
			while (codigosAcoes.good()) {
				codigosAcoes >> subComando;
				if (subComando.compare("\n") != 0) {
					cout << endl;
					carteria.remover(subComando);
				}
			}

		} else if (!comando.compare("3")) {
			cout << "# Insira o codigo da ação: ";
			getline(cin, subComando);
			cout << endl;
			subMenu(carteria.buscar(subComando));

		} else if (!comando.compare("4")) {
			cout << "Indice Sharpe dos Ativos" << endl;

		} else if (!comando.compare("5")) {
			cout << "Rentabilidade por Periodo" << endl;

		} else if (!comando.compare("6")) {
			cout << "Correlacao dos Ativos" << endl;

		} else if (!comando.compare("7")) {
			cout << "Retorno Medio dos Ativos" << endl;

		} else if (!comando.compare("8")) {
			cout << "Carteira Otima" << endl;

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

		cout << "\nAperte Enter para continuar...";
		getline(cin, comando);
	}

	Externo::finalizar();

	return (0);
}

void exibirSubMenu(string codigoAcao) {
	cout << endl;
	cout << "|¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨|\n";
	cout << "|           Detalhes Sobre: "
		 << left << setw(8) << codigoAcao
		 << right << "         |\n";
	cout << "|                                            |\n";
	cout << "|    Digite o numero do comando desejado:    |\n";
	cout << "|                                            |\n";
	cout << "|    0 - Sobre a Empresa                     |\n";
	cout << "|    1 - Informacoes da Acao                 |\n";
	cout << "|    2 - Historico Pagamento Dividendos      |\n";
	cout << "|    3 - Historico Ultima Semana             |\n";
	cout << "|                                            |\n";
	cout << "|    9 - Voltar para Menu Principal          |\n";
	cout << "|____________________________________________|"
		 << endl
		 << endl;
}

void subMenu(Acao* acao) {

	string comando;

	if (!acao)
		return ;

	while (true) {

		exibirSubMenu(acao->getCodigo());
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
			cout << "\n/¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨\\\n";
			cout << "|     Comando não encontrado     |\n";
			cout << "|         Tente novamente        |\n";
			cout << "\\________________________________/\n"
				 << endl;
		}

		cout << "Aperte Enter para continuar...";
		getline(cin, comando);
	}
}
