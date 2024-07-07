import yfinance as yf
import requests as rq

def get_selic():

	# Realizando um Get para a API do Banco Central
	response = rq.get("https://api.bcb.gov.br/dados/serie/bcdata.sgs.11/dados/ultimos/1?formato=json")

	# Verifica se a requisição foi bem-sucedida, lança uma exceção caso contrario
	response.raise_for_status()

	# Coletando a taxa selic em % a.d.
	selic = response.json()[0]['valor']

	return selic

def get_acao(acao_nome):

	retorno = []

	# Extraindo e preparando as informações necessarias da Ação
	acao = yf.Ticker(f"{acao_nome}.SA")
	# Verificação para saber se o codigo da ação passado é valido
	if acao.history('1d').empty:
		raise ValueError(f"O identificador '{acao_nome}' não pertence a uma ação valida!")
	infos = acao.info
	vDia = acao.history('5d')['Close'].to_numpy()
	vMes = acao.history('1mo')['Close'].to_numpy()
	vAno = acao.history('1y')['Close'].to_numpy()
	divs = acao.dividends
	historico_semana = acao.history('5d')
	historico_fechamento = acao.history('2y')['Close'].to_numpy()


	# Registra informações referentes a empresa
	retorno.append("")
	if ('longName' in infos):			retorno[-1] += f"Nome;{infos['longName']}\n"
	if ('symbol' in infos):				retorno[-1] += f"Sigla;{infos['symbol'].replace('.SA','')}\n"
	if ('industry' in infos):			retorno[-1] += f"Industria;{infos['industry']}\n"
	if ('website' in infos):			retorno[-1] += f"Site;{infos['website']}\n"
	if ('marketCap' in infos):			retorno[-1] += f"Valor de Mercado;R$ {infos['marketCap']:,.2f}\n"
	if ('enterpriseValue' in infos):	retorno[-1] += f"Valor da Empresa;R$ {infos['enterpriseValue']:,.2f}\n"
	if ('totalRevenue' in infos):		retorno[-1] += f"Receita Liquida;R$ {infos['totalRevenue']:,.2f}\n"
	if ('netIncomeToCommon' in infos):	retorno[-1] += f"Lucro Liquido;R$ {infos['netIncomeToCommon']:,.2f}\n"
	if ('totalDebt' in infos):			retorno[-1] += f"Divida Bruta;R$ {infos['totalDebt']:,.2f}\n"
	if ('totalDebt' in infos \
		and 'totalCash' in infos):		retorno[-1] += f"Divida Liquida;R$ {infos['totalDebt'] - infos['totalCash']:,.2f}\n"
	if ('ebitda' in infos):				retorno[-1] += f"Ebitda;R$ {infos['ebitda']:,.2f}\n"
	if ('ebitdaMargins' in infos):		retorno[-1] += f"Margem Ebitda;{infos['ebitdaMargins'] * 100:.2f}%\n"
	if ('trailingPE' in infos):			retorno[-1] += f"P/L;{infos['trailingPE']:.2f}\n"
	if ('dividendYield' in infos):		retorno[-1] += f"Dividend Yield;{infos['dividendYield'] * 100:.2f}%\n"
	if ('sharesOutstanding' in infos):	retorno[-1] += f"Acoes em Ciculacao;{infos['sharesOutstanding']:,.2f}\n"


	# Registra informações referentes a cotação da ação
	retorno.append("")
	retorno[-1] += f"Fechamento Anterior;R$ {infos['previousClose']}\n"
	try:
		retorno[-1] += f"Abertura;R$ {infos['open']}\n"
		retorno[-1] += f"Min -- Max (Dia);R$ {infos['dayLow']} -- {infos['dayHigh']}\n"
		retorno[-1] += f"Volume;{infos['volume']:,}\n"
	except:
		df = historico_semana
		retorno[-1] += f"Abertura;R$ {df.loc[df.index[-1], 'Open']:.2f}\n"
		retorno[-1] += f"Min -- Max (Dia);R$ \
{df.loc[df.index[-1], 'Low']:.2f} -- {df.loc[df.index[-1], 'High']:.2f}\n"
		retorno[-1] += f"Volume;{df.loc[df.index[-1], 'Volume']:,}\n"
	retorno[-1] += f"Volume Medio (10 dias);{infos['averageVolume10days']:,}\n"
	retorno[-1] += f"Recomendacao;{infos['recommendationKey']}\n"
	retorno[-1] += f"Variacao (Dia);{((vDia[-1] - vDia[-2]) * 100 / vDia[-2]):.2f}%\n"
	retorno[-1] += f"Variacao (Mes);{((vMes[-1] - vMes[0]) * 100 / vMes[0]):.2f}%\n"
	retorno[-1] += f"Variacao (Ano);{((vAno[-1] - vAno[0]) * 100 / vAno[0]):.2f}%\n"


	# Registra os historicos de dividendos pagos
	# data - valor
	retorno.append("")
	for i in range(divs.shape[0]-1, -1, -1):
		data = divs.index[i].date().strftime('%d/%m/%Y')
		retorno[-1] += f"{data} {divs.iloc[i]}\n"


	# Registra informações referentes as negocioações da ação na ultima semana
	# data - abertura - alta - baixa - fechamento - volume
	retorno.append("")
	for i in range(historico_semana.shape[0]-1, -1, -1):
		data = historico_semana.index[i].date().strftime('%d/%m/%Y')
		linha = historico_semana.iloc[i]
		retorno[-1] += f"{data} {linha[0]:.2f} {linha[1]:.2f} {linha[2]:.2f} \
{linha[3]:.2f} {linha[4]:.0f}\n"


	# Registra as informações de fechamento da ação nos ultimos 5 anos
	retorno.append("")
	for valor in historico_fechamento[::-1]:
		retorno[-1] += f"{valor:.4f} "

	return retorno


if __name__ == '__main__':

	print("/¨¨¨¨   TESTE SELIC   ¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨")
	selic = get_selic()
	print(f"| Selic Atual em '%' a.d.: {selic}")
	print("\___________________________________________________________")

	print("/¨¨¨¨   TESTE ACAO   ¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨")
	retorno = get_acao("PETR4")
	print(f"| Tamanho da Lista: {len(retorno)}")
	print(f"| Conteudo: \n")
	for dado in retorno:
		print(dado, end='\n\n')
	print("\___________________________________________________________")
