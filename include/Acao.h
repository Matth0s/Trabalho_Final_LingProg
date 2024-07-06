# ifndef ACAO_H
# define ACAO_H

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct DadosAcaoDividendos
{
	public:
		/* Data em que foi concedido os dividendos. */
		string			data;
		/* Valor de dividendos por ação que foram distribuidos na data.  */
		double			valor;

		DadosAcaoDividendos(void)
			: data(), valor()
		{};
		DadosAcaoDividendos(const DadosAcaoDividendos& src)
			: data(src.data), valor(src.valor)
		{};
};

struct DadosAcaoComercial
{
	public:

		/* Data em que foram registradas as medições  */
		string			data;
		/* Valor da Ação na abertura das negociações em bolsa.  */
		double			abertura;
		/* Valor mais alto que a ação atingiu na data.  */
		double			alta;
		/* Valor mais baixo que a ação atingiu na data. */
		double			baixa;
		/* Valor da ação no fechamento das negociações em bolsa. */
		double			fechamento;
		/* Volume total de ações negociadas naquela data. */
		unsigned int	volume;

		DadosAcaoComercial(void)
			: data(), abertura(), alta(), baixa(), fechamento(), volume()
		{};
		DadosAcaoComercial(const DadosAcaoComercial& src)
			: data(src.data), abertura(src.abertura), alta(src.alta),
			baixa(src.baixa), fechamento(src.fechamento), volume(src.volume)
		{};
};

class Acao
{
	friend	ostream&	operator<<(ostream& out, const Acao& rhs);

	private:
		/* Armazena informações da empresa que a Ação representa, como: nome,
		endereço, industria... */
		vector<pair<string, string> >	_sobreEmpresa;
		/* Armazena informações sobre a Acão em si, como: valor de fechamento,
		 volume média de ações negociado em bolsa... */
		vector<pair<string, string> >	_infoAcao;
		/* Armazena a data e o valor dos ultimos dividendos distribuidos. */
		vector<DadosAcaoDividendos>		_historicoDividendos;
		/* Armazena informações da ultima semana sobre as negociações da Acão
		como: alta, baixa, volume... */
		vector<DadosAcaoComercial>		_historicoComercial;
		/* Armazena a serie historica de fechamentos da ação nos ultimos 2 anos. */
		vector<double>					_historicoFechamentos;


		/* Função auxiliar para separar os parametros recebidos pelas funções
		externas. */
		vector<string>	_splitString(string str, char delimitador);
		/* Transforma "Nome;teste1\nEndereco;teste2" em vector<pair> onde:
		vector[0].first = Nome,     vector[0].second = teste1,
		vector[1].first = Endereco, vector[1].second = teste2, ... */
		void			_extrairSobreEmpresa(string dadoBruto);
		/* Transforma "Fechamento;teste1\nVolume;teste2" em vector<pair> onde:
		vector[0].first = Fechamento, vector[0].second = teste1,
		vector[1].first = Volume,     vector[1].second = teste2, ... */
		void			_extrairInfoAcao(string dadoBruto);
		/* Transforma "00-00-0000  0.0\n11-11-1111  1.1" em
		vector<DadosAcaoDividendos> onde:
		vector[0].data = 00-00-0000,       vector[0].valor = 0.0,
		vector[1].data = 11-11-1111,       vector[1].valor = 1.1, ... */
		void			_extrairHistoricoDividendos(string dadoBruto);
		/* Transforma "00-00-0000  0.0  0.1  0.2...\n11-11-1111  1.0  1.1  1.2..."
		em vector<DadosAcaoComercial> onde:
		v[0].data = 00-00-0000, v[0].abertura = 0.0, v[0].alta = 0.1, v[0].baixa = 0.2,...
		v[1].data = 11-11-1111, v[1].abertura = 1.0, v[1].alta = 1.1, v[1].baixa = 1.2,... */
		void			_extrairHistoricoComercial(string dadoBruto);
		/* Transforma "0.0   0.1   0.2   0.3   0.4  ..." em vector<double> onde:
		vector[0]= 0.0, vector[1] = 0.1, vector[2] = 0.2, ... */
		void			_extrairHistoricoFechamentos(string dadoBruto);


	public:
		Acao(void);
		Acao(const Acao& src);
		Acao(vector<string> extracao);
		~Acao(void);

		Acao&	operator=(const Acao& rhs);
};

# endif
