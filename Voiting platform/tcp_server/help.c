#include <server.h>
// Получение информации о командах
char *help(){
    FILE *hp = fopen("help.txt", "r");
    char container[256];
    char *tmp = "";
    if (hp == NULL){
        printf("Error while opening file help.txt.\n");
        answer = "An error has occurred on server.\n";
        fclose(hp);
        return (char*)1;
    }
    while(fgets(container, sizeof(container), hp)){
        tmp = concat(tmp, container);
    }
    fclose(hp);
    return tmp;
}
