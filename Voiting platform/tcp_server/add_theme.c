#include <server.h>
// Добавляем новую тему
void add_theme(char *name){
    char *PATH, word[256], *tmp, *saveptr;
    FILE *themes;
    PATH = concat(CURRENT_DIR,"/THEMES/themes.txt");
    // Проверяем наличие файла
    themes = fopen(PATH, "a+t");
    if (check_file(themes, PATH) != 0){
        return;
    };
    // Проверяем наличие темы
    while (fgets(word, sizeof(word), themes))
    {
        tmp = strtok_r(word,"-", &saveptr);
        if(strcmp(tmp,name) == 0){
            answer = concat("Theme ", name);
            answer = concat(answer, " already exists.\n");
            fclose(themes);
            free(PATH);
            return;
        }
    }
    fprintf(themes, "%s-closed;\n", name);
    PATH = concat(CURRENT_DIR,"/THEMES/");
    PATH = concat(PATH, name);
    mkdir(PATH);
    fclose(themes);
    answer = concat("Theme ", name);
    answer = concat(answer, " created.\n");
    free(PATH);
    return;
}
