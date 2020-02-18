#include "Polynomial.hpp"

// Default ctor
Polynomial::Polynomial()
{
    this->degree = 10;
    this->coef = new int[11];
    for(int i=0;i<=this->degree;i++) this->coef[i] = 0;
}

// ctor
Polynomial::Polynomial(int degree)
{
    this->degree = degree;
    this->coef = new int[degree+1];
    for(int i=0;i<=this->degree;i++) this->coef[i] = 0;
}
// cctor
Polynomial::Polynomial(const Polynomial& other)
{
    this->degree = other.degree;
    this->coef = new int[other.degree+1];
    for(int i=0;i<=this->degree;i++) this->coef[i] = other.coef[i];
}
// Assignment operator
Polynomial& Polynomial::operator=(const Polynomial& other)
{
    this->degree = other.degree;
    this->coef = new int[other.degree+1];
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
int Polynomial::getCoef(int n)
{
    return this->coef[n];
}

// Set degree of the polynomial
void Polynomial::setDegree(int n)
{
    int prev = this->degree;
    this->degree = n;
    int arr[prev+1];
    for(int i=0;i<=prev;i++) arr[i] = this->coef[i];
    this->coef = new int[this->degree+1];
    for(int i=0;i<=this->degree;i++)
    {
        if(i>prev) coef[i]=0;
        else this->coef[i] = arr[i];
    }
}

// Set coeffcient of the term with the power of n
void Polynomial::setCoef(int x, int n)
{
    this->coef[n] = x;
}

// + operator
Polynomial Polynomial::operator+(const Polynomial& other)
{
    int maxDegree = max(this->degree, other.degree);
    Polynomial result(maxDegree);
    for(int i=0;i<=maxDegree;i++)
    {
        if(i>this->degree) result.coef[i] = other.coef[i];
        else if(i>other.degree) result.coef[i] = this->coef[i];
        else result.coef[i] = this->coef[i] + other.coef[i];
    }

    return result;
}

// - operator
Polynomial Polynomial::operator-(const Polynomial& other)
{
    int maxDegree = max(this->degree, other.degree);
    Polynomial result(maxDegree);
    for(int i=0;i<=maxDegree;i++)
    {
        if(i>this->degree) result.coef[i] = -other.coef[i];
        else if(i>other.degree) result.coef[i] = this->coef[i];
        else result.coef[i] = this->coef[i] - other.coef[i];
    }

    int minimize = result.degree;
    while(this->coef[minimize]==0) minimize--; 
    
    result.degree = minimize;
    return result;
}

// Multiply two polynomials in a brute force manner. O(N^2)
Polynomial Polynomial::operator*(const Polynomial& other)
{
    Polynomial result(this->degree+other.degree);
    for(int i=0;i<=this->degree;i++)
        for(int j=0;j<=other.degree;j++)
            result.coef[i+j] = this->coef[i] * other.coef[i];

    return result;
}


// Multiply two polynomials in a brute force manner. O(N^2)
Polynomial Polynomial::multiplyBruteForce(const Polynomial& other)
{
    Polynomial result(this->degree+other.degree);
    for(int i=0;i<=this->degree;i++)
        for(int j=0;j<=other.degree;j++)
            result.coef[i+j] = this->coef[i] * other.coef[i];

    return result;
}

// Multiply two polynomials in a divide and conquer manner. O(N^1.585)
Polynomial Polynomial::multiplyDivideConquer(const Polynomial& other)
{
    Polynomial result(this->degree*other.degree);

    // Based on slide..
    int size = this->degree>>1;
    int otherSize = other.degree>>1;

    Polynomial A0(size-1);
    for(int i=0;i<=A0.getDegree();i++) A0.setCoef(this->coef[i],i);

    Polynomial A1(this->degree-size);
    for(int i=0;i<=A1.getDegree();i++) A1.setCoef(this->coef[size+i], i);

    Polynomial B0(otherSize-1);
    for(int i=0;i<=B0.getDegree();i++) B0.setCoef(other.coef[i],i);

    Polynomial B1(other.degree-otherSize);
    for(int i=0;i<=B1.getDegree();i++) B1.setCoef(other.coef[size+i], i);

    Polynomial Asum = A0+A1;
    Polynomial Bsum = B0+B1;
    Polynomial Y = Asum * Bsum;
    Polynomial U = A0 * B0;
    Polynomial Z = A1 * B1;

    Polynomial x1(size);
    x1.setCoef(1, size);
    Polynomial x2(size<<1);
    x2.setCoef(1, size<<1);
    printf("x2: ");
    x2.printPolynomial();

    Polynomial W = Y-U-Z;
    printf("W: ");
    W.printPolynomial();

    result = U + W.multiplyBruteForce(x1);
    result.printPolynomial();
    result = result + Z.multiplyBruteForce(x2);
    result.printPolynomial();
    return result;

}

// Procedure to output polynomials
void Polynomial::printPolynomial()
{
    bool printed = false;
    for(int i=0;i<=this->degree;i++)
    {
        int curr = this->coef[i];
        int absCurr = abs(this->coef[i]);
        if(curr!=0)
        {
            if(!printed) printed = true;

            if(i==0) printf(curr > 0 ? "%d" : "- %d", absCurr);
            else printf(curr > 0 ? " + %d" : " - %d", absCurr);

            if(i!=0) printf("x^%d", i);
        }
    }
    if(!printed) printf("0");

    printf("\n");
}
// Procedure to take input for polynomials
void Polynomial::inputPolynomial()
{
    for(int i=0;i<=this->degree;i++) scanf("%d", &this->coef[i]);
}
