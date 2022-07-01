/**
 * @file grandomAlgorithms.cpp
 * @brief Source file for random number algorithms
 *
 *
 * @author Tim Robbins
 * @version v2.0.0.0
 * @date 06-30-2022
 *
 */
#ifndef GRANDOM_ALGORITHMS_CPP_
#define GRANDOM_ALGORITHMS_CPP_

#include <limits.h>
#include "grandomAlgorithms.h"


/**
 * @brief Performs an xorshift to create a random number
 *
 *
 * @param value The value to randomize
 * @return The value created
 */
template<typename T>
T xor8(T value)
{
    static_assert(std::is_integral<T>::value, "T must be numeric");
    T rand = value;
    rand ^= (value << 5);
    rand ^= (value >> 3);
    rand ^= (value << 4);
    return rand;
}



/**
 * @brief Performs an xorshift to create a random number
 *
 *
 * @param value The value to randomize
 * @return The value created
 */
template<typename T>
T xor16(T value)
{
    static_assert(std::is_integral<T>::value, "T must be numeric");
    T rand = value;
    rand ^= (value << 13);
    rand ^= (value >> 10);
    rand ^= (value << 7);
    return rand;
}




/**
 * @brief Xor shift variation: (value >> 17) ^ (value >> 34) ^ (value >> 51) & <data type max value>
 *
 *
 * @param value The value to randomize
 * @return The value created
 */
template<typename T>
T xor17(T value) {

    static_assert(std::is_integral<T>::value, "T must be numeric");

    T rval = ( (value ^ (value >> 17) ^ (value >> 34) ^ (value >> 51)) & 0x7fffffff);

    return rval;
}



/**
 * @brief Xor shift variation: (value << 23) ^ (value << 46)) & <data type max value>
 *
 *
 * @param value The value to randomize
 * @return The value created
 */
template<typename T>
T xor23(T value) {
    static_assert(std::is_integral<T>::value, "T must be numeric");

    T rval = ((value ^ (value << 23) ^ (value << 46)) & 0x7fffffff);
    return rval;
}



/**
 * @brief Performs an xorshift to create a random number
 *
 *
 * @param value The value to randomize
 * @return The value created
 */
template<typename T>
T xor32(T value)
{
    static_assert(std::is_integral<T>::value, "T must be numeric");
    T rand = value;
    rand ^= (value << 13);
    rand ^= (value >> 17);
    rand ^= (value << 5);
    return rand;
}



/**
 * @brief Performs an xorshift to create a random number
 *
 *
 * @param value The value to randomize
 * @return The value created
 */
template<typename T>
T xor128(T value)
{
    static_assert(std::is_integral<T>::value, "T must be numeric");
    T val2 = xor23(xor17(value));
    T rand = value;
    rand ^= (rand << 23);
    rand ^= (rand << 17);
    rand ^= val2;
    rand ^= (val2 >> 7);
    return rand;
}



/**
 * @brief A version of the Lehmer 64 algorithm
 *
 *
 * @param value The value to randomize
 * @return The value created
 */
template<typename T>
T Lehmer64(T value) {
    static_assert(std::is_integral<T>::value, "T must be numeric");
    return (T)(((unsigned long long)value * 0xda942042e4dd58b5) >> 64);
}



/**
 * @brief A version of the Lehmer 32 algorithm
 *
 *
 * @param value The number to randomize
 * @return The random value
 */
template<typename T>
T AdaptedLehmer32(T value) {
    static_assert(std::is_integral<T>::value, "T must be numeric");

    unsigned long long tmp = (unsigned long long)(value + 0xe120fc15) * 0x4a39b70d;
    unsigned long long m1 = (unsigned long long)((tmp >> 32) ^ tmp);
    tmp = (unsigned long long)m1 * 0x12fad5c9;
    return (T)((tmp >> 32)^tmp);
}



/**
 * @brief  A version of the wyhash hash algorithm by Wang Yi
 *
 *
 * @param value The value to randomize
 * @return The random value
 */
template<typename T>
T wyhash(T value) {
    static_assert(std::is_integral<T>::value, "T must be numeric");
    unsigned long long v = value + (0x60bee2bee120fc15);
    unsigned long long tmp = v * (0x60bee2bee120fc15);
    unsigned long long m1 = ((tmp << 16) ^ tmp);
    tmp = m1 * (0x1b03738712fad5c9);
    return (T)((tmp >> 16) ^ tmp);
}





#endif
