
#include <Resource/BlenderLoader.hpp>

// Lib
#include <assimp/Importer.hpp>
#include <assimp/scene.h>           // Output data structure


namespace jerobins {
    namespace resource {
        void BlenderLoader::LoaderTest() {
            Assimp::Importer importer;
			auto scene = importer.ReadFile("models/cube.dae", 0);
			if (!scene) {
				exit(1);
			}
			if (scene->HasMeshes()) {
				
				auto meshes = scene->mMeshes;
				
			}
        }
        
    }
}