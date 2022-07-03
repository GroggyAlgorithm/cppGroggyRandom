/**
 * @file grng.cpp
 * @brief Source file for grng class
 *
 *
 * @author Tim Robbins
 * @version v2.0.0.0
 * @date 06-30-2022
 *
 */
#ifndef GRNG_CPP_INCLUDED
#define GRNG_CPP_INCLUDED

#define SQRT3           1.7320508075688772935
#define SQR(v)          v*v
#define MIN(x, y)       (x <= y) ? x : y
#define MAX(x, y)       (x >= y) ? x : y

#include "grng.h"


/// <summary>
/// The permutation table from ken perlins noise source code
/// </summary>
/// <value></value>
static const int PermutationTable[] = {
    151,160,137,91,90,15,
    131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
    190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
    88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
    77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
    102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
    135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
    5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
    223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
    129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
    251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
    49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
    138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,
    151
};


#pragma region STATIC_MATH


static float FadeFloat(float t) { 
    return (t*t*t*(t*(t*6-15)+10)); 
}



static double FadeDouble(double t)  {
    return (t*t*t*(t*(t*6-15)+10)); 
}



static float Clamp01(float value ) {
    if( value < 0.f ) value = 0.f;
    if( value > 1.f ) value = 1.f;
    return value;
}



static float InverseLerp( float a, float b, float value ) {
    return ( value - a ) / ( b - a );
}



static float Clamp(float value, float minValue, float maxValue) {
    if( value < minValue ) value = minValue;
    if( value > maxValue ) value = maxValue;
    return value;
}



static float InverseLerpClamped( float a, float b, float value ) {
    return Clamp(( value - a ) / ( b - a ),a,b );
}



static float CbFloatLerp( float a, float b, float t ) {
    return ( b - a ) * t + a;
}



static double CbDoubleLerp( double a, double b, double t ) {
    return ( b - a ) * t + a;
}



static float LerpFloatClamped( float a, float b, float t ) {
    t = Clamp01( t );
    return ( 1.f - t ) * a + t * b;
}



static float CbLerpFloatClamped( float a, float b, float t ) {
    t = Clamp01( t );
    return CbFloatLerp(a,b,t);
}



static double LerpDoubleClamped( double a, double b, double t ) {
    t = Clamp01( t );
    return ( 1.f - t ) * a + t * b;
}



static float CbLerpDoubleClamped( double a, double b, double t ) {
    t = Clamp01( t );
    return CbFloatLerp(a,b,t);
}





/// <summary>
/// Normalizes the value within a range. Example: (value = 8, min = 7, max = 24) = (float)0.0588235...
/// </summary>
/// <param name="value"></param>
/// <param name="minPossibleValue"></param>
/// <param name="maxPossibleValue"></param>
/// <returns></returns>
static double NormalizeDoubleInRange(double value, double minPossibleValue, double maxPossibleValue) {
    double normalizedValue = 0.f;
    double checkedMin = MIN(minPossibleValue,maxPossibleValue);
    double checkedMax = MAX(minPossibleValue,maxPossibleValue);

    if(value < checkedMin || (checkedMax - checkedMin == 0)) {
        normalizedValue = 0;
    }
    else if(value > checkedMax || checkedMin == checkedMax) {
        normalizedValue = 1;
    }
    else {
        normalizedValue = ((value - checkedMin) / (checkedMax - checkedMin));
    }

    return normalizedValue;
}

#pragma endregion


#pragma region CONSTRUCTORS_DESTRUCTORS

/**
* \brief Constructor
*/
template<typename T>
grng<T>::grng()
{
    static_assert(std::is_integral<T>::value, "T must be an integral number");
    selectedAlgorithm = 0;
    m_gdtSeed = 0;
    m_gdtSeed |= 6256256;
    m_udtAlgorithmSelection = Random_Algorithm_AdaptedLehmer32;
    selectedAlgorithm = AdaptedLehmer32;
}



/**
* \brief Constructor
*/
template<typename T>
template<typename U>
grng<T>::grng(grng<U> grngtoCopy)
{
    static_assert(std::is_integral<U>::value, "U must be an integral numbers. Howd you initialize a class without that?");
    m_gdtSeed = grngtoCopy.GetSeed();
    SetAlgorithm(grngtoCopy.GetAlgorithm());
}



/**
* \brief Constructor
*/
template<typename T>
grng<T>::grng(const T newSeed)
{
    static_assert(std::is_integral<T>::value, "T must be an integral number");
    m_gdtSeed = newSeed;
    m_udtAlgorithmSelection = Random_Algorithm_AdaptedLehmer32;
    selectedAlgorithm = AdaptedLehmer32;
}



/**
* \brief Constructor
*/
template<typename T>
grng<T>::grng(const T newSeed, AlgorithmChoice_t algorithmSelection)
{
    static_assert(std::is_integral<T>::value, "T must be an integral number");
    m_gdtSeed = newSeed;

    

    SetAlgorithm(algorithmSelection);
}



/**
* \brief Constructor
*/
template<typename T>
grng<T>::grng(const char* seedPointer)
{
    selectedAlgorithm = 0;
    m_gdtSeed = 0;
    
    //Set selected algorithm
    m_udtAlgorithmSelection = Random_Algorithm_AdaptedLehmer32;

    //Loop through the seed pointer and create the seed
    while (*seedPointer)
    {
        m_gdtSeed += (*seedPointer++);
    }

    //Set the choice of algorithm
    selectedAlgorithm = AdaptedLehmer32;

}



/**
* \brief Constructor
*/
template<typename T>
grng<T>::grng(const char* seedPointer, AlgorithmChoice_t algorithmSelection)
{
    selectedAlgorithm = 0;
    m_gdtSeed = 0;


    //Loop through the seed pointer and create the seed
    while (*seedPointer)
    {
        m_gdtSeed += (*seedPointer++);
    }

    //Set the choice of algorithm
    SetAlgorithm(algorithmSelection);

}



/// <summary>
/// Constructor
/// </summary>
/// <param name="seedString"></param>
template<typename T>
grng<T>::grng(const std::string seedString)
{
    //Declare a hasher for hashing the string
    std::hash<std::string> seedHasher;

    //Hash the string and set the seed to it
    m_gdtSeed = (T)seedHasher(seedString);

    //Set selected algorithm
    m_udtAlgorithmSelection = Random_Algorithm_AdaptedLehmer32;

    //Set the choice of algorithm
    selectedAlgorithm = AdaptedLehmer32;
}



/// <summary>
/// Constructor
/// </summary>
/// <param name="seedString"></param>
/// <param name="algorithmSelection"></param>
template<typename T>
grng<T>::grng(const std::string seedString, AlgorithmChoice_t algorithmSelection)
{
    //Declare a hasher for hashing the string
    std::hash<std::string> seedHasher;

    //Hash the string and set the seed to it
    m_gdtSeed = (T)seedHasher(seedString);

    //Set the choice of algorithm
    SetAlgorithm(algorithmSelection);
}



/**
* \brief Destructor
*/
template<typename T>
grng<T>::~grng()
{
    m_gdtSeed = 0;
    selectedAlgorithm = 0;
}



#pragma endregion



#pragma region OPERATOR_OVERLOADS


template<typename T>
void grng<T>::operator=(const grng<T> otherGrng)
{
    m_gdtSeed = otherGrng.GetSeed();
    SetAlgorithm(otherGrng.GetAlgorithm());
}



template<typename T>
void grng<T>::operator=(const T seedToCopy)
{
    m_gdtSeed = seedToCopy;
}



template<typename T>
void grng<T>::operator=(const AlgorithmChoice_t selectedAlgorithm)
{
    SetAlgorithm(selectedAlgorithm);
}



template<typename T>
bool grng<T>::operator==(const grng<T> otherGrng)
{
    if (otherGrng.GetSeed() == m_gdtSeed && otherGrng.GetAlgorithm() == m_udtAlgorithmSelection)
    {
        return true;
    }
    else
    {
        return false;
    }
}


template<typename T>
bool grng<T>::operator!=(const grng<T> otherGrng)
{
    if (otherGrng.GetSeed() == m_gdtSeed && otherGrng.GetAlgorithm() == m_udtAlgorithmSelection)
    {
        return false;
    }
    else
    {
        return true;
    }
}



template<typename T>
void grng<T>::operator&=(const grng<T> otherGrng)
{
    this.m_gdtSeed &= otherGrng.GetSeed();
}


template<typename T>
void grng<T>::operator|=(const grng<T> otherGrng)
{
    this.m_gdtSeed |= otherGrng.GetSeed();
}


template<typename T>
void grng<T>::operator^=(const grng<T> otherGrng)
{
    m_gdtSeed ^= otherGrng.GetSeed();
}



template<typename T>
bool operator>(const grng<T>& grngLeft, const grng<T>& grngRight)
{
    return (grngLeft.GetSeed() > grngRight.GetSeed());
}



template<typename T>
bool operator<(const grng<T>& grngLeft, const grng<T>& grngRight)
{
    return (grngLeft.GetSeed() < grngRight.GetSeed());
}


template<typename T>
bool operator>=(const grng<T>& grngLeft, const grng<T>& grngRight)
{
    return (grngLeft.GetSeed() >= grngRight.GetSeed());
}



template<typename T>
bool operator<=(const grng<T>& grngLeft, const grng<T>& grngRight)
{
    return (grngLeft.GetSeed() <= grngRight.GetSeed());
}



template<typename T>
T operator&(const grng<T>& grngLeft, const grng<T>& grngRight)
{
    return (T)(grngLeft.GetSeed() & grngRight.GetSeed());
}

template<typename T>
T operator|(const grng<T>& grngLeft, const grng<T>& grngRight)
{
    return (T)(grngLeft.GetSeed() | grngRight.GetSeed());
}


template<typename T>
T operator^(const grng<T>& grngLeft, const grng<T>& grngRight)
{
    return (T)(grngLeft.GetSeed() ^ grngRight.GetSeed());
}


#pragma endregion






/**
* \brief Sets the classes random algorithm
*/
template<typename T>
void grng<T>::SetAlgorithm(AlgorithmChoice_t algorithmSelection)
{

    //Set selected algorithm
    m_udtAlgorithmSelection = algorithmSelection;

    switch(algorithmSelection)
    {

    case Random_Algorithm_AdaptedLehmer32:
        selectedAlgorithm = AdaptedLehmer32;
    break;

    case Random_Algorithm_Lehmer64:
        selectedAlgorithm = Lehmer64;
    break;

    case Random_Algorithm_xor8:
        selectedAlgorithm = xor8;
    break;

    case Random_Algorithm_xor16:
        selectedAlgorithm = xor16;
    break;

    case Random_Algorithm_xor17:
        selectedAlgorithm = xor17;
    break;

    case Random_Algorithm_xor23:
        selectedAlgorithm = xor23;
    break;

    case Random_Algorithm_xor32:
        selectedAlgorithm = xor32;
    break;

    case Random_Algorithm_xor128:
        selectedAlgorithm = xor128;
    break;

    case Random_Algorithm_Wyhash:
        selectedAlgorithm = wyhash;
    break;

    default:
        selectedAlgorithm = AdaptedLehmer32;
    break;


    }
}




template<typename T>
T grng<T>::Next()
{
    T randVal = selectedAlgorithm(m_gdtSeed);
    m_gdtSeed = selectedAlgorithm(randVal);
    return randVal;
}



template<typename T>
T grng<T>::Next(T maxValue)
{
    return (T)NextFloat((float)maxValue);
}



template<typename T>
T grng<T>::Range(T minValue, T maxValue)
{
    return (T)RangeFloat((float)minValue, (float)maxValue);
}



/**
* \brief Returns a random double
*/
template<typename T>
double grng<T>::NextDouble()
{
    T randVal = selectedAlgorithm(m_gdtSeed);
    m_gdtSeed = selectedAlgorithm(randVal);
    return NormalizeDoubleInRange((double)randVal,(double)-0x7fffffff,0x7fffffff);
}



/**
* \brief Returns a random double
*/
template<typename T>
double grng<T>::NextDouble(double maxValue)
{
    T randVal = selectedAlgorithm(m_gdtSeed);
    m_gdtSeed = selectedAlgorithm(randVal);
    return NormalizeDoubleInRange((double)randVal,(double)-0x7fffffff,maxValue);
}



/**
* \brief Returns a random float
*/
template<typename T>
float grng<T>::NextFloat()
{
    T randVal = selectedAlgorithm(m_gdtSeed);
    m_gdtSeed = selectedAlgorithm(randVal);
    return (float)NormalizeDoubleInRange((double)randVal,(double)-0x7fffffff,(double)0x7fffffff);
}



/**
* \brief Returns a random float
*/
template<typename T>
float grng<T>::NextFloat(float maxFloat)
{
    T randVal = selectedAlgorithm(m_gdtSeed);
    m_gdtSeed = selectedAlgorithm(randVal);
    return (float)NormalizeDoubleInRange((double)randVal,(double)-0x7fffffff,(double)maxFloat);
}



/**
* \brief Returns a random int
*/
template<typename T>
int grng<T>::NextInt()
{
    T randVal = selectedAlgorithm(m_gdtSeed);
    m_gdtSeed = selectedAlgorithm(randVal);
    return (int) randVal;
}



/**
* \brief Returns a random int
*/
template<typename T>
int grng<T>::NextInt(int maxInt)
{
    return (int)std::floor(NextFloat((float)maxInt));
}



/**
* \brief Returns a random boolean
*/
template<typename T>
bool grng<T>::NextBool()
{
    float nxtFloat = NextFloat();
    return ((nxtFloat > 0.5f) ? true : false);
}



/**
* \brief Returns a value within the passed range
*/
template<typename T>
double grng<T>::RangeDouble(double minValue, double maxValue) {
    double randVal = NextDouble();
    return (double)NormalizeDoubleInRange((double)randVal,(double)minValue,(double)maxValue);
}



/**
* \brief Returns a value within the passed range
*/
template<typename T>
float grng<T>::RangeFloat(float minValue, float maxValue) {
    float randVal = NextFloat();
    if(randVal > maxValue) randVal = maxValue;
    else if(randVal < minValue) randVal = minValue;
    else
    {
        randVal = (1 -  randVal) * minValue + randVal * maxValue;
    }
    return randVal;
}



/**
* \brief Returns a value within the passed range
*/
template<typename T>
int grng<T>::RangeInt(int minValue, int maxValue) {
    return (int)std::floor(RangeFloat((float)minValue, (float)maxValue));
}



/**
* \brief Returns a random percentage
*/
template<typename T>
float grng<T>::NextPercentage() {
    int randVal = selectedAlgorithm(m_gdtSeed);
    m_gdtSeed = selectedAlgorithm(randVal);
    return RangeFloat(0.0f,100.0f);
}



/**
* \brief Returns a random sign value
*/
template<typename T>
float grng<T>::Sign() {
    return  ((NextBool()) ? -1 : 1);
}



/**
* \brief Creates a random value based on distribution around a point
*/
template<typename T>
float grng<T>::GaussianValue() {
    float value1 = 0;
    float value2 = 0;
    float s = 0; //Idk what this one is supposed to be named


    do
    {

        value1 = 2.0f * RangeFloat(0.0f, 1.0f) - 1.0f;
        value2 = 2.0f * RangeFloat(0.0f, 1.0f) - 1.0f;
        s = (value1 * value1) + (value2 * value2);

    } while (s >= 1.0f || s == 0.0f);

    s = std::sqrt((-2.0f * std::log(s)) / s);

    return value1 * s;
}



/**
* \brief Creates a random value based on distribution around a point
*/
template<typename T>
float grng<T>::Gaussian(float center, float deviation)
{
    return (center + GaussianValue() * deviation);
}



/**
* \brief Creates a gaussian value within a range
*/
template<typename T>
float grng<T>::GaussianRange(float deviation, float minValue, float maxValue)
{

    float newRand = 0;
    float a = minValue;
    float b = maxValue;

    if(minValue > maxValue)
    {
        a = maxValue;
        b = minValue;
    }

    do
    {
        newRand = Gaussian(((a+b)/2), deviation);

        if (a == b) break;

    } while (newRand < a || newRand > b);

    return newRand;

}



/**
 * @brief Creates a value weighted towards 0
 * @param strength The strength of the weight, between 0 and 1
 * @return float
 */
 template<typename T>
float grng<T>::LowerBiasValue(float strength) {
    float t = NextFloat();

    strength = Clamp01(strength);

    // Avoid possible division by zero
    if (strength == 1) {
        return 0;
    }

    // Remap strength for nicer input -> output relationship
    float k = Clamp01 (1 - strength);
    k = k * k * k - 1;

    return Clamp01 ((t + t * k) / (t * k + 1));
}



/**
 * @brief Creates a value weighted towards 1
 * @param strength The strength of the weight, between 0 and 1
 * @return float
 */
 template<typename T>
float grng<T>::UpperBiasValue(float strength) {
     return  (1 - LowerBiasValue((strength)));
}



/**
 * @brief Creates a value weighted towards the extremes of 0 and 1
 * @param strength The strength of the weight, between 0 and 1
 * @return float
 */
 template<typename T>
float grng<T>::ExtremesBiasValue(float strength) {
    float t = LowerBiasValue((strength));
    return(NextBool() ? 1-t : t);
}



/**
 * @brief Creates a value weighted towards 0.5
 * @param strength The strength of the weight, between 0 and 1
 * @return float
 */
 template<typename T>
float grng<T>::CenterBiasValue(float strength) {
    float t = LowerBiasValue((strength));
    return (0.5f + t * 0.5f * Sign());
}



/**
 * @brief Creates a value weighted towards the weight passed
 *
 *
 * @param weight The weight to use \n
 * 1 = LowerBiasValue \n
 * 2 = UpperBiasValue \n
 * 3 = CenterBiasValue \n
 * 4 = ExtremesBiasValue \n
 * Any other = NextFloat \n
 * @param strength The strength of the weight, between 0 and 1
 * @return float
 */
 template<typename T>
float grng<T>::WeightedValue(RandomWeight_t weight, float strength) {

    float randVal = 0;
    switch(weight) {
        case Random_Weight_Lower:
            randVal = LowerBiasValue(strength);
            break;
        case Random_Weight_Upper:
            randVal = UpperBiasValue(strength);
            break;

        case Random_Weight_Center:
            randVal = CenterBiasValue(strength);
            break;

        case Random_Weight_Ends:
            randVal = ExtremesBiasValue(strength);
            break;

        default:
            randVal = NextFloat();
            break;
    }



    return randVal;
}

/**
* \brief Creates Value Noise
*/
template<typename T>
long grng<T>::ValueNoise3DInt(int x, int y, int z, int seedValue)
{
    long n = (NextInt() * x + NextInt() * y + NextInt() * z +
                m_gdtSeed * seedValue) & 0x7fffffff;
    n = (n >> 13) ^ n;
    return (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
}


/**
* \brief Creates Value Noise
*/
template<typename T>
long grng<T>::ValueNoise2DInt(int x, int y, int seedValue)
{
    long n = (NextInt() * x + NextInt() * y +
                m_gdtSeed * seedValue) & 0x7fffffff;
    n = (n >> 13) ^ n;
    return (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
}


/**
* \brief Creates Value Noise
*/
template<typename T>
long grng<T>::ValueNoise1DInt(int x, int seedValue)
{
    long n = (NextInt() * x + m_gdtSeed * seedValue) & 0x7fffffff;
    n = (n >> 13) ^ n;
    return (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
}


/**
* \brief Creates Value Noise
*/
template<typename T>
double grng<T>::ValueNoise3D(int x, int y, int z, int seedValue)
{
    return 1.0 - (ValueNoise3DInt(x, y, z, seedValue) / 1073741824.0);
}


/**
* \brief Creates Value Noise
*/
template<typename T>
double grng<T>::ValueNoise2D(int x, int y, int seedValue)
{
    return 1.0 - (ValueNoise2DInt(x, y, seedValue) / 1073741824.0);
}


/**
* \brief Creates Value Noise
*/
template<typename T>
double grng<T>::ValueNoise1D(int x, int seedValue)
{
    return 1.0 - (ValueNoise1DInt(x, seedValue) / 1073741824.0);
}



/// <summary>
/// Returns the output value for the given input coordinates.
/// </summary>
/// <param name="x">The input coordinate on the x-axis.</param>
/// <returns>The resulting output value.</returns>
template<typename T>
double grng<T>::Voronoi1D(double x, double frequency, bool useDistance, double displacement)
{
    x *= frequency * NextDouble();
    double xi = (x > 0.0 ? (int)x : (int)x - 1);
    double md = 2147483647.0;
    double xc = 0;

        for (double xcu = xi - 2; xcu <= xi + 2; xcu++)
        {
            double xp = xcu + ValueNoise1D(xcu, m_gdtSeed);
            double xd = xp - x;
            double d = xd * xd;
            if (d < md)
            {
                md = d;
                xc = xp;
            }
        }


    double v;

    if (useDistance)
    {
        double xd = xc - x;

        v = (std::sqrt(xd * xd)) * SQRT3 - 1.0;
    }
    else
    {
        v = 0.0;
    }
    return v + (displacement * ValueNoise1D(((int)std::floor(xc)), 0));
}


/// <summary>
/// Returns the output value for the given input coordinates.
/// </summary>
/// <param name="x">The input coordinate on the x-axis.</param>
/// <param name="y">The input coordinate on the y-axis.</param>
/// <param name="z">The input coordinate on the z-axis.</param>
/// <returns>The resulting output value.</returns>
template<typename T>
double grng<T>::Voronoi2D(double x, double y, double frequency, bool useDistance, double displacement)
{
    x *= frequency * NextDouble();
    y *= frequency * NextDouble();
    double xi = (x > 0.0 ? (int)x : (int)x - 1);
    double iy = (y > 0.0 ? (int)y : (int)y - 1);
    double md = 2147483647.0;
    double xc = 0;
    double yc = 0;
    for (double ycu = iy - 2; ycu <= iy + 2; ycu++)
    {
        for (double xcu = xi - 2; xcu <= xi + 2; xcu++)
        {
            double xp = xcu + ValueNoise2D(xcu, ycu, m_gdtSeed);
            double yp = ycu + ValueNoise2D(xcu, ycu, m_gdtSeed + 1);
            double xd = xp - x;
            double yd = yp - y;
            double d = xd * xd + yd * yd;
            if (d < md)
            {
                md = d;
                xc = xp;
                yc = yp;
            }
        }
    }

    double v;
    if (useDistance)
    {
        double xd = xc - x;
        double yd = yc - y;

        v = (std::sqrt(xd * xd + yd * yd)) * SQRT3 - 1.0;
    }
    else
    {
        v = 0.0;
    }
    return v + (displacement * ValueNoise2D(((int)std::floor(xc)), ((int)std::floor(yc)), 0));
}



/// <summary>
/// Returns the output value for the given input coordinates.
/// </summary>
/// <param name="x">The input coordinate on the x-axis.</param>
/// <param name="y">The input coordinate on the y-axis.</param>
/// <param name="z">The input coordinate on the z-axis.</param>
/// <returns>The resulting output value.</returns>
template<typename T>
double grng<T>::Voronoi3D(double x, double y, double z, double frequency, bool useDistance, double displacement)
{
    x *= frequency * NextDouble();
    y *= frequency * NextDouble();
    z *= frequency * NextDouble();
    double xi = (x > 0.0 ? (int)x : (int)x - 1);
    double iy = (y > 0.0 ? (int)y : (int)y - 1);
    double iz = (z > 0.0 ? (int)z : (int)z - 1);
    double md = 2147483647.0;
    double xc = 0;
    double yc = 0;
    double zc = 0;
    for (double zcu = iz - 2; zcu <= iz + 2; zcu++)
    {
        for (double ycu = iy - 2; ycu <= iy + 2; ycu++)
        {
            for (double xcu = xi - 2; xcu <= xi + 2; xcu++)
            {
                double xp = xcu + ValueNoise3D(xcu, ycu, zcu, m_gdtSeed);
                double yp = ycu + ValueNoise3D(xcu, ycu, zcu, m_gdtSeed + 1);
                double zp = zcu + ValueNoise3D(xcu, ycu, zcu, m_gdtSeed + 2);
                double xd = xp - x;
                double yd = yp - y;
                double zd = zp - z;
                double d = xd * xd + yd * yd + zd * zd;
                if (d < md)
                {
                    md = d;
                    xc = xp;
                    yc = yp;
                    zc = zp;
                }
            }
        }
    }
    double v;
    if (useDistance)
    {
        double xd = xc - x;
        double yd = yc - y;
        double zd = zc - z;

        v = (std::sqrt(xd * xd + yd * yd + zd * zd)) * SQRT3 - 1.0;
    }
    else
    {
        v = 0.0;
    }
    return v + (displacement * ValueNoise3D(((int)std::floor(xc)), ((int)std::floor(yc)),
        ((int)std::floor(zc)), 0));
}



/// <summary>
/// 1D Perlin Noise
/// </summary>
/// <param name="x"></param>
/// <param name="randomPermTable"></param>
/// <returns></returns>
template<typename T>
float grng<T>::Perlin1D(float x) {
    int newX = (int)std::floor(x) & 0xff;
    x -= (int)std::floor(x);
    float fadedX = FadeFloat(x);
    return CbFloatLerp(fadedX, FloatGradient(PermutationTable[newX],x),FloatGradient(PermutationTable[newX+1],x-1))*2;
}



/// <summary>
/// 2D Perlin Noise
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="randomPermTable"></param>
/// <returns></returns>
template<typename T>
float grng<T>::Perlin2D(float x, float y) {
    int newX = (int)std::floor(x) & 0xff;
    int newY = (int)std::floor(y) & 0xff;
    x -=(int)std::floor(x);
    y -= (int)std::floor(y);
    float fadedX = FadeFloat(x);
    float fadedY = FadeFloat(y);
    int A = (PermutationTable[newX] + newY) & 0xff;
    int B = (PermutationTable[newX + 1] + newY) & 0xff;

    float l1 = CbFloatLerp(fadedY, CbFloatLerp(fadedX, FloatGradient2D(PermutationTable[A],x,y),FloatGradient2D(PermutationTable[B], x-1,y)),
        CbFloatLerp(fadedX, FloatGradient2D(PermutationTable[A+1],x,y-1), FloatGradient2D(PermutationTable[B+1], x-1, y-1)));

    return l1;
}



/// <summary>
/// 3D Perlin Noise
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
/// <param name="randomPermTable"></param>
/// <returns></returns>
template<typename T>
float grng<T>::Perlin3D(float x, float y, float z) {

    int newX = (int)std::floor(x) & 0xff;
    int newY = (int)std::floor(y) & 0xff;
    int newZ = (int)std::floor(z) & 0xff;
    x -= (int)std::floor(x);
    y -= (int)std::floor(y);
    z -= (int)std::floor(y);
    float fadedX = FadeFloat(x);
    float fadedY = FadeFloat(y);
    float fadedZ = FadeFloat(z);

    int A = (PermutationTable[newX] + newY) & 0xff;
    int B = (PermutationTable[newX + 1] + newY) & 0xff;
    int AA = (PermutationTable[A] + newZ) & 0xff;
    int BA = (PermutationTable[B] + newZ) & 0xff;
    int AB = (PermutationTable[A+1] + newZ) & 0xff;
    int BB = (PermutationTable[B+1] + newZ) & 0xff;

    float l1 = CbFloatLerp(fadedZ, CbFloatLerp(fadedY, CbFloatLerp(fadedX, FloatGradient3D(PermutationTable[AA], x  , y  , z   ),
        FloatGradient3D(PermutationTable[BA], x-1, y  , z   )),
        CbFloatLerp(fadedX, FloatGradient3D(PermutationTable[AB], x  , y-1, z   ),
        FloatGradient3D(PermutationTable[BB], x-1, y-1, z   ))),
        CbFloatLerp(fadedY, CbFloatLerp(fadedX, FloatGradient3D(PermutationTable[AA+1], x  , y  , z-1 ),
        FloatGradient3D(PermutationTable[BA+1], x-1, y  , z-1 )),
        CbFloatLerp(fadedX, FloatGradient3D(PermutationTable[AB+1], x  , y-1, z-1 ),
        FloatGradient3D(PermutationTable[BB+1], x-1, y-1, z-1 ))));

    //Changed HERE
    return l1;
}



/// <summary>
/// Ken perlins improved noise
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
/// <returns></returns>
template<typename T>
double grng<T>::ImprovedNoise(double x, double y) {


    //var PermutationTable = CreatePermutationTable();
    double z = 0.01;
    x +=NextDouble();
    y+=NextDouble();
    z+=NextDouble();

    // FIND UNIT CUBE THAT CONTAINS POINT.
    int X = (int)std::floor(x) & 255;
    int Y = (int)std::floor(y) & 255;
    int Z = (int)std::floor(z) & 255;
    x -= std::floor(x);                                // FIND RELATIVE X,Y,Z
    y -= std::floor(y);                                // OF POINT IN CUBE.
    z -= std::floor(z);
    double u = std::floor(x);                                // COMPUTE FADE CURVES
    double v = std::floor(y);                                // FOR EACH OF X,Y,Z.
    double w = std::floor(z);

    // HASH COORDINATES OF THE 8 CUBE CORNERS,
    int A = PermutationTable[X  ]+Y, AA = PermutationTable[A]+Z, AB = PermutationTable[A+1]+Z;
    int B = PermutationTable[X+1]+Y, BA = PermutationTable[B]+Z, BB = PermutationTable[B+1]+Z;
    // AND ADD BLENDED RESULTS FROM  8 CORNERS OF CUBE
    return CbDoubleLerp(w, CbDoubleLerp(v, CbDoubleLerp(u, DoubleGradient(PermutationTable[AA], x  , y  , z   ),
        DoubleGradient(PermutationTable[BA], x-1, y  , z   )),
        CbDoubleLerp(u, DoubleGradient(PermutationTable[AB], x  , y-1, z   ),
        DoubleGradient(PermutationTable[BB], x-1, y-1, z   ))),
        CbDoubleLerp(v, CbDoubleLerp(u, DoubleGradient(PermutationTable[AA+1], x  , y  , z-1 ),
        DoubleGradient(PermutationTable[BA+1], x-1, y  , z-1 )),
        CbDoubleLerp(u, DoubleGradient(PermutationTable[AB+1], x  , y-1, z-1 ),
        DoubleGradient(PermutationTable[BB+1], x-1, y-1, z-1 ))));
}



/// <summary>
/// Ken perlins improved noise
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
/// <returns></returns>
template<typename T>
double grng<T>::ImprovedNoise(double x, double y, double z) {


    //var PermutationTable = CreatePermutationTable();

    x +=NextDouble();
    y+=NextDouble();
    z+=NextDouble();

    // FIND UNIT CUBE THAT CONTAINS POINT.
    int X = (int)std::floor(x) & 255;
    int Y = (int)std::floor(y) & 255;
    int Z = (int)std::floor(z) & 255;
    x -= std::floor(x);                                // FIND RELATIVE X,Y,Z
    y -= std::floor(y);                                // OF POINT IN CUBE.
    z -= std::floor(z);
    double u = std::floor(x);                                // COMPUTE FADE CURVES
    double v = std::floor(y);                                // FOR EACH OF X,Y,Z.
    double w = std::floor(z);

    // HASH COORDINATES OF THE 8 CUBE CORNERS,
    int A = PermutationTable[X  ]+Y, AA = PermutationTable[A]+Z, AB = PermutationTable[A+1]+Z;
    int B = PermutationTable[X+1]+Y, BA = PermutationTable[B]+Z, BB = PermutationTable[B+1]+Z;
    // AND ADD BLENDED RESULTS FROM  8 CORNERS OF CUBE
    return CbDoubleLerp(w, CbDoubleLerp(v, CbDoubleLerp(u, DoubleGradient(PermutationTable[AA], x  , y  , z   ),
        DoubleGradient(PermutationTable[BA], x-1, y  , z   )),
        CbDoubleLerp(u, DoubleGradient(PermutationTable[AB], x  , y-1, z   ),
        DoubleGradient(PermutationTable[BB], x-1, y-1, z   ))),
        CbDoubleLerp(v, CbDoubleLerp(u, DoubleGradient(PermutationTable[AA+1], x  , y  , z-1 ),
        DoubleGradient(PermutationTable[BA+1], x-1, y  , z-1 )),
        CbDoubleLerp(u, DoubleGradient(PermutationTable[AB+1], x  , y-1, z-1 ),
        DoubleGradient(PermutationTable[BB+1], x-1, y-1, z-1 ))));
}




/// <summary>
/// Returns gradient value
/// </summary>
/// <param name="hash"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns></returns>
template<typename T>
float grng<T>::FloatGradient(int hash, float x) {
    return ((hash&1) == 0 ? x : -x);
}





/// <summary>
/// Returns gradient value
/// </summary>
/// <param name="hash"></param>
/// <param name="x"></param>
/// <returns></returns>
template<typename T>
float grng<T>::FloatGradient2D(int hash, float x, float y) {
    return ((hash & 1) == 0 ? x : -x) + ((hash & 2) == 0 ? y : -y);
}




/// <summary>
/// Returns gradient value
/// </summary>
/// <param name="hash"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
/// <returns></returns>
template<typename T>
float grng<T>::FloatGradient3D(int hash, float x, float y, float z) {
    int h = hash & 15;
    float u = h<8 ? x : y,
            v = h<4 ? y : h==12||h==14 ? x : z;
    return ((h&1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
}



/// <summary>
/// Returns gradient value
/// </summary>
/// <param name="hash"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
/// <returns></returns>
template<typename T>
double grng<T>::DoubleGradient(int hash, double x, double y, double z) {
    int h = hash & 15;
    double u = h<8 ? x : y,
            v = h<4 ? y : h==12||h==14 ? x : z;
    return ((h&1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
}



/// <summary>
/// Creates a permutation table with defaults of length 512 with values from 0 - 255 inclusive
/// </summary>
/// <param name="tableSize"></param>
/// <param name="maxSize"></param>
/// <returns>A new permutation table</returns>
template<typename T>
unsigned int* grng<T>::CreatePermutationTable(unsigned int tableSize, unsigned int maxSize) {

    unsigned int newPermutation[tableSize] = {0};
    if(maxSize > 0 && tableSize > 0)
    {
        for(int i = 0, j = 0; i < tableSize; i++) {
            if(i > maxSize) {
                newPermutation[i] = newPermutation[j];
                j++;
            }
            else {
                newPermutation[i] = i;
            }
        }
    }
    return newPermutation;
}



/// <summary>
/// Creates a permutation table with defaults of length 512 with values from 0 - 255 inclusive
/// </summary>
/// <returns>A new permutation table</returns>
template<typename T>
unsigned int* grng<T>::CreatePermutationTable() {

    unsigned int newPermutation[512] = {0};

    for(int i = 0, j = 0; i < 512; i++) {
        if(i > 255) {
            newPermutation[i] = newPermutation[j];
            j++;
        }
        else {
            newPermutation[i] = i;
        }
    }

    Shuffle(newPermutation);
    
    return newPermutation;
}




/// <summary>
/// Creates offset perlin noise
/// </summary>
template<typename T>
float grng<T>::OffsetPerlinNoise2D(int xIteration, int yIteration, float noiseScale, float xOffset, float yOffset,
float centerX, float centerY, float frequency)
{
    float perlinValue = 0.0f;
    float devisor = (noiseScale != 0 && frequency != 0) ? noiseScale * frequency : 1;
    float x = (xIteration - centerX + xOffset) / devisor;
    float y = (yIteration - centerY - yOffset) / devisor;
    perlinValue = Perlin2D(x,y)*2-1;
    return perlinValue;

}



/// <summary>
/// Creates offset perlin noise
/// </summary>
template<typename T>
float grng<T>::OffsetPerlinNoise3D(int xIteration, int yIteration, int zIteration, float noiseScale, float xOffset, float yOffset, float zOffset,
    float centerX, float centerY, float centerZ, float frequency)
{
    float perlinValue = 0.0f;
    float devisor = (noiseScale != 0 && frequency != 0) ? noiseScale * frequency : 1;
    float x = (xIteration - centerX + xOffset) / devisor;
    float y = (yIteration - centerY - yOffset) / devisor;
    float z = (zIteration - centerZ + zOffset) / devisor;

    perlinValue = Perlin3D(x, y, z) * 2 - 1;

    return perlinValue;

}



/// <summary>
/// Creates perlin fractal brownian octave noise
/// </summary>
template<typename T>
float** grng<T>::PerlinOctaves2D(int octaveAmount, int resolution, float offsetX, float offsetY,
float noisePersistance, float noiseLacunarity, float noiseScale, float roughness, bool normalizeHeightGlobally)
{
    if(roughness == 0) roughness = 10000;
    if(octaveAmount < 1) octaveAmount = 1;
    if(noisePersistance <= 0) noisePersistance = 0.001f;
    if(noiseLacunarity < 0.01f) noiseLacunarity = 0.01f;
    if(resolution <= 0) return NULL;


    float maximumHeight = -0x7fffffff;
    float minimumHeight = 0x7fffffff;

    float **noiseMap = 0;
    noiseMap = new float*[resolution+1];

    float octaveOffsetsX[octaveAmount] = {0};
    float octaveOffsetsY[octaveAmount] = {0};
    float center = resolution/2;
    float amplitude = 1;
    float frequency = 1;
    int x = 0;
    int y = 0;

    //GetOctaves;
    for (int i = 0; i < octaveAmount; i++)
    {
        float newX = RangeFloat(-roughness, roughness) + offsetX + center;
        float newY = RangeFloat(-roughness, roughness) - offsetY - center;
        octaveOffsetsX[i] = newX;
        octaveOffsetsY[i] = newY;
    }

    for(x = 0; x < (resolution+1); x++)
    {
        noiseMap[x] = new float[resolution+1];

        for(y = 0; y < (resolution + 1); y++)
        {
            float noiseValue = 0;
            amplitude = 1;
            frequency = 1;
            for(int j = 0; j < octaveAmount; j++) {
                float noise = OffsetPerlinNoise2D(x,y,noiseScale,octaveOffsetsX[j], octaveOffsetsY[j],center,center,frequency);
                noiseValue += (noise * amplitude);
                amplitude *= noisePersistance;
                frequency *= noiseLacunarity;
            }

            noiseMap[x][y] = noiseValue;

            if (noiseValue < minimumHeight)
            {
                minimumHeight = noiseValue;
            }
            else if (noiseValue > maximumHeight)
            {
                maximumHeight = noiseValue;
            }

            if (normalizeHeightGlobally)
            {
                float normalizedHeight = (noiseMap[x][y] + 1) / (maximumHeight / 0.9f);
                noiseMap[x][y] = Clamp(normalizedHeight, 0, INT_MAX);

            }

        }

        if (normalizeHeightGlobally == false)
        {
            for (x = 0, y=0; x < resolution; y++)
            {
                if (y >= resolution)
                {
                    y = 0;
                    x++;
                }
                noiseMap[x][y] = InverseLerpClamped(minimumHeight, maximumHeight, noiseMap[x][y]);
			}
        }


    }



    for(int i = 0; i < SQR(resolution+1); i++) {
        noiseMap[i] = new float[resolution+1];
        amplitude = 1;
        frequency = 1;
        float noiseValue = 0;



        for(int j = 0; j < octaveAmount; j++) {
            float noise = OffsetPerlinNoise2D(x,y,noiseScale,octaveOffsetsX[j], octaveOffsetsY[j],center,center,frequency);
            noiseValue += (noise * amplitude);
            amplitude *= noisePersistance;
            frequency *= noiseLacunarity;
        }



        noiseMap[x][y] = noiseValue;

        y+=1;

        if(y >= resolution) {
            x+=1;
            y=0;
        }
        else if(x >= resolution) {
            break;
        }

    }

    return noiseMap;

}





/// <summary>
/// Returns the smallest value in x iterations
/// </summary>
/// <param name="iterations"></param>
/// <returns></returns>
template<typename T>
T grng<T>::SmallestRandom(int iterations) {
    T smallestValue = 1;
    for(int i = 0; i < iterations; i++) {
        smallestValue = MIN(smallestValue,Next());
    }

    return smallestValue;
}



/// <summary>
/// Returns the largest value in x iterations
/// </summary>
/// <param name="iterations"></param>
/// <returns></returns>
template<typename T>
T grng<T>::LargestRandom(int iterations) {
    T largestValue = -1;
    for(int i = 0; i < iterations; i++) {
        largestValue = MAX(largestValue,Next());
    }

    return largestValue;
}



/// <summary>
/// Returns the most centered of values in a range up to x iterations
/// </summary>
/// <param name="iterations"></param>
/// <returns></returns>
template<typename T>
T grng<T>::MostCenteredRandom(int iterations) {
    T centeredValue = 0;

    for(int i = 0; i < iterations; i++) {
        T rVal = Next();
        if(std::abs(rVal - 0.5f) < (centeredValue - 0.5f)) centeredValue = rVal;
    }

    return centeredValue;
}



/**
* \brief Returns a random element from the array
*
*/
template<typename T>
template<typename U>
U grng<T>::Element(U a[])
{
    return a[RangeInt(0, (sizeof(a) / sizeof(U))-1)];
}



/**
* \brief Shuffles the array into a random order
*
*/
template<typename T>
template<typename U>
void grng<T>::Shuffle(U a[])
{
    int aCount = (sizeof(a) / sizeof(U));
    for(int i = 0; i < aCount; i++) {
        int j = RangeInt(i,aCount-1);
        T temp = a[j];
        a[j] = a[i];
        a[i] = temp;
    }
}







#endif
