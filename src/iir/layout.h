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

#include "common.h"

#include "math_supplement.h"
#include "types.h"

/**
 * Describes a filter as a collection of poles and zeros along with
 * normalization information to achieve a specified gain at a specified
 * frequency. The poles and zeros may lie either in the s or the z plane.
 **/
namespace IIR {

static const char errPoleisNaN[] = "Pole to add is NaN.";
static const char errZeroisNaN[] = "Zero to add is NaN.";

static const char errCantAdd2ndOrder[] = "Can't add 2nd order after a 1st order filter.";

static const char errPolesNotComplexConj[] = "Poles not complex conjugate.";
static const char errZerosNotComplexConj[] = "Zeros not complex conjugate.";

static const char pairIndexOutOfBounds[] = "Pair index out of bounds.";

/**
 * Base uses pointers to reduce template instantiations
 **/
class LayoutBase {
public:
    LayoutBase() : m_numPoles(0), m_maxPoles(0) {}

    LayoutBase(int maxPoles, PoleZeroPair *pairs)
        : m_numPoles(0), m_maxPoles(maxPoles), m_pair(pairs) {}

    void setStorage(const LayoutBase &other) {
        m_numPoles = 0;
        m_maxPoles = other.m_maxPoles;
        m_pair = other.m_pair;
    }

    void reset() { m_numPoles = 0; }

    int getNumPoles() const { return m_numPoles; }

    int getMaxPoles() const { return m_maxPoles; }

    void add(const complex_t &pole, const complex_t &zero) {
        if (m_numPoles & 1) {
            throw_invalid_argument(errCantAdd2ndOrder);
        }
        if (IIR::is_nan(pole)) {
            throw_invalid_argument(errPoleisNaN);
        }
        if (IIR::is_nan(zero)) {
            throw_invalid_argument(errZeroisNaN);
        }
        m_pair[m_numPoles / 2] = PoleZeroPair(pole, zero);
        ++m_numPoles;
    }

    void addPoleZeroConjugatePairs(const complex_t pole, const complex_t zero) {
        if (m_numPoles & 1) {
            throw_invalid_argument(errCantAdd2ndOrder);
        }
        if (IIR::is_nan(pole)) {
            throw_invalid_argument(errPoleisNaN);
        }
        if (IIR::is_nan(zero)) {
            throw_invalid_argument(errZeroisNaN);
        }
        m_pair[m_numPoles / 2] = PoleZeroPair(pole, zero, std::conj(pole), std::conj(zero));
        m_numPoles += 2;
    }

    void add(const ComplexPair &poles, const ComplexPair &zeros) {
        if (m_numPoles & 1) {
            throw_invalid_argument(errCantAdd2ndOrder);
        }
        if (! poles.isMatchedPair()) {
            throw_invalid_argument(errPolesNotComplexConj);
        }
        if (! zeros.isMatchedPair()) {
            throw_invalid_argument(errZerosNotComplexConj);
        }
        m_pair[m_numPoles / 2] = PoleZeroPair(poles.first, zeros.first, poles.second, zeros.second);
        m_numPoles += 2;
    }

    const PoleZeroPair &getPair(int pairIndex) const {
        if ((pairIndex < 0) || (pairIndex >= (m_numPoles + 1) / 2)) {
            throw_invalid_argument(pairIndexOutOfBounds);
        }
        return m_pair[pairIndex];
    }

    const PoleZeroPair &operator[](int pairIndex) const { return getPair(pairIndex); }

    double getNormalW() const { return m_normalW; }

    double getNormalGain() const { return m_normalGain; }

    void setNormal(double w, double g) {
        m_normalW = w;
        m_normalGain = g;
    }

private:
    int m_numPoles;
    int m_maxPoles;
    PoleZeroPair *m_pair;
    double m_normalW = 0;
    double m_normalGain = 1;
};

//------------------------------------------------------------------------------

/**
 * Storage for Layout
 **/
template<int MaxPoles>
class Layout {
public:
    operator LayoutBase() { return LayoutBase(MaxPoles, m_pairs); }

private:
    PoleZeroPair m_pairs[(MaxPoles + 1) / 2];
};

} // namespace IIR
