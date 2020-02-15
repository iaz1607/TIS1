#include "iostream"
#include "vector"
#include "algorithm"

using namespace std;

/*
 * Данная функция работает рекурсивно, на каждом шаге ей подается диапазон, для которого необходимо вывести
 * палиндром. С помощью массива dp определяется, следующий максимальный подотрезок, для которого необходимо вывести
 * палиндром.
 */
string restore_palindrome(const vector<vector<int>> &dp, const string &st, int l, int r) {
    string res;
    if (l > r) {
        res = "";
    } else if (l == r) {
        res = st[l];
    } else {
        int left = dp[l][r - 1];
        int right = dp[l + 1][r];
        int mid = dp[l + 1][r - 1] + 2 * (st[l] == st[r]);
        if (left >= right && left >= mid) {
            res = restore_palindrome(dp, st, l, r - 1);
        } else if (right >= mid && right >= left) {
            res = restore_palindrome(dp, st, l + 1, r);
        } else {
            res = st[l] + restore_palindrome(dp, st, l + 1, r - 1) + st[r];
        }
    }
    return res;
}
/*
 * Решаем данную задачу с помощью динамического программирования "снизу вверх",
 * сначала считаем ответ для всех подстрок длины 1, затем для подстрок длины 2
 * и т.д.
 * в dp[i][j] храним длину максимальной подпоследовательности, являющейся палиндромом для подстроки
 * st[i..j]. 
 * Допустим мы хотим посчитать dp[i][j]. заметим, что максимальная подпоследовательность-палиндром на этой
 * подстроке может находиться либо целиком в st[i + 1..j],
 * либо целиком в st[i..j - 1], 
 * либо(если предыдущие два утверждения не верны) в st[i..j], но тогда st[i] и st[j] принадлежат палиндрому
 * и нам достаточно знать st[i + 1..j - 1]. т.о.
 * dp[i][j] = max(dp[i + 1][j], dp[i][j - 1], dp[i + 1][j - 1] + 2 * (st[i] == st[j]))
 * т.к. dp для всех подстрок меньшей длины уже было посчитано, то подсчет каждого dp[i][j] будет работать за O(1)
 * итоговая сложность: O(n^2), где - длина строки.
 * Восстанавливаем ответ с помощью restore_palindrome
 */
string get_longest_palindrome(const string &st) {
    vector<vector<int>> dp(st.size(), vector<int>(st.size(), 0));
    for (int i = 0; i < st.size(); ++i) {
        dp[i][i] = 1;
    }
    for (int len = 1; len < st.size(); ++len) {
        for (int i = 0; i + len < st.size(); ++i) {
            dp[i][i + len] = max(dp[i + 1][i + len], dp[i][i + len - 1]);
            if (st[i] == st[i + len]) {
                dp[i][i + len] = max(dp[i][i + len], 2 + dp[i + 1][i + len - 1]);
            }
        }
    }

    return restore_palindrome(dp, st, 0, st.size() - 1);
}

int main() {
    cout << get_longest_palindrome("abacabadabacaba") << '\n';
    cout << get_longest_palindrome("aaaaaaa") << '\n';
    cout << get_longest_palindrome("a") << '\n';
    cout << get_longest_palindrome("colya") << '\n';
    cout << get_longest_palindrome("sasha") << '\n';
    cout << get_longest_palindrome("margarita") << '\n';
    cout << get_longest_palindrome("ilyasha") << '\n';
    cout << get_longest_palindrome("crystynyna") << '\n';
    cout << get_longest_palindrome("aa") << '\n';
    cout << get_longest_palindrome("gsafdsafagsflkjgfdshgkjdsfhgdsfjssadgjhfsghfdjgshsadjfhskfjhsf") << '\n';
    cout << get_longest_palindrome("ahdsjhfshdjfhdjfhjdshfjadshfsahfdljksahfdsahflsahfkjsahfjsdhf") << '\n';
    return 0;
}
