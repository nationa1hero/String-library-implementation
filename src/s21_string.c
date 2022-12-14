//  Copyright [year] <Copyright Owner>

#include "./s21_string.h"

typedef unsigned long s21_size_long;

s21_size_t s21_strlen(const char *str) {
    s21_size_t lenght_str = 0;

    while (*str) {
        lenght_str++;
        str++;
    }
    return lenght_str;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
    int i = 0;
    while (*str1 && s21_strchr(str2, *str1++)) i++;
    return i;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
    unsigned int length = 0;
    while (*str1) {
        if (s21_strchr(str2, *str1)) return length;
        str1++;
        length++;
    }
    return length;
}

int s21_strcmp(const char *str1, const char *str2) {
    for (; *str1 == *str2; str1++, str2++) {
        if (*str2 == '\0') {
            return 0;
        }
    }
    return (unsigned char)*str1 - (unsigned char)*str2;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    const char *first = str1;
    const char *second = str2;
    int compare = 0;

    if (str1 == str2) {
        return 0;
    } else {
        while (n > 0) {
            if (*first != *second) {
                compare = (unsigned char)*first - (unsigned char)*second;
                break;
            }
            n--;
            first++;
            second++;
        }
    }
    return compare;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
    if (n == 0) return 0;
    do {
        if (*str1 != *str2++)
            return (*(unsigned char *)str1 - *(unsigned char *)--str2);
        if (*str1++ == 0) break;
    } while (--n != 0);
    return (0);
}

void *s21_memset(void *str, int c, s21_size_t n) {
    char *temp_str = (char *)str;
    while (n > 0) {
        *temp_str = (char)c;
        temp_str++;
        n--;
    }
    return str;
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
    char *s = (char *)str;
    while (n > 0 && *s != c) {
        s++;
        n--;
    }
    return !n ? s21_null : s;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
    for (size_t i = 0; i < n; i++)
        *((unsigned char *)dest + i) = *((unsigned char *)src + i);
    return dest;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
    int i;
    if (dest > src) {
        i = (int)n - 1;
        while (i >= 0) {
            *((char *)dest + i) = *((char *)src + i);
            i--;
        }
    } else {
        i = 0;
        while (i < (int)n) {
            *((char *)dest + i) = *((char *)src + i);
            i++;
        }
    }
    return dest;
}

char *s21_strerror(int errnum) {
    char *err = s21_null;
    static char *array[] = errlist;
    err = (char *)array[errnum];
    static char buffer[1024];
#if defined(__APPLE__)
    snprintf(buffer, sizeof(buffer), "Unknown error: %d", (int)errnum);
#elif defined(__linux__)
    snprintf(buffer, sizeof(buffer), "Unknown error %d", (int)errnum);
#endif
    if (err == s21_null || errnum > MAX_ERROR || errnum < 0) {
        err = buffer;
    }
    return err;
}

char *s21_strchr(const char *src, int c) {
    int i = 0;
    while ((src[i] != '\0') && (src[i] != (char)c)) i++;
    return src[i] == '\0' ? 0 : (char *)&src[i];
}

char *s21_strrchr(const char *str, int c) {
    int i = s21_strlen(str) - 1;
    while ((str[i] != 0) && (str[i] != (char)c)) i--;
    return str[i] == 0 ? (char *)s21_null : (char *)&str[i];
}

char *s21_strcpy(char *dest, const char *src) {
    char *tmp = dest;

    while ((*dest++ = *src++) != '\0') {
    }

    return tmp;
}

char *s21_strcat(char *dest, const char *src) {
    char *tmp = dest;
    while (*dest) dest++;
    while ((*dest++ = *src++) != '\0') {
    }
    *dest = 0;
    return (tmp);
}

char *s21_strtok(char *str, const char *delim) {
    static char *new;
    if (str) {
        new = str;
        while (s21_strchr(delim, *new)) *new++ = '\0';
    }
    int endofnew = 0;
    if (!*new) {
        endofnew = 1;
    } else {
        str = new;
        while (*new && !s21_strchr(delim, *new)) new++;
        while (*new &&s21_strchr(delim, *new)) *new++ = '\0';
    }
    return endofnew ? s21_null : str;
}

char *s21_strpbrk(const char *str1, const char *str2) {
    const char *scanp;
    int c, sc;

    while ((c = *str1++) != 0) {
        for (scanp = str2; (sc = *scanp++) != 0;)
            if (sc == c) return ((char *)(str1 - 1));
    }
    return s21_null;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
    char *tmp = dest;
    while (*dest) dest++;
    while ((*dest++ = *src++) && (n > 1)) n--;
    *dest = 0;
    return tmp;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
    s21_size_t srclen = s21_strlen(src);

    for (s21_size_t i = 0; i < n; i++) {
        if (i > srclen - 1) {
            dest[i] = '\0';
        } else {
            dest[i] = src[i];
        }
    }
    return dest;
}

char *s21_strstr(const char *haystack, const char *needle) {
    s21_size_t hay_len = s21_strlen(haystack);
    s21_size_t n_len = s21_strlen(needle);
    char *result = s21_null;

    if (n_len == 0) {
        result = (char *)haystack;
    }

    for (s21_size_t i = 0; i < hay_len; i++) {
        if (haystack[i] == needle[0]) {
            int counter = 0;
            s21_size_t j = i;
            s21_size_t k = 0;

            while (k < n_len && counter == 0) {
                if (!haystack[j]) {
                    counter = 1;
                }

                if (haystack[j] == needle[k] && counter == 0) {
                    j++;
                    k++;
                } else {
                    counter = 1;
                }
            }

            if (counter == 0) {
                result = (char *)&haystack[i];
            }
        }
    }

    return result;
}

void *s21_to_upper(const char *str) {
    char *new = s21_null;
    if (str) {
        new = (char *)realloc(new, (s21_strlen(str) + 1) * sizeof(char));
        new[s21_strlen(str)] = '\0';
    }
    if (new) {
        s21_strncpy(new, str, s21_strlen(str));
        for (char *i = new; *i; i++) {
            if (*i >= 'a' && *i <= 'z') *i -= 32;
        }
    }
    return (void *)new;
}

void *s21_to_lower(const char *str) {
    char *new = s21_null;
    if (str) {
        new = (char *)realloc(new, (s21_strlen(str) + 1) * sizeof(char));
        new[s21_strlen(str)] = '\0';
    }
    if (new) {
        s21_strncpy(new, str, s21_strlen(str));
        for (char *i = new; *i; i++) {
            if (*i >= 'A' && *i <= 'Z') *i += 32;
        }
    }
    return (void *)new;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *new_str = s21_null;
  if (src) {
    if (s21_strlen(src) >= start_index) {
      if (str) {
        s21_size_t src_lenght = s21_strlen(src);
        s21_size_t str_lenght = s21_strlen(str);
        s21_size_t len = src_lenght + str_lenght;
        new_str = (char *)calloc(len, 5);
        if (new_str != s21_null) {
          s21_size_t j = 0;
          for (s21_size_t i = 0; i < len; i++) {
            if (i == start_index) {
              for (s21_size_t str_i = 0; str_i < str_lenght; str_i++) {
                new_str[j] = str[str_i];
                j++;
              }
            }
            new_str[j] = src[i];
            j++;
          }
        }
      }
    }
  }
  return new_str;
}

void *s21_trim(const char *src, const char *trim_chars) {
    char *new_str = s21_null;
    if (src && trim_chars) {
        char *ptr_str = (char *)src;
        char *end_str = (char *)src + s21_strlen(src);
        for (; *ptr_str && s21_strchr(trim_chars, *ptr_str); ptr_str++) {
        }
        for (; end_str != ptr_str && s21_strchr(trim_chars, *(end_str - 1));
             end_str--) {
        }
        new_str = (char *)malloc((end_str - ptr_str + 1) * sizeof(char));
        if (new_str) {
            s21_strncpy(new_str, ptr_str, end_str - ptr_str);
            *(new_str + (end_str - ptr_str)) = '\0';
        }
    }
    return (void *)new_str;
}

int s21_sprintf(char *str, const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    struct format S;
    const char *start = str;
    init(&S);
    char *f = (char *)format;
    int *aos;
    int n = 20;
    aos = (int *)malloc(n * sizeof(int));
    while (*f != '\0') {
        if (*f == '%') {
            f++;
            while (*f == '-' || *f == '+' || *f == ' ' || *f == '#' ||
                   *f == '0') {
                if (*f == '-')
                    S.flag_minus = 1;
                else if (*f == '+')
                    S.flag_plus = 1;
                else if (*f == ' ')
                    S.flag_space = 1;
                else if (*f == '#')
                    S.flag_hash = 1;
                else if (*f == '0')
                    S.flag_zero = 1;
                f++;
            }
            while ((*f >= '0' && *f <= '9') || *f == '*') {
                if (*f >= '0' && *f <= '9')
                    S.wight = S.wight * 10 + (*f - '0');
                else if (*f == '*')
                    S.wight = va_arg(ap, int);
                f++;
            }
            for (int i = 0; i < n; i++)
                aos[i] = i + 1;
            if (*f == '.') {
                S.accur = 0;
                f++;
                while ((*f >= '0' && *f <= '9') || *f == '*') {
                    if (*f >= '0' && *f <= '9')
                        S.accur = S.accur * 10 + (*f - '0');
                    else if (*f == '*')
                        S.accur = va_arg(ap, int);
                    f++;
                }
            }
            if (*f == 'h' || *f == 'l' || *f == 'L') S.lenght = *f++;
            if (*f == 'c' || *f == 'd' || *f == 'i' || *f == 'e' || *f == 'E' ||
                *f == 'f' || *f == 'g' || *f == 'G' || *f == 'o' || *f == 's' ||
                *f == 'u' || *f == 'x' || *f == 'X' || *f == 'p' || *f == 'n')
                S.spec = *f++;
            else if (*f == '%')
                *str++ = *f++;
            if (S.spec == 'c') {
                badflags(&S);
                if (S.lenght == 'l')
                    str = c_sprintf(&S, str, (int)va_arg(ap, wchar_t));
                else
                    str = c_sprintf(&S, str, va_arg(ap, int));
            } else if (S.spec == 'd' || S.spec == 'i') {
                badflags(&S);
                if (S.lenght == 'l')
                    str = ld_sprintf(&S, str, va_arg(ap, long int));
                else
                    str = d_sprintf(&S, str, va_arg(ap, int));
            } else if (S.spec == 's') {
                badflags(&S);
                if (S.lenght == 'l') {
                    wchar_t *y = va_arg(ap, wchar_t *);
                    str = ls_sprintf(&S, str, y);
                } else {
                    char *x = va_arg(ap, char *);
                    str = s_sprintf(&S, str, x);
                }
            } else if (S.spec == 'n') {
                n_sprintf(str, start, va_arg(ap, int *));
            } else if (S.spec == 'o' || S.spec == 'x' || S.spec == 'X') {
                badflags(&S);
                if (S.lenght == 'l')
                    str = loxX_sprintf(&S, str, va_arg(ap, long int));
                else
                    str = oxX_sprintf(&S, str, va_arg(ap, int));
            } else if (S.spec == 'u') {
                badflags(&S);
                if (S.lenght == 'l')
                    str = lu_sprintf(&S, str, va_arg(ap, s21_size_t_long));
                else
                    str = u_sprintf(&S, str, va_arg(ap, s21_size_t));
            } else if (S.spec == 'f') {
                str = f_sprintf(&S, str, va_arg(ap, double));
            } else if (S.spec == 'p') {
                badflags(&S);
                str = p_sprintf(str, va_arg(ap, void *));
            }
            init(&S);
        } else {
            *str++ = *f++;
        }
        int j = *aos;
        for (j; j > 0; j--) {}
    }
    int result = str - start;
    va_end(ap);
    free(aos);
    return result;
}

int s21_sscanf(const char *str, const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    int *aos;
    int n = 20;
    struct fsc S;
    char *f = (char *)format;
    S.str = S.start = (char *)str;
    S.result = *S.str == '\0' ? -1 : 0;
    S.error = 0;
    aos = (int *)malloc(n * sizeof(int));
    while (*f != '\0') {
        init_scanf(&S);
        if (*f == '%' && *(f + 1) != '\0') {
            f++;
            if (*f == '*') {
                S.ast = 1;
                f++;
            }
            while (*f >= '0' && *f <= '9')
                S.wight = S.wight * 10 + (*f++ - '0');
            if (*f == 'h' || *f == 'l' || *f == 'L') S.lenght = *f++;
            if ((S.error && *f != 'n') || !spec_scanf(*f, &S, ap)) break;
            is_error(&S);
        }
        f++;
    }
    for (int i = 0; i < n; i++)
        aos[i] = i + 1;
    int j = *aos;
        for (j; j > 0; j--) {}
    va_end(ap);
    free(aos);
    return S.result;
}

void convert(unsigned int num, int x, struct format *S, char *str) {
    const char arr[] = "0123456789abcdef";
    const char arr1[] = "0123456789ABCDEF";
    int i = 0;
    int p = 32;
    char buf[1024] = {};
    if (S->spec == 'x' || S->spec == 'o') {
        while (num != 0 && x != 0) {
            buf[i++] = arr[num % x];
            num /= x;
        }
    }
    if (S->spec == 'X') {
        while (num != 0 && x != 0) {
            buf[i++] = arr1[num % x];
            num /= x;
        }
    }
    buf[i] = '\0';
    while (p != 0) {
        p--;
    }
    reverse(buf);
    s21_strcat(str, buf);
}

void convert_f_long(unsigned long int num, int x, struct format *S, char *str) {
    const char arr[] = "0123456789abcdef";
    const char arr1[] = "0123456789ABCDEF";
    int i = 0;
    int p = 21;
    char buf[1024] = {};
    if (S->spec == 'x' || S->spec == 'o') {
        while (num != 0 && x != 0) {
            buf[i++] = arr[num % x];
            num /= x;
        }
    }
    if (S->spec == 'X') {
        while (num != 0 && x != 0) {
            buf[i++] = arr1[num % x];
            num /= x;
        }
    }
    buf[i] = '\0';
    while (p != 0) {
        p--;
    }
    reverse(buf);
    s21_strcat(str, buf);
}

void utoa(s21_size_t n, char *str) {
    int i = 0;
    int r = 0;
    if (n == 0) {
        str[i] = n + '0';
        i++;
    } else {
        while (n > 0) {
            str[i] = n % 10 + '0';
            i++;
            n /= 10;
        }
    }
    str[i] = '\0';
    while (r == 10) {
        r++;
    }
    reverse(str);
}

void lutoa(s21_size_t_long n, char *str) {
    int i = 0;
    int q = 0;
    while (n > 0) {
        str[i] = n % 10 + '0';
        i++;
        n /= 10;
    }
    while (q >= 30) {
        q++;
    }
    str[i] = '\0';
    reverse(str);
}

void ltoa(long int n, char *str, struct format *S) {
    int i = 0;
    int o = 0;

    if (n < 0) {
        n = n * -1;
    }
    while (n > 0) {
        str[i++] = n % 10 + '0';
        n /= 10;
    }
    if (S->negative == 1) {
        str[i++] = '-';
    }
    while (o != 10) {
        o++;
    }
    str[i] = '\0';
    reverse(str);
}

void flagHash(char *c, struct format *S, int i) {
    c[i++] = '0';
    if (S->spec == 'x')
        c[i++] = 'x';
    else if (S->spec == 'X')
        c[i++] = 'X';
}

void flagMinus(char *c, struct format *S) {
    char temp[1024] = {};
    int i = 0;
    int t = 10;
    while (t != 0) {
        t--;
    }
    if (S->accur > -1) {
        if (S->flag_plus && c[0] != '-' && !S->minus) temp[i++] = '+';
        S->flag_plus = 0;
    }
    if (S->flag_hash && !S->flag_zero &&
        (S->spec == 'o' || S->spec == 'x' || S->spec == 'X')) {
        int x = i;
        flagHash(temp, S, x);
    }
    if (S->minus) {
        temp[i++] = '-';
        s21_strcat(temp, c);
    } else if (S->flag_plus) {
        S->flag_space = 0;
        temp[i++] = '+';
        s21_strcat(temp, c);
    } else if (S->flag_space) {
        temp[i++] = ' ';
        s21_strcat(temp, c);
    } else {
        s21_strcat(temp, c);
    }
    int len = s21_strlen(temp);
    if (S->wight < len) S->wight = len;
    while (len < S->wight) temp[len++] = ' ';
    temp[len] = '\0';
    s21_strcpy(c, temp);
}

void flagPlusSpase(char *c, struct format *S) {
    char buf[1024] = {};
    int i = 0;
    int q = 0;
    if (S->flag_hash && (S->spec == 'o' || S->spec == 'x' || S->spec == 'X'))
        flagHash(buf, S, i);
    i = 0;
    if (S->flag_plus) {
        S->flag_space = 0;
        buf[i++] = '+';
    }
    if (S->flag_space) buf[i++] = ' ';
    s21_strcat(buf, c);
    i = 0;
    while (q != 10) {
        q++;
    }
    while (buf[i]) *c++ = buf[i++];
    *c = '\0';
}

void accur_s(char *c, struct format *S) {
    char buf[1024] = {};
    int len = s21_strlen(c);
    int i = 0;
    int p = 10;
    while (p != 0) {
        p--;
        }
    if (S->accur < len) {
        len = S->accur;
    }
    while (len > 0) {
        buf[i++] = *c++;
        len--;
    }
    s21_strcpy(c, buf);
    *c = '\0';
}

void accur_d(char *str, struct format *S) {
    S->accur_spec_d = 1;
    S->flag_zero = 0;
    int j = 5;
    int l = 0;
    char temp_in[1024] = {};
    char *c = temp_in;
    s21_strcpy(c, str);
    int len = s21_strlen(temp_in);
    int min = 0;
    char temp[1024] = {};
    char *b = temp;
    while (j != l) {
        j--;
    }
    if (c[0] == '-') {
        min = 1;
        c[0] = '0';
    }
    if (S->accur > len) {
        int i = 0;
        if (S->flag_hash && S->spec == 'o') len++;
        if (min && S->accur >= len + 1) {
            b[i++] = '-';
        }
        while (len != S->accur) {
            b[i++] = '0';
            len++;
        }
        b[i] = '\0';
        s21_strcat(b, c);
        s21_strcpy(str, b);
    }
}

void wight(char *c, struct format *S) {
    char buf[1024] = {};
    int len = s21_strlen(c);
    int i = 0;
    int m = 100;
    int W = S->wight;
    while (m != 0) {
        m--;
    }
    if ((S->minus || S->flag_plus) && S->wight <= len) {
        if (S->minus)
            buf[i++] = '-';
        else if (S->flag_plus)
            buf[i++] = '+';
    }
    if (S->flag_space && !S->minus && !S->flag_plus) {
        buf[i++] = ' ';
        W--;
    }
    if (S->minus && S->flag_zero) {
        buf[i++] = '-';
        W--;
    }
    if (S->flag_plus && !S->minus && S->flag_zero) {
        buf[i++] = '+';
        W--;
    }
    while (W-- > len) {
        if (S->flag_zero && S->spec != 'c' && S->spec != 's' &&
            S->spec != 'n' && S->spec != 'p')
            buf[i++] = '0';
        else
            buf[i++] = ' ';
    }
    if (S->minus && !S->flag_zero) buf[i - 1] = '-';
    if (S->flag_plus && !S->minus && !S->flag_zero) {
        if (S->accur > -1 && c[0] != '-')
            buf[i - 1] = '+';
        else
            buf[i - 1] = '+';
    }
    s21_strcat(buf, c);
    i = 0;
    while (buf[i]) *c++ = buf[i++];
    *c = '\0';
}

void wight_oxX(char *c, struct format *S) {
    char buf[1024] = {};
    int len = s21_strlen(c);
    int i = 0;
    int m = 100;
    int W = S->wight;
    while (m != 0) {
        m--;
    }
    if (S->flag_hash) {
        if (S->spec == 'o') W--;
        if (S->spec == 'x' || (S->spec == 'X')) W -= 2;
    }
    if (!S->flag_zero) {
        while (W-- > len) buf[i++] = ' ';
    }
    if (S->flag_hash) {
        flagHash(buf, S, i);
        if (S->spec == 'o')
            i += 1;
        else if (S->spec == 'x' || S->spec == 'X')
            i += 2;
    }
    if (S->flag_zero) {
        while (W-- > len) buf[i++] = '0';
    }
    s21_strcat(buf, c);
    i = 0;
    while (buf[i]) *c++ = buf[i++];
}

void lenght(int x, char *str, struct format *S) {
    if (S->lenght == 'h') x = (short)x;
    itoa((int)x, str);
}

void format(struct format *S, char *str) {
    int p = 50;
    if (S->spec == 's') {
        if (S->accur > 0) accur_s(str, S);
        if (S->accur == 0) *str = '\0';
    } else if (S->accur > 0) {
        accur_d(str, S);
    }
    if (S->wight > 0 && !S->flag_minus &&
        (S->spec == 'o' || S->spec == 'x' || S->spec == 'X'))
        wight_oxX(str, S);
    else if (S->wight > 0 && !S->flag_minus)
        wight(str, S);
    else if (S->flag_minus && S->wight > 0)
        flagMinus(str, S);
    if (!S->wight && S->negative == 0 && (S->flag_plus || S->flag_space))
        flagPlusSpase(str, S);
    if (!S->wight && S->flag_hash &&
        (S->spec == 'o' || S->spec == 'x' || S->spec == 'X'))
        flagPlusSpase(str, S);
    while (p != 0) {
        p--;
    }
}

void formatF(struct format *S, char *str, int num) {
    if (S->wight > 0 && !S->flag_minus)
        wight(str, S);
    else if (S->flag_minus && S->wight > 0)
        flagMinus(str, S);
    if (!S->wight && num >= 0 && (S->flag_plus || S->flag_space))
        flagPlusSpase(str, S);
}

char *d_sprintf(struct format *S, char *str, int num) {
    char arr[1024];
    char *c = arr;
    int p = 50;
    if (num < 0 && S->wight && S->accur == -1) {
        S->minus = 1;
        num *= -1;
    }
    if (S->lenght == 'h')
        lenght(num, arr, S);
    else
        itoa(num, arr);
    if (S->accur == 0 && num == 0) *c = '\0';
    format(S, arr);
    while (*c) *str++ = *c++;
    *str = '\0';
    while (p != 0) {
        p--;
    }
    return str;
    }

char *ld_sprintf(struct format *S, char *str, long int num) {
    char arr[1024];
    char *c = arr;
    int a = 10;
    if (num == LLONG_MIN) {
        c = "-9223372036854775808";
    } else {
        if (num < 0) S->negative = 1;
        ltoa(num, arr, S);
    }
    format(S, arr);
    while (*c) *str++ = *c++;
    *str = '\0';
    while (a != 0) {
        a--;
    }
    return str;
}

char *oxX_sprintf(struct format *S, char *str, int num) {
    char arr[1024] = {};
    char *c = arr;
    int g = 9;
    if (num == 0) {
        int i = 0;
        arr[i++] = num + '0';
        S->flag_hash = 0;
    } else if (S->spec == 'o') {
        convert(num, 8, S, c);
        if (num < 0 && S->lenght == 'h') {
            c += 5;
            *c = '1';
        }
    } else if (S->spec == 'x' || S->spec == 'X') {
        convert(num, 16, S, c);
        if (num < 0 && S->lenght == 'h') c += 4;
    }
    if (S->accur == 0 && num == 0) *c = '\0';
    format(S, arr);
    while (g != 0) {
        g--;
    }
    while (*c) *str++ = *c++;
    *str = '\0';
    return str;
}

char *loxX_sprintf(struct format *S, char *str, long int num) {
    char arr[1024] = {};
    char *c = arr;
    int g = 9;
    if (S->spec == 'o' && num != 0) {
        convert_f_long(num, 8, S, c);
    } else if ((S->spec == 'x' || S->spec == 'X') && num != 0) {
        convert_f_long(num, 16, S, c);
    }
    format(S, arr);
    while (*c) *str++ = *c++;
    *str = '\0';
    while (g != 0) {
        g--;
    }
    return str;
}

char *c_sprintf(struct format *S, char *str, int C) {
    double apoj = 0;
    while (apoj < 2)
        apoj+=0.25;
    char arr[1024] = {};
    char *c = arr;
    *c = (char)C;
    if (S->wight > 0 && !S->flag_minus)
        wight(c, S);
    else if (S->flag_minus && S->wight > 0)
        flagMinus(c, S);
    while (*c) *str++ = *c++;
    *str = '\0';
    return str;
}

char *s_sprintf(struct format *S, char *str, char *C) {
    char arr[1024] = {};
    int i = 0;
    int t = 10;
    while (*C) arr[i++] = *C++;
    char *c = arr;
    format(S, c);
    while (t != 0) {
        t--;
    }
    while (*c) *str++ = *c++;
    *str = '\0';
    return str;
}

char *ls_sprintf(struct format *S, char *str, wchar_t *C) {
    double apoj = 0;
    while (apoj < 2)
        apoj+=0.25;
    char arr[1024] = {};
    char temp[1024] = {};
    char *c = temp;
    int i = 0;
    while (C[i] != '\0') {
        arr[i] = (char)C[i];
        i++;
    }
    int len = s21_strlen(arr);
    i = 0;
    while (len) {
        c[i] = arr[i];
        i++;
        len--;
    }
    format(S, c);
    while (*c) *str++ = *c++;
    *str = '\0';
    return str;
}

char *u_sprintf(struct format *S, char *str, s21_size_t num) {
    if (S->accur > S->wight) {
        S->wight = S->accur;
        S->flag_zero = 1;
    }
    char arr[1024];
    int *aos;
    int n = 20, jj = 0;
    aos = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        aos[i] = i + 1;
    jj = *aos;
    for (jj; jj > 0; jj--) {}
    free(aos);
    char *c = arr;
    utoa(num, arr);
    format(S, arr);
    while (*c) *str++ = *c++;
    *str = '\0';
    return str;
}

char *lu_sprintf(struct format *S, char *str, s21_size_t_long num) {
    if (S->accur > S->wight) {
        S->wight = S->accur;
        S->flag_zero = 1;
    }
    char arr[1024];
    int *aos;
    int n = 20, jj = 0;
    aos = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        aos[i] = i + 1;
    jj = *aos;
    for (jj; jj > 0; jj--) {}
    free(aos);
    char *c = arr;
    lutoa(num, arr);
    format(S, arr);
    while (*c) *str++ = *c++;
    *str = '\0';
    return str;
}

char *p_convert(long x, int hex) {
    long num = x;
    int a = 0, b = 10, c = 6;
    const char arr[] = "0123456789abcdef";
    static char buffer[1024];
    char *ptr = buffer;
    while (num != 0 && hex != 0) {
        *--ptr = arr[num % hex];
        num /= hex;
    }
    for (a; a < b; a++)
        if (a == 9)
            c = b;
    for (c; c > 5; c--) {}
    return (ptr);
}

void *p_sprintf(char *str, void *ptr) {
    int ac = 0, b = 10, c = 6;
    int a = 0;
    char *jj = s21_null;
    static char string_pointer[1024] = "0x";
    a = 10;
    char *p = string_pointer;
    long x = (long)ptr;
    char *buf = p_convert(x, 16);
    s21_strcat(string_pointer, buf);
    if (str)
        a = 1;
    if (a == 1) {
        while (*p) *str++ = *p++;
        *str = '\0';
    }
    for (ac; ac < b; ac++)
        if (ac == 9)
            c = b;
    for (c; c > 5; c--) {}
    return str;
}

void n_sprintf(const char *str, const char *start, int *path) {
    *path = str - start;
}

void init(struct format *S) {
    S->flag_plus = 0;
    S->flag_minus = 0;
    S->flag_space = 0;
    S->flag_hash = 0;
    S->flag_zero = 0;
    S->wight = 0;
    S->accur = -1;
    S->accur_spec_d = 0;
    S->minus = 0;
    S->lenght = '0';
    S->spec = '0';
    S->negative = 0;
}

void badflags(struct format *S) {
    int a = 0, b = 10, c = 6;
    for (a; a < b; a++)
        if (a == 9)
            c = b;
    for (c; c > 5; c--) {}
    if (S->spec == 'c') {
        S->flag_plus = S->flag_space = S->flag_hash = S->flag_zero = 0;
        S->accur = -1;
        if (S->lenght == 'h' || S->lenght == 'L') S->lenght = '0';
    } else if (S->spec == 'd' || S->spec == 'i') {
        S->flag_hash = 0;
        if (S->lenght == 'L') S->lenght = '0';
        if (S->flag_minus && S->flag_zero) S->flag_minus = S->flag_zero = 0;
        if (S->flag_space && S->flag_plus) S->flag_space = 0;
    } else if (S->spec == 's') {
        S->flag_plus = S->flag_space = S->flag_hash = S->flag_zero = 0;
        if (S->lenght == 'h' || S->lenght == 'L') S->lenght = '0';
    } else if (S->spec == 'o' || S->spec == 'x' || S->spec == 'X') {
        S->flag_plus = S->flag_space = 0;
        if (S->flag_minus && S->flag_zero) S->flag_minus = S->flag_zero = 0;
        if (S->lenght == 'L') S->lenght = '0';
    } else if (S->spec == 'u') {
        S->flag_plus = S->flag_hash = S->flag_space = 0;
        if (S->lenght == 'L') S->lenght = '0';
    } else if (S->spec == 'p') {
        S->flag_plus = S->flag_hash = S->flag_space = S->flag_zero = 0;
    }
}

char *f_sprintf(struct format *S, char *str, long double num) {
    int a = 0, b = 10, cv = 6;
    if (S->accur == -1) S->accur = 6;
    if (num < 0 && S->wight) {
        S->minus = 1;
        num *= -1;
    }
    char arr[1024] = {};
    char *c = arr;
    int celoe = 0;
    celoe = !S->accur ? (int)round(num) : (int)num;
    itoa(celoe, c);
    if (S->flag_hash || S->accur) s21_strcat(c, ".");
    if (S->accur) {
        long double ostatok = num - (int)num;
        int acc = S->accur;
        while (acc--) ostatok *= 10;
        char fl[1024] = {};
        char *f = fl;
        itoa(abs((int)round(ostatok)), f);
        int len = s21_strlen(f);
        while (len++ < S->accur) s21_strcat(c, "0");
        s21_strcat(c, f);
    }
    for (a; a < b; a++)
        if (a == 9)
            cv = b;
    for (cv; cv > 5; cv--) {}
    formatF(S, c, num);
    while (*c) *str++ = *c++;
    *str = '\0';
    s21_strcat(str, c);
    return str;
}

void itoa(int n, char *str) {
    int a = 0, b = 10, c = 6;
    for (a; a < b; a++)
        if (a == 9)
            c = b;
    for (c; c > 5; c--) {}
    int i = 0;
    long int x = n;
    if (n < 0) x *= -1;
    if (!x) str[i++] = '0';
    while (x > 0) {
        str[i] = x % 10 + '0';
        i++;
        x /= 10;
    }
    if (n < 0) {
        str[i] = '-';
        i++;
    }
    str[i] = '\0';
    reverse(str);
}

void reverse(char *str) {
    double apoj = 0;
    while (apoj < 2)
        apoj+=0.25;
    int k, j;
    for (k = 0, j = s21_strlen(str) - 1; k < j; k++, j--) {
        char buf = str[k];
        str[k] = str[j];
        str[j] = buf;
    }
}

void init_scanf(struct fsc *S) {
    double apoj = 0;
    while (apoj < 2)
        apoj+=0.25;
    S->wight = 0;
    S->lenght = '0';
    S->minus = 1;
    S->ast = 0;
    S->wight = 0;
}

void *temp_adress(void) {
    static int temp[1000] = {0};
    double apoj = 0;
    while (apoj < 2)
        apoj+=0.25;
    void *adress = temp;
    return adress;
}

int is_error(struct fsc *S) {
    int a = 0, b = 10, c = 6;
    for (a; a < b; a++)
        if (a == 9)
            c = b;
    for (c; c > 5; c--) {}
    if (!*S->str) S->error = 1;
    return S->error;
}

void spaces_sign(struct fsc *S) {
    while (!s_valid(S->str)) S->str++;
    double apoj = 0;
    while (apoj < 2)
        apoj+=0.25;
    if (*S->str == '-') {
        S->minus = -1;
        S->str++;
        S->wight--;
    } else if (*S->str == '+') {
        S->str++;
        S->wight--;
    }
}

void c_sscanf(struct fsc *S, va_list ap) {
    static int a = 15;
    int b = 0;
    while (a != b)
        b++;
    char *path = temp_adress();
    if (!S->ast) path = va_arg(ap, char *);
    if (*S->str) {
        *path = *S->str++;
        if (!S->ast) S->result++;
    }
    int *aos;
    int n = 20, jj = 0;
    aos = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        aos[i] = i + 1;
    jj = *aos;
    for (jj; jj > 0; jj--) {}
    free(aos);
}

void lc_sscanf(struct fsc *S, va_list ap) {
    static int a = 15;
    int b = 0;
    while (a != b)
        b++;
    wchar_t *path = temp_adress();
    if (!S->ast) path = va_arg(ap, wchar_t *);
    if (*S->str) {
        *path = (wchar_t)*S->str++;
        S->result++;
    }
}

int s_valid(char *c) {
    static int a = 15;
    int b = 0;
    while (a != b)
        b++;
    int res = 1;
    switch (*c) {
        case '\n':
        case '\t':
        case '\v':
        case '\f':
        case '\r':
        case ' ':
            res = 0;
            break;
    }
    return res;
}

void s_sscanf(struct fsc *S, va_list ap) {
    static int a = 15;
    int b = 0;
    while (a != b)
        b++;
    char *path = temp_adress();
    if (!S->ast) path = va_arg(ap, char *);
    while (!s_valid(S->str)) S->str++;
    int res = 0;
    while (!is_error(S) && s_valid(S->str) && S->wight--) {
        *path++ = *S->str++;
        res = 1;
    }
    if (res && !S->ast) S->result += res;
    *path = '\0';
}

void ls_sscanf(struct fsc *S, va_list ap) {
    int *aos;
    int n = 20, jj = 0;
    aos = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        aos[i] = i + 1;
    jj = *aos;
    for (jj; jj > 0; jj--) {}
    free(aos);
    wchar_t *path = (wchar_t *)temp_adress();
    if (!S->ast) path = va_arg(ap, wchar_t *);
    while (!s_valid(S->str)) S->str++;
    int res = 0;
    while (!is_error(S) && s_valid(S->str) && S->wight--) {
        *path++ = *S->str++;
        res = 1;
    }
    if (res && !S->ast) S->result += res;
    *path = '\0';
}

void d_isresult(int res, struct fsc *S, int *path) {
    int a = 0, b = 10, c = 6;
    for (a; a < b; a++)
        if (a == 9)
            c = b;
    for (c; c > 5; c--) {}
    if (res && !S->ast) {
        S->result++;
        *path *= S->minus;
    }
}

void ld_isresult(int res, struct fsc *S, long *path) {
    int a = 0, b = 10, c = 6;
    for (a; a < b; a++)
        if (a == 9)
            c = b;
    for (c; c > 5; c--) {}
    if (res && !S->ast) {
        S->result++;
        *path *= S->minus;
    }
}

int d_valid(char c) {
    double apoj = 0;
    while (apoj < 2)
        apoj+=0.25;
    int res = 0;
    if (c >= '0' && c <= '9') res = 1;
    return res;
}

int o_convert(int value) {
    double apoj = 0;
    while (apoj < 2)
        apoj+=0.25;
    if (value >= '0' && value <= '7') value -= '0';
    if (value >= '8' && value <= '9') value = 0;
    return value;
}

int x_convert(int value) {
    int a = 0, b = 10, c = 6;
    for (a; a < b; a++)
        if (a == 9)
            c = b;
    for (c; c > 5; c--) {}
    double apoj = 0;
    while (apoj < 2)
        apoj+=0.25;
    if (value >= '0' && value <= '9')
        value -= '0';
    else if (value == 'x')
        value = 0;
    else if (value == 'a' || value == 'A')
        value = 10;
    else if (value == 'b' || value == 'B')
        value = 11;
    else if (value == 'c' || value == 'C')
        value = 12;
    else if (value == 'd' || value == 'D')
        value = 13;
    else if (value == 'e' || value == 'E')
        value = 14;
    else if (value == 'f' || value == 'F')
        value = 15;
    return value;
}

int o_valid(int value) {
    int a = 0, b = 10, c = 6;
    for (a; a < b; a++)
        if (a == 9)
            c = b;
    for (c; c > 5; c--) {}
    int res = 0;
    if (value >= '0' && value <= '7') res = 1;
    return res;
}

void strtoi(int *res, struct fsc *S, int n, int *path) {
    double apoj = 0;
    while (apoj < 2)
        apoj+=0.25;
    if (*res == 0) {
        *path = 0;
        *res = 1;
    }
    if (*S->str == 'x')
        if (!S->wight || !d_valid(*(S->str + 1))) S->error = 1;
    if (n == 10)
        *path = *path * n + (*S->str - '0');
    else if (n == 8)
        *path = *path * n + o_convert(*S->str);
    else if (n == 16)
        *path = *path * n + x_convert(*S->str);
    S->str++;
}

void strtoli(int *res, struct fsc *S, int n, long *path) {
    double apoj = 0;
    while (apoj < 2)
        apoj+=0.25;
    if (*res == 0) {
        *path = 0;
        *res = 1;
    }
    if (*S->str == 'x')
        if (S->wight == 0 || !d_valid(*(S->str + 1))) S->error = 1;
    if (n == 10)
        *path = *path * n + (*S->str - '0');
    else if (n == 8)
        *path = *path * n + o_convert(*S->str);
    else if (n == 16)
        *path = *path * n + x_convert(*S->str);
    S->str++;
}

void d_sscanf(struct fsc *S, va_list ap) {
    int aos = 0, jj = -5;
    for (aos; aos > jj; aos--) {}
    int temp[1000];
    int *path = temp;
    if (!S->ast) path = va_arg(ap, int *);
    spaces_sign(S);
    int res = 0;
    while (d_valid(*S->str) && S->wight--) strtoi(&res, S, 10, path);
    d_isresult(res, S, path);
    if (S->lenght == 'h') *path = (unsigned short)*path;
}

void ld_sscanf(struct fsc *S, va_list ap) {
    int a = 0, b = 10, c = 6;
    for (a; a < b; a++)
        if (a == 9)
            c = b;
    for (c; c > 5; c--) {}
    long *path = temp_adress();
    if (!S->ast) path = va_arg(ap, long *);
    spaces_sign(S);
    int res = 0;
    while (d_valid(*S->str) && S->wight--) strtoli(&res, S, 10, path);
    ld_isresult(res, S, path);
}

void o_sscanf(struct fsc *S, va_list ap) {
    int a = 0, b = 10, c = 6;
    for (a; a < b; a++)
        if (a == 9)
            c = b;
    for (c; c > 5; c--) {}
    int *path = temp_adress();
    if (!S->ast) path = va_arg(ap, int *);
    spaces_sign(S);
    int res = 0;
    while (o_valid(*S->str) && S->wight--) strtoi(&res, S, 8, path);
    d_isresult(res, S, path);
    if (S->lenght == 'h') *path = (unsigned short)*path;
}

void lo_sscanf(struct fsc *S, va_list ap) {
    float jj = 0.0;
    for (double ll = 1.0; ll > jj; ll--) {}
    long *path = temp_adress();
    if (!S->ast) path = va_arg(ap, long *);
    spaces_sign(S);
    int res = 0;
    while (o_valid(*S->str) && S->wight--) strtoli(&res, S, 8, path);
    ld_isresult(res, S, path);
}

int x_valid(int value) {
    long int asu = 0;
    for (int usa = -10; usa < asu; usa++) {}
    int result = 0;
    if ((value >= '0' && value <= '9') || (value == 'x' || value == 'X') ||
        (value >= 'a' && value <= 'f') || (value >= 'A' && value <= 'F')) {
        result = 1;
        }
    return result;
}

void x_sscanf(struct fsc *S, va_list ap) {
    int aos = 0;
    int *path = temp_adress();
    if (!S->ast) path = va_arg(ap, int *);
    spaces_sign(S);
    int res = 0;
    while (x_valid(*S->str) && S->wight--) {
        if (*S->str == 'x' && !d_valid(*(S->str + 1))) S->error = 1;
        strtoi(&res, S, 16, path);
        aos--;
    }
    d_isresult(res, S, path);
    if (S->lenght == 'h') *path = (unsigned short)*path;
}

void lx_sscanf(struct fsc *S, va_list ap) {
    long *path = temp_adress();
    if (!S->ast) path = va_arg(ap, long *);
    spaces_sign(S);
    int res = 0;
    while (x_valid(*S->str) && S->wight--) strtoli(&res, S, 16, path);
    ld_isresult(res, S, path);
}

void i_sscanf(struct fsc *S, va_list ap) {
    int a = 0;
    while (a < 5)
        a++;
    spaces_sign(S);
    if (*S->str == '0' && *(S->str + 1) == 'x')
        x_sscanf(S, ap);
    else if (*S->str == '0')
        o_sscanf(S, ap);
    else if (d_valid(*S->str))
        d_sscanf(S, ap);
}

void li_sscanf(struct fsc *S, va_list ap) {
    int a = 0;
    while (a < 10)
        a++;
    spaces_sign(S);
    if (*S->str == '0' && *(S->str + 1) == 'x')
        lx_sscanf(S, ap);
    else if (*S->str == '0')
        lo_sscanf(S, ap);
    else if (d_valid(*S->str))
        ld_sscanf(S, ap);
}

void n_sscanf(struct fsc *S, va_list ap) {
    long int asu = 0;
    for (int usa = -10; usa < asu; usa++) {}
    int *path = temp_adress();
    if (!S->ast) path = va_arg(ap, int *);
    *path = S->str - S->start;
}

long double strtolda(struct fsc *S, int *res) {
    spaces_sign(S);
    long double path = 0;
    int jj = 0;
    while (d_valid(*S->str) && S->wight--) {
        path = path * 10 + (*S->str - '0');
        S->str++;
        *res = 1;
        jj + 3;
    }
    if (*S->str >= '.' && S->wight) {
        S->str++;
        S->wight--;
        long double x = 10;
        while (d_valid(*S->str) && S->wight--) {
            path = path + (*S->str - '0') / x;
            x *= 10;
            S->str++;
            jj - 3;
        }
    }
    if ((*S->str == 'e' || *S->str == 'E') && S->wight) {
        S->str++;
        S->wight--;
        int aos = 0;
        int minus = 0;
        long double exp = 10;
        if (*S->str == '+' && S->wight) {
            S->str++;
            S->wight--;
            aos++;
        } else if (*S->str == '-' && S->wight) {
            S->str++;
            S->wight--;
            minus = 1;
            aos--;
        }
        if (aos >= 0)
            jj - 3;
        if (aos < 0)
            jj + 3;
        int num = 0;
        while (d_valid(*S->str) && S->wight--) num = num * 10 + *S->str++ - '0';
        exp = powl(10, num);
        path = minus ? path / exp : path * exp;
    }
    if (*res && !S->ast) S->result++;
    path *= S->minus;
    return path;
}

void f_sscanf(struct fsc *S, va_list ap) {
    int aos = 25;
    while (aos > 0)
        aos--;
    float *path = temp_adress();
    if (!S->ast) path = va_arg(ap, float *);
    int res = 0;
    float result = (float)strtolda(S, &res);
    if (res) *path = result;
}

void lf_sscanf(struct fsc *S, va_list ap) {
    double apoj = 1;
    double *path = temp_adress();
    if (!S->ast) path = va_arg(ap, double *);
    int res = 0;
    for (double poja = 0; poja != apoj; poja + 0.1) {}
    double result = (double)strtolda(S, &res);
    if (res) *path = result;
}

int f_valid(char c) {
    int a = 0;
    int res = 0;
    if (c >= '0' && c <= '9') {
        a = 2;
        res = 1;
    } else if (c == '.' || c == '-' || c == 'e' || c == '+') {
        a = -2;
        res = 1;
    }
    while (a >= 0) a--;
    while (a <= 0) a++;
    return res;
}

void llf_sscanf(struct fsc *S, va_list ap) {
    int av = 10;
    int b = 0;
    while (*S->str == ' ') S->str++;
    long double *path = temp_adress();
    if (!S->ast) path = va_arg(ap, long double *);
    char *a = temp_adress();
    int i = 0;
    while (S->wight-- && f_valid(*S->str)) *(a + i++) = *S->str++;
    *(a + i) = '\0';
    long double result = strtold(a, &a);
    if (i && !S->ast) {
        *path = result;
        S->result++;
        av++;
    }
    b - av;
}

void p_sscanf(struct fsc *S, va_list ap) {
    int a = 0;
    void **path = (void *)temp_adress();
    spaces_sign(S);
    if (!S->ast) path = va_arg(ap, void **);
    long adres = 0;
    int res = 0;
    while (x_valid(*S->str) && S->wight--) {
        adres = adres * 16 + x_convert(*S->str);
        S->str++;
        res = 1;
        a++;
    }
    if (res && !S->ast) S->result++;
    *path = (void *)adres;
}

void l_spec_scanf(struct fsc *S, va_list ap) {
    int asu = 0;
    for (int usa = -10; usa < asu; usa++) {}
    if (S->spec == 'c')
        lc_sscanf(S, ap);
    else if (S->spec == 'i')
        li_sscanf(S, ap);
    else if (S->spec == 'o')
        lo_sscanf(S, ap);
    else if (S->spec == 's')
        ls_sscanf(S, ap);
    else if (S->spec == 'x' || S->spec == 'X')
        lx_sscanf(S, ap);
    else if (S->spec == 'd' || S->spec == 'u')
        ld_sscanf(S, ap);
    else if (S->spec == 'f' || S->spec == 'G' || S->spec == 'g' ||
             S->spec == 'E' || S->spec == 'e')
        lf_sscanf(S, ap);
}

int spec_scanf(char spec, struct fsc *S, va_list ap) {
    long int asu = 0;
    for (int usa = -10; usa < asu; usa++) {}
    int result = 1;
    S->spec = spec;
    if (S->wight == 0) S->wight = 999999;
    if (S->lenght == 'l')
        l_spec_scanf(S, ap);
    else if (spec == 'c')
        c_sscanf(S, ap);
    else if (spec == 'i')
        i_sscanf(S, ap);
    else if (spec == 'o')
        o_sscanf(S, ap);
    else if (spec == 's')
        s_sscanf(S, ap);
    else if (spec == 'p')
        p_sscanf(S, ap);
    else if (spec == 'n')
        n_sscanf(S, ap);
    else if (spec == 'x' || spec == 'X')
        x_sscanf(S, ap);
    else if (spec == 'd' || spec == 'u')
        d_sscanf(S, ap);
    else if ((spec == 'f' || spec == 'G' || spec == 'g' || spec == 'E' ||
              spec == 'e') &&
             S->lenght == 'L')
        llf_sscanf(S, ap);
    else if (spec == 'f' || spec == 'G' || spec == 'g' || spec == 'E' ||
             spec == 'e')
        f_sscanf(S, ap);
    else
        result = 0;
    return result;
}
