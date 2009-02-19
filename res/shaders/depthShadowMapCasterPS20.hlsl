void depthShadowMapCasterFPMain(
	float2 depth			: TEXCOORD0,
	out float4 result		: COLOR)
	
{
	float finalDepth = depth.x;
	// just smear across all components 
	// therefore this one needs high individual channel precision
	result = float4(finalDepth, finalDepth, finalDepth, 1);
}