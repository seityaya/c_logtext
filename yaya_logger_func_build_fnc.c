#include "yaya_logger_func_build_fnc.h"

#include "yaya_logger.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LOGGER_FUNC_GENERATE(void){

}

LOGGER_FUNC_GENERATE(str){
  strncpy(lvg->tmp_buff, &format[mas_opt->beg], mas_opt->end - mas_opt->beg + 1);
  format_build_str(lvg, mas_opt, lvg->tmp_buff);
}

LOGGER_FUNC_GENERATE(line){
  format_build_num(lvg, mas_opt, line);
}

LOGGER_FUNC_GENERATE(file){
  format_build_str(lvg, mas_opt, file);
}

LOGGER_FUNC_GENERATE(func){
  format_build_str(lvg, mas_opt, func);
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
