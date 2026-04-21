/* return name of n-th month */
char *month_name(int n)
{
    // static array is initialized only once when the program starts
    // -> pointers to these strings remain valid
    static char *name[] = {
        "Illegal month",
        "January", "February", "March",
        "April", "May", "June",
        "July", "August", "September",
        "October", "November", "December"};

    return (n < 1 || n > 12) ? name[0] : name[n];
}