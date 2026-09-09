int RomanToDecimal(const std::string& roman) {
    std::unordered_map<char, int> values = {
        {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
        {'C', 100}, {'D', 500}, {'M', 1000}
    };
    int result = 0;
    int n = roman.size();
    for (int i = 0; i < n; ++i) {
        int value = values[roman[i]];
        if (i + 1 < n && values[roman[i+1]] > value) {
            result -= value;
        } else {
            result += value;
        }
    }
    return result;
}

string DecimalToRoman(int num) {
    if (num <= 0 || num > 3999)
        throw invalid_argument("num must be in 1..3999");

    static const pair<int, const char*> map[] = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
        {100,  "C"}, {90,  "XC"}, {50,  "L"}, {40,  "XL"},
        {10,   "X"}, {9,   "IX"}, {5,   "V"}, {4,   "IV"},
        {1,    "I"}
    };

    string out;
    for (auto [val, sym] : map) {
        while (num >= val) {
            out += sym;
            num -= val;
        }
    }
    return out;
}
