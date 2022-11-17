#define _GNU_SOURCE
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>


struct c {
 int saldo;
};


typedef struct c conta;
conta from, to;
int valor;
int aux=1;


void transferencia( void *arg){

  int codigo=arg;
  int valor=4;

  if ((from.saldo >= valor) && (aux==1)){

    from.saldo -= valor;
		to.saldo += valor;

    if (from.saldo < 0 ){
      from.saldo += valor;
      to.saldo -= valor;
    }

    if (from.saldo == 0){      
      aux=2;
    }
	}


  if ((to.saldo >=valor)&& (aux==2)){

		to.saldo -= valor;
		from.saldo += valor;

    if (to.saldo < 0){
      from.saldo -= valor;
		  to.saldo += valor;
      aux=1;
    }

    if(to.saldo == 0){
      aux=1;
    }
	}

  printf("Transferência %d concluída com sucesso!\nSaldo de c1: $%d\nSaldo de c2: $%d\n", codigo + 1, from.saldo, to.saldo);

}


int main(){
  
  int qtd_transferencias,situacao;
  

  printf("Digite a quantidade de transferencias simultaneas (máx=100):");
  scanf("%d",&qtd_transferencias);
    
  
   pthread_t thread[qtd_transferencias];  //threads
   

//Todas as contas começam com saldo 100
  
  from.saldo = 100;  
  to.saldo = 100;


//Cria as threads
  for (int i = 0; i < qtd_transferencias; i++) {
  pthread_create(&thread[i],NULL,transferencia,(void*)i);
  }

//Espera as threads para finalizar
  for(int i = 0; i < qtd_transferencias; i++){
  pthread_join(thread[i], NULL);
  }
}