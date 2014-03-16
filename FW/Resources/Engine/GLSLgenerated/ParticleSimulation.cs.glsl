// layout (binding = 2) requires 420
// compute shader requires 430
#version 430 core

// Input layout qualifier declaring a 16x 16(x 1)local
// workgroup size
layout (local_size_x =16, local_size_y = 16) in;
void main()
{
	//Do nothing.
}