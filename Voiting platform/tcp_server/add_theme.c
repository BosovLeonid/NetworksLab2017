#include <server.h>
// Добавляем новую тему
void add_theme(char *name){
    char *PATH, word[256], *tmp;
    FILE *themes;
    PATH = concat(CURRENT_DIR,"/THEMES/");
    chdir(PATH);
    themes = fopen("themes.txt", "a+t");
    if (themes == NULL){
        printf("Error while opening file themes.txt.\n");
        answer = "An error has occurred on server.\n";
        return;
    }
    while (fgets(word, sizeof(word), themes))
    {
    tmp = strtok(word,"-");
    if(strcmp(tmp,name) == 0){
        answer = concat("Theme ", name);
        answer = concat(answer, " already exists.\n");
        fclose(themes);
        chdir(CURRENT_DIR);
        free(PATH);
        return;
    }
    }
    fprintf(themes,"%s-closed;\n",name);

    PATH = concat(PATH, name);
    mkdir(PATH);
    fclose(themes);
    answer = concat("Theme ", name);
    answer = concat(answer, " created.\n");
    chdir(CURRENT_DIR);
    free(PATH);
    return;
}
