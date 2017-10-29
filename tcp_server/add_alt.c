#include <server.h>
// Добавляем альтернативу выбора в теме
void add_alt(char *theme, char *alt){
    char *PATH, word_theme[255], word_alt[255], *tmp_theme, *tmp_alt;
    FILE *alts, *themes;
    bool is_theme = false;

    PATH = concat(CURRENT_DIR,"/THEMES/");
    chdir(PATH);
    // Проверяем наличие темы
    themes = fopen("themes.txt","r");
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
        answer = "There's no such theme.";
        chdir(CURRENT_DIR);
        free(PATH);
        return;
    }
    PATH = concat(PATH,theme);
    chdir(PATH);

    alts = fopen("alts.txt", "a+t");
    while (fgets(word_alt, sizeof(word_alt), alts))
    {    
    tmp_alt = strtok(word_alt,"-");
    if(strcmp(tmp_alt,alt) == 0){
        answer = "Alternative with this name already exists.";
        fclose(alts);
        chdir(CURRENT_DIR);
        free(PATH);
        return;
    }
    }
    fprintf(alts,"%s-0;\n",alt);
    fclose(alts);
    answer = "Alternative created.";
    chdir(CURRENT_DIR);
    free(PATH);
    return;
}
