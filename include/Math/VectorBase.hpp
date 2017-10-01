
#ifndef _VECTORBASE_HPP_
#define _VECTORBASE_HPP_

#include <iostream>
#include <map>

// Conversion
#include <json.hpp>
#include <stdexcept>

namespace jerobins {
  namespace math {

    template <bool B> using EnableIfB = typename std::enable_if<B, int>::type;

    template <class DerivedClass, int Dim, typename ElementType>
    class VectorBase {

    public:
      DerivedClass &operator=(const DerivedClass &other) {
        if (this != *other) {
          for (int i = 0; i < Dim; ++i)
            Set(i, other.Get(i));
        }
        return CastToDerived();
      }
      DerivedClass &operator=(const DerivedClass &&other) {
        for (int i = 0; i < Dim; ++i)
          Set(i, other.Get(i));
        return CastToDerived();
      }

      // Pure Virtual

      // Pairwise multiplication
      virtual DerivedClass &operator*=(const DerivedClass &other) = 0;
      // Scalar multiplication
      virtual DerivedClass &operator*=(const ElementType &scalar) = 0;
      // Pairwise Addition
      virtual DerivedClass &operator+=(const DerivedClass &other) = 0;
      // Pairwise Subtraction
      virtual DerivedClass &operator-=(const DerivedClass &other) = 0;
      // Dot
      virtual ElementType Dot(const DerivedClass &other) const = 0;
      // Get the value at a position
      virtual ElementType Get(int) const = 0;
      // Set the value at a position
      virtual void Set(int, ElementType) = 0;
      // Return the raw pointer
      virtual const ElementType *Raw() const = 0;

      // Implementations

      // Pairwise Multiplication
      DerivedClass &operator*=(const DerivedClass &&other) {
        return *this *= other;
      }

      DerivedClass operator*(const DerivedClass &other) const {
        DerivedClass result;
        for (int i = 0; i < Dim; ++i) {
          result.Set(i, Get(i));
        }
        result *= other;
        return result;
      }

      DerivedClass operator*(const DerivedClass &&other) const {
        return *this * other;
      }

      DerivedClass &operator*=(const ElementType &&scalar) {
        return (*this *= scalar);
      }

      // Scalar multiplication
      DerivedClass operator*(const ElementType &scalar) {
        DerivedClass result(*this);
        return result *= scalar;
      }

      DerivedClass operator*(const ElementType &&scalar) {
        return *this * scalar;
      }

      // Pairwise Addition
      DerivedClass &operator+=(const DerivedClass &&other) {
        return *this += other;
      }

      DerivedClass operator+(const DerivedClass &other) const {
        DerivedClass result = Clone();
        result += other;
        return result;
      }

      DerivedClass operator+(const DerivedClass &&other) const {
        return *this + other;
      }

      // Pairwise subtraction
      DerivedClass &operator-=(const DerivedClass &&other) {
        return *this -= other;
      }

      DerivedClass operator-(const DerivedClass &other) const {
        DerivedClass result = Clone();
        result -= other;
        return result;
      }

      DerivedClass operator-(const DerivedClass &&other) const {
        return (*this - other);
      }

      // Dot product
      ElementType Dot(const DerivedClass &&other) const { return Dot(other); }

    protected:
      void BoundsCheck(int pos) const {
        if (pos < 0 || pos > Dim) {
          throw std::runtime_error("Out of bounds");
        }
      }

      DerivedClass &CastToDerived() {
        return *static_cast<DerivedClass *>(this);
      }

      const DerivedClass &CastToDerived() const {
        return *static_cast<DerivedClass *>(this);
      }

    private:
      DerivedClass Clone() const {
        DerivedClass result;
        for (int i = 0; i < Dim; ++i)
          result.Set(i, Get(i));
        return result;
      }
    };

    template <class DerivedClass, int Dim, typename ElementType>
    void to_json(nlohmann::json &j,
                 const VectorBase<DerivedClass, Dim, ElementType> &input) {
      std::map<int, std::string> mapping = {
          {0, "x"}, {1, "y"}, {2, "z"}, {3, "w"}};

      for (int i = 0; i < Dim; ++i) {
        j[mapping[i]] = input.Get(i);
      }
    }

    template <class DerivedClass, int Dim, typename ElementType>
    void from_json(const nlohmann::json &j,
                   VectorBase<DerivedClass, Dim, ElementType> &output) {
      std::map<int, std::string> mapping = {
          {0, "x"}, {1, "y"}, {2, "z"}, {3, "w"}};

      for (int i = 0; i < Dim; ++i) {
        output.Set(i, j[mapping[i]]);
      }
    }
  }
}

#endif