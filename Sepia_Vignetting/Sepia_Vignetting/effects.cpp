#include "effects.h"
#include "libs/ImageEffects_api.h"

#include <array>
#include <algorithm>

#include <QImage>

extern "C" void doSepiaEffectASM(const EffectParams* params);
//extern "C" void doVignetteEffectASM(const EffectParams* params);

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

        void doVignetteEffectASM(const EffectParams* params)
        {

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
