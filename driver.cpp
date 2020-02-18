#include <bits/stdc++.h>
#include "Polynomial.hpp"

using namespace std;

int main()
{
    Polynomial P1(5);
    Polynomial P2(5);

    P1.inputPolynomial();
    P2.inputPolynomial();

    P1.printPolynomial();
    P2.printPolynomial();

    Polynomial P3 = P1.multiplyBruteForce(P2);
    P3.printPolynomial();

    Polynomial P3Other = P1.multiplyDivideConquer(P2);
    P3Other.printPolynomial();

    // Polynomial P4 = P1+P2;
    // P4.printPolynomial();

    // Polynomial P5 = P1-P2;
    // P5.printPolynomial();

    // Polynomial P6 = P1.multiplyDivideConquer(P2);
    // P6.printPolynomial();

}