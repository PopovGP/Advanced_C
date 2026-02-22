// https://metanit.com/c/tutorial/10.6.php

#include <stdlib.h>
#include <stdio.h>
#include <errno.h> // Для errno
#include <limits.h> // Для LONG_MAX, LONG_MIN
 
int main() {
    char *str = "/";
    char *endptr;
    long result;
 
    errno = 0; // Сбрасываем errno перед вызовом
    result = strtol(str, &endptr, 10);
 
    // Проверяем возможные ошибки
    if (errno == ERANGE) {
        puts("Произошло переполнение! Значение слишком велико");
        if (result == LONG_MAX) {
            puts("Переполнение вверх (MAX)");
        } else if (result == LONG_MIN) {
            puts("Переполнение вниз (MIN)");
        }
    }
    // Проверяем, были ли преобразованы какие-либо цифры
    else if (endptr == str) {
        puts("Не найдено ни одной цифры для преобразования");
    }
    // Проверяем, дошли ли мы до конца строки ('\0')
    else if (*endptr != '\0') {
        printf("Преобразование успешно, но остановилось на символе: '%c'\n", *endptr);
        printf("Остаток строки: '%s'\n", endptr);
    }
    else {
        puts("Преобразование прошло успешно и полностью.");
    }
 
    printf("Результат: %ld\n", result);
    return 0;
}
