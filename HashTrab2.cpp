
// Anderson Baltar Marcus
// @Alu201512958

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct linha{
    int chave;
    char status;
};

typedef struct linha Linha;

struct hash{
    Linha *d;
    int m;
};

typedef struct hash Hash;




Hash *criarHash(int m){
    Hash * h = (Hash *) malloc(sizeof(Hash));
    h->m = m;

    h->d = (Linha *) malloc(sizeof(Linha) * m);
    int i;
    for(i=0; i < h->m; i++){
        h->d[i].status = 'L';
        h->d[i].chave = 0;
    }

    return h;
}

int h_(int x, int m, int j){
 return ((x % m)+j)%m;
}

int h_quad(int x, int m, int k, int ant){

    if(k == 0){
        return x % m;
    }

    return (ant + k)% m;


}

void inserirLinear(Hash * h, int chave){

    int j = 0;
    int idx;

    int sair = 1;
    do{
        idx = h_(chave, h->m, j);

        if(h->d[idx].status == 'L'){
            h->d[idx].status = 'O';
            h->d[idx].chave = chave;
            sair = 0;
        }

        if(j >= h->m){
            printf("Hash ta cheia, não consegui inserir o %d\n",chave);
            sair = 0;
        }

        j++;
    }while(sair);
}


void inserirQuad(Hash * h, int chave){

    int k = 0; // Quantidade de colisões
    int idx;
    int ant = 0;
    int sair = 1;
    do{
        idx = h_quad(chave, h->m, k, ant);
        ant = idx;

        if(h->d[idx].status == 'L'){
            h->d[idx].status = 'O';
            h->d[idx].chave = chave;
            sair = 0;
        }

        if(k >= h->m){
            printf("Hash ta cheia, não consegui inserir o %d\n",chave);
            sair = 0;
        }

        k++;
    }while(sair);
}

void removerLinear(Hash * h, int chave){
    int j = 0; //numero de colisões
    int idx;

    int sair = 1;
    do{
        idx = h_(chave, h->m, j);

        if(h->d[idx].chave == chave){
            h->d[idx].status = 'L';
            h->d[idx].chave = 0;
            sair = 0;
        }

        if(h->d[idx].status == 'L' || j >= h->m){
            printf("Não encontre a chave %d\n",chave);
            sair = 0;
        }

        j++;
    }while(sair);
}




void imprime(Hash * h){
    int i;

    for(i=0; i < h->m; i++){

        printf("%d | %c | %d |\n", i, h->d[i].status, h->d[i].chave);
    }
}


int main()
{
	setlocale(LC_ALL, "Portuguese");
    printf("\nTENTATIVA LINEAR\n");
	Hash *h = criarHash(5);

    inserirLinear(h, 9);
    inserirLinear(h, 14);
    inserirLinear(h, 19);
    inserirLinear(h, 24);
    inserirLinear(h, 29);
    removerLinear(h,29);
    inserirLinear(h, 30);

  	imprime(h);

 	printf("\nTENTATIVA QUADRATICA\n");
    Hash *hq = criarHash(5);

    inserirQuad(hq, 1);
    inserirQuad(hq, 6);
    inserirQuad(hq, 11);
    inserirQuad(hq, 5);
    inserirQuad(hq, 7);

    imprime(hq);

    return 0;
}
