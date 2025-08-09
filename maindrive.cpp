#include <bits/stdc++.h>
#include "json.hpp" // JSON library

using namespace std;
using json = nlohmann::json;

// Function to decode Y value from given base
long long decodeY(const string &y, int base) {
    long long val = 0;
    for (char c : y) {
        val = val * base + (c - '0');
    }
    return val;
}

int main() {
    // Open JSON file
    ifstream file("testcase.json");
    if (!file.is_open()) {
        cerr << "Error: Could not open testcase.json\n";
        return 1;
    }

    // Parse JSON
    json j;
    file >> j;

    int n = j["n"];
    int k = j["k"];
    vector<long long> x_vals;
    vector<long long> y_vals;

    // Read and decode roots
    for (auto &root : j["roots"]) {
        int base = root["base"];
        long long x = root["x"];
        string y_enc = root["y"];

        long long y_dec = decodeY(y_enc, base);
        x_vals.push_back(x);
        y_vals.push_back(y_dec);
    }

    // Only take first k points for polynomial interpolation
    x_vals.resize(k);
    y_vals.resize(k);

    // Lagrange interpolation to find constant term (x = 0)
    double C = 0;
    for (int j = 0; j < k; j++) {
        double term = y_vals[j];
        for (int i = 0; i < k; i++) {
            if (i != j) {
                term *= (0 - x_vals[i]) * 1.0 / (x_vals[j] - x_vals[i]);
            }
        }
        C += term;
    }

    cout << "Secret C = " << llround(C) << endl;
    return 0;
}
