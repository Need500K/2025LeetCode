#include <stdbool.h>
#include <stdio.h>

// Max Num = 10^9
// Max Binary Len = 30
char maxStr[30];

static inline int updateBinStr(int n)
{
    // int n is 32 bit.
    int len = 32 - __builtin_clz(n);
    
    // From the back
    int idx = len-1;
    while(n != 0)
    { 
        maxStr[idx--] = (n & 1) == 0 ? '0' : '1';
        n >>= 1;
    } 
    return len;
}

static inline bool checkSubstr(const char* s, int len)
{
    for(int i = 0; i < len; ++i)
    {
        if(s[i] != maxStr[i])
            return false;
    }
    return true;
}

static inline void printBinStr(int len)
{
    for(int i = 0; i < len; ++i)
    {
        printf("%c", maxStr[i]);
    }
    printf("\n");
}

bool queryString(char* s, int n) {

    int len = 0;
    for (int i = n; i != 0; --i)
    {
        len = updateBinStr(i);

        // Check substr
        for(unsigned int j = 0; j < 1000; ++j)
        {
            // out of char s* range. which means no corresponding substr in S*
            if (s[j] != '1' && s[j] != '0')
            {
                return false;
            }

            bool isSubstr = checkSubstr(&s[j], len); // or use s+j for address calculation

            // Early stop if we found target
            if (isSubstr)
                break;
        }
    }
    return true;
}

int main(void)
{
   char a[4] = "0110";
   int n = 4;
   bool ans = queryString(a, n);
   printf("%d\n", ans);
}
