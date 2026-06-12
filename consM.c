#include <stdio.h>
#include <stdlib.h>

int qt_matriz;

struct matriz
{
    int **valor;
    int linha;
    int coluna;
};
typedef struct matriz Matriz;

Matriz *novaMatriz(int linha, int coluna, int **valor)
{
    Matriz *novoM = (Matriz *)malloc(sizeof(Matriz));
    novoM->linha = linha;
    novoM->coluna = coluna;
    novoM->valor = (int **)malloc(coluna * sizeof(int *));
    for (int i = 0; i < linha; i++)
    {
        novoM->valor[i] = (int *)malloc(coluna * sizeof(int));
    }

    for (int i = 0; i < linha; i++)
    {
        for (int j = 0; j < coluna; j++)
        {
            novoM->valor[i][j] = valor[i][j];
        }
    }

    return novoM;
}

void menu()
{
    printf("//////////// CALCULADORA DE MATRIZES ////////////\n");
    printf("------------------OPÇÕES-------------------\n");
    printf("0 - Encerrar\n");
    printf("1 - Criar Matriz\n");
    printf("2 - Listar Matrizes\n");
    printf("3 - Eliminar única Matriz\n");
    printf("4 - Eliminar todas as Matrizes\n");
    printf("------------------OPERAÇÕES-----------------\n");
    printf("[OBS: A propriedade das operações de soma e subtração entre matrizes devem ser de ordens iguais (IEZZI, 2013, p. 50-54)]\n\n");
    printf("5 - Somar Matrizes\n");
    printf("6 - Subtrair Matrizes\n\n");
    printf("[OBS: A propriedade da multiplicação de matrizes tem que ser de matrizes com Coluna(A) igual a Linha(B) (IEZZI, 2013, p. 57)]\n\n");
    printf("7 - Multiplicar Matrizes\n");
    printf("8 - Multiplicar número por Matriz (IEZZI, 2013, p. 54-57)\n");
    printf("-----------------DETERMINANTES---------------\n");
    printf("9 - Achar a determinante por Sarrus\n");
    printf("    Ex: Ordem 3x3 inferior - Matriz quadradas (IEZZI, 2013, p. 82-84)\n");
    printf("10 - Achar a determinante por Laplace\n");
    printf("    Ex: Ordem 4x4 superior - Matriz quadradas (IEZZI, 2013, p. 91-92)\n");
    printf("---------------------------------------------\n");
}

int criarMatriz(Matriz **matrizes, int max_matrizes)
{
    qt_matriz = 0;
    int cont = 0;
    printf("Deseja criar quantas matrizes?\n");
    scanf(" %d", &qt_matriz);

    for (int i = 0; i < max_matrizes; i++)
    {
        if (matrizes[i] == NULL)
        {
            if (cont < qt_matriz)
            {
                // matriz depende de linha e coluna
                int linha = 0;
                int coluna = 0;

                printf("[Digite a ordem da matriz]\n");
                printf("Linha: \n");
                scanf(" %d", &linha);
                printf("Coluna: \n");
                scanf(" %d", &coluna);
                int elementos = linha * coluna;

                if (elementos != 0)
                {

                    printf("Ordem %dx%d, é possível inserir %d elementos\n", linha, coluna, elementos);
                    int **valor = (int **)malloc((linha * coluna) * sizeof(int *));

                    for (int g = 0; g < linha; g++)
                    {
                        valor[g] = malloc((linha * coluna) * sizeof(int));
                        for (int j = 0; j < coluna; j++)
                        {
                            printf("Insira o valor posição %dx%d:\n", g+1, j+1);
                            scanf(" %d", &valor[g][j]);
                        }
                    }

                    matrizes[i] = novaMatriz(linha, coluna, valor);

                    // liberar memoria do ponteiro matriz local
                    for (int g = 0; g < coluna; g++)
                    {
                        free(valor[g]);
                    }
                    free(valor);
                    cont++;
                }
                else if (elementos == 0)
                {
                    printf("Não é possível criar uma Matriz com %d elementos!!!\n", elementos);
                }
            }
            else
            {
                return 0;
            }
        }
    }
}

void listarMatrizes(Matriz **matrizes, int max_matrizes)
{
    int matriz_livre = 0;
    for (int i = 0; i < max_matrizes; i++)
    {
        if (matrizes[i] != NULL)
        {
            printf("Matriz %d (%dx%d):\n", i, matrizes[i]->linha, matrizes[i]->coluna);
            for (int g = 0; g < matrizes[i]->linha; g++)
            {
                for (int j = 0; j < matrizes[i]->coluna; j++)
                {
                    printf("%d ", matrizes[i]->valor[g][j]);
                }
                printf("\n");
            }
        }
        else if (matrizes[i] == NULL)
        {
            matriz_livre++;
        }
    }

    if (matriz_livre == max_matrizes)
    {
        printf("Nenhuma Matriz encontrada!!!!\n");
        return;
    }
}

void freeMatriz(Matriz *matrizes)
{
    if (matrizes == NULL)
    {
        return;
    }

    for (int i = 0; i < matrizes->coluna; i++)
    {
        free(matrizes->valor[i]);
    }
    free(matrizes->valor);

    // free(matrizes->coluna);
    // free(matrizes->linha);
    free(matrizes);
}

// Remove uma única Matriz
void removerMatriz(Matriz **matrizes)
{
    int posicao;
    printf("Insira a posição que deseja remover:\n");
    scanf("%d", &posicao);
    if (matrizes[posicao] == NULL)
    {
        printf("Não há posição a ser removida!\n");
    }
    else
    {
        freeMatriz(matrizes[posicao]);
        matrizes[posicao] = NULL;
    }
}

// Remove toda as Matrizes
void removerMatrizes(Matriz **matrizes, int max_matrizes)
{
    for (int i = 0; i <= max_matrizes; i++)
    {
        if (matrizes[i] != NULL)
        {
            printf("Removendo Matriz %d\n", i);
            freeMatriz(matrizes[i]);
            matrizes[i] = NULL;
        }
    }
}

void multiplicarMatrizes(Matriz **matrizes, int max_matrizes)
{
    // contar as matrizes para informar se deve criar mais uma
    int cont_matriz = 0;
    int qtd_matriz = 0;
    for (int i = 0; i < max_matrizes; i++)
    {
        if (matrizes[i] != NULL)
        {
            cont_matriz++;
        }
    }

    // decisão de acordo com a quantidade de matrizes exitentes
    while (cont_matriz >= 0)
    {
        if (cont_matriz <= 1)
        {
            printf("Você deve criar mais matrizes!!!\n");
            qt_matriz = 0;
            criarMatriz(matrizes, max_matrizes);
            cont_matriz += qt_matriz;
        }
        else if (cont_matriz > 1)
        {
            break;
        }
    }

    // selecionando as matrizes para a operação
    int endMatA = 0;
    int endMatB = 0;
    listarMatrizes(matrizes, max_matrizes);
    printf("Selecione 1º Matriz para multiplicar:\n");
    scanf("%d", &endMatA);
    printf("Selecione 2º Matriz para multiplicar:\n");
    scanf("%d", &endMatB);

    // operação
    // verificar se a quantidade de linha da matriz 1 é igual a da coluna matriz 2
    if (matrizes[endMatA] != NULL && matrizes[endMatB] != NULL)
    {
        int linhaA = matrizes[endMatA]->linha;
        int linhaB = matrizes[endMatB]->linha;
        int colunaA = matrizes[endMatA]->coluna;
        int colunaB = matrizes[endMatB]->coluna;
        int aux;

        // serve para obedecer a regra de multiplicação de matrizes
        if ((colunaA == colunaB) && (linhaA == linhaB))
        {
            // Aloca dinamicamente a matriz resultante
            int **matrizResult = (int **)malloc(linhaA * sizeof(int *));
            for (int l = 0; l < linhaA; l++)
            {
                matrizResult[l] = (int *)malloc(colunaB * sizeof(int));
            }
            // multiplicar matrizes
            for (int g = 0; g < linhaA; g++)
            {
                for (int j = 0; j < colunaB; j++)
                {
                    int aux = 0;
                    for (int x = 0; x < colunaA; x++)
                    {
                        // pega o valor da Matriz A e B
                        int valorA = matrizes[endMatA]->valor[g][x];
                        int valorB = matrizes[endMatB]->valor[x][j];
                        // adiciona ao auxiliar para alocar na matriz resultante após o fim do loops
                        aux += valorA * valorB;
                    }

                    matrizResult[g][j] = aux;
                }
            }

            printf("Matriz Resultante da multiplicação:\n");
            for (int g = 0; g < linhaA; g++)
            {
                for (int j = 0; j < colunaB; j++)
                {
                    printf("%d ", matrizResult[g][j]);
                }
                printf("\n");
            }

            // Liberar a memória alocada para a matriz resultante
            for (int l = 0; l < linhaA; l++)
            {
                free(matrizResult[l]);
                matrizResult[l] = NULL;
            }

            free(matrizResult);
            matrizResult = NULL;

            while (getchar() != '\n')
                ;
            printf("Presssione enter para Sair:\n");
            getchar();
        }
        else
        {
            printf("Não é possível multiplicar matrizes com a Linha da 1ª Matriz e linha da 2ª Matriz diferentes (IEZZI, 2013, p. 57)!!!\n");
            while (getchar() != '\n')
                ;
            printf("Presssione enter para Sair:\n");
            getchar();
            return;
        }
    }
}

void multiplicarNumeroMatriz(Matriz **matrizes, int max_matrizes)
{
    // contar as matrizes para informar se deve criar mais uma
    int cont_matriz = 0;
    int qtd_matriz = 0;

    for (int i = 0; i < max_matrizes; i++)
    {
        if (matrizes[i] != NULL)
        {
            cont_matriz++;
        }
    }

    // decisão de acordo com a quantidade de matrizes exitentes
    while (cont_matriz >= 0)
    {
        if (cont_matriz < 1)
        {
            printf("Você deve criar mais matrizes!!!\n");
            qt_matriz = 0;
            criarMatriz(matrizes, max_matrizes);
            cont_matriz += qt_matriz;
        }
        else if (cont_matriz = 1)
        {
            break;
        }
    }

    // selecionando as matrizes para a operação
    int endMatA = 0;

    int NumMulti;
    listarMatrizes(matrizes, max_matrizes);
    printf("Selecione 1º Matriz para multiplicar:\n");
    scanf("%d", &endMatA);
    printf("Digite o número para multiplicar com a Matriz:\n");
    scanf("%d", &NumMulti);

    // operação
    // Soma de matrizes

    int linhaA = matrizes[endMatA]->linha;
    int colunaA = matrizes[endMatA]->coluna;

    // Aloca dinamicamente a matriz resultante
    int **matrizResult = (int **)malloc(linhaA * sizeof(int *));
    for (int l = 0; l < linhaA; l++)
    {
        matrizResult[l] = (int *)malloc(colunaA * sizeof(int));
    }
    // multiplicação do numero por matriz
    for (int g = 0; g < linhaA; g++)
    {
        for (int j = 0; j < linhaA; j++)
        {
            // pega o valor da Matriz A e NumMulti
            int valorA = matrizes[endMatA]->valor[g][j];

            matrizResult[g][j] = valorA * NumMulti;
        }
    }

    printf("Matriz Resultante da Multiplicação:\n");
    for (int g = 0; g < linhaA; g++)
    {
        for (int j = 0; j < linhaA; j++)
        {
            printf("%d ", matrizResult[g][j]);
        }
        printf("\n");
    }

    // Liberar a memória alocada para a matriz resultante
    for (int l = 0; l < linhaA; l++)
    {
        free(matrizResult[l]);
        matrizResult[l] = NULL;
    }

    free(matrizResult);
    matrizResult = NULL;

    while (getchar() != '\n')
        ;
    printf("Presssione enter para Sair:\n");
    getchar();
}

void somarMatrizes(Matriz **matrizes, int max_matrizes)
{
    // contar as matrizes para informar se deve criar mais uma
    int cont_matriz = 0;
    int qtd_matriz = 0;

    for (int i = 0; i < max_matrizes; i++)
    {
        if (matrizes[i] != NULL)
        {
            cont_matriz++;
        }
    }

    // decisão de acordo com a quantidade de matrizes exitentes
    while (cont_matriz >= 0)
    {
        if (cont_matriz <= 1)
        {
            printf("Você deve criar mais matrizes!!!\n");
            qt_matriz = 0;
            criarMatriz(matrizes, max_matrizes);
            cont_matriz += qt_matriz;
        }
        else if (cont_matriz > 1)
        {
            break;
        }
    }

    // selecionando as matrizes para a operação
    int endMatA = 0;
    int endMatB = 0;
    listarMatrizes(matrizes, max_matrizes);
    printf("Selecione 1º Matriz para somar:\n");
    scanf("%d", &endMatA);
    printf("Selecione 2º Matriz para somar:\n");
    scanf("%d", &endMatB);

    // operação
    // Soma de matrizes
    if (matrizes[endMatA] != NULL && matrizes[endMatB] != NULL)
    {
        int linhaA = matrizes[endMatA]->linha;
        int linhaB = matrizes[endMatB]->linha;
        int colunaA = matrizes[endMatA]->coluna;
        int colunaB = matrizes[endMatB]->coluna;
        int aux;

        // serve para obedecer a regra de soma de matrizes
        if ((colunaA == colunaB) && (linhaA == linhaB))
        {
            // Aloca dinamicamente a matriz resultante
            int **matrizResult = (int **)malloc(linhaA * sizeof(int *));
            for (int l = 0; l < linhaA; l++)
            {
                matrizResult[l] = (int *)malloc(colunaB * sizeof(int));
            }
            // soma matrizes
            for (int g = 0; g < linhaA; g++)
            {
                for (int j = 0; j < linhaA; j++)
                {
                    // pega o valor da Matriz A e B
                    int valorA = matrizes[endMatA]->valor[g][j];
                    int valorB = matrizes[endMatB]->valor[g][j];

                    matrizResult[g][j] = valorA + valorB;
                }
            }

            printf("Matriz Resultante da soma:\n");
            for (int g = 0; g < linhaA; g++)
            {
                for (int j = 0; j < linhaA; j++)
                {
                    printf("%d ", matrizResult[g][j]);
                }
                printf("\n");
            }

            // Liberar a memória alocada para a matriz resultante
            for (int l = 0; l < linhaA; l++)
            {
                free(matrizResult[l]);
                matrizResult[l] = NULL;
            }

            free(matrizResult);
            matrizResult = NULL;

            while (getchar() != '\n')
                ;
            printf("Presssione enter para Sair:\n");
            getchar();
        }
        else
        {
            printf("Não é possível somar matrizes de ordens diferentes (IEZZI, 2013, p. 50-54)!!!\n");
            while (getchar() != '\n')
                ;
            printf("Presssione enter para Sair:\n");
            getchar();
            return;
        }
    }
}

void subtracaoMatrizes(Matriz **matrizes, int max_matrizes)
{
    // contar as matrizes para informar se deve criar mais uma
    int cont_matriz = 0;
    int qtd_matriz = 0;
    for (int i = 0; i < max_matrizes; i++)
    {
        if (matrizes[i] != NULL)
        {
            cont_matriz++;
        }
    }

    // decisão de acordo com a quantidade de matrizes exitentes
    while (cont_matriz >= 0)
    {
        if (cont_matriz <= 1)
        {
            printf("Você deve criar mais matrizes!!!\n");
            qt_matriz = 0;
            criarMatriz(matrizes, max_matrizes);
            cont_matriz += qt_matriz;
        }
        else if (cont_matriz > 1)
        {
            break;
        }
    }

    // selecionando as matrizes para a operação
    int endMatA = 0;
    int endMatB = 0;
    listarMatrizes(matrizes, max_matrizes);
    printf("Selecione 1º Matriz para subtração:\n");
    scanf("%d", &endMatA);
    printf("Selecione 2º Matriz para subtração:\n");
    scanf("%d", &endMatB);

    // operação
    // Subtracao de matrizes
    if (matrizes[endMatA] != NULL && matrizes[endMatB] != NULL)
    {
        int linhaA = matrizes[endMatA]->linha;
        int linhaB = matrizes[endMatB]->linha;
        int colunaA = matrizes[endMatA]->coluna;
        int colunaB = matrizes[endMatB]->coluna;
        int aux;

        // serve para obedecer a regra de subracao de matrizes
        if ((colunaA == colunaB) && (linhaA == linhaB))
        {
            // Aloca dinamicamente a matriz resultante
            int **matrizResult = (int **)malloc(linhaA * sizeof(int *));
            for (int l = 0; l < linhaA; l++)
            {
                matrizResult[l] = (int *)malloc(colunaB * sizeof(int));
            }
            // subtracao matrizes
            for (int g = 0; g < linhaA; g++)
            {
                for (int j = 0; j < linhaA; j++)
                {
                    // pega o valor da Matriz A e B
                    int valorA = matrizes[endMatA]->valor[g][j];
                    int valorB = matrizes[endMatB]->valor[g][j];

                    matrizResult[g][j] = valorA - valorB;
                }
            }

            printf("Matriz Resultante da subtracao:\n");
            for (int g = 0; g < linhaA; g++)
            {
                for (int j = 0; j < linhaA; j++)
                {
                    printf("%d ", matrizResult[g][j]);
                }
                printf("\n");
            }

            // Liberar a memória alocada para a matriz resultante
            for (int l = 0; l < linhaA; l++)
            {
                free(matrizResult[l]);
                matrizResult[l] = NULL;
            }

            free(matrizResult);
            matrizResult = NULL;

            while (getchar() != '\n')
                ;
            printf("Presssione enter para Sair:\n");
            getchar();
        }
        else
        {
            printf("Não é possível subtrair matrizes de ordens diferentes (IEZZI, 2013, p. 50-54)!!!\n");
            while (getchar() != '\n')
                ;
            printf("Presssione enter para Sair:\n");
            getchar();
            return;
        }
    }
}

void detsarrusMatrizes(Matriz **matrizes, int max_matrizes)
{
    // contar as matrizes para informar se deve criar mais uma
    int cont_matriz = 0;
    int qtd_matriz = 0;
    for (int i = 0; i < max_matrizes; i++)
    {
        if (matrizes[i] != NULL)
        {
            cont_matriz++;
        }
    }

    // decisão de acordo com a quantidade de matrizes exitentes
    while (cont_matriz <= 0)
    {
        printf("Você deve criar mais matrizes!!!\n");
        qt_matriz = 0;
        criarMatriz(matrizes, max_matrizes);
        cont_matriz += qt_matriz;
    }

    // selecionando as matrizes para a operação
    int endMatA = 0;
    int endMatB = 0;
    listarMatrizes(matrizes, max_matrizes);
    printf("Selecione a Matriz para encontrar o determinante:\n");
    scanf("%d", &endMatA);

    // operação
    // Teorema de Sarrus de matrizes
    if (matrizes[endMatA] != NULL && matrizes[endMatB] != NULL)
    {
        int linhaA = matrizes[endMatA]->linha;
        int colunaA = matrizes[endMatA]->coluna;

        // serve para obedecer a regra de encontrar a determinante por sarrus
        if ((linhaA == colunaA) && linhaA <= 3)
        {
            int p1, p2, p3, n1, n2, n3, det;
            // Determinante Sarrus 3x3
            if ((linhaA == 3) && (colunaA == 3))
            {
                p1 = matrizes[endMatA]->valor[0][0] * matrizes[endMatA]->valor[1][1] * matrizes[endMatA]->valor[2][2];
                p2 = matrizes[endMatA]->valor[1][0] * matrizes[endMatA]->valor[2][1] * matrizes[endMatA]->valor[0][2];
                p3 = matrizes[endMatA]->valor[2][0] * matrizes[endMatA]->valor[0][1] * matrizes[endMatA]->valor[1][2];
                n1 = matrizes[endMatA]->valor[2][0] * matrizes[endMatA]->valor[1][1] * matrizes[endMatA]->valor[0][2];
                n2 = matrizes[endMatA]->valor[0][0] * matrizes[endMatA]->valor[2][1] * matrizes[endMatA]->valor[1][2];
                n3 = matrizes[endMatA]->valor[1][0] * matrizes[endMatA]->valor[0][1] * matrizes[endMatA]->valor[2][2];
                det = p1 + p2 + p3 - n1 - n2 - n3;
            }
            // Determinante Sarrus 2x2
            else if ((linhaA == 2) && (colunaA == 2))
            {
                p1 = matrizes[endMatA]->valor[0][0] * matrizes[endMatA]->valor[1][1];
                n1 = matrizes[endMatA]->valor[0][1] * matrizes[endMatA]->valor[1][0];
                det = p1 - n1;
            } // Determinante Sarrus 1x1
            else if ((linhaA == 1) && (colunaA == 1))
            {
                p1 = matrizes[endMatA]->valor[0][0];
                det = p1;
                printf("%d ", matrizes[endMatA]->valor[0][0]);
            }

            printf("Matriz %d:\n", endMatA);
            for (int g = 0; g < matrizes[endMatA]->linha; g++)
            {
                for (int j = 0; j < matrizes[endMatA]->coluna; j++)
                {
                    printf("%d ", matrizes[endMatA]->valor[g][j]);
                }
                printf("\n");
            }
            printf("Ordem %dx%d\n", matrizes[endMatA]->linha, matrizes[endMatA]->coluna);
            printf("Determinante Sarrus: %d\n", det);

            while (getchar() != '\n')
                ;
            printf("Presssione enter para Sair:\n");
            getchar();
        }
        else
        {
            printf("Não é possível achar o determinante pelo teorema de Sarrus(IEZZI, 2013, p. 82-84)!!!\n");
            while (getchar() != '\n')
                ;
            printf("Presssione enter para Sair:\n");
            getchar();
            return;
        }
    }
}

void detlaplaceMatrizes(Matriz **matrizes, int max_matrizes)
{
    // contar as matrizes para informar se deve criar mais uma
    int cont_matriz = 0;
    int qtd_matriz = 0;
    for (int i = 0; i < max_matrizes; i++)
    {
        if (matrizes[i] != NULL)
        {
            cont_matriz++;
        }
    }

    // decisão de acordo com a quantidade de matrizes exitentes
    while (cont_matriz <= 0)
    {
        printf("Você deve criar mais matrizes!!!\n");
        qt_matriz = 0;
        criarMatriz(matrizes, max_matrizes);
        cont_matriz += qt_matriz;
    }

    // selecionando as matrizes para a operação
    int endMatA = 0;
    int endMatB = 0;
    listarMatrizes(matrizes, max_matrizes);
    printf("Selecione a Matriz para encontrar o determinante:\n");
    scanf("%d", &endMatA);

    // operação
    // Teorema de Laplace de matrizes
    if (matrizes[endMatA] != NULL && matrizes[endMatB] != NULL)
    {
        int linhaA = matrizes[endMatA]->linha;
        int colunaA = matrizes[endMatA]->coluna;

        // serve para obedecer a regra de encontrar a determinante por Laplace
        if ((linhaA == colunaA) && linhaA >= 4)
        {
            int det = 0;

            // Calcular determinante usando expansão de Laplace

            for (int col = 0; col < linhaA; col++)
            {
                // Alocar submatriz dinamicamente
                int **submatriz = (int **)malloc((linhaA - 1) * sizeof(int *));
                for (int i = 0; i < linhaA - 1; i++)
                {
                    submatriz[i] = (int *)malloc((linhaA - 1) * sizeof(int));
                }

                int subi = 0;
                for (int i = 1; i < linhaA; i++)
                {
                    int subj = 0;
                    for (int j = 0; j < linhaA; j++)
                    {
                        if (j == col)
                            continue;
                        submatriz[subi][subj] = matrizes[endMatA]->valor[i][j];
                        subj++;
                    }
                    subi++;
                }

                // Calcular determinante da submatriz
                int subdet = 0;
                if (linhaA - 1 == 1)
                {
                    subdet = submatriz[0][0];
                }
                else if (linhaA - 1 == 2)
                {
                    subdet = submatriz[0][0] * submatriz[1][1] - submatriz[0][1] * submatriz[1][0];
                }
                else
                {
                    // Expandir Laplace para a submatriz
                    for (int subcol = 0; subcol < linhaA - 1; subcol++)
                    {
                        int **subsubmatriz = (int **)malloc((linhaA - 2) * sizeof(int *));
                        for (int subi2 = 0; subi2 < linhaA - 2; subi2++)
                        {
                            subsubmatriz[subi2] = (int *)malloc((linhaA - 2) * sizeof(int));
                        }

                        int subi2 = 0;
                        for (int subi1 = 1; subi1 < linhaA - 1; subi1++)
                        {
                            int subj2 = 0;
                            for (int subj1 = 0; subj1 < linhaA - 1; subj1++)
                            {
                                if (subj1 == subcol)
                                    continue;
                                subsubmatriz[subi2][subj2] = submatriz[subi1][subj1];
                                subj2++;
                            }
                            subi2++;
                        }

                        int subsubdet = 0;
                        if (linhaA - 2 == 1)
                        {
                            subsubdet = subsubmatriz[0][0];
                        }
                        else if (linhaA - 2 == 2)
                        {
                            subsubdet = subsubmatriz[0][0] * subsubmatriz[1][1] - subsubmatriz[0][1] * subsubmatriz[1][0];
                        }
                        // Adicionar mais casos recursivos para tamanhos maiores, se necessário

                        subdet += (subcol % 2 == 0 ? 1 : -1) * submatriz[0][subcol] * subsubdet;

                        for (int subi2 = 0; subi2 < linhaA - 2; subi2++)
                        {
                            free(subsubmatriz[subi2]);
                        }
                        free(subsubmatriz);
                        while (getchar() != '\n')
                            ;
                        printf("Presssione enter para Sair:\n");
                        getchar();
                    }
                }

                det += (col % 2 == 0 ? 1 : -1) * matrizes[endMatA]->valor[0][col] * subdet;

                for (int i = 0; i < linhaA - 1; i++)
                {
                    free(submatriz[i]);
                }
                free(submatriz);
            }

            // Imprimir determinante
            printf("Matriz %d:\n", endMatA);
            for (int g = 0; g < matrizes[endMatA]->linha; g++)
            {
                for (int j = 0; j < matrizes[endMatA]->coluna; j++)
                {
                    printf("%d ", matrizes[endMatA]->valor[g][j]);
                }
                printf("\n");
            }
            printf("Ordem %dx%d\n", matrizes[endMatA]->linha, matrizes[endMatA]->coluna);
            printf("Determinante Laplace: %d\n", det);
            int res;
            printf("Pressione Enter para Sair\n");
            scanf(" %d", &res);
        }
        else
        {
            printf("Não é possível achar o determinante pela regra de Laplace(IEZZI, 2013, p. 91-92)!!!\n");
            while (getchar() != '\n')
                ;
            printf("Presssione enter para Sair:\n");
            getchar();
            return;
        }
    }
}

void main()
{
    int resposta = 1;
    int max_matrizes = 100;
    Matriz **matrizes = (Matriz **)malloc(max_matrizes * sizeof(Matriz *));

    while (resposta != 0)
    {
        menu();
        printf("Escolha a opção:\n");
        scanf(" %d", &resposta);

        if (resposta == 1)
        {
            criarMatriz(matrizes, max_matrizes);
        }
        else if (resposta == 2)
        {
            listarMatrizes(matrizes, max_matrizes);
        }
        else if (resposta == 3)
        {
            removerMatriz(matrizes);
        }
        else if (resposta == 4)
        {
            removerMatrizes(matrizes, max_matrizes);
        }
        else if (resposta == 5)
        {
            somarMatrizes(matrizes, max_matrizes);
        }
        else if (resposta == 6)
        {
            subtracaoMatrizes(matrizes, max_matrizes);
        }
        else if (resposta == 7)
        {
            multiplicarMatrizes(matrizes, max_matrizes);
        }
        else if (resposta == 8)
        {
            multiplicarNumeroMatriz(matrizes, max_matrizes);
        }
        else if (resposta == 9)
        {
            detsarrusMatrizes(matrizes, max_matrizes);
        }
        else if (resposta == 10)
        {
            detlaplaceMatrizes(matrizes, max_matrizes);
        }
    }
}