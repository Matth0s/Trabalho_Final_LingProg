/******************************************************************************/
/*                                                                            */
/*     Autor: Matheus Moreira do Nascimento - 119042060                       */
/*     Trabalho Final                                                         */
/*                                                                            */
/*                   ____ Programa Principal de Testes ____                   */
/*                                                                            */
/******************************************************************************/

#include <vector>
#include "Externo.h"
#include "Acao.h"
#include "Utils.h"

using namespace std;

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
		Acao acao(Externo::extrair_acao_python("PETR4"));

		cout << acao;
	}
	separador();

	Externo::finalizar();

	return (0);
}

// cout << ( 1 == 1 ? "✅" : "❌");
