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
#include "Utils.h"

using namespace std;

int	main(void)
{
	Externo::inicializar();
	{
		cout << "____________________________//_____________________________"
			 << endl
			 << endl;

		vector<string>	resultado = Externo::extrair_acao_python("PETR4");

		for (unsigned i = 0; i < resultado.size(); i++) {
			cout << resultado.at(i) << endl;
		}

		cout << "____________________________//_____________________________"
			 << endl
			 << endl;
	}

	{
		cout << "____________________________//_____________________________"
			 << endl
			 << endl;

		string	resultado = Externo::extrair_selic_python();

		cout << "Selic \% a.d.: " << resultado << endl;

		cout << "____________________________//_____________________________"
			 << endl
			 << endl;
	}

	Externo::finalizar();

	return (0);
}

// cout << ( 1 == 1 ? "✅" : "❌");
