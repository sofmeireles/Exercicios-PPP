#define MAX_TEXTO 3000
#define TAM_LINHA 80

struct Dados{
    struct Palavra *palavra;
    struct Dados *back;
    struct Dados *next;
};

struct Palavra{
    char palavra[100];
    int ocorrencias;
};

void strtobase_u8(char *dest, const char *orig);

void print_lista();

void colocar_ordenado(char* palavra);

void inicializa();

bool ler_texto(char *ptexto);

void libertaLista();



