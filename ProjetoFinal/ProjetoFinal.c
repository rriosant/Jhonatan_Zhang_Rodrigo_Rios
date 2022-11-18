#define _GNU_SOURCE
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>
#include <pthread.h>

struct c {
 int saldo;
};

typedef struct c conta;
conta from, to;

int valor;
int aux=0;
int zerou=0;


void transferencia( void *arg){

  int codigo=arg;
  int valor=2;        //valor que será retirada e adicionado em cada conta

  
  // Se o valor for menor ou igual ao saldo de FROM
  if ((from.saldo >= valor) && (aux==0)){  
    from.saldo -= valor;
		to.saldo += valor;

    // Se o valor do saldo for negativado volta a transação
    if (from.saldo < 0 ){
      from.saldo += valor;
      to.saldo -= valor;
    }

    // Se o valor do saldo for igual a zero
    if (from.saldo == 0){      
      aux=1;
    }
	}

  // Se o valor for menor ou igual ao saldo de TO e o valor de saldo já estiver zerado
  if ((to.saldo >=valor)&& (aux==1) && (zerou==1)){

		to.saldo -= valor;
		from.saldo += valor;

    if (to.saldo < 0){
      from.saldo -= valor;
		  to.saldo += valor;
    }

    if(to.saldo == 0){
      aux=0;
      
    }
	}

  if (from.saldo==0){
    zerou=1;
  }
  printf("Transferência %d concluída com sucesso!\nSaldo de c1: $%d\nSaldo de c2: $%d\n\n", codigo + 1, from.saldo, to.saldo);
  
}

int main(){
  
  int qtd_transferencias,situacao;
  
  
  printf("Digite a quantidade de transferencias simultaneas (máx=100):");
  scanf("%d",&qtd_transferencias);

  //Fica em looping caso os dados sejam inseridos errados 
  while (qtd_transferencias>100 && qtd_transferencias>-1){
    printf("Digite a quantidade de transferencias simultaneas (máx=100):");
    scanf("%d",&qtd_transferencias);
  }
    
  
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
