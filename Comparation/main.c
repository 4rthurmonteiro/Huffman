#include "avl.c"
#include "tree.c"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc,char* argv[])
{
    /*
    Sao necesssarios pelo menos 4 parametros para inicializar o programa.
    argv[1] = quantidade de elementos iniciais
    argv[2] = quantidade de elementos que vai ser incrementada em cada iteração
    argv[3]= quantidade de elementos finais
    argv[4]= local de arquivo de saida;
    argv[5] = "--crescente" define ordem crescente de inserção (opcional).
    */
    if(argc<5){
        printf("Parametros insuficientes\n");
        return 0;
    }

    int crescente=0;
    if(argc>5){
        crescente=!(strcmp("--crescente",argv[5]));
    }


    int inicio=atoi(argv[1]);
    int step=atoi(argv[2]);
    int fim=atoi(argv[3]);

    node *avl = NULL;  //Arvore de avl
    node *tree = NULL; //Arvore Normal
    int number;
    srand(time(NULL));
    FILE* arq=fopen(argv[4],"wt"); //arquivo de saida
    long tempo_avl,tempo_tree;
    int i,j;
    int op,op2;
    for( i=inicio;i<=fim;i+=step){ //varios testes sao realizados, comecando com "inicio" elementos ate "fim"  elementos

        tree=NULL;
        avl=NULL;
        printf("Realizando Teste com %d elementos\n",i);
        for( j=0;j<i;j++){//insere "i" quantidade de elementos para esse teste
            if(crescente){
                number=j; //numero em ordem crescente
            }else{
                number=rand()%i; //numero  aleatorio
            }

            tree=add_node(tree,number);
            avl=add_avl_node(avl,number);
        }
        int* sortedNumbers= (int*) malloc(sizeof(int)*i);
        for( j=0;j<i;j++){
           sortedNumbers[j]=rand()%i; //define os numeros que serao procurados. (sempre aleatorios)
        }

        op=0;
         for(j=0;j<i;j++){
           search_(tree,sortedNumbers[j],&op);//procura na arvore normal
        }
        op2=0;
         for( j=0;j<i;j++){
           search_(avl,sortedNumbers[j],&op2); //procura na Avl
        }
        fprintf(arq,"%d %lf %lf\n",i,op/(double)i,op2/(double)i); //imprimi a quantidade de elementos inseridos/procurados
                                                                //  e a media de operações para achar um elemento.

        //Libera a memoria alocada para esse teste.
        free(sortedNumbers);
        freeTree(tree);
        freeTree(avl);
    }
    fclose(arq);

    //pre_order(root);



    return 0;
}
