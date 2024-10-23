void sort(int array[], int dim) {
    for (int i = 0; i < dim - 1; ++i)
        for (int j = 0; j < dim - 1 - i; ++j)
            if (array[j] > array[j + 1])
                swap(&array[j], &array[j + 1]);
}
