/*
MIT License

Copyright (c) 2019 Math Nerd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <iostream>
#include <NTL/RR.h>

// Sum of divisors of a positive integer.
NTL::ZZ sum_of_divisors(NTL::ZZ number);

int main()
{
    NTL::RR harmonic_number{ 1 }; // Holds H_n.

    NTL::ZZ number{ 1 };
    NTL::ZZ MAX_VALUE{ 1000000000 }; // Go up to 1,000,000,000.

    constexpr bool VERBOSE{ true };
    
    for( ; number <= MAX_VALUE; ++number )
    {
        if( NTL::MakeRR(sum_of_divisors(number), 0)
          > harmonic_number
            + NTL::exp(harmonic_number)*NTL::log(harmonic_number) )
        {   // If Lagarias's Inequality fails, exit loop.
            std::cout << "Failed at n = " << number << '\n';

            break;
        }

        if( VERBOSE && NTL::divide(number, 10000) )
        {   // Display verification status every 10,000 integers.
            std::cout << "Verified up to " << number << '\n';
        }

        // Add next reciprocal to harmonic number.
        harmonic_number += 1 / NTL::MakeRR(number + 1, 0);
    }

    return EXIT_SUCCESS;
}


NTL::ZZ sum_of_divisors(NTL::ZZ number)
{
    NTL::ZZ maximum{ NTL::SqrRoot(number) + 1 }; // Need only go up to sqrt(number).
    NTL::ZZ sum{ 0 };

    for( NTL::ZZ idx{ 1 }; idx < maximum; ++idx )
    {
        if( NTL::divide(number, idx) )
        {
            if( idx == number / idx )
            {   // prevents double counting the square root, if number = idx^2
                sum += idx;
            }
            else
            {   // Add idx as well as its companion number/idx, as it is also a divisor.
                sum += idx + (number / idx);
            }
        }
    }

    return sum;
}
