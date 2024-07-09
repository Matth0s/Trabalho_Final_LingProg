#include "Carteira.h"

Carteira::Carteira(void) : _acoes(), _pesos() {}

Carteira::~Carteira(void) {}

void	Carteira::_ajustarPesos(void)
{
	this->_pesos = vector<double>(this->_acoes.size(), (1 / (double)this->_acoes.size()));
}

void	Carteira::mostrar(void) const
{
	stringstream	out;
	string			linha;

	cout << "\n/¨¨¨¨¨¨¨¨¨¨  ACOES  ¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨\\\n";
	for (unsigned i = 0; i < this->_acoes.size(); i++) {
		if (i % 4 == 0)  {
			out << left << "|  ";
		}
		out << string(2, ' ') << setw(8) << this->_acoes.at(i).getCodigo();
		if (i % 4 == 3 || i == this->_acoes.size() - 1) {
			getline(out, linha);
			cout << left << setw(44) << linha << right << " |\n";
			out.str("");
			out.clear();
		}
	}
	cout << "\\" << string(44, '_') << "/\n" << endl;
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
		else {
			this->_acoes.push_back(Acao(codigoAcao, extracao));
			_ajustarPesos();
		}

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

void	Carteira::_mostrarEstatisticas(string texto, int precisao,
									const vector<double>& estatisticas) const
{
	stringstream	out;
	string			linha;

	cout << left << "\n/¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨  "
		 << setw(18) << texto
		 << right << "  ¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨\\"
		 << endl;

	for (unsigned i = 0; i < this->_acoes.size(); i++) {
		if (i % 2 == 0)  {
			out << left << "| ";
		}
		out << string(4, ' ') << setw(8) << this->_acoes.at(i).getCodigo()
			<< " :  "
			<< setw(10) << fixed << setprecision(precisao) << estatisticas.at(i);
		if (i % 2 == 1 || i == this->_acoes.size() - 1) {
			getline(out, linha);
			cout << left << setw(54) << linha << right << " |\n";
			out.str("");
			out.clear();
		}
	}
	if (estatisticas.size() > 1) {
		cout << "| " << string(52, '-') << " |\n";
		cout << left << "| "
			 << string(16, ' ') << "CARTEIRA :  "
			 << setw(24) << fixed << setprecision(precisao) << estatisticas.back()
			 << right << " |\n";
	}

	cout << "\\" << string(54, '_') << "/\n" << endl;
}

void	Carteira::rentabilidade(void) const
{
	vector<double>	rentabilidades;
	double			rentabilidadeCarteira = 0;

	for (unsigned i = 0; i < this->_acoes.size(); i++) {
		vector<double> serie = this->_acoes.at(i).getHistorico();

		rentabilidades.push_back((serie.back() - serie.front()) * 100 / serie.front());
	}
	rentabilidadeCarteira = Matematica::produtoVetorial(this->_pesos, rentabilidades);
	rentabilidades.push_back(rentabilidadeCarteira);

	_mostrarEstatisticas("RENTABILIDADE %", 2, rentabilidades);
}

void	Carteira::retornoMedio(void) const
{
	vector<double>	retornosMedios;
	double			retornoMedioCarteira = 0;

	for (unsigned i = 0; i < this->_acoes.size(); i++) {
		vector<double> serie = this->_acoes.at(i).getHistorico();
		vector<double> retornos = Matematica::vetorRetorno(serie);
		double media = Matematica::media(retornos);

		retornosMedios.push_back(media * 10000);
	}
	retornoMedioCarteira = Matematica::produtoVetorial(this->_pesos, retornosMedios);
	retornosMedios.push_back(retornoMedioCarteira);

	_mostrarEstatisticas("RETORNO MEDIO 1e-4", 7, retornosMedios);
}

void	Carteira::riscoMedio(void) const
{
	vector<vector<double> >	serieRetornos;
	vector<double>			riscosMedios;
	double					riscoMedioCarteira = 0;

	for (unsigned i = 0; i < this->_acoes.size(); i++) {
		vector<double> serie = this->_acoes.at(i).getHistorico();
		vector<double> retornos = Matematica::vetorRetorno(serie);
		double desvioPadrao = Matematica::desvioPadrao(retornos);

		serieRetornos.push_back(retornos);
		riscosMedios.push_back(desvioPadrao * 100);
	}
	riscoMedioCarteira = Matematica::correlacao(this->_pesos, serieRetornos);
	riscosMedios.push_back(riscoMedioCarteira * 100);

	_mostrarEstatisticas("RISCO MEDIO 1e-2", 7, riscosMedios);
}

void	Carteira::indiceSharpe(void) const
{
	vector<vector<double> >	serieRetornos;
	vector<double>			serieMedias;
	vector<double>			sharpes;
	double					sharpeCarteira = 0;
	double					selic = stod(Externo::extrair_selic_python()) / 100;

	for (unsigned i = 0; i < this->_acoes.size(); i++) {
		vector<double> serie = this->_acoes.at(i).getHistorico();
		vector<double> retornos = Matematica::vetorRetorno(serie);
		double media = Matematica::media(retornos);
		double desvioPadrao = Matematica::desvioPadrao(retornos);

		serieRetornos.push_back(retornos);
		serieMedias.push_back(media);
		sharpes.push_back((media - selic) * 100/ desvioPadrao);
	}
	sharpeCarteira = Matematica::produtoVetorial(this->_pesos, serieMedias) - selic;
	sharpeCarteira /= Matematica::correlacao(this->_pesos, serieRetornos);
	sharpes.push_back(sharpeCarteira * 100);

	_mostrarEstatisticas("INDICE SHARPE 1e-2", 7, sharpes);
}

void	Carteira::correlacao(void) const
{
	vector<vector<double> >	serieRetornos;
	vector<vector<double> >	matrizCor;
	stringstream			out;
	string					linha;

	for (unsigned i = 0; i < this->_acoes.size(); i++) {
		vector<double> serie = this->_acoes.at(i).getHistorico();
		vector<double> retornos = Matematica::vetorRetorno(serie);
		serieRetornos.push_back(retornos);
	}
	matrizCor = Matematica::matrizCorrelacao(serieRetornos);

	cout << "\n/¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨  CORRELACAO  ¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨\\\n";

	for (unsigned i = 0; i < this->_acoes.size(); i++) {
		if (i % 3 == 0)  {
			out << left << "| ";
		}
		out << string(4, ' ') << i + 1 << " - "
			<< setw(8) << this->_acoes.at(i).getCodigo();
		if (i % 3 == 2 || i == this->_acoes.size() - 1) {
			getline(out, linha);
			cout << left << setw(54) << linha << right << " |\n";
			out.str("");
			out.clear();
		}
	}
	cout << "\\" << string(54, '_') << "/\n";

	for (unsigned i = 0; i < this->_acoes.size(); i++) {
		if (i == 0)
			cout << left << "\n      ";
		cout << string(3, ' ') << setw(5) << i + 1;
	}
	for (unsigned i = 0; i < this->_acoes.size(); i++) {
		if (i == 0)
			cout << right << "\n   +--";
		cout << string(8, '-');
	}
	for (unsigned i = 0; i < matrizCor.size(); i++) {
		cout << "\n" << setw(2) << i + 1 << " |  ";
		for (unsigned j = 0; j < matrizCor[i].size(); j++) {
			cout << fixed << setprecision(4) << matrizCor[i][j] << "  ";
		}
	}
	cout << endl << endl;
}

void	Carteira::carteiraOtima(void) const
{
	cout << "\nCARTEIRA OTIMA\n" << endl;
}
