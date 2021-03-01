#include <stdio.h>
#include "yaya_logger.h"

void foo(){
    loggerf(L_BEGF, "im a sub");

    loggerf(L_TODO, "im a void");

    loggerf(L_ENDF, "return");
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    ___logger_setting define[] = { { .head_format = "HEAD ## $line%3. $mess",
                                     .logs_format = "LOGS ## $line%03. -- | $type%.08 $name%.08 >> $func%10.  $mesg%.10 <<",
                                     .atom_format = " ",
                                     .type = L_ALL,
                                     .name = LL_ALL,
                                     .stream = LS_STDOUT,
                                     .style = LOGGER_FALSE
                                   } };

    loggerf_init(&___logger_main_def, NULL, NULL, define);

    loggerf(L_BEGF, "Start");

    foo();

    loggerf(L_ENDF, "end");

    return 0;
}
