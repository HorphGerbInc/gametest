
namespace jerobins {
  namespace Platform {
    class Window {
    public:
      bool BorderLess() const { return borderless; }
      bool FullScreen() const { return fullscreen; }
      bool Resizable() const { return resizable; }
      std::size_t Height() const {return height};
      std::size_t Width() const {return width};

      void SetHeight(std::size_t height);
      void SetWidth(std::size_t width);
      void SetSize(std::size_t height, std::size_t width);

      float AspectRatio() const { return (float)width / (float)height; }

    private:
      bool borderless;
      bool fullscreen;
      bool resizable;
      std::size_t height, width;
    }
  }
}