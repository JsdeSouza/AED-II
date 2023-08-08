#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Evento {
    char data_hora[17];
    char descricao[141];
    char prioridade[11];
    struct Evento* proximo;
};

typedef struct Evento Evento;

Evento* criarEvento(char data_hora[], char descricao[], char prioridade[]) {
    Evento* novo_evento = (Evento*)malloc(sizeof(Evento));
    if (novo_evento != NULL) {
        strcpy(novo_evento->data_hora, data_hora);
        strcpy(novo_evento->descricao, descricao);
        strcpy(novo_evento->prioridade, prioridade);
        novo_evento->proximo = NULL;
    }
    return novo_evento;
}

void agendar_evento(Evento** agenda, char data_hora[], char descricao[], char prioridade[]) {
    Evento* novo_evento = criarEvento(data_hora, descricao, prioridade);
    if (novo_evento == NULL) {
        printf("Erro: Não foi possível agendar o evento.\n");
        return;
    }

    if (*agenda == NULL || strcmp(data_hora, (*agenda)->data_hora) < 0) {
        novo_evento->proximo = *agenda;
        *agenda = novo_evento;
    } else {
        Evento* atual = *agenda;
        while (atual->proximo != NULL && strcmp(data_hora, atual->proximo->data_hora) >= 0) {
            atual = atual->proximo;
        }
        novo_evento->proximo = atual->proximo;
        atual->proximo = novo_evento;
    }

    printf("Evento agendado com sucesso!\n");
}

Evento* proximo_evento(Evento* agenda) {
    if (agenda == NULL) {
        printf("Agenda vazia.\n");
        return NULL;
    }

    return agenda;
}

Evento* finalizar_evento(Evento** agenda) {
    if (*agenda == NULL) {
        printf("Agenda vazia. Nenhum evento para finalizar.\n");
        return NULL;
    }

    Evento* evento_removido = *agenda;
    *agenda = (*agenda)->proximo;
    evento_removido->proximo = NULL;
    return evento_removido;
}

int quantificar_evento(Evento* agenda) {
    int quantidade = 0;
    Evento* atual = agenda;
    while (atual != NULL) {
        quantidade++;
        atual = atual->proximo;
    }
    return quantidade;
}

void liberar_evento(Evento* evento) {
    free(evento);
}

int main() {
    Evento* agenda = NULL;

    int opcao;
    char data_hora[17];
    char descricao[141];
    char prioridade[11];

    while (1) {
        printf("\nEscolha a operacao:\n");
        printf("1 - Agendar evento\n");
        printf("2 - Proximo evento\n");
        printf("3 - Finalizar evento\n");
        printf("4 - Quantidade de eventos\n");
        printf("5 - Modificar evento\n");
        printf("0 - Sair\n");

        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 0:
                printf("Saindo...\n");
                liberar_evento(agenda);
                return 0;

            case 1:
                printf("Informe a data e hora (dd/mm/aaaa hh:mm): ");
                fgets(data_hora, sizeof(data_hora), stdin);
                data_hora[strlen(data_hora) - 1] = '\0';
                printf("Informe a descricao (ate 140 caracteres): ");
                fgets(descricao, sizeof(descricao), stdin);
                descricao[strlen(descricao) - 1] = '\0';
                printf("Informe a prioridade (ate 10 caracteres): ");
                fgets(prioridade, sizeof(prioridade), stdin);
                prioridade[strlen(prioridade) - 1] = '\0';
                agendar_evento(&agenda, data_hora, descricao, prioridade);
                break;

            case 2:
                {
                    Evento* prox_evento = proximo_evento(agenda);
                    if (prox_evento != NULL) {
                        printf("Proximo evento:\n");
                        printf("Data e hora: %s\n", prox_evento->data_hora);
                        printf("Descricao: %s\n", prox_evento->descricao);
                        printf("Prioridade: %s\n", prox_evento->prioridade);
                    }
                }
                break;
            case 3:
                {
                    Evento* evento_finalizado = finalizar_evento(&agenda);
                    if (evento_finalizado != NULL) {
                        printf("Evento finalizado:\n");
                        printf("Data e hora: %s\n", evento_finalizado->data_hora);
                        printf("Descricao: %s\n", evento_finalizado->descricao);
                        printf("Prioridade: %s\n", evento_finalizado->prioridade);
                        liberar_evento(evento_finalizado);
                    }
                }
                break;

            case 4:
            
                printf("Quantidade de eventos agendados: %d\n", quantificar_evento(agenda));
                break;

            case 5:
                {
                    int indice;
                    printf("Informe o indice do evento a ser modificado: ");
                    scanf("%d", &indice);
                    getchar(); 
                    if (indice <= 0 || indice > quantificar_evento(agenda)) {
                        printf("Indice invalido. Nao existe um evento nesse indice.\n");
                    } else {
                        printf("Informe a nova data e hora (dd/mm/aaaa hh:mm): ");
                        fgets(data_hora, sizeof(data_hora), stdin);
                        data_hora[strlen(data_hora) - 1] = '\0';
                        printf("Informe a nova descricao (ate 140 caracteres): ");
                        fgets(descricao, sizeof(descricao), stdin);
                        descricao[strlen(descricao) - 1] = '\0';
                        printf("Informe a nova prioridade (ate 10 caracteres): ");
                        fgets(prioridade, sizeof(prioridade), stdin);
                        prioridade[strlen(prioridade) - 1] = '\0';

                        Evento* atual = agenda;
                        for (int i = 1; i < indice; i++) {
                            atual = atual->proximo;
                        }

                        strcpy(atual->data_hora, data_hora);
                        strcpy(atual->descricao, descricao);
                        strcpy(atual->prioridade, prioridade);

                        printf("Evento modificado com sucesso!\n");
                    }
                }
                break;
            default:
                printf("Opcao invalida. Escolha uma opcao valida.\n");
        }
    }
}
