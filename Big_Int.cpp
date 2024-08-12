#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cstring>

using namespace std;

class BigInt {
    string digits;
public:
    // Constructors:
    BigInt(unsigned long long n = 0);
    BigInt(string &);
    BigInt(const char *);
    BigInt(const BigInt &);

    // Helper Functions:
    friend void divide_by_2(BigInt &a);
    friend bool Null(const BigInt &);
    friend int Length(const BigInt &);
    int operator[](const int) const;

     int countDigits() const;
    // Operator Overloading
    BigInt &operator=(const BigInt &);

    // Post/Pre - Incrementation
    BigInt &operator++();
    BigInt operator++(int temp);
    BigInt &operator--();
    BigInt operator--(int temp);

    // Addition and Subtraction
    friend BigInt &operator+=(BigInt &, const BigInt &);
    friend BigInt operator+(const BigInt &, const BigInt &);
    friend BigInt operator-(const BigInt &, const BigInt &);
    friend BigInt &operator-=(BigInt &, const BigInt &);

    // Comparison operators
    friend bool operator==(const BigInt &, const BigInt &);
    friend bool operator!=(const BigInt &, const BigInt &);
    friend bool operator>(const BigInt &, const BigInt &);
    friend bool operator>=(const BigInt &, const BigInt &);
    friend bool operator<(const BigInt &, const BigInt &);
    friend bool operator<=(const BigInt &, const BigInt &);

    // Multiplication and Division
    friend BigInt &operator*=(BigInt &, const BigInt &);
    friend BigInt operator*(const BigInt &, const BigInt &);
    friend BigInt &operator/=(BigInt &, const BigInt &);
    friend BigInt operator/(const BigInt &, const BigInt &);

    // Modulo
    friend BigInt operator%(const BigInt &, const BigInt &);
    friend BigInt &operator%=(BigInt &, const BigInt &);

    // Power Function
    friend BigInt &operator^=(BigInt &, const BigInt &);
    friend BigInt operator^(BigInt &, const BigInt &);

    // Square Root Function
    friend BigInt sqrt(BigInt &a);

    // Read and Write
    friend ostream &operator<<(ostream &, const BigInt &);
    friend istream &operator>>(istream &, BigInt &);

    // Others
    friend BigInt NthCatalan(int n);
    friend BigInt NthFibonacci(int n);
    friend BigInt Factorial(int n);
};

// Constructors
BigInt::BigInt(string &s) {
    digits = "";
    int n = s.size();
    for (int i = n - 1; i >= 0; i--) {
        if (!isdigit(s[i]))
            throw("ERROR");
        digits.push_back(s[i] - '0');
    }
}

BigInt::BigInt(unsigned long long nr) {
    do {
        digits.push_back(nr % 10);
        nr /= 10;
    } while (nr);
}

BigInt::BigInt(const char *s) {
    digits.clear(); // Ensure digits is cleared
    for (int i = strlen(s) - 1; i >= 0; i--) {
        if (!isdigit(s[i]))
            throw("ERROR");
        digits.push_back(s[i] - '0');
    }
}

BigInt::BigInt(const BigInt &a) {
    digits = a.digits;
}

// Helper functions
bool Null(const BigInt &a) {
    return a.digits.size() == 1 && a.digits[0] == 0;
}

int Length(const BigInt &a) {
    return a.digits.size();
}

int BigInt::operator[](const int index) const {
    if (digits.size() <= index || index < 0)
        throw("ERROR");
    return digits[index];
}

// Comparison operators
bool operator==(const BigInt &a, const BigInt &b) {
    return a.digits == b.digits;
}

bool operator!=(const BigInt &a, const BigInt &b) {
    return !(a == b);
}

bool operator<(const BigInt &a, const BigInt &b) {
    int n = Length(a), m = Length(b);
    if (n != m)
        return n < m;
    while (n--)
        if (a.digits[n] != b.digits[n])
            return a.digits[n] < b.digits[n];
    return false;
}

bool operator>(const BigInt &a, const BigInt &b) {
    return b < a;
}

bool operator>=(const BigInt &a, const BigInt &b) {
    return !(a < b);
}

bool operator<=(const BigInt &a, const BigInt &b) {
    return !(a > b);
}

// Assignment operator
BigInt &BigInt::operator=(const BigInt &a) {
    digits = a.digits;
    return *this;
}

// Increment and decrement operators
BigInt &BigInt::operator++() {
    int i, n = digits.size();
    for (i = 0; i < n && digits[i] == 9; i++)
        digits[i] = 0;
    if (i == n)
        digits.push_back(1);
    else
        digits[i]++;
    return *this;
}

BigInt BigInt::operator++(int temp) {
    BigInt aux = *this;
    ++(*this);
    return aux;
}

BigInt &BigInt::operator--() {
    if (digits[0] == 0 && digits.size() == 1)
        throw("UNDERFLOW");
    int i, n = digits.size();
    for (i = 0; digits[i] == 0 && i < n; i++)
        digits[i] = 9;
    digits[i]--;
    if (n > 1 && digits[n - 1] == 0)
        digits.pop_back();
    return *this;
}

BigInt BigInt::operator--(int temp) {
    BigInt aux = *this;
    --(*this);
    return aux;
}

// Addition and subtraction operators
BigInt &operator+=(BigInt &a, const BigInt &b) {
    int t = 0, s, i;
    int n = Length(a), m = Length(b);
    if (m > n)
        a.digits.append(m - n, 0);
    n = Length(a);
    for (i = 0; i < n; i++) {
        if (i < m)
            s = a.digits[i] + b.digits[i] + t;
        else
            s = a.digits[i] + t;
        t = s / 10;
        a.digits[i] = s % 10;
    }
    if (t)
        a.digits.push_back(t);
    return a;
}

BigInt operator+(const BigInt &a, const BigInt &b) {
    BigInt temp = a;
    temp += b;
    return temp;
}

BigInt &operator-=(BigInt &a, const BigInt &b) {
    if (a < b)
        throw("UNDERFLOW");
    int n = Length(a), m = Length(b);
    int i, t = 0, s;
    for (i = 0; i < n; i++) {
        if (i < m)
            s = a.digits[i] - b.digits[i] + t;
        else
            s = a.digits[i] + t;
        if (s < 0)
            s += 10, t = -1;
        else
            t = 0;
        a.digits[i] = s;
    }
    while (n > 1 && a.digits[n - 1] == 0)
        a.digits.pop_back(), n--;
    return a;
}

BigInt operator-(const BigInt &a, const BigInt &b) {
    BigInt temp = a;
    temp -= b;
    return temp;
}

// Multiplication and division operators
BigInt &operator*=(BigInt &a, const BigInt &b) {
    if (Null(a) || Null(b)) {
        a = BigInt();
        return a;
    }
    int n = a.digits.size(), m = b.digits.size();
    vector<int> v(n + m, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            v[i + j] += a.digits[i] * b.digits[j];
    n += m;
    a.digits.resize(v.size());
    for (int s, i = 0, t = 0; i < n; i++) {
        s = t + v[i];
        v[i] = s % 10;
        t = s / 10;
        a.digits[i] = v[i];
    }
    while (a.digits.size() > 1 && a.digits.back() == 0)
        a.digits.pop_back();
    return a;
}

BigInt operator*(const BigInt &a, const BigInt &b) {
    BigInt temp = a;
    temp *= b;
    return temp;
}

BigInt &operator/=(BigInt &a, const BigInt &b) {
    if (Null(b))
        throw("Arithmetic Error: Division By 0");
    if (a < b) {
        a = BigInt();
        return a;
    }
    if (a == b) {
        a = BigInt(1);
        return a;
    }
    int i, lgcat = 0, cc;
    int n = Length(a), m = Length(b);
    vector<int> cat(n, 0);
    BigInt t;
    for (i = n - 1; t * 10 + a.digits[i] < b; i--)
        t = t * 10 + a.digits[i];
    for (; i >= 0; i--) {
        t = t * 10 + a.digits[i];
        for (cc = 9; cc * b > t; cc--);
        t -= cc * b;
        cat[lgcat++] = cc;
    }
    a.digits.resize(cat.size());
    for (i = 0; i < lgcat; i++)
        a.digits[i] = cat[lgcat - i - 1];
    a.digits.resize(lgcat);
    while (a.digits.size() > 1 && a.digits.back() == 0)
        a.digits.pop_back();
    return a;
}

BigInt operator/(const BigInt &a, const BigInt &b) {
    BigInt temp = a;
    temp /= b;
    return temp;
}

// Modulo operator
BigInt &operator%=(BigInt &a, const BigInt &b) {
    if (Null(b))
        throw("Arithmetic Error: Division By 0");
    if (a < b)
        return a;
    if (a == b) {
        a = BigInt();
        return a;
    }
    int i, lgcat = 0, cc;
    int n = Length(a), m = Length(b);
    BigInt t;
    for (i = n - 1; t * 10 + a.digits[i] < b; i--)
        t = t * 10 + a.digits[i];
    for (; i >= 0; i--) {
        t = t * 10 + a.digits[i];
        for (cc = 9; cc * b > t; cc--);
        t -= cc * b;
    }
    a = t;
    return a;
}

BigInt operator%(const BigInt &a, const BigInt &b) {
    BigInt temp = a;
    temp %= b;
    return temp;
}

// Power operator
BigInt &operator^=(BigInt &a, const BigInt &b) {
    BigInt Exponent, Base(a);
    Exponent = b;
    a = 1;
    while (!Null(Exponent)) {
        if (Exponent[0] & 1)
            a *= Base;
        Base *= Base;
        divide_by_2(Exponent);
    }
    return a;
}

BigInt operator^(BigInt &a, const BigInt &b) {
    BigInt temp = a;
    temp ^= b;
    return temp;
}

// Square root function
BigInt sqrt(BigInt &a) {
    BigInt left(1), right(a), v(1), mid, prod;
    divide_by_2(right);
    while (left <= right) {
        mid = (left + right);
        divide_by_2(mid);
        prod = (mid * mid);
        if (prod == a)
            return mid;
        if (prod < a) {
            left = mid;
            ++left;
            v = mid;
        } else {
            right = mid;
            --right;
        }
    }
    return v;
}

// Read and write functions
ostream &operator<<(ostream &out, const BigInt &a) {
    for (int i = a.digits.size() - 1; i >= 0; i--)
        cout << (short)a.digits[i];
    return cout;
}

istream &operator>>(istream &in, BigInt &a) {
    string s;
    in >> s;
    a = BigInt(s);
    return in;
}

// Additional functions
BigInt NthCatalan(int n) {
    BigInt a(1), b;
    for (int i = 2; i <= n; i++)
        a *= i;
    b = a;
    for (int i = n + 1; i <= 2 * n; i++)
        b *= i;
    a *= a;
    a *= (n + 1);
    b /= a;
    return b;
}

BigInt NthFibonacci(int n) {
    BigInt a(1), b(1), c;
    if (!n)
        return c;
    n--;
    while (n--) {
        c = a + b;
        b = a;
        a = c;
    }
    return b;
}

BigInt Factorial(int n) {
    BigInt f(1);
    for (int i = 2; i <= n; i++)
        f *= i;
    return f;
}

// Helper function to divide by 2
void divide_by_2(BigInt &a) {
    int add = 0;
    for (int i = a.digits.size() - 1; i >= 0; i--) {
        int digit = (a.digits[i] + add * 10) / 2;
        add = (a.digits[i] + add * 10) % 2;
        a.digits[i] = digit;
    }
    while (a.digits.size() > 1 && a.digits.back() == 0)
        a.digits.pop_back();
}

int BigInt::countDigits() const {
    return digits.size();
}


int main() {
    BigInt a, b;
    int choice;

    while (true) {
        cout << "1. Addition\n";
        cout << "2. Subtraction\n";
        cout << "3. Multiplication\n";
        cout << "4. Division\n";
        cout << "5. Modulo\n";
        cout << "6. Power\n";
        cout << "7. Square Root\n";
        cout << "8. Factorial\n";
        cout << "9. Count Digits\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 10) {
            cout << "Exiting...\n";
            break;
        }

        switch (choice) {
            case 1:  // Addition
                cout << "Enter two numbers:\n";
                cin >> a >> b;
                cout << "Result: " << (a + b) << endl;
                break;

            case 2:  // Subtraction
                cout << "Enter two numbers:\n";
                cin >> a >> b;
                cout << "Result: " << (a - b) << endl;
                break;

            case 3:  // Multiplication
                cout << "Enter two numbers:\n";
                cin >> a >> b;
                cout << "Result: " << (a * b) << endl;
                break;

            case 4:  // Division
                cout << "Enter two numbers:\n";
                cin >> a >> b;
                try {
                    cout << "Result: " << (a / b) << endl;
                } catch (const char *msg) {
                    cerr << msg << endl;
                }
                break;

            case 5:  // Modulo
                cout << "Enter two numbers:\n";
                cin >> a >> b;
                try {
                    cout << "Result: " << (a % b) << endl;
                } catch (const char *msg) {
                    cerr << msg << endl;
                }
                break;

            case 6:  // Power
                cout << "Enter base and exponent:\n";
                cin >> a >> b;
                cout << "Result: " << (a ^ b) << endl;
                break;

            case 7:  // Square Root
                cout << "Enter a number:\n";
                cin >> a;
                try {
                    cout << "Result: " << sqrt(a) << endl;
                } catch (const char *msg) {
                    cerr << msg << endl;
                }
                break;

            case 8:  // Factorial
                int n;
                cout << "Enter n:\n";
                cin >> n;
                try {
                    cout << "Result: " << Factorial(n) << endl;
                } catch (const char *msg) {
                    cerr << msg << endl;
                }
                break;

            case 9:  // Count Digits
                cout << "Enter a number:\n";
                cin >> a;
                cout << "Number of digits: " << a.countDigits() << endl;
                break;

            default:
                cout << "Invalid choice, please try again.\n";
        }
    }

    return 0;
}

