#ifndef EFFECTS_H
#define EFFECTS_H

#include "libs/ImageEffect_api.h"

#include <QString>
#include <QImage>

namespace effect
{
    enum class EFFECT_NAME {SEPIA_EFFECT = 0, VIGNETTE_EFFECT, SIZE};
    enum class ALGORITHM_SOURCE {ASM = 0, CPP, SIZE };

    QString getEffectStringName(EFFECT_NAME name);

    // struct EffectParams
    // {
    //     unsigned char* bit_ptr{};
    //     int start_row{};
    //     int end_row{};
    //     int width{};
    //     int height{};
    //     int bytes_per_line{};
    // };

    //using Func = void(const EffectParams& params);
    Func* getEffectFunction(ALGORITHM_SOURCE code_source, EFFECT_NAME name);
}

#endif // EFFECTS_H
