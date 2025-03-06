#include <iostream>

int main() {
    float monkey1, monkey2, product;

    // Prompt for the first number
    do {
        std::cout << "Pick a number from 1-10: "; 
        std::cin >> monkey1;
        
        if (monkey1 > 10 || monkey1 < 1) {
            std::cout << "Invalid input. Try again.\n";
        }
    } while (monkey1 > 10 || monkey1 < 1);

    // Prompt for the second number
    do {
        std::cout << "Pick a number from 1-100: ";
        std::cin >> monkey2;

        if (monkey2 > 100 || monkey2 < 1) {
            std::cout << "Invalid input. Try again.\n";
        }
    } while (monkey2 > 100 || monkey2 < 1);

    // Calculate and display the product
    product = monkey1 * monkey2;
    std::cout << "Your IQ is the following: " << product << std::endl;

    return 0;
}
