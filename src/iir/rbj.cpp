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

#include "rbj.h"

#include "common.h"

namespace IIR {

namespace RBJ {

void LowPass::setupN(double cutoffFrequency, double q) {
    double const w0 = 2 * double_pi * cutoffFrequency;
    double const cs = std::cos(w0);
    double const sn = std::sin(w0);
    double const AL = sn / (2 * q);
    double const b0 = (1 - cs) / 2;
    double const b1 = 1 - cs;
    double const b2 = (1 - cs) / 2;
    double const a0 = 1 + AL;
    double const a1 = -2 * cs;
    double const a2 = 1 - AL;
    setCoefficients(a0, a1, a2, b0, b1, b2);
}

void HighPass::setupN(double cutoffFrequency, double q) {
    double const w0 = 2 * double_pi * cutoffFrequency;
    double const cs = std::cos(w0);
    double const sn = std::sin(w0);
    double const AL = sn / (2 * q);
    double const b0 = (1 + cs) / 2;
    double const b1 = -(1 + cs);
    double const b2 = (1 + cs) / 2;
    double const a0 = 1 + AL;
    double const a1 = -2 * cs;
    double const a2 = 1 - AL;
    setCoefficients(a0, a1, a2, b0, b1, b2);
}

void BandPass1::setupN(double centerFrequency, double bandWidth) {
    double const w0 = 2 * double_pi * centerFrequency;
    double const cs = std::cos(w0);
    double const sn = std::sin(w0);
    double const AL = sn / (2 * bandWidth);
    double const b0 = bandWidth * AL; // sn / 2;
    double const b1 = 0;
    double const b2 = -bandWidth * AL; //-sn / 2;
    double const a0 = 1 + AL;
    double const a1 = -2 * cs;
    double const a2 = 1 - AL;
    setCoefficients(a0, a1, a2, b0, b1, b2);
}

void BandPass2::setupN(double centerFrequency, double bandWidth) {
    double const w0 = 2 * double_pi * centerFrequency;
    double const cs = std::cos(w0);
    double const sn = std::sin(w0);
    double const AL = sn / (2 * bandWidth);
    double const b0 = AL;
    double const b1 = 0;
    double const b2 = -AL;
    double const a0 = 1 + AL;
    double const a1 = -2 * cs;
    double const a2 = 1 - AL;
    setCoefficients(a0, a1, a2, b0, b1, b2);
}

void BandStop::setupN(double centerFrequency, double bandWidth) {
    double const w0 = 2 * double_pi * centerFrequency;
    double const cs = std::cos(w0);
    double const sn = std::sin(w0);
    double const AL = sn / (2 * bandWidth);
    double const b0 = 1;
    double const b1 = -2 * cs;
    double const b2 = 1;
    double const a0 = 1 + AL;
    double const a1 = -2 * cs;
    double const a2 = 1 - AL;
    setCoefficients(a0, a1, a2, b0, b1, b2);
}

void IIRNotch::setupN(double centerFrequency, double q_factor) {
    double const w0 = 2 * double_pi * centerFrequency;
    double const cs = std::cos(w0);
    double const r = std::exp(-(w0 / 2) / q_factor);
    double const b0 = 1;
    double const b1 = -2 * cs;
    double const b2 = 1;
    double const a0 = 1;
    double const a1 = -2 * r * cs;
    double const a2 = r * r;
    setCoefficients(a0, a1, a2, b0, b1, b2);
}

void LowShelf::setupN(double cutoffFrequency, double gainDb, double shelfSlope) {
    double const A = std::pow(10, gainDb / 40);
    double const w0 = 2 * double_pi * cutoffFrequency;
    double const cs = std::cos(w0);
    double const sn = std::sin(w0);
    double const AL = sn / 2 * std::sqrt((A + 1 / A) * (1 / shelfSlope - 1) + 2);
    double const sq = 2 * std::sqrt(A) * AL;
    double const b0 = A * ((A + 1) - (A - 1) * cs + sq);
    double const b1 = 2 * A * ((A - 1) - (A + 1) * cs);
    double const b2 = A * ((A + 1) - (A - 1) * cs - sq);
    double const a0 = (A + 1) + (A - 1) * cs + sq;
    double const a1 = -2 * ((A - 1) + (A + 1) * cs);
    double const a2 = (A + 1) + (A - 1) * cs - sq;
    setCoefficients(a0, a1, a2, b0, b1, b2);
}


void HighShelf::setupN(double cutoffFrequency, double gainDb, double shelfSlope) {
    double const A = std::pow(10, gainDb / 40);
    double const w0 = 2 * double_pi * cutoffFrequency;
    double const cs = std::cos(w0);
    double const sn = std::sin(w0);
    double const AL = sn / 2 * std::sqrt((A + 1 / A) * (1 / shelfSlope - 1) + 2);
    double const sq = 2 * std::sqrt(A) * AL;
    double const b0 = A * ((A + 1) + (A - 1) * cs + sq);
    double const b1 = -2 * A * ((A - 1) + (A + 1) * cs);
    double const b2 = A * ((A + 1) + (A - 1) * cs - sq);
    double const a0 = (A + 1) - (A - 1) * cs + sq;
    double const a1 = 2 * ((A - 1) - (A + 1) * cs);
    double const a2 = (A + 1) - (A - 1) * cs - sq;
    setCoefficients(a0, a1, a2, b0, b1, b2);
}


void BandShelf::setupN(double centerFrequency, double gainDb, double bandWidth) {
    double const A = std::pow(10, gainDb / 40);
    double const w0 = 2 * double_pi * centerFrequency;
    double const cs = std::cos(w0);
    double const sn = std::sin(w0);
    double const AL = sn * std::sinh(double_ln_2 / 2 * bandWidth * w0 / sn);
    if (IIR::is_nan(AL)) {
        throw_invalid_argument("No solution available for these parameters.");
    }
    double const b0 = 1 + AL * A;
    double const b1 = -2 * cs;
    double const b2 = 1 - AL * A;
    double const a0 = 1 + AL / A;
    double const a1 = -2 * cs;
    double const a2 = 1 - AL / A;
    setCoefficients(a0, a1, a2, b0, b1, b2);
}

void AllPass::setupN(double phaseFrequency, double q) {
    double const w0 = 2 * double_pi * phaseFrequency;
    double const cs = std::cos(w0);
    double const sn = std::sin(w0);
    double const AL = sn / (2 * q);
    double const b0 = 1 - AL;
    double const b1 = -2 * cs;
    double const b2 = 1 + AL;
    double const a0 = 1 + AL;
    double const a1 = -2 * cs;
    double const a2 = 1 - AL;
    setCoefficients(a0, a1, a2, b0, b1, b2);
}

} // namespace RBJ

} // namespace IIR
