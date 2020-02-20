#include <bits/stdc++.h>
#include "Polynomial.hpp"

using namespace std;

int additionCounter;
int multiplicationCounter;

int main()
{
    // Degree Input
    int n;
    printf("Input degree for P1 & P2: ");
    scanf("%d", &n);

    // Initialization 
    Polynomial P1(n);
    Polynomial P2(n);

    Polynomial P3; // Storing brute force result
    Polynomial P4; // Storing DnC result

    // Initialize seed for random coefficient generation
    srand(time(NULL));

    // Generate random coefficients for P1
    P1.generateRandom();
    printf("P1 (%d)\t: ", P1.getDegree());
    P1.printCoefficients();

    // Generate random coefficients for P2
    P2.generateRandom();
    printf("P2 (%d)\t: ", P2.getDegree());
    P2.printCoefficients();

    // Reset counter
    additionCounter = 0;
    multiplicationCounter = 0;

    // Brute force multiplication timer
    auto start1 = std::chrono::steady_clock::now();
    P3 = P1 * P2;
    auto stop1 = std::chrono::steady_clock::now();
    
    printf("P3 (%d)\t: ", P3.getDegree());
    P3.printPolynomial();

    // Output result by brute force
    printf("By Brute Force O(n^2): \n");
    // Show brute force duration in microseconds
    auto duration1  = std::chrono::duration_cast<std::chrono::microseconds>(stop1-start1);
    std::cout << '\n' << "Time taken: " << duration1.count() << " microsecond(s)\n";
    std::cout << "Addition count: " << additionCounter << " time(s)\n";
    std::cout << "Multiplication count: " << multiplicationCounter << " time(s)\n\n";

    // Reset counter
    additionCounter = 0;
    multiplicationCounter = 0;
    // Divide and conquer multiplication timer
    auto start2 = std::chrono::steady_clock::now();
    P4 = P1.multiplyDivideConquer(P2);
    auto stop2 = std::chrono::steady_clock::now();

    printf("P3 (%d)\t: ",P3.getDegree());
    P4.printPolynomial();

    // Output result by Divide and Conquer
    printf("By Divide and Conquer O(n^1.585): \n");
    // Show divide and conquer duration in microseconds
    auto duration2  = std::chrono::duration_cast<std::chrono::microseconds>(stop2-start2);
    std::cout << '\n' << "Time taken: " << duration2.count() << " microsecond(s)\n";
    std::cout << "Addition count: " << additionCounter << " times\n";
    std::cout << "Multiplication count: " << multiplicationCounter << " times\n\n";

    // Outputs verdict for checking equal result or not
    printf("VERDICT : ");
    printf(P3==P4 ? "EQUAL\n" : "NOT EQUAL\n");

}