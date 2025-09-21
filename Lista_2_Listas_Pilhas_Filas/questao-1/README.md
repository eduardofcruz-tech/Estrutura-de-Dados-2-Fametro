# Controle de Estoque com Lista Ligada

## Visão Geral
Este projeto implementa um sistema de controle de estoque simples, utilizando uma lista simplesmente encadeada para armazenar e gerenciar produtos. A aplicação interage com o usuário através de uma interface de linha de comando.

## Estrutura do Código
- **`main.c`**: Contém a lógica principal da aplicação, incluindo o `struct Produto` e a implementação das operações da lista ligada.
- **`main`**: Gerencia o loop de interação com o usuário, lê os comandos da entrada padrão e invoca as funções apropriadas.

## Comandos Suportados
- `ADD <cod> "<nome>" <qtd> <preco>`: Adiciona um novo produto de forma ordenada. Se o código já existe, atualiza as informações do produto.
- `UPD <cod> <delta_qtd>`: Ajusta a quantidade de um produto. Não permite que a quantidade se torne negativa.
- `DEL <cod>`: Remove um produto da lista.
- `FIND <cod>`: Busca um produto e exibe suas informações.
- `LIST`: Exibe todos os produtos do catálogo.
- `REL`: Mostra um relatório com o total de itens distintos, o valor total do estoque e o produto com maior valor imobilizado.
- `HELP`: Exibe a lista de comandos.
- `EXIT`: Encerra a aplicação e libera toda a memória alocada.

## Análise de Complexidade (Big-O)

A complexidade de cada operação da lista ligada é analisada em relação a `N`, o número de produtos na lista.

### `inserir_inicio`
- **Complexidade:** `O(1)`
- **Justificativa:** A operação envolve apenas a alocação de um novo nó e a atualização de um ponteiro. O tempo de execução é constante, independentemente do tamanho da lista.

### `inserir_ordenado_por_codigo`
- **Complexidade:** `O(N)` no pior caso.
- **Justificativa:** Para encontrar a posição correta de inserção (ou para verificar se o item já existe), a função pode precisar percorrer toda a lista. No pior caso (inserir no final ou atualizar o último item), o tempo é linear em relação ao número de elementos.

### `remover_por_codigo`
- **Complexidade:** `O(N)` no pior caso.
- **Justificativa:** Similar à inserção ordenada, a busca pelo nó a ser removido pode exigir a travessia de toda a lista.

### `ajustar_quantidade`
- **Complexidade:** `O(N)` no pior caso.
- **Justificativa:** Depende da função `buscar`, que tem complexidade linear. A operação de ajuste da quantidade é constante após a busca, mas o tempo total é dominado pela busca.

### `buscar`
- **Complexidade:** `O(N)` no pior caso.
- **Justificativa:** A função percorre a lista sequencialmente até encontrar o produto ou chegar ao fim da lista.

### `listar`
- **Complexidade:** `O(N)`
- **Justificativa:** A função precisa iterar sobre todos os nós da lista para imprimir suas informações.

### `limpar`
- **Complexidade:** `O(N)`
- **Justificativa:** A função percorre a lista de um nó por vez, liberando a memória de cada um. O tempo de execução é proporcional ao número de nós.