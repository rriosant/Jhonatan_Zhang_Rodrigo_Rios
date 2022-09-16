//Referências do pseudocodigo da figura 2-47 do livro "Sistemas Operacionais Modernos 4-edicao", Tanenbaum

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <semaphore.h>

// definindo variaveis 
#define PENSANDO 0                 // Estado = Filosofo está pensando 
#define FOME 1                    // Estado = Filosofo está com fome 
#define COMENDO 2                // Estado = Filosofo está pensando
#define qtd_filosofo 5          //Quantidade de filosofo
#define ESQUERDA (i+5-1)%5     //Quantidade de filosofo a esquerda
#define DIREITA  (i+1)%5      //Quantidade de filosofo a direita


int estado[qtd_filosofo];          //Um array para controlar os estados de cada um
sem_t mutex;                       //Exclusao mutua para as regioes criticas
sem_t sem_filo[qtd_filosofo];       //Semaforo para cada filosofo

// funcoes
void situacao();
void *filosofo(void *j);
void pegar_Garfo(int i);
void devolver_Garfo(int i);
void intencao(int i);

int main(){

  printf("\nJANTAR DOS FILOSOFOS\n\n");
  
  pthread_t thread[qtd_filosofo];  //threads
  int num[qtd_filosofo];            //Auxilia na criação de thread
  
	for(int i = 0; i < qtd_filosofo; i++)
    	num[i]= i;

  //Inicializa os semaforos
	sem_init(&mutex,0,1);
	for(int i = 0; i < qtd_filosofo; i++){
    	sem_init(&sem_filo[i],0,0);
	}
  
  //Cria as threads
	for(int i = 0; i < qtd_filosofo; i++){
   	pthread_create(&thread[i],NULL,filosofo,(void*) &num[i]);
	}
 
  //Espera as threads para finalizar
	for(int i = 0; i < qtd_filosofo; i++){
    	pthread_join(thread[i],NULL);
    
	}

  return 0;

}

void *filosofo(void *j){

	while(1){  
      sleep(random() % 1 + 2);    //Tempo para o filosofo pensar (aleatorio)
    	pegar_Garfo(*(int*)j);      //Pega os dois garfos ou é bloqueado
    	sleep(random() % 1 + 1);    //Tempo para o filosofo comer (aleatorio)
    	devolver_Garfo(*(int*)j);    //Coloca os dois garfos na mesa
	}
}



void pegar_Garfo(int i){
	sem_wait(&mutex);              //Entra na regiao critica
	estado[i]=FOME;               //O filosofo está com fome
	situacao();                  //Mostra o estado dos filosofos
	intencao(i);                //Tenta pegar os dois garfos pra comer
	sem_post(&mutex);          //Sai da regiao critica
	sem_wait(&sem_filo[i]);    //Bloqueia se não conseguir pegar os dois garfos
}
 
void devolver_Garfo(int i){
  
	sem_wait(&mutex);          // Entra na regiao critica
	estado[i]=PENSANDO;        // O filosofo está comendo
	situacao();                 // Mostra o estado dos filosofos
	intencao(ESQUERDA);        //Verifica se algum filosofo da esquerda pode comer
	intencao(DIREITA);          //Verifica se algum filosofo da direita pode comer
	sem_post(&mutex);          // Sai da regiao critica
}
 
//funcao que testa se o filósofo pode comer
void intencao(int i){
   if(estado[i] == FOME && estado[ESQUERDA] != COMENDO && estado[DIREITA] != COMENDO){
   	estado[i]=COMENDO;
   	situacao();
   	sem_post(&sem_filo[i]);
   }
}

//Mostra o estado dos filosofos
void situacao(){
   for(int i=0; i<qtd_filosofo; i++){
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
