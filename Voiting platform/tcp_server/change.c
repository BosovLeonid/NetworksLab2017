#include <server.h>
// Изменить состояне темы(открыта/закрыта)
void change(char *theme){
    char *PATH, word_theme[256], *tmp_theme, *saveptr;
    int file_pos = 0;
    FILE *themes;
    bool is_theme = false;
    PATH = concat(CURRENT_DIR,"/THEMES/themes.txt");
    // Проверяем наличие файла
    themes = fopen(PATH,"r+");
    if (check_file(themes, PATH)!= 0){
        return;
    }
    // Проверяем наличие темы
    while (fgets(word_theme, sizeof(word_theme), themes))
    {
        file_pos = file_pos + strlen(word_theme);
        tmp_theme = strtok_r(word_theme, "-", &saveptr);
        if(strcmp(tmp_theme,theme) == 0){
            file_pos = file_pos - 8;
            is_theme = true;
            break;
        }
        file_pos ++;
    }
    // Если темы нет, то сообщаем пользователю, что указанной темы нет
    if (check_theme(is_theme, theme, PATH) != 0){
        fclose(themes);
        return;
    }
    answer = concat("State of theme ", theme);
    fseek(themes , file_pos, SEEK_SET);
    fgets(word_theme, sizeof(word_theme), themes);
    tmp_theme = strtok_r(word_theme, ";", &saveptr);
    fseek( themes , file_pos, SEEK_SET );
    if(strcmp(tmp_theme, "closed") == 0){
        fputs("opened", themes);
        answer = concat(answer, " was changed to opened.\n");
    }
    else {
        fputs("closed", themes);
        answer = concat(answer, " was changed to closed.\n");
    }
    fclose(themes);
    free(PATH);
    return;
}
