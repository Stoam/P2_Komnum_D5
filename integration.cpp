#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

const double f1_ans = 2.3026;

double power(double num, int exp)
{
    double res = 1;

    while(exp > 0){
        if(exp & 1)
            res *= num;
        num *= num;
        exp >>= 1;
    }
    return res;
}

// func : f(x), lower : a, upper : b, interval : h
double trapezoidal(double (*func)(double), double lower, double upper, int n)
{
    double interval = (upper - lower) / (double) n;
    double integration = func(lower) + func(upper);

    for(double i = lower + interval; i < upper; i += interval){
        integration += 2 * func(i);
    }
    return integration * interval / 2;
}

double romberg(double (*func)(double), double a, double b, int n)
{
    double h[n + 1], r[n + 1][n + 1];

    for (int i = 1; i <= n; ++i){
        h[i] = (b - a) / power(2, i - 1);
    }
    r[1][1] = h[1] / 2 * (func(a) + func(b));

    for(int i = 2; i <= n; ++i)
    {
        double coef = 0;
        int batas = power(2, i - 2);

        for(int k = 1; k <= batas; ++k){
            coef += func(a + (2 * k - 1) * h[i]);
        }
        r[i][1] = (r[i - 1][1] + h[i - 1] * coef) / 2;
    }
    for (int i = 2; i <= n; ++i){
        for(int j = 2; j <= i; ++j)
        {
            r[i][j] = r[i][j - 1] + (r[i][j - 1] - r[i - 1][j - 1]) / (power(4, j - 1) - 1);
        }
    }
    return r[n][n];
}

double f1(double x)
{
    return 1 / x;
}

// double f2(double x)
// {

// }

void calcError(double result, double intended)
{
    double diff = abs(result - intended);
    double error = (diff / intended) * 100;
    cout << fixed << setprecision(3) << error << " %\n";
}

int main()
{
    double f1_traped = trapezoidal(&f1, 1, 10, 5);
    double f1_romberg = romberg(&f1, 1, 10, 5);

    cout << "Error for function f1 using Trapezoidal Method : ";
    calcError(f1_traped, f1_ans);
    cout << "Error for function f1 using Romberg Method     : ";
    calcError(f1_romberg, f1_ans);
    cout << endl;

    return 0;
}
