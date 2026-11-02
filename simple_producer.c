
#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>

sem_t empty, full;
pthread_mutex_t s;

int buff[5] = {0};
int in = 0;
int out = 0;

void *producer(void *arg) {

    int data = *(int *)arg;

    sem_wait(&empty);

    pthread_mutex_lock(&s);

    buff[in] = data;

    printf("Producer: inserted %d at buff[%d]\n", data, in);

    in = (in + 1) % 5;

    pthread_mutex_unlock(&s);

    sem_post(&full);

    return NULL;
}

void *consumer(void *arg) {

    int data;

    for (int i = 0; i < 5; i++) {

        sem_wait(&full);

        pthread_mutex_lock(&s);

        data = buff[out];

        buff[out] = -1;

        printf("Consumer: consumed %d at buff[%d] and changed it to -1\n",
               data, out);

        out = (out + 1) % 5;

        pthread_mutex_unlock(&s);

        sem_post(&empty);
    }

    return NULL;
}

int main() {

    pthread_t p[5], c;

    int a[5] = {11, 12, 13, 14, 15};

    printf("Initial Buffer: ");

    for (int i = 0; i < 5; i++) {
        printf("%d ", buff[i]);
    }

    printf("\n");

    sem_init(&empty, 0, 5);
    sem_init(&full, 0, 0);

    pthread_mutex_init(&s, NULL);

    pthread_create(&c, NULL, consumer, NULL);

    for (int i = 0; i < 5; i++) {
        pthread_create(&p[i], NULL, producer,&a[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(p[i], NULL);
    }

    pthread_join(c, NULL);

    printf("Final Buffer: ");

    for (int i = 0; i < 5; i++) {
        printf("%d ", buff[i]);
    }

    printf("\n");

    sem_destroy(&empty);
    sem_destroy(&full);

    pthread_mutex_destroy(&s);

    return 0;
}
