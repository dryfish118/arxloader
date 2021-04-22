#ifndef ODA_PAL_FONT_FONTPITCHANDFAMILY_
#define ODA_PAL_FONT_FONTPITCHANDFAMILY_

#ifdef PAL
#undef PAL
#endif

namespace Gstarsoft
{
  namespace GstarCAD
  {
    namespace PAL
    {
      namespace FontUtils
      {
        enum class FontPitch
        {
          kDefault,
          kFixed,
          kVariable
        };
        enum class FontFamily
        {
          kDoNotCare = 0,
          kRoman = 16,
          kSwiss = 32,
          kModern = 48,
          kScript = 64,
          kDecorative = 80
        };
      }
    }
  }
};

#endif
