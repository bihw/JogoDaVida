# Jogo Da Vida
Implementação do algoritmo do __Jogo da Vida de John Conway__ com __MPI__ para o segundo trabalho avaliativo da disciplina de Introdução a Processamento Paralelo e Distribuído na UFPel. 

<p align="center">
<img src="https://github.com/bihw/JogoDaVida/assets/76601652/0926009c-7deb-49a5-8a64-2f41fe659a9d)" >
</p>
<p align="center">
<img src="https://github.com/bihw/JogoDaVida/assets/76601652/c6838870-34d0-4bbd-ba0d-9c2a5a5f15fb" >
</p>

# 
* valores default ou não
* estado inicial
* verde ou não

## 🛠️ Compilando e executando
```

```

## ✔️ Saída


## ✅ To do
* ✔️ Implementar o algoritmo do Jogo da Vida. Este jogo possui um tabuleiro representado por uma matriz NxN. Cada posição da matriz representa uma célula. As células podem estar vivas, representado pelo valor 1 (um), ou mortas, valor 0 (zero). O estado de uma célula é calculado a cada passo: a cada passo todas as células são visitadas.  Uma célula viva continua viva no próximo passo se ela tem 2 ou 3 vizinhos vivos. Caso contrário, ela morre de solidão ou superpopulação. Uma célula morta se torna viva na próxima geração se ela tem exatamente 3 vizinhos vivos.

* O programa deve realizar o seguinte algoritmo básico:
  * ✔️ Nó rank 0: reparte a configuração inicial da matriz entre os todos os nós (cada nó tem uma parte do terreno)
  * ✔️ Cada nó, inclusive o mestre, evolui as células no seu terreno
  * ✔️ Todos os nós enviam par ao mestre o resultado do cálculo de cada geração
  * ✔️ O nó mestre apresenta (de forma gráfica ou simples caracteres ASCII) a evolução das gerações de células
