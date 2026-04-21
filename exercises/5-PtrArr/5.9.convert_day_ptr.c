/*
- use pointers instead of array indexing
*/

#include <stdio.h>

// ignore entry 0 in each row
static int daytable[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, // non-leap year
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, // leap year
};

/* helper: return 1 if year is leap year, 0 otherwise */
int is_leap(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

/* set day of year from month & day; return -1 if input is invalid */
int day_of_year(int year, int month, int day)
{
    int leap;
    int *p;

    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
    {
        printf("Invalid input (Y-m-d): %d-%d-%d\n", year, month, day);
        return -1;
    }

    leap = is_leap(year);
    p = daytable[leap];

    if (day > *(p + month))
    {
        printf("Invalid input (Y-m-d): %d-%d-%d\n", year, month, day);
        return -1;
    }

    while (--month > 0)
        day += *(++p);
    return day;
}

void test_day_of_year(int year, int month, int day, int expected)
{
    int result = day_of_year(year, month, day);
    if (result != expected)
        printf("(day_of_year) Expected: %d. Actual: %d.\n", expected, result);
}

/* set month and day from day of year;
return -1 if input is invalid, 0 otherwise */
int month_day(int year, int yearday, int *pmonth, int *pday)
{
    int leap;
    int *p;

    if (year < 0 || yearday < 0 || yearday > 366)
    {
        printf("Invalid input (year, yearday): %d-%d\n", year, yearday);
        return -1;
    }

    leap = is_leap(year);
    int maxday = leap ? 366 : 365;
    if (yearday > maxday)
    {
        printf("Invalid input (year, yearday): %d-%d\n", year, yearday);
        return -1;
    }

    p = daytable[leap];
    while (yearday > *p)
        yearday -= *(p++);

    *pmonth = p - daytable[leap];
    *pday = yearday;
    return 0;
}

void test_month_day(
    int year, int yearday, int *pmonth, int *pday,
    int expected_month, int expected_day)
{
    *pmonth = *pday = -1;
    month_day(year, yearday, pmonth, pday);
    if (*pmonth != expected_month || *pday != expected_day)
        printf("(month_day) Expected (m-d): %d-%d. Actual: %d-%d.\n",
               expected_month, expected_day, *pmonth, *pday);
}

int main()
{
    printf("==== test_day_of_year =====\n");
    test_day_of_year(2000, 2, 29, 60);
    test_day_of_year(2001, 2, 28, 59);
    test_day_of_year(2001, 2, 29, -1);
    test_day_of_year(-2001, 2, 28, -1);
    test_day_of_year(2001, -2, 28, -1);
    test_day_of_year(2001, 2, -28, -1);
    test_day_of_year(2001, 13, 28, -1);
    // ... more

    printf("==== test_month_day =====\n");
    int pmonth, pday;
    test_month_day(2000, 60, &pmonth, &pday, 2, 29);
    test_month_day(2001, 59, &pmonth, &pday, 2, 28);
    test_month_day(-2001, 59, &pmonth, &pday, -1, -1);
    test_month_day(2001, -59, &pmonth, &pday, -1, -1);
    test_month_day(2000, 366, &pmonth, &pday, 12, 31);
    test_month_day(2001, 366, &pmonth, &pday, -1, -1);
    // ... more
}