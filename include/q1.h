#ifndef Q1_H
#define Q1_H

#include<iostream>
#include<functional>

namespace q1
{
    inline double gradient(std::function<double(double)> f, double x)
    {
        return (f(x + 0.00001) - f(x)) / 0.00001;
    }

    inline double gradient_descent(double initial_value, double step_size, std::function<double(double)> f)
    {
        double x = initial_value;
        while (std::abs(gradient(f, x)) > 0.001)
        {
            x -= step_size * gradient(f, x);
        }
        return x;
    }

    template<typename T, typename Func>
    inline T gradient_descent(T initial_value, double step_size)
    {
        T x = initial_value;
        Func f = Func();
        while (std::abs(gradient(f, x)) > 0.001)
        {
            x -= step_size * gradient(f, x);
        }
        return x;
    }
}
#endif //Q1_H