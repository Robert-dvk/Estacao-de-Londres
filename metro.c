#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct estacao{ // struct para representar os vértices do grafo;
    char nome[100];
    int ativa;
    int visitado;
    struct estacao *proxEstacao; // percorrer a lista de estacões;
    struct aresta *proxAresta; // struct que faz a ligação das estações;
};

struct aresta{ // struct que representa as arestas do grafo;
    int tempo; // peso das arestas;
    char linha[100];
    struct estacao *estacao;
    struct aresta *proxAresta;
};

typedef struct estacao estacao;
typedef struct aresta aresta;

estacao *inserir_estacao(estacao *estacoes, char nome[], int ativa, int visitado) { // Função que insere uma estação no início da lista de estações;
    estacao *novo = (estacao*) malloc(sizeof(estacao));
    if(novo){ // verifica se novo foi alocado na memória;
        strcpy(novo->nome, nome);
        novo->ativa = ativa;
        novo->visitado = visitado;
        novo->proxAresta = NULL;
        if(estacoes){ // verifica se a lista de estações não esta vazia;
            novo->proxEstacao = estacoes;
            return novo;
        } else { // Verifica se é o primeiro elemento da lista;
            novo->proxEstacao = NULL;
            return novo;
        }
    }
    return NULL; // caso não tenha alocado nenhum elemento, retorna nulo;
}
void buscaDestinos(estacao *estacoes, char origem[], char destino[], int tempo, char linha[]){ // Inicializa a busca das estações origem e destino;
    estacao *aux = estacoes;
    estacao *guardaOrigem;
    estacao *guardaDestino;
    while(aux){
        if(strcmp(aux->nome, origem) == 0){ // verifica se a estação origem existe;
            guardaOrigem = aux; // guarda origem;
            break;
        }
        aux = aux->proxEstacao;
    }
    aux = estacoes;
    while(aux){
        if(strcmp(aux->nome, destino) == 0){ // verifica se a estação destino existe;
            guardaDestino = aux; // guarda destino;
            break;
        }
        aux = aux->proxEstacao;
    }
    inserir_aresta(guardaOrigem, guardaDestino, tempo, linha); // Chama a função para fazer as ligações das estações;
}

void inserir_aresta(estacao *estacaoIni, estacao *estacao_Dest, int tempo, char linha[]){
    aresta *nova_aresta = (aresta*) malloc(sizeof(aresta)); // aloca a linha na memória;
    if(nova_aresta){ // verifica se foi alocada a linha na memória;
        nova_aresta->tempo = tempo; // define o tempo de viagem entre a origem e destino;
        strcpy(nova_aresta->linha, linha);
        nova_aresta->estacao = estacao_Dest; // define o apontamento da aresta para a estação destino;
        nova_aresta->proxAresta = estacaoIni->proxAresta; // define o apontamento da aresta para 
        estacaoIni->proxAresta = NULL;
        if(estacaoIni->proxAresta == NULL){
            estacaoIni->proxAresta = nova_aresta;
        } else {
            estacao *aux = estacaoIni->proxAresta;
            while(aux->proxAresta != NULL){
                aux = aux->proxAresta;
            }
            aux->proxAresta = nova_aresta;
        }
    }
}

estacao *buscaEstacaoEspecifica(estacao *estacoes, char nome[], int op){ // Função que busca uma estação específica;
    estacao *aux = estacoes;
    estacao *guardaEstacao;
    while(aux != NULL){ // executa o laço em quanto a estação existir;
        if(strcmp(aux->nome, nome) == 0){ // Verifica se o nome da estação digitado existe na lista;
            guardaEstacao = aux; // guarda as informações da estação;
            break;
        } else { // se não existir
            guardaEstacao = NULL; //  guarada nulo 
        }
        aux = aux->proxEstacao;
    }
    // Abaixo ocorrem verificações de ações do menu do usuário;
    if(op == 2){
        if(guardaEstacao){ // verifica se "guardaEstacao" não esta nula
            exibeEstacaoEspecifica(guardaEstacao); // chama a função para exibir as informações da estação específica;
        } else {
            return NULL; // se "guardaEstacao" esta nulo, não toma nenhuma ação e volta ao menu;
        }
    } else if(op == 5 || op == 6){
        if(guardaEstacao){
            return guardaEstacao;
        } else {
            return NULL;
        }
    }
}

void exibeEstacaoEspecifica(estacao *estacaoSelecionada){ // função que printa uma estação específica na tela;
    if(estacaoSelecionada->ativa == 1){ // verifica se a estação esta ativa;
        printf("Nome: %s\n", estacaoSelecionada->nome);
        printf("Estação ativa\n");
        printf("Conexões: \n");
        aresta *conexao = estacaoSelecionada->proxAresta;
        while (conexao) { // percorre a lista de conexões(arestas) e printa as linhas que uma estação tem;
            printf("Linha: %s\n", conexao->linha);
            printf("%s, Tempo: %d minutos \n", conexao->estacao->nome, conexao->tempo);
            conexao = conexao->proxAresta;
            printf("\n");
        }
    } else { // se não estiver exobe mensagem de erro;
        printf("A estação %s está desativada.\n", estacaoSelecionada->nome);
    }
    printf("\n");
}
// função para fazer a listagem completa das estações
void exibir_estacoes(estacao *estacoes) {
    estacao *aux;
    for (aux = estacoes; aux != NULL ; aux = aux->proxEstacao) {
        printf("---------Estação %s\n", aux->nome);
        if(aux->ativa == 1)
            printf("Atualmente ativa\n");
        else 
            printf("Atualmente desativada\n");
        printf("Conexões: \n");
        aresta *conexao = aux->proxAresta;
        while (conexao != NULL) {
            printf("Linha: %s\n", conexao->linha);
            printf("%s, Tempo: %d minutos \n", conexao->estacao->nome, conexao->tempo);
            conexao = conexao->proxAresta;
            printf("\n");
        }
        printf("\n");
    }
}
// Função que remove as conexões entre duas estações no caso da inserção de uma nova estação.
void remove_conexao(estacao *estacao1, estacao *estacao2){
    estacao *aux = estacao1;
    aresta *conexao = aux->proxAresta;
    // avança entre as conexões até encontrar a estação de destino
    while(conexao->estacao != estacao2){ 
        conexao = conexao->proxAresta;
    }
    if(estacao1->proxAresta = conexao->estacao){ 
        estacao1->proxAresta = conexao->proxAresta;
    } else {
        aresta *aux1 = aux->proxAresta;
        while(aux1->proxAresta != conexao){ // percorre as conexoes até encontrar a estação a ser removida;
            aux1 = aux->proxAresta;
        }
        aux1->proxAresta = conexao->proxAresta;
        free(conexao);
    }
}

void remover_estacao(estacao *estacoes, char nome[]){
    estacao *atual = estacoes;
    estacao *anterior = NULL;
    while(atual != NULL){ // percorre todas as estações da lista
        if(strcmp(atual->nome, nome) == 0){ 
            if(anterior == NULL){ // verifica se a estação é a primeira
                estacoes = atual->proxEstacao;
            } else {
                anterior->proxEstacao = atual->proxEstacao;
            }
            free(atual);
            printf("Estação %s removida com sucesso\n", nome);
            return;
        }
        anterior = atual;
        atual = atual->proxEstacao; // avança a lista até que a condição seja verdadeira
    }
    printf("Estação %s não encontrada\n", nome);
}

estacao *ativa_desativa(estacao *estacoes, char nome[], int op){ // função que ativa ou desativa uma estação
    estacao *aux = estacoes;
    int altera;
    if(op == 1)
        altera = 0;
    else
        altera = 1;
    while(aux != NULL){ // percorre a lista de estações;
        if(strcmp(aux->nome, nome) == 0){ //se o nome da estação passado por parâmetro existir;
            aux->ativa = altera; // ativa ou desativa a estação;
            break;
        }
        aux = aux->proxEstacao;
    }
    return estacoes; // retorna a lista de estações;
}
// função para alterar o tempo de viagem entre duas estações adjacentes
estacao *alteraTempo(estacao *estacoes, char origem[], char destino[]){
    estacao *aux = estacoes;
    estacao *guardaOrigem, *guardaDestino;
    int tempo;
    //percorre para encontrar a origem
    while(aux != NULL){
        if(strcmp(aux->nome, origem) == 0){
            guardaOrigem = aux;
            break;
        }
        aux = aux->proxEstacao;
    }
    aresta *conexoes = guardaOrigem->proxAresta;
    //percorre as conexões para verificar se o destino está entre as conexões da origem
    while(conexoes){
        if(strcmp(conexoes->estacao->nome, destino) == 0){
            guardaDestino = conexoes->estacao;
            printf("Tempo atual: %d\n", conexoes->tempo);
            printf("Digite o novo tempo: ");
            scanf("%d", &tempo);
            conexoes->tempo = tempo;
            break;
        } else {
            return NULL;
        }
        conexoes = conexoes->proxAresta;
    }
    //caso as condições sejam atendidas, altera o tempo nos dois caminhos (ida e volta)
    aux = estacoes;
    guardaOrigem = NULL;
    guardaDestino = NULL;
    conexoes = NULL;
    while(aux != NULL){
        if(strcmp(aux->nome, destino) == 0){
            guardaDestino = aux;
            break;
        }
        aux = aux->proxEstacao;
    }
    conexoes = guardaDestino->proxAresta;
    while(conexoes){
        if(strcmp(conexoes->estacao->nome, origem) == 0){
            guardaOrigem = conexoes->estacao;
            conexoes->tempo = tempo;
            break;
        }
        conexoes = conexoes->proxAresta;
    }
    return estacoes;
}

void estacoesLinha(estacao *estacoes, char nome_estacao[], char linha[], int op) { // Função para buscar as estações vizinhas da estação atual;
    estacao *origem = buscaEstacaoEspecifica(estacoes, nome_estacao, op);
    char estacaoDestino[100];
    if(!origem){ // verifica se a estação escolhida não existe;
        printf("Estação de origem não encontrada!\n");
        return;
    } 
    printf("-----------------------------\n");
    estacao *estacao_atual = origem;
    while (estacao_atual) { // percorre as conexões da estação atual;
        aresta *conexao = estacao_atual->proxAresta;
        if(strcmp(conexao->linha, linha) != 0) { // Se conexão na linha escolhida não existir, vai pra próxima aresta;
            conexao = conexao->proxAresta;
        } else { // Se exixtir conexão, pega o nome da estação destino;
            strcpy(estacaoDestino, estacao_atual->nome);
            break;
        }
        estacao_atual = estacao_atual->proxEstacao;
    }
    printf("A estação na linha %s mais próxima da estação %s é %s\n", linha, origem->nome, estacaoDestino); // printa a linha e a estação vizinha da atual
    printf("-----------------------------\n");
}

void buscaRotas(estacao *estacoes, char nome_estacao_origem[100], char nome_estacao_final[100], int op) {
    estacao *origem = buscaEstacaoEspecifica(estacoes, nome_estacao_origem, op);
    estacao *destino = buscaEstacaoEspecifica(estacoes, nome_estacao_final, op);
    //verifica se existe a estação de origem ou destino
    if (!origem || !destino) {
        printf("Estação de origem ou destino não encontrada!");
        return;
    }
    origem->visitado = 1;
    //define a origem como visitada.
    estacao *aux = origem;
    aresta *conexoes = origem->proxAresta;
    //percorre as estações até chegar no destino
    while (aux != destino) {
        //percorre as conexoes de cada estacao
        while (conexoes) {
            estacao *prox = conexoes->estacao;
            //testa se uma estacao foi visitada. caso não, entra e seta como visitada.
            if (prox->visitado == 0) {
                printf("%s ->", prox->nome);
                prox->visitado = 1;
                aux = prox;
                conexoes = prox->proxAresta;
                break;
            }
        conexoes = conexoes->proxAresta;
        }
    }
  return;
}

int main(){
    system("clear");
    struct estacao *estacoes = NULL;
    //insere todas as estações definidas como ativas;
    estacoes = inserir_estacao(estacoes, "South Kensington",  1, 0);
    estacoes = inserir_estacao(estacoes, "Victoria",          1, 0);
    estacoes = inserir_estacao(estacoes, "Westminster",       1, 0);
    estacoes = inserir_estacao(estacoes, "Embankment",        1, 0);
    estacoes = inserir_estacao(estacoes, "Blackfriars",       1, 0);
    estacoes = inserir_estacao(estacoes, "Monument",          1, 0);
    estacoes = inserir_estacao(estacoes, "Tower Hill",        1, 0);
    estacoes = inserir_estacao(estacoes, "Liverpool Street",  1, 0);
    estacoes = inserir_estacao(estacoes, "Farringdon",        1, 0);
    estacoes = inserir_estacao(estacoes, "King's Cross E St Pancras International", 1, 0);
    estacoes = inserir_estacao(estacoes, "Warren",            1, 0);
    estacoes = inserir_estacao(estacoes, "Edgware Road",      1, 0);
    estacoes = inserir_estacao(estacoes, "Paddington",        1, 0);
    estacoes = inserir_estacao(estacoes, "Notting Hill Gate", 1, 0);
    estacoes = inserir_estacao(estacoes, "Waterloo",          1, 0);
    estacoes = inserir_estacao(estacoes, "Green Park",        1, 0);
    estacoes = inserir_estacao(estacoes, "Bond Street",       1, 0);
    estacoes = inserir_estacao(estacoes, "Baker Street",      1, 0);
    estacoes = inserir_estacao(estacoes, "Oxford Circus",     1, 0);
    estacoes = inserir_estacao(estacoes, "Charing Cross",     1, 0);
    estacoes = inserir_estacao(estacoes, "Piccadilly Circus", 1, 0);
    
    //manda as informações para a função que vai armazenar o endereço de memória das estações em structs
    //auxiliares para fazer a conexão com as arestas;
    buscaDestinos(estacoes, "South Kensington",   "Victoria",            3, "Amarela");
    buscaDestinos(estacoes, "South Kensington",   "Notting Hill Gate",   11, "Amarela");
   
    buscaDestinos(estacoes, "Victoria",           "South Kensington",    3, "Amarela");
    buscaDestinos(estacoes, "Victoria",           "Westminster",         4, "Amarela");
    buscaDestinos(estacoes, "Victoria",           "Green Park",          6, "Azul"   );
   
    buscaDestinos(estacoes, "Westminster",        "Victoria",            4, "Amarela");
    buscaDestinos(estacoes, "Westminster",        "Embankment",          2, "Amarela");
    buscaDestinos(estacoes, "Westminster",        "Green Park",          8, "Cinza"  );
    buscaDestinos(estacoes, "Westminster",        "Waterloo",            3, "Cinza"  );
   
    buscaDestinos(estacoes, "Waterloo",           "Westminster",         3, "Cinza"  );
    buscaDestinos(estacoes, "Waterloo",           "Embankment",          5, "Marrom" );
   
    buscaDestinos(estacoes, "Embankment",         "Blackfriars",         7, "Amarela");
    buscaDestinos(estacoes, "Embankment",         "Westminster",         2, "Amarela");
    buscaDestinos(estacoes, "Embankment",         "Waterloo",            5, "Marrom" );
    buscaDestinos(estacoes, "Embankment",         "Charing Cross",       4, "Marrom" );
   
    buscaDestinos(estacoes, "Blackfriars",        "Embankment",          7, "Amarela");
    buscaDestinos(estacoes, "Blackfriars",        "Monument",            12, "Amarela");
   
    buscaDestinos(estacoes, "Monument",           "Tower Hill",          2, "Amarela");
    buscaDestinos(estacoes, "Monument",           "Blackfriars",         12, "Amarela");
   
    buscaDestinos(estacoes, "Tower Hill",         "Monument",            2, "Amarela");
    buscaDestinos(estacoes, "Tower Hill",         "Liverpool Street",    10, "Amarela");
   
    buscaDestinos(estacoes, "Liverpool Street",   "Tower Hill",          10, "Amarela");
    buscaDestinos(estacoes, "Liverpool Street",   "Farringdon",          9, "Amarela");
   
    buscaDestinos(estacoes, "Farringdon",         "King's Cross E St Pancras International",    3, "Amarela");
    buscaDestinos(estacoes, "Farringdon",         "Liverpool Street",    9, "Amarela");
   
   
    buscaDestinos(estacoes, "King's Cross E St Pancras International",         "Farringdon",    3, "Amarela");
    buscaDestinos(estacoes, "King's Cross E St Pancras International",         "Warren",        2, "Amarela");
   
    buscaDestinos(estacoes, "Warren",             "King's Cross E St Pancras International",    2, "Amarela");
    buscaDestinos(estacoes, "Warren",             "Baker Street",        6, "Amarela");
    buscaDestinos(estacoes, "Warren",             "Oxford Circus",       8, "Azul");
   
    buscaDestinos(estacoes, "Baker Street",       "Warren",              6, "Amarela");
    buscaDestinos(estacoes, "Baker Street",       "Edgware Road",        7, "Amarela");
    buscaDestinos(estacoes, "Baker Street",       "Bond Street",         3, "Cinza");
    buscaDestinos(estacoes, "Baker Street",       "Oxford Circus",       9, "Marrom");
   
    buscaDestinos(estacoes, "Edgware Road",       "Baker Street",        7, "Amarela");
    buscaDestinos(estacoes, "Edgware Road",       "Paddington",          4, "Amarela");
   
    buscaDestinos(estacoes, "Paddington",         "Edgware Road",        4, "Amarela");
    buscaDestinos(estacoes, "Paddington",         "Notting Hill Gate",   5, "Amarela");
   
    buscaDestinos(estacoes, "Notting Hill Gate",  "Paddington",          5, "Amarela");
    buscaDestinos(estacoes, "Notting Hill Gate",  "South Kensington",    11, "Amarela");
   
    buscaDestinos(estacoes, "Green Park",  "Victoria",          6, "Azul");
    buscaDestinos(estacoes, "Green Park",  "Oxford Circus",     5, "Azul");
    buscaDestinos(estacoes, "Green Park",  "Bond Street",       5, "Cinza");
    buscaDestinos(estacoes, "Green Park",  "Westminster",       8, "Cinza");
   
    buscaDestinos(estacoes, "Bond Street",  "Green Park",       5, "Cinza");
    buscaDestinos(estacoes, "Bond Street",  "Baker Street",     3, "Cinza");
   
    buscaDestinos(estacoes, "Oxford Circus",  "Green Park",     5, "Azul");
    buscaDestinos(estacoes, "Oxford Circus",  "Warren",         8, "Azul");
    buscaDestinos(estacoes, "Oxford Circus",  "Baker Street",   9, "Marrom");
    buscaDestinos(estacoes, "Oxford Circus",     "Piccadilly Circus",     6, "Marrom");
   
    buscaDestinos(estacoes, "Piccadilly Circus", "Oxford Circus",         6, "Marrom");
    buscaDestinos(estacoes, "Piccadilly Circus", "Charing Cross",         3, "Marrom");
   
    buscaDestinos(estacoes, "Charing Cross", "Piccadilly Circus",         3, "Marrom");
    buscaDestinos(estacoes, "Charing Cross", "Embankment",         4, "Marrom");

    int op, opEdita;
    char continua, nome_estacao_origem[100], nome_estacao_final[100], nome_estacao[100], linha[100];
    estacao *auxTempo = estacoes;
    estacao *auxAtiva = estacoes;
    do {
        //menu de opções
        system("clear");
        printf("-------------Bem vindo ao metrô de Londres!-------------\n\n");
        printf("Escolha uma das opções do menu abaixo.\n");
        printf("Digite 1 para listar todas as estações e suas conexões diretas.\n");
        printf("Digite 2 para selecionar uma estação e exibir suas conexões diretas, ou inserir uma nova estação.\n");
        printf("Digite 3 para remover uma estação.\n");
        printf("Digite 4 para editar informações uma estação.\n");
        printf("Digite 5 para buscar rotas entre estações.\n");
        printf("Digite 6 para buscar linhas que dão acesso a uma linha escolhida.\n");
        scanf("%d", &op);
        switch(op) {
            case 1:
                system("clear");
                printf("-------------Estações de Londres e suas principais conexões-------------\n\n");
                exibir_estacoes(estacoes);
            break;
            case 2:
                system("clear");
                printf("Caso digite uma estação não encontrada, terá a opção de inserir.\n");
                printf("Digite o nome da estação que deseja buscar:\n");
                getchar();
                gets(nome_estacao);
                estacao *aux = estacoes;
                aux = buscaEstacaoEspecifica(estacoes, nome_estacao, op);
                if(!aux){
                    char insere;
                    printf("Estação não encontrada. Deseja inserir? s/n: ");
                    scanf("%c", &insere);
                    if(insere == 's'){
                        printf("\nA nova estação ficará localizada entre duas estações a serem escolhidas.\n");
                        printf("Digite a primeira estação: ");
                        getchar();
                        gets(nome_estacao_origem);
                        printf("Digite a estação final: ");
                        gets(nome_estacao_final);
                        estacao *aux = estacoes;
                        estacao *guardaOrigem = NULL, *guardaDestino = NULL;
                        while(aux != NULL){
                            if(strcmp(aux->nome, nome_estacao_origem) == 0){
                                guardaOrigem = aux;
                                break;
                            } else {
                                guardaOrigem = NULL;
                            }
                            aux = aux->proxEstacao;
                        }
                        aresta *conexoes = guardaOrigem->proxAresta;
                        while(conexoes){
                            if(strcmp(conexoes->estacao->nome, nome_estacao_final) == 0){
                                guardaDestino = conexoes->estacao;
                                break;
                            }
                            conexoes = conexoes->proxAresta;
                        }
                        //entre a linha 421 e 439 são feitos testes para testar se as estações são adjacentes;
                        if(guardaDestino != NULL && guardaOrigem != NULL){ //caso elas sejam, a nova estação ficara entre elas
                            char linha[100];
                            int tempoOrigem, tempoDestino;
                            printf("Perfeito, as estações %s e %s são adjacentes. A sua estação ficará entre elas.\n\n", guardaOrigem->nome, conexoes->estacao->nome);
                            estacoes = inserir_estacao(estacoes, nome_estacao, 1, 0);
                            //como a linha é só entre adjacentes, não é necessário testes de validação, então é só pegar da conexao direto
                            strcpy(linha, conexoes->linha);
                            //o tempo é setado entre a estação de origem e a nova estação
                            printf("Digite o tempo de viagem entre %s e %s: ", nome_estacao_origem, nome_estacao);
                            scanf("%d", &tempoOrigem);
                            while(tempoOrigem >= conexoes->tempo){ 
                                printf("O tempo entre a estação origem e a nova estação deve ser menor que: %d\n", conexoes->tempo);
                                printf("Digite o tempo de viagem entre %s e %s: ", nome_estacao_origem, nome_estacao);
                                scanf("%d", &tempoOrigem);
                            }
                            if(tempoOrigem < conexoes->tempo){
                                //o tempo entre a nova estação e o destino é o tempo original - o tempo setado para a nova origem
                                tempoDestino = conexoes->tempo - tempoOrigem;
                                //as funções são chamadas duas vezes para remover as conexoes ida e volta
                                remove_conexao(guardaDestino, guardaOrigem);
                                remove_conexao(guardaOrigem, guardaDestino);
                                // e aqui são chamadas as funções para fazer as conexoes ida e volta entre a nova origem e o novo destino
                                buscaDestinos(estacoes, nome_estacao, nome_estacao_origem, tempoOrigem, linha);
                                buscaDestinos(estacoes, nome_estacao_origem, nome_estacao, tempoOrigem, linha);
                                buscaDestinos(estacoes, nome_estacao, nome_estacao_final, tempoDestino, linha);
                                buscaDestinos(estacoes, nome_estacao_final, nome_estacao, tempoDestino, linha);
                                printf("\nA estação e suas conexões foram inseridas com sucesso!\n\n");
                            }
                        } else {
                            printf("As estações não são adjacentes ou não foram encontradas.");
                        }
                    }
                }
            break;
            case 3:
                system("clear");
                printf("Digite o nome da estação que deseja remover: ");
                getchar();
                gets(nome_estacao);
                estacao *atual = estacoes;
                estacao *e1 = NULL, *e2 = NULL, *e3 = NULL, *e4 = NULL, *e5 = NULL, *e6 = NULL, *e7 = NULL, *e8 = NULL;
                int contConexoes = 0, existe = 0, contAmarela = 0, contAzul = 0, contCinza = 0, contMarrom = 0;
                //percorre as estações para verificar se a estação escolhida existe
                while (atual != NULL) {
                    if (strcmp(atual->nome, nome_estacao) == 0) {
                        existe = 1;
                        break;
                    }
                    atual = atual->proxEstacao;
                }
                if (!existe) {
                    printf("Estação %s não encontrada\n", nome_estacao);
                    break;
                }
                atual = estacoes;
                int atribui = 0, tempo = 0;
                char linha[100];
                //perorre todas as conexões da estação e conta quantas conexoes ela tem.
                while (atual != NULL) {
                    aresta *conexao = atual->proxAresta;
                    while (conexao) {
                        if (strcmp(conexao->estacao->nome, nome_estacao) == 0) {
                            contConexoes++;
                        }
                        conexao = conexao->proxAresta;
                    }
                    atual = atual->proxEstacao;
                }
                //caso ela tenha somente duas conexoes é tratada no loop abaixo.
                atual = estacoes;
                while(atual){
                    aresta *conexao = atual->proxAresta;
                    aresta *anterior = NULL;
                    while (conexao) {
                        if (strcmp(conexao->estacao->nome, nome_estacao) == 0) {
                            if(contConexoes <= 2){
                                if (anterior == NULL) {
                                    atual->proxAresta = conexao->proxAresta;
                                } else {
                                    anterior->proxAresta = conexao->proxAresta;
                                }
                                if (atribui == 0) {// cria uma flag para não sobreescrever a struct
                                    //atribui a origem em uma struct auxiliar salvando o tempo e a linha
                                    e1 = atual;
                                    strcpy(linha, conexao->linha);
                                    tempo += conexao->tempo;
                                    atribui = 1;
                                } else if (e1 != atual && e2 == NULL) {
                                    //armazena o destino em outra struct auxiliar e soma o tempo
                                    e2 = atual;
                                    tempo += conexao->tempo;
                                    if(strcmp(e1->proxAresta->linha, e2->proxAresta->linha) != 0){
                                        // no caso de waterloo são duas conexoes em linhas diferentes, por isso essa validação
                                        e1 = NULL;
                                    }
                                }
                                free(conexao);
                                break;
                            } else {
                                //caso sejam mais de duas conexões, é contado quantas conexões possuem cada linha
                                if(strcmp(atual->proxAresta->linha, "Amarela")){
                                    contAmarela++;
                                } else if(strcmp(atual->proxAresta->linha, "Azul")){
                                    contAzul++;
                                } else if(strcmp(atual->proxAresta->linha, "Cinza")){
                                    contCinza++;
                                } else if(strcmp(atual->proxAresta->linha, "Marrom")){
                                    contMarrom++;
                                }
                            }
                        }
                        anterior = conexao;
                        conexao = conexao->proxAresta;
                    }
                    atual = atual->proxEstacao;
                }
                atual = estacoes;
                atribui = 0;
                //caso sejam mais de duas conexoes, cada linha vai ser tratada de uma forma
                if(contConexoes > 2){
                    while(atual){
                        aresta *conexao = atual->proxAresta;
                        aresta *anterior = NULL;
                        while (conexao) {
                            if (strcmp(conexao->estacao->nome, nome_estacao) == 0) {
                                if (anterior == NULL) {
                                    atual->proxAresta = conexao->proxAresta;
                                } else {
                                    anterior->proxAresta = conexao->proxAresta;
                                }
                                //em geral, o processo é o mesmo que para duas conexoes, com a diferença de que cria variaveis diferentes
                                //para cada cor
                                if(contAmarela > 0){
                                    if(strcmp(conexao->linha, "Amarela") == 0){
                                        if(atribui == 0){
                                            e1 = atual;
                                            strcpy(linha, conexao->linha);
                                            tempo += conexao->tempo;
                                            atribui = 1;
                                            } else if (e1 != atual && e2 == NULL) {
                                                tempo += conexao->tempo;
                                                e2 = atual;
                                            }
                                            contAmarela--;
                                            break;
                                        }
                                    } else if(contAzul > 0){
                                        if(strcmp(atual->proxAresta->linha, "Azul") == 0){
                                            if(atribui == 0){
                                                e3 = atual;
                                                strcpy(linha, conexao->linha);
                                                tempo += conexao->tempo;
                                                atribui = 1;
                                                } else if (e3 != atual && e4 == NULL) {
                                                    tempo += conexao->tempo;
                                                    e4 = atual;
                                                }
                                                contAzul--;
                                            break;
                                        }
                                    } else if(contCinza > 0){
                                        if(strcmp(atual->proxAresta->linha, "Cinza") == 0){
                                            if(atribui == 0){
                                                e5 = atual;
                                                strcpy(linha, conexao->linha);
                                                tempo += conexao->tempo;
                                                atribui = 1;
                                                } else if (e5 != atual && e6 == NULL) {
                                                    tempo += conexao->tempo;
                                                    e6 = atual;
                                                }
                                                contCinza--;
                                            break;
                                        }
                                    } else if(contMarrom > 0){
                                        if(strcmp(atual->proxAresta->linha, "Marrom") == 0){
                                            if(atribui == 0){
                                                e7 = atual;
                                                strcpy(linha, conexao->linha);
                                                tempo += conexao->tempo;
                                                atribui = 1;
                                            } else if (e7 != atual && e8 == NULL) {
                                                tempo += atual->proxAresta->tempo;
                                                e8 = atual;
                                            }
                                            contMarrom--;
                                            break;
                                        }
                                    }
                                    free(conexao);
                                }
                                anterior = conexao;
                                conexao = conexao->proxAresta;
                            }
                        atual = atual->proxEstacao;
                    }
                }
                //após remover as conexoes, a estação é removida.
                printf("Conexões com a estação %s removidas com sucesso\n", nome_estacao);
                remover_estacao(estacoes, nome_estacao);
                //aqui é testado se as variaveis possuem valor, caso sim, é refeito as conexoes. Caso somente
                //uma delas tenha valor, a estação ficara sem a conexao e a linha acabará nela.
                if(e1 != NULL && e2 != NULL){
                    buscaDestinos(estacoes, e1->nome, e2->nome, tempo, linha);
                    buscaDestinos(estacoes, e2->nome, e1->nome, tempo, linha);
                } else if(e3 != NULL && e4 != NULL){
                    buscaDestinos(estacoes, e3->nome, e4->nome, tempo, linha);
                    buscaDestinos(estacoes, e4->nome, e3->nome, tempo, linha);
                } else if(e5 != NULL && e6 != NULL){
                    buscaDestinos(estacoes, e5->nome, e6->nome, tempo, linha);
                    buscaDestinos(estacoes, e6->nome, e5->nome, tempo, linha);
                } else if(e7 != NULL && e8 != NULL){
                    buscaDestinos(estacoes, e7->nome, e8->nome, tempo, linha);
                    buscaDestinos(estacoes, e8->nome, e7->nome, tempo, linha);
                }
            break;
            case 4:
                system("clear");
                printf("Escolha uma opção abaixo!\n");
                printf("Digite 1 para desativar uma estação.\n");
                printf("Digite 2 para ativar uma estação desativada.\n");
                printf("Digite 3 para alterar o tempo entre duas estações.\n");
                scanf("%d", &opEdita);
                switch(opEdita){
                    case 1:
                        printf("Digite o nome da estação que deseja desativar: \n");
                        getchar();
                        gets(nome_estacao);
                        auxAtiva = ativa_desativa(estacoes, nome_estacao, opEdita);
                        if(auxAtiva){
                            printf("\nEstação desativada com sucesso!\n");
                        } else {
                            printf("\nEstação não encontrada!\n");
                        }
                    break;
                    case 2:
                        printf("Digite o nome da estação que deseja reativar: \n");
                        getchar();
                        gets(nome_estacao);
                        auxAtiva = ativa_desativa(estacoes, nome_estacao, opEdita);
                        if(auxAtiva){
                            printf("\nEstação reativada com sucesso!\n");
                        } else {
                            printf("\nEstação não encontrada!\n");
                        }
                    break;
                    case 3:
                        printf("Para alterar o tempo de viagem entre duas estações, será necessário digitar o nome de estações que possuem conexões entre si.");
                        printf("\nDigite o nome da estação de origem: ");
                        getchar();
                        gets(nome_estacao_origem);
                        printf("Digite o nome da estação destino: ");
                        gets(nome_estacao_final);
                        auxTempo = alteraTempo(estacoes, nome_estacao_origem, nome_estacao_final);
                        if(auxTempo){
                            printf("\nTempo de viagem alterado com sucesso!\n");
                        } else {
                            printf("\nEstação não encontrada!\n");
                        }
                    break;
                    default:
                        printf("Opção inválida!");
                    break;
                }
                break;
                case 5:
                    system("clear");
                    printf("Digite a estação de origem: ");
                    getchar();
                    gets(nome_estacao_origem);
                    printf("Digite a estação destino: ");
                    gets(nome_estacao_final);
                    buscaRotas(estacoes, nome_estacao_origem, nome_estacao_final, op);
                break;
                case 6:
                    system("clear");
                    printf("Digite a estação de origem: ");
                    getchar();
                    gets(nome_estacao);
                    printf("Escolha uma linha entre Amarela, Azul, Cinza e Marrom: ");
                    gets(linha);
                    estacoesLinha(estacoes, nome_estacao, linha, op);
                break;
            default:
                printf("Opção inválida!");
            break;
        }
        printf("Deseja continuar? s/n ");
        scanf("%s", &continua);
    } while (continua == 's');
    return 0;
}