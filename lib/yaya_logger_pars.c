#include "yaya_logger.h"

void ___logger_pars(const char *format, ___logger_tokens** tokens)
{
    char tmp_buff[LOGGER_TMP_BUFF_SIZE] = {0};

    (*tokens) = (___logger_tokens*)malloc(sizeof(___logger_tokens));
    memset((*tokens), 0, sizeof(___logger_tokens));

    (*tokens)->mas_opt = NULL;

    { /*Подсчет количества токенов и спецификаторов, выделение памяти и определение их диапазона и типа*/
        uintmax_t j = 0;
        for (uintmax_t i = 0; i < strlen(format); i++)
        {
            (*tokens)->mas_opt = (___logger_token_mas*)realloc((*tokens)->mas_opt, sizeof(___logger_token_mas) * (j + 1));
            memset(&(*tokens)->mas_opt[j], 0, sizeof(___logger_token_mas));

            if ((format[i] == ___logger_token_list[LEF_TOK].name[0]) &&
                (isalpha(format[i + 1]) ||
                 (format[i + 1] == ___logger_token_list[LEF_CAT].name[0])))
            {
                ((*tokens)->mas_opt)[j].id  = LEF_TOK;
                ((*tokens)->mas_opt)[j].beg = i;
                do {
                    ((*tokens)->mas_opt)[j].end = i;
                    i++;
                } while ((isalpha(format[i]) || (format[i] == ___logger_token_list[LEF_CAT].name[0])));

                if ((format[i] == ___logger_token_list[LEF_SPE].name[0]) &&
                    (isdigit(format[i + 1]) ||
                     (format[i + 1] == ___logger_token_list[LEF_HID].name[0])   ||
                     (format[i + 1] == ___logger_token_list[LEF_SEP].name[0])))
                {
                    ((*tokens)->mas_opt)[j].spe      = (___logger_token_specifiers*) malloc(sizeof(___logger_token_specifiers));
                    memset(((*tokens)->mas_opt)[j].spe, 0, sizeof(___logger_token_specifiers));

                    ((*tokens)->mas_opt)[j].spe->beg = i;
                    do {
                        ((*tokens)->mas_opt)[j].spe->end = i;
                        i++;
                    } while (isdigit(format[i]) || format[i] == ___logger_token_list[LEF_HID].name[0]
                             || format[i] == ___logger_token_list[LEF_SEP].name[0]);
                }
                i--;
            }
            else
            {
                if(format[i] == ___logger_token_list[LEF_TOK].name[0]){
                    i++;
                }
                ((*tokens)->mas_opt)[j].beg = i;
                ((*tokens)->mas_opt)[j].id  = LEF_str;
                do {
                    ((*tokens)->mas_opt)[j].end = i;
                    i++;
                } while (!(format[i] == ___logger_token_list[LEF_TOK].name[0] && isalpha(format[i + 1])) && (format[i] != '\0'));
                i--;
            }

            j++;
        }
        (*tokens)->num_token = j;
    }

    { /*Определение типа токенов*/
        for (uintmax_t i = 0; i < (*tokens)->num_token; i++) {
            memset(tmp_buff, 0, LOGGER_TMP_BUFF_SIZE);
            if (((*tokens)->mas_opt)[i].id == LEF_TOK) {
                strncpy(tmp_buff, &format[((*tokens)->mas_opt)[i].beg + 1], ((*tokens)->mas_opt)[i].end - ((*tokens)->mas_opt)[i].beg);
                for (uintmax_t j = LEF_BEG + 1; j < LEF_END; j++) {
                    if (strcmp(tmp_buff, ___logger_token_list[j].name) == 0) {
                        ((*tokens)->mas_opt)[i].id = j;
                        break;
                    }
                }
            }
            if(((*tokens)->mas_opt)[i].id == LEF_TOK){
                ((*tokens)->mas_opt)[i].id = LEF_str;
            }
        }
    }

    { /*Парсинг спецификаторов*/
        for (uintmax_t i = 0; i < (*tokens)->num_token; i++)
        {
            if (((*tokens)->mas_opt[i].spe) != NULL) {
                memset(tmp_buff, 0, LOGGER_TMP_BUFF_SIZE);

                strncpy(tmp_buff, &format[((*tokens)->mas_opt)[i].spe->beg ] , (((*tokens)->mas_opt)[i].spe->end - ((*tokens)->mas_opt)[i].spe->beg + 1) );
                int k   = 0;
                int beg = ((*tokens)->mas_opt)[i].spe->beg + 1;
                int end = ((*tokens)->mas_opt)[i].spe->end + 1;

                if (format[((*tokens)->mas_opt)[i].spe->beg + 1] == ___logger_token_list[LEF_HID].name[0]) {
                    beg++;
                    ((*tokens)->mas_opt)[i].spe->lfs = LFS_LEF;
                }
                if (format[((*tokens)->mas_opt)[i].spe->end] == ___logger_token_list[LEF_HID].name[0]
                    && ((*tokens)->mas_opt)[i].spe->lfs != LFS_LEF) {
                    end--;
                    ((*tokens)->mas_opt)[i].spe->lfs = LFS_RIG;
                }
                if (format[beg] == '0') {
                    beg++;
                    ((*tokens)->mas_opt)[i].spe->lfs = LFS_NUL;
                }
                while (isdigit(format[beg + k]) || format[beg + k] == ___logger_token_list[LEF_SEP].name[0]) {
                    k++;
                }
                end = beg + k;
                memset(tmp_buff, 0, LOGGER_TMP_BUFF_SIZE);
                strncpy(tmp_buff, &format[beg], end - beg);

                if (format[beg] == ___logger_token_list[LEF_SEP].name[0]) {
                    if (((*tokens)->mas_opt)[i].spe->lfs != LFS_NUL && ((*tokens)->mas_opt)[i].spe->lfs != LFS_LEF) {
                        ((*tokens)->mas_opt)[i].spe->lfs = LFS_RIG;
                    }
                    sscanf(tmp_buff, ".%" PRIXMAX "", &((*tokens)->mas_opt)[i].spe->rig);
                }
                else {
                    if (((*tokens)->mas_opt)[i].spe->lfs != LFS_NUL && ((*tokens)->mas_opt)[i].spe->lfs != LFS_RIG) {
                        ((*tokens)->mas_opt)[i].spe->lfs = LFS_LEF;
                    }
                    sscanf(tmp_buff, "%" PRIXMAX ".", &((*tokens)->mas_opt)[i].spe->lef);
                }
            }
        }
    }

#if LOGGER_DEBUG == 1
    { /*Тестовый вывод*/
        printf("FORMAT = %s\n", format);
        for (uintmax_t i = 0; i < *num_token; i++) {
            int k1 = 0;
            int f1 = 80;
            memset(tmp_buff, 0, LOGGER_TMP_BUFF_SIZE);
            strncpy(tmp_buff, &format[mas_opt[i].beg], mas_opt[i].end - mas_opt[i].beg + 1);
            char buffmod[300] = {0};
            if (mas_opt[i].spe != NULL) {
                strncpy(buffmod, &format[mas_opt[i].spe->beg], mas_opt[i].spe->end - mas_opt[i].spe->beg + 1);
            }
            printf("%3ld | %10s = %02ld | %3ld <%3ld> %3ld | -%s- %n",
                   i,
                   ___logger_token_list[mas_opt[i].id].name,
                    mas_opt[i].id,
                    mas_opt[i].beg,
                    mas_opt[i].end - mas_opt[i].beg + 1,
                    mas_opt[i].end,
                    tmp_buff,
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
