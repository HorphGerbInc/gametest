
#ifndef _ENGINE_HPP_
#define _ENGINE_HPP_

#include <Common/Configuration.hpp>

namespace jerobins {
  namespace engine {

    class Engine {
    private:
      Engine();

    public:
      /**
       * @brief Create a new engine using the configuration file.
       *
       * @param configuration The configuration of the engine.
       */
      Engine(jerobins::common::Configuration configuration);
    };
  } // namespace engine
} // namespace jerobins

#endif