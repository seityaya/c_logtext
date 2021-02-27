#include "yaya_logger.h"

int main(int argc, char *argv[]) {

    loggerf_test_param();

    loggerf_init();
    loggerf(L_HEAD, "Test Loger");

    loggerf(L_BEGF, "Start");

    loggerf(L_ATOM);

    loggerf(L_ENDF, "Stop");


    return 0;
}
