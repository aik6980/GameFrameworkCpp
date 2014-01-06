#pragma once
#ifndef Noise_h__
#define Noise_h__

class CPerlinNoise
{
	CPerlinNoise();

	float	Noise3(float x, float y, float z);
private:
	void	InitPermTbl();
	
	// utility
	float	Fade(float t);
	float	Grad(int hash, float x, float y, float z);

	static int32_t	m_PermutationSeed[256];	// seed table for creating permutation table
	vector<int32_t> m_PermutationTbl;		// repeated 
};

#endif // Noise_h__