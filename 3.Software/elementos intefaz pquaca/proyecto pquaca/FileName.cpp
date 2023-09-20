#include <iostream>

int main() {
    double x_value;
    std::cout << "Ingrese el valor de x: ";
    std::cin >> x_value;

    double result = 3 + 2 * x_value;
    std::cout << "El valor de la derivada en x = " << x_value << " es: " << result << std::endl;

    return 0;
}
