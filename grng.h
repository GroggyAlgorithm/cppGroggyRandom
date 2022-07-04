/**
* \file grng.h
* \author Tim Robbins
* \brief Random number generator class header
*
*/
#ifndef GRNG_H_INCLUDED
#define GRNG_H_INCLUDED

#include <math.h>
#include <cmath>
#include <string>
#include <functional>
#include <stddef.h>
#include <type_traits>
#include "grandomAlgorithms.h"

/**
 * @brief Possible weights for a weighted random value to lean towards
 *
 *
 */
typedef enum RandomWeights {

    Random_Weight_None,
    Random_Weight_Lower,
    Random_Weight_Upper,
    Random_Weight_Center,
    Random_Weight_Ends

} RandomWeight_t ;


/**
 * @brief Available algorithms to create the random values
 */
typedef enum RandomAlgorithmChoices {

    Random_Algorithm_AdaptedLehmer32,
    Random_Algorithm_Lehmer64,
    Random_Algorithm_xor8,
    Random_Algorithm_xor16,
    Random_Algorithm_xor17,
    Random_Algorithm_xor23,
    Random_Algorithm_xor32,
    Random_Algorithm_xor128,
    Random_Algorithm_Wyhash,

} AlgorithmChoice_t;




template<typename T>
class grng
{

private:



protected:

    ///Seed for the random number generator
    T m_gdtSeed;

    ///Algorithm selection. Helpful for checking what algorithm is active and to copy object
    AlgorithmChoice_t m_udtAlgorithmSelection;

    ///The algorithm selected
    T(*selectedAlgorithm)(T);




public:
    void operator=(const grng<T> otherGrng);
    void operator=(const T seedToCopy);
    void operator=(const AlgorithmChoice_t selectedAlgorithm);
    bool operator==(const grng<T> otherGrng);
    bool operator!=(const grng<T> otherGrng);
    void operator&=(const grng<T> otherGrng);
    void operator|=(const grng<T> otherGrng);
    void operator^=(const grng<T> otherGrng);

    friend bool operator>(const grng<T>& grngLeft, const grng<T>& grngRight);
    friend bool operator<(const grng<T>& grngLeft, const grng<T>& grngRight);
    friend bool operator>=(const grng<T>& grngLeft, const grng<T>& grngRight);
    friend bool operator<=(const grng<T>& grngLeft, const grng<T>& grngRight);
    friend T operator&(const grng<T>& grngLeft, const grng<T>& grngRight);
    friend T operator|(const grng<T>& grngLeft, const grng<T>& grngRight);
    friend T operator^(const grng<T>& grngLeft, const grng<T>& grngRight);
    


    grng();

    template<typename U>
    grng(const grng<U> grngtoCopy);
    
    grng(const T newSeed);
    grng(const char* seedPointer);
    grng(const char* seedPointer, AlgorithmChoice_t algorithmSelection);
    grng(const std::string seedString);
    grng(const std::string seedString, AlgorithmChoice_t algorithmSelection);
    grng(const T newSeed, AlgorithmChoice_t algorithmSelection);
    ~grng();

    /**
    * \brief Sets this objects seed to the seed passed
    */
    inline void SetSeed(const T newSeed)
    {
        static_assert(std::is_integral<T>::value, "T must be an integral number");
        m_gdtSeed = newSeed;
    }

    /**
    * \brief Returns this objects seed
    */
    const inline T GetSeed()
    {
        return m_gdtSeed;
    }

    void SetAlgorithm(AlgorithmChoice_t algorithmSelection);

    /**
    * \brief Gets the classes random algorithm
    */
    const inline AlgorithmChoice_t GetAlgorithm()
    {
        return m_udtAlgorithmSelection;
    }

    T Next();
    T Next(T maxValue);
    T Range(T minValue, T maxValue);
    double NextDouble();
    double NextDouble(double maxValue);
    float NextFloat();
    float NextFloat(float maxFloat);
    int NextInt();
    int NextInt(int maxInt);
    bool NextBool();
    double RangeDouble(double minValue, double maxValue);
    float RangeFloat(float minValue, float maxValue);
    int RangeInt(int minValue, int maxValue);
    float NextPercentage();
    float Sign();
    float GaussianValue();
    float Gaussian(float center, float deviation);
    float GaussianRange(float deviation, float minValue, float maxValue);
    float LowerBiasValue(float strength);
    float UpperBiasValue(float strength);
    float ExtremesBiasValue(float strength);
    float CenterBiasValue(float strength);
    float WeightedValue(RandomWeight_t weight, float strength);
    long ValueNoise1DInt(int x, int seedValue);
    long ValueNoise2DInt(int x, int y, int seedValue);
    long ValueNoise3DInt(int x, int y, int z, int seedValue);
    double ValueNoise1D(int x, int seedValue);
    double ValueNoise2D(int x, int y, int seedValue);
    double ValueNoise3D(int x, int y, int z, int seedValue);
    double Voronoi3D(double x, double y, double z, double frequency, bool useDistance, double displacement);
    double Voronoi2D(double x, double y, double frequency, bool useDistance, double displacement);
    double Voronoi1D(double x, double frequency, bool useDistance, double displacement);
    float Perlin1D(float x);
    float Perlin2D(float x, float y);
    float Perlin3D(float x, float y, float z);
    double ImprovedNoise(double x, double y);
    double ImprovedNoise(double x, double y, double z);
    float FloatGradient(int hash, float x);
    float FloatGradient2D(int hash, float x, float y);
    float FloatGradient3D(int hash, float x, float y, float z);
    double DoubleGradient(int hash, double x, double y, double z);
    unsigned int* CreatePermutationTable(unsigned int tableSize, unsigned int maxSize);
    unsigned int* CreatePermutationTable() ;
    float OffsetPerlinNoise2D(int xIteration, int yIteration, float noiseScale, float xOffset, float yOffset,
        float centerX, float centerY, float frequency);
    float OffsetPerlinNoise3D(int xIteration, int yIteration, int zIteration, float noiseScale, float xOffset, float yOffset, float zOffset,
    float centerX, float centerY, float centerZ, float frequency);

    float** PerlinOctaves2D(int octaveAmount, int resolution, float offsetX, float offsetY,
        float noisePersistance, float noiseLacunarity, float noiseScale, float roughness, bool normalizeHeightGlobally);

    T SmallestRandom(int iterations);
    T LargestRandom(int iterations);
    T MostCenteredRandom(int iterations);

    template<typename U>
    U Element(U a[]);
    
    template<typename U>
    void Shuffle(U a[]);

    bool ChanceRoll(const float percentageChance);
};




#include "grng.cpp"


#endif // GRNG_H_INCLUDED

//
//
//#pragma region OPERATOR_OVERLOADS
//
//
//template<typename T>
//void grng<T>::operator=(const grng<T> otherGrng)
//{
//    m_gdtSeed = otherGrng.GetSeed();
//    SetAlgorithm(otherGrng.GetAlgorithm());
//}
//
//
//
//template<typename T>
//void grng<T>::operator=(const T seedToCopy)
//{
//    m_gdtSeed = seedToCopy;
//}
//
//
//
//template<typename T>
//void grng<T>::operator=(const AlgorithmChoice_t selectedAlgorithm)
//{
//    SetAlgorithm(selectedAlgorithm);
//}
//
//
//
//template<typename T>
//bool grng<T>::operator==(const grng<T> otherGrng)
//{
//    if (otherGrng.GetSeed() == m_gdtSeed && otherGrng.GetAlgorithm() == m_udtAlgorithmSelection)
//    {
//        return true;
//    }
//    else
//    {
//        return false;
//    }
//}
//
//
//template<typename T>
//bool grng<T>::operator!=(const grng<T> otherGrng)
//{
//    if (otherGrng.GetSeed() == m_gdtSeed && otherGrng.GetAlgorithm() == m_udtAlgorithmSelection)
//    {
//        return false;
//    }
//    else
//    {
//        return true;
//    }
//}
//
//
//
//template<typename T>
//void grng<T>::operator&=(const grng<T> otherGrng)
//{
//    this.m_gdtSeed &= otherGrng.GetSeed();
//}
//
//
//template<typename T>
//void grng<T>::operator|=(const grng<T> otherGrng)
//{
//    this.m_gdtSeed |= otherGrng.GetSeed();
//}
//
//
//template<typename T>
//void grng<T>::operator^=(const grng<T> otherGrng)
//{
//    m_gdtSeed ^= otherGrng.GetSeed();
//}
//
//
//
//template<typename T>
//bool operator>(const grng<T>& grngLeft, const grng<T>& grngRight)
//{
//    return (grngLeft.GetSeed() > grngRight.GetSeed());
//}
//
//
//
//template<typename T>
//bool operator<(const grng<T>& grngLeft, const grng<T>& grngRight)
//{
//    return (grngLeft.GetSeed() < grngRight.GetSeed());
//}
//
//
//template<typename T>
//bool operator>=(const grng<T>& grngLeft, const grng<T>& grngRight)
//{
//    return (grngLeft.GetSeed() >= grngRight.GetSeed());
//}
//
//
//
//template<typename T>
//bool operator<=(const grng<T>& grngLeft, const grng<T>& grngRight)
//{
//    return (grngLeft.GetSeed() <= grngRight.GetSeed());
//}
//
//
//
//template<typename T>
//T operator&(const grng<T>& grngLeft, const grng<T>& grngRight)
//{
//    return (T)(grngLeft.GetSeed() & grngRight.GetSeed());
//}
//
//template<typename T>
//T operator|(const grng<T>& grngLeft, const grng<T>& grngRight)
//{
//    return (T)(grngLeft.GetSeed() | grngRight.GetSeed());
//}
//
//
//template<typename T>
//T operator^(const grng<T>& grngLeft, const grng<T>& grngRight)
//{
//    return (T)(grngLeft.GetSeed() ^ grngRight.GetSeed());
//}
//
//
//#pragma endregion
//
