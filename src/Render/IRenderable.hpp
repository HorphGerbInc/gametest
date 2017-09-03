
namespace jerobins
{
namespace render
{
class IRenderable
{
  public:
    virtual std::vector<float> GetData() = 0;
    virtual std::vector<int> GetAdja() = 0;
    virtual RenderType Type() = 0;
    virtual bool UseAdjacency() = 0;
}
}
}