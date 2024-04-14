#include <stdio.h>
#include <pthread.h>
#include <inttypes.h>
#include <errno.h>
#include <sys/neutrino.h>
#include "../include/logger.h"

void server(void) {
    int rcvid;
    int chid;
    char message[256];
    char response[512];

    chid = ChannelCreate(0);
    log_info("id канала: %d", chid);

    log_info("Pid: %d", getpid());

    log_info("Сервер запущен и ждёт сообщений от клиента");

    while (1) {
        rcvid = MsgReceive(chid, message, sizeof(message), NULL);
        log_info("Полученное сообщение от клиента: %s", message);
        snprintf(response, sizeof(response), "Текст ответа на сообщение %s", message);
        MsgReply(rcvid, EOK, response, sizeof(response));

        log_info("Сформированный ответ сервера: %s", response);
    }
}

int main(void) {
    init_logger("server_logs.txt", 0, 1);
    log_info("Сервер. Сидорова Юлия И903Б");
    server();
    destroy_logger();
    return (1);
}