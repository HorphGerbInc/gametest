
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

    /**
     * @brief Base class for all array based vectors.
     *
     * @tparam DerivedClass   The child class that inherits from us.
     * @tparam Dim            How many dimensions.
     * @tparam ElementType    The type of elements in the vector.
     */
    template <class DerivedClass, int Dim, typename ElementType>
    class VectorBase {

    public:
      /**
       * @brief Assignment operator.
       *
       * @param other           Right hand side.
       * @return DerivedClass&  This object.
       */
      DerivedClass &operator=(const DerivedClass &other) {
        if (this != *other) {
          for (int i = 0; i < Dim; ++i)
            Set(i, other.Get(i));
        }
        return CastToDerived();
      }

      /**
       * @brief Assignment operator.
       *
       * @param other           Right hand side.
       * @return DerivedClass&  This object.
       */
      DerivedClass &operator=(const DerivedClass &&other) {
        for (int i = 0; i < Dim; ++i)
          Set(i, other.Get(i));
        return CastToDerived();
      }

      // Pure Virtual

      /**
       * @brief Pariwise multiplication.
       *
       * @param other             Right hand side.
       * @return DerivedClass&    The left hand side.
       */
      virtual DerivedClass &operator*=(const DerivedClass &other) = 0;

      /**
       * @brief Scalar multiplication.
       *
       * @param scalar          The right hand side scalar.
       * @return DerivedClass&  Left hand side.
       */
      virtual DerivedClass &operator*=(const ElementType &scalar) = 0;

      /**
       * @brief Pairwise addition.
       *
       * @param other           Right hand side vector.
       * @return DerivedClass&  Left hand side vector.
       */
      virtual DerivedClass &operator+=(const DerivedClass &other) = 0;

      /**
       * @brief Pairwise subtraction.
       *
       * @param other           Right hand side vector.
       * @return DerivedClass&  Left hand side vector.
       */
      virtual DerivedClass &operator-=(const DerivedClass &other) = 0;

      /**
       * @brief Dot product.
       *
       * @param other           Right hand side vector.
       * @return ElementType    Dot product.
       */
      virtual ElementType Dot(const DerivedClass &other) const = 0;

      /**
       * @brief Get the element at the given index.
       *
       * @parama index        Vector index.
       * @return ElementType  Value at given index.
       */
      virtual ElementType Get(int index) const = 0;

      /**
       * @brief Set the value at the given index.
       *
       * @param index Vector index.
       * @param value New value.
       */
      virtual void Set(int index, ElementType value) = 0;

      /**
       * @brief Return the raw underlying array.
       *
       * @return const ElementType* Underlying array.
       */
      virtual const ElementType *Raw() const = 0;

      // Implementations

      /**
       * @brief Pairwise multiplication.
       *
       * @param other           Right hand side vector.
       * @return DerivedClass&  Left hand side vector.
       */
      DerivedClass &operator*=(const DerivedClass &&other) {
        return *this *= other;
      }

      /**
       * @brief Pairwise multiplication.
       *
       * @param other         Right hand side vector.
       * @return DerivedClass New vector.
       */
      DerivedClass operator*(const DerivedClass &other) const {
        DerivedClass result;
        for (int i = 0; i < Dim; ++i) {
          result.Set(i, Get(i));
        }
        result *= other;
        return result;
      }

      /**
       * @brief Pairwise multiplication.
       *
       * @param other         Right hand side vector.
       * @return DerivedClass New vector.
       */
      DerivedClass operator*(const DerivedClass &&other) const {
        return *this * other;
      }

      /**
       * @brief Scalar multiplication.
       *
       * @param scalar          Scalar value.
       * @return DerivedClass&  Left hand side vector.
       */
      DerivedClass &operator*=(const ElementType &&scalar) {
        return (*this *= scalar);
      }

      /**
       * @brief Scalar multiplication.
       *
       * @param scalar          Scalar value.
       * @return DerivedClass   New vector with result.
       */
      DerivedClass operator*(const ElementType &scalar) {
        DerivedClass result(*this);
        return result *= scalar;
      }

      /**
       * @brief Scalar multiplication.
       *
       * @param scalar          Scalar value.
       * @return DerivedClass   New vector with result.
       */
      DerivedClass operator*(const ElementType &&scalar) {
        return *this * scalar;
      }

      /**
       * @brief Pairwise addition.
       *
       * @param other           Right hand side vector.
       * @return DerivedClass&  Right hand side vector.
       */
      DerivedClass &operator+=(const DerivedClass &&other) {
        return *this += other;
      }

      /**
       * @brief Pairwise addition.
       *
       * @param other           Right hand side vector.
       * @return DerivedClass   New vector with result.
       */
      DerivedClass operator+(const DerivedClass &other) const {
        DerivedClass result = Clone();
        result += other;
        return result;
      }

      /**
       * @brief Pairwise addition.
       *
       * @param other           Right hand side vector.
       * @return DerivedClass   New vector with result.
       */
      DerivedClass operator+(const DerivedClass &&other) const {
        return *this + other;
      }

      /**
       * @brief Pairwise subtraction.
       *
       * @param other           Right hand side vector.
       * @return DerivedClass&  Left hand side vector.
       */
      DerivedClass &operator-=(const DerivedClass &&other) {
        return *this -= other;
      }

      /**
       * @brief Pairwise subtraction.
       *
       * @param other           Right hand side vector.
       * @return DerivedClass   New vector with result.
       */
      DerivedClass operator-(const DerivedClass &other) const {
        DerivedClass result = Clone();
        result -= other;
        return result;
      }

      /**
       * @brief Pairwise subtraction.
       *
       * @param other           Right hand side vector.
       * @return DerivedClass   New vector with result.
       */
      DerivedClass operator-(const DerivedClass &&other) const {
        return (*this - other);
      }

      /**
       * @brief Dot product.
       *
       * @param other           Right hand side vector.
       * @return ElementType    Dot product.
       */
      ElementType Dot(const DerivedClass &&other) const { return Dot(other); }

    protected:
      /**
       * @brief Check the bounds of the index.
       *
       * @param pos The index to check.
       */
      void BoundsCheck(int pos) const {
        if (pos < 0 || pos > Dim) {
          throw std::runtime_error("Out of bounds");
        }
      }

      /**
       * @brief Cast to the derived class.
       *
       * @return DerivedClass&  This object as the derived class type.
       */
      DerivedClass &CastToDerived() {
        return *static_cast<DerivedClass *>(this);
      }

      /**
       * @brief Cast to the derived class.
       *
       * @return DerivedClass&  This object as the derived class type.
       */
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
  } // namespace math
} // namespace jerobins

#endif