/* helper: interchange v[i] and v[j] */
void swap(int v[], int i, int j)
{
    int temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* sort v[] into increasing order */
void qsort(int v[], int left, int right)
{
    int i, last;

    // do nothing if array has less than 2 elements
    if (left >= right)
        return;

    // move partition elem to v[left]
    swap(v, left, (left + right) / 2);
    last = left;

    // partition
    for (i = left + 1; i <= right; i++)
        if (v[i] < v[left])
            swap(v, ++last, i);

    // restore partition elem
    swap(v, left, last);

    // sort the 2 partitions
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}
