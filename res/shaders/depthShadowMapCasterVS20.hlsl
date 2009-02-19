void depthShadowMapCasterVPMain(
	float4 position			: POSITION,
	out float4 outPos		: POSITION,
	out float2 outDepth		: TEXCOORD0,

	uniform float4x4 worldViewProj,
	uniform float4 texelOffsets,
	uniform float4 depthRange
	)
{
	outPos = mul(worldViewProj, position);

	// fix pixel / texel alignment
	outPos.xy += texelOffsets.zw * outPos.w;
	// linear depth storage
	// offset / scale range output
	outDepth.x = (outPos.z - depthRange.x) * depthRange.w;
	outDepth.y = outPos.w;
}