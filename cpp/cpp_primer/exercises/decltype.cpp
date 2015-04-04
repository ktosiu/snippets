int main() {
    const int ci = 0;
    const int& cj = ci;

    decltype(ci) x = 0;
    decltype(cj) y = x;
    // Error: decltype(cj) z;
    return 0;
}
