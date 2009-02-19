void depthShadowMapReceiverVPMain(
	float4 position		: POSITION,
	float4 normal		: NORMAL,

	out float4 outPos			: POSITION,
	out float4 outColour		: COLOR,
	out float4 outShadowUV		: TEXCOORD0,

	uniform float4x4 world,
	uniform float4x4 worldIT,
	uniform float4x4 worldViewProj,
	uniform float4x4 texViewProj,
	uniform float4 lightPosition,
	uniform float4 lightColour,
	uniform float4 shadowDepthRange
	)
{
	float4 worldPos = mul(world, position);
	outPos = mul(worldViewProj, position);

	float3 worldNorm = mul(worldIT, normal).xyz;

	// calculate lighting (simple vertex lighting)
	float3 lightDir = normalize( lightPosition.xyz -  (worldPos.xyz * lightPosition.w));

	outColour = lightColour * max(dot(lightDir, worldNorm), 0.0);

	// calculate shadow map coords
	outShadowUV = mul(texViewProj, worldPos);
	// adjust by fixed depth bias, rescale into range
	outShadowUV.z = (outShadowUV.z - shadowDepthRange.x) * shadowDepthRange.w;
}

