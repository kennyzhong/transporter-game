float4x4 matViewProjection;
float3 fvEyePosition;
float4 fvLightPosition;

struct VS_INPUT
{
	float4 Position : POSITION0;
	float2 TexCoord : TEXCOORD0;
	float3 Normal   : NORMAL;
};

struct VS_OUTPUT
{
	float4 Position  : POSITION0;
	float2 TexCoord  : TEXCOORD0;
	float3 Normal    : TEXCOORD1;
	float3 HalfAngle : TEXCOORD2;
	float3 LightDir  : TEXCOORD3;
	float3 cubeCoord : TEXCOORD4;
};

VS_OUTPUT cubeLightingVS(VS_INPUT input)
{
	VS_OUTPUT output;
	
	float3 eyeDir     = input.Position - fvEyePosition;
	
	output.Position   = mul(matViewProjection, input.Position);
	output.TexCoord   = input.TexCoord;
	output.Normal     = input.Normal;
	output.LightDir   = normalize(fvLightPosition - input.Position);
	output.HalfAngle  = normalize(output.LightDir +  eyeDir);
	output.cubeCoord  = normalize(reflect(eyeDir,input.Normal));
	
	return output;
}

