#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct {
    int size;
    Node *ini;
    Node *end;
} Descritor;

void iniciarLista(Descritor *lista) {
    lista->ini = NULL;
    lista->end = NULL;
    lista->size = 0;
}

Node *criarNovoNo(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->next = NULL;
        newNode->prev = NULL;
    }
    return newNode;
}

void inserirInicio(Descritor *lista, int data) {
    Node *newNode = criarNovoNo(data);

    if (newNode != NULL) {
        newNode->next = lista->ini;
        if (lista->ini != NULL) {
            lista->ini->prev = newNode;
        } else {
            lista->end = newNode;
        }
        lista->ini = newNode;
        lista->size++;
    }
}

void inserirFim(Descritor *lista, int data) {
    Node *newNode = criarNovoNo(data);

    if (newNode != NULL) {
        newNode->prev = lista->end;
        if (lista->end != NULL) {
            lista->end->next = newNode;
        } else {
            lista->ini = newNode;
        }
        lista->end = newNode;
        lista->size++;
    }
}

void imprimirLista(Descritor *list) {
    Node *current = list->ini;

    printf("Lista: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void listaParaVetor(Descritor *list, int vetor[]) {
    Node *current = list->ini;
    int i = 0;

    while (current != NULL) {
        vetor[i] = current->data;
        current = current->next;
        i++;
    }
}

void removerNoPorDado(Descritor *list, int dado) {
    Node *current = list->ini;
    Node *prev = NULL;

    while (current != NULL) {
        if (current->data == dado) {
            if (prev == NULL) {
                list->ini = current->next;
                if (list->ini != NULL) {

                    list->ini->prev = NULL;
                } else {

                    list->end = NULL;
                }
            } else {
      
                prev->next = current->next;
                if (current->next != NULL) {

                    current->next->prev = prev;
                } else {
                    
                    list->end = prev;
                }
            }

            free(current);
            list->size--;
            break;
        }

        prev = current;
        current = current->next;
    }
}

void ordenarLista(Descritor *list) {
    if (list->size <= 1) {

        return;
    }

    int trocado;

    do {
        trocado = 0;
        Node *current = list->ini;

        while (current->next != NULL) {
            if (current->data > current->next->data) {
        
                int tempData = current->data;
                current->data = current->next->data;
                current->next->data = tempData;
                trocado = 1;
            }
            current = current->next;
        }
    } while (trocado);
}

void removerDuplicatasLista(Descritor *list) {
    Node *current = list->ini;

    while (current != NULL) {
        Node *runner = current->next;

        while (runner != NULL) {
            if (current->data == runner->data) {
                Node *temp = runner;

                if (runner->next != NULL) {
                    runner->next->prev = runner->prev;
                } else {
                    list->end = runner->prev;
                }

                if (runner->prev != NULL) {
                    runner->prev->next = runner->next;
                } else {
                    list->ini = runner->next;
                }

                runner = runner->next;
                free(temp);
                list->size--;
            } else {
                runner = runner->next;
            }
        }

        current = current->next;
    }
}

void removerPrimeiroElemento(Descritor *lista) {
    if (lista->ini != NULL) {
        Node *temp = lista->ini;

        if (lista->ini->next != NULL) {
            lista->ini = lista->ini->next;
            lista->ini->prev = NULL;
        } else {
            lista->ini = NULL;
            lista->end = NULL;
        }

        free(temp);
        lista->size--;
    }
}

void removerUltimoElemento(Descritor *lista) {
    if (lista->end != NULL) {
        Node *temp = lista->end;

        if (lista->end->prev != NULL) {
            lista->end = lista->end->prev;
            lista->end->next = NULL;
        } else {
            lista->ini = NULL;
            lista->end = NULL;
        }

        free(temp);
        lista->size--;
    }
}

void adicionarNoPosicao(Descritor *list, int dado, int posicao) {
    if (posicao < 0 || posicao > list->size) {
        return;
    }

    Node *newNode = criarNovoNo(dado);
    if (newNode == NULL) {
        return;
    }

    if (posicao == 0) {
        newNode->next = list->ini;

        if (list->ini != NULL) {
            list->ini->prev = newNode;
        } else {
            list->end = newNode;
        }

        list->ini = newNode;
    } else if (posicao == list->size) {

        newNode->prev = list->end;

        if (list->end != NULL) {
            list->end->next = newNode;
        } else {
            list->ini = newNode;
        }

        list->end = newNode;
    } else {
        // Adicionar no meio da lista
        Node *current = list->ini;

        for (int i = 0; i < posicao - 1; i++) {
            current = current->next;
        }

        newNode->prev = current;
        newNode->next = current->next;
        current->next->prev = newNode;
        current->next = newNode;
    }

    list->size++;
}

void inverterLista(Descritor *list) {
    Node *temp = NULL;
    Node *current = list->ini;

    while (current != NULL) {

        temp = current->prev;
        current->prev = current->next;
        current->next = temp;

        current = current->prev;
    }

    if (temp != NULL) {
        list->ini = temp->prev;
    }
    list->end = list->ini;
    while (list->end->next != NULL) {
        list->end = list->end->next;
    }
}

void removerNoPosicao(Descritor *list, int posicao) {
    if (posicao < 0 || posicao >= list->size) {
        
        return;
    }

    Node *current = list->ini;

    for (int i = 0; i < posicao; i++) {
        current = current->next;
    }

    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
      
        list->ini = current->next;
    }

    if (current->next != NULL) {
        current->next->prev = current->prev;
    } else {
       
        list->end = current->prev;
    }

    free(current);
    list->size--;
}

int contemTodos(Descritor *lista1, Descritor *lista2) {
    Node *current1 = lista1->ini;

    while (current1 != NULL) {
        int encontrado = 0;
        Node *current2 = lista2->ini;

        while (current2 != NULL) {

            if (current1->data == current2->data) {
                encontrado = 1;
                break;
            }

            current2 = current2->next;
        }

        if (!encontrado) {
            return 0;
        }

        current1 = current1->next;
    }

    Node *current2 = lista2->ini;

    while (current2 != NULL) {
        int encontrado = 0;
        Node *current1 = lista1->ini;

        while (current1 != NULL) {

            if (current2->data == current1->data) {
                encontrado = 1;
                break;
            }

            current1 = current1->next;
        }

        if (!encontrado) {
            return 0;
        }

        current2 = current2->next;
    }

    return 1; 
}

int compararListas(Descritor *lista1, Descritor *lista2) {
    Node *current1 = lista1->ini;
    Node *current2 = lista2->ini;

    while (current1 != NULL && current2 != NULL) {

        if (current1->data != current2->data) {
            return 0; 
        }

        current1 = current1->next;
        current2 = current2->next;
    }

    return 1; 
}

int encontrarMaiorElemento(Descritor *lista) {
    if (lista->ini == NULL) {
        return -1;
    }

    int maiorElemento = lista->ini->data;
    Node *current = lista->ini->next;

    while (current != NULL) {
        if (current->data > maiorElemento) {
            maiorElemento = current->data;
        }
        current = current->next;
    }

    return maiorElemento;
}

int encontrarMenorElemento(Descritor *lista) {
    if (lista->ini == NULL) {
        return -1;
    }

    int menorElemento = lista->ini->data;
    Node *current = lista->ini->next;

    while (current != NULL) {
        if (current->data < menorElemento) {
            menorElemento = current->data;
        }
        current = current->next;
    }

    return menorElemento;
}

void elementosDiferentes(Descritor *lista1, Descritor *lista2) {
    Node *current1 = lista1->ini;
    Node *current2 = lista2->ini;

    printf("Elementos diferentes: ");
    while (current1 != NULL && current2 != NULL) {
        if (current1->data != current2->data) {
            printf("%d ", current1->data);
        }

        current1 = current1->next;
        current2 = current2->next;
    }

    while (current1 != NULL) {
        printf("%d ", current1->data);
        current1 = current1->next;
    }

    while (current2 != NULL) {
        printf("%d ", current2->data);
        current2 = current2->next;
    }

    printf("\n");
}

void elementosIguais(Descritor *lista1, Descritor *lista2) {
    Node *current1 = lista1->ini;
    Node *current2 = lista2->ini;

    printf("Elementos iguais: ");
    while (current1 != NULL && current2 != NULL) {
        if (current1->data == current2->data) {
            printf("%d ", current1->data);
        }

        current1 = current1->next;
        current2 = current2->next;
    }

    printf("\n");
}

void juntarListas(Descritor *lista1, Descritor *lista2) {
    if (lista1->ini == NULL) {
        lista1->ini = lista2->ini;
    } else if (lista2->ini != NULL) {
    
        lista1->end->next = lista2->ini;
        lista2->ini->prev = lista1->end;
        lista1->end = lista2->end; 
    }

    lista1->size += lista2->size; 
    iniciarLista(lista2); 
}

void separarAposDadoEspecifico(Descritor *lista, int valor, Descritor *lista2) {
    Node *current = lista->ini;

    while (current != NULL && current->data != valor) {
        current = current->next;
    }

    if (current == NULL) {
        return;
    }

    if (current->next == NULL) {
        printf("O valor está no último nó da lista. Não há itens após o valor.\n");
        return;
    }

    lista->end = current;

    lista2->ini = current->next;
    lista2->ini->prev = NULL;

    lista2->end = lista->end; 

    current->next->prev = NULL;
    current->next = NULL;

    lista->size = lista->size - lista2->size;
    lista2->size = lista2->size + lista->size;
}

void separarAposPosicaoEspecifica(Descritor *lista, int posicao, Descritor *lista2) {
    if (posicao < 0 || posicao >= lista->size) {
        return;
    }

    Node *current = lista->ini;
    int i = 0;

    while (current != NULL && i < posicao) {
        current = current->next;
        i++;
    }

    if (current == NULL || current->next == NULL) {
        printf("Posição inválida ou não há itens após a posição.\n");
        return;
    }

    lista->end = current;

    lista2->ini = current->next;
    lista2->ini->prev = NULL;

    lista2->end = lista->end; 

    current->next->prev = NULL;
    current->next = NULL;

    lista->size = lista->size - lista2->size;
    lista2->size = lista2->size + lista->size;
}



/*
void iniciarLista(Descritor *lista);
Node *criarNovoNo(int data);
void inserirInicio(Descritor *lista, int data);
void inserirFim(Descritor *lista, int data);
void imprimirLista(Descritor *list);
void listaParaVetor(Descritor *list, int vetor[]);
void removerNoPorDado(Descritor *list, int dado);
void ordenarLista(Descritor *list);
void removerDuplicatasLista(Descritor *list);
void removerPrimeiroElemento(Descritor *lista);
void removerUltimoElemento(Descritor *lista);
void adicionarNoPosicao(Descritor *list, int dado, int posicao);
void inverterLista(Descritor *list);
void removerNoPosicao(Descritor *list, int posicao);
int contemTodos(Descritor *lista1, Descritor *lista2);
int compararListas(Descritor *lista1, Descritor *lista2);
int encontrarMaiorElemento(Descritor *lista);
int encontrarMenorElemento(Descritor *lista);
void elementosDiferentes(Descritor *lista1, Descritor *lista2);
void elementosIguais(Descritor *lista1, Descritor *lista2);
void juntarListas(Descritor *lista1, Descritor *lista2);
void separarAposDadoEspecifico(Descritor *lista, int valor, Descritor *lista2);
void separarAposPosicaoEspecifica(Descritor *lista, int posicao, Descritor *lista2);
*/

int main() {
   
    Descritor lista1, lista2;
    iniciarLista(&lista1);
    iniciarLista(&lista2);

    inserirInicio(&lista1, 10);
    inserirInicio(&lista1, 5);
    inserirInicio(&lista1, 15);
    inserirInicio(&lista1, 8);

    printf("Lista 1 antes da separação: ");
    imprimirLista(&lista1);

    int posicaoSeparacao = 1; 
    separarAposPosicaoEspecifica(&lista1, posicaoSeparacao, &lista2);

    printf("Lista 1 após a separação: ");
    imprimirLista(&lista1);

    printf("Lista 2 após a separação: ");
    imprimirLista(&lista2);

    return 0;
}