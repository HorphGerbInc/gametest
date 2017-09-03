

#include <Engine/Engine.hpp>

namespace jerobins
{
namespace engine
{

Engine::Engine(Configuration configuration)
{
}

void RenderPolygons(std::vector<Polygon> polygons) {
    std::for_each(polygons.begin(), polygons.end(), RenderPolygon);
}

void RenderPolygon(Polygon &poly) {

}

}
}
