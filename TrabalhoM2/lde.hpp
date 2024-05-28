#include <iostream>
#include "abb.hpp"
using namespace std;

struct No{
    NoArvore *nozin;
    No *eloA, *eloP;
};

struct LDE{
    No *comeco;
    No *fim;
};


//
// Inicializa a lista dada por par�metro
//
void inicializarLDE(LDE &lista){
    lista.comeco = NULL;
    lista.fim = NULL;
}

//
// Mostra todo o conte�do da lista na tela
//
void mostrarLDE(LDE lista, char ordem='C'){
    No *aux;

    aux = (ordem == 'C') ? lista.comeco : lista.fim;
    while( aux != NULL ){
        cout << aux->nozin->info << "-" << aux->nozin->peso << "\t";
        aux = (ordem == 'C') ? aux->eloP : aux->eloA;
    }
    if( lista.comeco == NULL ) cout << "<Vazio>";
}

//
// Insere o valor na lista dada respeitando a ordem crescente
//
bool inserirLDE(LDE &lista, char valor, int freq, NoArvore *arvore1 = NULL){
    No *novo;

    NoArvore *arvore = new NoArvore;
    arvore->info = valor;
    arvore->peso = freq;
    arvore->esq = NULL;
    arvore->dir = NULL;

    // Criar o novo no
    novo = new No;
    if( novo == NULL ) return false;
    
    if(arvore1 == NULL){
        novo->nozin = arvore;
        novo->eloA = NULL;
        novo->eloP = NULL;
    }else{
        novo->nozin = arvore1;
        novo->eloA = NULL;
        novo->eloP = NULL;
    }
    
    // Lista vazia
    if( lista.comeco == NULL ){
        lista.comeco = novo;
        lista.fim = novo;
        return true;
    }

    // Inser��o no comeco
    if( freq <= lista.comeco->nozin->peso ){
        novo->eloP = lista.comeco;
        lista.comeco->eloA = novo;
        lista.comeco = novo;
        return true;
    }

    // Inser��o no final
    if( freq >= lista.fim->nozin->peso ){
        lista.fim->eloP = novo;
        novo->eloA = lista.fim;
        lista.fim = novo;
        return true;
    }

    // Inserir no meio
    No *ant = lista.comeco;
    while( ant->nozin->peso < freq && ant->eloP->nozin->peso <= freq )
        ant = ant->eloP;
    No *prox = ant->eloP;

    novo->eloA = ant;
    novo->eloP = prox;
    ant->eloP = novo;
    prox->eloA = novo;
    return true;
}

//
// Insere o valor dado sempre no final da lista
//
bool inserirFinalLDE(LDE &lista, char valor){
    No *novo;

    // Criar o novo no
    novo = new No;
    if( novo == NULL ) return false;
    novo->nozin->info = valor;
    novo->eloA = NULL;
    novo->eloP = NULL;

    // Lista vazia
    if( lista.comeco == NULL ){
        lista.comeco = novo;
        lista.fim = novo;
        return true;
    }

    lista.fim->eloP = novo;
    novo->eloA = lista.fim;
    lista.fim = novo;
    return true;
}

//
// Pesquisar se o valor est� na lista
// retornar o endere�o do valor ou nulo se n�o estiver
//
No *pesquisarLDE(LDE lista, char valor){
    No *aux = lista.comeco;

    while( aux != NULL ){
        if( aux->nozin->info == valor ) return aux;
        aux = aux->eloP;
    }
    return NULL;
}

//
// Retirar o valor da lista
// retornar verdadeiro ou false se n�o achar
//
bool retirarLDE(LDE &lista, char valor){
    No *aux, *anterior, *proximo;

    aux = pesquisarLDE(lista, valor);

    if( aux == NULL ) return false;
    anterior = aux->eloA;
    proximo = aux->eloP;


    if( aux == lista.comeco ){ // Casos 1 e 2
        lista.comeco = proximo;
        if( aux == lista.fim ) lista.fim = NULL;
        else proximo->eloA = NULL;
    } else { // Casos 3 e 4
        anterior->eloP = aux->eloP;
        if( aux == lista.fim ) lista.fim = anterior;
        else proximo->eloA = anterior;
    }
    delete aux;
    return true;
}

//
// Libera toda a mem�ria alocada para a lista fornecida
//
void liberarLDE(LDE &lista){
    No *aux = lista.comeco;
    No *aux2;


    while( aux != NULL ){
    liberar(aux->nozin);
        aux2 = aux->eloP;
        delete aux;
        aux = aux2;
    }

    lista.comeco = NULL;
    lista.fim = NULL;
}

//construcao da arvore
NoArvore* Huffman(LDE &lista){
    if(lista.comeco == lista.fim){
        return lista.comeco->nozin;
    }
    NoArvore *Tr = new NoArvore;
    NoArvore *T1;
    NoArvore *T2;
    
    T1 = lista.comeco->nozin;
    T2 = lista.comeco->eloP->nozin;

    Tr->peso = T1->peso + T2->peso;
    Tr->info = '*';
    Tr->esq = T1;
    Tr->dir = T2;
    inserirLDE(lista,'*',Tr->peso, Tr);
    retirarLDE(lista, T1->info);
    retirarLDE(lista, T2->info);
    return Huffman(lista);
}

//codificação
string caminhoCaracter(NoArvore *raiz, char caractere, string caminho = "") {
    if (raiz == NULL) {
        return "";  // Retorna uma string vazia se o nó for nulo
    }

    if (raiz->info == caractere) {
        return caminho;
    }

    string caminhoEsquerda = caminhoCaracter(raiz->esq, caractere, caminho + "0");
    string caminhoDireita = caminhoCaracter(raiz->dir, caractere, caminho + "1");

    if (!caminhoEsquerda.empty()) {
        return caminhoEsquerda;  // Retorna o caminho da subárvore esquerda se o caractere for encontrado
    } else {
        return caminhoDireita;   // Retorna o caminho da subárvore direita se o caractere for encontrado ou se não for encontrado
    }
}