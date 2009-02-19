void depthShadowMapReceiverFPMain(
	float4 position			: POSITION,
	float4 shadowUV			: TEXCOORD0,
	float4 vertexColour		: COLOR,

	uniform sampler2D shadowMap : register(s0),
	uniform float inverseShadowmapSize,
	uniform float fixedDepthBias,
	uniform float gradientClamp,
	uniform float gradientScaleBias,
	
	out float4 result		: COLOR)
{
	// point on shadowmap
	shadowUV.xy = shadowUV.xy / shadowUV.w;
	float centerdepth = tex2D(shadowMap, shadowUV.xy).x;
    
    // gradient calculation
  	float pixeloffset = inverseShadowmapSize;
    float4 depths = float4( tex2D(shadowMap, shadowUV.xy + float2(-pixeloffset, 0)).x,
    	                    tex2D(shadowMap, shadowUV.xy + float2(+pixeloffset, 0)).x,
    	                    tex2D(shadowMap, shadowUV.xy + float2(0, -pixeloffset)).x,
    	                    tex2D(shadowMap, shadowUV.xy + float2(0, +pixeloffset)).x);							

	float2 differences = 2*abs( depths.yw - depths.xz );
	float gradient = min(gradientClamp, max(differences.x, differences.y));
	float gradientFactor = gradient * gradientScaleBias;

	// visibility function
	float depthAdjust = gradientFactor + (fixedDepthBias * centerdepth);
	float finalCenterDepth = centerdepth + depthAdjust;

	// shadowUV.z contains lightspace position of current object

	// use depths from prev, calculate diff
	depths += depthAdjust.xxxx;
	float final = (finalCenterDepth > shadowUV.z) ? 1.0f : 0.0f;
	final += (depths.x > shadowUV.z) ? 1.0f : 0.0f;
	final += (depths.y > shadowUV.z) ? 1.0f : 0.0f;
	final += (depths.z > shadowUV.z) ? 1.0f : 0.0f;
	final += (depths.w > shadowUV.z) ? 1.0f : 0.0f;
	
	final *= 0.1f;

	result = float4(vertexColour.xyz * final, 1);
}


