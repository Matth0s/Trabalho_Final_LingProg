# include "Matematica.h"

vector<double>	Matematica::vetorRetorno(const vector<double>& vetor)
{
	vector<double> retorno;

	for (unsigned i = 0; i < vetor.size() - 1; i ++) {
		retorno.push_back((vetor[i+1] - vetor[i]) / vetor[i]);
	}

	return (retorno);
}

double	Matematica::produtoVetorial(const vector<double>& vetorX,
												const vector<double>& vetorY)
{
	double	resultado = 0;
	double	tamanho = fmin(vetorX.size(), vetorY.size());

	for (unsigned i = 0; i < tamanho; i++) {
		resultado += vetorX[i] * vetorY[i];
	}

	return (resultado);
}

double	Matematica::media(const vector<double>& vetor)
{
	double	resultado = 0;

	for (unsigned i = 0; i < vetor.size(); i++) {
		resultado += vetor[i];
	}

	return (resultado / (double)vetor.size());
}

double	Matematica::variancia(const vector<double>& vetor)
{
	double	resultado = 0;
	double	media = Matematica::media(vetor);

	for (unsigned i = 0; i < vetor.size(); i++) {
		resultado += pow(vetor[i] - media, 2);
	}

	return (resultado / ((double)vetor.size() - 1));
}

double	Matematica::desvioPadrao(const vector<double>& vetor)
{
	return (sqrt(Matematica::variancia(vetor)));
}

double	Matematica::covariancia(const vector<double>& vetorX,
									const vector<double>& vetorY)
{
	double	resultado = 0;
	double	mediaX = Matematica::media(vetorX);
	double	mediaY = Matematica::media(vetorY);
	double	tamanho = fmin(vetorX.size(), vetorY.size());

	for (unsigned i = 0; i < tamanho; i++) {
		resultado += (vetorX[i] - mediaX) * (vetorY[i] - mediaY);
	}

	return (resultado / (tamanho - 1));
}

vector<vector<double> >	Matematica::matrizCovariancia(
										const vector<vector<double> >& retornos)
{
	vector<vector<double> >	matriz;

	for (unsigned i = 0; i < retornos.size(); i++) {
		vector<double>	linha;
		for (unsigned j = 0; j < retornos.size(); j++) {
			linha.push_back(Matematica::covariancia(retornos[i], retornos[j]));
		}
		matriz.push_back(linha);
	}

	return (matriz);
}

double	Matematica::correlacao(const vector<double>& pesos,
										const vector<vector<double> >& retornos)
{
	vector<vector<double> >	matriz;
	double					resultado;

	matriz = Matematica::matrizCovariancia(retornos);

	for (unsigned i = 0; i < matriz.size(); i++) {
		for (unsigned j = 0; j < matriz[i].size(); j++) {
			resultado += (pesos[i] * matriz[i][j] * pesos[j]);
		}
	}

	return (sqrt(resultado));
}

vector<vector<double> >	Matematica::matrizCorrelacao(
										const vector<vector<double> >& retornos)
{
	vector<vector<double> >	matriz;

	for (unsigned i = 0; i < retornos.size(); i++) {
		vector<double>	linha;
		for (unsigned j = 0; j < retornos.size(); j++) {
			double	covariancia = Matematica::covariancia(retornos[i], retornos[j]);
			double	desvioPadraoI = Matematica::desvioPadrao(retornos[i]);
			double	desvioPadraoJ = Matematica::desvioPadrao(retornos[j]);
			linha.push_back(covariancia / (desvioPadraoI * desvioPadraoJ));
		}
		matriz.push_back(linha);
	}

	return (matriz);
}
