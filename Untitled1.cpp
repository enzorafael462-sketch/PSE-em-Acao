#include <stdio.h>
#include <string.h>

#define MAX 100

#define PLANEJADA 1
#define REALIZADA 2
#define CANCELADA 3

struct Acao {
    int codigo;
    char escola[60];
    int tema;
    char descricao[100];
    int dia, mes, ano;
    int previstos;
    int efetivos;
    int situacao;
};

struct Acao acoes[MAX];
int total = 0;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int lerInteiro(char mensagem[], int minimo, int maximo) {
    int valor, lidos;

    while (1) {
        printf("%s", mensagem);
        lidos = scanf("%d", &valor);
        limparBuffer();

        if (lidos != 1) {
            printf("  ERRO: digite apenas numeros.\n");
        } else if (valor < minimo || valor > maximo) {
            printf("  ERRO: digite um valor entre %d e %d.\n", minimo, maximo);
        } else {
            return valor;
        }
    }
}

int dataValida(int dia, int mes, int ano) {
    int diasDoMes;

    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        diasDoMes = 30;
    } else if (mes == 2) {

        if ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0) {
            diasDoMes = 29;
        } else {
            diasDoMes = 28;
        }
    } else {
        diasDoMes = 31;
    }

    if (dia >= 1 && dia <= diasDoMes) {
        return 1;
    }
    return 0;
}

int buscarPosicao(int codigo) {
    int i;
    for (i = 0; i < total; i++) {
        if (acoes[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void mostrarTemas() {
    printf("  1 - Alimentacao saudavel\n");
    printf("  2 - Atividades fisicas\n");
    printf("  3 - Saude mental\n");
    printf("  4 - Vacinacao\n");
    printf("  5 - Saude bucal\n");
    printf("  6 - Prevencao da violencia\n");
}

void imprimirTema(int tema) {
    switch (tema) {
        case 1: printf("Alimentacao saudavel"); break;
        case 2: printf("Atividades fisicas"); break;
        case 3: printf("Saude mental"); break;
        case 4: printf("Vacinacao"); break;
        case 5: printf("Saude bucal"); break;
        case 6: printf("Prevencao da violencia"); break;
    }
}

void imprimirSituacao(int situacao) {
    if (situacao == PLANEJADA) {
        printf("Planejada");
    } else if (situacao == REALIZADA) {
        printf("Realizada");
    } else {
        printf("Cancelada");
    }
}

void exibirAcao(int i) {
    printf("------------------------------------------\n");
    printf("Codigo    : %d\n", acoes[i].codigo);
    printf("Escola    : %s\n", acoes[i].escola);
    printf("Tema      : ");
    imprimirTema(acoes[i].tema);
    printf("\n");
    printf("Descricao : %s\n", acoes[i].descricao);
    printf("Data      : %02d/%02d/%d\n", acoes[i].dia, acoes[i].mes, acoes[i].ano);
    printf("Previstos : %d\n", acoes[i].previstos);
    printf("Efetivos  : %d\n", acoes[i].efetivos);
    printf("Situacao  : ");
    imprimirSituacao(acoes[i].situacao);
    printf("\n");
}

void cadastrarAcao() {
    int i = total;

    printf("\n=== CADASTRAR ACAO ===\n");

    if (total >= MAX) {
        printf("ERRO: limite de %d acoes atingido.\n", MAX);
        return;
    }

    acoes[i].codigo = total + 1;
    printf("Codigo: %d\n", acoes[i].codigo);

    printf("Nome da escola: ");
    scanf(" %59[^\n]", acoes[i].escola);
    limparBuffer();

    printf("Temas:\n");
    mostrarTemas();
    acoes[i].tema = lerInteiro("Escolha o tema (1-6): ", 1, 6);

    printf("Descricao da atividade: ");
    scanf(" %99[^\n]", acoes[i].descricao);
    limparBuffer();

    do {
        acoes[i].dia = lerInteiro("Dia (1-31): ", 1, 31);
        acoes[i].mes = lerInteiro("Mes (1-12): ", 1, 12);
        acoes[i].ano = lerInteiro("Ano (2000-2100): ", 2000, 2100);

        if (dataValida(acoes[i].dia, acoes[i].mes, acoes[i].ano) == 0) {
            printf("  ERRO: essa data nao existe. Digite novamente.\n");
        }
    } while (dataValida(acoes[i].dia, acoes[i].mes, acoes[i].ano) == 0);

    acoes[i].previstos = lerInteiro("Participantes previstos (1-5000): ", 1, 5000);
    acoes[i].efetivos = 0;
    acoes[i].situacao = PLANEJADA;

    total++;
    printf("Acao cadastrada! Situacao inicial: Planejada.\n");
}

void listarAcoes() {
    int i;

    printf("\n=== LISTA DE ACOES ===\n");

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    for (i = 0; i < total; i++) {
        exibirAcao(i);
    }
    printf("------------------------------------------\n");
    printf("Total: %d acao(oes).\n", total);
}

void pesquisarAcoes() {
    int opcao, i, encontrados = 0;
    int codigo, posicao, tema;
    char nome[60];

    printf("\n=== PESQUISAR ACOES ===\n");

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    printf("1 - Por codigo\n");
    printf("2 - Por escola\n");
    printf("3 - Por tema\n");
    opcao = lerInteiro("Escolha (1-3): ", 1, 3);

    if (opcao == 1) {
        codigo = lerInteiro("Digite o codigo: ", 1, MAX);
        posicao = buscarPosicao(codigo);
        if (posicao != -1) {
            exibirAcao(posicao);
            encontrados = 1;
        }
    } else if (opcao == 2) {
        printf("Digite o nome da escola: ");
        scanf(" %59[^\n]", nome);
        limparBuffer();
        for (i = 0; i < total; i++) {
            if (strcmp(acoes[i].escola, nome) == 0) {
                exibirAcao(i);
                encontrados++;
            }
        }
    } else {
        mostrarTemas();
        tema = lerInteiro("Escolha o tema (1-6): ", 1, 6);
        for (i = 0; i < total; i++) {
            if (acoes[i].tema == tema) {
                exibirAcao(i);
                encontrados++;
            }
        }
    }

    if (encontrados == 0) {
        printf("Nenhuma acao encontrada.\n");
    } else {
        printf("------------------------------------------\n");
        printf("%d acao(oes) encontrada(s).\n", encontrados);
    }
}

void atualizarSituacao() {
    int codigo, posicao, nova;

    printf("\n=== ATUALIZAR SITUACAO ===\n");

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    codigo = lerInteiro("Codigo da acao: ", 1, MAX);
    posicao = buscarPosicao(codigo);

    if (posicao == -1) {
        printf("ERRO: acao nao encontrada.\n");
        return;
    }

    exibirAcao(posicao);
    printf("1 - Planejada\n2 - Realizada\n3 - Cancelada\n");
    nova = lerInteiro("Nova situacao (1-3): ", 1, 3);

    acoes[posicao].situacao = nova;

    if (nova != REALIZADA) {
        acoes[posicao].efetivos = 0;
    }

    printf("Situacao atualizada!\n");
    if (nova == REALIZADA) {
        printf("Use a opcao 5 para registrar os participantes efetivos.\n");
    }
}

void registrarParticipantes() {
    int codigo, posicao;

    printf("\n=== REGISTRAR PARTICIPANTES EFETIVOS ===\n");

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    codigo = lerInteiro("Codigo da acao: ", 1, MAX);
    posicao = buscarPosicao(codigo);

    if (posicao == -1) {
        printf("ERRO: acao nao encontrada.\n");
        return;
    }

    if (acoes[posicao].situacao != REALIZADA) {
        printf("ERRO: so e possivel registrar em acoes Realizadas.\n");
        printf("Use a opcao 4 para mudar a situacao antes.\n");
        return;
    }

    acoes[posicao].efetivos = lerInteiro("Participantes efetivos (0-5000): ", 0, 5000);
    printf("Participantes registrados!\n");
}

void gerarResumo() {
    int i;
    int planejadas = 0, realizadas = 0, canceladas = 0;
    int porTema[7] = {0, 0, 0, 0, 0, 0, 0};
    int somaEfetivos = 0;

    printf("\n=== RESUMO GERAL ===\n");

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    for (i = 0; i < total; i++) {
        porTema[acoes[i].tema]++;

        if (acoes[i].situacao == PLANEJADA) {
            planejadas++;
        } else if (acoes[i].situacao == REALIZADA) {
            realizadas++;
            somaEfetivos = somaEfetivos + acoes[i].efetivos;
        } else {
            canceladas++;
        }
    }

    printf("Total de acoes: %d\n", total);
    printf("  Planejadas: %d (%.1f%%)\n", planejadas, 100.0 * planejadas / total);
    printf("  Realizadas: %d (%.1f%%)\n", realizadas, 100.0 * realizadas / total);
    printf("  Canceladas: %d (%.1f%%)\n", canceladas, 100.0 * canceladas / total);

    printf("\nAcoes por tema:\n");
    for (i = 1; i <= 6; i++) {
        printf("  ");
        imprimirTema(i);
        printf(": %d\n", porTema[i]);
    }

    printf("\nParticipantes efetivos (acoes realizadas): %d\n", somaEfetivos);
    if (realizadas > 0) {
        printf("Media por acao realizada: %.1f\n", (float) somaEfetivos / realizadas);
    }
}

void exibirMenu() {
    printf("\n==============================\n");
    printf("   PSE EM ACAO\n");
    printf("==============================\n");
    printf("1 - Cadastrar acao\n");
    printf("2 - Listar acoes\n");
    printf("3 - Pesquisar acoes\n");
    printf("4 - Atualizar situacao\n");
    printf("5 - Registrar participantes efetivos\n");
    printf("6 - Resumo geral\n");
    printf("0 - Sair\n");
    printf("==============================\n");
}

int main() {
    int opcao;

    do {
        exibirMenu();
        opcao = lerInteiro("Escolha uma opcao: ", 0, 6);

        switch (opcao) {
            case 1: cadastrarAcao(); break;
            case 2: listarAcoes(); break;
            case 3: pesquisarAcoes(); break;
            case 4: atualizarSituacao(); break;
            case 5: registrarParticipantes(); break;
            case 6: gerarResumo(); break;
            case 0: printf("\nEncerrando. Ate logo!\n"); break;
        }
    } while (opcao != 0);

    return 0;
}
