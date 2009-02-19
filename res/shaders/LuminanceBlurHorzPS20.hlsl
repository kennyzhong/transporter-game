sampler RT: register(s0);

static const float2 pos[19] =
{
	-5,0,
	-4, 0,
	-3.0, 0,
	-2.1, 0,
	-1.5, 0,
	-1.05, 0,
	-0.675, 0,
	-0.35, 0,
	-0.15, 0,
	0, 0,        
	0.15, 0, 
	0.35, 0, 
	0.675, 0, 
	1.05, 0, 
	1.5, 0, 
	2.1, 0,
	3.0, 0,    
	4, 0,
	5, 0
};

float4 main( float2 texCoord: TEXCOORD0 ) : COLOR 
{
   float3 sum = tex2D(RT, texCoord);   					   
   
   for (int i = 0; i < 19; i++)
   {
      sum += tex2D(RT, texCoord + pos[i] * 0.00425);
   }
     
   float brg = dot(sum,sum)*0.00175;
   return float4(0.075*sum,brg);
}
