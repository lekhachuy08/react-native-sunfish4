using ReactNative.Bridge;
using System;
using System.Collections.Generic;
using Windows.ApplicationModel.Core;
using Windows.UI.Core;

namespace Sunfish.RNSunfish
{
    /// <summary>
    /// A module that allows JS to share data.
    /// </summary>
    class RNSunfishModule : NativeModuleBase
    {
        /// <summary>
        /// Instantiates the <see cref="RNSunfishModule"/>.
        /// </summary>
        internal RNSunfishModule()
        {

        }

        /// <summary>
        /// The name of the native module.
        /// </summary>
        public override string Name
        {
            get
            {
                return "RNSunfish";
            }
        }
    }
}
