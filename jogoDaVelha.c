//Jonas Felipe Muniz Rodrigues      21.1.4048
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TAM 20
#define ANSI_RESET            "\x1b[0m"  // desativa os efeitos anteriores
#define ANSI_BOLD             "\x1b[1m"  // coloca o texto em negrito
#define ANSI_COLOR_BLACK      "\x1b[30m"
#define ANSI_COLOR_RED        "\x1b[31m"
#define ANSI_COLOR_GREEN      "\x1b[32m"
#define ANSI_COLOR_YELLOW     "\x1b[33m"
#define ANSI_COLOR_BLUE       "\x1b[34m"
#define ANSI_COLOR_WHITE      "\x1b[37m"
#define BOLD(string)       ANSI_BOLD             string ANSI_RESET
#define BLUE(string)       ANSI_COLOR_BLUE       string ANSI_RESET
#define RED(string)        ANSI_COLOR_RED        string ANSI_RESET
#define GREEN(string)      ANSI_COLOR_GREEN      string ANSI_RESET
#define YELLOW(string)     ANSI_COLOR_YELLOW     string ANSI_RESET
#define BLUE(string)       ANSI_COLOR_BLUE       string ANSI_RESET
#define WHITE(string)      ANSI_COLOR_WHITE      string ANSI_RESET


//Criando struct 
typedef struct jogador{
    char nome[TAM];
    int vitorias;
    int empates;
    int derrotas;
}TipoJogador;

//Protótipo das funçõs
void tabuleiro(char casas2 [3][3]);
int gerarAleatorio(int aleatorio);
char *lerStringSeguramente(char *string, int tamanho);


//Função main
int main(int argc, char **argv){     
    char casas[3][3];
    int cont_jogadas, l, c, vez = 0; //l = linha  c = coluna 
    //Agora vamos criar duas variaveis para limpar nossa matrix i e j 
    int marcar, aleatorio;
    int inicio, voltarJogo0, voltarJogo1, voltarJogo2; //variaveis usadas apenas para o goto   
    //system("clear") da biblioteca “stdlib.h” usada para limpar o terminal 
    int op, nJogadores = 0; //op => opção  nJogadores => numero de jogadores
    TipoJogador jogador1, jogador2;
    char escolha[TAM], computador[] = "Computador"; // "marcar" ou "voltar" "salvar"
    
    system("clear");
    
    inicio:
        do{
            system("clear");

            printf(BLUE(BOLD("\n# BEM VINDO AO JOGO DA VELHA #")) "\n\n");
            printf(RED(BOLD("  0. Sair do Jogo")) "\n");
            printf(YELLOW(BOLD("  1. Começar um novo jogo")) "\n");
            printf(YELLOW(BOLD("  2. Continuar um jogo salvo")) "\n");
            printf(YELLOW(BOLD("  3. Continuar o jogo atual")) "\n");
            printf(YELLOW(BOLD("  4. Exibir o ranking\t")) "\n\n");
            printf(BLUE(BOLD("Durante o jogo digite “voltar” para retornar ao menu.")) "\n");
            printf(BLUE(BOLD("Escolha a opção: ")) "\n");
            scanf("%d", &op);
        }while(op != 0 && op != 1 && op != 2 && op != 3 && op != 4); //condição para vaidação de entradas das opções
        
        system("clear");
        if(op == 0){
            return 0;
        }
        else if(op == 1){
            do{  
                system("clear");
                printf(BOLD(GREEN("Digite o numero de jogadores (1 ou 2): ")));
                scanf("%d", &nJogadores);
            }while(nJogadores != 1 && nJogadores != 2);
            if(nJogadores == 1){
                //caso seja contra o computador
                fflush(stdin);
                printf(BOLD(RED("Digite o nome do jogador 1: ")) "\n");
                if(fgets(jogador1.nome, TAM, stdin) != NULL){
                    lerStringSeguramente(jogador1.nome, TAM);
                }
                cont_jogadas = 1;
                for(int i = 0; i <=2; i++){
                    for(int j = 0; j <=2; j++){
                        casas[i][j] = ' ';
                    }
                }
            do{
                tabuleiro(casas);

                do{
                    if(vez%2 == 0){
                        do{
                            if(voltarJogo0 == 1){
                                voltarJogo0:
                                system("clear");
                                tabuleiro(casas);
                            }                           
                            printf(BOLD(RED("%s, digite o comando: ")), jogador1.nome);
                            scanf("%s", escolha);
                            if(strcmp(escolha,"salvar") == 0){
                                FILE *arq;
                                arq = fopen("jogoatual.txt", "w");
                                if(arq == NULL){
                                    printf("Houve um erro ao abrir o arquivo. o programa será fechado.\n");
                                    return 0;
                                }
                                printf("arquivo criado com sucesso\n\n");
                                    fprintf(arq, "%d\n", nJogadores);
                                    fprintf(arq, "%s\n", jogador1.nome);
                                    for(int i = 0; i < 3; i++){
                                        for(int j = 0; j < 3; j++){
                                            fprintf(arq, "%c ", casas[i][j]);
                                        }fprintf(arq, "\n");

                                    }
                                fclose(arq);
                            }
                        }while(strcmp(escolha,"salvar") == 0);
                        if(strcmp(escolha,"voltar") == 0){
                            goto inicio;
                        }
                        scanf("%d", &marcar);
                    }
                    else{
                        printf("Vez computador \n");
                        if(vez == 1){
                            marcar = gerarAleatorio(aleatorio);
                        }
                        else if(vez == 3 || vez == 5 || vez == 7 || vez == 7){
                            //ANTES DE EVITAR A VITORIA VAMOS TENTAR GANHAR
                            //Condições para ganhar na 1ªlinha
                            if(casas [0][0] == 'O' && casas [0][1] == 'O' && casas[0][2] == ' '){
                                marcar = 13;
                            }
                            else if(casas [0][0] == 'O' && casas [0][2] == 'O' && casas[0][1] == ' '){
                                marcar = 12;
                            }
                            else if(casas [0][1] == 'O' && casas [0][2] == 'O' && casas[0][0] == ' '){
                                marcar = 11;
                            }
                            //condições para ganhar na 2ª linha
                            else if(casas [1][0] == 'O' && casas [1][1] == 'O' && casas[1][2] == ' '){
                                marcar = 23;
                            }
                            else if(casas [1][0] == 'O' && casas [1][2] == 'X' && casas[1][1] == ' '){
                                marcar = 22;
                            }
                            else if(casas [1][1] == 'O' && casas [1][2] == 'O' && casas[1][0] == ' '){
                                marcar = 21;
                            }
                            //condições para ganhar na 3ª linha
                            else if(casas [2][0] == 'O' && casas [2][1] == 'O' && casas[2][2] == ' '){
                                marcar = 33;
                            }
                            else if(casas [2][0] == 'O' && casas [2][2] == 'O' && casas[2][1] == ' '){
                                marcar = 32;
                            }
                            else if(casas [2][1] == 'O' && casas [2][2] == 'O' && casas[2][0] == ' '){
                                marcar = 31;
                            }
                            //EVITANDO VITORIA NAS COLUNAS
                            //condições para ganhar na 1ª coluna
                            else if(casas [0][0] == 'O' && casas [1][0] == 'O' && casas[2][0] == ' '){
                                marcar = 31;
                            }
                            else if(casas [0][0] == 'O' && casas [2][0] == 'O' && casas[1][0] == ' '){
                                marcar = 21;
                            }
                            else if(casas [1][0] == 'O' && casas [2][0] == 'X' && casas[0][0] == ' '){
                                marcar = 11;
                            }
                            //condições para ganhar na 2ª coluna
                            else if(casas [0][1] == 'O' && casas [1][1] == 'O' && casas[2][1] == ' '){
                                marcar = 32;
                            }
                            else if(casas [0][1] == 'O' && casas [2][1] == 'O' && casas[1][1] == ' '){
                                marcar = 22;
                            }
                            else if(casas [1][1] == 'O' && casas [2][1] == 'O' && casas[0][1] == ' '){
                                marcar = 12;
                            }
                            //condições para ganhar na 3ª coluna
                            else if(casas [0][2] == 'O' && casas [1][2] == 'O' && casas[2][2] == ' '){
                                marcar = 33;
                            }
                            else if(casas [0][2] == 'O' && casas [2][2] == 'O' && casas[1][2] == ' '){
                                marcar = 23;
                            }
                            else if(casas [1][2] == 'O' && casas [2][2] == 'O' && casas[0][2] == ' '){
                                marcar = 13;
                            }
                            //EVITANDO VITORIA NAS DIAGONAIS
                            //condições para ganhar na diagonal PRINCIPAL 
                            else if(casas [0][0] == 'O' && casas [1][1] == 'O' && casas[2][2] == ' '){
                                marcar = 33;
                            }
                            else if(casas [0][0] == 'O' && casas [2][2] == 'O' && casas[1][1] == ' '){
                                marcar = 22;
                            }
                            else if(casas [1][1] == 'O' && casas [2][2] == 'O' && casas[0][0] == ' '){
                                marcar = 11;
                            }//condições para ganhar diagonal SECUNDARIA 
                            else if(casas [0][2] == 'O' && casas [1][1] == 'O' && casas[2][0] == ' '){
                                marcar = 31;
                            }
                            else if(casas [0][2] == 'X' && casas [2][0] == 'O' && casas[1][1] == ' '){
                                marcar = 22;
                            }
                            else if(casas [2][0] == 'O' && casas [1][1] == 'O' && casas[0][2] == ' '){
                                marcar = 13;
                            }

                            //EVITANDO VITÓTIA NAS LINHAS
                            //condições para evitar vitoria na 1ª linha
                            else if(casas [0][0] == 'X' && casas [0][1] == 'X' && casas[0][2] == ' '){
                                marcar = 13;
                            }
                            else if(casas [0][0] == 'X' && casas [0][2] == 'X' && casas[0][1] == ' '){
                                marcar = 12;
                            }
                            else if(casas [0][1] == 'X' && casas [0][2] == 'X' && casas[0][0] == ' '){
                                marcar = 11;
                            }
                            //condições para evitar vitoria na 2ª linha
                            else if(casas [1][0] == 'X' && casas [1][1] == 'X' && casas[1][2] == ' '){
                                marcar = 23;
                            }
                            else if(casas [1][0] == 'X' && casas [1][2] == 'X' && casas[1][1] == ' '){
                                marcar = 22;
                            }
                            else if(casas [1][1] == 'X' && casas [1][2] == 'X' && casas[1][0] == ' '){
                                marcar = 21;
                            }
                            //condições para evitar vitoria na 3ª linha
                            else if(casas [2][0] == 'X' && casas [2][1] == 'X' && casas[2][2] == ' '){
                                marcar = 33;
                            }
                            else if(casas [2][0] == 'X' && casas [2][2] == 'X' && casas[2][1] == ' '){
                                marcar = 32;
                            }
                            else if(casas [2][1] == 'X' && casas [2][2] == 'X' && casas[2][0] == ' '){
                                marcar = 31;
                            }
                            //EVITANDO VITORIA NAS COLUNAS
                            //condições para evitar vitoria na 1ª coluna
                            else if(casas [0][0] == 'X' && casas [1][0] == 'X' && casas[2][0] == ' '){
                                marcar = 31;
                            }
                            else if(casas [0][0] == 'X' && casas [2][0] == 'X' && casas[1][0] == ' '){
                                marcar = 21;
                            }
                            else if(casas [1][0] == 'X' && casas [2][0] == 'X' && casas[0][0] == ' '){
                                marcar = 11;
                            }
                            //condições para evitar vitória na 2ª coluna
                            else if(casas [0][1] == 'X' && casas [1][1] == 'X' && casas[2][1] == ' '){
                                marcar = 32;
                            }
                            else if(casas [0][1] == 'X' && casas [2][1] == 'X' && casas[1][1] == ' '){
                                marcar = 22;
                            }
                            else if(casas [1][1] == 'X' && casas [2][1] == 'X' && casas[0][1] == ' '){
                                marcar = 12;
                            }
                            //condições para evitar vitória na 3ª coluna
                            else if(casas [0][2] == 'X' && casas [1][2] == 'X' && casas[2][2] == ' '){
                                marcar = 33;
                            }
                            else if(casas [0][2] == 'X' && casas [2][2] == 'X' && casas[1][2] == ' '){
                                marcar = 23;
                            }
                            else if(casas [1][2] == 'X' && casas [2][2] == 'X' && casas[0][2] == ' '){
                                marcar = 13;
                            }
                            //EVITANDO VITORIA NAS DIAGONAIS
                            //condições para evitar vitoria na diagonal PRINCIPAL 
                            else if(casas [0][0] == 'X' && casas [1][1] == 'X' && casas[2][2] == ' '){
                                marcar = 33;
                            }
                            else if(casas [0][0] == 'X' && casas [2][2] == 'X' && casas[1][1] == ' '){
                                marcar = 22;
                            }
                            else if(casas [1][1] == 'X' && casas [2][2] == 'X' && casas[0][0] == ' '){
                                marcar = 11;
                            }//condições para evitar vitoria na diagonal SECUNDARIA 
                            else if(casas [0][2] == 'X' && casas [1][1] == 'X' && casas[2][0] == ' '){
                                marcar = 31;
                            }
                            else if(casas [0][2] == 'X' && casas [2][0] == 'X' && casas[1][1] == ' '){
                                marcar = 22;
                            }
                            else if(casas [2][0] == 'X' && casas [1][1] == 'X' && casas[0][2] == ' '){
                                marcar = 13;
                            }
                            //Vou testar uma opção para gerar um numero aleatóri caso as condissões acima não se satisfazem
                            //ou seja, se o jogador ainda não conseguir ganhar o jogo com APENAS mais um movimento 
                            else{
                                //vamos fazer um pequeno do while para evitar que o programa execute coisas desnecessárias
                                do{
                                    marcar = gerarAleatorio(aleatorio);
                                    l = (marcar%100)/10;
                                    c = marcar%10;

                                }while(casas[l-1][c-1] != ' ');
                            }

                        }   
                    }
                    l = (marcar%100)/10;
                    c = marcar%10;
        
                    if(marcar > 33 || strcmp(escolha, "marcar") != 0){
                        printf(BOLD(RED("ERRO/entrada invalida!!!"))"\n");//OBS:colocar os erros de vermelho
                    }
                }while(marcar > 33 || strcmp(escolha, "marcar") != 0);//com isso eu invalido jogadas com mais de duas casas decimais evitando o erro na proxima etapa
                
                system("clear");
                
                if(c < 1 || l < 1 || l > 3 || c > 3){
                    /* Neste caso igualamos igual a 0 pois queremso dizer
                    que o resultado foi invalido, OBS: desta forma podemos reaproveitar esses 
                    valores*/ 
                    l = 0;
                    c = 0;
                }
                else if(casas[l-1][c-1] != ' '){
                    l = 0;
                    c = 0;
                }
                else{
                    if(vez%2 == 0){
                        casas[l-1][c-1] = 'X';   
                    }//OBS é coluna e linha -1 pois se ele marcar 1 e 1 e fazendo a coluna e linha 0. OBS vetores começam na posição 0
                    else{
                        casas[l-1][c-1] = 'O';
                    }
                    vez++;
                    cont_jogadas++;
                }
                //Agora vamos fazer a nossas condições de vitória do Jogado X
                //Fazendo para as linhas
                if(casas [0][0] == 'X' && casas [0][1] == 'X' && casas [0][2] == 'X'){
                    cont_jogadas = 11; 
                // desta maneira terminamos o jogo pois se vermos na linha de baixo veremos que o numero maximo de jogadas é igual a 9
                }                    
                else if(casas [1][0] == 'X' && casas [1][1] == 'X' && casas [1][2] == 'X'){
                    cont_jogadas = 11; 
                }
                else if(casas [2][0] == 'X' && casas [2][1] == 'X' && casas [2][2] == 'X'){
                    cont_jogadas = 11; 
                }
                //Agora fazendo para as colunas
                else if(casas [0][0] == 'X' && casas [1][0] == 'X' && casas [2][0] == 'X'){
                    cont_jogadas = 11; 
                }
                else if(casas [0][1] == 'X' && casas [1][1] == 'X' && casas [2][1] == 'X'){
                    cont_jogadas = 11; 
                }
                else if(casas [0][2] == 'X' && casas [1][2] == 'X' && casas [2][2] == 'X'){
                    cont_jogadas = 11; 
                }
                //Fazendo para as diagonais
                else if(casas [0][0] == 'X' && casas [1][1] == 'X' && casas [2][2] == 'X'){
                    cont_jogadas = 11; 
                }
                else if(casas [0][2] == 'X' && casas [1][1] == 'X' && casas [2][0] == 'X'){
                    cont_jogadas = 11; 
                }
                //Agora vamos fazer a nossas condições de vitória do Jogado O
                //Fazendo para as linhas
                if(casas [0][0] == 'O' && casas [0][1] == 'O' && casas [0][2] == 'O'){
                    cont_jogadas = 12; // desta maneira terminamos o jogo pois se vermos na linha de baixo veremos que o numero maximo de jogadas é igual a 9
                }                    
                else if(casas [1][0] == 'O' && casas [1][1] == 'O' && casas [1][2] == 'O'){
                    cont_jogadas = 12; 
                }
                else if(casas [2][0] == 'O' && casas [2][1] == 'O' && casas [2][2] == 'O'){
                    cont_jogadas = 12; 
                }
                //Agora fazendo para as colunas
                else if(casas [0][0] == 'O' && casas [1][0] == 'O' && casas [2][0] == 'O'){
                    cont_jogadas = 12; 
                }
                else if(casas [0][1] == 'O' && casas [1][1] == 'O' && casas [2][1] == 'O'){
                    cont_jogadas = 12; 
                }
                else if(casas [0][2] == 'O' && casas [1][2] == 'O' && casas [2][2] == 'O'){
                    cont_jogadas = 12; 
                }
                //Fazendo para as diagonais
                else if(casas [0][0] == 'O' && casas [1][1] == 'O' && casas [2][2] == 'O'){
                    cont_jogadas = 12; 
                }
                else if(casas [0][2] == 'O' && casas [1][1] == 'O' && casas [2][0] == 'O'){
                    cont_jogadas = 12; 
                }

                
            }while(cont_jogadas <= 9);
            tabuleiro(casas);
            if(cont_jogadas == 10){  //OBSERVAR o porque cont jogadas chega ate 12
                printf("Jogo empatado\n"); 
            }
            else if(cont_jogadas == 11){
                printf(BOLD(RED("Vencedor %s!!!"))"\n", jogador1.nome);
            }
            else if(cont_jogadas == 12){
                printf(BOLD(BLUE("Vencedor %s!!!"))"\n", computador);
            }
            
            }
            else{
            //2-jogadores 2-jogadores 2-jogadores 2-jogadores  2-jogadores 2-jogadores 2-jogadores 2-jogadores 

                fflush(stdin);
                printf(BOLD(RED("Digite o nome do jogador 1: ")) "\n");
                if(fgets(jogador1.nome, TAM, stdin) != NULL) {
                    lerStringSeguramente(jogador1.nome, TAM);
                }
                fflush(stdin);
                printf(BOLD(BLUE("Digite o nome do jogador 2: ")) "\n");
                scanf("%s", jogador2.nome);
                system("clear");
                cont_jogadas = 1;
                for(int i = 0; i <=2; i++){
                    for(int j = 0; j <=2; j++){
                        casas[i][j] = ' ';
                    }

                }

            do{
                tabuleiro(casas);
                do{
                    if(vez%2 == 0){  
                        do{
                            if(voltarJogo1 == 1){
                                voltarJogo1:
                                system("clear");
                                tabuleiro(casas);
                            }         
                            printf(BOLD(RED("%s, digite o comando: ")), jogador1.nome);
                            scanf("%s", escolha);
                            if(strcmp(escolha,"salvar") == 0){
                                FILE *arq;
                                arq = fopen("jogoatual.txt", "w");
                                if(arq == NULL){
                                    printf("Houve um erro ao abrir o arquivo. o programa será fechado.\n");
                                    return 0;
                                }
                                printf("arquivo criado com sucesso\n\n");
                                fprintf(arq, "%d\n", nJogadores);
                                fprintf(arq, "%s\n", jogador1.nome);
                                fprintf(arq, "%s\n", jogador2.nome);
                                    for(int i = 0; i < 3; i++){
                                        for(int j = 0; j < 3; j++){
                                            fprintf(arq, "%c ", casas[i][j]);
                                        }
                                        fprintf(arq, "\n");
                                    }
                                fclose(arq);
                            }
                        }while(strcmp(escolha,"salvar") == 0);
                        if(strcmp(escolha,"voltar") == 0){
                            goto inicio;
                        }
                    }
                    else{
                        do{
                            if(voltarJogo2 == 1){
                                voltarJogo2:
                                system("clear");
                                tabuleiro(casas);
                            } 
                            printf(BOLD(BLUE("%s, digite o comando: ")), jogador2.nome);
                            scanf("%s", escolha);
                            if(strcmp(escolha,"salvar") == 0){
                                FILE *arq;
                                arq = fopen("jogoatual.txt", "w");
                                if(arq == NULL){
                                    printf("Houve um erro ao abrir o arquivo. o programa será fechado.\n");
                                    return 0;
                                }
                                printf("arquivo criado com sucesso\n\n");
                                fprintf(arq, "%d\n", nJogadores);
                                fprintf(arq, "%s\n", jogador1.nome);
                                fprintf(arq, "%s\n", jogador2.nome);
                                    for(int i = 0; i < 3; i++){
                                        for(int j = 0; j < 3; j++){
                                            fprintf(arq, "%c ", casas[i][j]);
                                        }
                                        fprintf(arq, "\n");
                                    }
                                fclose(arq);
                            }
                        }while(strcmp(escolha,"salvar") == 0);
                        if(strcmp(escolha,"voltar") == 0){
                            goto inicio;
                        }
                    }
                    scanf("%d", &marcar);
                    if(marcar > 33 || strcmp(escolha, "marcar") != 0){
                        printf(BOLD(RED("ERRO/entrada invalida!!!"))"\n");//OBS:colocar os erros de vermelho
                    }

                }while(marcar > 33 || strcmp(escolha, "marcar") != 0);//com isso eu invalido jogadas com mais de duas casas decimais evitando o erro na proxima etapa
                system("clear");
                l = (marcar%100)/10;
                c = marcar%10;
                if(c < 1 || l < 1 || l > 3 || c > 3){
                    /* Neste caso igualamos igual a 0 pois queremso dizer
                    que o resultado foi invalido, OBS: desta forma podemos reaproveitar esses 
                    valores*/ 
                    l = 0;
                    c = 0;
                }
                else if(casas[l-1][c-1] != ' ' ){
                    l = 0;
                    c = 0;
                }
                else{
                    if(vez%2 == 0){
                        casas[l-1][c-1] = 'X';   
                    }//OBS é coluna e linha -1 pois se ele marcar 1 e 1 e fazendo a coluna e linha 0. OBS vetores começam na posição 0
                    else{
                        casas[l-1][c-1] = 'O';
                    }
                    vez++;
                    cont_jogadas++;
                }
                //Agora vamos fazer a nossas condições de vitória do Jogado X
                //Fazendo para as linhas
                if(casas [0][0] == 'X' && casas [0][1] == 'X' && casas [0][2] == 'X'){
                    cont_jogadas = 11; 
                // desta maneira terminamos o jogo pois se vermos na linha de baixo veremos que o numero maximo de jogadas é igual a 9
                }                    
                else if(casas [1][0] == 'X' && casas [1][1] == 'X' && casas [1][2] == 'X'){
                    cont_jogadas = 11; 
                }
                else if(casas [2][0] == 'X' && casas [2][1] == 'X' && casas [2][2] == 'X'){
                    cont_jogadas = 11; 
                }
                //Agora fazendo para as colunas
                else if(casas [0][0] == 'X' && casas [1][0] == 'X' && casas [2][0] == 'X'){
                    cont_jogadas = 11; 
                }
                else if(casas [0][1] == 'X' && casas [1][1] == 'X' && casas [2][1] == 'X'){
                    cont_jogadas = 11; 
                }
                else if(casas [0][2] == 'X' && casas [1][2] == 'X' && casas [2][2] == 'X'){
                    cont_jogadas = 11; 
                }
                //Fazendo para as diagonais
                else if(casas [0][0] == 'X' && casas [1][1] == 'X' && casas [2][2] == 'X'){
                    cont_jogadas = 11; 
                }
                else if(casas [0][2] == 'X' && casas [1][1] == 'X' && casas [2][0] == 'X'){
                    cont_jogadas = 11; 
                }

                //Agora vamos fazer a nossas condições de vitória do Jogado O
                //Fazendo para as linhas
                if(casas [0][0] == 'O' && casas [0][1] == 'O' && casas [0][2] == 'O'){
                    cont_jogadas = 12; // desta maneira terminamos o jogo pois se vermos na linha de baixo veremos que o numero maximo de jogadas é igual a 9
                }                    
                else if(casas [1][0] == 'O' && casas [1][1] == 'O' && casas [1][2] == 'O'){
                    cont_jogadas = 12; 
                }
                else if(casas [2][0] == 'O' && casas [2][1] == 'O' && casas [2][2] == 'O'){
                    cont_jogadas = 12; 
                }
                //Agora fazendo para as colunas
                else if(casas [0][0] == 'O' && casas [1][0] == 'O' && casas [2][0] == 'O'){
                    cont_jogadas = 12; 
                }
                else if(casas [0][1] == 'O' && casas [1][1] == 'O' && casas [2][1] == 'O'){
                    cont_jogadas = 12; 
                }
                else if(casas [0][2] == 'O' && casas [1][2] == 'O' && casas [2][2] == 'O'){
                    cont_jogadas = 12; 
                }
                //Fazendo para as diagonais
                else if(casas [0][0] == 'O' && casas [1][1] == 'O' && casas [2][2] == 'O'){
                    cont_jogadas = 12; 
                }
                else if(casas [0][2] == 'O' && casas [1][1] == 'O' && casas [2][0] == 'O'){
                    cont_jogadas = 12; 
                }

            }while(cont_jogadas <= 9);
            tabuleiro(casas);
            if(cont_jogadas == 10){  
                printf(BOLD(GREEN("Jogo empatado"))"\n"); 
            }
            else if(cont_jogadas == 11){
                printf(BOLD(RED("Vencedor %s!!!"))"\n", jogador1.nome);
            }
            else if(cont_jogadas == 12){
                printf(BOLD(RED("Vencedor %s!!!"))"\n", jogador2.nome);
            }
            
            }
            printf("Digite qualquer tecla para continuar! ");
        }
        else if(op == 2){
            printf(BOLD(RED("\nERRO/Opção 2 não finalizada\n")));
            printf(BOLD(RED("Digite 'sair' para finalizar programa.\nOu 'voltar' para voltar ao menu.\n")));
            scanf("%s", escolha);
            if(strcmp(escolha,"sair") == 0){
                return 0;
            }
            else{
                goto inicio;
            }
        }
        else if(op == 3){ 
            if(nJogadores != 1 && nJogadores != 2){
                goto inicio;
            }         
            else if(nJogadores == 1 && vez%2 == 0){
                goto voltarJogo0;
            }
            else if(nJogadores == 2 && vez%2 == 0){
                goto voltarJogo1;
            }
            else
                goto voltarJogo2;
        }
        else{
            printf(BOLD(RED("\nERRO/Opção 4 não finalizada\n")));
            printf(BOLD(RED("Digite 'sair' para finalizar programa.\nOu 'voltar' para voltar ao menu.\n")));
            scanf("%s", escolha);
            if(strcmp(escolha,"sair") == 0){
                return 0;
            }
            else{
                goto inicio;
            }
        }
    return 0;
}


//Implementação das funções
void tabuleiro(char casas2 [3][3]){
    printf("\t   | 1 | 2 | 3 |  \n");
    printf("\t----------------\n");
    printf("\t 1 | %c | %c | %c |\n", casas2[0][0], casas2[0][1], casas2[0][2]);
    printf("\t----------------\n");
    printf("\t 2 | %c | %c | %c |\n", casas2 [1][0], casas2[1][1], casas2[1][2]);
    printf("\t----------------\n");
    printf("\t 3 | %c | %c | %c |\n", casas2[2][0], casas2[2][1], casas2[2][2]); 
    printf("\t----------------\n");
}

char *lerStringSeguramente(char *string, int tamanho){
	if(fgets(string, TAM, stdin) != NULL){
		int ultimoCaractere = strlen(string) - 1;
		if(string[ultimoCaractere] == '\n') {
			string[ultimoCaractere] = '\0';
		}
		return string;
	}
	return NULL;
}


int gerarAleatorio(int aleatorio){
    srand(time(NULL));
    aleatorio = (rand() % 9)+1;
    printf("%d \n", aleatorio);
    if(aleatorio == 1)
        aleatorio = 11;
    else if(aleatorio == 2)
        aleatorio = 12;
    else if(aleatorio == 3)
        aleatorio = 13;
    else if(aleatorio == 4)
        aleatorio = 21;
    else if(aleatorio == 5)
        aleatorio = 22;
    else if(aleatorio == 6)
        aleatorio = 23;
    else if(aleatorio == 7)
        aleatorio = 31;
    else if(aleatorio == 8)
        aleatorio = 32;
    else if(aleatorio == 9)
        aleatorio = 33;
    return aleatorio;
}
