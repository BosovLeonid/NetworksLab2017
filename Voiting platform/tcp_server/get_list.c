#include <server.h>
// Получение списка тем
char *get_list(){
    char container[256];
    char *tmp = "", *tmp_theme, *PATH;
    FILE *themes;
    PATH = concat(CURRENT_DIR,"/THEMES/themes.txt");
    themes = fopen(PATH, "r");
    if (themes == NULL){
        printf("Error while opening file themes.txt.\n");
        fclose(themes);
        return "An error has occurred on server.\n";
    }
    while(fgets(container, sizeof(container), themes)){
        tmp_theme = strtok(container,"-");
        tmp = concat(tmp, tmp_theme);
        tmp = concat(tmp, "\n");
    }
    fclose(themes);
    if (strcmp(tmp, "") == 0)
        return "There is no themes.\n";
    else
        return tmp;
}
