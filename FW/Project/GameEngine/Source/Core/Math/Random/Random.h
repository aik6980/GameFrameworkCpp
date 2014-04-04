#ifndef Random_h__
#define Random_h__

#include <stdint.h>
#include <random>

struct MT19937 
{
public:
	// This is equivalent to srand().
	static void seed(uint64_t new_seed = std::mt19937_64::default_seed) 
	{
		rng.seed(new_seed);
	}

	// This is equivalent to rand().
	static uint64_t get()
	{
		return rng();
	}
private:
	static std::mt19937_64 rng;
};

#endif // Random_h__
