sampler2D baseMap   : register(s0);
sampler2D specMap   : register(s1);
sampler2D diffMap   : register(s2);
sampler2D bumpMap   : register(s3);
samplerCUBE cubeMap : register(s4);

struct PS_INPUT
{
	float4 Position  : POSITION0;
	float2 TexCoord  : TEXCOORD0;
	float3 Normal    : TEXCOORD1;
	float3 HalfAngle : TEXCOORD2;
	float3 LightDir  : TEXCOORD3;
	float3 cubeCoord : TEXCOORD4;	
};

float4 specNormDiffCubeLightingPS( PS_INPUT input, 
							       uniform float4 ambientClr,
                                   uniform float diffFactor,
							       uniform float specFactor,
							       uniform float cubeFactor,
							       uniform float specExp,
							       uniform float baseFactor
						         ) : COLOR0
{
	float4 cubeTex   = texCUBE(cubeMap, input.cubeCoord);
	float4 specTex   = tex2D(specMap, input.TexCoord);	
	float4 diffTex   = tex2D(diffMap, input.TexCoord);
	float4 baseTex   = tex2D(baseMap, input.TexCoord);
	float3 normTex   = tex2D(bumpMap, input.TexCoord);
	
	float3 normVec   = 2.0*(normTex-0.5);
	float  lit       = saturate(dot(normVec,input.LightDir));
	float  shine     = pow(dot(normVec, input.HalfAngle),specExp);
	
	float4 diffClr   = diffFactor * diffTex * lit;
	float4 specClr   = specFactor * shine * specTex * lit;
	float4 cubeClr   = cubeFactor * cubeTex;
	float4 baseClr   = baseFactor * baseTex * ambientClr;

	return baseClr + diffClr + specClr + cubeClr;
}

