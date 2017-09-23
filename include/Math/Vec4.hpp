
#ifndef _VEC4_HPP_
#define _VEC4_HPP_

#include <Math/ArrayVector.hpp>

namespace jerobins {
  namespace math {

    class Vec4 : public ArrayVector<Vec4,4> {
    public:
      Vec4();
      Vec4(float x, float y, float z, float w);

      float X() const;
      float Y() const;
      float Z() const;
      float W() const;
      
      void SetX(float);
      void SetY(float);
      void SetZ(float);
      void SetW(float);

      friend class Matrix4;
    };
  }
}

#endif