#pragma once

extern "C"
{
    struct EffectParams
    {
        unsigned char* bit_ptr{};
        int start_row{};
        int end_row{};
        int width{};
        int height{};
        int bytes_per_line{};
    };

    using Func = void(const EffectParams* params);

    __declspec(dllexport) void doSepiaEffectCPP(const EffectParams* params);
    __declspec(dllexport) void doVignetteEffectCPP(const EffectParams* params);
}