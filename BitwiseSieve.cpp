//***********************************************
// Author: Fritz Ammon
// Date: 30 August 2014
// Sieve of Eratosthenes v3
// Revised: 4 February 2016
// Was not optimally utilizing all bits.
//***********************************************

#include <iostream>
#include <cstring>

using namespace std;

typedef unsigned long long ull;

void mark(ull a[], ull i);
bool check(ull a[], ull i);

const ull NUM_BYTES = 3920; // Must divide evenly with 4 so as not to corrupt mem.
const ull LAST_ODD = 2 * (NUM_BYTES * 8 - 1) + 3; // 2n + 3; just determining the last odd to refine algo.

int main()
{
	ull s[NUM_BYTES / 8];
    ull p, i;
    bool done = false;
    ull count = 1;

	if (NUM_BYTES % 8 != 0)
		return 0; // Must align to reach NUM_BYTES.

    memset(s, -1, NUM_BYTES); // Init all bits to 1 (-1 on unsigned).

    p = 3;
    while (!done)
    {
		i = p;
		if ((i *= i) > LAST_ODD) // Can stop once P^2 > last odd num.
		{
			done = true;
			continue;
		}

		while (i <= LAST_ODD)
		{
			mark(s, i); // Turn bit off.
			i += (2 * p); // Continue marking multiples of p.
		}

		while (!check(s, (p += 2)));
    }

    std::ios_base::sync_with_stdio(false); // Speed up output.

    cout << "2 (1)\n";
    for (ull c = 3; c <= LAST_ODD; c += 2)
    {
    	if (check(s, c))
			cout << c << " (" << ++count << ")\n";
	}

    return 0;
}

void mark(ull a[], ull i)
{
	// i - 3 comes from the formula 2n + 3 = i.
	// We use 2n + 3 = i instead of 2n + 1 = i because we start our list of odds with 3.
	// In other words, the odd number 3 should correspond to the index 0.
	// i is the actual odd number, so to get the index of that odd number in the bitwise index,
	// we need to rearrange the formula to i - 3 / 2 = n.
	// 128 comes from taking the index divided by 64, so that's (i - 3) / 2 / 64.
	// We need to divide by 64 in order to manipulate the bits of the correct element (ull) in the array.
    a[(i - 3) / 128] &= ~(static_cast<ull> (1) << (63 - (((i - 3) / 2) % 64)));
}

bool check(ull a[], ull i)
{
    return (a[(i - 3) / 128] & (static_cast<ull> (1) << (63 - (((i - 3) / 2) % 64)))) != 0;
}
