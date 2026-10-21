#include "effects.h"

QString effect::getEffectStringName(EFFECT_NAME name)
{
    switch(name)
    {
        case EFFECT_NAME::SEPIA_EFFECT: return "Serpia effect";
        case EFFECT_NAME::VIGNETTE_EFFECT: return "Vignette effect";

        default: return "Unknown effect";
    }
}
