#include <string>
#include <unordered_set>
#include <iostream>
#include <ctime>
#include <chrono>

#define MAXLEN (31)
#define ARRAY_SIZE (32)

using namespace std;
class Solution {

private:
    // Max N = 10^9 -> len 31.
    int cnt[ARRAY_SIZE];
    unordered_set<std::string> substrs[ARRAY_SIZE];

public:
    /**
     * Note:
     *  First Approach. Make all the substring sets for max length.
     *  Check whether binary str of 1~N exists in set array.
     */
    // 접근은 맞았음 그러나 전부 만들 필요 없음. substring을 찾아가는 로직을 찾아보자
    Solution()
    {
        // Initialize containers
        for (int i = 0; i != ARRAY_SIZE; ++i)
        {
            cnt[i] = 0;
            substrs[i].clear();
        }
    }

public:
    inline int getNBinaryLen(int n)
    {
        int len;
        for (len = 0; n != 0; n>>=1)
        {
            len += 1;
        }
        return len;
    }

    // Maybe Change to BFS or DFS?
    inline void initializeSubstr(string s, int n)
    {
       int len = getNBinaryLen(n);
       for (int i = len; i != 0; --i)
       {
            int limit_offset = s.length() - len;
            for (int j = 0; j <= limit_offset; ++j)
            {
                substrs[i].insert(s.substr(j, i));
            }
            cnt[i] = substrs[i].size();
       }
    }

    inline string intToStr(int n)
    {
        string s = "";
        while(n != 0)
        {
            char tmp = n & 1 ? '1' : '0';
            s = tmp + s;
            n >>= 1; 
        }
        return s;
    }

public:
    bool queryString(string s, int n) {

        // Init substring collection
        initializeSubstr(s, n);

        for (int i = n; i != 0; --i)
        {
            string target = intToStr(i);
            int len = target.length();
            if (substrs[len].count(target) == 0)
            {
                return false;
            }
        } 
        return true;
    }
public:
    void printSubstrSet(void)
    {
        for(int i = MAXLEN; i != 0; --i)
        {
            if (cnt[i] != 0)
            {
                cout << "[" << i << "]: "; 
                for (auto iter : substrs[i])
                {
                    cout << iter << " ";
                }
                cout << endl;
            }
        }
    }
};

int main(void)
{

    Solution sol;
    int n = pow(10, 9);
    int length = 1000;

    std::srand(std::time(0));
    string str = "";
    for (int i = 0; i < length; ++i) {
        char random_char = '0' + (std::rand() % 2); // '0' 또는 '1' 생성
        str += random_char;
    }

    auto start_time = std::chrono::high_resolution_clock::now();
    sol.queryString(str, n);
    auto end_time = std::chrono::high_resolution_clock::now();

    // 실행 시간 계산 (밀리초 단위)
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "실행 시간: " << duration_ms.count() << " ms" << std::endl;

    return 0;
}
