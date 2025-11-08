#include <stdio.h>

#include "../include/funcs.h"
#include "../include/return_codes.h"
#include "../include/macros.h"

void err_status(return_codes status) {
	switch (status) {
		case OK:
			printf("ok :)\n");
			return;
		case INVALID_INPUT:
			printf("error: invalid input\n");
			return;
		case INVALID_BASE:
			printf("error: invalid base\n");
			return;
		case ERROR_OVERFLOW:
			printf("error: overflow\n");
			return;
		case NO_MULTIPLES:
			printf("error: no multiplies\n");
			return;
		case ERROR_ALLOC:
			printf("error: alloc\n");
			return;
		case UNKNOWN_FLAG:
			printf("error: unknown flag\n");
			return;
		case UNKNOWN_ERROR:
			printf("unknown error\n");
			return;
	}
	return;
}

void *memchr(const void *str, int c, size_t n) {
    unsigned char *ptr_target = NULL;
    unsigned char *str_target = (unsigned char*)str;
    unsigned char char_c = (unsigned char)c;
    for (size_t i = 0; i < n; ++i) {
        if (str_target[i] == char_c) {
            ptr_target = str_target + i;
            break;
        }
    }
    return ptr_target;
}

int memcmp(const void *str1, const void *str2, size_t n) {
    unsigned char *s_str1 = (unsigned char*)str1;
    unsigned char *s_str2 = (unsigned char*)str2;

    for (size_t i = 0; i < n; ++i) {
        if (s_str1[i] < s_str2[i]) {
            return -1;
        } else if (s_str1[i] > s_str2[i]) {
            return 1;
        }
    }
    return 0;
}

void *memcpy(void *dest, const void *src, size_t n) {
    unsigned char *s_src = (unsigned char*)src;
    unsigned char *s_dest = (unsigned char*)dest;
    for (size_t i = 0; i < n; ++i) {
        s_dest[i] = s_src[i];
    }
    return dest;
}

void *memset(void *str, int c, size_t n) {
    unsigned char *s_str = (unsigned char*)str;
    unsigned char char_c = (unsigned char)c;

    for (size_t i = 0; i < n; ++i) {
        s_str[i] = char_c;
    }
    return str;
}

char *strncat(char *dest, const char *src, size_t n) {
    size_t len1 = strlen(dest);
    size_t i = 0;
    for (; i < n && src[i] != '\0'; ++i) {
        dest[len1 + i] = src[i];
    }
    dest[len1 + i] = '\0';
    return dest;
}

char *strchr(const char *str, int c) {
    char *ptr_target = NULL;
    unsigned char *s_str = (unsigned char*)str;
    unsigned char c_char = (unsigned char)c;
    while (*s_str != '\0') {
        if (*s_str == c_char) {
            ptr_target = (char*)s_str;
            break;
        }
        s_str++;
    }
    return ptr_target;
}

int strncmp(const char *str1, const char *str2, size_t n) {
    unsigned char *s_str1 = (unsigned char*)str1;
    unsigned char *s_str2 = (unsigned char*)str2;
    size_t i = 0;
    while ((*s_str1 != '\0' || *s_str2 != '\0') && i < n) {
        if (*s_str1 < *s_str2) {
            return -1;
        } else if (*s_str1 > *s_str2) {
            return 1;
        }
        s_str1++;
        s_str2++;
    }
    return 0;
}

char *strncpy(char *dest, const char *src, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        if (src[i] != '\0') {
            dest[i] = src[i];
        } else {
            dest[i] = '\0';
        }
    }
    return dest;
}

size_t strcspn(const char *str1, const char *str2) {
    size_t count = 0;
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    for (size_t i = 0; i < len1; ++i) {
        int flag = 0;
        for (size_t j = 0; j < len2; ++j) {
            if (str1[i] == str2[j]) {
                flag = 1;
                break;
            }
        }
        if (flag) {
            break;
        }
        count++;
    }
    return count;
}

char *strerror(int errnum) {
    const char* buf[] = ERROR_MESSAGES;
    
    #ifdef __APPLE__
        const int ERR_MAX = 107;
    #elif __linux__
        const int ERR_MAX 133;
    #endif

    if (errnum < 0 || errnum > ERR_MAX) {
        return (char*)UNKNOWN_ERROR;
    }
    return (char*)buf[errnum];
}

size_t strlen(const char *str) {
    unsigned char* s_str = (unsigned char*)str;
    size_t len = 0;
    while (*s_str != '\0') {
        s_str++;
        len++;
    }
    return len;
}

char *strpbrk(const char *str1, const char *str2) {
    char *ptr_target = NULL;
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    for (size_t i = 0; i < len1; ++i) {
        for (size_t j = 0; j < len2; ++j) {
            if (str1[i] == str2[j]) {
                ptr_target = (char*)(str1 + i);
                return ptr_target;
            }
        }
    }
    return NULL;
}

char *strrchr(const char *str, int c) {
    char *ptr_target = NULL;
    unsigned char c_char = (unsigned char)c;
    for (ssize_t i = strlen(str) - 1; i >= 0; i--) {
        if (str[i] == c_char) {
            ptr_target = (char*)(str + i);
            break;
        }
    }
    return ptr_target;
}

char *strstr(const char *haystack, const char *needle) {
    size_t len1 = strlen(haystack);
    size_t len2 = strlen(needle);
    char *ptr_target = NULL;
    
    if (len2 == 0) {
        ptr_target = (char*)haystack;
        return ptr_target;
    }

    if (len2 > len1) {
        return NULL;
    }

    for (size_t i = 0; i <= len1 - len2; ++i) {
        size_t j = 0;
        for (; j < len2; ++j) {
            if (haystack[i + j] != needle[j]) {
                break;
            }
        }
        if (j == len2) {
            ptr_target = (char*)(haystack + i);
            return ptr_target;
        }
    }
    return ptr_target;
}

char *strtok(char *str, const char *delim) {
    static char *next = NULL;
    if (str != NULL) {
        next = str; //начало стр/остановка
    }

    if (next == NULL) {
        return NULL;
    }

    // скип разделителей
    while (*next && strchr(delim, *next)) {
        next++;
    }

    if (*next == '\0') {
        next = NULL;
        return NULL;
    }
    
    char *start = next; //старт токена

    while (*next && !strchr(delim, *next)) {
        next++;
    }

    //остановка на разделителе => разделитель = '\0';
    if (*next) {
        *next = '\0';
        next++;
    } else {
        next = NULL;
    }
    return start;
}

