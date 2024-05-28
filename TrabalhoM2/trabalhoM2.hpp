#include <iostream>
#include <string>
#include <fstream>
#include "lde.hpp"
using namespace std;


//decodificacao
void decotifica(NoArvore *raiz, string binario, int posicao = 0){
    NoArvore *p = raiz;
    for(int i = posicao; i < binario.length(); i++){
        if(binario[i] == '0'){
        p = p->esq;

        }else if(binario[i] == '1'){
            p = p->dir;
        }

        if (p->esq == NULL  && p->dir == NULL) {
            cout << p->info; 
            p = raiz;
        }
    }

}

string le_arquivo(string frase, string nomeDoArquivo){
    
    ifstream arquivo(nomeDoArquivo);
    string linha;

    if(arquivo.is_open()){
        while(getline(arquivo, linha)){
            frase = frase + linha;
        }
        arquivo.close();
    }else{
        cout << "nao foi possivel abrir o arquivo";
    }
    return frase;
}

string menu(string frase){
    int escolha;
    string nomeDoArquivo;


    cout << "Quer ler um arquivo ou escrever uma frase?" << endl;
    cout << "[1] Escrever minha frase" << endl;
    cout << "[2] Ler um arquivo" << endl;
    cout << "[3] Sobre" << endl;
    cin >> escolha;

    switch(escolha){
        case 1:
            cout << "Escreva a sua frase: ";
            cin.ignore();
            getline(cin, frase);
        break;

        case 2:
            cout << "Escreva o nome do arquivo: ";
            cin >> nomeDoArquivo;
            frase = le_arquivo(frase, nomeDoArquivo);
        break;

        case 3:
            cout << "Trabalho que faz a compressao e descompressao de frases, desde que nao tenham caracter especial '*'." << endl;
            cout << "Autor: Marco Antonio Martins Akerman." << endl;
            cout << "Ano: 2023" << endl;
            return menu(frase);
        break;
    }

    return frase;
    
}


void principal(){

    LDE lista_arvore;
    inicializarLDE(lista_arvore);

    string frase;


    int numeroTotalCaracteres = 0;
    int contadorDeCaracter[256] = {0};


    frase = menu(frase);

    for(int i = 0; i < frase.length(); i++){
        //cout << frase[i] << endl;
        contadorDeCaracter[frase[i]]++;
        numeroTotalCaracteres++;
    }


    // static_cast<char>(i) unica opcao que funcionou
    for(int i = 0; i < 256; i++){
        if(contadorDeCaracter[i] != 0){
            inserirLDE(lista_arvore, static_cast<char>(i), contadorDeCaracter[i]);
        }
    }

    cout << "Letras e frequencias: ";
    mostrarLDE(lista_arvore, 'C');

    NoArvore *raiz = Huffman(lista_arvore);

    cout << endl;
    cout << "arvore infixado: ";
    infixado(raiz);
    cout << endl;

    cout << "no raiz: ";
    mostrarLDE(lista_arvore, 'C');

    cout << endl;

    string fraseBinaria;
    for(int i = 0; i < frase.length(); i++){
        fraseBinaria = fraseBinaria + caminhoCaracter(raiz, frase[i]);
    }

    cout << "codificado: ";
    cout << fraseBinaria;

    cout << endl;

    cout << "decotificado: ";
    decotifica(raiz,fraseBinaria);

    
    //libera arovre e lista
    liberarLDE(lista_arvore);


}