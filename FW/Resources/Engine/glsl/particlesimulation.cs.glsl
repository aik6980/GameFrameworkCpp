// layout (binding = 2) requires 420
// compute shader requires 430
#version 430 core

// uniforms
layout (binding = 0) uniform CB00
{
    mat4x4 ViewXf;
    mat4x4 ProjectionXf;
    mat4x4 ViewIXf;
    mat4x4 ProjectionIXf;
    mat4x4 ViewProjectionIXf;
}CbViewCommon;

layout (binding = 1) uniform CB01
{
	vec4	GameTimerData;
}CbSceneCommon;

// buffers
struct Particle
{
	vec4	Position_Id;
	vec3	Velocity;
	vec2	Begintime_Lifetime;
};

layout (std430, binding = 0) buffer SSBO00 
{
	Particle Data[];
} g_ParticleInstances;

layout (std430, binding = 1) buffer SSBO01 
{
	uint Data[];
} g_ParticleDeadlist;

struct ParticleAliveID
{
	uint 	Id;
	float	DistanceFromCamera;
};

layout (std430, binding = 2) buffer SSBO02
{
	ParticleAliveID Data[];
} g_ParticleSortlist;

layout (binding = 0, offset = 0) uniform atomic_uint g_LastDeadParticleID;
layout (binding = 0, offset = 4) uniform atomic_uint g_LastAliveParticleID;


// functions
vec3 CameraPosition()
{
	return CbViewCommon.ViewIXf[3].xyz;
}

float CurrentTime()
{
	return CbSceneCommon.GameTimerData.x;
}

float DeltaTime()
{
	return CbSceneCommon.GameTimerData.y;
}

bool Particle_Active(Particle p)
{
	return (p.Position_Id.w != -1);
}

void Particle_MarkInactive(inout Particle p)
{
	p.Position_Id.w = -1;
}

bool Particle_Alive(Particle p, float t)
{
	return (p.Begintime_Lifetime.x <= t) && (p.Begintime_Lifetime.x + p.Begintime_Lifetime.y > t);
}

void Particle_SimulationStep(inout Particle p)
{
	p.Velocity 			+= -9.81 * DeltaTime() * 0.01;
	p.Position_Id.xyz 	+= p.Velocity * DeltaTime();
}

void AddToSortList(uint pid, Particle p)
{
	uint id = atomicCounterIncrement(g_LastAliveParticleID);

	ParticleAliveID aliveID;
	aliveID.Id = pid;
	aliveID.DistanceFromCamera = length( p.Position_Id.xyz - CameraPosition());
	
	g_ParticleSortlist.Data[id] = aliveID;
}

void AddToDeadList(uint pid, inout Particle p)
{
	uint id = atomicCounterIncrement(g_LastDeadParticleID);
	
	// mark this particle inactive
	Particle_MarkInactive(p);
	
	g_ParticleDeadlist.Data[id] = pid;
}

// Input layout qualifier declaring a 16x 16(x 1)local
// workgroup size
layout (local_size_x = 16) in;
void main()
{
	uint pid = gl_GlobalInvocationID.x;
	Particle particle = g_ParticleInstances.Data[pid];
	
	if(Particle_Active(particle))
	{
		float currTime = CurrentTime();
		if(Particle_Alive(particle, currTime))
		{
			// simulation
			Particle_SimulationStep(particle);
			// add to sort list
			AddToSortList(pid, particle);
		}
		else
		{
			// add to dead list
			AddToDeadList(pid, particle);
		}
		
		// update particle state
		g_ParticleInstances.Data[pid] = particle;
	}
}

















