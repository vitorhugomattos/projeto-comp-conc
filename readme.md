# Ordenação concorrente usando Merge Sort.
### Bacharelo em Ciência da Computação // IC // UFRJ

## Descrição do problema
Faremos a implementação do algoritmo de ordenação Merge Sort. No Merge Sort dividimos o problema (vetor desordenado) em várias partes pequenas e resolvemos cada subproblema recursivamente. Para a entrada, usaremos um vetor de inteiros aleatório de tamanho a ser definido pelo usuário e como saída a verificação da corretude da ordenação, além do tempo de execução do algoritmo (de forma sequencial e concorrente), além do ganho de desempenho.

Podemos usar a concorrencia para acelerar a ordenação dos subvetores que esse algortimo cria.

## Projeto e implementação da solução concorrente

A ideia é usar concorrência para resolver cada subproblema (ordenar os subvetores), já que eles são independentes entre si. Uma vez que todos os subvetores estejam ordenados (devemos esperar que todas as threads tenham completado seus trabalhos), devemos juntá-los em subvetores maiores e realizar a ordenação concorrente desses subvetores também, de forma que as threads sejam bem aproveitadas.

Podemos realizar a tarefa de algumas formas:
- realizar a etapa da divisão dos vetores sincronamente e dividir os subvetores em blocos, realizando a divisão de tarefas para cada nível de forma que um nível só poderia começar a ser processado por uma thread depois que o nível inferior já tenha sido concluído em todas as threads;
- realizar a etapa da divisão dos vetores sincronamente e dividir os subvetores de maneira intercalada, realizando a divisão de tarefas para cada nível de forma que um nível só poderia começar a ser processado por uma thread depois que o nível inferior já tenha sido concluído em todas as threads;
- realizar a etapa da divisão dos vetores sincronamente e colocar os subvetores em uma fila de processamento, gerando uma fila de tarefas para cada nível de forma que a fila de um nível só poderia começar a ser processada por uma thread depois que o nível inferior já tenha sido concluído em todas as threads;
- realizar a etapa da divisão dos vetores sincronamente e deixar cada thread responsável pelo processamento de todas as ordenações daquele nível.

A ideia escolhida foi a quarta e última, pois ela é a de mais fácil implementação e qual mais facilmente podemos aplicar e tornar nítidos os conceitos de barreira e semáforo.

## Casos de teste
O programa deverá verificar a ordenação dos elementos do vetor resultante por comparação simples: cada entrada deve ser maior ou igual em comparação à entrada anterior. Essa verificação será feita de maneira sequencial.

## Avaliação de desempenho

## Discussão

## Referências bibliográficas
