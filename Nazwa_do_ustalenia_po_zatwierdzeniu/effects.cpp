#include "effects.h"

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
        void doSepiaEffectASM(){};
        void doVignetteEffectASM(){};
        void doSepiaEffectCPP(){};
        void doVignetteEffectCPP(){};

        using  FunctionContainer = std::array<std::array<FuncPtr*, static_cast<size_t>(EFFECT_NAME::SIZE)>, static_cast<size_t>(ALGORITHM_SOURCE::SIZE)>;

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

    FuncPtr* getEffectFunction(ALGORITHM_SOURCE code_source, EFFECT_NAME name)
    {
        size_t source_id = static_cast<size_t>(code_source);
        size_t name_id = static_cast<size_t>(name);

       return function_container.at(source_id).at(name_id);
    }

}
