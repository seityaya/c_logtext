#include "yaya_logger.h"

void format_build_num(___logger *lvg, ___logger_token_mas *mas_opt, uintmax_t buff_orig)
{
  mas_opt->beglog = lvg->out_offset;
  if (mas_opt->spe != NULL) {
    if (mas_opt->spe->lfs == LFS_NUL) {
      lvg->out_offset += sprintf(&lvg->out_buff[lvg->out_offset], "%0*" PRIuMAX "", (int)mas_opt->spe->lef, (uintmax_t)buff_orig);
    }
    else if (mas_opt->spe->lfs == LFS_LEF) {
      lvg->out_offset
          += sprintf(&lvg->out_buff[lvg->out_offset], "%*" PRIuMAX "", (int)mas_opt->spe->lef, (uintmax_t)buff_orig);
    }
    else if (mas_opt->spe->lfs == LFS_RIG) {
      lvg->out_offset += sprintf(&lvg->out_buff[lvg->out_offset],
                                 "%-*" PRIuMAX "",
                                 (int)mas_opt->spe->rig,
                                 (uintmax_t)buff_orig);
    }
  }
  else {
    lvg->out_offset += sprintf(&lvg->out_buff[lvg->out_offset], "%" PRIuMAX "", (uintmax_t)buff_orig);
  }
  mas_opt->endlog = lvg->out_offset;
}


void format_build_str(___logger *lvg, ___logger_token_mas *mas_opt, const char *buff_orig)
{
    char buff[LOGGER_TMP_BUFF_SIZE] = {0};
    mas_opt->beglog                 = lvg->out_offset;
    if (mas_opt->spe != NULL) {
        uintmax_t max = mas_opt->spe->lef > mas_opt->spe->rig ? mas_opt->spe->lef : mas_opt->spe->rig;
        uintmax_t len = strlen(buff_orig);
        if (len <= mas_opt->spe->lef || len <= mas_opt->spe->rig) {
            goto jmp_else_null;
        }
        if (mas_opt->spe->lfs == LFS_LEF) {
            strncpy(buff, &buff_orig[len - max], max);
            strncpy(buff, LOGGER_HIDDEN_STR, strlen(LOGGER_HIDDEN_STR));
            lvg->out_offset += sprintf(&lvg->out_buff[lvg->out_offset], "%s", buff);
        }
        else if (mas_opt->spe->lfs == LFS_RIG) {
            strncpy(buff, &buff_orig[0], max);
            strncpy(&buff[max - strlen(LOGGER_HIDDEN_STR)], LOGGER_HIDDEN_STR, strlen(LOGGER_HIDDEN_STR));
            lvg->out_offset += sprintf(&lvg->out_buff[lvg->out_offset], "%s", buff);
        }
        else {
        jmp_else_null:
            if (mas_opt->spe->lef != 0) {
                lvg->out_offset += sprintf(&lvg->out_buff[lvg->out_offset], "%*s", (int)max, buff_orig);
            }
            else if (mas_opt->spe->rig != 0) {
                lvg->out_offset += sprintf(&lvg->out_buff[lvg->out_offset], "%-*s", (int)max, buff_orig);
            }
            else {
                goto jmp_else_main;
            }
        }
    }
    else {
    jmp_else_main:
        lvg->out_offset += sprintf(&lvg->out_buff[lvg->out_offset], "%s", buff_orig);
    }
    mas_opt->endlog = lvg->out_offset;
}

LOGGER_TOKEN_GENERATE_FUNC(str){
    LOGGER_FUNC_UNUSED;
    strncpy(lvg->tmp_buff, &format[mas_opt->beg], mas_opt->end - mas_opt->beg + 1);
    format_build_str(lvg, mas_opt, lvg->tmp_buff);
}

LOGGER_TOKEN_GENERATE_FUNC(line){
    LOGGER_FUNC_UNUSED;
    format_build_num(lvg, mas_opt, line);
}

LOGGER_TOKEN_GENERATE_FUNC(file){
    LOGGER_FUNC_UNUSED;
    format_build_str(lvg, mas_opt, file);
}

LOGGER_TOKEN_GENERATE_FUNC(func){
    LOGGER_FUNC_UNUSED;
    format_build_str(lvg, mas_opt, func);
}

LOGGER_TOKEN_GENERATE_FUNC(type){
    LOGGER_FUNC_UNUSED;
    for (uintmax_t j = 0; j < lvg->type.num - 1; j++) {
        if (type == L_ALL) {
            strcpy(lvg->tmp_buff, lvg->type.ptr[lvg->type.num - 1].name);
            break;
        } else if (type == L_NUL) {
            strcpy(lvg->tmp_buff, lvg->type.ptr[0].name);
            break;
        } else {
            if (LOGGER_BIT_GET(type, j)) {
                strcat(lvg->tmp_buff, lvg->type.ptr[j + 1].name);
            }
        }
    }
    format_build_str(lvg, mas_opt, lvg->tmp_buff);
}


LOGGER_TOKEN_GENERATE_FUNC(name){
    LOGGER_FUNC_UNUSED;

    for (uintmax_t j = 0; j < lvg->name.num - 1; j++) {
        if (name == LL_ALL) {
            strcpy(lvg->tmp_buff, lvg->name.ptr[lvg->name.num - 1].name);
            break;
        } else if (name == LL_NUL) {
            strcpy(lvg->tmp_buff, lvg->name.ptr[0].name);
            break;
        } else {
            if (LOGGER_BIT_GET(name, j)) {
                strcat(lvg->tmp_buff, lvg->name.ptr[j + 1].name);
            }
        }
    }
    format_build_str(lvg, mas_opt, lvg->tmp_buff);
}

LOGGER_TOKEN_GENERATE_FUNC(mesg){
    LOGGER_FUNC_UNUSED;
    vsprintf(lvg->tmp_buff, mes, mes_list);
    format_build_str(lvg, mas_opt, lvg->tmp_buff);
}

LOGGER_TOKEN_GENERATE_FUNC(debug){
    LOGGER_FUNC_UNUSED;
    format_build_str(lvg, mas_opt, debug);
}

LOGGER_TOKEN_GENERATE_FUNC(count){
    LOGGER_FUNC_UNUSED;

}

LOGGER_TOKEN_GENERATE_FUNC(curnum){
    LOGGER_FUNC_UNUSED;

}

LOGGER_TOKEN_GENERATE_FUNC(absnum){
    LOGGER_FUNC_UNUSED;

}

LOGGER_TOKEN_GENERATE_FUNC(short_path){
    LOGGER_FUNC_UNUSED;

}

LOGGER_TOKEN_GENERATE_FUNC(full_path){
    LOGGER_FUNC_UNUSED;

}

LOGGER_TOKEN_GENERATE_FUNC(data_build){
    LOGGER_FUNC_UNUSED;

}

LOGGER_TOKEN_GENERATE_FUNC(time_build){
    LOGGER_FUNC_UNUSED;

}

LOGGER_TOKEN_GENERATE_FUNC(data_curent){
    LOGGER_FUNC_UNUSED;

}

LOGGER_TOKEN_GENERATE_FUNC(time_curent){
    LOGGER_FUNC_UNUSED;

}

LOGGER_TOKEN_GENERATE_FUNC(prog){
    LOGGER_FUNC_UNUSED;

}

LOGGER_TOKEN_GENERATE_FUNC(prog_v){
    LOGGER_FUNC_UNUSED;

}

LOGGER_TOKEN_GENERATE_FUNC(prog_p){
    LOGGER_FUNC_UNUSED;

}

LOGGER_TOKEN_GENERATE_FUNC(proj){
    LOGGER_FUNC_UNUSED;

}

LOGGER_TOKEN_GENERATE_FUNC(compiler){
    LOGGER_FUNC_UNUSED;

}

LOGGER_TOKEN_GENERATE_FUNC(compiler_v){
    LOGGER_FUNC_UNUSED;

}


LOGGER_TOKEN_GENERATE_FUNC(tik_core){
    LOGGER_FUNC_UNUSED;

}

LOGGER_TOKEN_GENERATE_FUNC(tik_sec){
    LOGGER_FUNC_UNUSED;

}

LOGGER_TOKEN_GENERATE_FUNC(tic_rtos){
    LOGGER_FUNC_UNUSED;

}

LOGGER_TOKEN_GENERATE_FUNC(tik_unix){
    LOGGER_FUNC_UNUSED;

}


LOGGER_TOKEN_GENERATE_FUNC(type_filter){
    LOGGER_FUNC_UNUSED;

}

LOGGER_TOKEN_GENERATE_FUNC(name_filter){
    LOGGER_FUNC_UNUSED;

}

LOGGER_TOKEN_GENERATE_FUNC(type_mask){
    LOGGER_FUNC_UNUSED;

}

LOGGER_TOKEN_GENERATE_FUNC(name_mask){
    LOGGER_FUNC_UNUSED;

}

LOGGER_TOKEN_GENERATE_FUNC(type_list){
    LOGGER_FUNC_UNUSED;

}

LOGGER_TOKEN_GENERATE_FUNC(name_list){
    LOGGER_FUNC_UNUSED;

}


LOGGER_TOKEN_GENERATE_FUNC(seed){
    LOGGER_FUNC_UNUSED;

}


LOGGER_TOKEN_GENERATE_FUNC(alignl){
    LOGGER_FUNC_UNUSED;

}

LOGGER_TOKEN_GENERATE_FUNC(aliggt){
    LOGGER_FUNC_UNUSED;

}

//            case LEF_COUNT: {
//                format_build_num(&mas_opt[i], count);
//                break;
//            }
//            case LEF_MESSAGE: {
//                vsprintf(lvg->tmp_buff, mes, mes_list);
//                format_build_str(&mas_opt[i], lvg->tmp_buff);
//                break;
//            }
//            case LEF_TYPE: {
//                for (uintmax_t j = 0; j < lvg->type.num - 1; j++) {
//                    if (type == L_ALL) {
//                        strcpy(lvg->tmp_buff, &logger_type_def[j + 1].name[2]);
//                        break;
//                    } else if (type == L_NUL) {
//                        strcpy(lvg->tmp_buff, &logger_type_def[0].name[2]);
//                        break;
//                    } else {
//                        if (LOGGER_BIT_GET(type, j)) {
//                            strcat(lvg->tmp_buff, &logger_type_def[j + 1].name[2]);
//                        }
//                    }
//                }
//                format_build_str(&mas_opt[i], lvg->tmp_buff);
//                break;
//            }
//            case LEF_NAME: {
//                for (uintmax_t j = 0; j < lvg->name.num - 1; j++) {
//                    if (name == LL_ALL) {
//                        strcpy(lvg->tmp_buff, &logger_name_def[j + 1].name[3]);
//                        break;
//                    } else if (name == LL_NUL) {
//                        strcpy(lvg->tmp_buff, &logger_name_def[0].name[3]);
//                        break;
//                    } else {
//                        if (LOGGER_BIT_GET(name, j)) {
//                            strcat(lvg->tmp_buff, &logger_name_def[j + 1].name[3]);
//                        }
//                    }
//                }
//                format_build_str(&mas_opt[i], lvg->tmp_buff);
//                break;
//            }
//            case LEF_CURNUM: {
//                format_build_num(&mas_opt[i], &lvg->curnum);
//                break;
//            }
//            case LEF_ABSNUM: {
//                format_build_num(&mas_opt[i], &lvg->absnum);
//                break;
//            }
//            case LEF_PROG: {
//                format_build_str(&mas_opt[i], lvg->pdefn->prog);
//                break;
//            }
//            case LEF_PROJ: {
//                format_build_str(&mas_opt[i], lvg->pdefn->proj);
//                break;
//            }
//            case LEF_VERSION: {
//                format_build_str(&mas_opt[i], lvg->pdefn->version);
//                break;
//            }
//                //            case LEF_PROJPATH: {
//                //                format_build_str(&mas_opt[i], lvg->pglob->projpath);
//                //                break;
//                //            }

//                //            case LEF_DATA_BUILD: {
//                //                format_build_str(&mas_opt[i],
//                //                lvg->pglob->data_build); break;
//                //            }
//                //            case LEF_TIME_BUILD: {
//                //                format_build_str(&mas_opt[i],
//                //                lvg->pglob->time_build); break;
//                //            }
//                //            case LEF_SEED: {
//                //                format_build_num(&mas_opt[i], &lvg->pdefn->seed);
//                //                break;
//                //            }
//                //            case LEF_TIKSEC: {
//                //                break;
//                //            }
//                //            case LEF_DATA: {
//                //                sprintf(buff, "%d", 0);
//                //                strcat(lvg->out_buff, buff);
//                //                break;
//                //            }
//                //            case LEF_TIME: {
//                //                sprintf(buff, "%d", 0);
//                //                strcat(lvg->out_buff, buff);
//                //                break;
//                //            }
//                //            case LEF_FULLPATH: {
//                //                break;
//                //            }
//                //            case LEF_SHORPATH: {
//                //                break;
//                //            }
//                //            case LEF_ALIGNL: {
//                //                break;
//                //            }
//                //            case LEF_ALIGGT: {
//                //                break;
//                //            }
//                //            case LEF_NAME_ALL: {
//                //                { /*вывод настроек фильтрации*/
//                //                    for (uintmax_t i = 0; i < lvg->type_num - 1;
//                //                    i++) {
//                //                        if (lvg->psett->type == L_ALL) {
//                //                            printf("%s ",
//                //                            lvg->ptype[lvg->type_num].name); break;
//                //                        } else if (lvg->psett->type == L_NUL) {
//                //                            printf("%s ", lvg->ptype[0].name);
//                //                            break;
//                //                        } else {
//                //                            if (LOGGER_BIT_GET(lvg->psett->type, i))
//                //                            {
//                //                                printf("%s ", lvg->ptype[i +
//                //                                1].name);
//                //                            }
//                //                        }
//                //#define GCC_VERSION (__GNUC__ * 10000 \
//                        //                     + __GNUC_MINOR__ * 100 \
//                        //                     + __GNUC_PATCHLEVEL__)
//                //                    }
//                //                }
//                //            }
//            default: {
//                lvg->error = LOGGER_TRUE;
//                strncpy(lvg->tmp_buff, &format[mas_opt[i].beg], mas_opt[i].end - mas_opt[i].beg + 1);
//                // sprintf(&lvg->out_buff[lvg->out_offset], "WARNING: NOT FOUND TOKEN
//                // = %s", buff);
//                printf("LOGGER WARNING: NOT FOUND TOKEN: %s\n", lvg->tmp_buff);
//                return;
//            }
//            }
//        }
//    }


