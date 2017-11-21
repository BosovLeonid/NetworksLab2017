#include <server.h>
// Получить информацию об определенной теме
void check(char *theme){
    char *PATH, word_theme[255], word_alt[255], *tmp_theme, *tmp_alt;
    FILE *alts, *themes;
    bool is_theme = false;

    PATH = concat(CURRENT_DIR,"/THEMES/");
    chdir(PATH);
    // Проверяем наличие темы
    themes = fopen("themes.txt","r");
    if (themes == NULL){
        printf("Error while opening file themes.txt.\n");
        answer = "An error has occurred on server.\n";
        return;
    }
    while (fgets(word_theme, sizeof(word_theme), themes))
    {
    tmp_theme = strtok(word_theme,"-");
    if(strcmp(tmp_theme,theme) == 0){
        is_theme = true;
        answer = concat(theme, concat(" ",strtok(NULL,";")));
        answer = concat(answer, " for voting.\n");
        break;
    }
    }
    fclose(themes);

    // Если темы нет, то сообщаем пользователю, что указанной темы нет
    if(!is_theme){
        answer = concat(theme, " doesn't exists.\n");
        chdir(CURRENT_DIR);
        free(PATH);
        return;
    }
    PATH = concat(PATH,theme);
    chdir(PATH);

    alts = fopen("alts.txt", "r");
    if (alts == NULL){
        printf("Error while opening file alts.txt in theme %s.\n", theme);
        answer = "An error has occurred on server.\n";
        chdir(CURRENT_DIR);
        free(PATH);
        return;
    }
    while (fgets(word_alt, sizeof(word_alt), alts))
    {
    tmp_alt = strtok(word_alt,"-");
    answer = concat(answer, "Alternative ");
    answer = concat(answer, tmp_alt);
    tmp_alt = strtok(NULL, ";");
    answer = concat(answer, " have ");
    answer = concat(answer, tmp_alt);
    answer = concat(answer, " votes.\n");
    }
    fclose(alts);
    chdir(CURRENT_DIR);
    free(PATH);
    return;
}
