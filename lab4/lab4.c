#include <stdio.h>
#include <time.h>
#include <sync.h>
#include <pthread.h>
#include <sys/neutrino.h>
#include "../include/logger.h"

barrier_t barrier;

void *thread1(void * not_used)
{
    char buf[27];
    time_t now;

    log_info("Ставим барьер в первом потоке");
    sleep(3);
    barrier_wait(&barrier);
    log_info("Барьер в первом потоке преодален");
}

void *thread2(void * not_used)
{
    char buf[27];
    time_t now;

    log_info("Ставим барьер во втором потоке");
    sleep(6);
    barrier_wait(&barrier);
    log_info("Барьер во втором потоке преодален");
}


int main()
{
    init_logger("logs.txt", 0, 1);

    char buf[27];
    time_t now;
    int NUM_THREADS = 2;
    pthread_t t1;
    pthread_t t2;

    //барьер, атрибуты, число потоков + 1, т.к. мейн помимо thread 1 и thread 2 есть главный поток программы
    barrier_init(&barrier, NULL, NUM_THREADS + 1); 
    log_info("Сидорова Юлия И903Б");
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    log_info("Ставим барьер в мейн потоке");
    barrier_wait(&barrier);
    log_info("Барьер в мейн потоке преодален");

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    destroy_logger();

    return 0;
}