# Jogo Da Vida
Implementação do algoritmo do __Jogo da Vida de John Conway__ com __MPI__ para o segundo trabalho avaliativo da disciplina de Introdução a Processamento Paralelo e Distribuído na UFPel. 

<p align="center">
      <img src="https://upload.wikimedia.org/wikipedia/commons/1/18/%D0%98%D0%B3%D1%80%D0%B0_%22%D0%96%D0%B8%D0%B7%D0%BD%D1%8C%22.gif" width="20%" height="20%" alt="Animação de um Glider andando no tabuleiro"> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
      <img src="https://miro.medium.com/v2/resize:fit:448/1*C-684fOao3DieyLZfnGTKw.gif" width="15%" height="15%" alt="Animação de um Glider mostrando como funcionam as regras do jogo">
</p>

<p align="center">
      Créditos da imagem: Lev Kalmykov, via <a href="https://en.wikipedia.org/wiki/File:%D0%98%D0%B3%D1%80%D0%B0_%22%D0%96%D0%B8%D0%B7%D0%BD%D1%8C%22.gif">Wikipedia</a> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
      Créditos da imagem: Felipe Lodur, via <a href="https://medium.com/@lodur/swarm-intelligence-o-que-%C3%A9-64a0323356e2">Medium</a>
</p>

## 🔍 🚩 ❗
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
