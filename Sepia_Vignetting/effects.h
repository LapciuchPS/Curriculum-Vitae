#ifndef EFFECTS_H
#define EFFECTS_H

#include <QString>
#include <QImage>

namespace effect
{
    enum class EFFECT_NAME {SEPIA_EFFECT = 0, VIGNETTE_EFFECT, SIZE};
    enum class ALGORITHM_SOURCE {ASM = 0, CPP, SIZE };

    QString getEffectStringName(EFFECT_NAME name);

    using Func = QImage(QImage image);
    Func* getEffectFunction(ALGORITHM_SOURCE code_source, EFFECT_NAME name);
}

#endif // EFFECTS_H
