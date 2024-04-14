#include <stdio.h>
#include <pthread.h>
#include "../include/logger.h"

int data_ready = 0;
int inf = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condvar = PTHREAD_COND_INITIALIZER;

int flag = 0;;

void* consumer(void* not_used)
{
    while(!flag)
    {
        pthread_mutex_lock(&mutex);
        log_info("W1");
        while(!data_ready)
        {
            log_info("W2");
            pthread_cond_wait(&condvar, &mutex);
            log_info("W3");
        }
        log_info("Полученные consumer данные = %d ", inf);
        data_ready = 0;
        pthread_cond_signal(&condvar);
        pthread_mutex_unlock(&mutex);
    }
}

void* producer(void* not_used)
{
    while(!flag)
    {
        sleep(1);
        log_info("Полученные producer данные от h/w = %d ", inf);
        pthread_mutex_lock(&mutex);
        log_info("WP1");
        while(data_ready)
        {
            log_info("WP2");
            pthread_cond_wait(&condvar, &mutex);
        }
        data_ready = 1;
        inf++;
        log_info("WP3");
        pthread_cond_signal(&condvar);
        pthread_mutex_unlock(&mutex);
    }
}

void main()
{
    init_logger("logs.txt", 0, 1);
    log_info("Сидорова Юлия И903Б");

    pthread_t consumer_id, producer_id;
    pthread_create(&consumer_id, NULL, consumer, NULL);
    pthread_create(&producer_id, NULL, producer, NULL);

    sleep(3);
    flag = 1;
    
    pthread_join(consumer_id, NULL);
    pthread_join(producer_id, NULL);

    destroy_logger();

    return 0;
}