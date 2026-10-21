#ifndef EFFECTS_H
#define EFFECTS_H

#include <QString>

namespace effect
{

    enum class EFFECT_NAME {SEPIA_EFFECT = 0, VIGNETTE_EFFECT};

    QString getEffectStringName(EFFECT_NAME name);

    void doSepiaEffectASM();
    void doSepiaEffectCPP();
    void doVignetteEffectASM();
    void doVignetteEffectCPP();

}



#endif // EFFECTS_H
