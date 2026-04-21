void swap(int *px, int *py)
{
    int temp;
    temp = *px;
    *px = *py;
    *py = temp;
}

int main()
{
    int x, y;
    x = 0;
    y = 1;
    swap(&x, &y);
}