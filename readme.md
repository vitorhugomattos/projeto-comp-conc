# Ordenação concorrente usando Merge Sort.
### Vitor Hugo de Brito Mattos
### Computação Concorrente (ICP-117) - 2022/1

## Descrição do problema
Foi escolhida a implementação do algoritmo de ordenação Merge Sort. No Merge Sort dividimos o problema (vetor desordenado) em várias partes pequenas e resolvemos cada subproblema recursivamente. Para a entrada, usaremos um vetor de inteiros aleatório de tamanho a ser definido pelo usuário e como saída a verificação da corretude da ordenação, além do tempo de execução do algoritmo (de forma sequencial e concorrente), além do ganho de desempenho.

Podemos usar a concorrencia para acelerar a ordenação dos subvetores que esse algortimo cria.

## Projeto e implementação da solução concorrente

O algoritmo do Mergesort pode ser visualizado como uma árvore binária: a ideia é usar concorrência para resolver uma subárvore (ordenar os subvetores) que aparecerem quando tivermos threads livres na fila.

Podemos realizar a tarefa de algumas formas:
- realizar a etapa da divisão dos vetores sincronamente e dividir os subvetores em blocos, realizando a divisão de tarefas para cada nível de forma que um nível só poderia começar a ser processado por uma thread depois que o nível inferior já tenha sido concluído em todas as threads;
- realizar a etapa da divisão dos vetores sincronamente e dividir os subvetores de maneira intercalada, realizando a divisão de tarefas para cada nível de forma que um nível só poderia começar a ser processado por uma thread depois que o nível inferior já tenha sido concluído em todas as threads;
- realizar a etapa da divisão dos vetores sincronamente e colocar os subvetores em uma fila de processamento, gerando uma fila de tarefas para cada nível de forma que a fila de um nível só poderia começar a ser processada por uma thread depois que o nível inferior já tenha sido concluído em todas as threads;
- realizar a divisão já assíncronamente, fazendo com que uma thread processe uma subárvore (mas verifique se não existe uma thread livre para entregar um pedaço dessa subárvore e acelerar o trabalho).

A ideia escolhida foi a quarta e última, pois ela é a de mais fácil implementação. Como um índice do vetor a ser ordenado nunca será acessado 2 vezes no mesmo nível, podemos usar um vetor global sem necessidade de implementar exclusão mútua para ele.

## Casos de teste
O programa deverá verificar a ordenação dos elementos do vetor resultante por comparação simples: cada entrada deve ser maior ou igual em comparação à entrada anterior. Essa verificação será feita de maneira sequencial.

## Avaliação de desempenho
Essas foram as entradas utilizadas:

* Dimensão do vetor aleatório:
    1. 10<sup>5</sup> inteiros
    2. 10<sup>7</sup> inteiros
    3. 10<sup>9</sup> inteiros

* Número de threads:
    1. 1 thread _(sequencial, usado para avaliação da aceleração)_
    2. 2 threads
    3. 4 threads
    4. 8 threads
    5. 12 threads

Essas são as médias dos resultados obtidos (5 vezes para cada combinação de entradas e aceleração calculada com _média de tempo sequencial/média de tempo concorrente_):

1. 10<sup>5</sup> inteiros aleatórios:
    1. 1 thread: 0.015628 segundo.
    2. 2 threads: 0.019935 segundo. _Aceleração: 0.78394783_.
    3. 4 threads: 0.017329 segundo. _Aceleração: 0.901840845_.
    4. 8 threads: 0.017660 segundo. _Aceleração: 0.884937712_.
    5. 12 threads: 0.020009. _Aceleração: 0.781048528_.

2. 10<sup>7</sup> inteiros aleatórios:
    1. 1 thread: 2.150986 segundos.
    2. 2 threads: 1.742907 segundos. _Aceleração: 1.234136991_.
    3. 4 threads: 1.608417 segundos. _Aceleração: 1.337331053_.
    4. 8 threads: 1.621717 segundos. _Aceleração: 1.326363354_.
    5. 12 threads: 1.782047 segundos. _Aceleração: 1.207031015_.

3. 10<sup>9</sup> inteiros aleatórios:
    1. 1 thread: 275.207717 segundos.
    2. 2 threads: 201.260297 segundos. _Aceleração: 1.367421797_.
    3. 4 threads: 233.125037 segundos. _Aceleração: 1.180515489_.
    4. 8 threads: 168.145133 segundos. _Aceleração: 1.636727225_.
    5. 12 threads: 182.791572 segundos. _Aceleração: 1.50558209_.

## Discussão
O ganho de desempenho esperado **não** foi alcançado. Problemas no método de divisão das tarefas foram os principais responsáveis, pois não permitiram o uso mais eficiente das diversas threads disponíveis.

Uma forma melhor de divisão das tarefas poderia acelerar consideralvelmente a execução do algoritmo.

## Referências bibliográficas
1. L., Sergei. passing struct to pthread as an argument. **Stack Overflow**, 2013. Disponível em: <https://stackoverflow.com/questions/20196121/passing-struct-to-pthread-as-an-argument>. Acesso em: 4 de jul. de 2022.

2. Puckett, Jeff. How to markdown nested list items in Bitbucket?. **Stack Overflow**, 2016. Disponível em: <https://stackoverflow.com/questions/37575916/how-to-markdown-nested-list-items-in-bitbucket>. Acesso em: 4 de jul. de 2022.
