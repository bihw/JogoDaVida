# Conway's Game of Life
Implementação do algoritmo d __Jogo da vida de Conway__ com __MPI__ para o segundo trabalho avaliativo da disciplina de Introdução a Processamento Paralelo e Distribuído na UFPel. O jogo da vida é um __autômato celular__ desenvolvido pelo matemático britânico __John Horton Conway__ em 1970.

<p align="center">
      <img src="https://upload.wikimedia.org/wikipedia/commons/1/18/%D0%98%D0%B3%D1%80%D0%B0_%22%D0%96%D0%B8%D0%B7%D0%BD%D1%8C%22.gif" width="20%" height="20%">
      <br>Glider andando no tabuleiro. Créditos: Lev Kalmykov, via <a href="https://en.wikipedia.org/wiki/File:%D0%98%D0%B3%D1%80%D0%B0_%22%D0%96%D0%B8%D0%B7%D0%BD%D1%8C%22.gif">Wikipedia</a>
      <br><br><img src="https://miro.medium.com/v2/resize:fit:448/1*C-684fOao3DieyLZfnGTKw.gif" width="15%" height="15%">
      <br>Regras sendo aplicadas em um Glider. Créditos: Felipe Lodur, via <a href="https://medium.com/@lodur/swarm-intelligence-o-que-%C3%A9-64a0323356e2">Medium</a>
</p>

## 🚩 Atenção
* O número de processos deve ser divisível pela dimensão do tabuleiro.
* O número de gerações default é 200, mas você pode ajustá-lo pela linha de comando.
* A dimensão do tabuleiro está definida para 12, para alterá-la altere direto no código na macro "N".
* O estado inicial do tabuleiro é gerado "aleatoriamente", mas deixei comentado um tabuleiro inicial com dois gliders (planadores). Com esses gliders, pode-se observar melhor que a movimentação funciona corretamente.

## 🛠️ Compilando e executando
Em um Linux com MPI instalado:
* Para compilar:
```
make
```
* Ou:
```
mpicc -o jogodavida jogodavida.c
```
* Para executar: 
```
mpirun -np <numero_de_processos> jogodavida 
```
* Ou:
```
mpirun -np <numero_de_processos> jogodavida <numero_de_geracoes>
```

## ✔️ Saída

<p align="center">
      <img src="https://github.com/bihw/JogoDaVida/assets/76601652/f5af3d82-4e25-473d-b8c5-60e1d98458a3" width="30%" height="30%"> &nbsp&nbsp&nbsp&nbsp&nbsp
      <img src="https://github.com/bihw/JogoDaVida/assets/76601652/ce608734-32fe-4364-85ba-a1b5361afa0f" width="30%" height="30%">
</p>

## ✅ To Do
Implementar o algoritmo do Jogo da Vida. Este jogo possui um tabuleiro representado por uma matriz NxN. Cada posição da matriz representa uma célula. As células podem estar vivas, representado pelo valor 1 (um), ou mortas, valor 0 (zero). O estado de uma célula é calculado a cada passo: a cada passo todas as células são visitadas.  Uma célula viva continua viva no próximo passo se ela tem 2 ou 3 vizinhos vivos. Caso contrário, ela morre de solidão ou superpopulação. Uma célula morta se torna viva na próxima geração se ela tem exatamente 3 vizinhos vivos.

O programa deve realizar o seguinte algoritmo básico: 
 * ✔️ Nó rank 0: reparte a configuração inicial da matriz entre os todos os nós (cada nó tem uma parte do terreno)
 * ✔️ Cada nó, inclusive o mestre, evolui as células no seu terreno
 * ✔️ Todos os nós enviam par ao mestre o resultado do cálculo de cada geração
 * ✔️ O nó mestre apresenta (de forma gráfica ou simples caracteres ASCII) a evolução das gerações de células
