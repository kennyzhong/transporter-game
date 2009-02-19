sampler2D baseMap : register(s0);
sampler2D specMap : register(s1);
sampler2D diffMap : register(s2);
sampler2D bumpMap : register(s3);

struct PS_INPUT
{
	float4 Position  : POSITION0;
	float2 TexCoord  : TEXCOORD0;
	float3 Normal    : TEXCOORD1;
	float3 HalfAngle : TEXCOORD2;
	float3 LightDir  : TEXCOORD3;
};

float4 perPixelLightingPS(PS_INPUT input,
                          	uniform float4 ambientClr,
                            uniform float diffFactor,
							uniform float specFactor,
							uniform float specExp,
							uniform float baseFactor) : COLOR0
{
	float3 halfAngle = normalize(input.HalfAngle);
	float4 specular  = tex2D(specMap, input.TexCoord);	
	float4 base      = tex2D(baseMap, input.TexCoord);
	float4 diffuse   = tex2D(diffMap, input.TexCoord);
	float3 normal    = 2*(tex2D(bumpMap, input.TexCoord)-0.5);
	float lit        = saturate(dot(normal, normalize(input.LightDir)));
	
	float4 diff    = diffFactor * diffuse * lit;
	float4 spec    = specFactor * pow(dot(normal, halfAngle),specExp) * specular * lit;
	float4 color   = baseFactor * base * ambientClr;
	
	return color + diff + spec;
}

