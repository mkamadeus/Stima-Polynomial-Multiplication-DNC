#include "Polynomial.hpp"

// Default ctor
Polynomial::Polynomial()
{
    this->degree = 0;
    this->coef = new int[degree+1];
    this->coef[0] = 0;
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
    // Save previous values
    int prev = this->degree;
    int tmp[prev+1];
    for(int i=0;i<=prev;i++) tmp[i] = this->coef[i];

    // Set to new degree
    this->degree = n;
    this->coef = new int[this->degree+1];

    for(int i=0;i<=this->degree;i++)
    {
        if(i>prev) coef[i]=0;
        else this->coef[i] = tmp[i];
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
    int temp[maxDegree+1];
    memset(temp, 0, sizeof(temp));

    for(int i=0;i<=this->degree;i++) temp[i] = this->coef[i];
    for(int i=0;i<=other.degree;i++) temp[i] += other.coef[i];
    
    int builtDegree = maxDegree;
    while(temp[builtDegree]==0) builtDegree--;

    Polynomial result(builtDegree);
    for(int i=0;i<=builtDegree;i++) result.coef[i] = temp[i];

    return result;
}

// - operator
Polynomial Polynomial::operator-(const Polynomial& other)
{
    int maxDegree = max(this->degree, other.degree);
    int temp[maxDegree+1];
    memset(temp, 0, sizeof(temp));

    for(int i=0;i<=this->degree;i++) temp[i] = this->coef[i];
    for(int i=0;i<=other.degree;i++) temp[i] -= other.coef[i];
    
    int builtDegree = maxDegree;
    while(temp[builtDegree]==0) builtDegree--;

    Polynomial result(builtDegree);
    for(int i=0;i<=builtDegree;i++) result.coef[i] = temp[i];

    return result;
}

// Multiply two polynomials in a brute force manner. O(N^2)
Polynomial Polynomial::operator*(const Polynomial& other)
{
    Polynomial result(this->degree+other.degree);
    for(int i=0;i<=this->degree;i++)
        for(int j=0;j<=other.degree;j++)
            result.coef[i+j] += this->coef[i] * other.coef[j];

    return result;
}

// Compare two polynomials
bool Polynomial::operator==(const Polynomial& other)
{
    bool result = this->degree==other.degree ? true : false;
    int i=0;
    while(result && i<=other.degree)
    {
        if(this->coef[i]!=other.coef[i]) result = false;
        else i++;
    }

    return result;
}

// Multiply polynomial by a factor of x
Polynomial Polynomial::operator<<(int n)
{
    this->setDegree(this->degree + n);
    for(int i=this->degree;i>=0;i--)
    {
        if(i-n<0) this->coef[i] = 0;
        else this->coef[i] = this->coef[i-n];
    }
    return *this;   
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
    // Base Case
    if(this->degree<=1 || other.degree<=1) return (*this)*other;

    Polynomial result(this->degree+other.degree);
    
    // Based on slide..
    int size = this->degree>>1; // equal to floor(n/2)

    // Divide...
    Polynomial A0(size-1);
    for(int i=0;i<=A0.getDegree();i++) A0.setCoef(this->coef[i],i);

    Polynomial A1(this->degree-size);
    for(int i=0;i<=A1.getDegree();i++) A1.setCoef(this->coef[size+i], i);

    Polynomial B0(size-1);
    for(int i=0;i<=B0.getDegree();i++) B0.setCoef(other.coef[i],i);

    Polynomial B1(other.degree-size);
    for(int i=0;i<=B1.getDegree();i++) B1.setCoef(other.coef[size+i], i);

    Polynomial Y = (A0+A1).multiplyDivideConquer(B0+B1);
    Polynomial U = A0.multiplyDivideConquer(B0);
    Polynomial Z = A1.multiplyDivideConquer(B1);

    // ..and Conquer.

    Polynomial W = Y-U-Z;

    result = U + (W<<size) + (Z<<(size<<1));

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
            if(!printed) printf(curr > 0 ? "%d" : "- %d", absCurr);
            else printf(curr > 0 ? " + %d" : " - %d", absCurr);

            if(i!=0) printf("x^%d", i);
            
            if(!printed) printed = true;
        }
    }
    if(!printed) printf("0");

    printf("\n");
}

// Procedure to output polynomials by coefficients only
void Polynomial::printCoefficients()
{
    for(int i=0;i<=this->degree;i++) printf("%d ", this->coef[i]);
    printf("\n");
}

// Procedure to take input for polynomials
void Polynomial::inputPolynomial()
{
    for(int i=0;i<=this->degree;i++) scanf("%d", &this->coef[i]);
}

void Polynomial::generateRandom()
{
    for(int i=0;i<=this->degree;i++) this->coef[i] = rand()%100 - 50;
}
