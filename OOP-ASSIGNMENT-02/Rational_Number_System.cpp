#include <iostream>
using namespace std;

class Rational {
private:
   int numerator;   
   int denominator; 

   int gcd(int a, int b) {
       a = (a < 0) ? -a : a;
       b = (b < 0) ? -b : b;

       while (b != 0) {
           int temp = b;
           b = a % b;
           a = temp;
       }
       return a;
   }

   
   void reduce() {
       if (denominator == 0) {
           denominator = 1; 
       }

       
       if (denominator < 0) {
           numerator = -numerator;
           denominator = -denominator;
       }

       int divisor = gcd(numerator, denominator);
       if (divisor != 0) {
           numerator /= divisor;
           denominator /= divisor;
       }
   }

public:
   // Default
   Rational() {
       numerator = 0;
       denominator = 1;
   }

   // Parameterized
   Rational(int num, int den) {
       if (den == 0) {
           cout << "Error: Denominator cannot be zero. Setting to 0/1." << endl;
           numerator = 0;
           denominator = 1;
           return;
       }
       numerator = num;
       denominator = den;
       reduce();
   }


   Rational(int num) {
       numerator = num;
       denominator = 1;
   }

   // Copy
   Rational(const Rational& other) {
       numerator = other.numerator;
       denominator = other.denominator;
   }

   // Getters
   int getNumerator() const {
       return numerator;
   }

   int getDenominator() const {
       return denominator;
   }

   // Setters
   void setNumerator(int num) {
       numerator = num;
       reduce();
   }

   void setDenominator(int den) {
       if (den == 0) {
           cout << "Error: Denominator cannot be zero." << endl;
           return;
       }
       denominator = den;
       reduce();
   }

   // Display
   void display() const {
       cout << numerator << "/" << denominator;
   }

   
   Rational operator+(const Rational& other) const {
       int newNum = numerator * other.denominator + other.numerator * denominator;
       int newDen = denominator * other.denominator;
       return Rational(newNum, newDen);
   }

   Rational operator+(int num) const {
       return *this + Rational(num);
   }

   friend Rational operator+(int num, const Rational& r);

   
   Rational operator-(const Rational& other) const {
       int newNum = numerator * other.denominator - other.numerator * denominator;
       int newDen = denominator * other.denominator;
       return Rational(newNum, newDen);
   }

 
   Rational operator-(int num) const {
       return *this - Rational(num);
   }

  
   friend Rational operator-(int num, const Rational& r);

   
   Rational operator*(const Rational& other) const {
       int newNum = numerator * other.numerator;
       int newDen = denominator * other.denominator;
       return Rational(newNum, newDen);
   }

 
   Rational operator*(int num) const {
       return *this * Rational(num);
   }

   
   friend Rational operator*(int num, const Rational& r);

   
   Rational operator/(const Rational& other) const {
       if (other.numerator == 0) {
           cout << "Error: Division by zero. Returning 0/1." << endl;
           return Rational(0, 1);
       }
       int newNum = numerator * other.denominator;
       int newDen = denominator * other.numerator;
       return Rational(newNum, newDen);
   }

   
   Rational operator/(int num) const {
       return *this / Rational(num);
   }

   
   friend Rational operator/(int num, const Rational& r);

   Rational& operator+=(const Rational& other) {
       *this = *this + other;
       return *this;
   }

   Rational& operator-=(const Rational& other) {
       *this = *this - other;
       return *this;
   }

   Rational& operator*=(const Rational& other) {
       *this = *this * other;
       return *this;
   }

   Rational& operator/=(const Rational& other) {
       *this = *this / other;
       return *this;
   }

   bool operator==(const Rational& other) const {
       return (numerator == other.numerator && denominator == other.denominator);
   }

   bool operator!=(const Rational& other) const {
       return !(*this == other);
   }

   bool operator<(const Rational& other) const {
       return (numerator * other.denominator < other.numerator * denominator);
   }

   bool operator<=(const Rational& other) const {
       return (*this < other || *this == other);
   }

   bool operator>(const Rational& other) const {
       return (numerator * other.denominator > other.numerator * denominator);
   }

   bool operator>=(const Rational& other) const {
       return (*this > other || *this == other);
   }

  
   Rational& operator++() {
       numerator += denominator; 
       reduce();
       return *this;
   }

   Rational operator++(int) {
       Rational temp = *this;
       numerator += denominator;
       reduce();
       return temp;
   }

   Rational& operator--() {
       numerator -= denominator; 
       reduce();
       return *this;
   }

   Rational operator--(int) {
       Rational temp = *this;
       numerator -= denominator;
       reduce();
       return temp;
   }

   Rational operator()() const {
       if (numerator == 0) {
           throw "Error: Cannot take reciprocal of zero";
       }
       return Rational(denominator, numerator);
   }

  
   friend ostream& operator<<(ostream& out, const Rational& r);
   friend istream& operator>>(istream& in, Rational& r);
};

Rational operator+(int num, const Rational& r) {
   return Rational(num) + r;
}

Rational operator-(int num, const Rational& r) {
   return Rational(num) - r;
}

Rational operator*(int num, const Rational& r) {
   return Rational(num) * r;
}

Rational operator/(int num, const Rational& r) {
   return Rational(num) / r;
}

ostream& operator<<(ostream& out, const Rational& r) {
   out << r.numerator << "/" << r.denominator;
   return out;
}

istream& operator>>(istream& in, Rational& r) {
   int num, den;
   in >> num >> den;
   r = Rational(num, den);
   return in;
}


int main() {
   Rational r1, r2;
   int choice, num, den;

   do {

       cout << "1. Create new rational numbers\n";
       cout << "2. Display rational numbers\n";
       cout << "3. Test arithmetic (+, -, *, /)\n";
       cout << "4. Test compound assignment (+=, -=, *=, /=)\n";
       cout << "5. Test comparison operators\n";
       cout << "6. Test increment/decrement (++, --)\n";
       cout << "7. Test function call operator (reciprocal)\n";
       cout << "8. Test with integers\n";
       cout << "9. Test copy constructor\n";
       cout << "0. Exit\n";
       cout << "Enter choice: ";
       cin >> choice;

       switch (choice) {
       case 1: {
           cout << "Enter first rational (numerator denominator): ";
           cin >> r1;
           cout << "Enter second rational (numerator denominator): ";
           cin >> r2;
           cout << "Rational numbers created successfully!\n";
           break;
       }

       case 2: {
           cout << "r1 = " << r1 << endl;
           cout << "r2 = " << r2 << endl;
           break;
       }

       case 3: {
           cout << "r1 + r2 = " << r1 + r2 << endl;
           cout << "r1 - r2 = " << r1 - r2 << endl;
           cout << "r1 * r2 = " << r1 * r2 << endl;
           cout << "r1 / r2 = " << r1 / r2 << endl;
           break;
       }

       case 4: {
           Rational r3 = r1;
           r3 += r2;
           cout << "r1 += r2 = " << r3 << endl;
           r3 = r1;
           r3 -= r2;
           cout << "r1 -= r2 = " << r3 << endl;
           r3 = r1;
           r3 *= r2;
           cout << "r1 *= r2 = " << r3 << endl;
           r3 = r1;
           r3 /= r2;
           cout << "r1 /= r2 = " << r3 << endl;
           break;
       }

       case 5: {
           cout << "r1 == r2: " << (r1 == r2 ? "true" : "false") << endl;
           cout << "r1 != r2: " << (r1 != r2 ? "true" : "false") << endl;
           cout << "r1 < r2: " << (r1 < r2 ? "true" : "false") << endl;
           cout << "r1 <= r2: " << (r1 <= r2 ? "true" : "false") << endl;
           cout << "r1 > r2: " << (r1 > r2 ? "true" : "false") << endl;
           cout << "r1 >= r2: " << (r1 >= r2 ? "true" : "false") << endl;
           break;
       }

       case 6: {
           Rational r3 = r1;
           cout << "Original r1: " << r1 << endl;
           cout << "++r1: " << ++r3 << endl;
           r3 = r1;
           cout << "r1++: " << r3++ << " (then becomes " << r3 << ")" << endl;
           r3 = r1;
           cout << "--r1: " << --r3 << endl;
           r3 = r1;
           cout << "r1--: " << r3-- << " (then becomes " << r3 << ")" << endl;
           break;
       }

       case 7: {
           try {
               Rational recip = r1();
               cout << "Reciprocal of " << r1 << " is " << recip << endl;
           }
           catch (const char* msg) {
               cout << msg << endl;
           }
           break;
       }

       case 8: {
           int num;
           cout << "Enter an integer: ";
           cin >> num;
           cout << "r1 + " << num << " = " << r1 + num << endl;
           cout << num << " + r1 = " << num + r1 << endl;
           cout << "r1 - " << num << " = " << r1 - num << endl;
           cout << num << " - r1 = " << num - r1 << endl;
           cout << "r1 * " << num << " = " << r1 * num << endl;
           cout << num << " * r1 = " << num * r1 << endl;
           cout << "r1 / " << num << " = " << r1 / num << endl;
           cout << num << " / r1 = " << num / r1 << endl;
           break;
       }

       case 9: {
           Rational r3(r1); 
           cout << "Copy of r1: " << r3 << endl;
           cout << "Modifying original doesn't affect copy:" << endl;
           r1.setNumerator(999);
           cout << "Original now: " << r1 << endl;
           cout << "Copy still: " << r3 << endl;
           break;
       }

       case 0:
           cout << "Exiting program. Goodbye!" << endl;
           break;

       default:
           cout << "Invalid choice! Try again.\n";
       }
   } while (choice != 0);

   return 0;
}