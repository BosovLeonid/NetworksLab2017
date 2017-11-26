#include <server.h>
// Добавляем альтернативу выбора в теме
void add_alt(char *theme, char *alt){
    char *PATH, word_theme[256], word_alt[256], *tmp_theme, *tmp_alt;
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

    alts = fopen("alts.txt", "a+t");
    if (alts == NULL){
        printf("Error while opening file alts.txt in theme %s.\n", theme);
        answer = "An error has occurred on server.\n";
        return;
    }
    while (fgets(word_alt, sizeof(word_alt), alts))
    {    
    tmp_alt = strtok(word_alt,"-");
    if(strcmp(tmp_alt,alt) == 0){
        answer = concat("Alternative ", alt);
        answer = concat(answer, " already exists in theme ");
        answer = concat(answer, theme);
        answer = concat(answer, ".\n");
        fclose(alts);
        chdir(CURRENT_DIR);
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
    chdir(CURRENT_DIR);
    free(PATH);
    return;
}
