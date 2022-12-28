//Author                 : Seityagiya Terlekchi
//Contacts               : seityaya@ukr.net
//Creation Date          : 2020.02
//License Link           : https://spdx.org/licenses/LGPL-2.1-or-later.html
//SPDX-License-Identifier: LGPL-2.1-or-later
//Copyright © 2020-2022 Seityagiya Terlekchi. All rights reserved.

#include "yaya_logger.h"
#include "yaya_logger_private.h"

logger_error tokens_free(___logger *lvg, ___logger_tokens* tokens){
    if(tokens == NULL){
        return LE_ERR;
    }

    for(uintmax_t i = 0; i < tokens->num_token; i++) {
        logger_memory_del(lvg, &(tokens)->mas_opt[i].spe);
    }

    logger_memory_del(lvg, &(tokens)->mas_opt);
    logger_memory_del(lvg, &(tokens));

    return LE_OK;
}

logger_error tokens_init(___logger *lvg, const char *format, ___logger_tokens** tokens)
{
    /*Проверка на  NULL*/
    if((format == NULL) || (format[0] == '\0')){
        return LE_ERR;
    }

    /*Выделение памяти под токены*/
    if(!logger_memory_new(lvg, (void*)(&(*tokens)), NULL, sizeof(___logger_tokens))){
        return LE_ERR;
    }

    { /*Подсчет количества токенов и спецификаторов, выделение памяти и определение их диапазона и типа*/
        uintmax_t j = 0;
        for (uintmax_t i = 0; i < strlen(format); i++)
        {
            /*Выделение памяти под токен*/
            if(!logger_memory_new(lvg, (void*)(&((*tokens)->mas_opt)), (*tokens)->mas_opt, sizeof(___logger_token_mas) * (j + 1))){
                tokens_free(lvg, *tokens);
                return LE_ERR;
            }

            /*Проверка что текуще вхождение начало токена*/
            if ((format[i] == ___logger_token_list[LEF_TOK].name[0]) && isalpha(format[i + 1]))
            {
                ((*tokens)->mas_opt)[j].id  = LEF_TOK;
                ((*tokens)->mas_opt)[j].beg = i;
                do
                {
                    ((*tokens)->mas_opt)[j].end = i;
                    i++;
                }
                while ((isalpha(format[i]) || (format[i] == ___logger_token_list[LEF_CAT].name[0])));

                /*Проверка что текуще вхождение начало спецификатора*/
                if ((format[i] == ___logger_token_list[LEF_SPE].name[0]) &&
                    (isdigit(format[i + 1])
                     || (format[i + 1] == ___logger_token_list[LEF_HID].name[0])
                     || (format[i + 1] == ___logger_token_list[LEF_SEP].name[0])
                     || (format[i + 1] == ___logger_token_list[LEF_CAT].name[0])
                     || (format[i + 1] == '-')
                     || (format[i + 1] == '+')))
                {
                    /*Выделение памяти под спецификатор*/
                    if(!logger_memory_new(lvg, (void*)(&(((*tokens)->mas_opt)[j].spe)), NULL, sizeof(___logger_token_specifiers))){
                        tokens_free(lvg, *tokens);
                        return LE_ERR;
                    }

                    ((*tokens)->mas_opt)[j].spe->beg = i;
                    ((*tokens)->mas_opt)[j].spe->end = i;
                    i++;

                    /*Проверка что текуще вхождение конец спецификатора*/
                    do {
                        ((*tokens)->mas_opt)[j].spe->end = i;
                        if((format[i - 1] != ___logger_token_list[LEF_SPE].name[0]) &&
                           (
                               (format[i] == ___logger_token_list[LEF_HID].name[0])
                               || (format[i] == ___logger_token_list[LEF_SEP].name[0])
                               || (format[i] == ___logger_token_list[LEF_CAT].name[0])
                               || (format[i] == '-')
                               || (format[i] == '+'))){
                            i++;
                            break;
                        }
                        i++;
                    }
                    while (isdigit(format[i])
                           || (format[i] == ___logger_token_list[LEF_HID].name[0])
                           || (format[i] == ___logger_token_list[LEF_SEP].name[0])
                           || (format[i] == ___logger_token_list[LEF_CAT].name[0])
                           || (format[i] == '-')
                           || (format[i] == '+'));
                }
                i--;
            }
            else
            {
                /*Пропуск ключа токенов*/
                if(format[i] == ___logger_token_list[LEF_TOK].name[0])
                {
                    i++;
                }

                ((*tokens)->mas_opt)[j].id  = LEF_STR;
                ((*tokens)->mas_opt)[j].beg = i;
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

    { /*Определение имени токенов*/
        for (uintmax_t i = 0; i < (*tokens)->num_token; i++) {
            memset(lvg->tmp_buff, 0, lvg->tmp_buff_size);
            if (((*tokens)->mas_opt)[i].id == LEF_TOK) {
                strncpy(lvg->tmp_buff, &format[((*tokens)->mas_opt)[i].beg + 1], ((*tokens)->mas_opt)[i].end - ((*tokens)->mas_opt)[i].beg);
                for (uintmax_t j = LEF_BEG + 1; j < LEF_END; j++) {
                    if (strcmp(lvg->tmp_buff, ___logger_token_list[j].name) == 0) {
                        ((*tokens)->mas_opt)[i].id = j;
                        goto end_1;
                    }
                }
            }
            if(((*tokens)->mas_opt)[i].id == LEF_TOK){
                ((*tokens)->mas_opt)[i].id = LEF_STR;

                if(((*tokens)->mas_opt)[i].spe != NULL)
                {
                    ((*tokens)->mas_opt)[i].end = ((*tokens)->mas_opt)[i].spe->end;
                    logger_memory_del(lvg, &(((*tokens)->mas_opt)[i].spe));
                }
            }
end_1:;
        }
    }

    { /*Парсинг спецификаторов*/
        for (uintmax_t i = 0; i < (*tokens)->num_token; i++)
        {
            if ((*tokens)->mas_opt[i].spe == NULL) {
                continue;
            }

            uintmax_t beg = ((*tokens)->mas_opt)[i].spe->beg + 1;
            uintmax_t end = ((*tokens)->mas_opt)[i].spe->end + 1;

            memset(lvg->tmp_buff, 0, lvg->tmp_buff_size);
            snprintf(lvg->tmp_buff, end - beg + 1, "%s", &format[beg]);

            /*Поиск ограничителей*/
            ((*tokens)->mas_opt)[i].spe->lfs = LFS_NUL;
            if (format[beg] == ___logger_token_list[LEF_HID].name[0]) {
                beg++;
                ((*tokens)->mas_opt)[i].spe->lfs = LFS_LEF;
            }
            if (format[end] == ___logger_token_list[LEF_HID].name[0] && ((*tokens)->mas_opt)[i].spe->lfs != LFS_LEF) {
                end--;
                ((*tokens)->mas_opt)[i].spe->lfs = LFS_RIG;
            }

            /*Поиск отрывающих спецификаторов*/
            ((*tokens)->mas_opt)[i].spe->lms = LMS_VOID;
            if (format[beg] == '0') {
                beg++;
                ((*tokens)->mas_opt)[i].spe->lms = LMS_NUL;
            }
            if (format[beg] == '_') {
                beg++;
                ((*tokens)->mas_opt)[i].spe->lms = LMS_CAT;
            }
            if (format[beg] == '+') {
                beg++;
                ((*tokens)->mas_opt)[i].spe->lms = LMS_PLUS;
                if (format[beg] == '0') {
                    beg++;
                    ((*tokens)->mas_opt)[i].spe->lms = LMS_PLUS_NUL;
                }
                if (format[beg] == '_') {
                    beg++;
                    ((*tokens)->mas_opt)[i].spe->lms = LMS_PLUS_CAT;
                }
            }
            if (format[beg] == '-') {
                beg++;
                ((*tokens)->mas_opt)[i].spe->lms = LMS_MINUS;
                if (format[beg] == '0') {
                    beg++;
                    ((*tokens)->mas_opt)[i].spe->lms = LMS_MINUS_NUL;
                }
                if (format[beg] == '_') {
                    beg++;
                    ((*tokens)->mas_opt)[i].spe->lms = LMS_MINUS_CAT;
                }
            }

            /*Поиск ограничителей спецификатора*/
            end = beg;
            while (isdigit(format[end]) || format[end] == ___logger_token_list[LEF_SEP].name[0]) {
                end++;
            }

            if(beg == end){
                continue;
            }

            ((*tokens)->mas_opt)[i].spe->rig = -1;
            ((*tokens)->mas_opt)[i].spe->lef = -1;

            memset(lvg->tmp_buff, 0, lvg->tmp_buff_size);
            strncpy(lvg->tmp_buff, &format[beg], end - beg);

            if (format[beg] == ___logger_token_list[LEF_SEP].name[0]) {
                sscanf(lvg->tmp_buff, ".%" PRIuMAX "", &((*tokens)->mas_opt)[i].spe->rig);
                continue;
            }

            if (format[end] == ___logger_token_list[LEF_SEP].name[0]) {
                sscanf(lvg->tmp_buff, "%" PRIuMAX ".", &((*tokens)->mas_opt)[i].spe->lef);
                continue;
            }

            if (strchr(lvg->tmp_buff, ___logger_token_list[LEF_SEP].name[0]) == NULL) {
                sscanf(lvg->tmp_buff, "%" PRIuMAX "", &((*tokens)->mas_opt)[i].spe->lef);
                continue;
            }else{
                sscanf(lvg->tmp_buff, "%" PRIuMAX "." "%" PRIuMAX ".", &((*tokens)->mas_opt)[i].spe->lef, &((*tokens)->mas_opt)[i].spe->rig);
                continue;
            }
        }
    }

    { /*Тестовый вывод*/
        if(LOGGER_DEBUG_FORMAT == 1)
        {
            printf("\n");
            printf("FORMAT = %s\n", format);
            for (uintmax_t i = 0; i < (*tokens)->num_token; i++)
            {
                const int f1 = 80;
                int k1 = 0;
                memset(lvg->tmp_buff, 0, lvg->tmp_buff_size);
                strncpy(lvg->tmp_buff, &format[(*tokens)->mas_opt[i].beg], (*tokens)->mas_opt[i].end - (*tokens)->mas_opt[i].beg + 1);

                printf("%3" PRIXMAX " | %12s = %02" PRIXMAX " | %3" PRIXMAX " <%3" PRIXMAX "> %3" PRIXMAX " | ]%s[ %n",
                       i,
                       ___logger_token_list[(*tokens)->mas_opt[i].id].name,
                        (*tokens)->mas_opt[i].id,
                        (*tokens)->mas_opt[i].beg,
                        (*tokens)->mas_opt[i].end - (*tokens)->mas_opt[i].beg + 1,
                        (*tokens)->mas_opt[i].end,
                        lvg->tmp_buff,
                        &k1);

                memset(lvg->tmp_buff, 0, lvg->tmp_buff_size);
                if ((*tokens)->mas_opt[i].spe != NULL) {
                    strncpy(lvg->tmp_buff, &format[(*tokens)->mas_opt[i].spe->beg], (*tokens)->mas_opt[i].spe->end - (*tokens)->mas_opt[i].spe->beg + 1);
                }
                printf("%*s %" PRIXMAX " [(%2" PRIXMAX ") (%2" PRIXMAX ")] ]%s[ \n",
                       f1 - k1,
                       "",
                       (*tokens)->mas_opt[i].spe != NULL ? (*tokens)->mas_opt[i].spe->lfs : 0,
                       (*tokens)->mas_opt[i].spe != NULL ? (*tokens)->mas_opt[i].spe->lef : 0,
                       (*tokens)->mas_opt[i].spe != NULL ? (*tokens)->mas_opt[i].spe->rig : 0,
                       lvg->tmp_buff);
            }
        }
    }

    return LE_OK;
}
