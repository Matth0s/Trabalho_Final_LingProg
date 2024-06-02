#ifndef EXTERNO_H
#define EXTERNO_H

#include "Python.h"
#include <iostream>
#include <vector>

using namespace std;

class Externo {

	private:
		static const char		*modulo;

	public:
		static const int		diasUteisMes = 22;
		static const int		diasUteisAno = 252;

		static void				inicializar(void);
		static void				finalizar(void);
		static vector<string>	extrair_acao_python(string acao);
		static string			extrair_selic_python(void);
};

#endif
