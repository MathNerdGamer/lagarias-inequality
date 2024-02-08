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

        if( VERBOSE && NTL::divide(number, 100000) )
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
            auto other_divisor = number / idx;
            
            sum += idx;

            if( idx != other_divisor )
            {   // prevents double counting the square root, if number = idx^2
                sum += other_divisor;
            }
        }
    }

    return sum;
}
