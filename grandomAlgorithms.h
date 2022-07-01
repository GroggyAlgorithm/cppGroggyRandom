/**
 * @file grandomAlgorithms.h
 * @brief Header file for random number algorithms
 *
 *
 * @author Tim Robbins
 * @version v2.0.0.0
 * @date 06-30-2022
 *
 */
#ifndef GRANDOMALGORITHMS_H_INCLUDED
#define GRANDOMALGORITHMS_H_INCLUDED

#include <stddef.h>
#include <type_traits>


template<typename T>
T xor8(T value);


template<typename T>
T xor16(T value);


template<typename T>
T xor17(T value);


template<typename T>
T xor23(T value);


template<typename T>
T xor32(T value);


template<typename T>
T xor128(T value);


template<typename T>
T Lehmer64(T value);


template<typename T>
T AdaptedLehmer32(T value);


template<typename T>
T wyhash(T value);

#include "grandomAlgorithms.cpp"

#endif // GRANDOMALGORITHMS_H_INCLUDED
