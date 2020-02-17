#ifndef __POLYNOMIAL_HPP__
#define __POLYNOMIAL_HPP__

#include<bits/stdc++.h>

using namespace std;

class Polynomial {
private:
    int degree;
    float* coef;

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
    float getCoef(int n);
    // Set degree of the polynomial
    int setDegree(int n);
    // Set coeffcient of the term with the power of n
    void setCoef(float x, int n);

    // + operator
    Polynomial operator+(const Polynomial& other);
    // - operator
    Polynomial operator-(const Polynomial& other);
    
    // Multiply two polynomials in a brute force manner. O(N^2)
    Polynomial multiplyBruteForce(const Polynomial& other);
    // Multiply two polynomials in a divide and conquer manner. O(N^1.585)
    Polynomial multiplyDivideConquer(const Polynomial& other);

    // Procedure to output polynomials
    void printPolynomial();
    // Procedure to take input for polynomials
    void inputPolynomial();
};

#endif