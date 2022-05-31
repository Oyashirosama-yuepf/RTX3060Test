

/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file Deserializer.h
 * @brief This header file defines the input/output serializer base class.
 * @author zhengshulei@holomatic.com
 * @date 2021-10-08
 */
#ifndef HOLO_MAP_ADASIS_SERIALIZER_H_
#define HOLO_MAP_ADASIS_SERIALIZER_H_

#include <stdint.h>

#include <map>
#include <vector>

namespace holo
{
namespace map
{
namespace adasis
{
namespace serialization
{
class Deserializer;
class Serializer;

/**
 *  Serialization traits for objects of type T. By default,
 *  we expect that Serialize and Deserialize are defined
 *  on objects of type T. Redefinition must be made in
 *  case this is not the case.
 */
template <class T>
struct SerializationTraits
{
    static const bool IS_ARRAY_BASE_TYPE = false;

    static Serializer& Store(Serializer& s, const T& x)
    {
        x.Serialize(s);
        return s;
    }

    static Deserializer& Retrieve(Deserializer& s, T& x)
    {
        x.Deserialize(s);
        return s;
    }
};

/**
   The abstract base class for serializing an object.
   It is similar to an ostream.
   The same << notation as for ostreams can be used. It is implemented
   for the basic data types and for classes derived from Osiris. For the
   latter the store function of the object is called.
*/
class Serializer
{
public:
    Serializer(uint32_t v = 0);
    virtual ~Serializer() {}
    // returns the version of the dump data format.
    uint32_t Version() const { return version_; }

    /**
       write an array of signed 64-bit integers.
       The default is calling the WriteOne for each element in the array.
       This function is used by the implementation of dumping the array classes
       and usually does not need to be called directly.
       @param n the number of elements
       @param p a pointer to the array
    */
    virtual void WriteArray(std::size_t n, const int64_t* p);

    /**
       write an array of signed 32-bit integers.
       The default is calling the WriteOne for each element in the array.
       This function is used by the implementation of dumping the array classes
       and usually does not need to be called directly.
       @param n the number of elements
       @param p a pointer to the array
    */
    virtual void WriteArray(std::size_t n, const int32_t* p);

    /**
       write an array of signed 16-bit integers.
       The default is calling the WriteOne for each element in the array.
       This function is used by the implementation of dumping the array classes
       and usually does not need to be called directly.
       @param n the number of elements
       @param p a pointer to the array
    */
    virtual void WriteArray(std::size_t n, const int16_t* p);

    /**
       write an array of signed 8-bit integers.
       The default is calling the WriteOne for each element in the array.
       This function is used by the implementation of dumping the array classes
       and usually does not need to be called directly.
       @param n the number of elements
       @param p a pointer to the array
    */
    virtual void WriteArray(std::size_t n, const int8_t* p);

    /**
       write an array of unsigned 64-bit integers.
       The default is calling the WriteOne for each element in the array.
       This function is used by the implementation of dumping the array classes
       and usually does not need to be called directly.
       @param n the number of elements
       @param p a pointer to the array
    */
    virtual void WriteArray(std::size_t n, const uint64_t* p);

    /**
       write an array of unsigned 32-bit integers.
       The default is calling the WriteOne for each element in the array.
       This function is used by the implementation of dumping the array classes
       and usually does not need to be called directly.
       @param n the number of elements
       @param p a pointer to the array
    */
    virtual void WriteArray(std::size_t n, const uint32_t* p);

    /**
       write an array of unsigned 16-bit integers.
       The default is calling the WriteOne for each element in the array.
       This function is used by the implementation of dumping the array classes
       and usually does not need to be called directly.
       @param n the number of elements
       @param p a pointer to the array */
    virtual void WriteArray(std::size_t n, const uint16_t* p);

    /**
       write an array of unsigned 8-bit integers.
       The default is calling the WriteOne for each element in the array.
       This function is used by the implementation of dumping the array classes
       and usually does not need to be called directly.
       @param n the number of elements
       @param p a pointer to the array
    */
    virtual void WriteArray(std::size_t n, const uint8_t* p);

    /**
       write an array of float.
       The default is unsigned the WriteOne for each element in the array.
       This function is used by the implementation of dumping the array classes
       and usually does not need to be called directly.
       @param n the number of elements
       @param p a pointer to the array */
    virtual void WriteArray(std::size_t n, const float* p);

    /**
       write an array of double.
       The default is calling the WriteOne for each element in the array.
       This function is used by the implementation of dumping the array classes
       and usually does not need to be called directly.
       @param n the number of elements
       @param p a pointer to the array
    */
    virtual void WriteArray(std::size_t n, const double* p);

    /**
       write an array of long double.
       The default is calling the WriteOne for each element in the array.
       This function is used by the implementation of dumping the array classes
       and usually does not need to be called directly.
       @param n the number of elements
       @param p a pointer to the array
    */
    virtual void WriteArray(std::size_t n, const long double* p);

    /**
       write an array of booleans.
       The default is calling the WriteOne for each element in the array.
       This function is used by the implementation of dumping the array classes
       and usually does not need to be called directly.
       @param n the number of elements
       @param p a pointer to the array
    */
    virtual void WriteArray(std::size_t n, const bool* p);

    /**
       write a string.
       Perform character set translations when possible.
       The default is calling the unsigned 8-bit integer version of WriteArray.
       This function is used by the implementation of dumping the std::string
       class and usually does not need to be called directly.
       @param n the number of elements
       @param s a pointer to the C-style string
    */

    virtual void WriteString(std::size_t n, const char* s);

    /**
       register an object to prepare serializing a pointer to it.
       after writing an object it has to be registered with the dump to
       allow writing a pointer to the object.
    */

    void RegisterObjectAddress(void* p);

    /**
       serialize a pointer.
       after registering an object's address a pointer to it can be serialized.
       This is done by writing an integer number associated with the object
       when its address is registered.
    */
    void WritePointer(void* p);

public:
    // implements writing a signed 64-bit integer. The default is using the
    // 32-bit version.
    virtual void WriteOne(const int64_t x);
    // implements writing a signed 32-bit integer. This has to be implemented by
    // all classes derived from Serializer.
    virtual void WriteOne(const int32_t x) = 0;
    // implements writing a signed 16-bit integer. The default is using the
    // 32-bit version.
    virtual void WriteOne(const int16_t x);
    // implements writing a signed 8-bit integer. The default is using the
    // 16-bit version.
    virtual void WriteOne(const int8_t x);
    // implements writing an unsigned 64-bit integer. The default is using the
    // signed version.
    virtual void WriteOne(const uint64_t x);
    // implements writing an unsigned 32-bit integer. The default is using the
    // signed version.
    virtual void WriteOne(const uint32_t x);
    // implements writing an unsigned 16-bit integer. The default is using the
    // signed version.
    virtual void WriteOne(const uint16_t x);
    // implements writing an unsigned 8-bit integer. The default is using the
    // signed version.
    virtual void WriteOne(const uint8_t x);
    // implements writing a float. The default is using the double version.
    virtual void WriteOne(const float x);
    // implements writing a double. This has to be implemented by all classes
    // derived from Serializer.
    virtual void WriteOne(const double x) = 0;
    // implements writing a long double. The default is using the double
    // version.
    virtual void WriteOne(const long double x);
    // implements writing a bool. The default is using the signed 32-bit integer
    // version.
    virtual void WriteOne(const bool x);

protected:
    uint32_t version_;
    std::map<void*, uint32_t> pointer_id_;
};

/// Serialize an object x to serializer s
template <class T>
Serializer& operator<<(Serializer& s, const T& x)
{
    SerializationTraits<T>::Store(s, x);
    return s;
}

/**
   The abstract base class for de-serializing an object.
   It is similar to an istream.
   The same >> notation as for istreams can be used for basic data types
   Deserialization of objects from a dump is usually implemented
   through a constructor which takes an Deserializer as argument.
   Alternatively the >> operator calls the retrieve function by default.
*/
class Deserializer
{
public:
    /** The constructor. It takes a version number as
        argument. Different version numbers allow to distinguish
        different data formats, athough this is not used yet.*/
    Deserializer(uint32_t v = 0);
    virtual ~Deserializer() {}

    // returns the version of the data format.
    uint32_t Version() const { return version_; }

    /** read an array of signed 64-bit integers.
        The default is calling the ReadOne for each element in the array.
        This function is used by the implementation of deserializing the array
       classes and usually does not need to be called directly.
        @param n the number of elements
        @param p a pointer to the array */
    virtual void ReadArray(std::size_t n, int64_t* p);

    /** read an array of signed 32-bit integers.
        The default is calling the ReadOne for each element in the array.
        This function is used by the implementation of deserializing the array
       classes and usually does not need to be called directly.
        @param n the number of elements
        @param p a pointer to the array */
    virtual void ReadArray(std::size_t n, int32_t* p);
    /** read an array of signed 16-bit integers.
        The default is calling the ReadOne for each element in the array.
        This function is used by the implementation of deserializing the array
       classes and usually does not need to be called directly.
        @param n the number of elements
        @param p a pointer to the array */
    virtual void ReadArray(std::size_t n, int16_t* p);
    /** read an array of signed 8-bit integers.
        The default is calling the ReadOne for each element in the array.
        This function is used by the implementation of deserializing the array
       classes and usually does not need to be called directly.
        @param n the number of elements
        @param p a pointer to the array */
    virtual void ReadArray(std::size_t n, int8_t* p);

    /** read an array of unsigned 64-bit integers.
        The default is calling the ReadOne for each element in the array.
        This function is used by the implementation of deserializing the array
       classes and usually does not need to be called directly.
        @param n the number of elements
        @param p a pointer to the array */
    virtual void ReadArray(std::size_t n, uint64_t* p);

    /** read an array of unsigned 32-bit integers.
        The default is calling the ReadOne for each element in the array.
        This function is used by the implementation of deserializing the array
       classes and usually does not need to be called directly.
        @param n the number of elements
        @param p a pointer to the array */
    virtual void ReadArray(std::size_t n, uint32_t* p);
    /** read an array of unsigned 16-bit integers.
        The default is calling the ReadOne for each element in the array.
        This function is used by the implementation of deserializing the array
       classes and usually does not need to be called directly.
        @param n the number of elements
        @param p a pointer to the array */
    virtual void ReadArray(std::size_t n, uint16_t* p);
    /** read an array of unsigned 8-bit integers.
        The default is calling the ReadOne for each element in the array.
        This function is used by the implementation of deserializing the array
       classes and usually does not need to be called directly.
        @param n the number of elements
        @param p a pointer to the array */
    virtual void ReadArray(std::size_t n, uint8_t* p);
    /** read an array of floats.
        The default is calling the ReadOne for each element in the array.
        This function is used by the implementation of deserializing the array
       classes and usually does not need to be called directly.
        @param n the number of elements
        @param p a pointer to the array */
    virtual void ReadArray(std::size_t n, float* p);
    /** read an array of doubles.
        The default is calling the ReadOne for each element in the array.
        This function is used by the implementation of deserializing the array
       classes and usually does not need to be called directly.
        @param n the number of elements
        @param p a pointer to the array */
    virtual void ReadArray(std::size_t n, double* p);
    /** read an array of long doubles.
        The default is calling the ReadOne for each element in the array.
        This function is used by the implementation of deserializing the array
       classes and usually does not need to be called directly.
        @param n the number of elements
        @param p a pointer to the array */
    virtual void ReadArray(std::size_t n, long double* p);
    /** read an array of booleans.
        The default is calling the ReadOne for each element in the array.
        This function is used by the implementation of deserializing the array
       classes and usually does not need to be called directly.
        @param n the number of elements
        @param p a pointer to the array */
    virtual void ReadArray(std::size_t n, bool* p);

    /** read a C-style string.
        Perform character set translations when possible.
        The default is calling the unsigned 8-bit integer version of ReadArray.
        This function is used by the implementation of dumping the std::string
       class and usually does not need to be called directly.
        @param n the number of elements
        @param s a pointer to memory allocated for a C-style string. At least
       n+1 bytes must be allocated. */
    virtual void ReadString(std::size_t n, char* s);

    /** register an object to prepare deserializing a pointer to it.
        after reading an object it has to be registered with the dump to
        allow reading a pointer to the object. */
    void RegisterObjectAddress(void* p);

    /** deserialize a pointer.
        After registering an object's address a pointer to it can be
       deserialized. This is done by reading an integer number associated with
       the object when its address is registered. */
    void* ReadPointer();

public:
    // implements reading a signed 64-bit integer. This has to be implemented by
    // all classes derived from Deserializer.
    virtual void ReadOne(int64_t& x) = 0;
    // implements reading a signed 32-bit integer. This has to be implemented by
    // all classes derived from Deserializer.
    virtual void ReadOne(int32_t& x) = 0;
    // implements reading a signed 16-bit integer. The default is using the
    // 32-bit version.
    virtual void ReadOne(int16_t& x);
    // implements reading a signed 8-bit integer. The default is using the
    // 16-bit version.
    virtual void ReadOne(int8_t& x);
    // implements reading an unsigned 64-bit integer. The default is using the
    // signed version.
    virtual void ReadOne(uint64_t& x);
    // implements reading an unsigned 32-bit integer. The default is using the
    // signed version.
    virtual void ReadOne(uint32_t& x);
    // implements reading an unsigned 16-bit integer. The default is using the
    // signed version.
    virtual void ReadOne(uint16_t& x);
    // implements reading an unsigned 8-bit integer. The default is using the
    // signed version.
    virtual void ReadOne(uint8_t& x);
    // implements reading a float. The default is using the double version.
    virtual void ReadOne(float& x);
    // implements reading a double. This has to be implemented by all classes
    // derived from Serializer.
    virtual void ReadOne(double& x) = 0;
    // implements reading a long double. The default is using the double
    // version.
    virtual void ReadOne(long double& x);
    // implements reading a boolean. The default is using the signed 32-bit
    // integer version.
    virtual void ReadOne(bool& x);

protected:
    uint32_t version_;
    std::vector<void*> pointers_;
};

/// Deserialize an object x from serializer s
template <class T>
Deserializer& operator>>(Deserializer& s, T& x)
{
    SerializationTraits<T>::Retrieve(s, x);
    return s;
}

#define SL_DECLARE_BASE_SERIALIZER(T)                        \
    template <>                                              \
    struct SerializationTraits<T>                            \
    {                                                        \
        static const bool IS_ARRAY_BASE_TYPE = true;         \
        static Serializer& Store(Serializer& s, const T& x)  \
        {                                                    \
            s.WriteOne(x);                                   \
            return s;                                        \
        }                                                    \
        static Deserializer& Retrieve(Deserializer& s, T& x) \
        {                                                    \
            s.ReadOne(x);                                    \
            return s;                                        \
        }                                                    \
    }

SL_DECLARE_BASE_SERIALIZER(int64_t);
SL_DECLARE_BASE_SERIALIZER(uint64_t);

SL_DECLARE_BASE_SERIALIZER(int32_t);
SL_DECLARE_BASE_SERIALIZER(uint32_t);
SL_DECLARE_BASE_SERIALIZER(int16_t);
SL_DECLARE_BASE_SERIALIZER(uint16_t);
SL_DECLARE_BASE_SERIALIZER(int8_t);
SL_DECLARE_BASE_SERIALIZER(uint8_t);
SL_DECLARE_BASE_SERIALIZER(float);
SL_DECLARE_BASE_SERIALIZER(double);
SL_DECLARE_BASE_SERIALIZER(long double);
SL_DECLARE_BASE_SERIALIZER(bool);

#undef SL_DECLARE_BASE_SERIALIZER

} // namespace serialization
} // namespace adasis
} // namespace map
} // namespace holo

#endif /* HOLO_MAP_ADASIS_SERIALIZER_H_ */