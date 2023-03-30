#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#define EMPTY NULL
#define NO_LINK NULL

typedef enum _STATUS { ERROR = 0, OK = 1 } STATUS;
typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
typedef enum _LIST_LOCATION { LIST_START, LIST_END } LIST_LOCATION;

typedef struct _LIST_NODE
{
    void* pData;
    struct _LIST_NODE* next;
} LIST_NODE;

typedef LIST_NODE* LIST;
#define DATA(node) ((node)->pData)
#define NEXT(node) ((node)->next)

void initList(LIST* plist);
BOOLEAN emptyList(LIST list);
LIST_NODE* createNewNode(void* pdata);
STATUS insertStartList(LIST* plist, void* pdata);
STATUS insertEndList(LIST* plist, void* pdata);
int ListSize(LIST list);
void printList(LIST list); // esta solução não é “genérica”

typedef struct _ALUNO
{
    char nome[30];
    int idade;
} ALUNO;

/**************************************************************
* Função initList(): Inicializa a lista
*
* Parâmetros: pL - lista (passado por ref)
* Saída: void
***************************************************************/
void initList(LIST* pL)
{
    *pL = NULL;
}
/**************************************************************
* Função emptyList(): verifica se a lista está vazia
*
* Parâmetros: L - lista
* Saída: TRUE se a lista estiver vazia, FALSE caso contrário
***************************************************************/
BOOLEAN emptyList(LIST L)
{
    return (L == NULL) ? TRUE : FALSE;    //isto signifca, se L == NULL mostrar True senão mostrar False
}

/**************************************************************
* Função createNewNode(): cria um nó da lista
*
* Parâmetros: pData - apontador genérico para os dados a inserir no nó criado
* Saída: apontador para o nó criado ou NULL em caso de erro
***************************************************************/
LIST_NODE* createNewNode(void* pData)
{
    LIST_NODE* pNew;
    if ((pNew = (LIST_NODE*)malloc(sizeof(LIST_NODE))) != NULL)
    {
        DATA(pNew) = pData;
        NEXT(pNew) = NULL;
    }
    return pNew;
}



/**************************************************************
* Função insertStartList(): insere um elemento (nó) no início da lista
*
* Parâmetros: pL – lista (passado por ref)
* pData - apontador genérico para os dados a inserir no nó criado
* Saída: OK se o nó foi inserido na LISTA e ERROR caso contrário
***************************************************************/

STATUS insertStartList(LIST* pL, void* pData)
{
    LIST_NODE* pNew;
    if ((pNew = createNewNode(pData)) == EMPTY)
        return ERROR;
    NEXT(pNew) = *pL;
    *pL = pNew;
    return OK;
}

/**************************************************************
* Função insertEndList(): insere um elemento (nó) no final da lista
*
* Parâmetros: pL – lista (passado por ref)
* pData - apontador genérico para os dados a inserir no nó criado
* Saída: OK se o nó foi inserido na lista e ERROR caso contrário
***************************************************************/

STATUS insertEndList(LIST* pL, void* pData)
{
    LIST_NODE* pNew, * pTemp;
    if ((pNew = createNewNode(pData)) == EMPTY)
        return ERROR;
    if (*pL == NULL)
        *pL = pNew;
    else
    {
        pTemp = *pL;
        while (NEXT(pTemp) != NULL)
            pTemp = NEXT(pTemp);
        NEXT(pTemp) = pNew;
    }
    return OK;
}

/**************************************************************
* Função listSize(): calcula o número de elementos da lista
*
* Parâmetros: L – lista
* Saída: número de elementos da lista
***************************************************************/
int listSize(LIST L)
{
    LIST pTemp = L;
    int count = 0;
    while (pTemp != NULL)
    {
        count++;
        pTemp = NEXT(pTemp);
    }
    return count;
}

/**************************************************************
* Função printList(): apresenta no ecrã os elementos da lista
*
* Parâmetros: L – lista
* Saída: void
*
* Esta função não é genérica: só funciona para elemento de tipo ALUNO
***************************************************************/

void printList(LIST L)
{
    LIST pTemp = L;
    if (emptyList(pTemp) == TRUE)
    {
        printf("\nLista vazia.\n");
        return;
    }
    while (pTemp != NULL)
    {
        printf(" %s;%d ->", ((ALUNO*)DATA(pTemp))->nome, ((ALUNO*)DATA(pTemp))->idade);
        pTemp = NEXT(pTemp);
    }
    printf("NULL\n");
    return;
}

int main() {

    LIST L = NULL;
    ALUNO* pAluno;
    ALUNO al1, al2;
    char nomeAux[30];
    int idadeAux;

    strcpy(al1.nome, "Aluno 1");
    al1.idade = 11;

    strcpy(al2.nome, "Aluno 2");
    al2.idade = 22;

    if (insertStartList(&L, &al1) == ERROR)
    {
        printf("\nErro na alocacao de memoria\n");
        printf("\n<Prima qualquer tecla>\n");
        getch();
        exit(ERROR);
    }
    if (insertStartList(&L, &al2) == ERROR)
    {
        printf("\nErro na alocacao de memoria\n");
        printf("\n<Prima qualquer tecla>\n");
        getch();
        exit(ERROR);
    }
    printf("\n");
    printf("\nTamanho da lista = %d\n", listSize(L));

    pAluno = (ALUNO*)malloc(sizeof(ALUNO));
    printf("Introduza o nome do aluno: ");
    flushall();
    gets_s(pAluno->nome);
    printf("Introduza a idade do aluno: ");
    scanf("%d", &(pAluno->idade));

    if (insertEndList(&L, pAluno) == ERROR)
    {
        printf("\nErro na alocacao de memoria\n");
        printf("\n<Prima qualquer tecla>\n");
        getch();
        exit(ERROR);
    }
    printf("\n");
    printf("\nTamanho da lista = %d\n", listSize(L));
    printf("ALUNOS:\n");
    printList(L);
    printf("\n");

    strcpy(((ALUNO*)DATA(L))->nome, "Desconhecido 1");

    // strcpy(((ALUNO *)(L->data))->nome,"Desconhecido 1");
    ((ALUNO*)DATA(L))->idade = 111;

    // ((ALUNO *)(L->data))->idade = 111;
    ((ALUNO*)DATA(NEXT(L)))->idade = 222;

    // ((ALUNO *)(L->next->data))->idade = 222;
    ((ALUNO*)DATA(NEXT(NEXT(L))))->idade = 333;

    // ((ALUNO *)(L->next->next->data))->idade = 333;
    printf("\n");
    printf("\nTamanho da lista = %d\n", listSize(L));
    printf("ALUNOS:\n");
    printList(L);
    printf("\n");

    //Nunca fazer o seguinte segmento de código. Porquê?
    while (NEXT(L) != NULL)
        L = NEXT(L);
    strcpy(((ALUNO*)DATA(L))->nome, "Desconhecido 3");

    printf("\n");
    printf("\nTamanho da lista = %d\n", listSize(L));
    printf("ALUNOS:\n");
    printList(L);
    printf("\n");

    getch();
    return OK;

}