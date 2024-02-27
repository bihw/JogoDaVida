# Jogo Da Vida
Implementação do algoritmo do __Jogo da Vida de John Conway__ com __MPI__ para o segundo trabalho avaliativo da disciplina de Introdução a Processamento Paralelo e Distribuído na UFPel. 
* valores default ou não
* estado inicial
* verde ou não

## 🛠️ Compilando e executando
```

```

## ✔️ Saída
<p align="center">
<img src="https://github.com/bihw/EditorDeCenaCG/assets/76601652/896f8479-809c-4175-8779-7bd6a714608c" width="45%" height="40%" >
</p>

## ✅ To do
* ✔️ Implementar o algoritmo do Jogo da Vida. Este jogo possui um tabuleiro representado por uma matriz NxN. Cada posição da matriz representa uma célula. As células podem estar vivas, representado pelo valor 1 (um), ou mortas, valor 0 (zero). O estado de uma célula é calculado a cada passo: a cada passo todas as células são visitadas.  Uma célula viva continua viva no próximo passo se ela tem 2 ou 3 vizinhos vivos. Caso contrário, ela morre de solidão ou superpopulação. Uma célula morta se torna viva na próxima geração se ela tem exatamente 3 vizinhos vivos.

* O programa deve realizar o seguinte algoritmo básico:
  * ✔️ Nó rank 0: reparte a configuração inicial da matriz entre os todos os nós (cada nó tem uma parte do terreno)
  * ✔️ Cada nó, inclusive o mestre, evolui as células no seu terreno
  * ✔️ Todos os nós enviam par ao mestre o resultado do cálculo de cada geração
  * ✔️ O nó mestre apresenta (de forma gráfica ou simples caracteres ASCII) a evolução das gerações de células
