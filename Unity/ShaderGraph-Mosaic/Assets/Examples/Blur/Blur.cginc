void Blur_float(UnityTexture2D _texture, float texelW, float texelH, float2 uv, UnitySamplerState _sampler, float sigma, float scale, out float3 _out)
{       
    float count = 0.0;
    int kernelSize = int(round(sigma * 3 * 2 + 1)) | 1;
    sigma = 0;
    float rate = sign(sigma);
    sigma = max(0.01, sigma);
    float scale2X = lerp(0,-0.5 / (sigma * sigma), rate);    
    _out.rgb = float3(0, 0, 0);
    for (int x = -kernelSize / 2; x <= kernelSize / 2; x++)
    {
        for (int y = -kernelSize / 2; y <= kernelSize / 2; y++)
        {
            float weight = exp(scale2X * x * y);
            _out.rgb += weight * SAMPLE_TEXTURE2D(_texture, _sampler, uv + scale * float2(x * texelW, y * texelH)).rgb;
            count += weight;
        }
    }
    _out.rgb /= count;
}