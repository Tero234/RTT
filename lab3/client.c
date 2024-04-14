#include <stdio.h>
#include <pthread.h>
#include <inttypes.h>
#include <errno.h>
#include <sys/neutrino.h>
#include "../include/logger.h"

int main(void) {
    init_logger("client_logs.txt", 0, 1);

    char smsg[100];
    char rmsg[200];
    int coid;
    long serv_pid;

    log_info("Клиент. Сидорова Юлия И903Б");
    sleep(1);
    printf("Введите PID сервера:\n");
    scanf("%ld", &serv_pid);
    getchar();

    coid = ConnectAttach(0, serv_pid, 1, 0, 0);
    log_info("coid=%d", coid);

    sleep(1);
    printf("Введите сообщение:\n");
    fgets(smsg, sizeof(smsg), stdin);
    size_t len = strlen(smsg);
    if (len > 0 && smsg[len - 1] != '\0') {
        smsg[len - 1] = '\0';
    }
    log_info("Вы ввели: %s", smsg);
    if (MsgSend(coid, smsg, strlen(smsg) + 1, rmsg, sizeof(rmsg)) == -1) {
        ConnectDetach(coid);
        destroy_logger();
        log_error("Ошибка. Сообщение не отправлено");
        return 1;
    }
    log_info("Полученный клиентом ответ сервера: '%s'", rmsg);

    ConnectDetach(coid);
    destroy_logger();
    return 0;
}
