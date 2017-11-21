#include <server.h>
// Проголосовать за альтернативу в теме
void vote(char *theme, char *alt, int votes){
    char *PATH, word_theme[255], word_alt[255], *tmp_theme, *tmp_alt;
    int file_pos, strl;
    FILE *themes, *alts;
    bool is_theme = false, is_opened = false, is_alt = false;

    PATH = concat(CURRENT_DIR,"/THEMES/");
    chdir(PATH);

    themes = fopen("themes.txt","r+");
    if (themes == NULL){
        printf("Error while opening file themes.txt.\n");
        answer = "An error has occurred on server.\n";
        chdir(CURRENT_DIR);
        free(PATH);
        return;
    }
    // Проверяем наличие темы
    while (fgets(word_theme, sizeof(word_theme), themes))
    {
    tmp_theme = strtok(word_theme,"-");
    if(strcmp(tmp_theme,theme) == 0){
        is_theme = true;
        if(strcmp(strtok(NULL,";"), "opened") == 0){
            is_opened = true;
        }
        break;
    }
    file_pos ++;
    }
    fclose(themes);

    // Если темы нет, то сообщаем пользователю, что указанной темы нет
    if(!is_theme){
        answer = concat(theme, " doesn't exists.\n");
        chdir(CURRENT_DIR);
        free(PATH);
        return;
    }

    // Если тема закрыта для голосования, то сообщаем пользователю об этом
    if(!is_opened){
        answer = concat(theme, " closed for voting.\n");
        chdir(CURRENT_DIR);
        free(PATH);
        return;
    }

    PATH = concat(PATH,theme);
    chdir(PATH);
    file_pos = 0;

    alts = fopen("alts.txt", "r+");
    if (alts == NULL){
        printf("Error while opening file alts.txt in theme %s.\n", theme);
        answer = "An error has occurred on server.\n";
        chdir(CURRENT_DIR);
        free(PATH);
        return;
    }
    while (fgets(word_alt, sizeof(word_alt), alts))
    {
    strl = strlen(word_alt);
    file_pos = file_pos + strl;
    tmp_alt = strtok(word_alt,"-");
    if(strcmp(tmp_alt,alt) == 0){
        is_alt = true;
        file_pos = file_pos - strl + strlen(tmp_alt) + 1;
        tmp_alt = strtok(NULL, ";");
        int cur_votes = atoi(tmp_alt);
        cur_votes = cur_votes + votes;
        fseek(alts, file_pos, SEEK_SET);
        char buf[10], *str;
        itoa(cur_votes, buf, 10);
        str = buf;
        str = concat(str, ";\n");
        fputs(str, alts);
        fclose(alts);
        answer = "Votes have been added.\n";
        chdir(CURRENT_DIR);
        free(PATH);
        return;
    }
    file_pos ++;
    }
    fclose(alts);

    // Если альтернативы нет, то сообщаем пользователю, что её нет.
    if(!is_alt){
        answer = concat(alt, " doesn't exists in theme ");
        answer = concat(answer, theme);
        answer = concat(answer, ".\n");
        chdir(CURRENT_DIR);
        free(PATH);
        return;
    }
}
