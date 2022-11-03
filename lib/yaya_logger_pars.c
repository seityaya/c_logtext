//Author                 : Seityagiya Terlekchi
//Contacts               : seityaya@ukr.net
//Creation Date          : 2020.02
//License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
//SPDX-License-Identifier: LGPL-2.1-or-later
//Copyright © 2020-2022 Seityagiya Terlekchi. All rights reserved.

#include "yaya_logger.h"
#include "yaya_logger_private.h"

logger_error logger_pars(___logger *lvg, const char *format, ___logger_tokens** tokens)
{
    (*tokens) = (___logger_tokens*)malloc(sizeof(___logger_tokens));
    memset((*tokens), 0, sizeof(___logger_tokens));

    (*tokens)->mas_opt = NULL;

    { /*Подсчет количества токенов и спецификаторов, выделение памяти и определение их диапазона и типа*/
        uintmax_t j = 0;
        for (uintmax_t i = 0; i < strlen(format); i++)
        {
            (*tokens)->mas_opt = (___logger_token_mas*)realloc((*tokens)->mas_opt, sizeof(___logger_token_mas) * (j + 1));
            memset(&(*tokens)->mas_opt[j], 0, sizeof(___logger_token_mas));

            if ((format[i] == ___logger_token_list[LEF_TOK].name[0])
                && (isalpha(format[i + 1])
                    || (format[i + 1] == ___logger_token_list[LEF_CAT].name[0])))
            {
                ((*tokens)->mas_opt)[j].id  = LEF_TOK;
                ((*tokens)->mas_opt)[j].beg = i;
                do
                {
                    ((*tokens)->mas_opt)[j].end = i;
                    i++;
                }
                while ((isalpha(format[i]) || (format[i] == ___logger_token_list[LEF_CAT].name[0])));

                if ((format[i] == ___logger_token_list[LEF_SPE].name[0])
                    && (isdigit(format[i + 1])
                        || (format[i + 1] == ___logger_token_list[LEF_HID].name[0])
                        || (format[i + 1] == ___logger_token_list[LEF_SEP].name[0])))
                {
                    ((*tokens)->mas_opt)[j].spe = (___logger_token_specifiers*) malloc(sizeof(___logger_token_specifiers));
                    memset(((*tokens)->mas_opt)[j].spe, 0, sizeof(___logger_token_specifiers));

                    ((*tokens)->mas_opt)[j].spe->beg = i;
                    do
                    {
                        ((*tokens)->mas_opt)[j].spe->end = i;
                        i++;
                    }
                    while (isdigit(format[i])
                           || format[i] == ___logger_token_list[LEF_HID].name[0]
                           || format[i] == ___logger_token_list[LEF_SEP].name[0]);
                }
                i--;
            }
            else
            {
                if(format[i] == ___logger_token_list[LEF_TOK].name[0])
                {
                    i++;
                }
                ((*tokens)->mas_opt)[j].beg = i;
                ((*tokens)->mas_opt)[j].id  = LEF_STR;
                do
                {
                    ((*tokens)->mas_opt)[j].end = i;
                    i++;
                }
                while (!(format[i] == ___logger_token_list[LEF_TOK].name[0]
                         && isalpha(format[i + 1]))
                       && (format[i] != '\0'));
                i--;
            }

            j++;
        }
        (*tokens)->num_token = j;
    }

    { /*Определение типа токенов*/
        for (uintmax_t i = 0; i < (*tokens)->num_token; i++) {
            memset(lvg->tmp_buff, 0, lvg->tmp_buff_size);
            if (((*tokens)->mas_opt)[i].id == LEF_TOK) {
                strncpy(lvg->tmp_buff, &format[((*tokens)->mas_opt)[i].beg + 1], ((*tokens)->mas_opt)[i].end - ((*tokens)->mas_opt)[i].beg);
                for (uintmax_t j = LEF_BEG + 1; j < LEF_END; j++) {
                    if (strcmp(lvg->tmp_buff, ___logger_token_list[j].name) == 0) {
                        ((*tokens)->mas_opt)[i].id = j;
                        break;
                    }
                }
            }
            if(((*tokens)->mas_opt)[i].id == LEF_TOK){
                ((*tokens)->mas_opt)[i].id = LEF_STR;

                if(((*tokens)->mas_opt)[i].spe != NULL)
                {
                    ((*tokens)->mas_opt)[i].end = ((*tokens)->mas_opt)[i].spe->end;
                    free(((*tokens)->mas_opt)[i].spe);
                    ((*tokens)->mas_opt)[i].spe = NULL;
                }

            }
        }
    }

    { /*Парсинг спецификаторов*/
        for (uintmax_t i = 0; i < (*tokens)->num_token; i++)
        {
            if (((*tokens)->mas_opt[i].spe) != NULL)
            {
                memset(lvg->tmp_buff, 0, lvg->tmp_buff_size);
                strncpy(lvg->tmp_buff, &format[((*tokens)->mas_opt)[i].spe->beg ] , (((*tokens)->mas_opt)[i].spe->end - ((*tokens)->mas_opt)[i].spe->beg + 1) );

                uintmax_t k   = 0;
                uintmax_t beg = ((*tokens)->mas_opt)[i].spe->beg + 1;
                uintmax_t end = ((*tokens)->mas_opt)[i].spe->end + 1;

                if (format[((*tokens)->mas_opt)[i].spe->beg + 1] == ___logger_token_list[LEF_HID].name[0])
                {
                    beg++;
                    ((*tokens)->mas_opt)[i].spe->lfs = LFS_LEF;
                }
                if (format[((*tokens)->mas_opt)[i].spe->end] == ___logger_token_list[LEF_HID].name[0] && ((*tokens)->mas_opt)[i].spe->lfs != LFS_LEF)
                {
                    end--;
                    ((*tokens)->mas_opt)[i].spe->lfs = LFS_RIG;
                }
                if (format[beg] == '0')
                {
                    beg++;
                    ((*tokens)->mas_opt)[i].spe->lfs = LFS_NUL;
                }
                while (isdigit(format[beg + k]) || format[beg + k] == ___logger_token_list[LEF_SEP].name[0])
                {
                    k++;
                }
                end = beg + k;

                memset(lvg->tmp_buff, 0, lvg->tmp_buff_size);
                strncpy(lvg->tmp_buff, &format[beg], end - beg);

                if (format[beg] == ___logger_token_list[LEF_SEP].name[0])
                {
                    if (((*tokens)->mas_opt)[i].spe->lfs != LFS_NUL && ((*tokens)->mas_opt)[i].spe->lfs != LFS_LEF)
                    {
                        ((*tokens)->mas_opt)[i].spe->lfs = LFS_RIG;
                    }
                    sscanf(lvg->tmp_buff, ".%" PRIXMAX "", &((*tokens)->mas_opt)[i].spe->rig);
                }
                else
                {
                    if (((*tokens)->mas_opt)[i].spe->lfs != LFS_NUL && ((*tokens)->mas_opt)[i].spe->lfs != LFS_RIG)
                    {
                        ((*tokens)->mas_opt)[i].spe->lfs = LFS_LEF;
                    }
                    sscanf(lvg->tmp_buff, "%" PRIXMAX ".", &((*tokens)->mas_opt)[i].spe->lef);
                }
            }
        }
    }

    { /*Тестовый вывод*/
        if(LOGGER_DEBUG_FORMAT == 1)
        {
            printf("FORMAT = %s\n", format);
            for (uintmax_t i = 0; i < (*tokens)->num_token; i++)
            {
                const int f1 = 80;
                int k1 = 0;
                memset(lvg->tmp_buff, 0, lvg->tmp_buff_size);
                strncpy(lvg->tmp_buff, &format[(*tokens)->mas_opt[i].beg], (*tokens)->mas_opt[i].end - (*tokens)->mas_opt[i].beg + 1);
                char buffmod[LOGGER_TMP_BUFF_SIZE] = {0}; //FIXME
                if ((*tokens)->mas_opt[i].spe != NULL)
                {
                    strncpy(buffmod, &format[(*tokens)->mas_opt[i].spe->beg], (*tokens)->mas_opt[i].spe->end - (*tokens)->mas_opt[i].spe->beg + 1);
                }
                printf("%3" PRIXMAX " | %10s = %02" PRIXMAX " | %3" PRIXMAX " <%3" PRIXMAX "> %3" PRIXMAX " | -%s- %n",
                       i,
                       ___logger_token_list[(*tokens)->mas_opt[i].id].name,
                        (*tokens)->mas_opt[i].id,
                        (*tokens)->mas_opt[i].beg,
                        (*tokens)->mas_opt[i].end - (*tokens)->mas_opt[i].beg + 1,
                        (*tokens)->mas_opt[i].end,
                        lvg->tmp_buff,
                        &k1);
                printf("%*s %" PRIXMAX " [(%2" PRIXMAX ") (%2" PRIXMAX ")] -%s- \n",
                       f1 - k1,
                       "",
                       (*tokens)->mas_opt[i].spe != NULL ? (*tokens)->mas_opt[i].spe->lfs : 0,
                       (*tokens)->mas_opt[i].spe != NULL ? (*tokens)->mas_opt[i].spe->lef : 0,
                       (*tokens)->mas_opt[i].spe != NULL ? (*tokens)->mas_opt[i].spe->rig : 0,
                       buffmod);
            }
            printf("\n");
        }
    }

    return LE_OK;
}
