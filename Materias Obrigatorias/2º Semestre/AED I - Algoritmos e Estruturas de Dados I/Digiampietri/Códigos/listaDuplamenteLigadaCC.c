/******************************************************************************
     listaLigadaCabCirc.c
  Este programa gerencia listas lineares ligadas circulares (implementacao 
dinamica) com n� cabe�a no in�cio da lista.
  As listas gerenciadas podem ter um numero arbitrario de elementos.
  O no cabe�a acelera o algoritmo de busta sequencial por reduzir o numero
de comparacoes. Alem disso algumas operacoes ficam mais simples pois a lista
nunca esta "vazia"
******************************************************************************/
#include <stdio.h>
#define true 1
#define false 0

typedef int bool;
typedef int TIPOCHAVE;

typedef struct tempRegistro{
  TIPOCHAVE chave;
  struct tempRegistro *prox;
  struct tempRegistro *ant;
// outros campos...
} REGISTRO;

typedef REGISTRO* PONT;

typedef struct {
  PONT cabeca;
} LISTA;

/* Inicializa��o da lista ligada (a lista jah esta criada e eh apontada 
pelo endereco em l) */
void inicializarLista(LISTA *l){
  l->cabeca = (PONT) malloc(sizeof(REGISTRO));
  l->cabeca->prox = l->cabeca;  // faz com que a lista seja circular
  l->cabeca->ant = l->cabeca;
} /* inicializarLista */

/* Exibi��o da lista sequencial */
void exibirLista(LISTA *l){
  PONT end = l->cabeca->prox;
  printf("Lista: \" ");
  while (end != l->cabeca){
    printf("%d ", end->chave); // soh lembrando TIPOCHAVE = int
    end = end->prox;
  }
  printf("\"\n");
} /* exibirLista */ 

/* Retornar o tamanho da lista (numero de elementos "validos") */
int tamanho(LISTA *l) {
  PONT end = l->cabeca->prox;
  int tam = 0;
 while (end != l->cabeca){
    tam++;
    end = end->prox;
  }
  return tam;
} /* tamanho */

/* Retornar o tamanho em bytes da lista. Neste caso, isto depende do numero
   de elementos que estao sendo usados.   */
int tamanhoEmBytes(LISTA *l) {
  return((tamanho(l)+1)*sizeof(REGISTRO))+sizeof(LISTA); // sizeof(LISTA) = sizeof(PONT) pois a "LISTA" eh um ponteiro para o 1o elemento
} /* tamanhoEmBytes */

/* Busca sequencial (lista ordenada ou nao) */
PONT buscaSeq(TIPOCHAVE ch, LISTA *l){
  PONT pos = l->cabeca->prox;
  l->cabeca->chave = ch;
  while (pos->chave != ch) pos = pos->prox;
  if (pos != l->cabeca) return pos;
  return NULL;
} /* buscaSeq */

/* Busca sequencial - funcao de exclusao (retorna no endere�o *ant o indice do
   elemento anterior ao elemento que est� sendo buscado [ant recebe o elemento
   anterior independente do elemento buscado ser ou n�o encontrado]) 
   O n� cabeca pode ser o anterior.   
*/
PONT buscaSeqExc(TIPOCHAVE ch, LISTA *l, PONT *ant){
  *ant = l->cabeca;
  PONT pos = l->cabeca->prox;
  while ((pos != l->cabeca) && (pos->chave<ch)){
    *ant = pos;
    pos = pos->prox;
  }
  if ((pos != l->cabeca) && (pos->chave == ch)) return pos;
  return NULL;
} /* buscaSeqExc */

/* Exclus�o do elemento de chave indicada */
bool excluirElemLista(TIPOCHAVE ch, LISTA *l){
  PONT anterior, i;
  i = buscaSeqExc(ch, l, &anterior);
  if (i == NULL) return false;  // elemento a ser excluido nao existe
  anterior->prox = i->prox;
  i->prox->ant = anterior;
  free(i);
  return true;
} /* excluirElemListaEnc */

/* Destrui��o da lista sequencial 
   libera a memoria de todos os elementos da lista*/
void destruirLista(LISTA *l) {
  PONT end = l->cabeca->prox;
  while (end != l->cabeca){
    PONT apagar = end;
    end = end->prox;
    free(apagar);
  }
  l->cabeca->prox = l->cabeca;
  l->cabeca->ant = l->cabeca;
} /* destruirLista */


/* Inser��o em lista ordenada sem duplica��o */
bool inserirElemListaOrd(REGISTRO reg, LISTA *l) {
  TIPOCHAVE ch = reg.chave;
  PONT anterior, i;
  i = buscaSeqExc(ch, l, &anterior);
  if (i != NULL)  return false;
  i = (PONT) malloc(sizeof(REGISTRO));
  *i = reg;
  i->ant = anterior;
  i->prox = anterior->prox;
  anterior->prox = i;
  i->prox->ant = i;
  return true;
} /* inserirElemListaOrd */

/* retornarPrimeiro - retorna o endereco do primeiro elemento da lista e (caso
   a lista nao esteja vazia) retorna a chave desse elemento na memoria 
   apontada pelo ponteiro ch */
PONT retornarPrimeiro(LISTA *l, TIPOCHAVE *ch){
  if (l->cabeca->prox != l->cabeca) *ch = l->cabeca->prox->chave;
  return l->cabeca->prox;
} /* retornarPrimeiro */

/* retornarUltimo - retorna o endereco do ultimo elemento da lista e (caso
   a lista nao esteja vazia) retorna a chave desse elemento na memoria 
   apontada pelo ponteiro ch */
PONT retornarUltimo(LISTA *l, TIPOCHAVE *ch){
  PONT ultimo = l->cabeca->ant;
  if (ultimo == l->cabeca) return NULL;
  *ch = ultimo->chave;
  return ultimo;
} /* retornarUltimo */
