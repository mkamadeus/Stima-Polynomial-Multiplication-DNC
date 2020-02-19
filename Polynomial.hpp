#ifndef __POLYNOMIAL_HPP__
#define __POLYNOMIAL_HPP__

#include<bits/stdc++.h>

using namespace std;

class Polynomial {
private:
    int degree;
    int* coef;

public:
    // Default ctor
    Polynomial();
    // ctor
    Polynomial(int degree);
    // cctor
    Polynomial(const Polynomial& other);
    // Assignment operator
    Polynomial& operator=(const Polynomial& other);
    // Destructor
    ~Polynomial();

    // Get degree of the polynomial
    int getDegree();
    // Get coefficient of the term with the power of n
    int getCoef(int n);
    // Set degree of the polynomial (increasing only)
    void setDegree(int n);
    // Set coeffcient of the term with the power of n
    void setCoef(int x, int n);

    // + operator
    Polynomial operator+(const Polynomial& other);
    // - operator
    Polynomial operator-(const Polynomial& other);
    // Multiply two polynomials in a brute force manner. O(N^2)
    Polynomial operator*(const Polynomial& other);
    // Compare two polynomials
    bool operator==(const Polynomial& other);
    // Multiply polynomial by a factor of x
    Polynomial operator<<(int n);
    // Divide polynomial by a factor of x (remove constants)
    Polynomial operator>>(int n);

    // Multiply two polynomials in a brute force manner. O(N^2)
    Polynomial multiplyBruteForce(const Polynomial& other);
    // Multiply two polynomials in a divide and conquer manner. O(N^1.585)
    Polynomial multiplyDivideConquer(const Polynomial& other);


    // Procedure to output polynomials
    void printPolynomial();
    // Procedure to output polynomials by coefficients only
    void printCoefficients();
    // Procedure to take input for polynomials
    void inputPolynomial();
    // Procedure to generate random coefficients
    void generateRandom();
};

#endif