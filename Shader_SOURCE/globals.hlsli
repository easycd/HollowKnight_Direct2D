

cbuffer Transform : register(b0)
{
    row_major matrix WorldMatrix;
    row_major matrix ViewMatrix;
    row_major matrix ProjectionMatrix;
}


/// 1
//
///



cbuffer Grid : register(b2)
{
    float4 CameraPosition;
    float2 CameraScale;
    float2 Resolution;
}

cbuffer Animator : register(b3)
{
    float2 SpriteLeftTop;
    float2 SpriteSize;
    float2 SpriteOffset;
    float2 AtlasSize;
    uint animationType;
    float3 pad;
    uint Reverse;
}

// 충돌체 관련 
cbuffer Col : register(b4)
{
    
    int c_ColCount;
}

Texture2D albedoTexture : register(t0);
Texture2D atlasTexture : register(t12);

struct LightAttribute
{
    float4 color;
    float4 position;
    float4 direction;

    uint type;
    float radius;
    float angle;
    int pad;
};

StructuredBuffer<LightAttribute> lightsAttribute : register(t13);

SamplerState pointSampler : register(s0);
SamplerState anisotropicSampler : register(s1);

void CalculateLight2D(in out float4 lightColor, float3 position, int idx)
{
    if (0 == lightsAttribute[idx].type)
    {
        lightColor += lightsAttribute[idx].color;
    }
    else if (1 == lightsAttribute[idx].type)
    {
        float length = distance(position.xy, lightsAttribute[idx].position.xy);
        
        if (length < lightsAttribute[idx].radius)
        {
            float ratio = 1.0f - (length / lightsAttribute[idx].radius);
            lightColor += lightsAttribute[idx].color * ratio;
        }
    }
    else
    {
        
    }
}