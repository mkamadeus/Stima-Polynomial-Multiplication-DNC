#include "Polynomial.hpp"

// Default ctor
Polynomial::Polynomial()
{
    this->degree = 10;
    this->coef = new float[11];
    memset(this->coef, 0, sizeof(this->coef));
}

// ctor
Polynomial::Polynomial(int degree)
{
    this->degree = degree;
    this->coef = new float[degree+1];
    memset(this->coef, 0, sizeof(this->coef));
}
// cctor
Polynomial::Polynomial(const Polynomial& other)
{
    this->degree = other.degree;
    this->coef = new float[other.degree+1];
    for(int i=0;i<=this->degree;i++) this->coef[i] = other.coef[i];
}
// Assignment operator
Polynomial& Polynomial::operator=(const Polynomial& other)
{
    this->degree = other.degree;
    this->coef = new float[other.degree+1];
    for(int i=0;i<=this->degree;i++) this->coef[i] = other.coef[i];

    return *this;
}

// Destructor
Polynomial::~Polynomial()
{
    delete this->coef;
}

// Get degree of the polynomial
int Polynomial::getDegree()
{
    return this->degree;
}

// Get coefficient of the term with the power of n
float Polynomial::getCoef(int n)
{
    return this->coef[n];
}

// Set degree of the polynomial
int Polynomial::setDegree(int n)
{
    int prev = this->degree;
    this->degree = n;
}

// Set coeffcient of the term with the power of n
void Polynomial::setCoef(float x, int n)
{
    this->coef[n] = x;
}

// + operator
Polynomial Polynomial::operator+(const Polynomial& other)
{
    Polynomial result(max(this->degree, other.degree));
    for(int i=0;i<=result.degree;i++) result.coef[i] = this->coef[i] + other.coef[i];

    return result;
}

// - operator
Polynomial Polynomial::operator-(const Polynomial& other)
{
    Polynomial result(max(this->degree, other.degree));
    for(int i=0;i<=result.degree;i++) result.coef[i] = this->coef[i] - other.coef[i];

    return result;
}

// Multiply two polynomials in a brute force manner. O(N^2)
Polynomial Polynomial::multiplyBruteForce(const Polynomial& other)
{
    Polynomial result(this->degree*other.degree);
    for(int i=0;i<=this->degree;i++)
        for(int j=0;j<=other.degree;j++)
            result.coef[i+j] = this->coef[i] * other.coef[i];

    return result;
}

// Multiply two polynomials in a divide and conquer manner. O(N^1.585)
Polynomial Polynomial::multiplyDivideConquer(const Polynomial& other)
{

}

// Procedure to output polynomials
void Polynomial::printPolynomial()
{
    bool printed = false;
    for(int i=0;i<=this->degree;i++)
    {
        float curr = this->coef[i];
        float absCurr = abs(this->coef[i]);
        if(curr!=0)
        {
            if(!printed) printed = true;

            if(i==0) printf(curr > 0 ? "%.2f" : "- %.2f", absCurr);
            else printf(curr > 0 ? "+ %.2f" : "- %.2f", absCurr);
        }
    }
    if(!printed) printf("0");

    printf("\n");
}
// Procedure to take input for polynomials
void Polynomial::inputPolynomial()
{
    for(int i=0;i<=this->degree;i++) scanf("%f", &this->coef[i]);
}
