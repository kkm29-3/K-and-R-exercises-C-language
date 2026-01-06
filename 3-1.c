int binsearch(int x, int v[], int n) {
    int low = 0;
    int high = n - 1;
    int mid;

    while (low <= high) {                 /* single test in loop */
        mid = (low + high) / 2;

        if (x <= v[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }

    /* when loop ends, low is the least index with v[low] >= x (or n) */
    if (low < n && v[low] == x)
        return low;                       /* found */
    else
        return -1;                        /* not found */
}

