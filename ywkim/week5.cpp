int numberOfSubstrings(char* s, int k) {
    int num[256] = {0};
    int i = 0, j = 0;
    char *ps = s - 1;
    int sum = 0;
    while(*++ps){
        ++num[*ps];
        while (num[*ps] >= k){
            --num[*(s + i++)];
        }
        sum -= j++ - i + 1;
    }
    return sum + (ps - s + 1) * (ps - s) / 2;
}
