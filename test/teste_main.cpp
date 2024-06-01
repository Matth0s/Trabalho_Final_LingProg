/******************************************************************************/
/*                                                                            */
/*     Autor: Matheus Moreira do Nascimento - 119042060                       */
/*     Trabalho Final                                                         */
/*                                                                            */
/*                   ____ Programa Principal de Testes ____                   */
/*                                                                            */
/******************************************************************************/

#define PY_SSIZE_T_CLEAN

#include "Python.h"
#include "Utils.h"


using namespace std;

int	main(int argc, char *argv[]) {

	wchar_t *program = Py_DecodeLocale(argv[0], NULL);

	(void) argc;

	if (program == NULL) {
		cerr << "Erro Fatal: Não foi possivel decodificar argv[0]" << endl;
		exit(1);
	}

	Py_SetProgramName(program);

	Py_Initialize();

	PyRun_SimpleString("exec(open('./py_source/getAcao.py').read())");

	if (Py_FinalizeEx() < 0) {
		cerr << "Erro: Programa não finalizado corretamente" << endl;
		exit(120);
	}
	PyMem_RawFree(program);

	return (0);
}

	// {
	// 	cout << "____________________________//_____________________________"
	// 		 << endl
	// 		 << endl;

	// 	cout << ( 1 == 1 ? "✅" : "❌");

	// 	cout << "____________________________//_____________________________"
	// 		 << endl
	// 		 << endl;
	// }
