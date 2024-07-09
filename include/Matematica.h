# ifndef MATEMATICA_H
# define MATEMATICA_H

# include <iostream>
# include <cmath>
# include <vector>

using namespace std;

class Matematica
{
	public:
		static vector<double>	vetorRetorno(const vector<double>& vetor);
		static double			produtoVetorial(const vector<double>& vetorX,
													const vector<double>& vetorY);
		static double			media(const vector<double>& vetor);
		static double			variancia(const vector<double>& vetor);
		static double			desvioPadrao(const vector<double>& vetor);
		static double			covariancia(const vector<double>& vetorX,
													const vector<double>& vetorY);
		static vector<vector<double> >	matrizCovariancia(
										const vector<vector<double> >& retornos);
		static double			correlacao(const vector<double>& pesos,
										const vector<vector<double> >& retornos);
		static vector<vector<double> >	matrizCorrelacao(
										const vector<vector<double> >& retornos);
};


#endif
