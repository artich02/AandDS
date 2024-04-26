#include <iostream>
#include <string>
#include <cmath>

class Polynom {
private:
    int degree; //степень
    double* coefficients; //коэффициенты

public:
    Polynom() : degree(0), coefficients(nullptr) {}

    Polynom(int deg, const double* coeffs) : degree(deg) {
        coefficients = new double[deg + 1];
        for (int i = 0; i <= deg; ++i) {
            coefficients[i] = coeffs[i];
        }
    }

    Polynom(const Polynom& other) : degree(other.degree) {
        coefficients = new double[degree + 1];
        for (int i = 0; i <= degree; ++i) {
            coefficients[i] = other.coefficients[i];
        }
    }

    ~Polynom() {
        delete[] coefficients;
    }

    double evaluate(double x) const {
        double result = 0.0;
        for (int i = 0; i <= degree; ++i) {
            result += coefficients[i] * pow(x, i);
        }
        return result;
    }

    Polynom& operator=(const Polynom& other) {
        if (this != &other) {
            delete[] coefficients;
            degree = other.degree;
            coefficients = new double[degree + 1];
            for (int i = 0; i <= degree; ++i) {
                coefficients[i] = other.coefficients[i];
            }
        }
        return *this;
    }

    Polynom& operator+=(const Polynom& other) {
        int newDegree = std::max(degree, other.degree);
        double* newCoefficients = new double[newDegree + 1];
        for (int i = 0; i <= newDegree; ++i) {
            newCoefficients[i] = (i <= degree ? coefficients[i] : 0.0) +
                (i <= other.degree ? other.coefficients[i] : 0.0);
        }
        delete[] coefficients;
        degree = newDegree;
        coefficients = newCoefficients;
        return *this;
    }

    Polynom& operator-=(const Polynom& other) {
        int newDegree = std::max(degree, other.degree);
        double* newCoefficients = new double[newDegree + 1];
        for (int i = 0; i <= newDegree; ++i) {
            newCoefficients[i] = (i <= degree ? coefficients[i] : 0.0) -
                (i <= other.degree ? other.coefficients[i] : 0.0);
        }
        delete[] coefficients;
        degree = newDegree;
        coefficients = newCoefficients;
        return *this;
    }

    Polynom& operator*=(const Polynom& other) {
        int newDegree = degree + other.degree;
        double* newCoefficients = new double[newDegree + 1];
        for (int i = 0; i <= newDegree; ++i) {
            newCoefficients[i] = 0.0;
            for (int j = 0; j <= i; ++j) {
                if (j <= degree && (i - j) <= other.degree) {
                    newCoefficients[i] += coefficients[j] * other.coefficients[i - j];
                }
            }
        }
        delete[] coefficients;
        degree = newDegree;
        coefficients = newCoefficients;
        return *this;
    }

    // Перегрузка операторов сложения, вычитания и умножения
    Polynom operator+(const Polynom& other) const {
        Polynom result(*this);
        result += other;
        return result;
    }

    Polynom operator-(const Polynom& other) const {
        Polynom result(*this);
        result -= other;
        return result;
    }

    Polynom operator*(const Polynom& other) const {
        Polynom result(*this);
        result *= other;
        return result;
    }

    // Метод для вывода полинома
    void print() const {
        for (int i = degree; i >= 0; --i) {
            std::cout << coefficients[i];
            if (i > 0) {
                std::cout << "x^" << i << " + ";
            }
            else {
                std::cout << std::endl;
            }
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    double coeffs1[] = { 3, 2, 1 }; // 3x^2 + 2x + 1
    double coeffs2[] = { 5, 4 };  

    Polynom poly1(2, coeffs1);
    Polynom poly2(1, coeffs2);

    // Примеры использования
    Polynom sum = poly1 + poly2;
    Polynom diff = poly1 - poly2;
    Polynom product = poly1 * poly2;

    std::cout << "1) ";
    poly1.print();

    std::cout << "2) ";
    poly2.print();

    std::cout << "Сумма: ";
    sum.print();

    std::cout << "Вычетание: ";
    diff.print();

    std::cout << "Умножение: ";
    product.print();

    return 0;
}