#include <server.h>
// Удаляем тему со всеми альтернативами
void remove_theme(char *name){
    int i;
    char *PATH, *tmp_theme;
    char word_theme[255], stack[255];
    FILE *themes, *tmp;
    bool is_theme = false;

    PATH = concat(CURRENT_DIR,"/THEMES/");
    chdir(PATH);
    // Проверяем наличие темы
    themes = fopen("themes.txt","a+");
    tmp = fopen("tmp.txt", "w+");
    while (fgets(word_theme, sizeof(word_theme), themes))
    {
    for (i = 0; word_theme[i] != '\0'; i++){
        stack[i] = word_theme[i];
    }
    //stack[i] = ';';
    //stack[i] = '\n';
    stack[i] = '\0';
    tmp_theme = strtok(word_theme,"-");
    if(strcmp(tmp_theme,name) == 0){
        is_theme = true;
    }
    else fprintf(tmp,"%s",stack);
    }
    fclose(themes);
    fclose(tmp);

    // Если темы нет, то сообщаем пользователю, что указанной темы нет
    if(!is_theme){
        answer = "There's no such theme.";
        remove("tmp.txt");
        chdir(CURRENT_DIR);
        free(PATH);
        return;
    }

    remove("themes.txt");
    rename("tmp.txt", "themes.txt");

    PATH = concat(PATH,name);
    chdir(PATH);

    remove("alts.txt");
    PATH = concat(CURRENT_DIR,"/THEMES/");
    PATH = concat(PATH,name);
    //rmdir(PATH);
    // Нужен способ обойти права на удаление папки
    //perror("Error: ");
    answer = "Theme deleted.";
    return;
}
