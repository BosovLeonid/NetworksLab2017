#include <server.h>
// Добавляем альтернативу выбора в теме
void add_alt(char *theme, char *alt){
    char *PATH, word_theme[256], word_alt[256], *tmp_theme, *tmp_alt, *saveptr;
    FILE *alts, *themes;
    bool is_theme = false;
    PATH = concat(CURRENT_DIR,"/THEMES/themes.txt");
    // Проверяем наличие файла
    themes = fopen(PATH, "r");
    if (check_file(themes, PATH) != 0){
        return;
    }
    // Проверяем наличие темы
    while (fgets(word_theme, sizeof(word_theme), themes))
    {    
        tmp_theme = strtok_r(word_theme, "-", &saveptr);
        if(strcmp(tmp_theme, theme) == 0){
            is_theme = true;
            break;
        }
    }
    fclose(themes);
    // Если темы нет, то сообщаем пользователю, что указанной темы нет
    if (check_theme(is_theme, theme, PATH) != 0){
        return;
    }
    PATH = concat(CURRENT_DIR,"/THEMES/");
    PATH = concat(PATH, theme);
    PATH = concat(PATH, "/alts.txt");
    // Проверяем наличие файла
    alts = fopen(PATH, "a+t");
    if(check_file(themes, PATH) != 0){
        return;
    };
    // Проверяем наличие альтернативы
    while (fgets(word_alt, sizeof(word_alt), alts))
    {    
        tmp_alt = strtok(word_alt, "-");
        if(strcmp(tmp_alt, alt) == 0){
            answer = concat("Alternative ", alt);
            answer = concat(answer, " already exists in theme ");
            answer = concat(answer, theme);
            answer = concat(answer, ".\n");
            fclose(alts);
            free(PATH);
            return;
        }
    }
    fprintf(alts,"%s-0;\n",alt);
    fclose(alts);
    answer = concat("Alternative ", alt);
    answer = concat(answer, " created in theme ");
    answer = concat(answer, theme);
    answer = concat(answer, ".\n");
    free(PATH);
    return;
}
