#include "Carteira.h"

Carteira::Carteira(void) : _selic(), _acoes() {}

Carteira::~Carteira(void) {}

void	Carteira::mostrar(void)
{
	stringstream	out;
	string			linha;

	cout << "\n/¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨\\\n";
	for (unsigned i = 0; i < this->_acoes.size(); i++) {
		if (i % 4 == 0)  {
			out << left << "|  ";
		}
		out << string(2, ' ') << setw(8) << this->_acoes.at(i).getCodigo();
		if (i % 4 == 3 || i == this->_acoes.size() - 1) {
			getline(out, linha);
			cout << left << setw(44) << linha << right << " |\n";
		}
	}
	cout << "\\____________________________________________/\n"
		 << endl;
}

void	Carteira::adicionar(string codigoAcao)
{
	try {
		vector<Acao>::iterator	it;
		vector<string>			extracao;

		extracao = Externo::extrair_acao_python(codigoAcao);

		it = find(this->_acoes.begin(), this->_acoes.end(), codigoAcao);
		if (it != this->_acoes.end())
			*it = Acao(codigoAcao, extracao);
		else
			this->_acoes.push_back(Acao(codigoAcao, extracao));

		cout << "Ação '" << codigoAcao << "' adicionada a carteira com sucesso!"
			 << endl;
	} catch (exception& e) {
		cerr << "Não foi possivel adicionar a Ação '" << codigoAcao << "': "
			 << e.what() << endl;
	}
}

Acao*	Carteira::buscar(string codigoAcao)
{
	vector<Acao>::iterator	it;
	Acao*					acao = NULL;

	it = find(this->_acoes.begin(), this->_acoes.end(), codigoAcao);
	if (it != this->_acoes.end()) {
		acao = &(*it);
	} else {
		cerr << "A carteira não possui uma Ação com o identificar: " << codigoAcao
			 << endl;
	}

	return (acao);
}

void	Carteira::remover(string codigoAcao)
{
	vector<Acao>::iterator	it;

	it = find(this->_acoes.begin(), this->_acoes.end(), codigoAcao);
	if (it != this->_acoes.end()) {
		this->_acoes.erase(it);

		cout << "Ação '" << codigoAcao << "' removida da carteira com sucesso!"
			 << endl;
	} else {
		cerr << "A carteira não possui uma Ação com o identificar: " << codigoAcao
			 << endl;
	}
}
