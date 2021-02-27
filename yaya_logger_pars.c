#include "yaya_logger.h"



void ___logger_pars(logger *lvg, const char *format, logger_token_mas **mas_opt_f, uintmax_t *num_token)
{
    logger_token_mas *mas_opt = malloc(sizeof(logger_token_mas));
    { /*Подсчет количества токенов и спецификаторов, выделение памяти и определение их диапазона и типа*/
        uintmax_t j = 0;
        for (uintmax_t i = 0; i < strlen(format); i++) {
            mas_opt = realloc(mas_opt, sizeof(logger_token_mas) * (j + 1));
            if (format[i] == logger_token_list[LEF_TOK].name[0] && isalpha(format[i + 1])) {
                mas_opt[j].id  = LEF_TOK;
                mas_opt[j].beg = i;
                do {
                    mas_opt[j].end = i;
                    i++;
                } while (isalpha(format[i]));
                if (format[i] == logger_token_list[LEF_SPE].name[0]
                    && (isdigit(format[i + 1]) || format[i + 1] == logger_token_list[LEF_HID].name[0]
                        || format[i + 1] == logger_token_list[LEF_SEP].name[0])) {
                    mas_opt[j].spe      = calloc(1, sizeof(logger_token_specifiers));
                    mas_opt[j].spe->beg = i;
                    do {
                        mas_opt[j].spe->end = i;
                        i++;
                    } while (isdigit(format[i]) || format[i] == logger_token_list[LEF_HID].name[0]
                             || format[i] == logger_token_list[LEF_SEP].name[0]);
                }
                i--;
            }
            else {
                mas_opt[j].beg = i;
                mas_opt[j].id  = LEF_str;
                do {
                    mas_opt[j].end = i;
                    i++;
                } while (!(format[i] == logger_token_list[LEF_TOK].name[0] && isalpha(format[i + 1]))
                         && (format[i] != '\0'));
                i--;
            }
            j++;
        }
        *num_token = j;
    }

    { /*Определение типа токенов*/
        for (uintmax_t i = 0; i < *num_token; i++) {
            memset(lvg->tmp_buff, 0, LOGGER_TMP_BUFF_SIZE);
            if (mas_opt[i].id == LEF_TOK) {
                strncpy(lvg->tmp_buff, &format[mas_opt[i].beg + 1], mas_opt[i].end - mas_opt[i].beg);
                for (uintmax_t j = 0; j < LEF_END; j++) {
                    if (strstr(lvg->tmp_buff, logger_token_list[j].name) != NULL) {
                        mas_opt[i].id = j;
                        break;
                    }
                }
            }
        }
    }

    { /*Парсинг спецификаторов*/
        for (uintmax_t i = 0; i < *num_token; i++) {
            if (mas_opt[i].spe != NULL) {
                memset(lvg->tmp_buff, 0, LOGGER_TMP_BUFF_SIZE);
                strncpy(lvg->tmp_buff, &format[mas_opt[i].spe->beg], mas_opt[i].spe->end - mas_opt[i].spe->beg + 1);
                int k   = 0;
                int beg = mas_opt[i].spe->beg + 1;
                int end = mas_opt[i].spe->end + 1;

                if (format[mas_opt[i].spe->beg + 1] == logger_token_list[LEF_HID].name[0]) {
                    beg++;
                    mas_opt[i].spe->lfs = LFS_LEF;
                }
                if (format[mas_opt[i].spe->end] == logger_token_list[LEF_HID].name[0]
                    && mas_opt[i].spe->lfs != LFS_LEF) {
                    end--;
                    mas_opt[i].spe->lfs = LFS_RIG;
                }
                if (format[beg] == '0') {
                    beg++;
                    mas_opt[i].spe->lfs = LFS_NUL;
                }
                while (isdigit(format[beg + k]) || format[beg + k] == logger_token_list[LEF_SEP].name[0]) {
                    k++;
                }
                end = beg + k;
                memset(lvg->tmp_buff, 0, LOGGER_TMP_BUFF_SIZE);
                strncpy(lvg->tmp_buff, &format[beg], end - beg);

                if (format[beg] == logger_token_list[LEF_SEP].name[0]) {
                    if (mas_opt[i].spe->lfs != LFS_NUL && mas_opt[i].spe->lfs != LFS_LEF) {
                        mas_opt[i].spe->lfs = LFS_RIG;
                    }
                    //(char*)logger_token_list[LEF_SEP].name, (char*)logger_token_list[LEF_SPE].name
                    sscanf(lvg->tmp_buff, ".%" PRIXMAX "", &mas_opt[i].spe->rig);
                }
                else {
                    if (mas_opt[i].spe->lfs != LFS_NUL && mas_opt[i].spe->lfs != LFS_RIG) {
                        mas_opt[i].spe->lfs = LFS_LEF;
                    }
                    sscanf(lvg->tmp_buff, "%" PRIXMAX ".", &mas_opt[i].spe->lef);
                }
            }
        }
    }

    *mas_opt_f = mas_opt;

#ifdef LOGGER_DEBUG
    { /*Тестовый вывод*/
        printf("FORMAT = %s\n", format);
        for (uintmax_t i = 0; i < *num_token; i++) {
            int k1 = 0;
            int f1 = 80;
            memset(lvg->tmp_buff, 0, LOGGER_TMP_BUFF_SIZE);
            strncpy(lvg->tmp_buff, &format[mas_opt[i].beg], mas_opt[i].end - mas_opt[i].beg + 1);
            char buffmod[300] = {0};
            if (mas_opt[i].spe != NULL) {
                strncpy(buffmod, &format[mas_opt[i].spe->beg], mas_opt[i].spe->end - mas_opt[i].spe->beg + 1);
            }
            printf("%3ld | %10s = %02ld | %3ld <%3ld> %3ld | -%s- %n",
                   i,
                   logger_token_list[mas_opt[i].id].name,
                    mas_opt[i].id,
                    mas_opt[i].beg,
                    mas_opt[i].end - mas_opt[i].beg + 1,
                    mas_opt[i].end,
                    lvg->tmp_buff,
                    &k1);
            printf("%*s %ld [(%2ld) (%2ld)] -%s-    \n",
                   f1 - k1,
                   "",
                   mas_opt[i].spe != NULL ? mas_opt[i].spe->lfs : 0,
                   mas_opt[i].spe != NULL ? mas_opt[i].spe->lef : 0,
                   mas_opt[i].spe != NULL ? mas_opt[i].spe->rig : 0,
                   buffmod);
        }
        printf("\n");
    }
#endif
}
