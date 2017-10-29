#include <client.h>
int decoder(char *command){
    if(strcmp(command, "new") == 0)
        return 1;
    else if(strcmp(command, "add") == 0)
        return 2;
    else if(strcmp(command, "remove") == 0)
        return 3;
    else if(strcmp(command, "list") == 0)
        return 4;
    else if(strcmp(command, "open") == 0)
        return 5;
    else if(strcmp(command, "close") == 0)
        return 6;
    else if(strcmp(command, "vote") == 0)
        return 8;
    else if(strcmp(command, "disconnect") == 0)
        return 8;
    else
        return 0;
}
