#include "Acao.h"

Acao::Acao(void)
	: _codigo(""), _sobreEmpresa(), _infoAcao(), _historicoDividendos(),
	 _historicoComercial(), _historicoFechamentos()
{}

Acao::Acao(const Acao& src)
	: _codigo(src._codigo),
	_sobreEmpresa(src._sobreEmpresa),
	_infoAcao(src._infoAcao),
	_historicoDividendos(src._historicoDividendos),
	_historicoComercial(src._historicoComercial),
	_historicoFechamentos(src._historicoFechamentos)
{}

Acao::Acao(string codigo, vector<string> extracao)
	: _codigo(codigo), _sobreEmpresa(), _infoAcao(), _historicoDividendos(),
	 _historicoComercial(), _historicoFechamentos()
{
	_extrairSobreEmpresa(extracao[0]);
	_extrairInfoAcao(extracao[1]);
	_extrairHistoricoDividendos(extracao[2]);
	_extrairHistoricoComercial(extracao[3]);
	_extrairHistoricoFechamentos(extracao[4]);
}

Acao::~Acao(void)
{}

Acao&	Acao::operator=(const Acao& rhs)
{
	if (this != &rhs) {
		this->_codigo = rhs._codigo;
		this->_sobreEmpresa = rhs._sobreEmpresa;
		this->_infoAcao = rhs._infoAcao;
		this->_historicoDividendos = rhs._historicoDividendos;
		this->_historicoComercial = rhs._historicoComercial;
		this->_historicoFechamentos = rhs._historicoFechamentos;
	}
	return (*this);
}

bool	Acao::operator==(const string& codigo) const
{
	return (this->_codigo.compare(codigo) == 0);
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

	linhas = _splitString(dadoBruto);
	for (unsigned i = 0; i < linhas.size(); i++) {
		dados = _splitString(linhas.at(i), ';');
		this->_sobreEmpresa.push_back({dados.at(0), dados.at(1)});
	}
}

void	Acao::_extrairInfoAcao(string dadoBruto)
{
	vector<string>	linhas;
	vector<string>	dados;

	linhas = _splitString(dadoBruto);
	for (unsigned i = 0; i < linhas.size(); i++) {
		dados = _splitString(linhas.at(i), ';');
		this->_infoAcao.push_back({dados.at(0), dados.at(1)});
	}
}

void	Acao::_extrairHistoricoDividendos(string dadoBruto)
{
	vector<string>		linhas;
	DadosAcaoDividendos	dividendos;

	linhas = _splitString(dadoBruto);
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

	linhas = _splitString(dadoBruto);
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

string	Acao::getCodigo(void) const
{
	return (this->_codigo);
}

vector<double>	Acao::getHistorico(void) const
{
	return (this->_historicoFechamentos);
}

void	Acao::_mostrarCabecalho(string texto) const
{
	cout << left << "\n/¨¨¨¨¨¨¨   "
		 << setw(18) << texto
		 << right << "¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨\\"
		 << endl;
}

void	Acao::_mostrarSeparador(void) const
{
	cout << "| " << string(60, '-') << endl;
}

void	Acao::_mostrarRodape(void) const
{
	cout << "\\" << string(62, '_') << "/\n" << endl;
}

void	Acao::mostarSobreEmpresa(void) const
{
	vector<pair<string, string> >::const_iterator it;

	_mostrarCabecalho("SOBRE A EMPRESA");
	for (it = _sobreEmpresa.begin(); it != _sobreEmpresa.end(); it++) {
		cout << "| ";
		cout << left << setw(20) << it->first;
		cout << right << ": ";
		cout << setw(38) << it->second;
		cout << endl;
	}
	_mostrarRodape();
}

void	Acao::mostarInfoAcao(void) const
{
	vector<pair<string, string> >::const_iterator it;

	_mostrarCabecalho("SOBRE A ACAO");
	for (it = _infoAcao.begin(); it != _infoAcao.end(); it++) {
		cout << "| ";
		cout << left << setw(24) << it->first;
		cout << right << ": ";
		cout << setw(34) << it->second;
		cout << endl;
	}
	_mostrarRodape();
}

void	Acao::mostrarHistoricoDividendos(void) const
{
	vector<DadosAcaoDividendos>::const_iterator it;

	_mostrarCabecalho("DIVIDENDOS");
	cout << left << "| "
		 << string(13, ' ') << setw(17) << "Data"
		 << string(8, ' ') << "Valor por Acao"
		 << right << endl;
	_mostrarSeparador();
	for (it = _historicoDividendos.begin(); it != _historicoDividendos.end(); it++) {
		cout << left << "| ";
		cout << string(10, ' ') << setw(20) << it->data;
		cout << string(9, ' ') << "R$ " << fixed << setprecision(6) << it->valor;
		cout << right << endl;
	}
	_mostrarRodape();
}

void	Acao::mostrarHistoricoComercial(void) const
{
	vector<DadosAcaoComercial>::const_iterator it;

	_mostrarCabecalho("INFOS. SEMANA");
	cout << left << "| "
		 << string(2, ' ') << setw(10) << "Data"
		 << setw(11) << "Abertura"
		 << string(1, ' ') << setw(7) << "Alta"
		 << setw(8) << "Baixa"
		 << setw(12) << "Fechamento"
		 << string(2, ' ') << "Volume"
		 << right << endl;
	_mostrarSeparador();
	for (it = _historicoComercial.begin(); it != _historicoComercial.end(); it++) {
		cout << left << "| ";
		cout << setw(12) << it->data;
		cout << string(2, ' ') << setw(9) << fixed << setprecision(2) << it->abertura;
		cout << setw(8) << fixed << setprecision(2) << it->alta;
		cout << setw(8) << fixed << setprecision(2) << it->baixa;
		cout << string(3, ' ') << setw(9) << fixed << setprecision(2) << it->fechamento;
		cout << string(1, ' ') << it->volume;
		cout << right << endl;
	}
	_mostrarRodape();
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
	for (unsigned i = 0; i < rhs._infoAcao.size(); i++) {
		out << rhs._infoAcao.at(i).first;
		out << "  :  ";
		out << rhs._infoAcao.at(i).second;
		out << endl;
	}
	out << endl;
	for (unsigned i = 0; i < rhs._historicoDividendos.size(); i++) {
		out << rhs._historicoDividendos.at(i).data;
		out << "  ";
		out << rhs._historicoDividendos.at(i).valor;
		out << endl;
	}
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
	for (unsigned i = 0; i < rhs._historicoFechamentos.size(); i++) {
		out << rhs._historicoFechamentos.at(i);
		out << " ";
	}
	out << endl;

	return (out);
}
