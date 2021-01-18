// https://www.hackerrank.com/challenges/insertion-sort/problem
#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the insertionSort function below.
using Index = ptrdiff_t;

template <typename T>
class BinIndexTree {
public:
    using index = ptrdiff_t;
    BinIndexTree(index size)
        : _data(size + 1)
    { }

    T prefix_query(index idx) const noexcept {
        T result{};
        for (; idx > 0; idx -= idx & (-idx))
            result += _data[idx];
        return result;
    }

    void update(index idx, T const add) {
        assert(idx);
        auto const sz = (index)_data.size();
        for (; idx < sz; idx += idx & (-idx))
            _data[idx] += add;
    }

private:
    std::vector<T> _data;
};

using iarr = std::vector<int>;

int coordinate_compression(iarr& arr) {
    int max_elm = 1;
    std::unordered_map<int, int> ranks;
    auto copy = arr;
    std::sort(copy.begin(), copy.end());
    int prev = arr[0];
    ranks[prev] = max_elm++;
    for (auto elm : copy)
        if (elm != prev)
            ranks[prev = elm] = max_elm++;
    for (auto& elm : arr)
        elm = ranks[elm];
    return max_elm - 1;
}


Index insertionSort(iarr& arr) {
    int const max_elm = coordinate_compression(arr);

    BinIndexTree<int> bts(max_elm);

    Index res = 0;

    for (Index i = (Index)arr.size() - 1; i > -1; --i) {
        res += bts.prefix_query((Index)arr[i] - 1);
        bts.update(arr[i], 1);
    }

    return res;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string arr_temp_temp;
        getline(cin, arr_temp_temp);

        vector<string> arr_temp = split_string(arr_temp_temp);

        vector<int> arr(n);

        for (int i = 0; i < n; i++) {
            int arr_item = stoi(arr_temp[i]);

            arr[i] = arr_item;
        }

        int result = insertionSort(arr);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
