#ifndef _GRAPHICSDESCRIPTION_H_
#define _GRAPHICSDESCRIPTION_H_

// Engine specific includes
#include "Defines.h"
#include "GraphicsModuleType.h"

// Declare namespace PuReEngine::Core
namespace PuReEngine {
  namespace Core {

    /// @brief Description of the Graphic Object
    ///
    struct SGraphicsDescription
    {
      /// @brief The resolution width.
      ///
      int32 ResolutionWidth;

      /// @brief The resolution height.
      ///
      int32 ResolutionHeight;

      /// @brief The graphics module.
      ///
      EGraphicsModuleType Module;
    };

  }
}

#endif /* _GRAPHICSDESCRIPTION_H_ */