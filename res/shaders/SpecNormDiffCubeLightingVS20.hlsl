float4x4 matViewProjection;
float3 fvEyePosition;
float4 fvLightPosition;

struct VS_INPUT
{
	float4 Position : POSITION0;
	float2 TexCoord : TEXCOORD0;
	float3 Normal   : NORMAL;
	float3 Tangent  : TANGENT;
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

VS_OUTPUT specNormDiffCubeLightingVS(VS_INPUT input)
{
	VS_OUTPUT output;
	
	float3 lightDir   = normalize(fvLightPosition.xyz - input.Position.xyz);
	float3 binormal   = cross(input.Tangent, input.Normal);
	float3x3 rotation = float3x3(input.Tangent, binormal, input.Normal);
	float3 eyeDir     = input.Position - fvEyePosition;
	float3 halfAngle  = normalize(eyeDir + lightDir);
	
	output.Position   = mul(matViewProjection, input.Position);
	output.TexCoord   = input.TexCoord;
	output.Normal     = input.Normal;
	output.LightDir   = normalize(mul(rotation, lightDir));
	output.HalfAngle  = normalize(mul(rotation, halfAngle));
	output.cubeCoord  = normalize(reflect(eyeDir,input.Normal));	
	
	return output;
}

