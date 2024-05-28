#include <iostream>
using namespace std;

struct NoArvore{
    char info;
    int peso = 0;
    NoArvore *esq=NULL, *dir=NULL;
};

bool inserir(NoArvore *&raiz, char valor){
    if( raiz == NULL ){
        raiz = new NoArvore;
        raiz->info = valor;
        return true;
    }
    if( raiz->info == valor ) return false;
    if( valor < raiz->info )
        return inserir(raiz->esq, valor);
    else
        return inserir(raiz->dir, valor);
}

char buscar_maior( NoArvore *raiz ){
    if( raiz->dir != NULL )
        return buscar_maior(raiz->dir);
    else
        return raiz->info;
}

bool retirar( NoArvore *&raiz, char valor ){
    if( raiz == NULL ) return false;
    if( raiz->info == valor ){
        NoArvore *aux = raiz;
        if( raiz->esq == NULL && raiz->dir == NULL ){ // Caso A
            raiz = NULL;
            delete aux;
            return true;
        }
        if( raiz->esq == NULL && raiz->dir != NULL ){ // Caso B - parte I
            raiz = raiz->dir;
            delete aux;
            return true;
        }
        if( raiz->esq != NULL && raiz->dir == NULL ){ // Caso B - parte II
            raiz = raiz->esq;
            delete aux;
            return true;
        }
        // caso C
        char info_aux = buscar_maior(raiz->esq);
        raiz->info = info_aux;
        return retirar(raiz->esq, info_aux);
    }
    if( valor < raiz->info )
        return retirar(raiz->esq, valor);
    else
        return retirar(raiz->dir, valor);
}

void prefixado(NoArvore *raiz){
    if( raiz == NULL ) return;
    cout << raiz->info << " ";
    prefixado(raiz->esq);
    prefixado(raiz->dir);
}


void infixado(NoArvore *raiz){
    if( raiz == NULL ) return;
    infixado(raiz->esq);
    cout << raiz->info << " ";
    infixado(raiz->dir);
}


void posfixado(NoArvore *raiz){
    if( raiz == NULL ) return;
    posfixado(raiz->esq);
    posfixado(raiz->dir);
    cout << raiz->info << " ";
}


void liberar(NoArvore *raiz){
    if( raiz == NULL ) return;
    liberar(raiz->esq);
    liberar(raiz->dir);
    delete raiz;
}


bool pesquisar(NoArvore  *raiz, char valor){
    if( raiz == NULL ) return false;
    if( raiz->info == valor ) return true;
    if( valor < raiz->info )
        return pesquisar(raiz->esq, valor);
    else
        return pesquisar(raiz->dir, valor);
}


int contar(NoArvore *raiz){
    if( raiz == NULL ) return 0;
    return 1 + contar(raiz->esq) + contar(raiz->dir);
}


int altura( NoArvore *raiz ){
    if( raiz == NULL ) return 0;
    int altE = altura(raiz->esq);
    int altD = altura(raiz->dir);
    return (altE > altD) ? altE+1 : altD+1;
}
