


int get_clz(int n) {
    if (n == 0) return 32;
    return __builtin_clz(n);

    //int cnt = 0;
    //
    //while (n) {
    //    n >>= 1;
    //    ++cnt;
    //}
    //return 32 - cnt;
}


bool queryString(char* s, int n) {

    /*
    
     2048 = 2^12 = 0b 1000 0000 0000
     2027 = 0b 0111 1111 1111 
     1024 = 0b 0100 0000 0000

     2027 - 1024 > 1000 �̰�, ���ڿ� �ϳ� �߰� ��ĵ�Ҷ����� �Ź� �޶� �� ä��� ���� ������. (len(s) <= 1000)
     
    */
    if (n >= 2047) { //
        return 0;
    }
    while (*(s) == '0') ++s;
    if (*s == 0) return 0;


    /*

    (1) ���� n�� 0b 1xxx xxxx xxxx �϶�. 0b 1000 0000 0000 ~ n ������ Ž���ؾ���.

    (2) 0b 100 0000 0000 ~ 0b 111 1111 1111 ������ ��� �ִٸ� "0b 100 0000 0000" �Ʒ� ������ �ش� ������ subset��. 

    (3) (2)�� Ž���Ҷ� (1)�� 0b xxx xxxx xxxxx (n�� MSB�� 0���� ����ŷ)�� 0b 1xx xxxx xxxx (n >> 1) �� �߿� ū �� ������ (1)���� ������ ���� subset�̹Ƿ� Ž�� x

    ** MSB (Most Significant Bit) : �ֻ��� 1�� ��ġ.
    ** CLZ (Count Leading Zero) : MSB���� ���� 0�� ���ڸ� ī��Ʈ (get_clz(1) = 31, get_clz(2) = 30)

    */


    //0b 0000 0000, 0000 0000, 0000 1xxx, xxxx xxxx // 32 Bit n
    int clz = get_clz(n);
    int min0 = 1 << (32 - clz - 1); // get_clz(n) = 20, min0 = 0b 1000 0000 0000

    int dp[2048] = { 0 };



    int start_int = (n >> 1) > (n & (~min0)) ? (n >> 1) : (n & (~min0)); // max ((n�� MSB�� 0���� ����ŷ) , (n >> 1) )
    int cnt = 0;
    int target_cnt = n - start_int;


    ++start_int;

    int k = 0;
    if (start_int == min0) { // start_int�� �ڸ����� ���� (111111 ���̽�)

        int binary_digit = 32 - clz;
        int mask = ~(min0 << 1);
        for (int i = 0; i < binary_digit; i++) {
            if (*s == 0)
                return 0;
            k <<= 1;
            k += *(s++) == '1' ? 1 : 0;
        }

        while (1) {
            if (k >= start_int && k <= n && dp[k] == 0) {
                ++cnt;
                dp[k] = 1;
            }
            if (cnt == target_cnt) {
                return 1;
            }
            if (*s == 0)
                return 0;
            k <<= 1;
            k += *(s++) == '1' ? 1 : 0;
            k &= mask;
        }

    }
    else {

        int binary_digit = 32 - clz - 1;
        int mask = ~min0;
        for (int i = 0; i < binary_digit; i++) {
            if (*s == 0)
                return 0;
            k <<= 1;
            k += *(s++) == '1' ? 1 : 0;
        }

        if (*s == 0)
            return 0;
        while (1) {
            if (k >= start_int && k <= n && dp[k] == 0) {
                ++cnt;
                dp[k] = 1;
            }
            k <<= 1;
            k += *(s++) == '1' ? 1 : 0;
            if (k >= start_int && k <= n && dp[k] == 0) {
                ++cnt;
                dp[k] = 1;
            }
            if (cnt == target_cnt) {
                return 1;
            }
            if (*s == 0)
                return 0;
            k &= mask;
        }


    }

}
