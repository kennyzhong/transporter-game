sampler2D baseMap   : register(s0);
sampler2D bumpMap   : register(s1);

struct PS_INPUT
{
	float4 Position  : POSITION0;
	float2 TexCoord  : TEXCOORD0;
	float3 Normal    : TEXCOORD1;
	float3 HalfAngle : TEXCOORD2;
	float3 LightDir  : TEXCOORD3;	
};

float4 normLightingPS( PS_INPUT input, 
					   uniform float4 ambientClr,
                       uniform float4 diffColor,
					   uniform float4 specColor,
					   uniform float specExp,
					   uniform float baseFactor
					 ) : COLOR0
{
	float4 baseTex   = tex2D(baseMap, input.TexCoord);
	float3 normTex   = tex2D(bumpMap, input.TexCoord);
	
	float3 normVec   = 2.0*(normTex-0.5);
	float  lit       = saturate(dot(normVec,input.LightDir));
	float  shine     = pow(dot(normVec, input.HalfAngle),specExp);
	
	float4 diffClr   = diffColor * lit;
	float4 specClr   = shine * specColor * lit;
	float4 baseClr   = baseFactor * baseTex * ambientClr;

	return 0.5*(baseClr + diffClr) + specClr;
}

