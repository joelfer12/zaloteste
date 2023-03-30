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
void printList(LIST list); // esta solu��o n�o � �gen�rica�

typedef struct _ALUNO
{
    char nome[30];
    int idade;
} ALUNO;

/**************************************************************
* Fun��o initList(): Inicializa a lista
*
* Par�metros: pL - lista (passado por ref)
* Sa�da: void
***************************************************************/
void initList(LIST* pL)
{
    *pL = NULL;
}
/**************************************************************
* Fun��o emptyList(): verifica se a lista est� vazia
*
* Par�metros: L - lista
* Sa�da: TRUE se a lista estiver vazia, FALSE caso contr�rio
***************************************************************/
BOOLEAN emptyList(LIST L)
{
    return (L == NULL) ? TRUE : FALSE;    //isto signifca, se L == NULL mostrar True sen�o mostrar False
}

/**************************************************************
* Fun��o createNewNode(): cria um n� da lista
*
* Par�metros: pData - apontador gen�rico para os dados a inserir no n� criado
* Sa�da: apontador para o n� criado ou NULL em caso de erro
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
* Fun��o insertStartList(): insere um elemento (n�) no in�cio da lista
*
* Par�metros: pL � lista (passado por ref)
* pData - apontador gen�rico para os dados a inserir no n� criado
* Sa�da: OK se o n� foi inserido na LISTA e ERROR caso contr�rio
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
* Fun��o insertEndList(): insere um elemento (n�) no final da lista
*
* Par�metros: pL � lista (passado por ref)
* pData - apontador gen�rico para os dados a inserir no n� criado
* Sa�da: OK se o n� foi inserido na lista e ERROR caso contr�rio
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
* Fun��o listSize(): calcula o n�mero de elementos da lista
*
* Par�metros: L � lista
* Sa�da: n�mero de elementos da lista
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
* Fun��o printList(): apresenta no ecr� os elementos da lista
*
* Par�metros: L � lista
* Sa�da: void
*
* Esta fun��o n�o � gen�rica: s� funciona para elemento de tipo ALUNO
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

    //Nunca fazer o seguinte segmento de c�digo. Porqu�?
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