#include "hw1.h"
#include <iomanip>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

namespace algebra
{
    Matrix zeros(size_t n, size_t m)
    {
        Matrix mat{};
        std::vector<double> row0{};
        for (size_t i{}; i < m; i++)
        {
            row0.push_back(0);
        }
        for (size_t i{}; i < n; i++)
        {
            mat.push_back(row0);
        }
        return mat;
    }

    Matrix ones(size_t n, size_t m)
    {
        Matrix mat{zeros(n, m)};
        for (auto &row : mat)
        {
            for (auto &element : row)
            {
                element = 1;
            }
        }
        return mat;
    }

    Matrix random(size_t n, size_t m, double min, double max)
    {
        if (min > max)
            throw std::logic_error("min cannot be greater than max!");
        Matrix mat{zeros(n, m)};
        std::uniform_real_distribution<double> dist(min, max);
        std::default_random_engine rng;
        for (auto &row : mat)
        {
            for (auto &element : row)
            {
                element = dist(rng);
            }
        }
        return mat;
    }

    void show(const Matrix &matrix)
    {
        std::cout << std::fixed;
        std::cout << std::setprecision(3);
        for (auto &row : matrix)
        {
            for (auto &element : row)
            {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::setprecision(-1);
        std::cout << std::endl;
    }

    Matrix multiply(const Matrix &matrix, double c)
    {
        Matrix mat{matrix};
        for (auto &row : mat)
        {
            for (auto &element : row)
            {
                element *= c;
            }
        }
        return mat;
    }

    Matrix multiply(const Matrix &matrix1, const Matrix &matrix2)
    {
        size_t n1{matrix1.size()};
        size_t n2{matrix2.size()};
        if (n1 == 0 || n2 == 0)
            return matrix1;
        size_t m1{matrix1[0].size()};
        size_t m2{matrix2[0].size()};
        if (m1 != n2)
            throw std::logic_error("number of columns in matrix1 should be equal with number of rows in matrix2!");
        Matrix mat{zeros(n1, m2)};
        for (size_t i{}; i < n1; i++)
        {
            for (size_t j{}; j < m2; j++)
            {
                double element{};
                for (size_t k{}; k < m1; k++)
                {
                    element += matrix1[i][k] * matrix2[k][j];
                }
                mat[i][j] = element;
            }
        }
        return mat;
    }

    Matrix sum(const Matrix &matrix, double c)
    {
        size_t n{matrix.size()};
        if (n == 0)
            return matrix;
        Matrix mat{matrix};
        for (auto &row : mat)
        {
            for (auto &element : row)
            {
                element += c;
            }
        }
        return mat;
    }

    Matrix sum(const Matrix &matrix1, const Matrix &matrix2)
    {
        size_t n1{matrix1.size()};
        size_t n2{matrix2.size()};
        if (n1 == n2 && n1 == 0)
        {
            Matrix mat{};
            return mat;
        }
        if (n1 != n2 && (n1 == 0 || n2 == 0))
            throw std::logic_error("matrices should be the same dimention!");
        size_t m1{matrix1[0].size()};
        size_t m2{matrix2[0].size()};
        if (n1 != n2 || m1 != m2)
            throw std::logic_error("matrices should be the same dimention!");
        Matrix mat{zeros(n1, m1)};
        for (size_t i{}; i < n1; i++)
        {
            for (size_t j{}; j < m1; j++)
            {
                mat[i][j] = matrix1[i][j] + matrix2[i][j];
            }
        }
        return mat;
    }

    Matrix transpose(const Matrix &matrix)
    {
        size_t n{matrix.size()};
        if (n == 0)
            return matrix;
        size_t m{matrix[0].size()};
        Matrix mat{zeros(m, n)};
        for (size_t i{}; i < n; i++)
        {
            for (size_t j{}; j < m; j++)
            {
                mat[j][i] = matrix[i][j];
            }
        }
        return mat;
    }

    Matrix minor(const Matrix &matrix, size_t n, size_t m)
    {
        size_t _n{matrix.size()};
        size_t _m{matrix[0].size()};
        if (n >= _n || m >= _m || n < 0 || m < 0)
            throw std::logic_error("out of index!");
        Matrix mat{zeros(_n - 1, _m - 1)};
        for (size_t i{}; i < _n - 1; i++)
        {
            for (size_t j{}; j < _m - 1; j++)
            {
                size_t _i{i}, _j{j};
                if (i >= n)
                    _i++;
                if (j >= m)
                    _j++;
                mat[i][j] = matrix[_i][_j];
            }
        }
        return mat;
    }

    double determinant(const Matrix &matrix)
    {
        size_t n{matrix.size()};
        if (n == 0)
            return 1;
        size_t m{matrix[0].size()};
        if (n != m)
        {
            throw std::logic_error("matrix should be square!");
        }
        if (n == 1)
        {
            return matrix[0][0];
        }
        if (n == 2)
        {
            return (matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1]);
        }
        double deter{};
        for (size_t i{}; i < n; i++)
        {
            deter += cofactor(matrix, 1, i) * matrix[1][i];
        }
        return deter;
    }

    double cofactor(const Matrix &matrix, size_t i, size_t j)
    {
        return pow(-1, (i + j)) * determinant(minor(matrix, i, j));
    }

    Matrix cofactors_matrix(const Matrix &matrix)
    {
        size_t n{matrix.size()};
        size_t m{matrix[0].size()};
        Matrix mat{zeros(m, n)};
        for (size_t i{}; i < n; i++)
        {
            for (size_t j{}; j < m; j++)
            {
                mat[i][j] = cofactor(matrix, i, j);
            }
        }
        return mat;
    }

    Matrix adjunct(const Matrix &matrix)
    {
        return transpose(cofactors_matrix(matrix));
    }

    Matrix inverse(const Matrix &matrix)
    {
        size_t n{matrix.size()};
        if (n == 0)
            return matrix;
        size_t m{matrix[0].size()};
        if (n != m)
            throw std::logic_error("non-square matrices have no upper triangular form!");
        double det{determinant(matrix)};
        if (!det)
            throw std::logic_error("cannot calculate non-singular matrix inverse, determinant is zero!");
        return multiply(adjunct(matrix), (1 / det));
    }

    Matrix concatenate(const Matrix &matrix1, const Matrix &matrix2, int axis)
    {
        size_t n1{matrix1.size()};
        size_t n2{matrix2.size()};
        size_t m1{matrix1[0].size()};
        size_t m2{matrix2[0].size()};

        if (axis == 0)
        {
            if (m1 != m2)
                throw std::logic_error("number of columns in both matrices should be equal!");
            Matrix mat{zeros(n2 + n1, m1)};
            for (size_t i{}; i < n1 + n2; i++)
                if (i < n1)
                    for (size_t j{}; j < m1; j++)
                        mat[i][j] = matrix1[i][j];
                else
                    for (size_t j{}; j < m1; j++)
                        mat[i][j] = matrix2[i - n1][j];
            return mat;
        }
        else if (axis == 1)
        {
            if (n1 != n2)
                throw std::logic_error("number of rows in both matrices should be equal!");
            Matrix mat{zeros(n1, m1 + m2)};
            for (size_t i{}; i < n1; i++)
                for (size_t j{}; j < m1 + m2; j++)
                    if (j < m1)
                        mat[i][j] = matrix1[i][j];
                    else
                        mat[i][j] = matrix2[i][j - m1];
            return mat;
        }
        else
            throw std::logic_error("invalid axis!");
    }

    Matrix ero_swap(const Matrix &matrix, size_t r1, size_t r2)
    {
        size_t n{matrix.size()};
        size_t m{matrix[0].size()};
        if (r1 >= n || r2 >= n)
            throw std::logic_error("r1 or r2 inputs are out of range!");
        Matrix mat{matrix};
        for (size_t j{}; j < m; j++)
        {
            mat[r1][j] = matrix[r2][j];
            mat[r2][j] = matrix[r1][j];
        }
        return mat;
    }

    Matrix ero_multiply(const Matrix &matrix, size_t r, double c)
    {
        size_t n{matrix.size()};
        size_t m{matrix[0].size()};
        if (r >= n)
            throw std::logic_error("r input is out of range!");
        Matrix mat{matrix};
        for (size_t j{}; j < m; j++)
        {
            mat[r][j] *= c;
        }
        return mat;
    }

    Matrix ero_sum(const Matrix &matrix, size_t r1, double c, size_t r2)
    {
        size_t m{matrix[0].size()};
        Matrix mat{matrix};
        for (size_t j{}; j < m; j++)
        {
            mat[r2][j] += matrix[r1][j] * c;
        }
        return mat;
    }

    Matrix upper_triangular(const Matrix &matrix)
    {
        size_t n{matrix.size()};
        if (n == 0)
            return matrix;
        size_t m{matrix[0].size()};
        if (n != m)
            throw std::logic_error("non-square matrices have no upper triangular form!");
        Matrix mat{matrix};
        if (mat[0][0] == 0)
            mat = ero_swap(mat, 0, 1);
        for (size_t i{1}; i < n; i++)
        {
            for (size_t j{}; j < i; j++)
            {
                if (mat[j][j] == 0)
                    continue;
                double c{mat[i][j] / mat[j][j]};
                mat = ero_sum(mat, j, -c, i);
            }
            if (mat[i][i] == 0 && i != n - 1 && mat[i + 1][i])
            {
                mat = ero_swap(mat, i, i + 1);
                i -= 2;
            }
        }
        return mat;
    }
}
