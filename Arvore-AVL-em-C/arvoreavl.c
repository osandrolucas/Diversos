#include <stdio.h>
#include <stdlib.h>

typedef struct tp_no {
	int num;
	int alt;
	struct tp_no *esq;
	struct tp_no *dir;
} tp_no;

int altura(tp_no *arv) {
    int altesq, altdir;

    if (arv == NULL)
      return 0;

    altesq = altura(arv->esq);
    altdir = altura(arv->dir);

    if (altesq > altdir){
        altesq++;
        return altesq;
    }
    else{
        altdir++;
        return altdir;
    }

}

void leelem(int *n){
    printf("Entre com um elemento: ");
    scanf("%d", n);
}

int vazia(tp_no *arv) {

    return (arv == NULL);
}

tp_no* criano(){
    tp_no *no;

    no = (tp_no*) malloc(sizeof(struct tp_no));
    if (no == NULL) {
        printf("Erro: criacao do no");
        return NULL;
    }
	else
        return no;
}

void checarAltura(tp_no *arv){
    if (!vazia(arv)) {
        arv->alt = altura(arv->esq) - altura(arv->dir);
        checarAltura(arv->esq);
        checarAltura(arv->dir);
    }
}

tp_no* RotacaoEsquerda(tp_no *pai){
    tp_no *filho;

    filho = pai->dir;
    pai->dir = filho->esq;
    filho->esq = pai;
    filho->alt = altura(filho->esq) - altura(filho->dir);
    pai->alt = altura(pai->esq) - altura(pai->dir);
    return filho;
}

tp_no* RotacaoDireita(tp_no *pai){
    tp_no *filho;

    filho = pai->esq;
    pai->esq = filho->dir;
    filho->dir = pai;
    filho->alt = altura(filho->esq) - altura(filho->dir);
    pai->alt = altura(pai->esq) - altura(pai->dir);
    return filho;
}

tp_no* RotacaoDuplaEsquerda(tp_no *pai){
    pai->dir = RotacaoDireita(pai->dir);
    pai = RotacaoEsquerda(pai);
    return(pai);
}

tp_no* RotacaoDuplaDireita(tp_no *pai){
    pai->esq = RotacaoEsquerda(pai->esq);
    pai = RotacaoDireita(pai);
    return(pai);
}

int checarBalanco(tp_no *arv){

    if(arv->alt == 2){
        if(arv->esq->alt < 0){
            printf("\n");
            listar(arv);
            printf("rotacao dupla a direita.");
            printf("\n");
            return(3);
        }else{
            printf("\n");
            listar(arv);
            printf("Girar pra direita.\n");
            printf("\n");
            return(1);
        }
    }

    else{
        if(arv->alt == -2){
            if(arv->dir->alt > 0){
                printf("\n");
                listar(arv);
                printf("rotacao dupla a esquerda.");
                printf("\n");
                return(4);
            }else{
                printf("\n");
                listar(arv);
                printf("Girar pra esquerda.\n");
                printf("\n");
                return(2);
            }
        }
    }

    return 0;
}

void inserir(tp_no **arv, int elem) {
    int resposta = 0;

    if (vazia(*arv)) {
        *arv = criano();
        (*arv)->num = elem;
        (*arv)->alt = 0;
        (*arv)->esq = (*arv)->dir = NULL;
    }

    else{
        if (elem < (*arv)->num){
            inserir(&(*arv)->esq, elem);
        }
        else{
            if (elem > (*arv)->num){
                inserir(&(*arv)->dir, elem);
            }
        }
    }

    checarAltura(*arv);
    resposta = checarBalanco(*arv);
    if(resposta == 1){
        (*arv) = RotacaoDireita(*arv);
        listar(*arv);
        return;
    }

    if(resposta == 2){
        (*arv) = RotacaoEsquerda(*arv);
        listar(*arv);
        return;
    }

    if(resposta == 3){
        (*arv) = RotacaoDuplaDireita(*arv);
        listar(*arv);
        return;
    }

    if(resposta == 4){
        (*arv) = RotacaoDuplaEsquerda(*arv);
        listar(*arv);
        return;
    }

}

void listar(tp_no *arv) {

    if (!vazia(arv)) {
        printf("elemento: %d ", arv->num);
        printf("Indice: %d\n", arv->alt);
        listar(arv->esq);
        listar(arv->dir);
    }
}

tp_no *pesquisar(tp_no *arv, tp_no **pai, int elem) {

    *pai = arv;

    while (!vazia(arv)) {
        if (elem == arv->num)
            return arv;
        else {
            *pai = arv;
            if (elem < arv->num)
                arv = arv->esq;
            else
                arv = arv->dir;
        }
    }

    return NULL;
}

void excluir(tp_no **raiz, tp_no *no, tp_no *paino) {
    tp_no *pai, *filho;
    int resposta = 0;

    // Se o no possui dois filhos
	if ((no->esq != NULL) && (no->dir != NULL)) {
        pai = no;
        filho = pai->dir;
		while (filho->esq != NULL){ // Busca pelo maior
            pai = filho;
			filho = filho->esq;
        }
		// Prepara a eliminacao pelos ifs abaixo
		no->num = filho->num;
		paino = pai;
		no = filho;
	}

	// Se o no n�o possui filhos, ou seja, e uma folha
	if ((no->esq == NULL) && (no->dir == NULL)) {
        if (no == *raiz) // Elimina a raiz
            *raiz = NULL;
        else {
            if (paino == *raiz) // Elemina folha esquerda da raiz
                if (paino->esq == no)
                    (*raiz)->esq = NULL;
                else            // Elemina folha direita da raiz
                    (*raiz)->dir = NULL;
            else
                if (paino->esq == no) // Elemina folha esquerda
                    paino->esq = NULL;
                else                  // Elemina folha direita
                    paino->dir = NULL;
        }
	}

	else
        // Se o no possui apenas filho a esquerda
        if ((no->esq != NULL) && (no->dir == NULL)) {
            if (no == *raiz) { // Eh a raiz
                (*raiz)->num = no->esq->num;
                no = (*raiz)->esq;
                (*raiz)->esq = NULL;
            }
            else
                if (paino->esq == no)
                    paino->esq = no->esq;
                else
                    paino->dir = no->esq;
        }

    else
        // Se no possui apenas filho a direita
        if ((no->esq == NULL) && (no->dir != NULL)) {
            if (no == *raiz) { // Eh a raiz
                (*raiz)->num = no->dir->num;
                no = (*raiz)->dir;
                (*raiz)->dir = NULL;
            }
            else
                if (paino->esq == no)
                    paino->esq = no->dir;
                else
                    paino->dir = no->dir;
    }

    if(*raiz == NULL){
        printf("Arvore apagada.\n");
    }

    else{
        (*raiz)->alt = altura((*raiz)->esq) - altura((*raiz)->dir);
        resposta = checarBalanco(*raiz);
    }

    if(resposta == 1){
        (*raiz) = RotacaoDireita(*raiz);
        checarAltura(*raiz);
        return;
    }

    if(resposta == 2){
        (*raiz) = RotacaoEsquerda(*raiz);
        checarAltura(*raiz);
        return;
    }

    if(resposta == 3){
        (*raiz) = RotacaoDuplaDireita(*raiz);
        checarAltura(*raiz);
        return;
    }

    if(resposta == 4){
        (*raiz) = RotacaoDuplaEsquerda(*raiz);
        checarAltura(*raiz);
        return;
    }

    free(no);
}

void apagar(tp_no *arv) {

    if (!vazia(arv)) {
        apagar(arv->esq);
        apagar(arv->dir);
        free(arv);
    }
}

void main() {
	tp_no *raiz = NULL, *no, *pai;
	char op;
	int elem;

	do {

        printf("\n[I]ncluir, [L]istar, [E]xcluir, [P]esquisar elemento, [A]pagar arvore, [S]air: ");
        fflush(stdin); scanf("%c", &op);
        switch (op) {

        case 'i':
        case 'I':
            leelem(&elem);
            inserir(&raiz, elem);
            break;

        case 'l':
        case 'L':
            if(!vazia(raiz)){
                listar(raiz);
            }
            else{
                printf("Arvore vazia.\n");
            }
            break;

        case 'e':
        case 'E':
            if(!vazia(raiz)){
                leelem(&elem);
                if ((no = pesquisar(raiz, &pai, elem)) != NULL) {
                    listar(raiz);
                    printf("\nNumero %d encontrado e com pai %d\n", no->num, pai->num);
                    excluir(&raiz, no, pai);
                    listar(raiz);
                }
                else {
                    listar(raiz);
                    printf("\nNumero nao encontrado\n");
                }
            }
            else{
                printf("Arvore vazia.\n");
            }
            break;

        case 'p':
        case 'P':
            if(!vazia(raiz)){
                leelem(&elem);
                if ((no = pesquisar(raiz, &pai, elem)) != NULL) {
                    printf("\nNumero %d encontrado\n", no->num);
                }
                else{
                    printf("\nNumero nao encontrando na arvore.\n");
                }

            }
            else{
                printf("Arvore vazia.\n");
            }
            break;

        case 'a':
        case 'A':
                apagar(raiz);
                raiz = NULL;
                printf("arvore apagada.\n");
            break;

        case 's':
        case 'S':
            apagar(raiz);
            printf("Fim do programa");
            break;

        default:
            printf("Opcao invalida\n");
        }

    } while (op != 's' && op != 'S');
// Cria uma �rvore bin�ria de busca utilizando recursividade
// Percorre a �rvore em ordem com a utliza��o de recursividade

#include <stdio.h>
#include <stdlib.h>

typedef struct tp_no {
	int num;
	int alt;
	struct tp_no *esq;
	struct tp_no *dir;
} tp_no;

int altura(tp_no *arv) {
    int altesq, altdir;

    if (arv == NULL)
      return 0;

    altesq = altura(arv->esq);
    altdir = altura(arv->dir);

    if (altesq > altdir){
        altesq++;
        return altesq;
    }
    else{
        altdir++;
        return altdir;
    }

}

void leelem(int *n){
    printf("Entre com um elemento: ");
    scanf("%d", n);
}

int vazia(tp_no *arv) {

    return (arv == NULL);
}

tp_no* criano(){
    tp_no *no;

    no = (tp_no*) malloc(sizeof(struct tp_no));
    if (no == NULL) {
        printf("Erro: criacao do no");
        return NULL;
    }
	else
        return no;
}

void checarAltura(tp_no *arv){
    if (!vazia(arv)) {
        arv->alt = altura(arv->esq) - altura(arv->dir);
        checarAltura(arv->esq);
        checarAltura(arv->dir);
    }
}

tp_no* RotacaoEsquerda(tp_no *pai){
    tp_no *filho;

    filho = pai->dir;
    pai->dir = filho->esq;
    filho->esq = pai;
    filho->alt = altura(filho->esq) - altura(filho->dir);
    pai->alt = altura(pai->esq) - altura(pai->dir);
    return filho;
}

tp_no* RotacaoDireita(tp_no *pai){
    tp_no *filho;

    filho = pai->esq;
    pai->esq = filho->dir;
    filho->dir = pai;
    filho->alt = altura(filho->esq) - altura(filho->dir);
    pai->alt = altura(pai->esq) - altura(pai->dir);
    return filho;
}

tp_no* RotacaoDuplaEsquerda(tp_no *pai){
    pai->dir = RotacaoDireita(pai->dir);
    pai = RotacaoEsquerda(pai);
    return(pai);
}

tp_no* RotacaoDuplaDireita(tp_no *pai){
    pai->esq = RotacaoEsquerda(pai->esq);
    pai = RotacaoDireita(pai);
    return(pai);
}

int checarBalanco(tp_no *arv){

    if(arv->alt == 2){
        if(arv->esq->alt < 0){
            printf("\n");
            listar(arv);
            printf("rotacao dupla a direita.");
            printf("\n");
            return(3);
        }else{
            printf("\n");
            listar(arv);
            printf("Girar pra direita.\n");
            printf("\n");
            return(1);
        }
    }

    else{
        if(arv->alt == -2){
            if(arv->dir->alt > 0){
                printf("\n");
                listar(arv);
                printf("rotacao dupla a esquerda.");
                printf("\n");
                return(4);
            }else{
                printf("\n");
                listar(arv);
                printf("Girar pra esquerda.\n");
                printf("\n");
                return(2);
            }
        }
    }

    return 0;
}

void inserir(tp_no **arv, int elem) {
    int resposta = 0;

    if (vazia(*arv)) {
        *arv = criano();
        (*arv)->num = elem;
        (*arv)->alt = 0;
        (*arv)->esq = (*arv)->dir = NULL;
    }

    else{
        if (elem < (*arv)->num){
            inserir(&(*arv)->esq, elem);
        }
        else{
            if (elem > (*arv)->num){
                inserir(&(*arv)->dir, elem);
            }
        }
    }

    checarAltura(*arv);
    resposta = checarBalanco(*arv);
    if(resposta == 1){
        (*arv) = RotacaoDireita(*arv);
        listar(*arv);
        return;
    }

    if(resposta == 2){
        (*arv) = RotacaoEsquerda(*arv);
        listar(*arv);
        return;
    }

    if(resposta == 3){
        (*arv) = RotacaoDuplaDireita(*arv);
        listar(*arv);
        return;
    }

    if(resposta == 4){
        (*arv) = RotacaoDuplaEsquerda(*arv);
        listar(*arv);
        return;
    }

}

void listar(tp_no *arv) {

    if (!vazia(arv)) {
        printf("elemento: %d ", arv->num);
        printf("Indice: %d\n", arv->alt);
        listar(arv->esq);
        listar(arv->dir);
    }
}

tp_no *pesquisar(tp_no *arv, tp_no **pai, int elem) {

    *pai = arv;

    while (!vazia(arv)) {
        if (elem == arv->num)
            return arv;
        else {
            *pai = arv;
            if (elem < arv->num)
                arv = arv->esq;
            else
                arv = arv->dir;
        }
    }

    return NULL;
}

void excluir(tp_no **raiz, tp_no *no, tp_no *paino) {
    tp_no *pai, *filho;
    int resposta = 0;

    // Se o no possui dois filhos
	if ((no->esq != NULL) && (no->dir != NULL)) {
        pai = no;
        filho = pai->dir;
		while (filho->esq != NULL){ // Busca pelo maior
            pai = filho;
			filho = filho->esq;
        }
		// Prepara a eliminacao pelos ifs abaixo
		no->num = filho->num;
		paino = pai;
		no = filho;
	}

	// Se o no n�o possui filhos, ou seja, e uma folha
	if ((no->esq == NULL) && (no->dir == NULL)) {
        if (no == *raiz) // Elimina a raiz
            *raiz = NULL;
        else {
            if (paino == *raiz) // Elemina folha esquerda da raiz
                if (paino->esq == no)
                    (*raiz)->esq = NULL;
                else            // Elemina folha direita da raiz
                    (*raiz)->dir = NULL;
            else
                if (paino->esq == no) // Elemina folha esquerda
                    paino->esq = NULL;
                else                  // Elemina folha direita
                    paino->dir = NULL;
        }
	}

	else
        // Se o no possui apenas filho a esquerda
        if ((no->esq != NULL) && (no->dir == NULL)) {
            if (no == *raiz) { // Eh a raiz
                (*raiz)->num = no->esq->num;
                no = (*raiz)->esq;
                (*raiz)->esq = NULL;
            }
            else
                if (paino->esq == no)
                    paino->esq = no->esq;
                else
                    paino->dir = no->esq;
        }

    else
        // Se no possui apenas filho a direita
        if ((no->esq == NULL) && (no->dir != NULL)) {
            if (no == *raiz) { // Eh a raiz
                (*raiz)->num = no->dir->num;
                no = (*raiz)->dir;
                (*raiz)->dir = NULL;
            }
            else
                if (paino->esq == no)
                    paino->esq = no->dir;
                else
                    paino->dir = no->dir;
    }

    if(*raiz == NULL){
        printf("Arvore apagada.\n");
    }

    else{
        (*raiz)->alt = altura((*raiz)->esq) - altura((*raiz)->dir);
        resposta = checarBalanco(*raiz);
    }

    if(resposta == 1){
        (*raiz) = RotacaoDireita(*raiz);
        checarAltura(*raiz);
        return;
    }

    if(resposta == 2){
        (*raiz) = RotacaoEsquerda(*raiz);
        checarAltura(*raiz);
        return;
    }

    if(resposta == 3){
        (*raiz) = RotacaoDuplaDireita(*raiz);
        checarAltura(*raiz);
        return;
    }

    if(resposta == 4){
        (*raiz) = RotacaoDuplaEsquerda(*raiz);
        checarAltura(*raiz);
        return;
    }

    free(no);
}

void apagar(tp_no *arv) {

    if (!vazia(arv)) {
        apagar(arv->esq);
        apagar(arv->dir);
        free(arv);
    }
}

void main() {
	tp_no *raiz = NULL, *no, *pai;
	char op;
	int elem;

	do {

        printf("\n[I]ncluir, [L]istar, [E]xcluir, [P]esquisar elemento, [A]pagar arvore, [S]air: ");
        fflush(stdin); scanf("%c", &op);
        switch (op) {

        case 'i':
        case 'I':
            leelem(&elem);
            inserir(&raiz, elem);
            break;

        case 'l':
        case 'L':
            if(!vazia(raiz)){
                listar(raiz);
            }
            else{
                printf("Arvore vazia.\n");
            }
            break;

        case 'e':
        case 'E':
            if(!vazia(raiz)){
                leelem(&elem);
                if ((no = pesquisar(raiz, &pai, elem)) != NULL) {
                    listar(raiz);
                    printf("\nNumero %d encontrado e com pai %d\n", no->num, pai->num);
                    excluir(&raiz, no, pai);
                    listar(raiz);
                }
                else {
                    listar(raiz);
                    printf("\nNumero nao encontrado\n");
                }
            }
            else{
                printf("Arvore vazia.\n");
            }
            break;

        case 'p':
        case 'P':
            if(!vazia(raiz)){
                leelem(&elem);
                if ((no = pesquisar(raiz, &pai, elem)) != NULL) {
                    printf("\nNumero %d encontrado\n", no->num);
                }
                else{
                    printf("\nNumero nao encontrando na arvore.\n");
                }

            }
            else{
                printf("Arvore vazia.\n");
            }
            break;

        case 'a':
        case 'A':
                apagar(raiz);
                raiz = NULL;
                printf("arvore apagada.\n");
            break;

        case 's':
        case 'S':
            apagar(raiz);
            printf("Fim do programa");
            break;

        default:
            printf("Opcao invalida\n");
        }

    } while (op != 's' && op != 'S');

}
}
