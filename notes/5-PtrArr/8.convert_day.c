// ignore entry 0 in each row
// use 'char' since the numbers are known and small
static char daytable[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, // non-leap year
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, // leap year
};

/* helper: return 1 if year is leap year, 0 otherwise */
int is_leap(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

/* set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap;
    leap = is_leap(year);
    for (i = 1; i < month; i++)
        day += daytable[leap][i];
    return day;
}

/* set month and day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;
    leap = is_leap(year);
    for (i = 1; yearday > daytable[leap][i]; i++)
        yearday -= daytable[leap][i];
    *pmonth = i;
    *pday = yearday;
}