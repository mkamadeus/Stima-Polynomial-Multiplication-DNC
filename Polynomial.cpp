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

    // 
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
    // Store max possible degree
    int maxDegree = max(this->degree, other.degree);

    // Store values in a temporary array and set the array to 0
    int temp[maxDegree+1];
    memset(temp, 0, sizeof(temp));

    // Add up values in the array
    for(int i=0;i<=this->degree;i++) temp[i] = this->coef[i];
    for(int i=0;i<=other.degree;i++) temp[i] += other.coef[i];
    
    // Minimize degree if current degree holds coefficient of 0
    int builtDegree = maxDegree;
    while(temp[builtDegree]==0) builtDegree--;

    // Build Polynomial from known values
    Polynomial result(builtDegree);
    for(int i=0;i<=builtDegree;i++) result.coef[i] = temp[i];

    return result;
}

// - operator
Polynomial Polynomial::operator-(const Polynomial& other)
{
    // Store max possible degree
    int maxDegree = max(this->degree, other.degree);
    
    // Store values in a temporary array and set the array to 0
    int temp[maxDegree+1];
    memset(temp, 0, sizeof(temp));

    // Substract values in the array
    for(int i=0;i<=this->degree;i++) temp[i] = this->coef[i];
    for(int i=0;i<=other.degree;i++) temp[i] -= other.coef[i];
    
    // Minimize degree if current degree holds coefficient of 0
    int builtDegree = maxDegree;
    while(temp[builtDegree]==0) builtDegree--;

    // Build Polynomial from known values
    Polynomial result(builtDegree);
    for(int i=0;i<=builtDegree;i++) result.coef[i] = temp[i];

    return result;
}

// Multiply two polynomials in a brute force manner. O(N^2)
Polynomial Polynomial::operator*(const Polynomial& other)
{
    Polynomial result(this->degree+other.degree);
    
    /* =-=-=-= BRUTE FORCE ALGORITHM =-=-=-= */
    for(int i=0;i<=this->degree;i++)
        for(int j=0;j<=other.degree;j++)
            result.coef[i+j] += this->coef[i] * other.coef[j];

    return result;
}

// Compare two polynomials
bool Polynomial::operator==(const Polynomial& other)
{
    // If degree not equal, set to false; else true.
    bool result = this->degree==other.degree ? true : false;
    
    // While values equal..
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
    // Make a bigger Polynomial
    this->setDegree(this->degree + n);

    // Move contents to respective coefficients
    for(int i=this->degree;i>=0;i--)
    {
        // If already passed the limit of the polynomial, insert 0
        if(i-n<0) this->coef[i] = 0;
        else this->coef[i] = this->coef[i-n];
    }
    
    return *this;   
}

// Multiply two polynomials in a divide and conquer manner. O(N^1.585)
Polynomial Polynomial::multiplyDivideConquer(const Polynomial& other)
{
    // Base Case
    if(this->degree<=1 || other.degree<=1) return (*this)*other;

    Polynomial result(this->degree+other.degree);

    // Based on slide..
    int size = this->degree>>1; // equal to floor(n/2)

    /* -=-=- DIVIDE... -=-=-  */
    
    // (*this) = A0(x) + A1(x) * x^size
    Polynomial A0(size-1);
    for(int i=0;i<=A0.getDegree();i++) A0.setCoef(this->coef[i],i);

    Polynomial A1(this->degree-size);
    for(int i=0;i<=A1.getDegree();i++) A1.setCoef(this->coef[size+i], i);

    // other = B0(x) + B1(x) * x^size
    Polynomial B0(size-1);
    for(int i=0;i<=B0.getDegree();i++) B0.setCoef(other.coef[i],i);

    Polynomial B1(other.degree-size);
    for(int i=0;i<=B1.getDegree();i++) B1.setCoef(other.coef[size+i], i);

    // Recusive Call
    Polynomial Y = (A0+A1).multiplyDivideConquer(B0+B1);
    Polynomial U = A0.multiplyDivideConquer(B0);
    Polynomial Z = A1.multiplyDivideConquer(B1);

    /* -=-=- ...AND CONQUER. -=-=-  */

    // The Karatsuba Formula.
    Polynomial W = Y-U-Z;
    result = U + (W<<size) + (Z<<(size<<1));

    return result;
}

// Procedure to output polynomials
void Polynomial::printPolynomial()
{
    // Set printed flag
    bool printed = false;

    // Traverse through coefficients
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

    // If not yet printed (all coefficients = 0), output 0
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

// Generate random coefficients for the polynomial
void Polynomial::generateRandom()
{
    for(int i=0;i<=this->degree;i++) this->coef[i] = rand()%100 - 50;
}
