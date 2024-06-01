import yfinance as yf
import os

# Extraindo os dados da Ação indicada
acao_nome = "PETR4"
acao = yf.Ticker(f"{acao_nome}.SA")

# Criando o diretorio dos arquivos temporarios
dir = './temp'
if not os.path.exists(dir):
    os.mkdir(dir)

# Registra informações referentes a empresa
infos = acao.info
with open(f"{dir}/sobre.temp", "w") as sobre:
	sobre.write(f"Nome:{infos['longName']}\n")
	sobre.write(f"Sigla:{infos['symbol'].replace('.SA','')}\n")
	sobre.write(f"Industria:{infos['industry']}\n")
	sobre.write(f"Site:{infos['website']}\n")
	sobre.write(f"Valor de Mercado:R$ {infos['marketCap']:,.2f}\n")
	sobre.write(f"Valor da Empresa:R$ {infos['enterpriseValue']:,.2f}\n")
	sobre.write(f"Receita Liquida:R$ {infos['totalRevenue']:,.2f}\n")
	sobre.write(f"Lucro Liquido:R$ {infos['netIncomeToCommon']:,.2f}\n")
	sobre.write(f"Divida Bruta:R$ {infos['totalDebt']:,.2f}\n")
	sobre.write(f"Divida Liquida:R$ {infos['totalDebt'] - infos['totalCash']:,.2f}\n")
	sobre.write(f"Ebitda:R$ {infos['ebitda']:,.2f}\n")
	sobre.write(f"Margem Ebitda:{infos['ebitdaMargins'] * 100:.2f}%\n")
	sobre.write(f"P/L:{infos['trailingPE']:.2f}\n")
	sobre.write(f"Dividend Yield:{infos['dividendYield'] * 100:.2f}%\n")
	sobre.write(f"Acoes em Ciculacao:{infos['sharesOutstanding']:,.2f}\n")


# Registra informações referentes a cotação da ação
vDia = acao.history('5d')['Close'].to_numpy()
vMes = acao.history('1mo')['Close'].to_numpy()
vAno = acao.history('1y')['Close'].to_numpy()
with open(f"{dir}/info.temp", "w") as info:
	info.write(f"Fechamento Anterior:R$ {infos['previousClose']}\n")
	info.write(f"Abertura:R$ {infos['open']}\n")
	info.write(f"Volume:{infos['volume']:,}\n")
	info.write(f"Volume Medio (10 dias):{infos['averageVolume10days']:,}\n")
	info.write(f"Min -- Max (Dia):R$ {infos['dayLow']} -- {infos['dayHigh']}\n")
	info.write(f"Recomendacao:{infos['recommendationKey']}\n")
	info.write(f"Variacao (Dia):{((vDia[-1] - vDia[-2]) * 100 / vDia[-2]):.2f}%\n")
	info.write(f"Variacao (Mes):{((vMes[-1] - vMes[0]) * 100 / vMes[0]):.2f}%\n")
	info.write(f"Variacao (Ano):{((vAno[-1] - vAno[0]) * 100 / vAno[0]):.2f}%\n")


# Registra os historicos de dividendos pagos
divs = acao.dividends
with open(f"{dir}/dividendos.temp", "w") as dividendos:
	for i in range(divs.shape[0]-1, -1, -1):
		data = divs.index[i].date().strftime('%d-%m-%Y')
		dividendos.write(f"{data} {divs.iloc[i]}\n")


# Registra informações referentes as negocioações da ação na ultima semana
historico_semana = acao.history('5d')
with open(f"{dir}/semana.temp", "w") as semana:
	for i in range(historico_semana.shape[0]-1, -1, -1):
		data = historico_semana.index[i].date().strftime('%d-%m-%Y')
		linha = historico_semana.iloc[i]
		semana.write(f"{data} {linha[0]:.2f} \
{linha[1]:.2f} {linha[2]:.2f} \
{linha[3]:.2f} {linha[3]:.2f}\n")


# Registra as informações de fechamento da ação nos ultimos 5 anos
historico_fechamento = acao.history('5y')['Close'].to_numpy()
with open(f"{dir}/fechamento.temp", "w") as fechamento:
	for valor in historico_fechamento[::-1]:
		fechamento.write(f"{valor:.4f} ")
