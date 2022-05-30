#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int MAX(int a, int b) {
    return a > b ? a : b;
}

typedef struct noBst {
    int chave;
    struct noBst * esq;
    struct noBst * dir;
} BST;

BST * bstNovoNo(int chave) {
    BST * no = malloc(sizeof(struct noBst));
    no->chave = chave;
    no->esq = NULL;
    no->dir = NULL;
    return no;
}

BST * bstInsert(BST * raiz, int chave) {
    if (raiz == NULL) {
        return bstNovoNo(chave);
    }

    if (chave > raiz->chave) {
        raiz->dir = bstInsert(raiz->dir, chave);
    }
    else {
        raiz->esq = bstInsert(raiz->esq, chave);
    }

    return raiz;
}

int bstCalculaAltura(BST * raiz) {
  if (raiz == NULL)
    return 0;
  
  int alturaEsq = bstCalculaAltura(raiz->esq);
  int alturaDir = bstCalculaAltura(raiz->dir);
  return MAX(alturaEsq, alturaDir) + 1;
}

void bstFree(BST * raiz) {
  if (raiz == NULL) return;

  if (raiz->esq != NULL)
    bstFree(raiz->esq);
  if (raiz->dir != NULL)
    bstFree(raiz->dir);
  
  free(raiz);
}


typedef struct noAvl {
    int chave;
    int altura;
    struct noAvl * esq;
    struct noAvl * dir;
} AVL;

AVL * avlNovoNo(int chave) {
    AVL * no = malloc(sizeof(struct noAvl));
    no->chave = chave;
    no->altura = 1; 
    no->esq = NULL;
    no->dir = NULL;
    return no;
}

int avlGetAltura(AVL * raiz) {
  if (raiz == NULL) return 0;
  return raiz->altura;
}

int avlCalculaAltura(AVL * raiz) {
  if (raiz == NULL)
    return 0;

  int alturaEsq = avlCalculaAltura(raiz->esq);
  int alturaDir = avlCalculaAltura(raiz->dir);
  return MAX(alturaEsq, alturaDir) + 1;
}

int avlCalculaFb(AVL * no) {
  return avlGetAltura(no->esq) - avlGetAltura(no->dir);
}

AVL * avlRotL(AVL * raiz) {
  if (raiz == NULL) return raiz;
  
  AVL * novaRaiz = raiz->dir;
  raiz->dir = novaRaiz->esq;
  novaRaiz->esq = raiz;

  raiz->altura = avlCalculaAltura(raiz);
  novaRaiz->altura = avlCalculaAltura(novaRaiz);

  return novaRaiz;
}

AVL * avlRotR(AVL * raiz) {
  if (raiz == NULL) return raiz;
  
  AVL * novaRaiz = raiz->esq;
  raiz->esq = novaRaiz->dir;
  novaRaiz->dir = raiz;

  raiz->altura = avlCalculaAltura(raiz);
  novaRaiz->altura = avlCalculaAltura(novaRaiz);

  return novaRaiz;
}

AVL * avlInsert(AVL * raiz, int chave) {
  if (raiz == NULL)
    return avlNovoNo(chave);
  
  if (chave > raiz->chave)
    raiz->dir = avlInsert(raiz->dir, chave);
  else
    raiz->esq = avlInsert(raiz->esq, chave);

  raiz->altura = avlCalculaAltura(raiz);
  int fb = avlCalculaFb(raiz);
  if (fb == +2) {
    if (avlCalculaFb(raiz->esq) < 0) {
      raiz->esq = avlRotL(raiz->esq);
    }
    raiz = avlRotR(raiz);
  }
  else if (fb == -2) {
    if (avlCalculaFb(raiz->dir) > 0) {
      raiz->dir = avlRotR(raiz->dir);
    }
    raiz = avlRotL(raiz);
  }
  
  return raiz;
}


void avlFree(AVL * raiz) {
  if (raiz == NULL) return;

  if (raiz->esq != NULL)
    avlFree(raiz->esq);
  if (raiz->dir != NULL)
    avlFree(raiz->dir);
  
  free(raiz);
}

int* geraNumerosAleatorios(int N) {
  int* numerosAleatorios = malloc(sizeof(int) * N); 
  srand(time(NULL));
  
  for (int i = 0; i < N; i++) {
    numerosAleatorios[i] = (rand() % (N * 1000)) + 1;
  }
  return numerosAleatorios;
}

 void gerarArvores(int A, int N){    
  int* alturasBST = malloc(sizeof(int) * A);
  int* alturasAVL = malloc(sizeof(int) * A);
   
  double mediaGeral = 0;
  double mediaBST = 0;
  double mediaAVL = 0;
  double totalAVL = 0;
  double totalBST = 0; 
   
   for (int i = 0; i < A; i++) {
      int * numerosAleatorios = geraNumerosAleatorios(N);
      BST * rBst = malloc(sizeof(BST));
      AVL * rAvl = malloc(sizeof(AVL));
     
        for (int k = 0; k < N; k++) { 
            rBst = bstInsert(rBst, numerosAleatorios[k]);
            rAvl = avlInsert(rAvl, numerosAleatorios[k]);
        }

      alturasAVL[i] = bstCalculaAltura(rAvl);
      alturasBST[i] = avlCalculaAltura(rBst);
      }
   
  for(int i = 0; i < A; i++){
        totalAVL += alturasAVL[i];
        totalBST += alturasBST[i];        
    }
   
  mediaAVL = totalAVL/A;
  mediaBST = totalBST/A;
  mediaGeral = (mediaAVL + mediaBST)/2 ;

   
   printf("\n Experiment with A = %d e N = %d\n", A, N);

    printf("----------------------------\n");

    printf("Overall average height: %lf\n", mediaGeral);
  
    printf("----------------------------\n");

    printf("Average height BST common: %lf\n", mediaBST);
    
    printf("----------------------------\n");

    printf("Average height AVL: %lf\n", mediaAVL);
    
    printf("----------------------------\n");

   free(alturasAVL);
   free(alturasBST);
}   

int main(void) {
  srand(time(NULL));

  //titulo
  printf("\tWelcome, hope you enjoy this little program cuz we are going on the heights :P\n");

  //variaveis
  int option, qntAmostra, qntElemento; 

  do{
      //perguntas do menu e escolha
      printf("\n Your options are:\n\n 0 - Leave\n 1 - New Simulation\n\n Choose one: ");
      scanf("%d", &option);
  
    //switch que diz o que cada opção executa  
    switch(option){
      
      //case 0, sai do programa
      case 0: 
      printf("\n See You Later, Alligator!\n After A While, Crocodile!\n THX!! BYEE!!!");
      break;

      //case 1 executa o programa
      case 1: 
        printf(" Enter the number of samples: ");
        scanf("%d", &qntAmostra);
        printf(" Enter the amount of elements for each sample: ");
        scanf("%d", &qntElemento);
        gerarArvores(qntAmostra, qntElemento);
        break; 
      
      default:
        printf("\t\nThis option doesn't exist, sorry!\n Please try again...\n");
    }
    
  } while(option != 0);
  return 0;
}