/******************************************************************************/
/*                                                                            */
/*     Autor: Matheus Moreira do Nascimento - 119042060                       */
/*     Trabalho Final                                                         */
/*                                                                            */
/*                   ____ Programa Principal de Testes ____                   */
/*                                                                            */
/******************************************************************************/

#include "Carteira.h"

void	separador(void)
{
	cout << "____________________________//_____________________________"
		 << endl
		 << endl;
}

int	main(void)
{
	Externo::inicializar();

	separador();
	{
		vector<string>	resultado = Externo::extrair_acao_python("PETR4");

		for (unsigned i = 0; i < resultado.size(); i++) {
			cout << resultado.at(i) << endl;
		}
	}
	separador();
	{
		string	resultado = Externo::extrair_selic_python();

		cout << "Selic \% a.d.: " << resultado << endl;
	}
	separador();
	{
		try {
			Acao acao("PET4", Externo::extrair_acao_python("PET4"));
			cout << acao;
		} catch (Externo::ModuloPythonError& e) {
			cout << e.what() << endl;
		} catch (exception& e) {
			cout << e.what() << endl;
		}
	}
	separador();
	{
		Acao acao("PETR4", Externo::extrair_acao_python("PETR4"));

		cout << acao;
	}
	separador();
	{
		Acao acao("PETR4", Externo::extrair_acao_python("PETR4"));

		acao.mostarSobreEmpresa();
		acao.mostarInfoAcao();
		acao.mostrarHistoricoDividendos();
		acao.mostrarHistoricoComercial();
	}
	separador();
	{
		Carteira carteira;

		carteira.adicionar("PETR4");
		carteira.adicionar("ABEV3");
		carteira.adicionar("Teste");
		carteira.mostrar();
		cout << endl;
		carteira.remover("PETR4");
		carteira.mostrar();
	}
	separador();

	Externo::finalizar();

	return (0);
}
