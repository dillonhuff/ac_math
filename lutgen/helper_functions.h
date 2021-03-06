/**************************************************************************
 *                                                                        *
 *  Algorithmic C (tm) Math Library                                       *
 *                                                                        *
 *  Software Version: 3.1                                                 *
 *                                                                        *
 *  Release Date    : Tue Nov  6 17:35:53 PST 2018                        *
 *  Release Type    : Production Release                                  *
 *  Release Build   : 3.1.2                                               *
 *                                                                        *
 *  Copyright , Mentor Graphics Corporation,                     *
 *                                                                        *
 *  All Rights Reserved.                                                  *
 *  
 **************************************************************************
 *  Licensed under the Apache License, Version 2.0 (the "License");       *
 *  you may not use this file except in compliance with the License.      * 
 *  You may obtain a copy of the License at                               *
 *                                                                        *
 *      http://www.apache.org/licenses/LICENSE-2.0                        *
 *                                                                        *
 *  Unless required by applicable law or agreed to in writing, software   * 
 *  distributed under the License is distributed on an "AS IS" BASIS,     * 
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or       *
 *  implied.                                                              * 
 *  See the License for the specific language governing permissions and   * 
 *  limitations under the License.                                        *
 **************************************************************************
 *                                                                        *
 *  The most recent version of this package is available at github.       *
 *                                                                        *
 *************************************************************************/
#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

double pwl_new(double x_in)
{
  unsigned index;
  double x_in_sc = (x_in - x_min) * prop_constant;
  if (x_in_sc < nsegments) {index = floor(x_in_sc);}
  else {index = nsegments - 1;}
  double y_out = m[index] * (x_in_sc - index) + c[index];
  return y_out;
}

// Function that returns max value and presence of negative elements in an array.
bool is_neg_max_array(const double input_array[nsegments], double &max_val)
{
  // This variable is set to true if even a single element is negative.
  bool is_neg = false;
  max_val = abs(input_array[0]);
  for(unsigned i = 1; i < nsegments; i++) {
    if(input_array[i] < 0) { is_neg = true; }
    if(abs(input_array[i]) > max_val) { max_val = input_array[i]; }
  }
  return is_neg;
}

// Make a number non-zero, useful for log calculations.
double make_non_zero(double input)
{
  if(input == 0) {input = 1;}
  return input;
}

//int m_int_bits = ceil(log2(make_non_zero(abs(m_max_val)))) + 2*int(is_neg_m) + 1;
int int_bits_calc(double val, bool S)
{
  return ceil(log2(make_non_zero(abs(val)))) + int(S) + 1;
}

// This function takes a double variable and performs an operation that mimics the quantization of the same double variable into an ac_fixed variable with "nfrac_bits" number of fractional
// bits and rounding turned on (AC_RND).
ac_fixed<128, 64, true> o_ac_f(double input, int nfrac_bits)
{
  return (ac_fixed<128, 64, true>)((double)rint(input * (1 << nfrac_bits)) * pow(2, (double)(-nfrac_bits)));
}

#endif // HELPER_FUNCTIONS_H
