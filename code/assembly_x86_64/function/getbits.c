unsigned long getbits(unsigned long x, int p, int n) {
    return (x >> p) & ((1L << n) - 1);
}
