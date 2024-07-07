#include "Carteira.h"

Carteira::Carteira(void) : _selic(), _acoes() {}

Carteira::~Carteira(void) {}

void	Carteira::adicionarAcao(string codigoAcao)
{
	try {
		vector<string> extracao;

		this->_selic = stod(Externo::extrair_selic_python());
		extracao = Externo::extrair_acao_python(codigoAcao);
		this->_acoes.push_back(Acao(codigoAcao, extracao));
	} catch (exception& e) {
		cerr << "Não foi possivel adicionar a Ação: " << e.what() << endl;
	}
}

void	Carteira::mostrarAcoes(void)
{
	for (unsigned i = 0; i < this->_acoes.size(); i++) {
		cout << this->_acoes.at(i).getCodigo() << endl;
	}
}

void	Carteira::removerAcao(string codigoAcao)
{
	vector<Acao>::iterator	it;

	it = find(this->_acoes.begin(), this->_acoes.end(), codigoAcao);
	if (it == this->_acoes.end()) {
		cerr << "A carteira não possui uma Ação com o identificar: " << codigoAcao << endl;
	} else {
		this->_acoes.erase(it);
	}
}
