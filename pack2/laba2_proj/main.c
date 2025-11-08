#include <stdio.h>

#include "../include/funcs.h"
#include "../include/return_codes.h"
#include "../include/macros.h"

int main() {
    printf("\n===tests===\n\n");

    size_t n = 100;
    char str[] = "hello, world !";
    int c = 'o';
    char *find_char = memchr(str, c, n);
    printf("memchr(str, c, n): %s\n", find_char);

    char str1[] = "hello, world !";
    char str2[] = "hello, world !";
    int comparing_char = memcmp(str1, str2, n);
    printf("memcmp(str1, str2, n): %d\n", comparing_char);

    char src[] = "hello, world !";
    char dest[128] = "";
    char *copy_char = memcpy(dest, src, n);
    printf("memcpy(dest, src, n): %s\n", copy_char);

    char str_a[] = "hello, world !";
    int c_a = 'o';
    char *copy_char_c = memset(str_a, c_a, n);
    printf("memset(str, c, n): %s\n", copy_char_c);

    char src_a[] = "hello, world !";
    char dest_a[128] = "pupupu...";
    char *new_str = strncat(dest_a, src_a, n);
    printf("strncat(dest, src, n): %s\n", new_str);

    char str_b[] = "hello, world !";
    int c_b = 'o';
    char *find_char_str = strchr(str_b, c_b);
    printf("strchr(str, c): %s\n", find_char_str);

    char str1_a[] = "hello, world !";
    char str2_a[] = "hello, world !";
    int comparing_str = strncmp(str1_a, str2_a, n);
    printf("strncmp(str1, str2, n): %d\n", comparing_str);

    char src_b[] = "hello, worlddd";
    char dest_b[128] = "";
    char *copy_str = strncpy(dest_b, src_b, n);
    printf("strncpy(dest, src, n): %s\n", copy_str);

    char str1_b[] = "hello, world !";
    char str2_b[] = "oxyz";
    size_t length_start_seg = strcspn(str1_b, str2_b);
    printf("strcspn(str1, str2): %zu\n", length_start_seg);

    int errnum = 1;
    char *find_err = strerror(errnum);
    printf("strerror(errnum): %s\n", find_err);

    char str_c[] = "hello, world !";
    size_t length = strlen(str_c);
    printf("strlen(str): %zu\n", length);

    char str1_c[] = "h!";
    char str2_c[] = "hello, world !";
    char *find_first = strpbrk(str1_c, str2_c);
    printf("strpbrk(str1, str2): %s\n", find_first);

    char str_d[] = "hello, world !";
    int c_d = 'o';
    char *find_last_char_str = strrchr(str_d, c_d);
    printf("strrchr(str, c): %s\n", find_last_char_str);

    char haystack[] = "hello, world ! qwerty";
    char needle[] = "world";
    char *find_needle = strstr(haystack, needle);
    printf("strstr(haystack, needle): %s\n", find_needle);

    char str_e[] = "hello, world ! hello. user";
    char delim[] = ", !";
    char *separation = strtok(str_e, delim);
    while (separation != NULL) {
        printf("strtok(str, delim): %s\n", separation);
        separation = strtok(NULL, delim);
    }

    return 0;
}
