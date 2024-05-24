#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// ��������� ���������� �������� ������� n
std::vector<int> generateRandomPolynomial(int n) {
    std::vector<int> polynomial(n + 1); // ������ ��� �������� ������������� ��������

    // ��������� ��������� �������������
    for (int i = 0; i <= n; i++) {
        polynomial[i] = std::rand() % 10; // ��������� ���������� ������������ �� 0 �� 9
    }

    return polynomial;
}
std::vector<int> generateRandomPolynomial(int n) {
    std::vector<int> degrees(n + 1); // ������ ��� �������� ������������� ��������

    // ��������� ��������� �������������
    for (int i = 0; i <= n; i++) {
        degrees[i] = std::rand() % 10; // ��������� ���������� ������������ �� 0 �� 9
    }

    return degrees;
}

int main() {
    // ������������� ��������� ��������� ��������
    std::srand(std::time(nullptr));

    int degree = 3; // ������� ��������
    std::vector<int> randomPolynomial = generateRandomPolynomial(degree);

    // ����� ���������������� ��������
    std::cout << "��������������� ������� ������� " << degree << ": ";
    for (int i = 0; i <= degree; i++) {
        std::cout << randomPolynomial[i] << "x^" << i;
        if (i < degree) {
            std::cout << " + ";
        }
    }
    std::cout << std::endl;

    return 0;
}