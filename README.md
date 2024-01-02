# ImageEncoder
Projeto desenvolvido seguindo as diretrizes e instruções detalhadas do professor, como parte de um trabalho prático universitário.

## Sobre o Projeto
O ImageEncoder é um programa de linha de comando desenvolvido em C para codificar imagens binárias. Ele suporta imagens no formato PBM (Portable Bitmap) e também permite a inserção manual de dados de imagem. O programa divide a imagem em quadrantes sucessivos até que todos tenham pixels uniformes, indicando as divisões e as cores uniformes (preto ou branco) de cada quadrante.

## Funcionalidades
- **Ajuda**: Exibe informações sobre como usar o programa e seus argumentos.
- **Manual**: Permite ao usuário inserir as dimensões e os pixels da imagem manualmente.
- **Arquivo**: Processa uma imagem a partir de um arquivo no formato PBM.

## Pré-requisitos
Para executar o ImageEncoder, é necessário ter um ambiente que suporte a compilação e execução de programas em C. Um compilador de C, como o GCC, é essencial.

## Uso
Após a compilação, você pode executar o programa de diferentes maneiras, dependendo do modo desejado:
- **Exibição da Ajuda**: `ImageEncoder -?` ou `ImageEncoder --help`
- **Modo Manual**: `ImageEncoder -m` ou `ImageEncoder --manual`
- **Modo Arquivo**: `ImageEncoder -f ARQUIVO` ou `ImageEncoder --file ARQUIVO`

##  Formato do Arquivo PBM
O programa espera que os arquivos PBM estejam no formato adequado, com um "magic number" "P1" seguido pelas dimensões da imagem e pelos dados dos pixels (0s e 1s).
Linhas de comentários dentro do arquivo, iniciadas pelo caractere "#", são ignoradas.

Um exemplo do conteúdo de um arquivo em formato Portable bitmap (PBM) de uma imagem 6x10 contendo a letra "J":

![Exemplo do arquivo PBM](https://i.imgur.com/fGln30T.png)

##  Exibição de Resultados na Codificação de Imagens
O comportamento da exibição dos resultados na tela depende da uniformidade dos quadrantes e da divisão realizada durante o processamento. Abaixo estão detalhadas as duas principais situações:

###  Quando um Quadrante Possui Apenas Uma Cor:
Se todos os pixels dentro de um quadrante específico são da mesma cor, o programa identifica este quadrante como uniforme.
Para quadrantes uniformes, o programa exibe um único caractere representando a cor dominante em todo o quadrante:
- P é exibido se todos os pixels no quadrante são pretos (valor 1).
- B é exibido se todos os pixels são brancos (valor 0).
Esse método de representação ajuda a simplificar a representação da imagem, reduzindo a necessidade de detalhar cada pixel individualmente.

###  Quando Ocorre a Divisão da Imagem:
Se um quadrante não é uniforme (ou seja, contém pixels de ambas as cores), o programa procede com a divisão desse quadrante em até quatro subquadrantes menores.
- A cada divisão realizada, o caractere X é impresso. Este caractere serve como indicador de que uma divisão foi feita nesse ponto da imagem.
- O processo de divisão é recursivo: cada subquadrante gerado é novamente avaliado quanto à sua uniformidade. Se não for uniforme, sofre nova divisão, seguindo o mesmo processo.
Este método permite detalhar a imagem em áreas cada vez menores até que cada parte da imagem seja representada por quadrantes uniformes (todos brancos ou todos pretos).

## Contribuições
Este projeto foi desenvolvido como parte de uma atividade acadêmica e está aberto a sugestões e melhorias.

## Autor
- Vitor Arantes Vendramini - vitor_arantes@yahoo.com.br

---
