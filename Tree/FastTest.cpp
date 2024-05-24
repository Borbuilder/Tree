#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Генерация случайного полинома степени n
std::vector<int> generateRandomPolynomial(int n) {
    std::vector<int> polynomial(n + 1); // Вектор для хранения коэффициентов полинома

    // Генерация случайных коэффициентов
    for (int i = 0; i <= n; i++) {
        polynomial[i] = std::rand() % 10; // Генерация случайного коэффициента от 0 до 9
    }

    return polynomial;
}
std::vector<int> generateRandomPolynomial(int n) {
    std::vector<int> degrees(n + 1); // Вектор для хранения коэффициентов полинома

    // Генерация случайных коэффициентов
    for (int i = 0; i <= n; i++) {
        degrees[i] = std::rand() % 10; // Генерация случайного коэффициента от 0 до 9
    }

    return degrees;
}

int main() {
    // Устанавливаем случайное начальное значение
    std::srand(std::time(nullptr));

    int degree = 3; // Степень полинома
    std::vector<int> randomPolynomial = generateRandomPolynomial(degree);

    // Вывод сгенерированного полинома
    std::cout << "Сгенерированный полином степени " << degree << ": ";
    for (int i = 0; i <= degree; i++) {
        std::cout << randomPolynomial[i] << "x^" << i;
        if (i < degree) {
            std::cout << " + ";
        }
    }
    std::cout << std::endl;

    return 0;
}