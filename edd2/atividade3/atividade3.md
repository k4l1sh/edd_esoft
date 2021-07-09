    Os algoritmos de busca são os algoritmos responsáveis por retornar uma informação guardada em alguma estrutura de dados. Pode-se dividir os tipos de algoritmos de busca com base em seu mecanismo de busca: lineares, binários ou por hash. Os algoritmos de busca sequencial, busca sequencial indexada, busca binária e busca por interpolação se encaixam na categoria dos tipos de busca lineares e binárias.
    Uma diferença do algoritmo de busca sequencial para os 3 demais citados, deve-se ao fato de que a busca sequencial, ou busca linear como também é conhecida, consegue realizar uma busca em uma lista que não esteja ordenada. Sendo uma das formas mais simples de busca, a busca sequencial possui uma complexidade de tempo média de O(n/2), sendo n a quantidade de itens presentes na lista. Possuindo uma complexidade de tempo na escala linear, o algoritmo de busca sequencial é utilizado de uma forma eficiente em estruturas de dados muito pequenas ou quando não se deseja ordenar a lista de dados. Quando há a opção de ordenamento da lista, os algoritmos de busca sequencial indexada, busca binária ou busca por interpolação podem ser implementados para se obter uma complexidade de tempo mais eficiente.
    A busca sequencial indexada, de forma similar a busca sequencial, realiza uma busca em forma sequencial até achar o elemento correto, porém, na busca sequencial indexada, a estrutura de dados precisa estar ordenada, pois os elementos da lista são separados em outra lista com uma menor quantidade de dados, da qual os dados presentes são elementos em diferentes índices da lista de busca. Uma busca sequencial em menor escala é realizada nessa outra lista menor, com a finalidade de se aproximar mais rapidamente do índice alvo. Podem ser extraídas diversas listas menores em uma busca sequencial indexada, sendo que quanto mais abstrações da lista de busca forem realizadas, mais se diminui a complexidade de tempo necessária para achar o elemento alvo, porém aumenta-se a complexidade de espaço. De forma parecida com a busca sequencial indexada, porém sem a necessidade de abstração da lista principal em diferentes listas menores, existe o algoritmo da busca em pulos, ou jump search, que realiza também uma busca sequencial em uma lista ordenada, porém ao contrário de passar de elemento por elemento, são realizados saltos com um índice já determinado (por exemplo, de 10 em 10 elementos) e quando o índice passar do alvo, é realizada uma busca sequencial de elemento por elemento até achar o valor procurado.
    Uma outra forma de se realizar uma busca em uma lista ordenada, seria por meio do algoritmo de busca binária. A busca binária é interessante pelo fato de que possui uma complexidade temporal média logarítmica O(log(n)) com a base logarítmica de 2. No algoritmo de busca binária, começa-se pela metade da lista, e então é efetuada uma condição para determinar se o valor alvo está do início para o meio ou do meio para o final através de uma comparação de qual é o maior e o menor valor. Após decidir em qual metade está o alvo, o algoritmo de busca binária descarta a outra metade da busca, e repete o processo começando pela metade da metade. Para se ter uma ideia do quão mais eficiente é o algoritmo de busca binária do que o algoritmo de busca sequencial em uma lista grande ordenada, para uma lista com 1.048.576 itens, o algoritmo de busca sequencial iria demorar em média 524.288 iterações para achar o índice alvo, enquanto o algoritmo de busca binária iria achar o alvo em apenas 20 iterações.
    De forma parecida com o algoritmo de busca binária, temos o algoritmo de busca por interpolações, que é uma melhoria do algoritmo de busca binária para algumas situações das quais os valores da lista estejam uniformemente distribuídos. No caso do algoritmo de busca por interpolações, a busca não necessariamente é realizada sempre na metade da lista em consideração. Realiza-se uma interpolação linear para determinar em qual parte está mais tendente de se ter o valor procurado. Vale lembrar que como é realizada uma interpolação linear para determinar em qual parte há maior probabilidade de se encontrar o valor, o tempo computacional ideal para se realizar este algoritmo de busca seria O(log(log(n))) supondo-se que os valores da lista estejam uniformemente distribuídos. Caso contrário, em qual a lista não esteja com seus valores uniformemente distribuídos, o tempo de complexidade seria linear.
    oncluindo-se este texto dissertativo, podemos destacar a importância de conhecer os diferentes algoritmos de busca, pois como pode-se absorver da comparação do funcionamento dos algoritmos de busca sequencial, sequencial indexada, binária e por interpolação, é dedutível que não existe um melhor algoritmo para todas as situações. Antes de escolher qual algoritmo usar, deve-se conhecer o problema e analisar quais algoritmos irão se sair melhor naquele caso. Por exemplo, caso a lista não esteja ordenada, não é possível usar algoritmos como o de busca binária, sequencial indexada ou por interpolação e caso a lista esteja com seus valores ordenados e uniformemente distribuídos, o algoritmo por interpolação apresenta uma ótima performance.