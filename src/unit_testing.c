#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

START_TEST(sscanf_test) {
    wchar_t wc1, wc2;
    int a1 = 1, b1 = 0, i1 = 0, n1 = 0, i2 = 0, n2 = 0;
    unsigned int a2 = 1, a3 = 1, b2 = 0, b3 = 0;
    long e1 = 1, r1 = 1;
    unsigned long e2 = 0, r2 = 0;
    long double e3 = 0, e4 = 0, g3 = 0, g4 = 0, ld1 = 0, ld2 = 1;
    float f1 = 0, f2 = 1;
    char q1 = '0', w1 = '1', arr1[100] = "", arr2[100] = "";
    void *adres1 = s21_null, *adres2 = s21_null;
    ck_assert_int_eq(
        s21_sscanf(" -12345678asd", " %2d%2o%2x%1c%2s", &a1, &a2, &a3, &q1,
                   arr1),
        sscanf(" -12345678asd", " %2d%2o%2x%1c%2s", &b1, &b2, &b3, &w1, arr2));
    ck_assert_int_eq(a1, b1);
    ck_assert_int_eq(a2, b2);
    ck_assert_int_eq(a3, b3);
    ck_assert_int_eq(q1, w1);
    ck_assert_str_eq(arr1, arr2);
    ck_assert_int_eq(
        s21_sscanf("z1.25e5 1.23e+10", "%lc%G%Le", &wc1, &f1, &ld1),
        sscanf("z1.25e5 1.23e+10", "%lc%G%Le", &wc2, &f2, &ld2));
    ck_assert_float_eq(f1, f2);
    ck_assert_ldouble_eq(ld1, ld2);
    ck_assert_int_eq(s21_sscanf(" -123abcdeasd", "%2li%2lo", &e1, &e2),
                     sscanf(" -123abcdeasd", "%2li%2lo", &r1, &r2));
    ck_assert_int_eq(e1, r1);
    ck_assert_int_eq(e2, r2);
    ck_assert_int_eq(s21_sscanf("5 0x213def", "%1i%p%n", &i1, &adres1, &n1),
                     sscanf("5 0x213def", "%1i%p%n", &i2, &adres2, &n2));
    ck_assert_int_eq(i1, i2);
    ck_assert_int_eq(n1, n2);
    ck_assert_ptr_eq(adres1, adres2);
    ck_assert_int_eq(
        s21_sscanf("1.23451e+15 34567837433.456", "%Le%Lg", &e3, &g3),
        sscanf("1.23451e+15 34567837433.456", "%Le%Lg", &e4, &g4));
    ck_assert_ldouble_eq(e3, e4);
    ck_assert_ldouble_eq(g3, g4);
    ck_assert_int_eq(s21_sscanf(" -123abcdeasd", "%2li%2lo", &e1, &e2),
                     sscanf(" -123abcdeasd", "%2li%2lo", &r1, &r2));
    ck_assert_int_eq(s21_sscanf(" -123abcdeasd", "dfdf"),
                     sscanf(" -123abcdeasd", "dfdf"));
}
END_TEST

START_TEST(insert_test) {
    char *str1 = "Test";
    char *str2 = "quest";
    char *res = s21_null;

    res = s21_insert(str1, str2, 2);
    ck_assert_str_eq(res, "Tequestst");
    free(res);

    str1 = "The test";
    str2 = " perfect";
    res = s21_insert(str1, str2, 3);
    ck_assert_str_eq(res, "The perfect test");
    free(res);

    str1 = "Insert in";
    str2 = " end";
    res = s21_insert(str1, str2, 9);
    ck_assert_str_eq(res, "Insert in end");
    free(res);

    str1 = " with insert";
    str2 = "Start";
    res = s21_insert(str1, str2, 0);
    ck_assert_str_eq(res, "Start with insert");
    free(res);

    str1 = "Newspace";
    str2 = " ";
    res = s21_insert(str1, str2, 3);
    ck_assert_str_eq(res, "New space");
    free(res);

    str1 = "";
    str2 = " ";
    res = s21_insert(str1, str2, 0);
    ck_assert_str_eq(res, " ");
    free(res);

    char testSrc[] = "QWERTYUIOP";
    char testStr[] = "12345";
    char testResult[] = "QWERTY12345UIOP";
    size_t testIndex = 6;
    char *tests21_null = s21_null;
    char *funcResult = s21_null;
    int boolean = 0;

    funcResult = s21_insert(testSrc, testStr, testIndex);
    boolean = s21_memcmp(funcResult, testResult, 15) == 0;
    ck_assert_msg(boolean,
                  "FAILED with \"12345\" to 6th plase into \"QWERTYUIOP\"");
    free(funcResult);
    funcResult = s21_insert(tests21_null, tests21_null, testIndex);
    boolean = funcResult == s21_null;
    ck_assert_msg(boolean, "FAILED with S21_s21_null str");
    free(funcResult);
    funcResult = s21_insert(testSrc, testStr, 100);
    boolean = funcResult == s21_null;
    ck_assert_msg(boolean, "FAILED with exceeded index");
    free(funcResult);
}
END_TEST

START_TEST(trim_test) {
    char *res = s21_trim(" test ", " ");
    ck_assert_str_eq(res, "test");
    free(res);

    res = s21_trim(" ", " ");
    ck_assert_str_eq(res, "");
    free(res);

    res = s21_trim("*te*st*", "*");
    ck_assert_str_eq(res, "te*st");
    free(res);

    res = s21_trim(" te st001", " ");
    ck_assert_str_eq(res, "te st001");
    free(res);

    res = s21_trim(" /*()", ")(/ *");
    ck_assert_str_eq(res, "");
    free(res);
}
END_TEST

START_TEST(to_upper_test) {
    char destination[] = "Here w0 are123\0";
    char *test01 = s21_to_upper(destination);
    ck_assert_str_eq(test01, "HERE W0 ARE123");
    free(test01);

    char destination2[] = "Here w0 are\n\0";
    char *test02 = s21_to_upper(destination2);
    ck_assert_str_eq(test02, "HERE W0 ARE\n");
    free(test02);

    char destination3[] = "a\n\0";
    char *test03 = s21_to_upper(destination3);
    ck_assert_str_eq(test03, "A\n");
    free(test03);
}
END_TEST

START_TEST(to_lower_test) {
    char destination[] = "HERE W0 ARE123\0";
    char *test01 = s21_to_lower(destination);
    ck_assert_str_eq(test01, "here w0 are123");
    free(test01);

    char destination2[] = "HERE W0 ARE\n\0";
    char *test02 = s21_to_lower(destination2);
    ck_assert_str_eq(test02, "here w0 are\n");
    free(test02);

    char destination3[] = "A\n\0";
    char *test03 = s21_to_lower(destination3);
    ck_assert_str_eq(test03, "a\n");
    free(test03);
}
END_TEST

START_TEST(sprintf_test) {
    char c[255] = {}, d[255] = {}, x1 = 't';
    int n = 2100, n1 = 0, n2 = -21;
    short sh = 123, sh1 = -123;
    float f = 21.21, f1 = -21.21;
    long int lg = 12345678912345, lg1 = -12345678912345;
    s21_sprintf(c, "%% %p", &n);
    sprintf(d, "%% %p", &n);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%d %d %d %hd %hd %ld %ld %10ld", n, n1, n2, sh, sh1, lg,
                lg1, lg1);
    sprintf(d, "%d %d %d %hd %hd %ld %ld %10ld", n, n1, n2, sh, sh1, lg, lg1,
            lg1);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%10d %+3d %+010d %+-10d %+-10d % -10d %-10d %-10d", n,
                212121, 2121, n2, n, 21, 55, -55);
    sprintf(d, "%10d %+3d %+010d %+-10d %+-10d % -10d %-10d %-10d", n, 212121,
            2121, n2, n, 21, 55, -55);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%-10d %010d %010d %*d %2d", 21, n2, n, 10, n, n2);
    sprintf(d, "%-10d %010d %010d %*d %2d", 21, n2, n, 10, n, n2);
    ck_assert_str_eq(c, d);
    s21_sprintf(
        c, "%.*d %3.10d %.d %-+.5d %-+10.5d %.10d %.10d %2.2d %.d % d %.0d", 10,
        n, n2, 42, 21, 10, n, n2, -21, x1, 21, -42);
    sprintf(d, "%.*d %3.10d %.d %-+.5d %-+10.5d %.10d %.10d %2.2d %.d % d %.0d",
            10, n, n2, 42, 21, 10, n, n2, -21, x1, 21, -42);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%d %d %d %d %d %ld %ld", INT_MIN, INT_MAX, SHRT_MAX,
                SHRT_MIN, USHRT_MAX, LONG_MAX, LONG_MIN);
    sprintf(d, "%d %d %d %d %d %ld %ld", INT_MIN, INT_MAX, SHRT_MAX, SHRT_MIN,
            USHRT_MAX, LONG_MAX, LONG_MIN);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%c %10c %-10c", '!', 'a', 'b');
    sprintf(d, "%c %10c %-10c", '!', 'a', 'b');
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%c %c %c", CHAR_MAX, CHAR_MIN, UCHAR_MAX);
    sprintf(d, "%c %c %c", CHAR_MAX, CHAR_MIN, UCHAR_MAX);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%s %10s %-10s %-3s %.s %.3s %.10s", "hello", "hello",
                "hello", "hello", "hello", "hello", "hello");
    sprintf(d, "%s %10s %-10s %-3s %.s %.3s %.10s", "hello", "hello", "hello",
            "hello", "hello", "hello", "hello");
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%ls %10ls %-10ls %-3ls %.ls %.3ls %.10ls", L"hello",
                L"hello", L"hello", L"hello", L"hello", L"hello", L"hello");
    sprintf(d, "%ls %10ls %-10ls %-3ls %.ls %.3ls %.10ls", L"hello", L"hello",
            L"hello", L"hello", L"hello", L"hello", L"hello");
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%u %lu", UINT_MAX, ULONG_MAX);
    sprintf(d, "%u %lu", UINT_MAX, ULONG_MAX);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "hello %n", &n);
    sprintf(d, "hello %n", &n1);
    ck_assert_msg(c, d, "error");
    s21_sprintf(c, "%-10o %lo %lo %o %o %o %10o %#10o %0#10o", 21, lg, lg1, n,
                0, n2, 0, 21, 42);
    sprintf(d, "%-10o %lo %lo %o %o %o %10o %#10o %0#10o", 21, lg, lg1, n, 0,
            n2, 0, 21, 42);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%#o %#o %#10o %0#10o %.10o %.0o %#5.10o", n, n2, 0, 0, n, 0,
                123);
    sprintf(d, "%#o %#o %#10o %0#10o %.10o %.0o %#5.10o", n, n2, 0, 0, n, 0,
            123);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%x %x %x %10x %-10x %.10x %.0x %#5.10x", n, n1, n2, 0, 21,
                n, 0, 123);
    sprintf(d, "%x %x %x %10x %-10x %.10x %.0x %#5.10x", n, n1, n2, 0, 21, n, 0,
            123);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%#x %#x %#10x %#10x %-#10x %0#10x %0#10x %-10.5x %lx %lx",
                n, n2, 21, 0, 42, 21, 0, -65, lg, lg1);
    sprintf(d, "%#x %#x %#10x %#10x %-#10x %0#10x %0#10x %-10.5x %lx %lx", n,
            n2, 21, 0, 42, 21, 0, -65, lg, lg1);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%X %X %X %10X %-10X %lX", n, n1, n2, 0, 21, lg1);
    sprintf(d, "%X %X %X %10X %-10X %lX", n, n1, n2, 0, 21, lg1);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%#X %#X %-#10X %#10X %#10X %0#10X %0#10X", n, n2, 21, 42, 0,
                4221, n1);
    sprintf(d, "%#X %#X %-#10X %#10X %#10X %0#10X %0#10X", n, n2, 21, 42, 0,
            4221, n1);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%+.1f %.2f %.3f %.4f %10.5f %10.5f %-10.3f %-10.2f", f, f1,
                21.21, -21.21, 42.42, -42.42, f, f1);
    sprintf(d, "%+.1f %.2f %.3f %.4f %10.5f %10.5f %-10.3f %-10.2f", f, f1,
            21.21, -21.21, 42.42, -42.42, f, f1);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "% 10f % 10f %f %.0f %.0f %#.0f %.0f %f %010f", f, f1, 21.,
                21.21, 0.0, 21.21, 21., 0.0, 21.21);
    sprintf(d, "% 10f % 10f %f %.0f %.0f %#.0f %.0f %f %010f", f, f1, 21.,
            21.21, 0.0, 21.21, 21., 0.0, 21.21);
    ck_assert_str_eq(c, d);
    ck_assert_int_eq(
        s21_sprintf(c, "% 10f % 10f %f %.0f %.0f %#.0f %.0f %f %010f", f, f1,
                    21., 21.21, 0.0, 21.21, 21., 0.0, 21.21),
        sprintf(d, "% 10f % 10f %f %.0f %.0f %#.0f %.0f %f %010f", f, f1, 21.,
                21.21, 0.0, 21.21, 21., 0.0, 21.21));
    ck_assert_int_eq(
        s21_sprintf(c,
                    "%#x %#x %#10x %#10x %-#10x %0#10x %0#10x %-10.5x %lx %lx",
                    n, n2, 21, 0, 42, 21, 0, -65, lg, lg1),
        sprintf(d, "%#x %#x %#10x %#10x %-#10x %0#10x %0#10x %-10.5x %lx %lx",
                n, n2, 21, 0, 42, 21, 0, -65, lg, lg1));
}
END_TEST

START_TEST(strlen_test) {
    char len_test1[] = "1234567890";

    ck_assert_int_eq(strlen(len_test1), s21_strlen(len_test1));
    ck_assert_int_eq(strlen(""), s21_strlen(""));
}
END_TEST

START_TEST(strspn_test) {
    char spn_test1[] = "012201230010239102939939102";
    char spn_test2[] = "012";

    ck_assert_int_eq(strspn(spn_test1, spn_test2),
                     s21_strspn(spn_test1, spn_test2));
    ck_assert_int_eq(strspn("", spn_test2), s21_strspn("", spn_test2));
    ck_assert_int_eq(strspn(spn_test1, ""), s21_strspn(spn_test1, ""));
}
END_TEST

START_TEST(strcspn_test) {
    ck_assert_int_eq(strcspn("1234567890", "4567"),
                     s21_strcspn("1234567890", "4567"));
    ck_assert_int_eq(strcspn("1234567890", ""), s21_strcspn("1234567890", ""));
    ck_assert_int_eq(strcspn("", "1234567890"), s21_strcspn("", "1234567890"));
}
END_TEST

START_TEST(strcmp_test) {
    char str1[] = "abcd", str2[] = "abcd", str4[] = "efghi", str5[] = "";
    ck_assert_int_eq(s21_strcmp(str1, str2), strcmp(str1, str2));
    ck_assert_int_eq(s21_strcmp(str4, str1), strcmp(str4, str1));
    ck_assert_int_eq(s21_strcmp(str5, str1), strcmp(str5, str1));
    ck_assert_int_eq(s21_strcmp(str1, str5), strcmp(str1, str5));

    char scmp_test1[] = "asdfgh";
    char scmp_test2[] = "asdfgh";
    int res1 = strcmp(scmp_test1, scmp_test2);
    int res2 = s21_strcmp(scmp_test1, scmp_test2);
    ck_assert_int_eq(res1, res2);

    char scmp_test3[] = "qwertyuiop";
    char scmp_test4[] = "qwertyuiop";
    int res3 = strcmp(scmp_test3, scmp_test4);
    int res4 = s21_strcmp(scmp_test3, scmp_test4);
    ck_assert_int_eq(res3, res4);
}
END_TEST

START_TEST(memcmp_test) {
    char mcmp_test1[] = "Aqueris";
    char mcmp_test2[] = "Aqgoncat";

    int res1 = memcmp(mcmp_test1, mcmp_test2, 4);
    int res2 = s21_memcmp(mcmp_test1, mcmp_test2, 4);

    ck_assert_int_eq(res1, res2);

    char mcmp_test3[] = "0987654321";
    char mcmp_test4[] = "1234567890";

    int res3 = memcmp(mcmp_test3, mcmp_test4, 4);
    int res4 = s21_memcmp(mcmp_test3, mcmp_test4, 4);

    ck_assert_int_eq(res3, res4);

    char mcmp_test5[] = "";
    char mcmp_test6[] = "";

    int res5 = memcmp(mcmp_test5, mcmp_test6, 1);
    int res6 = s21_memcmp(mcmp_test5, mcmp_test6, 1);

    ck_assert_int_eq(res5, res6);
}
END_TEST

START_TEST(strncmp_test) {
    char stcmp_test1[] = "QWERTYUIO";
    char stcmp_test2[] = "QWERTYUIO";

    int res1 = strncmp(stcmp_test1, stcmp_test2, 7);
    int res2 = s21_strncmp(stcmp_test1, stcmp_test2, 7);

    ck_assert_int_eq(res1, res2);

    char stcmp_test3[] = "ASDFGHJKL";
    char stcmp_test4[] = "ASDFGHJKL";

    int res3 = strncmp(stcmp_test3, stcmp_test4, 10);
    int res4 = s21_strncmp(stcmp_test3, stcmp_test4, 10);

    ck_assert_int_eq(res3, res4);

    char stcmp_test5[] = "ASDFGHJKL";
    char stcmp_test6[] = "ASDFGHJKL";

    int res5 = strncmp(stcmp_test5, stcmp_test6, 10);
    int res6 = s21_strncmp(stcmp_test5, stcmp_test6, 10);

    ck_assert_int_eq(res5, res6);

    char stcmp_test7[] = "QWERTYUIO";
    char stcmp_test8[] = "QWERTYUIO";

    int res7 = strncmp(stcmp_test7, stcmp_test8, 0);
    int res8 = s21_strncmp(stcmp_test7, stcmp_test8, 0);

    ck_assert_int_eq(res7, res8);
}
END_TEST

START_TEST(memset_test) {
    char mset_test1[20] = "0987654321";
    char mset_test2[10] = "098765";
    char mset_test3[3];
    void *res1, *res2;

    res1 = memset(mset_test1, 'q', 17);
    res2 = s21_memset(mset_test1, 'q', 17);
    ck_assert_str_eq(res1, res2);

    res1 = memset(mset_test2, '\0', 5);
    res2 = s21_memset(mset_test2, '\0', 5);
    ck_assert_str_eq(res1, res2);

    res1 = memset(mset_test3, 'z', 3);
    res2 = s21_memset(mset_test3, 'z', 3);
    ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(memchr_test) {
    char str1[] = "Hello world!", str2[] = "";
    ck_assert_ptr_eq(s21_memchr(str1, 'w', 13), memchr(str1, 'w', 13));
    ck_assert_ptr_eq(s21_memchr(str1, ' ', 13), memchr(str1, ' ', 13));
    ck_assert_ptr_eq(s21_memchr(str1, 111, 13), memchr(str1, 111, 13));
    ck_assert_ptr_eq(s21_memchr(str2, ' ', 1), memchr(str2, ' ', 1));
    char mchr_test1[10] = "1234567890";
    char mchr_test2[5] = {'\0', '\0', '\0'};
    char mchr_test3[] = "";
    void *res1, *res2;

    res1 = memchr(mchr_test1, '4', 10);
    res2 = s21_memchr(mchr_test1, '4', 10);
    ck_assert_ptr_eq(res1, res2);

    res1 = memchr(mchr_test2, '\0', 2);
    res2 = s21_memchr(mchr_test2, '\0', 2);
    ck_assert_ptr_eq(res1, res2);

    res1 = memchr(mchr_test3, 'z', 1);
    res2 = s21_memchr(mchr_test3, 'z', 1);
    ck_assert_ptr_eq(res1, res2);
}
END_TEST

START_TEST(memcpy_test) {
    char mcp1_1[21] = "school 21";
    char mcp1_2[21] = {0};

    char mcp2_1[13] = "Valabala";
    char mcp2_2[13] = "12345";

    memcpy(mcp1_2, mcp1_1, 21);
    s21_memcpy(mcp1_2, mcp1_1, 21);
    ck_assert_str_eq(mcp1_1, mcp1_2);

    memcpy(mcp2_2, mcp2_1, 13);
    s21_memcpy(mcp2_2, mcp2_1, 13);
    ck_assert_str_eq(mcp2_1, mcp2_2);
}
END_TEST

START_TEST(memmove_test) {
    char move_test1_1[21] = "school 21";
    char move_test1_2[9] = "17263";

    char move_test2_1[13];
    char move_test2_2[6] = "123456";

    char src[10] = "1234567890";

    void *res1, *res2;

    res1 = memmove(move_test1_1, move_test1_2, 9);
    res2 = s21_memmove(move_test1_1, move_test1_2, 9);
    ck_assert_str_eq(res1, res2);

    res1 = memmove(move_test2_1, move_test2_2, 6);
    res2 = s21_memmove(move_test2_1, move_test2_2, 6);
    ck_assert_str_eq(res1, res2);

    res1 = memmove(&src[3], &src[4], 4);
    res2 = s21_memmove(&src[3], &src[4], 4);
    ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(strerror_test) {
#if defined(__APPLE__)
    for (int i = -14; i < MAX_ERROR; i++) {
        ck_assert_str_eq(strerror(i), s21_strerror(i));
    }
#elif defined(__linux__)
    for (int i = -14; i <= 150; i++) {
        ck_assert_str_eq(strerror(i), s21_strerror(i));
    }
#endif
}
END_TEST

START_TEST(strchr_test) {
    char schr_test1[] = "1234567890";
    char schr_test2[] = "0987654321";

    char *res1;
    char *res2;
    res1 = strchr(schr_test1, '5');
    res2 = s21_strchr(schr_test1, '5');
    ck_assert_str_eq(res1, res2);

    char *res3, *res4;
    res3 = strchr(schr_test2, '3');
    res4 = s21_strchr(schr_test2, '3');
    ck_assert_str_eq(res3, res4);
}
END_TEST

START_TEST(strrchr_test) {
    char str1[] = ";odsagjnpasdun 1242149215", str2[] = "";
    ck_assert_pstr_eq(s21_strrchr(str1, 'a'), strrchr(str1, 'a'));
    ck_assert_pstr_eq(s21_strrchr(str1, 100), strrchr(str1, 100));
    ck_assert_pstr_eq(s21_strrchr(str1, '/'), strrchr(str1, '/'));
    ck_assert_pstr_eq(s21_strrchr(str1, 98), strrchr(str1, 98));
    ck_assert_pstr_eq(s21_strrchr(str2, 'a'), strrchr(str2, 'a'));
    ck_assert_pstr_eq(s21_strrchr(str2, ' '), strrchr(str2, ' '));
    ck_assert_pstr_eq(s21_strrchr(str2, 56), strrchr(str2, 56));

    char schr_test1[] = "1234567890";
    char schr_test2[] = "0987654321";

    char *res1;
    char *res2;
    res1 = strrchr(schr_test1, '5');
    res2 = s21_strrchr(schr_test1, '5');
    ck_assert_str_eq(res1, res2);

    char *res3, *res4;
    res3 = strrchr(schr_test2, '3');
    res4 = s21_strrchr(schr_test2, '3');
    ck_assert_str_eq(res3, res4);
}
END_TEST

START_TEST(strcpy_test) {
    char str_test1[] = "qwertyuiop";
    char str_test1_1[] = "qwertyuiop";
    char str_test2[] = "0987";

    char str_test3[] = "312";
    char str_test3_1[] = "312";
    char str_test4[] = "1";

    char str_test5[] = "qw";
    char str_test5_1[] = "qw";
    char str_test6[] = "";

    char *res1, *res2;
    res1 = strcpy(str_test1, str_test2);
    res2 = s21_strcpy(str_test1_1, str_test2);
    ck_assert_str_eq(res1, res2);

    char *res3, *res4;
    res3 = strcpy(str_test3, str_test4);
    res4 = s21_strcpy(str_test3_1, str_test4);
    ck_assert_str_eq(res3, res4);

    char *res5, *res6;
    res5 = strcpy(str_test5, str_test6);
    res6 = s21_strcpy(str_test5_1, str_test6);
    ck_assert_str_eq(res5, res6);
}
END_TEST

START_TEST(strcat_test) {
    char scat_test1[12] = "qwerty";
    char scat_test2[12] = "er";
    char scat_test3[12] = "312";
    char scat_test4[12] = "1";
    char scat_test5[12] = "pupi";
    char scat_test6[12] = "papa";

    ck_assert_str_eq(strcat(scat_test1, scat_test2),
                     s21_strcat(scat_test1, scat_test2));
    ck_assert_str_eq(strcat(scat_test3, scat_test4),
                     s21_strcat(scat_test3, scat_test4));
    ck_assert_str_eq(strcat(scat_test5, scat_test6),
                     s21_strcat(scat_test5, scat_test6));
}
END_TEST

START_TEST(strtok_test) {
    char stok_test[] = "School-21";
    char *tok0 = strtok(stok_test, "-");
    char *tok1 = s21_strtok(stok_test, "-");
    char *tok2 = strtok(stok_test, "h");
    char *tok3 = s21_strtok(stok_test, "h");
    char *tok4 = strtok(stok_test, "o");
    char *tok5 = s21_strtok(stok_test, "o");
    char *tok6 = strtok(stok_test, "c");
    char *tok7 = s21_strtok(stok_test, "c");
    char *tok8 = strtok(stok_test, "21");
    char *tok9 = s21_strtok(stok_test, "21");
    char *tok10 = strtok(stok_test, "a");
    char *tok11 = s21_strtok(stok_test, "a");

    ck_assert_str_eq(tok0, tok1);
    ck_assert_str_eq(tok2, tok3);
    ck_assert_str_eq(tok4, tok5);
    ck_assert_str_eq(tok6, tok7);
    ck_assert_str_eq(tok8, tok9);
    ck_assert_str_eq(tok10, tok11);

    char stok_test2[] = "This is - something - terrible";
    char *token1 = strtok(stok_test2, "a");
    while (token1 != 0) {
        token1 = strtok(0, "-");
    }

    char stok_test3[] = "This is - something - terrible";
    char *token2 = strtok(stok_test3, "a");
    while (token2 != 0) {
        token2 = strtok(0, "-");
    }
    ck_assert_ptr_eq(token1, token2);
}
END_TEST

START_TEST(strpbrk_test) {
    char pbrk_test1[10] = "School 21";
    char pbrk_test2[3] = "ool";
    char pbrk_test3[2] = "21";
    char pbrk_test4[1] = "a";
    char pbrk_test5[5] = "";

    ck_assert_str_eq(strpbrk(pbrk_test1, pbrk_test2),
                     s21_strpbrk(pbrk_test1, pbrk_test2));
    ck_assert_str_eq(strpbrk(pbrk_test1, pbrk_test3),
                     s21_strpbrk(pbrk_test1, pbrk_test3));
    ck_assert_str_eq(strpbrk(pbrk_test1, pbrk_test4),
                     s21_strpbrk(pbrk_test1, pbrk_test4));
    ck_assert_pstr_eq(strpbrk(pbrk_test5, pbrk_test4),
                      s21_strpbrk(pbrk_test5, pbrk_test4));
}
END_TEST

START_TEST(strncat_test) {
    char sncat_test1[12] = "qwerty";
    char sncat_test2[12] = "er";
    char sncat_test3[12] = "312";
    char sncat_test4[12] = "1";
    char sncat_test5[12] = "pupi";
    char sncat_test6[12] = "papa";
    char sncat_test7[5] = "";

    char *res1, *res2;
    res1 = strncat(sncat_test1, sncat_test2, 1);
    res2 = s21_strncat(sncat_test1, sncat_test2, 1);
    ck_assert_str_eq(res1, res2);

    char *res3, *res4;
    res3 = strncat(sncat_test3, sncat_test4, 2);
    res4 = s21_strncat(sncat_test3, sncat_test4, 2);
    ck_assert_str_eq(res3, res4);

    char *res5, *res6;
    res5 = strncat(sncat_test5, sncat_test6, 3);
    res6 = s21_strncat(sncat_test5, sncat_test6, 3);
    ck_assert_str_eq(res5, res6);

    char *res7, *res8;
    res7 = strncat(sncat_test7, sncat_test6, 1);
    res8 = s21_strncat(sncat_test7, sncat_test6, 1);
    ck_assert_str_eq(res7, res8);
}
END_TEST

START_TEST(strncpy_test) {
    char sncpy_test1[] = "qwerty";
    char sncpy_test1_1[] = "qwerty";
    char sncpy_test2[] = "123456";
    char sncpy_test3[] = "312";
    char sncpy_test4[] = "";
    char sncpy_test4_1[] = "";

    strncpy(sncpy_test1, sncpy_test2, 3);
    s21_strncpy(sncpy_test1_1, sncpy_test2, 3);
    ck_assert_str_eq(sncpy_test1, sncpy_test1_1);

    strncpy(sncpy_test1, sncpy_test3, 2);
    s21_strncpy(sncpy_test1_1, sncpy_test3, 2);
    ck_assert_str_eq(sncpy_test1, sncpy_test1_1);

    strncpy(sncpy_test4, sncpy_test1, 0);
    s21_strncpy(sncpy_test4_1, sncpy_test1, 0);
    ck_assert_str_eq(sncpy_test4, sncpy_test4_1);
}
END_TEST

START_TEST(strstr_test) {
    char strstr_test1[12] = "qwer312ty";
    char strstr_test2[12] = "er";
    char strstr_test3[12] = "312";
    char strstr_test4[12] = "1";
    char strstr_test5[12] = "qwertyuiop";

    char *res1, *res2;
    res1 = strstr(strstr_test1, strstr_test2);
    res2 = s21_strstr(strstr_test1, strstr_test2);
    ck_assert_str_eq(res1, res2);

    char *res3, *res4;
    res3 = strstr(strstr_test1, strstr_test3);
    res4 = s21_strstr(strstr_test1, strstr_test3);
    ck_assert_str_eq(res3, res4);

    char *res5, *res6;
    res5 = strstr(strstr_test1, strstr_test4);
    res6 = s21_strstr(strstr_test1, strstr_test4);
    ck_assert_str_eq(res5, res6);

    char *res7, *res8;
    res7 = strstr(strstr_test5, strstr_test4);
    res8 = s21_strstr(strstr_test5, strstr_test4);
    ck_assert_ptr_eq(res7, res8);
}
END_TEST

Suite *main_suite(void) {
    Suite *s21_string_test = suite_create("s21_string");
    TCase *tc_core = tcase_create("Core");

    tcase_add_test(tc_core, strlen_test);
    tcase_add_test(tc_core, strspn_test);
    tcase_add_test(tc_core, strcspn_test);
    tcase_add_test(tc_core, strcmp_test);
    tcase_add_test(tc_core, memcmp_test);
    tcase_add_test(tc_core, strncmp_test);
    tcase_add_test(tc_core, memset_test);
    tcase_add_test(tc_core, memchr_test);
    tcase_add_test(tc_core, memcpy_test);
    tcase_add_test(tc_core, memmove_test);
    tcase_add_test(tc_core, strerror_test);
    tcase_add_test(tc_core, strchr_test);
    tcase_add_test(tc_core, strrchr_test);
    tcase_add_test(tc_core, strcpy_test);
    tcase_add_test(tc_core, strcat_test);
    tcase_add_test(tc_core, strtok_test);
    tcase_add_test(tc_core, strpbrk_test);
    tcase_add_test(tc_core, strncat_test);
    tcase_add_test(tc_core, strncpy_test);
    tcase_add_test(tc_core, strstr_test);
    tcase_add_test(tc_core, sprintf_test);
    tcase_add_test(tc_core, to_upper_test);
    tcase_add_test(tc_core, to_lower_test);
    tcase_add_test(tc_core, insert_test);
    tcase_add_test(tc_core, trim_test);
    tcase_add_test(tc_core, sscanf_test);

    suite_add_tcase(s21_string_test, tc_core);

    return s21_string_test;
}

int main(void) {
    int failed = 0;
    Suite *s;
    SRunner *runner;

    s = main_suite();
    runner = srunner_create(s);

    srunner_run_all(runner, CK_NORMAL);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
