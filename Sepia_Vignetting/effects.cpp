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

        void doSepiaEffectASM(const EffectParams& params)
        {


        };

        void doVignetteEffectASM(const EffectParams& params)
        {

        };

        void doSepiaEffectCPP(const EffectParams& params)
        {
            //byte per pixel = 4
            //blue byte encryption = 0
            //green byte encryption = 1
            //red byte encryption = 2

            for(int i= params.start_row; i<params.end_row; ++i)
                for(int j=0; j<params.width; ++j)
                {
                    int offset = i*params.bytes_per_line + j*4;

                    uchar oryginal_b = params.bit_ptr[offset];
                    uchar oryginal_g = params.bit_ptr[offset + 1];
                    uchar oryginal_r = params.bit_ptr[offset + 2];

                    int new_b = 0.272*oryginal_r + 0.534*oryginal_g + 0.131*oryginal_b;
                    int new_g = 0.349*oryginal_r + 0.686*oryginal_g + 0.168*oryginal_b;
                    int new_r = 0.393*oryginal_r + 0.769*oryginal_g + 0.189*oryginal_b;

                    params.bit_ptr[offset] = clampColour(new_b);
                    params.bit_ptr[offset + 1] = clampColour(new_g);
                    params.bit_ptr[offset + 2] = clampColour(new_r);
                }
        };

        void doVignetteEffectCPP(const EffectParams& params)
        {
            float image_center_x = params.width/2;
            float image_center_y = params.height/2;
            float center_radius = std::sqrt((image_center_x*image_center_x) + (image_center_y*image_center_y));

            for(int i=params.start_row; i<params.end_row; ++i)
            {
                float normalized_distance_y = (i-image_center_y)/image_center_y;

                for(int j=0; j<params.width; ++j)
                {
                    float normalized_distance_x = (j-image_center_x)/image_center_x;
                    float normalized_radius = std::sqrt(normalized_distance_x*normalized_distance_x + normalized_distance_y*normalized_distance_y);

                    float falloff = 1.0 - std::pow(normalized_radius, 3);
                    falloff = std::max(0.0f, falloff);

                    int offset = (i*params.bytes_per_line) + j*4;

                    uchar oryginal_b = params.bit_ptr[offset];
                    uchar oryginal_g = params.bit_ptr[offset+1];
                    uchar oryginal_r = params.bit_ptr[offset+2];

                    int new_b = oryginal_b * falloff;
                    int new_g = oryginal_g * falloff;
                    int new_r = oryginal_r * falloff;

                    params.bit_ptr[offset] = new_b;
                    params.bit_ptr[offset+1] = new_g;
                    params.bit_ptr[offset+2] = new_r;
                }
            }
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
