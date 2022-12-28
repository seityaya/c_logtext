//Author                 : Seityagiya Terlekchi
//Contacts               : seityaya@ukr.net
//Creation Date          : 2020.02
//License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
//SPDX-License-Identifier: LGPL-2.1-or-later
//Copyright © 2020-2022 Seityagiya Terlekchi. All rights reserved.

#include "yaya_logger.h"
#include "yaya_logger_private.h"

LOGGER_TOKEN_GENERATE_FUNC(STR){
    LOGGER_FUNC_UNUSED;
    strncpy(lvg->tmp_buff, &format[mas_opt->beg], mas_opt->end - mas_opt->beg + 1);
    format_build_str(lvg, mas_opt, lvg->tmp_buff);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(line){
    LOGGER_FUNC_UNUSED;
    format_build_num(lvg, mas_opt, line);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(file){
    LOGGER_FUNC_UNUSED;
    format_build_str(lvg, mas_opt, file);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(func){
    LOGGER_FUNC_UNUSED;
    format_build_str(lvg, mas_opt, func);
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
    format_build_str(lvg, mas_opt, lvg->tmp_buff);
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
    format_build_str(lvg, mas_opt, lvg->tmp_buff);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(mesg){
    LOGGER_FUNC_UNUSED;
    vsnprintf(lvg->tmp_buff, lvg->tmp_buff_size, mes, mes_list);
    format_build_str(lvg, mas_opt, lvg->tmp_buff);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(generic){
    LOGGER_FUNC_UNUSED;
    format_build_str(lvg, mas_opt, generic);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(count){
    LOGGER_FUNC_UNUSED;
    format_build_num(lvg, mas_opt, count);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(curnum){
    LOGGER_FUNC_UNUSED;
    format_build_num(lvg, mas_opt, lvg->curnum);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(absnum){
    LOGGER_FUNC_UNUSED;
    format_build_num(lvg, mas_opt, lvg->absnum);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(recnum){
    LOGGER_FUNC_UNUSED;
    intmax_t len = labs(lvg->recnum);
    format_build_num(lvg, mas_opt, len);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(rectab){
    LOGGER_FUNC_UNUSED;

    intmax_t len = labs(lvg->recnum);
    if(labs(lvg->recnum) > LOGGER_TMP_BUFF_SIZE){
        len = LOGGER_TMP_BUFF_SIZE;
    }

    lvg->tmp_buff[0] = '\0';
    for (intmax_t i = 0; i <= len; i++) {
        lvg->tmp_buff[i] = '\t';
        if(i == len - 1){
            lvg->tmp_buff[len] = ' ';
        }
    }
    lvg->tmp_buff[len] = '\0';

    format_build_str(lvg, mas_opt, lvg->tmp_buff);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(recast){
    LOGGER_FUNC_UNUSED;

    intmax_t len = labs(lvg->recnum);
    if(labs(lvg->recnum) > LOGGER_TMP_BUFF_SIZE){
        len = LOGGER_TMP_BUFF_SIZE;
    }

    lvg->tmp_buff[0] = '\0';
    for (intmax_t i = 0; i <= len; i++) {
        lvg->tmp_buff[i] = '*';
        if(i == len - 1){
            lvg->tmp_buff[len] = ' ';
        }
    }
    lvg->tmp_buff[len] = '\0';

    format_build_str(lvg, mas_opt, lvg->tmp_buff);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(data_build){
    LOGGER_FUNC_UNUSED;

    const unsigned char X__YEAR__[4+1] = {  __DATE__[7], __DATE__[8], __DATE__[9], __DATE__[10],  '\0' };
    const unsigned char X__MONTH__[2+1] = {
        (__DATE__[0] == 'O' || __DATE__[0] == 'N' || __DATE__[0] == 'D') ? '1' : '0',              // Oct, Nov, Dec
        (__DATE__[0] == 'J') ? ((__DATE__[1] == 'a') ? '1' : ((__DATE__[2] == 'n') ? '6' : '7')) : // Jan, Jun or Jul
        (__DATE__[0] == 'M') ? ((__DATE__[2] == 'r') ? '3' : '5') :                                // Mar or May
        (__DATE__[0] == 'A') ? ((__DATE__[1] == 'p') ? '4' : '8') :                                // Apr or Aug
        (__DATE__[0] == 'F') ? '2' :                                                               // Feb
        (__DATE__[0] == 'S') ? '9' :                                                               // Sep
        (__DATE__[0] == 'O') ? '0' :                                                               // Oct
        (__DATE__[0] == 'N') ? '1' :                                                               // Nov
        (__DATE__[0] == 'D') ? '2' :                                                               // Dec
        '\0'};
    const unsigned char X__DAY__[2+1] = { __DATE__[4]==' ' ? '0' : __DATE__[4],  __DATE__[5], '\0' };

    format_build_str(lvg, mas_opt, (char*)X__YEAR__);
    format_build_str(lvg, mas_opt, ".");
    format_build_str(lvg, mas_opt, (char*)X__MONTH__);
    format_build_str(lvg, mas_opt, ".");
    format_build_str(lvg, mas_opt, (char*)X__DAY__);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(time_build){
    LOGGER_FUNC_UNUSED;
    format_build_str(lvg, mas_opt, __TIME__);
    return LE_OK;
}

#define TM_YEAR 1900
LOGGER_TOKEN_GENERATE_FUNC(data_curent){
    LOGGER_FUNC_UNUSED;
    time_t curent = time(NULL);
    struct tm *ptr = NULL;
    ptr = localtime(&curent);
    snprintf(lvg->tmp_buff, lvg->tmp_buff_size, "%04d.%02d.%02d", ptr->tm_year + TM_YEAR, ptr->tm_mon + 1, ptr->tm_mday);
    format_build_str(lvg, mas_opt, lvg->tmp_buff);
    return LE_OK;
}
#undef TM_YEAR

LOGGER_TOKEN_GENERATE_FUNC(time_curent){
    LOGGER_FUNC_UNUSED;
    time_t curent = time(NULL);
    struct tm *ptr = NULL;
    ptr = localtime(&curent);
    snprintf(lvg->tmp_buff, lvg->tmp_buff_size, "%02d:%02d:%02d", ptr->tm_hour, ptr->tm_min, ptr->tm_sec);
    format_build_str(lvg, mas_opt, lvg->tmp_buff);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(type_filter){
    LOGGER_FUNC_UNUSED;
    for (uintmax_t j = 0; j < lvg->type.num - 1; j++){
        if (lvg->psett->type_l1 == L_ALL){
            strncpy(lvg->tmp_buff, lvg->type.ptr[lvg->type.num].name, lvg->tmp_buff_size);
            break;
        }
        if (lvg->psett->type_l1 == L_NUL){
            strncpy(lvg->tmp_buff, lvg->type.ptr[0].name, lvg->tmp_buff_size);
            break;
        }
        if (LOGGER_BIT_GET(lvg->psett->type_l1, j)){
            strncat(lvg->tmp_buff, lvg->type.ptr[j + 1].name, lvg->tmp_buff_size);
            strncat(lvg->tmp_buff, " ", lvg->tmp_buff_size);
        }
    }
    format_build_str(lvg, mas_opt, lvg->tmp_buff);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(name_filter){
    LOGGER_FUNC_UNUSED;
    for (uintmax_t j = 0; j < lvg->name.num - 1; j++){
        if (lvg->psett->name_l2 == LL_ALL){
            strncpy(lvg->tmp_buff, lvg->name.ptr[lvg->name.num].name, lvg->tmp_buff_size);
            break;
        }
        if (lvg->psett->name_l2 == LL_NUL){
            strncpy(lvg->tmp_buff, lvg->name.ptr[0].name, lvg->tmp_buff_size);
            break;
        }
        if (LOGGER_BIT_GET(lvg->psett->name_l2, j)){
            strncat(lvg->tmp_buff, lvg->name.ptr[j + 1].name, lvg->tmp_buff_size);
            strncat(lvg->tmp_buff, " ", lvg->tmp_buff_size);
        }
    }
    format_build_str(lvg, mas_opt, lvg->tmp_buff);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(type_mask){
    LOGGER_FUNC_UNUSED;
    for (uintmax_t j = 0; j < sizeof(uintmax_t) * __CHAR_BIT__; j++){
        if (LOGGER_BIT_GET(lvg->psett->type_l1, j)){
            strncat(lvg->tmp_buff, "1", lvg->tmp_buff_size);
        }else{
            strncat(lvg->tmp_buff, "0", lvg->tmp_buff_size);
        }
    }
    format_build_str(lvg, mas_opt, lvg->tmp_buff);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(name_mask){
    LOGGER_FUNC_UNUSED;
    for (uintmax_t j = 0; j < sizeof(uintmax_t) * __CHAR_BIT__; j++){
        if (LOGGER_BIT_GET(lvg->psett->name_l2, j)){
            strncat(lvg->tmp_buff, "1", lvg->tmp_buff_size);
        }else{
            strncat(lvg->tmp_buff, "0", lvg->tmp_buff_size);
        }
    }
    format_build_str(lvg, mas_opt, lvg->tmp_buff);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(type_list){
    LOGGER_FUNC_UNUSED;
    for (uintmax_t j = 0; j < lvg->type.num + 1; j++){
        strncat(lvg->tmp_buff, lvg->type.ptr[j].name, lvg->tmp_buff_size);
        strncat(lvg->tmp_buff, " ", lvg->tmp_buff_size);
    }
    format_build_str(lvg, mas_opt, lvg->tmp_buff);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(name_list){
    LOGGER_FUNC_UNUSED;
    for (uintmax_t j = 0; j < lvg->name.num + 1; j++){
        strncat(lvg->tmp_buff, lvg->name.ptr[j].name, lvg->tmp_buff_size);
        strncat(lvg->tmp_buff, " ", lvg->tmp_buff_size);
    }
    format_build_str(lvg, mas_opt, lvg->tmp_buff);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(proj){
    LOGGER_FUNC_UNUSED;
    format_build_str(lvg, mas_opt, lvg->pdefn->proj);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(prog){
    LOGGER_FUNC_UNUSED;
    format_build_str(lvg, mas_opt, lvg->pdefn->prog);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(version){
    LOGGER_FUNC_UNUSED;
    format_build_str(lvg, mas_opt, lvg->pdefn->version);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(comp_v){
    LOGGER_FUNC_UNUSED;
#if __GNUC__
    format_build_str(lvg, mas_opt, "GNUC:");
    format_build_num(lvg, mas_opt, 1);

    format_build_str(lvg, mas_opt, "; ");

    format_build_str(lvg, mas_opt, "VERSION:");
    format_build_str(lvg, mas_opt, __VERSION__);
#endif
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(lang_v){
    LOGGER_FUNC_UNUSED;
    format_build_str(lvg, mas_opt, "STDC:");
    format_build_num(lvg, mas_opt, __STDC__);

    format_build_str(lvg, mas_opt, "; ");

    format_build_str(lvg, mas_opt, "VERSION:");
    format_build_num(lvg, mas_opt, __STDC_VERSION__);
    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(stats){
    LOGGER_FUNC_UNUSED;

    if(lvg->mem_stats != NULL){
        format_build_str(lvg, mas_opt, "USAGE:");
        format_build_num(lvg, mas_opt, lvg->mem_stats->memory_produce - lvg->mem_stats->memory_release);
        format_build_str(lvg, mas_opt, "; ");

        format_build_str(lvg, mas_opt, "NEW:");
        format_build_num(lvg, mas_opt, lvg->mem_stats->memory_call_new);
        format_build_str(lvg, mas_opt, "; ");

        format_build_str(lvg, mas_opt, "RES:");
        format_build_num(lvg, mas_opt, lvg->mem_stats->memory_call_res);
        format_build_str(lvg, mas_opt, "; ");

        format_build_str(lvg, mas_opt, "DEL:");
        format_build_num(lvg, mas_opt, lvg->mem_stats->memory_call_del);
        format_build_str(lvg, mas_opt, "; ");
    }
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
