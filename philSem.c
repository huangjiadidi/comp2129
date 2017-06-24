#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

sem_t sem;

void* eating (void* arg) {
  int id = *(int*)arg;

  for(int i = 0; i < 100; i++) {
    sem_wait(&sem);
    printf("%d is eating\n", id);
    sem_post(&sem);
  }
  return NULL;
}

int main(void) {
  pthread_t phils[6];
  sem_init(&sem, 0, 3);

  for (int i = 0; i < 6; i++) {
    int id = i;
    pthread_create(&phils[i], NULL, eating, (void*)&id);
  }

  for (int i = 0; i < 6; i++) {
    pthread_join(phils[i]);
  }
  sem_destory(&sem);
  return 0;
}
