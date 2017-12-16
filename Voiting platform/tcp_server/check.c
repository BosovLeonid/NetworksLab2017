#include <server.h>
// Получить информацию об определенной теме
void check(char *theme){
    char *PATH, word_theme[256], word_alt[256], *tmp_theme, *tmp_alt, *saveptr;
    FILE *alts, *themes;
    bool is_theme = false;
    PATH = concat(CURRENT_DIR, "/THEMES/themes.txt");
    // Проверяем наличие файла
    themes = fopen(PATH, "r");
    if (check_file(themes, PATH) != 0){
        return;
    }
    // Проверяем наличие темы, если есть записываем её состояние
    while (fgets(word_theme, sizeof(word_theme), themes))
    {
        tmp_theme = strtok_r(word_theme, "-", &saveptr);
        if(strcmp(tmp_theme, theme) == 0){
            is_theme = true;
            answer = concat(theme, concat(" ", strtok_r(NULL, ";", &saveptr)));
            answer = concat(answer, " for voting.\n");
            break;
        }
    }
    fclose(themes);
    // Если темы нет, то сообщаем пользователю, что указанной темы нет
    if (check_theme(is_theme, theme, PATH) != 0){
        return;
    }
    PATH = concat(CURRENT_DIR, "/THEMES/");
    PATH = concat(PATH, theme);
    PATH = concat(PATH, "/alts.txt");
    // Проверяем наличие файла. Если его нет, значит альтернатив в теме нет
    alts = fopen(PATH, "r");
    if (alts == NULL){
        answer = concat(answer, "Theme has no alternatives.\n");
        free(PATH);
        return;
    }
    // Читаем альтернативы из файла
    while (fgets(word_alt, sizeof(word_alt), alts))
    {
        tmp_alt = strtok_r(word_alt, "-", &saveptr);
        answer = concat(answer, "Alternative ");
        answer = concat(answer, tmp_alt);
        tmp_alt = strtok_r(NULL, ";", &saveptr);
        answer = concat(answer, " have ");
        answer = concat(answer, tmp_alt);
        answer = concat(answer, " votes.\n");
    }
    fclose(alts);
    free(PATH);
    return;
}
