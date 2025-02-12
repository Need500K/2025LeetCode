/**
Problem:

Given a string s and an integer k, return the total number of substrings
of s where at least one character appears at least k times.
*/
/*
Example

Input: s = "abacb", k = 2
Output: 4

Explanation:
The valid substrings are:

"aba" (character 'a' appears 2 times).
"abac" (character 'a' appears 2 times).
"abacb" (character 'a' appears 2 times).
"bacb" (character 'b' appears 2 times).
*/

/*
Constraints

- 1 <= s.length <= 3000
- 1 <= k <= s.length
- s consists only of lowercase English letters.
*/
#include <stdio.h>
// To use character index
#define INDEX(x) (x-'a')

int numberOfSubstrings(char* s, int k) {
    int length = 0;
    char* strPtr = s;

    int charCnt[26] = {0, };

    while((*strPtr) != NULL)
    {
        length++; strPtr++;
    }

    if (k == 1)
    {
        // All substring
        return length * (length + 1) / 2;
    }

    int result = 0;
    int tmp_len = 0;
    int cnt[26] = {0, };
    for (int i = 0; i < length; ++i) {
        ++cnt[INDEX(s[i])];
        while (cnt[INDEX(s[i])] >= k) {
            --cnt[INDEX(s[tmp_len++])];
        }
        result += tmp_len;
    }
    return result;
}

int main() {
    char s[] = "abacb";
    int k = 2;
    printf("Number of substrings: %d\n", numberOfSubstrings(s, k));
    return 0;
}
