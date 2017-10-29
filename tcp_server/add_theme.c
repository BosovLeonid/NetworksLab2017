#include <server.h>
// Добавляем новую тему
void add_theme(char *name){
    char *PATH, word[255], *tmp;
    FILE *themes;
    PATH = concat(CURRENT_DIR,"/THEMES/");
    chdir(PATH);
    themes = fopen("themes.txt", "a+t");
    while (fgets(word, sizeof(word), themes))
    {
    tmp = strtok(word,"-");
    if(strcmp(tmp,name) == 0){
        answer = "Theme with this name already exists.";
        fclose(themes);
        chdir(CURRENT_DIR);
        free(PATH);
        return;
    }
    }
    fprintf(themes,"%s-close;\n",name);
    PATH = concat(PATH, name);
    mkdir(PATH);
    fclose(themes);
    answer = "Theme created.";
    chdir(CURRENT_DIR);
    free(PATH);
    return;
}
