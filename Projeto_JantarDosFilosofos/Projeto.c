#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

// definindo variaveis 
#define PENSANDO 0             // Estado = Filosofo está pensando 
#define FOME 1                // Estado = Filosofo está com fome 
#define COMENDO 2             // Estado = Filosofo está pensando
#define qtd_filosofo 5          //Quantidade de filosofo
#define DIREITA (i+5-1)%5     //Quantidade de filosofo a direita
#define ESQUERDA  (i+1)%5      //Quantidade de filosofo a esquerda
 
int i;

//semáforos
sem_t mutex;           

sem_t sem_filo[5];

int estado[5];


pthread_t *thread;


void situacao();
void *filosofo(void *j);
void pegar_Garfo(int i);
void devolver_Garfo(int i);
void intencao(int i);


void *filosofo(void *j){
	int i= *(int*) j;
	while(1){  
      sleep(random() % 1 + 2);
    	pegar_Garfo(i);
    	sleep(random() % 1 + 1);
    	devolver_Garfo(i);
	}
}
 
void pegar_Garfo(int i){
	sem_wait(&mutex); //Pega o semáforo pra si
	estado[i]=FOME; //Seta que está com fome
	situacao(); //Mostra o estado dos outros filosofos
	intencao(i); //Tenta pegar os garfos pra comer
	sem_post(&mutex); //Libera o semáforo
	sem_wait(&sem_filo[i]); //Atualiza seu próprio semáforo
}
 
void devolver_Garfo(int i){
	int esquerda, direita;
	sem_wait(&mutex);
	estado[i]=PENSANDO;
	situacao();
	intencao(ESQUERDA);
	intencao(DIREITA);
	sem_post(&mutex);
}
 
//funcao que testa se o filósofo pode comer
void intencao(int i){
   if(estado[i] == FOME && estado[ESQUERDA] != COMENDO && estado[DIREITA] != COMENDO){
   	estado[i]=COMENDO;
   	situacao();
   	sem_post(&sem_filo[i]);
   }
}


void situacao(){
   for(i=1; i<=qtd_filosofo; i++){
   	if(estado[i] == PENSANDO){
      	printf("O filósofo %d esta pensando...\n", i);
   	}
   	if(estado[i] == FOME){
      	printf("O filósofo %d esta com fome...\n", i);
   	}
   	if(estado[i] == COMENDO){
      	printf("O filósofo %d esta comendo!\n", i);
   	}
   }
   printf("\n");
}

int main(){

  printf("\nJANTAR DOS FILOSOFOS\n\n");
  
  pthread_t thread[5];
 
    //Inicializa o estado
	for(i = 0; i < qtd_filosofo; i++){
    	estado[i]=0;
	}
	situacao();

	//inicia os semáforos
	sem_init(&mutex,0,1);
	 
	for(i = 0; i < qtd_filosofo; i++){
    	sem_init(&sem_filo[i],0,0);
	}
 
	//cria as threads(filosofos)
	for(i = 0; i < qtd_filosofo; i++){
   	pthread_create(&thread[i],NULL,filosofo,&i);
	}
 
	//faz um join nas threads
	for(i = 0; i < qtd_filosofo; i++){
    	pthread_join(thread[i],NULL);
    
	}

  return 0;

}