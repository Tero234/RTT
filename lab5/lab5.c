#include <stdio.h>
#include <pthread.h>
#include <inttypes.h>
#include <errno.h>
#include <sys/neutrino.h>
#include "../include/logger.h"

#define SEC_NSEC 1000000000LL

void *long_thread(void *notused) {
    int time = 20;
    log_info("Время ожидания внутри потока: %d", time);
    sleep(time);
}

int main(void)
{
    init_logger("logs.txt", 0, 1);

    uint64_t timeout;
    struct sigevent event;
    int rval;
    pthread_t thread_id;

    log_info("Сидорова Юлия И903Б");

    event.sigev_notify = SIGEV_UNBLOCK; 
    pthread_create(&thread_id, NULL, long_thread, NULL);

    timeout = 10LL * SEC_NSEC;
    TimerTimeout(CLOCK_REALTIME, _NTO_TIMEOUT_JOIN, &event, &timeout, NULL);
    rval = pthread_join(thread_id, NULL);
    if (rval == ETIMEDOUT) log_info("Поток %d выполняется более 10 секунд", thread_id);
    TimerTimeout(CLOCK_REALTIME, _NTO_TIMEOUT_JOIN, &event, &timeout, NULL);
    sleep(5);
    rval = pthread_join(thread_id, NULL);
    if (rval == ETIMEDOUT) log_info("Поток %d выполняется более 25 секунд", thread_id);
    else log_info("Поток %d завершил работу", thread_id);

    destroy_logger();

    return 1;
}
