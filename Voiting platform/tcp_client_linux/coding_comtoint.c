#include <client.h>
// Кодируем команду числом
int coding_comToInt(char *command){
    if(strcmp(command, "help") == 0)
        return HELP;
    else if(strcmp(command, "new") == 0)
        return NEW;
    else if(strcmp(command, "add") == 0)
        return ADD;
    else if(strcmp(command, "remove") == 0)
        return REMOVE;
    else if(strcmp(command, "list") == 0)
        return LIST;
    else if(strcmp(command, "change") == 0)
        return CHANGE;
    else if(strcmp(command, "check") == 0)
        return CHECK;
    else if(strcmp(command, "vote") == 0)
        return VOTE;
    else if(strcmp(command, "disconnect") == 0)
        return DISCONNECT;
    else
        return -1;
}
