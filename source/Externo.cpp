#include "Externo.h"

const char* Externo::modulo = "financa";

void	Externo::inicializar(void)
{
	// Preparando o PATH Para Encontrar o Modulo
	setenv("PYTHONPATH", "./py_source", 1);

	//Inicializa o Interpretador Python Caso Não Esteja Inicializado
	if (!Py_IsInitialized()) {
		Py_Initialize();
	}
}

void	Externo::finalizar(void)
{
	//Finaliza o Interpretador Python Caso Esteja Inicializado
	if (Py_IsInitialized()) {
		Py_Finalize();
	}
}

vector<string>	Externo::extrair_acao_python(string acao)
{
	PyObject		*pyModulo = NULL;
	PyObject		*pyFuncao = NULL;
	PyObject		*pyArg = NULL;
	PyObject		*pyResultado = NULL;
	vector<string>	resultado;

	if (Py_IsInitialized())
	{
		// Selecionando o Modulo Python
		pyModulo = PyImport_ImportModule(Externo::modulo);
		if (pyModulo)
		{
			// Selecionando a Função Desejada no Modulo
			pyFuncao = PyObject_GetAttrString(pyModulo, "get_acao");
			if (pyFuncao && PyCallable_Check(pyFuncao))
			{
				// Preparando o Argumento Para a Função
				pyArg = Py_BuildValue("(s)", acao.c_str());
				// Chamando a Função com o Argumento
				pyResultado = PyObject_CallObject(pyFuncao, pyArg);
				if (pyResultado && PyList_Check(pyResultado))
				{
					// Extrai os Elementos da Lista Retornada e os Transforma
					// em um Vector de Strings
					for (Py_ssize_t i = 0; i < PyList_Size(pyResultado); i++)
					{
						PyObject	*pyItem = PyList_GetItem(pyResultado, i);
						const char	*str = PyUnicode_AsUTF8(pyItem);
						resultado.push_back(str);
					}
				}
			}
		}

		// Limpando Memoria Alocada
		Py_XDECREF(pyResultado);
		Py_XDECREF(pyArg);
		Py_XDECREF(pyFuncao);
		Py_XDECREF(pyModulo);
	}

	return (resultado);
}

string	Externo::extrair_selic_python(void)
{
	PyObject	*pyModulo = NULL;
	PyObject	*pyFuncao = NULL;
	PyObject	*pyResultado = NULL;
	string		resultado = "";

	if (Py_IsInitialized())
	{
		// Selecionando o Modulo Python
		pyModulo = PyImport_ImportModule(Externo::modulo);
		if (pyModulo)
		{
			// Selecionando a Função Desejada no Modulo
			pyFuncao = PyObject_GetAttrString(pyModulo, "get_selic");
			if (pyFuncao && PyCallable_Check(pyFuncao))
			{
				// Chamando a Função
				pyResultado = PyObject_CallObject(pyFuncao, NULL);
				if (pyResultado && PyUnicode_Check(pyResultado))
				{
					const char	*str = PyUnicode_AsUTF8(pyResultado);
					resultado = string(str);
				}
			}
		}

		// Limpando Memoria Alocada
		Py_XDECREF(pyResultado);
		Py_XDECREF(pyFuncao);
		Py_XDECREF(pyModulo);
	}

	return (resultado);
}
