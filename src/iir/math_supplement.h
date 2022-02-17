/**
 * License: MIT License (http://www.opensource.org/licenses/mit-license.php)
 *
 * Copyright (c) 2009 by Vinnie Falco
 * Copyright (c) 2012 by Bernd Porr
 * Copyright (c) 2022 by elegracer
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 **/

#pragma once

#include <complex>
#include <limits>

#include <cmath>

namespace IIR {

constexpr double double_pi = M_PI;
constexpr double double_pi_2 = M_PI_2;
constexpr double double_ln_2 = M_LN2;
constexpr double double_ln_10 = M_LN10;

using complex_t = std::complex<double>;
using complex_pair_t = std::pair<complex_t, complex_t>;

template<typename Real>
inline std::complex<Real> solve_quadratic_1(Real a, Real b, Real c) {
    return (-b + std::sqrt(std::complex<Real>(b * b - 4.0 * a * c, 0.0))) / (2.0 * a);
}

template<typename Real>
inline std::complex<Real> solve_quadratic_2(Real a, Real b, Real c) {
    return (-b - std::sqrt(std::complex<Real>(b * b - 4.0 * a * c, 0.0))) / (2.0 * a);
}

inline const complex_t infinity() {
    return complex_t(std::numeric_limits<double>::infinity());
}

inline const complex_t adjust_imag(const complex_t &c) {
    if (std::abs(c.imag()) < 1e-30) {
        return complex_t(c.real(), 0);
    } else {
        return c;
    }
}

template<typename TA, typename TB>
inline std::complex<TA> addmul(const std::complex<TA> &c, TA v, const std::complex<TB> &c1) {
    return std::complex<TA>(c.real() + v * c1.real(), c.imag() + v * c1.imag());
}

template<typename T>
inline std::complex<T> recip(const std::complex<T> &c) {
    T n = 1.0 / std::norm(c);
    return std::complex<T>(n * c.real(), n * c.imag());
}

template<typename T>
inline T asinh(T x) {
    return std::log(x + std::sqrt(x * x + 1));
}

template<typename T>
inline T acosh(T x) {
    return std::log(x + std::sqrt(x * x - 1));
}

template<typename T>
inline bool is_nan(T v) {
    return ! (v == v);
}

template<>
inline bool is_nan<complex_t>(complex_t v) {
    return is_nan(v.real()) || is_nan(v.imag());
}

} // namespace IIR
