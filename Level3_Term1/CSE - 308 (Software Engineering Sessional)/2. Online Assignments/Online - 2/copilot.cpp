#include <iostream>
#include <unordered_set>

bool isHappy(int n) {
    std::unordered_set<int> seen;
    while (n != 1 && seen.find(n) == seen.end()) {
        seen.insert(n);
        int sum = 0;
        while (n > 0) {
            int digit = n % 10;
            sum += digit * digit;
            n /= 10;
        }
        n = sum;
    }
    return n == 1;
}

int main() {
    int num;
    std::cout << "Enter a number: ";
    std::cin >> num;
    if (isHappy(num)) {
        std::cout << num << " is a happy number." << std::endl;
    } else {
        std::cout << num << " is not a happy number." << std::endl;
    }
    return 0;
}
