#include "yaya_logger.h"
#include "yaya_logger_private.h"

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

logger_error ___format_build_num(logger* lvg, ___logger_token_mas* mas_opt, uintmax_t buff_orig)
{
    mas_opt->beglog = lvg->out_offset;

    if (mas_opt->spe != NULL){
        if (mas_opt->spe->lfs == LFS_NUL){
            lvg->out_offset += snprintf(&lvg->out_buff[lvg->out_offset], lvg->out_buff_size, "%0*" PRIuMAX "", (int)mas_opt->spe->lef, buff_orig);
        }else if (mas_opt->spe->lfs == LFS_LEF){
            lvg->out_offset += snprintf(&lvg->out_buff[lvg->out_offset], lvg->out_buff_size, "%*" PRIuMAX "", (int)mas_opt->spe->lef, buff_orig);
        }else if (mas_opt->spe->lfs == LFS_RIG){
            lvg->out_offset += snprintf(&lvg->out_buff[lvg->out_offset], lvg->out_buff_size, "%-*" PRIuMAX "", (int)mas_opt->spe->rig, buff_orig);
        }
    }else{
        lvg->out_offset += snprintf(&lvg->out_buff[lvg->out_offset], lvg->out_buff_size, "%" PRIuMAX "", buff_orig);
    }

    mas_opt->endlog = lvg->out_offset;

    return LE_OK;
}


logger_error ___format_build_str(logger *lvg, ___logger_token_mas *mas_opt, const char *buff_orig)
{
    char buff[1000] = {0}; //FIXME

    mas_opt->beglog = lvg->out_offset;

    if (mas_opt->spe != NULL){
        uintmax_t max = mas_opt->spe->lef > mas_opt->spe->rig ? mas_opt->spe->lef : mas_opt->spe->rig;
        uintmax_t len = strlen(buff_orig);
        if (len <= mas_opt->spe->lef || len <= mas_opt->spe->rig){
            goto jmp_else_null;
        }
        if (mas_opt->spe->lfs == LFS_LEF){
            strncpy(buff, &buff_orig[len - max], max);
            strncpy(buff, LOGGER_HIDDEN_STR, strlen(LOGGER_HIDDEN_STR));
            lvg->out_offset += snprintf(&lvg->out_buff[lvg->out_offset], lvg->out_buff_size, "%s", buff);
        }else if (mas_opt->spe->lfs == LFS_RIG){
            strncpy(buff, &buff_orig[0], max);
            strncpy(&buff[max - strlen(LOGGER_HIDDEN_STR)], LOGGER_HIDDEN_STR, strlen(LOGGER_HIDDEN_STR));
            lvg->out_offset += snprintf(&lvg->out_buff[lvg->out_offset], lvg->out_buff_size, "%s", buff);
        }else{
        jmp_else_null:
            if (mas_opt->spe->lef != 0){
                lvg->out_offset += snprintf(&lvg->out_buff[lvg->out_offset], lvg->out_buff_size, "%*s", (int)max, buff_orig);
            }else if (mas_opt->spe->rig != 0){
                lvg->out_offset += snprintf(&lvg->out_buff[lvg->out_offset], lvg->out_buff_size, "%-*s", (int)max, buff_orig);
            }else{
                goto jmp_else_main;
            }
        }
    }else{
    jmp_else_main:
        lvg->out_offset += snprintf(&lvg->out_buff[lvg->out_offset], lvg->out_buff_size, "%s", buff_orig);
    }

    mas_opt->endlog = lvg->out_offset;

    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(STR){
    LOGGER_FUNC_UNUSED;
    strncpy(lvg->tmp_buff, &format[mas_opt->beg], mas_opt->end - mas_opt->beg + 1);
    ___format_build_str(lvg, mas_opt, lvg->tmp_buff);
    return LE_OK;
}

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

    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(time_build){
    LOGGER_FUNC_UNUSED;

    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(data_curent){
    LOGGER_FUNC_UNUSED;

    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(time_curent){
    LOGGER_FUNC_UNUSED;

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

LOGGER_TOKEN_GENERATE_FUNC(alignl){
    LOGGER_FUNC_UNUSED;

    return LE_OK;
}

LOGGER_TOKEN_GENERATE_FUNC(aliggt){
    LOGGER_FUNC_UNUSED;

    return LE_OK;
}
