#include "Menu.h"

void	Menu::exibirBemVindo(void)
{
	cout << endl;
	cout << " * ¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨ *\n";
	cout << " |       Bem Vindo Programa Principal       |\n";
	cout << " |                                          |\n";
	cout << " |        utilize os codigos do Menu        |\n";
	cout << " |       para interacao com o sistema       |\n";
	cout << " * ________________________________________ *"
		 << endl
		 << endl;
}

void	Menu::exibirMenuPrincipal(void)
{
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

void	Menu::exibirSubMenu(string codigoAcao)
{
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

void	Menu::opcao0(Carteira& carteira)
{
	carteira.mostrar();
}

void	Menu::opcao1(Carteira& carteira)
{
	stringstream	ss;
	string			codigosAcoes;

	cout << "# Insira os codigos das ações: ";
	getline(cin, codigosAcoes);
	ss << codigosAcoes;
	while (ss.good()) {
		ss >> codigosAcoes;
		if (codigosAcoes.compare("\n") != 0) {
			cout << endl;
			carteira.adicionar(codigosAcoes);
		}
	}
}

void	Menu::opcao2(Carteira& carteira)
{
	stringstream	ss;
	string			codigosAcoes;

	cout << "# Insira os codigos das ações: ";
	getline(cin, codigosAcoes);
	ss << codigosAcoes;
	while (ss.good()) {
		ss >> codigosAcoes;
		if (codigosAcoes.compare("\n") != 0) {
			cout << endl;
			carteira.remover(codigosAcoes);
		}
	}
}

Acao*	Menu::opcao3(Carteira& carteira)
{
	string	codigoAcao;

	cout << "# Insira o codigo da ação: ";
	getline(cin, codigoAcao);
	cout << endl;

	return (carteira.buscar(codigoAcao));
}

void	Menu::opcao4(Carteira& carteira)
{
	(void) carteira;

	cout << "Indice Sharpe dos Ativos" << endl;
}

void	Menu::opcao5(Carteira& carteira)
{
	(void) carteira;

	cout << "Rentabilidade por Periodo" << endl;
}

void	Menu::opcao6(Carteira& carteira)
{
	(void) carteira;

	cout << "Correlacao dos Ativos" << endl;
}

void	Menu::opcao7(Carteira& carteira)
{
	(void) carteira;

	cout << "Retorno Medio dos Ativos" << endl;
}

void	Menu::opcao8(Carteira& carteira)
{
	(void) carteira;

	cout << "Carteira Otima" << endl;
}

void	Menu::encerrarPrograma(void)
{
	cout << "\n/¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨\\\n";
	cout << "|       Programa Encerrado       |\n";
	cout << "\\________________________________/\n"
			<< endl;
}

void	Menu::comandoInvalido(void)
{
	cout << "\n/¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨\\\n";
	cout << "|     Comando não encontrado     |\n";
	cout << "|         Tente novamente        |\n";
	cout << "\\________________________________/\n"
			<< endl;
}
