# Smart Maze

![C](https://badgen.net/badge/MADE-WITH/C)
![LICENSE](https://badgen.net/badge/LICENSE/MIT/green)
![SDL](https://badgen.net/badge/SDL/SDL2/red)

Uma implementação simples de dois algoritmos para gerar e solucionar de forma eficiente labirintos aleatórios. As implementações aplicam o Randomized Depth-First Search Algorithm e o Pathfinder A* que é uma versão estendida de heurística do algoritmo de Dijkstra's.
<div align="center">
    <img width="50%" src="https://github.com/IltonPfleger/Smart-Maze/blob/main/preview.gif">
</div>

# Sobre o Projeto

Objetivo: Criar um sistema que gere um labirinto e encontre o melhor caminho entre o canto superior esquerdo e o canto inferior direito.

Todo o projeto é feito apenas com **SDL/SDL2** e **C** puro.

## Sobre os algoritmos
* Os arquivos presentes nesse repositório possuem um delay (**sleep**) em suas funções principais para que a visualização de todo o processo seja possível.
  
* Para encontrar o menor **F** no **A*** é aplicado uma implementação minha do famoso **QuickSort** ao invés da recomendável **Binary Heap**.
  
* O arquivo do **A*** pode ser facilmente escalável para outros projetos com uma simples extensão da estrutura **CELL**.

* Limitei o **A*** a apenas passos verticais e horizontais para facilitar a sua implementação no labirinto, sinta-se a vontade para criar uma versão com diagonais e compartilhar comigo se quiser.

## Outras informações:

* Os parâmetros gerais das funções podem ser alterados nas definições do arquivo **main.c**
  
* Não é necessário rodar os algoritmos em threads diferentes, fiz isso apenas para que a visualização fosse possível e não bloqueasse a thread principal onde está o main loop do SDL2.

* Fique a vontade para mandar ideias, sugestões, dúvidas e requests. 
