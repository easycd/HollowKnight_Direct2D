
//struct Vertex[3]
//{
//    Vector3 pos;
//    Vector4 color;
//};

//VertexShader에 들어오는 데이터
struct VSIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
};

//VertexShader에 나가는 데이터
struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
};

VSOut main(VSIn In)
{
    VSOut Out = (VSOut)0.0f;
        
    Out.Pos = float4(In.Pos, 1.0f);
    Out.Color = In.Color;
    
    return Out;
}