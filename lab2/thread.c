#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include "../include/logger.h"

typedef struct thread_params {
    const char* name;
    int n;
} thread_params;

void *thread_func(thread_params* params) {    
    // thread_params* cur_args = (thread_params*)args;
    log_info("%s: начал выполнение. n = %d", params->name, params->n);
    sleep(params->n);
    log_info("%s: завершил выполнение", params->name);
}


void create_thread(pthread_t* tid, int policy, int prio, void*(func)(void*), thread_params* params)
{
    pthread_attr_t attr;
    struct sched_param param;

    param.sched_priority = prio;
    pthread_attr_init(&attr);
    pthread_attr_setschedparam(&attr, &param);
    pthread_attr_setschedpolicy(&attr, policy);
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(tid, &attr, func, params);

    pthread_attr_destroy(&attr);
}


int main() {
    init_logger("thread_logs.txt", 0, 1);

    pthread_t thread_id1, thread_id2;
    pthread_attr_t attr1, attr2;
    struct sched_param param1, param2;
    int policy_1 = SCHED_FIFO;
    int policy_2 = SCHED_RR;
    int priority_1 = 11;
    int priority_2 = 13;
    int time_thread1 = 4;
    int time_thread2 = 2;

    thread_params params1 = {
        "Первый поток", 
        time_thread1, 
    };
    thread_params params2 = {
        "Второй поток", 
        time_thread2, 
    };

    create_thread(&thread_id1, policy_1, priority_1, thread_func, &params1);
    create_thread(&thread_id2, policy_2, priority_2, thread_func, &params2);

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
    destroy_logger();
    return 0;
}
