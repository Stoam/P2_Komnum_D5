#include <bits/stdc++.h>
using namespace std;

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

/*
f : fungsi f(x)
a : batas bawah integral
b : batas atas integral
n : banyak pias
h : selisih x
r : hasil integral
*/

double trapezoidal(double (*f)(double), double a, double b, int n)
{
    double h = (b - a) / (double) n;
    double r = f(a) + f(b);

    for(double i = a + h; i < b; i += h)
        r += 2 * f(i);
    return r * h / 2;
}

double romberg(double (*f)(double), double a, double b, int n)
{
    double h[n + 1], r[n + 1][n + 1];

    for (int i = 1; i <= n; ++i){
        h[i] = (b - a) / power(2, i - 1);
    }
    r[1][1] = h[1] / 2 * (f(a) + f(b));

    for(int i = 2; i <= n; ++i)
    {
        double coef = 0;
        int batas = power(2, i - 2);

        for(int k = 1; k <= batas; ++k){
            coef += f(a + (2 * k - 1) * h[i]);
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

double f2(double x)
{
    return sqrt(x);
}

double f3(double x)
{
    return sin(x);
}

double calcError(double result, double expected)
{
    double diff = abs(result - expected);
    double error = (diff / expected) * 100;
    return error;   
}

const double f_ans[4] = {0, 2.3026, 5.3333, 0.29289};

void solve(double (*f)(double), double a, double b, int n, int idx)
{
    double f_traped = trapezoidal(f, a, b, n);
    double f_romberg = romberg(f, a, b, n);

    cout << "\nIntegration Result for Function f" << idx << " using Analytical Method  : " << f_ans[idx];
    cout << "\nIntegration Result for Function f" << idx << " using Trapezoidal Method : " << f_traped;
    cout << "\nIntegration Result for Function f" << idx << " using Romberg Method     : " << f_romberg << "\n\n";

    cout << "Error for Function f" << idx << " using Trapezoidal Method : ";
    cout << fixed << setprecision(3) << calcError(f_traped, f_ans[idx]) << " %\n";

    cout << "Error for Function f" << idx << " using Romberg Method     : ";
    cout << fixed << setprecision(3) << calcError(f_romberg, f_ans[idx]) << " %\n\n";
    cout << string(72, '-') << '\n';
}

int main()
{
    solve(&f1, 1, 10, 5, 1);
    solve(&f2, 0, 4, 4, 2);
    solve(&f3, 0, 7.0 * M_PI / 4.0, 7, 3);
    return 0;
}
