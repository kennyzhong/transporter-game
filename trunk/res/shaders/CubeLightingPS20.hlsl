sampler2D baseMap   : register(s0);
samplerCUBE cubeMap : register(s1);

struct PS_INPUT
{
	float4 Position  : POSITION0;
	float2 TexCoord  : TEXCOORD0;
	float3 Normal    : TEXCOORD1;
	float3 HalfAngle : TEXCOORD2;
	float3 LightDir  : TEXCOORD3;	
	float3 cubeCoord : TEXCOORD4;
};

float4 cubeLightingPS( PS_INPUT input, 
					   uniform float4 ambientClr,
                       uniform float4 diffColor,
					   uniform float4 specColor,
					   uniform float specExp,
					   uniform float specFactor,
					   uniform float cubeFactor,
					   uniform float baseFactor
					 ) : COLOR0
{
	float4 baseTex   = tex2D(baseMap, input.TexCoord);
	float4 cubeTex   = texCUBE(cubeMap, input.cubeCoord);
	
	float  lit       = saturate(dot(input.Normal,input.LightDir));
	float  shine     = pow(dot(input.Normal, input.HalfAngle),specExp);
	
	float4 diffClr   = diffColor * lit;
	float4 specClr   = specFactor * shine * specColor * lit;
	float4 baseClr   = baseFactor * baseTex * ambientClr;
	float4 cubeClr   = cubeFactor * cubeTex;

	return baseClr + diffClr + specClr + cubeClr;
}

