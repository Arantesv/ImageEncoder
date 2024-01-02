/**
 * ImageEncoder.c - Codificador de Imagens. 
 * 
 * Autor: Vitor Arantes Vendramini
 * Criado em: 20 de Novembro de 2023
 * Última modificação: 30 de Dezembro de 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * @brief Exibe as instruções de uso do programa e informações sobre os argumentos da linha de comando.
 *
 * Esta função imprime na tela um guia de ajuda detalhando como usar o programa ImageEncoder, 
 * incluindo uma descrição de cada argumento de linha de comando suportado. É útil para usuários 
 * que precisam de informações sobre as diferentes opções e modos de operação do programa.
 *
 * As opções detalhadas incluem:
 * - ?, --help   : Apresenta esta orientação na tela.
 * - m, --manual : Ativa o modo de entrada manual, onde o usuário insere os dados da imagem pelo teclado.
 * - f, --file   : Processa a imagem a partir de um arquivo PBM especificado.
 *
 */
void ajuda()
{
    printf("Uso: ImageEncoder [-? | -m | -f ARQ]\n");
    printf("Codifica imagens binarias dadas em arquivos PBM ou por dados informados manualmente.\n");
    printf("Argumentos:\n");
    printf("-?, --help : apresenta essa orientação na tela.\n");
    printf("-m, --manual: ativa o modo de entrada manual.\n");
    printf("-f, --file: considera a imagem representada no arquivo PBM (Portable bitmap).\n");
}

/**
 * @brief Verifica se todos os pixels em um quadrante específico são da mesma cor.
 *
 * Esta função examina um quadrante dentro da matriz representando uma imagem
 * para determinar se todos os pixels nesse quadrante são da mesma cor.
 * O quadrante é definido por suas coordenadas de linha e coluna.
 *
 * @param altura Altura total da matriz.
 * @param largura Largura total da matriz.
 * @param matriz Matriz representando a imagem, onde cada elemento é um pixel.
 * @param primeira_linha Índice da primeira linha do quadrante a ser verificado.
 * @param ultima_linha Índice da última linha do quadrante a ser verificado.
 * @param primeira_coluna Índice da primeira coluna do quadrante a ser verificado.
 * @param ultima_coluna Índice da última coluna do quadrante a ser verificado.
 * @return Retorna `true` se todos os pixels no quadrante são da mesma cor,
 *         caso contrário, retorna `false`.
 * 
 */
bool uniforme(int altura, int largura, int matriz[altura][largura], int primeira_linha, int ultima_linha, int primeira_coluna, int ultima_coluna)
{
    int i, j;
    int uniforme = 0;

    for (i = primeira_linha; i <= ultima_linha; i++)
    {
        for (j = primeira_coluna; j <= ultima_coluna; j++)
        {
            if (matriz[i][j] != matriz[primeira_linha][primeira_coluna])
            {
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief Divide a matriz em quadrantes sucessivos até que todos tenham pixels uniformes.
 *
 * Esta função divide recursivamente uma matriz em quadrantes menores e utiliza a função "uniforme" para
 * verificar se cada quadrante contém pixels de uma única cor (preto ou branco). 
 * O processo de divisão continua até que cada quadrante restante seja uniforme em termos de cor de pixel.
 * Durante o processo, a função imprime 'X' para indicar uma divisão, 'P' se todos os
 * pixels em um quadrante são pretos, e 'B' se todos os pixels são brancos.
 *
 * @param altura Altura total da matriz.
 * @param largura Largura total da matriz.
 * @param matriz Matriz representando a imagem, onde cada elemento é um pixel.
 * @param primeira_linha Índice da primeira linha do quadrante atual.
 * @param ultima_linha Índice da última linha do quadrante atual.
 * @param primeira_coluna Índice da primeira coluna do quadrante atual.
 * @param ultima_coluna Índice da última coluna do quadrante atual.
 *
 */
void quadrantes(int altura, int largura, int matriz[altura][largura], int primeira_linha, int ultima_linha, int primeira_coluna, int ultima_coluna)
{
    if (!uniforme(altura, largura, matriz, primeira_linha, ultima_linha, primeira_coluna, ultima_coluna))
    {
        printf("X");

        // Realiza o corte na metade da linha e da coluna.
        int linha_meio = (primeira_linha + ultima_linha) / 2;
        int coluna_meio = (primeira_coluna + ultima_coluna) / 2;

        quadrantes(altura, largura, matriz, primeira_linha, linha_meio, primeira_coluna, coluna_meio);

        quadrantes(altura, largura, matriz, primeira_linha, linha_meio, coluna_meio + 1, ultima_coluna);

        // Verifica se a primeira linha/coluna do proximo quadrante nao sera maior que a ultima linha/coluna dele mesmo.
        if (linha_meio + 1 <= ultima_linha && primeira_coluna <= coluna_meio)
        {
            quadrantes(altura, largura, matriz, linha_meio + 1, ultima_linha, primeira_coluna, coluna_meio);
        }

        if (linha_meio + 1 <= ultima_linha && primeira_coluna <= coluna_meio)
        {
            quadrantes(altura, largura, matriz, linha_meio + 1, ultima_linha, coluna_meio + 1, ultima_coluna);
        }
    }
    else
    {
        if (matriz[primeira_linha][primeira_coluna] == 0)
        {
            printf("B");
        }
        else if (matriz[primeira_linha][primeira_coluna] == 1)
        {
            printf("P");
        }
    }
}

/**
 * @brief Lê e processa uma matriz a partir de um arquivo no formato PBM (Portable Bitmap).
 *
 * Esta função é projetada para ler arquivos no formato Portable Bitmap (PBM), que começam
 * com um "magic number" "P1". Após o "magic number", o arquivo contém dois valores numéricos
 * representando a largura e a altura da imagem, seguidos pelos dados dos pixels, representados
 * por 0s e 1s. Comentários dentro do arquivo, indicados pelo caractere "#", são ignorados durante
 * a leitura.
 *
 * A função espera que o arquivo esteja corretamente formatado de acordo com as especificações do PBM.
 * A matriz de pixels é processada a partir dos dados lidos do arquivo.
 *
 * @param fileName Nome do arquivo PBM a ser lido.
 * 
 */
void arquivo(const char *fileName)
{
    FILE *arquivo = fopen(fileName, "r");

    if (arquivo == NULL)
    {
        printf("Erro: Ao abrir o arquivo '%s'.\n", fileName);
        return;
    }

    char formato[3];
    int largura, altura, i, j;
    fscanf(arquivo, "%2s", formato);

    if (formato[0] != 'P' || formato[1] != '1')
    {
        printf("Erro: Formato de arquivo invalido.\n");
        fclose(arquivo);
        return;
    }

    char linha[128];
    while (fgets(linha, 128, arquivo) != NULL)
    {
        // Ignora os comentarios sinalizados pelo caractere "#".
        if (linha[0] == '#')
        {
            continue;
        }

        // Verifica se a linha contem as dimensoes da matriz.
        if (sscanf(linha, "%d %d", &largura, &altura) == 2)
        {
            break;
        }
    }

    if (largura > 1024 || altura > 768)
    {
        printf("Erro: Dimensoes da matriz maior que o maximo permitido.\n");
        fclose(arquivo);
        return;
    }

    int matriz[altura][largura];

    for (i = 0; i < altura; i++)
    {
        for (j = 0; j < largura; j++)
        {
            fscanf(arquivo, "%d", &matriz[i][j]);
        }
    }

    quadrantes(altura, largura, matriz, 0, altura - 1, 0, largura - 1);
    fclose(arquivo);
}

/**
 * @brief Permite ao usuário inserir manualmente as dimensões e os elementos de uma matriz.
 *
 * Esta função é chamada quando o usuário opta pelo modo manual de entrada de dados no programa.
 * Ela solicita ao usuário que forneça as dimensões da matriz (largura e altura) e, em seguida,
 * os elementos da matriz (pixels), um por um. Essa função é ideal para testes ou para pequenas
 * matrizes onde a entrada manual é viável.
 *
 * A função assume que o usuário insere dados válidos (por exemplo, números inteiros para as
 * dimensões e valores de pixel) e pode precisar de validação adicional em contextos onde a
 * entrada do usuário é menos confiável.
 *
 */
void manual()
{
    int altura, largura, i, j;

    printf("Digite as dimensoes da matriz (largura e altura): ");
    scanf("%d %d", &largura, &altura);

    if (largura > 1024 || altura > 768)
    {
        printf("Dimensoes da matriz maior que o maximo permitido.\n");
        return;
    }

    int matriz[altura][largura];

    printf("Digite os elementos da matriz:\n");
    for (i = 0; i < altura; i++)
    {
        for (j = 0; j < largura; j++)
        {
            scanf("%d", &matriz[i][j]);
        }
    }

    quadrantes(altura, largura, matriz, 0, altura - 1, 0, largura - 1);
}

/**
 * @brief Interface de linha de comando (CLI) para o programa ImageEncoder.
 *
 * Esta função é o ponto de entrada do programa ImageEncoder, que processa imagens
 * no formato PBM. Os argumentos necessários para a execução do programa são fornecidos
 * através da linha de comando. A função analisa esses argumentos e decide o modo de
 * operação do programa, podendo ser a exibição da ajuda, entrada manual de dados da imagem,
 * ou processamento de um arquivo PBM.
 * Se nenhum argumento for fornecido, a orientação será exibida na tela.
 *
 * @param argc Número de argumentos de linha de comando.
 * @param argv Vetor de strings contendo os argumentos de linha de comando.
 * @return Retorna 0 em caso de sucesso, ou um código de erro específico em caso de falha.
 *
 * Exemplo de uso:
 * @code
 * // Modo de ajuda
 * ImageEncoder -?
 *
 * // Modo manual
 * ImageEncoder -m
 *
 * // Modo de arquivo
 * ImageEncoder -f imagem.pbm
 * @endcode
 */
int main(int argc, char *argv[])
{
    int i;

    if (argc == 1)
    {
        ajuda();
    }
    else
    {
        for (i = 1; i < argc; i++)
        {
            if (strcmp(argv[i], "-?") == 0 || strcmp(argv[i], "--help") == 0)
            {
                ajuda();
            }
            else if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--manual") == 0)
            {
                manual();
            }
            else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0)
            {
                if (i + 1 < argc)
                {
                    arquivo(argv[i + 1]);
                    i++;
                }
                else
                {
                    printf("Erro: O argumento -f/--file requer o nome do arquivo.\n");
                }
            }
            else
            {
                printf("Erro: Argumento desconhecido: %s\n", argv[i]);
                ajuda();
            }
        }
    }
    return 0;
}
