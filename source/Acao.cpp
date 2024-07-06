#include "Acao.h"

Acao::Acao(void)
	: _sobreEmpresa(), _infoAcao(), _historicoDividendos(),
	 _historicoComercial(), _historicoFechamentos()
{}

Acao::Acao(const Acao& src)
	: _sobreEmpresa(src._sobreEmpresa),
	_infoAcao(src._infoAcao),
	_historicoDividendos(src._historicoDividendos),
	_historicoComercial(src._historicoComercial),
	_historicoFechamentos(src._historicoFechamentos)
{}

Acao::Acao(vector<string> extracao)
	: _sobreEmpresa(), _infoAcao(), _historicoDividendos(),
	 _historicoComercial(), _historicoFechamentos()
{
	this->_extrairSobreEmpresa(extracao[0]);
	this->_extrairInfoAcao(extracao[1]);
	this->_extrairHistoricoDividendos(extracao[2]);
	this->_extrairHistoricoComercial(extracao[3]);
	this->_extrairHistoricoFechamentos(extracao[4]);
}

Acao::~Acao(void)
{}

Acao&	Acao::operator=(const Acao& rhs)
{
	if (this == &rhs) {
		this->_sobreEmpresa = rhs._sobreEmpresa;
		this->_infoAcao = rhs._infoAcao;
		this->_historicoDividendos = rhs._historicoDividendos;
		this->_historicoComercial = rhs._historicoComercial;
		this->_historicoFechamentos = rhs._historicoFechamentos;
	}
	return (*this);
}

vector<string>	Acao::_splitString(string str, char delimitador = '\n')
{
	vector<string>	split;
	stringstream	in(str);
	string			elemento;

	while(getline(in, elemento, delimitador))
		split.push_back(elemento);

	return (split);
}

void	Acao::_extrairSobreEmpresa(string dadoBruto)
{
	vector<string>	linhas;
	vector<string>	dados;

	linhas = this->_splitString(dadoBruto);
	for (unsigned i = 0; i < linhas.size(); i++) {
		dados = this->_splitString(linhas.at(i), ';');
		this->_sobreEmpresa.push_back({dados.at(0), dados.at(1)});
	}
}

void	Acao::_extrairInfoAcao(string dadoBruto)
{
	vector<string>	linhas;
	vector<string>	dados;

	linhas = this->_splitString(dadoBruto);
	for (unsigned i = 0; i < linhas.size(); i++) {
		dados = this->_splitString(linhas.at(i), ';');
		this->_infoAcao.push_back({dados.at(0), dados.at(1)});
	}
}

void	Acao::_extrairHistoricoDividendos(string dadoBruto)
{
	vector<string>		linhas;
	DadosAcaoDividendos	dividendos;

	linhas = this->_splitString(dadoBruto);
	for (unsigned i = 0; i < linhas.size(); i++) {
		stringstream dados(linhas.at(i));
		dados >> dividendos.data;
		dados >> dividendos.valor;
		this->_historicoDividendos.push_back(dividendos);
	}
}

void	Acao::_extrairHistoricoComercial(string dadoBruto)
{
	vector<string>		linhas;
	DadosAcaoComercial	comercial;

	linhas = this->_splitString(dadoBruto);
	for (unsigned i = 0; i < linhas.size(); i++) {
		stringstream dados(linhas.at(i));
		dados >> comercial.data;
		dados >> comercial.abertura;
		dados >> comercial.alta;
		dados >> comercial.baixa;
		dados >> comercial.fechamento;
		dados >> comercial.volume;
		this->_historicoComercial.push_back(comercial);
	}
}

void	Acao::_extrairHistoricoFechamentos(string dadoBruto)
{
	stringstream	valores(dadoBruto);
	double			valor;

	while (valores.good()) {
		valores >> valor;
		this->_historicoFechamentos.push_back(valor);
	}
	this->_historicoFechamentos.pop_back();
	this->_historicoFechamentos.shrink_to_fit();
}

ostream&	operator<<(ostream& out, const Acao& rhs)
{
	for (unsigned i = 0; i < rhs._sobreEmpresa.size(); i++) {
		out << rhs._sobreEmpresa.at(i).first;
		out << "  :  ";
		out << rhs._sobreEmpresa.at(i).second;
		out << endl;
	}

	out << endl;
	out << endl;

	for (unsigned i = 0; i < rhs._infoAcao.size(); i++) {
		out << rhs._infoAcao.at(i).first;
		out << "  :  ";
		out << rhs._infoAcao.at(i).second;
		out << endl;
	}

	out << endl;
	out << endl;

	for (unsigned i = 0; i < rhs._historicoDividendos.size(); i++) {
		out << rhs._historicoDividendos.at(i).data;
		out << "  ";
		out << rhs._historicoDividendos.at(i).valor;
		out << endl;
	}
	out << endl;
	out << endl;

	for (unsigned i = 0; i < rhs._historicoComercial.size(); i++) {
		out << rhs._historicoComercial.at(i).data;
		out << "   ";
		out << rhs._historicoComercial.at(i).abertura;
		out << "   ";
		out << rhs._historicoComercial.at(i).alta;
		out << "   ";
		out << rhs._historicoComercial.at(i).baixa;
		out << "   ";
		out << rhs._historicoComercial.at(i).fechamento;
		out << "   ";
		out << rhs._historicoComercial.at(i).volume;
		out << endl;
	}

	out << endl;
	out << endl;

	for (unsigned i = 0; i < rhs._historicoFechamentos.size(); i++) {
		out << rhs._historicoFechamentos.at(i);
		out << " ";
	}

	out << endl;

	return (out);
}
