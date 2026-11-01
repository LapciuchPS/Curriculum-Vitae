#include "effects.h"

#include <array>
#include <algorithm>

#include <QImage>

namespace effect
{
    QString getEffectStringName(EFFECT_NAME name)
    {
        switch(name)
        {
        case EFFECT_NAME::SEPIA_EFFECT: return "Serpia effect";
        case EFFECT_NAME::VIGNETTE_EFFECT: return "Vignette effect";

        default: return "Unknown effect";
        }
    }

    namespace
    {
        int clampColour(int colour)
        {
            int clamped_colour = std::clamp(colour, 0, 255);
            return clamped_colour;
        }

        QImage doSepiaEffectASM(QImage original_image)
        {

            return QImage{};
        };

        QImage doVignetteEffectASM(QImage original_image)
        {
            return QImage{};
        };

        QImage doSepiaEffectCPP(QImage original_image)
        {

            uchar* bit_ptr = original_image.bits();
            int bytes_per_line = original_image.bytesPerLine();

            for(int i=0; i<original_image.height(); ++i)
                for(int j=0; j<original_image.width(); ++j)
                {
                    int offset =  i*bytes_per_line + j*4;

                    uchar oryginal_b = bit_ptr[offset];
                    uchar oryginal_g = bit_ptr[offset + 1];
                    uchar oryginal_r = bit_ptr[offset + 2];

                    int new_b = 0.272*oryginal_r + 0.534*oryginal_g + 0.131*oryginal_b;
                    int new_g = 0.349*oryginal_r + 0.686*oryginal_g + 0.168*oryginal_b;
                    int new_r = 0.393*oryginal_r + 0.769*oryginal_g + 0.189*oryginal_b;

                    bit_ptr[offset] = clampColour(new_b);
                    bit_ptr[offset + 1] = clampColour(new_g);
                    bit_ptr[offset + 2] = clampColour(new_r);
                }

            return original_image;
        };

        QImage doVignetteEffectCPP(QImage original_image)
        {
            return QImage{};
        };

        using  FunctionContainer = std::array<std::array<Func*, static_cast<size_t>(EFFECT_NAME::SIZE)>, static_cast<size_t>(ALGORITHM_SOURCE::SIZE)>;

        constexpr FunctionContainer function_container
            {{
                //function order:

                //horizontally:
                //Sepia -> Vignette -> ...

                //vertically:
                //ASM -> CPP -> ...

                /*ASM*/ {doSepiaEffectASM, doVignetteEffectASM },
                /*CPP*/ {doSepiaEffectCPP, doVignetteEffectCPP }

            }};
    }

    Func* getEffectFunction(ALGORITHM_SOURCE code_source, EFFECT_NAME name)
    {
        size_t source_id = static_cast<size_t>(code_source);
        size_t name_id = static_cast<size_t>(name);

       return function_container.at(source_id).at(name_id);
    }

}
