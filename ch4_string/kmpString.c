// 计算next数组（教材经典版）
void get_next(String T, int next[]) {
    int i = 1, j = 0;
    next[1] = 0;
    while (i < T[0]) {                 // T[0]存放串长
        if (j == 0 || T[i] == T[j]) {
            i++; j++;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
}

// KMP主函数
int Index_KMP(String S, String T, int pos, int next[]) {
    int i = pos, j = 1;
    int slen = S[0], tlen = T[0];      // S[0],T[0]存放长度
    while (i <= slen && j <= tlen) {
        if (j == 0 || S[i] == T[j]) { i++; j++; }
        else j = next[j];
    }
    if (j > tlen) return i - tlen;
    return 0;
}