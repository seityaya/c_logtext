#include <stdio.h>
#include "test.h"

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    loggerf_test_param();

    loggerf_test_format();

    return 0;
}
