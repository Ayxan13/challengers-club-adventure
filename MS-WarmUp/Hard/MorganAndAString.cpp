// https://www.hackerrank.com/challenges/morgan-and-a-string/problem
#include <bits/stdc++.h>

using namespace std;

// Complete the morganAndString function below.
string morganAndString(string& a, string& b) {
    char constexpr sentinel = 'Z' + 1;
    std::string res; // result
    res.reserve(a.size() + b.size()); // pre-allocate
    a += sentinel;
    b += sentinel;

    auto pa = a.c_str();
    auto pb = b.c_str();

    while (*pa != sentinel && *pb != sentinel) {
        if (strcmp(pa, pb) < 0) res += *pa++;
        else res += *pb++;
    }

    res.append(pa, &a.back() - pa);
    res.append(pb, &b.back() - pb);
    return res;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string a;
        getline(cin, a);

        string b;
        getline(cin, b);

        string result = morganAndString(a, b);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}
