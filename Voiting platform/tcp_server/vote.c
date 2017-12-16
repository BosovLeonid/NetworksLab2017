#include <server.h>
// Проголосовать за альтернативу в теме
void vote(char *theme, char *alt, int votes){
    char *PATH, *PATH_tmp, word_theme[256], word_alt[256], stack[256], *tmp_theme, *tmp_alt, *saveptr;
    int file_pos;
    FILE *themes, *alts, *tmp;
    bool is_theme = false, is_opened = false, is_alt = false;
    PATH = concat(CURRENT_DIR, "/THEMES/themes.txt");
    // Проверяем наличие файла
    themes = fopen(PATH, "r+");
    if(check_file(themes, PATH) != 0){
        answer = "Error: Cannot open file themes.txt.\n";
        return;
    };
    // Проверяем наличие темы
    while (fgets(word_theme, sizeof(word_theme), themes))
    {
        tmp_theme = strtok_r(word_theme, "-", &saveptr);
        if(strcmp(tmp_theme, theme) == 0){
            is_theme = true;
            if(strcmp(strtok_r(NULL, ";", &saveptr), "opened") == 0){
                is_opened = true;
            }
            break;
        }
        file_pos ++;
    }
    fclose(themes);
    // Если темы нет, то сообщаем пользователю, что указанной темы нет
    if (check_theme(is_theme, theme, PATH) != 0){
        answer = concat("Error: ", theme);
        answer = concat(answer, " doesn't exists.\n");
        return;
    }
    // Если тема закрыта для голосования, то сообщаем пользователю об этом
    if(!is_opened){
        answer = concat("Error: ", theme);
        answer = concat(answer, " closed for voting.\n");
        free(PATH);
        return;
    }
    PATH = concat(CURRENT_DIR, "/THEMES/");
    PATH = concat(PATH, theme);
    PATH_tmp = concat(PATH, "/tmp.txt");
    PATH = concat(PATH, "/alts.txt");
    file_pos = 0;
    alts = fopen(PATH, "r");
    if (alts == NULL){
        answer = "Error: Theme has no alternatives.\n";
        chdir(CURRENT_DIR);
        free(PATH);
        return;
    }
    tmp = fopen(PATH_tmp, "w");
    while (fgets(word_alt, sizeof(word_alt), alts))
    {
        int i;
        for (i = 0; word_alt[i] != '\0'; i++){
            stack[i] = word_alt[i];
        }
        stack[i] = '\0';
        tmp_alt = strtok(word_alt, "-");
        if(strcmp(tmp_alt, alt) == 0){
            is_alt = true;
            char *str = "";
            str = tmp_alt;
            str = concat(str, "-");
            int cur_votes = atoi(strtok(NULL, ";"));
            cur_votes = cur_votes + votes;
            char buf[10], *tmp_votes;
            itoa(cur_votes, buf, 10);
            tmp_votes = buf;
            str = concat(str, tmp_votes);
            str = concat(str, ";\n");
            fprintf(tmp, "%s", str);
            answer = "Votes have been added.\n";
        }
        else fprintf(tmp, "%s", stack);
    }
    fclose(alts);
    fclose(tmp);

    remove(PATH);
    rename(PATH_tmp, PATH);

    // Если альтернативы нет, то сообщаем пользователю, что её нет.
    if(!is_alt){
        answer = concat("Error: ", alt);
        answer = concat(answer, " doesn't exists in theme ");
        answer = concat(answer, theme);
        answer = concat(answer, ".\n");
        free(PATH);
        free(PATH_tmp);
        return;
    }
    free(PATH);
    free(PATH_tmp);
    return;
}
