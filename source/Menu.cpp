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
	cout << "|    1 - Mostrar Carteira                    |\n";
	cout << "|    2 - Adicionar Acao                      |\n";
	cout << "|    3 - Remover Acao                        |\n";
	cout << "|    4 - Configurar Pesos da Carteira        |\n";
	cout << "|    5 - Ver Detalhes Acoes                  |\n";
	cout << "|    6 - Ver Estatisticas Carteira           |\n";
	cout << "|                                            |\n";
	cout << "|    9 - Encerrar Programa                   |\n";
	cout << "|____________________________________________|"
		 << endl
		 << endl;
}

void	Menu::exibirMenuDetalhes(string codigoAcao)
{
	cout << endl;
	cout << "|¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨|\n";
	cout << "|           Detalhes Sobre: "
		 << left << setw(8) << codigoAcao
		 << right << "         |\n";
	cout << "|                                            |\n";
	cout << "|    Digite o numero do detalhe desejado:    |\n";
	cout << "|                                            |\n";
	cout << "|    1 - Sobre a Empresa                     |\n";
	cout << "|    2 - Informacoes da Acao                 |\n";
	cout << "|    3 - Historico Pagamento Dividendos      |\n";
	cout << "|    4 - Historico Ultima Semana             |\n";
	cout << "|                                            |\n";
	cout << "|    9 - Voltar para Menu Principal          |\n";
	cout << "|____________________________________________|"
		 << endl
		 << endl;
}

void	Menu::exibirMenuEstatisticas(void)
{
	cout << endl;
	cout << "|¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨|\n";
	cout << "|  Digite o numero da estatistica desejado:  |\n";
	cout << "|                                            |\n";
	cout << "|    1 - Rentabilidade                       |\n";
	cout << "|    2 - Retorno Medio                       |\n";
	cout << "|    3 - Risco Medio                         |\n";
	cout << "|    4 - Indice Sharpe                       |\n";
	cout << "|    5 - Correlacoes de Acoes                |\n";
	cout << "|    6 - Carteira Otima                      |\n";
	cout << "|                                            |\n";
	cout << "|    9 - Encerrar Programa                   |\n";
	cout << "|____________________________________________|"
		 << endl
		 << endl;
}

void	Menu::opcao1(Carteira& carteira)
{
	carteira.mostrar();
}

void	Menu::opcao2(Carteira& carteira)
{
	stringstream	ss;
	string			codigosAcoes;

	cout << "# Insira os codigos das ações: ";
	getline(cin, codigosAcoes);
	ss << codigosAcoes;
	while (ss.good() && ss.str().compare("\n")) {
		ss >> codigosAcoes;
		cout << endl;
		carteira.adicionar(codigosAcoes);
	}
}

void	Menu::opcao3(Carteira& carteira)
{
	stringstream	ss;
	string			codigosAcoes;

	cout << "# Insira os codigos das ações: ";
	getline(cin, codigosAcoes);
	ss << codigosAcoes;
	while (ss.good() && ss.str().compare("\n")) {
		ss >> codigosAcoes;
		cout << endl;
		carteira.remover(codigosAcoes);
	}
}

void	Menu::opcao4(Carteira& carteira)
{
	stringstream	ss;
	string			linha;
	vector<double>	pesos;
	double			peso;

	cout << "# Insira os pesos da carteira: ";
	getline(cin, linha);
	ss << linha;
	while (ss.good() && ss.str().compare("\n")) {
		ss >> peso;
		pesos.push_back(peso);
	}
	cout << endl;
	carteira.setPesos(pesos);
}

Acao*	Menu::opcao5(Carteira& carteira)
{
	string	codigoAcao;

	cout << "# Insira o codigo da ação: ";
	getline(cin, codigoAcao);
	cout << endl;

	return (carteira.buscar(codigoAcao));
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
