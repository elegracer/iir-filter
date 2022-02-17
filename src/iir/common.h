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

#include <cstdlib>

#include <cassert>
#include <cfloat>
#include <cmath>
#include <complex>
#include <cstring>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

static const char orderTooHigh[] =
    "Requested order is too high. Provide a higher order for the template.";

#define DEFAULT_FILTER_ORDER 4

/**
 * @brief Throw invalid argument exception if exceptions are enabled, otherwise abort.
 *
 * @param msg Error message
 */
inline void throw_invalid_argument(const char *msg) {

#if __cpp_exceptions
    throw std::invalid_argument(msg);
#else
    fprintf(stderr, "%s\n", msg);
    // (void) msg; // Discard parameter
    // abort();
#endif
}
