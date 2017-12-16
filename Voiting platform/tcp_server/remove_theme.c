#include <server.h>
// Удаляем тему со всеми альтернативами
void remove_theme(char *name){
    int i;
    char *PATH, *PATH_tmp, *tmp_theme, *saveptr;
    char word_theme[256], stack[256];
    FILE *themes, *tmp;
    bool is_theme = false;
    PATH = concat(CURRENT_DIR, "/THEMES/themes.txt");
    PATH_tmp = concat(CURRENT_DIR, "/THEMES/tmp.txt");
    // Проверяем наличие темы
    themes = fopen(PATH, "r");
    if (themes == NULL){
        printf("Error while opening file themes.txt.\n");
        answer = "An error has occurred on server.\n";
        return;
    }
    tmp = fopen(PATH_tmp, "w");
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
        tmp_theme = strtok_r(word_theme, "-", &saveptr);
        if(strcmp(tmp_theme, name) == 0){
            is_theme = true;
    }
    else fprintf(tmp, "%s", stack);
    }
    fclose(themes);
    fclose(tmp);
    remove(PATH);
    rename(PATH_tmp, PATH);
    // Если темы нет, то сообщаем пользователю, что указанной темы нет
    if (check_theme(is_theme, name, PATH) != 0){
        remove("tmp.txt");
        return;
    }
    PATH = concat(CURRENT_DIR, "/THEMES/");
    PATH = concat(PATH, name);
    PATH = concat(PATH, "/alts.txt");
    remove(PATH);
    PATH = concat(CURRENT_DIR, "/THEMES/");
    PATH = concat(PATH, name);
    rmdir(PATH);
    answer = concat("Theme ", name);
    answer = concat(answer, " deleted.\n");
    return;
}
