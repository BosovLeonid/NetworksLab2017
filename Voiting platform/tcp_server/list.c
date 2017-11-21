#include <server.h>
// Получение списка тем
char *list(){
    char container[256];
    char *tmp = "", *tmp_theme, *PATH;
    FILE *themes;
    PATH = concat(CURRENT_DIR,"/THEMES/");
    chdir(PATH);
    themes = fopen("themes.txt", "r");
    if (themes == NULL){
        printf("Error while opening file themes.txt.\n");
        answer = "An error has occurred on server.\n";
        fclose(themes);
        return (char)1;
    }
    while(fgets(container, sizeof(container), themes)){
        tmp_theme = strtok(container,"-");
        tmp = concat(tmp, tmp_theme);
        tmp = concat(tmp, "\n");
    }
    fclose(themes);
    return tmp;
}
