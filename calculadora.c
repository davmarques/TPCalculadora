#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAXPILHA 100
#define MAXEXPR 100

// Estrutura da pilha
typedef struct {
    double itens[MAXPILHA];
    int topo;
} Pilha;

// Inicializa a pilha
void inicializar(Pilha *p) {
    p->topo = -1;
}

// Verifica se a pilha está vazia
int estaVazia(Pilha *p) {
    return (p->topo == -1);
}

// Verifica se a pilha está cheia
int estaCheia(Pilha *p) {
    return (p->topo == MAXPILHA - 1);
}

// Empilha um elemento
void empilhar(Pilha *p, double valor) {
    if (estaCheia(p)) {
        printf("A pilha está cheia!\n");
        exit(1);
    } else {
        p->itens[++(p->topo)] = valor;
    }
}

// Desempilha um elemento
double desempilhar(Pilha *p) {
    if (estaVazia(p)) {
        printf("A pilha está vazia!\n");
        exit(1);
    } else {
        return p->itens[(p->topo)--];
    }
}

// Funções para operações matemáticas
double somar(double a, double b) { return a + b; }
double subtrair(double a, double b) { return a - b; }
double multiplicar(double a, double b) { return a * b; }
double dividir(double a, double b) { 
    if (b == 0) {
        printf("Divisão por zero!\n");
        exit(1);
    }
    return a / b; 
}
double potencia(double a, double b) { return pow(a, b); }
double raizQuadrada(double a) { return sqrt(a); }
double seno(double a) { return sin(a * M_PI / 180); }
double cosseno(double a) { return cos(a * M_PI / 180); }
double tangente(double a) { return tan(a * M_PI / 180); }
double logaritmo(double a) { return log10(a); }

// Avaliação da expressão pós-fixada
double avaliarPosfixa(char* expr) {
    Pilha pilha;
    inicializar(&pilha);
    char *token = strtok(expr, " ");

    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            empilhar(&pilha, atof(token));
        } else {
            double val1, val2;
            if (strcmp(token, "+") == 0) {
                val2 = desempilhar(&pilha);
                val1 = desempilhar(&pilha);
                empilhar(&pilha, somar(val1, val2));
            } else if (strcmp(token, "-") == 0) {
                val2 = desempilhar(&pilha);
                val1 = desempilhar(&pilha);
                empilhar(&pilha, subtrair(val1, val2));
            } else if (strcmp(token, "*") == 0) {
                val2 = desempilhar(&pilha);
                val1 = desempilhar(&pilha);
                empilhar(&pilha, multiplicar(val1, val2));
            } else if (strcmp(token, "/") == 0) {
                val2 = desempilhar(&pilha);
                val1 = desempilhar(&pilha);
                empilhar(&pilha, dividir(val1, val2));
            } else if (strcmp(token, "^") == 0) {
                val2 = desempilhar(&pilha);
                val1 = desempilhar(&pilha);
                empilhar(&pilha, potencia(val1, val2));
            } else if (strcmp(token, "raiz") == 0) {
                val1 = desempilhar(&pilha);
                empilhar(&pilha, raizQuadrada(val1));
            } else if (strcmp(token, "sen") == 0) {
                val1 = desempilhar(&pilha);
                empilhar(&pilha, seno(val1));
            } else if (strcmp(token, "cos") == 0) {
                val1 = desempilhar(&pilha);
                empilhar(&pilha, cosseno(val1));
            } else if (strcmp(token, "tg") == 0) {
                val1 = desempilhar(&pilha);
                empilhar(&pilha, tangente(val1));
            } else if (strcmp(token, "log") == 0) {
                val1 = desempilhar(&pilha);
                empilhar(&pilha, logaritmo(val1));
            }
        }
        token = strtok(NULL, " ");
    }

    return desempilhar(&pilha);
}

int main() {
    char expr[MAXEXPR];

    printf("Digite uma expressão pós-fixada: ");
    fgets(expr, MAXEXPR, stdin);
    expr[strcspn(expr, "\n")] = '\0';  // Remove o caractere de nova linha

    double resultado = avaliarPosfixa(expr);
    printf("O resultado é: %f\n", resultado);

    return 0;
}
