#ifndef EXTERNO_H
#define EXTERNO_H

#include "Python.h"
#include <iostream>
#include <vector>

using namespace std;

class Externo {

	public:
		class ModuloPythonError: public exception {
			private:
				string	_mensagem;
			public:
				explicit ModuloPythonError(const string& mensagem);
				virtual const char* what(void) const throw();
		};

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
