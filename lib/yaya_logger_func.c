//Author                 : Seityagiya Terlekchi
//Contacts               : seityaya@ukr.net
//Creation Date          : 2020.02
//License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
//SPDX-License-Identifier: LGPL-2.1-or-later
//Copyright © 2020-2022 Seityagiya Terlekchi. All rights reserved.

#include "yaya_logger.h"
#include "yaya_logger_private.h"

LOGGER_TOKEN_GENERATE_FUNC(line){
    LOGGER_FUNC_UNUSED;
    ___format_build_num(lvg, mas_opt, line);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(file){
    LOGGER_FUNC_UNUSED;
    ___format_build_str(lvg, mas_opt, file);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(func){
    LOGGER_FUNC_UNUSED;
    ___format_build_str(lvg, mas_opt, func);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(type){
    LOGGER_FUNC_UNUSED;
    for (uintmax_t j = 0; j < lvg->type.num - 1; j++){
        if (type == L_ALL){
            strncpy(lvg->tmp_buff, lvg->type.ptr[lvg->type.num].name, lvg->tmp_buff_size);
            break;
        }
        if (type == L_NUL){
            strncpy(lvg->tmp_buff, lvg->type.ptr[0].name, lvg->tmp_buff_size);
            break;
        }
        if (LOGGER_BIT_GET(type, j)){
            strncat(lvg->tmp_buff, lvg->type.ptr[j + 1].name, lvg->tmp_buff_size);
            strncat(lvg->tmp_buff, " ", lvg->tmp_buff_size);
        }
    }
    ___format_build_str(lvg, mas_opt, lvg->tmp_buff);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(name){
    LOGGER_FUNC_UNUSED;
    for (uintmax_t j = 0; j < lvg->name.num - 1; j++){
        if (name == LL_ALL){
            strncpy(lvg->tmp_buff, lvg->name.ptr[lvg->name.num].name, lvg->tmp_buff_size);
            break;
        }
        if (name == LL_NUL){
            strncpy(lvg->tmp_buff, lvg->name.ptr[0].name, lvg->tmp_buff_size);
            break;
        }
        if (LOGGER_BIT_GET(name, j)){
            strncat(lvg->tmp_buff, lvg->name.ptr[j + 1].name, lvg->tmp_buff_size);
            strncat(lvg->tmp_buff, " ", lvg->tmp_buff_size);
        }
    }
    ___format_build_str(lvg, mas_opt, lvg->tmp_buff);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(mesg){
    LOGGER_FUNC_UNUSED;
    vsnprintf(lvg->tmp_buff, lvg->tmp_buff_size, mes, mes_list);
    ___format_build_str(lvg, mas_opt, lvg->tmp_buff);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(debug){
    LOGGER_FUNC_UNUSED;
    ___format_build_str(lvg, mas_opt, debug);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(count){
    LOGGER_FUNC_UNUSED;
    ___format_build_num(lvg, mas_opt, count);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(curnum){
    LOGGER_FUNC_UNUSED;
    ___format_build_num(lvg, mas_opt, lvg->curnum);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(absnum){
    LOGGER_FUNC_UNUSED;
    ___format_build_num(lvg, mas_opt, lvg->absnum);
    return LE_OK;
}






LOGGER_TOKEN_GENERATE_FUNC(short_path){
    LOGGER_FUNC_UNUSED;

    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(full_path){
    LOGGER_FUNC_UNUSED;

    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(data_build){
    LOGGER_FUNC_UNUSED;
    ___format_build_str(lvg, mas_opt, __DATE__);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(time_build){
    LOGGER_FUNC_UNUSED;
    ___format_build_str(lvg, mas_opt, __TIME__);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(data_curent){
    LOGGER_FUNC_UNUSED;
    time_t curent = time(NULL);
    struct tm *ptr = NULL;
    ptr = localtime(&curent);
    snprintf(lvg->tmp_buff, lvg->tmp_buff_size, "%04d.%02d.%02d", ptr->tm_year + 1900, ptr->tm_mon + 1, ptr->tm_mday);
    ___format_build_str(lvg, mas_opt, lvg->tmp_buff);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(time_curent){
    LOGGER_FUNC_UNUSED;
    time_t curent = time(NULL);
    struct tm *ptr = NULL;
    ptr = localtime(&curent);
    snprintf(lvg->tmp_buff, lvg->tmp_buff_size, "%02d:%02d:%02d", ptr->tm_hour, ptr->tm_min, ptr->tm_sec);
    ___format_build_str(lvg, mas_opt, lvg->tmp_buff);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(prog){
    LOGGER_FUNC_UNUSED;

    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(prog_v){
    LOGGER_FUNC_UNUSED;

    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(prog_p){
    LOGGER_FUNC_UNUSED;

    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(proj){
    LOGGER_FUNC_UNUSED;

    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(compiler){
    LOGGER_FUNC_UNUSED;

    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(compiler_v){
    LOGGER_FUNC_UNUSED;

    return LE_OK;
}


LOGGER_TOKEN_GENERATE_FUNC(tik_core){
    LOGGER_FUNC_UNUSED;

    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(tik_sec){
    LOGGER_FUNC_UNUSED;

    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(tic_rtos){
    LOGGER_FUNC_UNUSED;

    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(tik_unix){
    LOGGER_FUNC_UNUSED;

    return LE_OK;
}


LOGGER_TOKEN_GENERATE_FUNC(type_filter){
    LOGGER_FUNC_UNUSED;

    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(name_filter){
    LOGGER_FUNC_UNUSED;

    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(type_mask){
    LOGGER_FUNC_UNUSED;

    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(name_mask){
    LOGGER_FUNC_UNUSED;

    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(type_list){
    LOGGER_FUNC_UNUSED;

    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(name_list){
    LOGGER_FUNC_UNUSED;

    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(seed){
    LOGGER_FUNC_UNUSED;

    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(alignl){
    LOGGER_FUNC_UNUSED;

    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(aliggt){
    LOGGER_FUNC_UNUSED;

    return LE_OK;
}
