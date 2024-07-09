#include "Carteira.h"

Carteira::Carteira(void) : _acoes(), _pesos() {}

Carteira::~Carteira(void) {}

void	Carteira::_ajustarPesos(int idx)
{
	double	pesosSize = this->_pesos.size();
	double	acoesSize = this->_acoes.size();

	// Indices menores que 0 indicam que objetos não foram removidos, mas sim
	// acrescentados
	if (idx < 0) {
		for (unsigned i = 0; i < pesosSize; i++) {
			this->_pesos.at(i) *= (pesosSize / acoesSize);
		}
		this->_pesos.push_back(1 / acoesSize);

	// Indices maiores ou iguais a 0 indicam que ações foram removidas
	} else {
		this->_pesos.erase(this->_pesos.begin() + idx);
		this->_pesos = Matematica::normalizarVetor(this->_pesos);
	}
}

void	Carteira::mostrar(void) const
{
	stringstream	out;
	string			linha;

	cout << "\n/¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨  CARTEIRA  ¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨\\\n";
	for (unsigned i = 0; i < this->_acoes.size(); i++) {
		if (i % 2 == 0)  {
			out << left << "| ";
		}
		out << string(3, ' ') << setw(8) << this->_acoes.at(i).getCodigo()
			<< " : "
			<< setw(6) << fixed << setprecision(2) << this->_pesos.at(i) * 100
			<< setw(6) << " %";
		if (i % 2 == 1 || i == this->_acoes.size() - 1) {
			getline(out, linha);
			cout << left << setw(54) << linha << right << " |\n";
			out.str("");
			out.clear();
		}
	}
	cout << "\\" << string(54, '_') << "/\n" << endl;
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
			_ajustarPesos(-1);
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
	unsigned				idx;

	it = find(this->_acoes.begin(), this->_acoes.end(), codigoAcao);
	if (it != this->_acoes.end()) {
		idx = it - this->_acoes.begin();
		this->_acoes.erase(this->_acoes.begin());

		_ajustarPesos(idx);
		cout << "Ação '" << codigoAcao << "' removida da carteira com sucesso!"
			 << endl;
	} else {
		cerr << "A carteira não possui uma Ação com o identificar: " << codigoAcao
			 << endl;
	}
}

void	Carteira::setPesos(vector<double> pesos)
{
	double	pesosSize = pesos.size();
	double	acoesSize = this->_acoes.size();

	// Completa o vetor de pesos caso seja menor que o vetor de ações
	for (unsigned i = pesosSize; i < acoesSize; i++) {
		pesos.push_back(1 / acoesSize);
	}
	// Descarta os elementos extras do vetor peso, caso ele seja maior que o vetor de ações
	pesos.resize(acoesSize);

	this->_pesos = Matematica::normalizarVetor(pesos);

	cout << "Pesos configurados com sucesso!" << endl;
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
		out << string(2, ' ') << setw(8) << this->_acoes.at(i).getCodigo()
			<< " :  "
			<< setw(12) << fixed << setprecision(precisao) << estatisticas.at(i);
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
	vector<double>	rentabilidades(this->_acoes.size() + 1);
	double			rentabilidadeCarteira = 0;

	for (unsigned i = 0; i < this->_acoes.size(); i++) {
		vector<double> serie = this->_acoes.at(i).getHistorico();

		rentabilidades[i] = (serie.back() - serie.front()) * 100 / serie.front();
	}
	rentabilidadeCarteira = Matematica::produtoVetorial(this->_pesos, rentabilidades);
	rentabilidades[this->_acoes.size()] = rentabilidadeCarteira;

	_mostrarEstatisticas("RENTABILIDADE %", 2, rentabilidades);
}

void	Carteira::retornoMedio(void) const
{
	vector<double>	retornosMedios(this->_acoes.size() + 1);
	double			retornoMedioCarteira = 0;

	for (unsigned i = 0; i < this->_acoes.size(); i++) {
		vector<double> serie = this->_acoes.at(i).getHistorico();
		vector<double> retornos = Matematica::vetorRetorno(serie);
		double media = Matematica::media(retornos);

		retornosMedios[i] = media * 10000;
	}
	retornoMedioCarteira = Matematica::produtoVetorial(this->_pesos, retornosMedios);
	retornosMedios[this->_acoes.size()] = retornoMedioCarteira;

	_mostrarEstatisticas("RETORNO MEDIO 1e-4", 7, retornosMedios);
}

void	Carteira::riscoMedio(void) const
{
	vector<vector<double> >	serieRetornos(this->_acoes.size());
	vector<double>			riscosMedios(this->_acoes.size() + 1);
	double					riscoMedioCarteira = 0;

	for (unsigned i = 0; i < this->_acoes.size(); i++) {
		vector<double> serie = this->_acoes.at(i).getHistorico();
		vector<double> retornos = Matematica::vetorRetorno(serie);
		double desvioPadrao = Matematica::desvioPadrao(retornos);

		serieRetornos[i] = retornos;
		riscosMedios[i] = desvioPadrao * 100;
	}
	riscoMedioCarteira = Matematica::correlacao(this->_pesos, serieRetornos);
	riscosMedios[this->_acoes.size()] = (riscoMedioCarteira * 100);

	_mostrarEstatisticas("RISCO MEDIO 1e-2", 7, riscosMedios);
}

void	Carteira::indiceSharpe(void) const
{
	vector<vector<double> >	serieRetornos(this->_acoes.size());
	vector<double>			serieMedias(this->_acoes.size());
	vector<double>			sharpes(this->_acoes.size() + 1);
	double					sharpeCarteira = 0;
	double					selic = stod(Externo::extrair_selic_python()) / 100;

	for (unsigned i = 0; i < this->_acoes.size(); i++) {
		vector<double> serie = this->_acoes.at(i).getHistorico();
		vector<double> retornos = Matematica::vetorRetorno(serie);
		double media = Matematica::media(retornos);
		double desvioPadrao = Matematica::desvioPadrao(retornos);

		serieRetornos[i] = retornos;
		serieMedias[i] = media;
		sharpes[i] = (media - selic) * 100/ desvioPadrao;
	}
	sharpeCarteira = Matematica::produtoVetorial(this->_pesos, serieMedias) - selic;
	sharpeCarteira /= Matematica::correlacao(this->_pesos, serieRetornos);
	sharpes[this->_acoes.size()] = sharpeCarteira * 100;

	_mostrarEstatisticas("INDICE SHARPE 1e-2", 7, sharpes);
}

void	Carteira::_mostrarMatrizCorrelacao(const vector<vector<double> >& matriz) const
{
	stringstream			out;
	string					linha;

	cout << "\n/¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨  CORRELACAO  ¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨\\\n";

	for (unsigned i = 0; i < this->_acoes.size(); i++) {
		if (i % 3 == 0)  {
			out << left << "| ";
		}
		out << string(5, ' ') << i + 1 << " - "
			<< setw(7) << this->_acoes.at(i).getCodigo();
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
	for (unsigned i = 0; i < matriz.size(); i++) {
		cout << "\n" << setw(2) << i + 1 << " |  ";
		for (unsigned j = 0; j < matriz[i].size(); j++) {
			cout << fixed << setprecision(4) << matriz[i][j] << "  ";
		}
	}

	cout << endl << endl;
}

void	Carteira::correlacao(void) const
{
	vector<vector<double> >	serieRetornos(this->_acoes.size());
	vector<vector<double> >	matrizCor;

	for (unsigned i = 0; i < this->_acoes.size(); i++) {
		vector<double> serie = this->_acoes.at(i).getHistorico();
		vector<double> retornos = Matematica::vetorRetorno(serie);
		serieRetornos[i] = retornos;
	}
	matrizCor = Matematica::matrizCorrelacao(serieRetornos);
	_mostrarMatrizCorrelacao(matrizCor);
}

void	Carteira::_mostrarCarteriraOtima(const vector<vector<double> >& serieRetornos,
											const vector<double>& serieMedias,
											const vector<double>& serieRentabilidade,
											const vector<double>& pesos,
											const double& sharpe) const
{
	stringstream			out;
	string					linha;

	cout << "\n/¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨  PESOS CARTEIRA OTIMA  ¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨\\\n";

	for (unsigned i = 0; i < this->_acoes.size(); i++) {
		if (i % 2 == 0)  {
			out << left << "| ";
		}
		out << string(3, ' ') << setw(8) << this->_acoes.at(i).getCodigo()
			<< " : "
			<< setw(6) << fixed << setprecision(2) << pesos.at(i) * 100
			<< setw(6) << " %";
		if (i % 2 == 1 || i == this->_acoes.size() - 1) {
			getline(out, linha);
			cout << left << setw(54) << linha << right << " |\n";
			out.str("");
			out.clear();
		}
	}

	if (this->_acoes.size()) {
		cout << "| " << string(52, '-') << " |\n";

		cout << left << "| "
			 << string(11, ' ') << "RENTABILIDADE :  "
			 << setw(12) << fixed << setprecision(2)
			 << Matematica::produtoVetorial(pesos, serieRentabilidade) * 100
			 << setw(12) << "%"
			 << " |\n";

		cout << "| "
			 << string(11, ' ') << "RETORNO MEDIO :  "
			 << setw(12) << fixed << setprecision(7)
			 << Matematica::produtoVetorial(pesos, serieMedias) * 10000
			 << setw(12) << "(1e-4)"
			 << " |\n";

		cout << "| "
			 << string(13, ' ') << "RISCO MEDIO :  "
			 << setw(12) << fixed << setprecision(7)
			 << Matematica::correlacao(pesos, serieRetornos) * 100
			 << setw(12) << "(1e-2)"
			 << " |\n";

		cout << "| "
			 << string(11, ' ') << "INDICE SHARPE :  "
			 << setw(12) << fixed << setprecision(7)
			 <<  sharpe * 100
			 << setw(12) << "(1e-2)"
			 << right << " |\n";
	}

	cout << "\\" << string(54, '_') << "/\n" << endl;
}

void	Carteira::carteiraOtima(void) const
{
	vector<vector<double> >	serieRetornos(this->_acoes.size());
	vector<double>			serieMedias(this->_acoes.size());
	vector<double>			serieRentabilidade(this->_acoes.size());
	vector<double>			melhoresPesos(this->_pesos);
	double					melhorSharpe = 0;
	double					selic = stod(Externo::extrair_selic_python()) / 100;

	for (unsigned i = 0; i < this->_acoes.size(); i++) {
		vector<double> serie = this->_acoes.at(i).getHistorico();
		vector<double> retornos = Matematica::vetorRetorno(serie);
		double media = Matematica::media(retornos);

		serieRetornos[i] = retornos;
		serieMedias[i] = media;
		serieRentabilidade[i] = (serie.back() - serie.front()) / serie.front();
	}

	melhorSharpe = Matematica::produtoVetorial(melhoresPesos, serieMedias) - selic;
	melhorSharpe /= Matematica::correlacao(melhoresPesos, serieRetornos);
	for (unsigned i = 0; i < 30000; i++) {
		vector<double> pesos = Matematica::vetorAleatorio(this->_acoes.size());
		double sharpe = Matematica::produtoVetorial(pesos, serieMedias) - selic;
		sharpe /= Matematica::correlacao(pesos, serieRetornos);

		if (sharpe > melhorSharpe) {
			melhoresPesos = pesos;
			melhorSharpe = sharpe;
		}
	}

	_mostrarCarteriraOtima(serieRetornos, serieMedias, serieRentabilidade,
												melhoresPesos, melhorSharpe);
}
