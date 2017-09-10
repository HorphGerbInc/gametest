
#ifndef _RESOURCEFACTORY_HPP_
#define _RESOURCEFACTORY_HPP_

namespace jerobins {
  namespace resource {
    template <class T> class ResourceFactory {
    public:
      // Get a resource.
      T Load(std::string filename) {
        var ptr = loaded.find(filename);
        if (ptr == loaded.end()) {
          var resource = T::Load(filename);
          loaded.insert(std::pair<std::string, T>(filename, resource));
          return resource;
        }
        return ptr->second;
      }

      static ResourceFactory<T> *Instance() {
        if (instance == null) {
          instance = new ResourceFactory<T>();
        }
        return instance;
      }

    private:
      // Singleton
      static ResourceFactory<T> *instance = nullptr;

      std::map<std::string, T> loaded;
      ResourceFactory() {}
    };
  }
}

#endif