#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<iostream>
#include<time.h>

using namespace std;

void menuInicial();

void limpaTela(){
    system("CLS");
}

void iniciaTabuleiro(char tabuleiro[10][10],char mascara[10][10]){
    int linha,coluna;
    for(linha =0;linha<10;linha++){
        for(coluna=0;coluna<10;coluna++){
            tabuleiro[linha][coluna] = 'A';
            mascara[linha][coluna] = '*';
        }
    }
}

void exibeMapa(){
    cout<<"     ";
    for(int i=0;i<10;i++){
        cout <<i << " ";
    }

    cout << "\n";



    cout<<"     ";
    for(int i=0;i<10;i++){
        cout <<"|"<< " ";
    }

    cout << "\n";
}

void exibeTabuleiro(char tabuleiro[10][10], char mascara[10][10], bool mostraGabarito){
    char blue[] = { 0x1b, '[', '1', ';', '3', '4', 'm', 0 };
    char green[] = { 0x1b, '[', '1', ';', '3', '2', 'm', 0 };
    char normal[] = { 0x1b, '[', '1', ';', '3', '9', 'm', 0 };

    int linha,coluna;
    for(linha = 0; linha < 10; linha++){
         cout << linha << " - ";
         for(coluna = 0; coluna < 10; coluna++){

            switch(mascara[linha][coluna]){
                case 'A':
                    cout << blue << " " <<mascara[linha][coluna] << normal;
                    break;
                case 'P':
                    cout << green << " " <<mascara[linha][coluna] << normal;
                    break;
                default:
                    cout << " " <<mascara[linha][coluna];
                    break;
            }
         }
         cout << "\n";
    }
    if(mostraGabarito == false){
        for(linha = 0; linha < 10; linha++){
             for(coluna = 0; coluna < 10; coluna++){
                 cout << " " <<tabuleiro[linha][coluna];
             }
             cout << "\n";
        }
    }
}

void posicionaBarcos(char tabuleiro[10][10]){
    int quantidade = 10,quantidadePosicionada=0;

    while(quantidadePosicionada < quantidade){
        int linhaAleatoria = rand()%10;
        int colunaAleatoria = rand()%10;

        if(tabuleiro[linhaAleatoria][colunaAleatoria] == 'A'){
            tabuleiro[linhaAleatoria][colunaAleatoria] = 'P';

        quantidadePosicionada++;
        }
    }

}

void verificaTiro(char tabuleiro[10][10],int linhaJogada,int colunaJogada,int *pontos, string *mensagem){
     switch(tabuleiro[linhaJogada][colunaJogada]){
            case 'P':
                *pontos=*pontos+10;
                *mensagem = "Voce acertou um barco pequeno! (10 pts)";
                break;
            case 'A':
                *mensagem = "Voce acertou a agua! (0 pts)";
                break;
        }
}

void jogo(string nomeDoJogador){
    char tabuleiro[10][10], mascara[10][10];
    int linha,coluna;
    int linhaJogada,colunaJogada;
    int estadoDeJogo = 1;
    int pontos = 0;
    string mensagem = "Bem vindo ao jogo";
    int tentativas=0,maximoDeTentativas = 5;
    int opcao;


    iniciaTabuleiro(tabuleiro,mascara);

    posicionaBarcos(tabuleiro);

    while(tentativas < maximoDeTentativas){
        limpaTela();

        exibeMapa();

        exibeTabuleiro(tabuleiro,mascara,true);

        cout<<"Pontos: "<<pontos<<", Tentativas Restantes: "<<maximoDeTentativas-tentativas<<"\n";
        cout<<mensagem<<"\n";

        linhaJogada = -1;
        colunaJogada = -1;

        while((linhaJogada < 0 || colunaJogada < 0) || (linhaJogada > 9 || colunaJogada > 9) ){
        cout<<"\n"<<nomeDoJogador<<", Digite uma linha: ";
        cin>> linhaJogada;
        cout<<nomeDoJogador<<", Digite uma coluna: ";
        cin>> colunaJogada;
        }

        verificaTiro(tabuleiro,linhaJogada,colunaJogada,&pontos,&mensagem);

        mascara[linhaJogada][colunaJogada]=tabuleiro[linhaJogada][colunaJogada];

    tentativas++;
    }
    cout<<"FIM de jogo";
    cout<<"\n1 - Jogar Novamente";
    cout<<"\n2 - Ir para o Menu";
    cout<<"\n3 - Sair\n";
    cin>>opcao;

    switch(opcao){
        case 1:
            jogo(nomeDoJogador);
            break;
        case 2:
            menuInicial();
            break;
    }

}

void menuInicial(){
    int opcao=0;
    string nomeDoJogador;


    while(opcao<1 || opcao>3){
    limpaTela();
    cout<<"Bem vindo";
    cout<<"\n1 - Jogar";
    cout<<"\n2 - Sobre";
    cout<<"\n3 - Sair";
    cout<<"\nEscolha uma opcao e tecle ENTER: ";
    cin>> opcao;

    switch(opcao){
    case 1:
        cout<<"Qual seu nome? ";
        cin>>nomeDoJogador;
        jogo(nomeDoJogador);
        break;
    case 2:
        cout<<"Feito por leomitx10 em 2023.";
        break;
    case 3:
        cout<<"Ate mais";
        break;
    }
    }
}

int main(){
    srand((unsigned)time(NULL));
    menuInicial();


}
