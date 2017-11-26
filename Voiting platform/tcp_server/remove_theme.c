#include <server.h>
// Удаляем тему со всеми альтернативами
void remove_theme(char *name){
    int i;
    char *PATH, *tmp_theme;
    char word_theme[256], stack[256];
    FILE *themes, *tmp;
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
    tmp = fopen("tmp.txt", "w");
    if (themes == NULL){
        printf("Error while opening file tmp.txt.\n");
        answer = "An error has occurred on server.\n";
        return;
    }
    while (fgets(word_theme, sizeof(word_theme), themes))
    {
    for (i = 0; word_theme[i] != '\0'; i++){
        stack[i] = word_theme[i];
    }
    stack[i] = '\0';
    tmp_theme = strtok(word_theme,"-");
    if(strcmp(tmp_theme,name) == 0){
        is_theme = true;
    }
    else fprintf(tmp,"%s",stack);
    }
    fclose(themes);
    fclose(tmp);

    remove("themes.txt");
    rename("tmp.txt", "themes.txt");

    // Если темы нет, то сообщаем пользователю, что указанной темы нет
    if(!is_theme){
        answer = concat(name, " doesn't exists.\n");
        remove("tmp.txt");
        chdir(CURRENT_DIR);
        free(PATH);
        return;
    }

    PATH = concat(PATH, name);
    chdir(PATH);
    remove("alts.txt");
    PATH = concat(CURRENT_DIR,"/THEMES/");
    chdir(PATH);
    rmdir(name);
    chdir(CURRENT_DIR);
    answer = concat("Theme ", name);
    answer = concat(answer, " deleted.\n");
    return;
}
