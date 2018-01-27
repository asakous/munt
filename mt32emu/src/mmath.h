/* Copyright (C) 2003, 2004, 2005, 2006, 2008, 2009 Dean Beeler, Jerome Fisher
 * Copyright (C) 2011-2017 Dean Beeler, Jerome Fisher, Sergey V. Mikayev
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 2.1 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MT32EMU_MMATH_H
#define MT32EMU_MMATH_H

#include <cmath>

#ifdef HAVE_NEON
#include "math_neon.h"
#endif

namespace MT32Emu {

// Mathematical constants
const double DOUBLE_PI = 3.141592653589793;
const double DOUBLE_LN_10 = 2.302585092994046;
const float FLOAT_PI = 3.1415927f;
const float FLOAT_2PI = 6.2831853f;
const float FLOAT_LN_2 = 0.6931472f;
const float FLOAT_LN_10 = 2.3025851f;

static inline float POWF(float x, float y) {
#ifdef HAVE_NEON
	return powf_neon(x, y);
#else
	return pow(x, y);
#endif
}

static inline float EXPF(float x) {
#ifdef HAVE_NEON
	return expf_neon(x);
#else
	return exp(x);
#endif
}

static inline float EXP2F(float x) {
#ifdef __APPLE__
	// on OSX exp2f() is 1.59 times faster than "exp() and the multiplication with FLOAT_LN_2"
	return exp2f(x);
#else
	#ifdef HAVE_NEON
		return expf_neon(FLOAT_LN_2*x);
	#else
		return exp(FLOAT_LN_2 * x);
	#endif
#endif
}

static inline float EXP10F(float x) {
#ifdef HAVE_NEON
	return expf_neon(FLOAT_LN_10 * x);
#else
	return exp(FLOAT_LN_10 * x);
#endif
}

static inline float LOGF(float x) {
#ifdef HAVE_NEON
	return logf_neon(x);
#else
	return log(x);
#endif
}

static inline float LOG2F(float x) {
#ifdef HAVE_NEON
	return logf_neon(x) / FLOAT_LN_2;
#else
	return log(x) / FLOAT_LN_2;
#endif
}

static inline float LOG10F(float x) {
#ifdef HAVE_NEON
	return log10f_neon(x);
#else
	return log10(x);
#endif
}

} // namespace MT32Emu

#endif // #ifndef MT32EMU_MMATH_H
