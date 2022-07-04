//Test file

#include <cstdio>
#include <iostream>

#include "grng.h"
#include "grandomAlgorithms.h"


int GetMainInput()
{
    int modeSelection = 0;
    
    std::cout << std::flush << std::endl;

    system("CLS");
    std::cout << "\tGRNG Random Numbers" << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;
    std::cout << "-2: Clear Screen" << std::endl;
    std::cout << "-1: Quit" << std::endl;
    std::cout << "0: Show help" << std::endl;
    std::cout << "1: Random Values" << std::endl;
    std::cout << "2: Random Ranges" << std::endl;
    std::cout << "3: Weighted Values" << std::endl;
    std::cout << "4: Most towards" << std::endl;
    std::cout << "5: Noise Values" << std::endl;
    std::cout << "6: Algorithms" << std::endl;
    std::cout << "7: GRNG setup" << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;

    while (modeSelection <= 0 || modeSelection >= 8)
    {
        std::cout << "\nEnter mode(0 for help): " << std::flush;
        if (!(std::cin >> modeSelection)) {
            std::cin.clear(); //clear bad input flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
            modeSelection = -99;
        }

        switch (modeSelection) {
        case -2:
            std::cout << std::flush << std::endl;
            system("CLS");
            std::cout << "\n\tGRNG Random Numbers" << std::endl;
            std::cout << "-----------------------------------------------------" << std::endl;
            std::cout << "-2: Clear Screen" << std::endl;
            std::cout << "-1: Quit" << std::endl;
            std::cout << "0: Show help" << std::endl;
            std::cout << "1: Random Values" << std::endl;
            std::cout << "2: Random Ranges" << std::endl;
            std::cout << "3: Weighted Values" << std::endl;
            std::cout << "4: Most towards" << std::endl;
            std::cout << "5: Noise Values" << std::endl;
            std::cout << "6: Algorithms" << std::endl;
            std::cout << "7: GRNG setup" << std::endl;
            std::cout << "-----------------------------------------------------" << std::endl;
            std::cout << std::flush << std::endl;
            break;

        case -1:
            return modeSelection;
            break;

        case 0:
            std::cout << "\n-----------------------------------------------------" << std::endl;
            std::cout << "-2: Clear Screen" << std::endl;
            std::cout << "-1: Quit" << std::endl;
            std::cout << "0: Show help" << std::endl;
            std::cout << "1: Random Values" << std::endl;
            std::cout << "2: Random Ranges" << std::endl;
            std::cout << "3: Weighted Values" << std::endl;
            std::cout << "4: Most towards" << std::endl;
            std::cout << "5: Noise Values" << std::endl;
            std::cout << "6: Algorithms" << std::endl;
            std::cout << "7: GRNG setup" << std::endl;
            std::cout << "-----------------------------------------------------" << std::endl;
            std::cout << std::flush << std::endl;
            break;


        default:
            if(modeSelection > 8) std::cout << "Incorrect entry! " << std::endl;
            else return modeSelection;
            break;
        };
    }

    return modeSelection;
}





template<typename T>
void ShowNext(grng<T> g);

template<typename T>
void ShowRanges(grng<T> g);

template<typename T>
void ShowWeightedValues(grng<T> g);

template<typename T>
void ShowRandomMostTowardsValues(grng<T> g);

template<typename T>
void ShowNoiseValues(grng<T> g);

void ShowAlgorithms();

template<typename T>
void GrngSetup(grng<T> &g);



int main()
{

    grng<int> g("Blarb");
    int input = 0;


    while (input != -1)
    {
        input = GetMainInput();
        switch (input)
        {
        case 1:
            ShowNext(g);
            break;

        case 2:
            ShowRanges(g);
            break;
        
        case 3:
            ShowWeightedValues(g);
            break;

        case 4:
            ShowRandomMostTowardsValues(g);
            break;

        case 5:
            ShowNoiseValues(g);
            break;
        case 6:
            ShowAlgorithms();
            break;
        case 7:
            GrngSetup(g);
            break;

        default: break;
        }
        
    }

    //
    //

    //std::cout << "Seed Phrase: Hello World!" << "\n";
    //std::cout << "Seed: " << g.GetSeed() << "\n";
    //
    //std::cout << "NextInt: "<< g.NextInt() << "\n";
    //std::cout << "NextInt: "<< g.NextInt() << "\n";
    //std::cout << "NextInt: " << g.NextInt() << "\n";
    //std::cout << "NextDouble: " <<g.NextDouble() << "\n";
    //std::cout << "NextFloat: " <<g.NextFloat() << "\n";
    //std::cout << "NextPercentage: " <<g.NextPercentage() << "%\n";
    //std::cout << "NextPercentage: " <<g.NextPercentage() << "%\n";
    //std::cout << "NextPercentage: " <<g.NextPercentage() << "%\n";
    //std::cout << "NextBool: " << (g.NextBool() ? "True": "False") << "\n";
    //std::cout << "NextBool: " << (g.NextBool() ? "True": "False") << "\n";
    //std::cout << "NextBool: " << (g.NextBool() ? "True": "False") << "\n";
    //std::cout << "NextBool: " << (g.NextBool() ? "True": "False") << "\n";
    //std::cout << "NextBool: " << (g.NextBool() ? "True": "False") << "\n";
    //std::cout << "NextBool: " << (g.NextBool() ? "True": "False") << "\n";
    //std::cout << "NextBool: " << (g.NextBool() ? "True": "False") << "\n";
    //std::cout << "NextBool: " << (g.NextBool() ? "True" : "False") << "\n";
    //std::cout << "Gaussian: " << g.Gaussian(3, 6) << "\n";
    //std::cout << "Improved Noise: " << g.ImprovedNoise(1,1,1) << "\n";
    //std::cout << "Improved Noise: " << g.ImprovedNoise(1,2,1) << "\n";
    //std::cout << "Improved Noise: " << g.ImprovedNoise(1,3,1) << "\n";
    //std::cout << "Improved Noise: " << g.ImprovedNoise(2,1,1) << "\n";
    //std::cout << "Voronoi2D: " << g.Voronoi2D(1, 2, 1, true, 5) << "\n";
    //std::cout << "\nVoronoi fun: " << "\n\n";
    //
    //for (int y = 0; y < 32; y++)
    //{
    //    std::cout << std::endl;
    //    for (int x = 0; x < 64; x++)
    //    {
    //        double currentVal = g.Voronoi2D(x, y, g.NextDouble(), true, g.Gaussian(5,3.0f));
    //        
    //        //double currentVal = g.Voronoi2D(x, y, g.NextDouble(), false, 5);
    //        if (currentVal > 0)
    //        {
    //            if (currentVal > 2)
    //            {
    //                std::cout << "^";
    //            }
    //            else
    //            {
    //                if(g.NextBool()) std::cout << "@";
    //                else std::cout << "~";
    //            }
    //        }
    //        else
    //        {
    //            std::cout << " ";
    //        }
    //    }
    //}

    
    std::cout << std::flush << std::endl;
    system("CLS");
    std::cout << "\n\n\nGood bye!\nPress enter to exit" << std::endl;
    getchar();
}




template<typename T>
void ShowNext(grng<T> g)
{

    int funcSelection = 0;
    float chancePercentage = 0;
    std::cout << std::flush << std::endl;
    system("CLS");
    std::cout <<"\tRANDOM VALUES" << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;
    std::cout << "-2: Clear Screen" << std::endl;
    std::cout << "-1: Quit" << std::endl;
    std::cout << "1: Next" << std::endl;
    std::cout << "2: NextDouble" << std::endl;
    std::cout << "3: NextFloat" << std::endl;
    std::cout << "4: NextInt" << std::endl;
    std::cout << "5: NextBool" << std::endl;
    std::cout << "6: NextPercentage" << std::endl;
    std::cout << "7: Sign" << std::endl;
    std::cout << "8: GaussianValue" << std::endl;
    std::cout << "9: ChanceRoll" << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;
    
    while (funcSelection != -1)
    {
        std::cout << "\nEnter your function selection for next values(0 for help): " << std::flush;
        if (!(std::cin >> funcSelection)) {
            std::cin.clear(); //clear bad input flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
            funcSelection = -99;
        }

        switch (funcSelection)
        {

        case -2:
            std::cout << std::flush << std::endl;
            system("CLS");
            std::cout << "\tRANDOM VALUES" << std::endl;
            std::cout << "-----------------------------------------------------" << std::endl;
            std::cout << "-2: Clear Screen" << std::endl;
            std::cout << "-1: Quit" << std::endl;
            std::cout << "1: Next" << std::endl;
            std::cout << "2: NextDouble" << std::endl;
            std::cout << "3: NextFloat" << std::endl;
            std::cout << "4: NextInt" << std::endl;
            std::cout << "5: NextBool" << std::endl;
            std::cout << "6: NextPercentage" << std::endl;
            std::cout << "7: Sign" << std::endl;
            std::cout << "8: GaussianValue" << std::endl;
            std::cout << "9: ChanceRoll" << std::endl;
            std::cout << "-----------------------------------------------------" << std::endl;
            break;

        case -1:
            std::cout << std::flush << std::endl;
            system("CLS");
            break;

        case 0:
            std::cout << "\n-----------------------------------------------------" << std::endl;
            std::cout << "-2: Clear Screen" << std::endl;
            std::cout << "-1: Quit" << std::endl;
            std::cout << "0: Show help" << std::endl;
            std::cout << "1: Next" << std::endl;
            std::cout << "2: NextDouble" << std::endl;
            std::cout << "3: NextFloat" << std::endl;
            std::cout << "4: NextInt" << std::endl;
            std::cout << "5: NextBool" << std::endl;
            std::cout << "6: NextPercentage" << std::endl;
            std::cout << "7: Sign" << std::endl;
            std::cout << "8: GaussianValue" << std::endl;
            std::cout << "9: ChanceRoll" << std::endl;
            std::cout << "-----------------------------------------------------" << std::endl;
            std::cout << std::flush << std::endl;
            break;

        case 1:
            std::cout << "Next: " << g.Next() << std::endl;
            break;

        case 2:
            std::cout << "NextDouble: " << g.NextDouble() << std::endl;
            break;

        case 3:
            std::cout << "NextFloat: " << g.NextFloat() << std::endl;
            break;

        case 4:
            std::cout << "NextInt: " << g.NextInt() << std::endl;
            break;

        case 5:
            std::cout << "NextBool: " << g.NextBool() << std::endl;
            break;

        case 6:
            std::cout << "NextPercentage: " << g.NextPercentage() << std::endl;
            break;

        case 7:
            std::cout << "Sign: " << g.Sign() << std::endl;
            break;

        case 8:
            std::cout << "GaussianValue: " << g.GaussianValue() << std::endl;
            break;

        case 9:
            std::cout << "Enter Percentage Chance for ~ vs @: " << std::flush;
            if (!(std::cin >> chancePercentage)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            std::cout << "ChanceRoll: " << g.ChanceRoll(chancePercentage) << std::endl;
            break;

        default:
            std::cout << "Incorrect entry! " << std::endl;
            break;
        };
    }


}

template<typename T>
void ShowRanges(grng<T> g)
{
    int funcSelection = 0;
    T tminValue = 0;
    T tmaxValue = 0;
    double dblminValue = 0;
    double dblmaxValue = 0;
    float sngminValue = 0;
    float sngmaxValue = 0;
    int intminValue = 0;
    int intmaxValue = 0;
    std::string buff;

    std::cout << std::flush << std::endl;
    system("CLS");
    std::cout << "\tRANDOM RANGE" << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;
    std::cout << "-2: Clear Screen" << std::endl;
    std::cout << "-1: Quit" << std::endl;
    std::cout << "1: Range" << std::endl;
    std::cout << "2: RangeDouble" << std::endl;
    std::cout << "3: RangeFloat" << std::endl;
    std::cout << "4: RangeInt" << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;

    while (funcSelection != -1)
    {
        std::cout << "\nEnter your function selection for range values(0 for help): " << std::flush;
        if (!(std::cin >> funcSelection)) {
            std::cin.clear(); //clear bad input flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
            funcSelection = -99;
        }

        

        switch (funcSelection)
        {

        case -2:
            std::cout << std::flush << std::endl;
            system("CLS");
            std::cout << "\tRANDOM RANGE" << std::endl;
            std::cout << "-----------------------------------------------------" << std::endl;
            std::cout << "-2: Clear Screen" << std::endl;
            std::cout << "-1: Quit" << std::endl;
            std::cout << "1: Range" << std::endl;
            std::cout << "2: RangeDouble" << std::endl;
            std::cout << "3: RangeFloat" << std::endl;
            std::cout << "4: RangeInt" << std::endl;
            std::cout << "-----------------------------------------------------" << std::endl;
            break;

        case -1:
            std::cout << std::flush << std::endl;
            system("CLS");
            break;

        case 0:
            std::cout << "\n-----------------------------------------------------" << std::endl;
            std::cout << "-2: Clear Screen" << std::endl;
            std::cout << "-1: Quit" << std::endl;
            std::cout << "1: Range" << std::endl;
            std::cout << "2: RangeDouble" << std::endl;
            std::cout << "3: RangeFloat" << std::endl;
            std::cout << "4: RangeInt" << std::endl;
            std::cout << "-----------------------------------------------------" << std::endl;
            std::cout << std::flush << std::endl;
            break;

        case 1:
            
            std::cout << "\nEnter Min value in range: " << std::flush;
            if (!(std::cin >> tminValue)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            std::cout << "\nEnter Max value in range: " << std::flush;
            
            if (!(std::cin >> tmaxValue)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            std::cout << "Range(" << tminValue << "-" << tmaxValue << "): " << g.Range(tminValue, tmaxValue) << std::endl;
            break;

        case 2:
            
            std::cout << "\nEnter Min value in range: " << std::flush;
            if (!(std::cin >> dblminValue)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            std::cout << "\nEnter Max value in range: " << std::flush;

            if (!(std::cin >> dblmaxValue)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            std::cout << "RangeDouble(" << dblminValue << "-" << dblmaxValue << "): " << g.RangeDouble(dblminValue, dblmaxValue) << std::endl;
            break;

        case 3:
            
            std::cout << "\nEnter Min value in range: " << std::flush;
            if (!(std::cin >> dblminValue)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            sngminValue = (float)dblminValue;
            std::cout << "\nEnter Max value in range: " << std::flush;

            if (!(std::cin >> dblmaxValue)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            sngmaxValue = (float)dblmaxValue;
            std::cout << "RangeFloat(" << sngminValue << "-" << sngmaxValue << "): " << g.RangeFloat(sngminValue, sngmaxValue) << std::endl;
            break;

        case 4:
            
            std::cout << "\nEnter Min value in range: " << std::flush;

            if (!(std::cin >> intminValue)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            std::cout << "\nEnter Max value in range: " << std::flush;

            if (!(std::cin >> intmaxValue)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            std::cout << "RangeInt(" << intminValue << "-" << intmaxValue << "): " << g.RangeInt(intminValue, intmaxValue) << std::endl;
            break;

        

        default:
            std::cout << "Incorrect entry! " << std::endl;
            break;
        };
    }
}

template<typename T>
void ShowWeightedValues(grng<T> g)
{
    int funcSelection = 0;
    float strengthValue = 0;
    std::cout << std::flush << std::endl;
    system("CLS");
    std::cout << "\tWEIGHTED VALUES" << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;
    std::cout << "-2: Clear Screen" << std::endl;
    std::cout << "-1: Quit" << std::endl;
    std::cout << "1: LowerBias" << std::endl;
    std::cout << "2: UpperBias" << std::endl;
    std::cout << "3: CenterBias" << std::endl;
    std::cout << "4: ExtremesBias" << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;

    while (funcSelection != -1)
    {
        std::cout << "\nEnter your function selection for weighted values(0 for help): " << std::flush;
        if (!(std::cin >> funcSelection)) {
            std::cin.clear(); //clear bad input flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
            funcSelection = -99;
        }

        switch (funcSelection)
        {

        case -2:
            std::cout << std::flush << std::endl;
            system("CLS");
            std::cout << "\tWEIGHTED VALUES" << std::endl;
            std::cout << "-----------------------------------------------------" << std::endl;
            std::cout << "-2: Clear Screen" << std::endl;
            std::cout << "-1: Quit" << std::endl;
            std::cout << "1: LowerBias" << std::endl;
            std::cout << "2: UpperBias" << std::endl;
            std::cout << "3: CenterBias" << std::endl;
            std::cout << "4: ExtremesBias" << std::endl;
            std::cout << "-----------------------------------------------------" << std::endl;
            break;

        case -1:
            std::cout << std::flush << std::endl;
            system("CLS");
            break;

        case 0:
            std::cout << "\n-----------------------------------------------------" << std::endl;
            std::cout << "-2: Clear Screen" << std::endl;
            std::cout << "-1: Quit" << std::endl;
            std::cout << "1: LowerBias" << std::endl;
            std::cout << "2: UpperBias" << std::endl;
            std::cout << "3: CenterBias" << std::endl;
            std::cout << "4: ExtremesBias" << std::endl;
            std::cout << "-----------------------------------------------------" << std::endl;
            std::cout << std::flush << std::endl;
            break;

        case 1:
            
            std::cout << "\nEnter bias strength: " << std::flush;

            if (!(std::cin >> strengthValue)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            std::cout << "LowerBiasValue(strength: " << strengthValue << "): " << g.LowerBiasValue(strengthValue) << std::endl;
            break;

        case 2:
            
            std::cout << "\nEnter bias strength: " << std::flush;

            if (!(std::cin >> strengthValue)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            std::cout << "UpperBiasValue(strength: " << strengthValue << "): " << g.UpperBiasValue(strengthValue) << std::endl;
            break;

        case 3:
            
            std::cout << "\nEnter bias strength: " << std::flush;

            if (!(std::cin >> strengthValue)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            std::cout << "CenterBiasValue(strength: " << strengthValue << "): " << g.CenterBiasValue(strengthValue) << std::endl;
            break;

        case 4:
            
            std::cout << "\nEnter bias strength: " << std::flush;

            if (!(std::cin >> strengthValue)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            std::cout << "ExtremesBiasValue(strength: " << strengthValue << "): " << g.ExtremesBiasValue(strengthValue) << std::endl;
            break;

        

        default:
            std::cout << "Incorrect entry! " << std::endl;
            break;
        };
    }
}

template<typename T>
void ShowRandomMostTowardsValues(grng<T> g)
{
    int funcSelection = 0;
    int iterations = 0;
    std::cout << std::flush << std::endl;
    system("CLS");
    std::cout << "\tRANDOM TOWARDS VALUES" << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;
    std::cout << "-2: Clear Screen" << std::endl;
    std::cout << "-1: Quit" << std::endl;
    std::cout << "1: Smallest Random" << std::endl;
    std::cout << "2: Largest Random" << std::endl;
    std::cout << "3: Most Centered" << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;

    while (funcSelection != -1)
    {
        std::cout << "\nEnter your function selection for random towards values(0 for help): " << std::flush;
        if (!(std::cin >> funcSelection)) {
            std::cin.clear(); //clear bad input flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
            funcSelection = -99;
        }

        switch (funcSelection)
        {

        case -2:
            std::cout << std::flush << std::endl;
            system("CLS");
            std::cout << "\tRANDOM TOWARDS VALUES" << std::endl;
            std::cout << "-----------------------------------------------------" << std::endl;
            std::cout << "-2: Clear Screen" << std::endl;
            std::cout << "-1: Quit" << std::endl;
            std::cout << "1: Smallest Random" << std::endl;
            std::cout << "2: Largest Random" << std::endl;
            std::cout << "3: Most Centered" << std::endl;
            std::cout << "-----------------------------------------------------" << std::endl;
            break;

        case -1:
            std::cout << std::flush << std::endl;
            system("CLS");
            break;

        case 0:
            std::cout << "\n-----------------------------------------------------" << std::endl;
            std::cout << "-2: Clear Screen" << std::endl;
            std::cout << "-1: Quit" << std::endl;
            std::cout << "1: Smallest Random" << std::endl;
            std::cout << "2: Largest Random" << std::endl;
            std::cout << "3: Most Centered" << std::endl;
            std::cout << "-----------------------------------------------------" << std::endl;
            std::cout << std::flush << std::endl;
            break;

        case 1:
            
            std::cout << "\nEnter iteration count: " << std::flush;
            if (!(std::cin >> iterations)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            std::cout << "SmallestRandom(strength: " << iterations << "): " << g.SmallestRandom(iterations) << std::endl;
            break;

        case 2:
            
            std::cout << "\nEnter iteration count: " << std::flush;
            if (!(std::cin >> iterations)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            std::cout << "LargestRandom(strength: " << iterations << "): " << g.LargestRandom(iterations) << std::endl;
            break;

        case 3:
            std::cout << "\nEnter iteration count: " << std::flush;
            if (!(std::cin >> iterations)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            std::cout << "MostCenteredRandom(strength: " << iterations << "): " << g.MostCenteredRandom(iterations) << std::endl;
            break;

        default:
            std::cout << "Incorrect entry! " << std::endl;
            break;
        };
    }
}

template<typename T>
void ShowNoiseValues(grng<T> g)
{
    int funcSelection = 0;
    int xCount = 0;
    int yCount = 0;
    double top = 0;
    float chancePercentage = 0;
    double freq = 0;
    double displacement = 0;
    bool useDistance = true;
    int tmp = 1;

    std::cout << std::flush << std::endl;
    system("CLS");
    std::cout << "\n2D NOISE VALUES" << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;
    std::cout << "-2: Clear Screen" << std::endl;
    std::cout << "-1: Quit" << std::endl;
    std::cout << "1: Perlin" << std::endl;
    std::cout << "2: Value" << std::endl;
    std::cout << "3: Voronoi" << std::endl;
    std::cout << "if > TOP VALUE: ^, else if greater than 0: @ or ~ else: space" << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;

    while (funcSelection != -1)
    {
        std::cout << "\nEnter your function selection for noise values(0 for help): " << std::flush;
        if (!(std::cin >> funcSelection)) {
            std::cin.clear(); //clear bad input flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
            funcSelection = -99;
        }

        switch (funcSelection)
        {

        case -2:
            std::cout << std::flush << std::endl;
            system("CLS");
            std::cout << "\n2D NOISE VALUES" << std::endl;
            std::cout << "-----------------------------------------------------" << std::endl;
            std::cout << "-2: Clear Screen" << std::endl;
            std::cout << "-1: Quit" << std::endl;
            std::cout << "1: Perlin" << std::endl;
            std::cout << "2: Value" << std::endl;
            std::cout << "3: Voronoi" << std::endl;
            std::cout << "if > TOP VALUE: ^, else if greater than 0: @ or ~ else: space" << std::endl;
            std::cout << "-----------------------------------------------------" << std::endl;
            break;

        case -1:
            std::cout << std::flush << std::endl;
            system("CLS");
            break;

        case 0:
            std::cout << "\n-----------------------------------------------------" << std::endl;
            std::cout << "-2: Clear Screen" << std::endl;
            std::cout << "-1: Quit" << std::endl;
            std::cout << "1: Perlin" << std::endl;
            std::cout << "2: Value" << std::endl;
            std::cout << "3: Voronoi" << std::endl;
            std::cout << "if > value 1: ^, else if greater than 0: @ or ~ else: space" << std::endl;
            std::cout << "-----------------------------------------------------" << std::endl;
            std::cout << std::flush << std::endl;
            break;

        case 1:



            std::cout << "Enter X iterations: " << std::flush;
            if (!(std::cin >> xCount)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }

            std::cout << "Enter Y iterations: " << std::flush;
            if (!(std::cin >> yCount)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }

            std::cout << "Enter Top Value: " << std::flush;
            if (!(std::cin >> top)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            
            std::cout << "Enter Percentage Chance for ~ vs @: " << std::flush;
            if (!(std::cin >> chancePercentage)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }


            std::cout << "\nPerlin Map: " << "\n\n";

            for (int x = 0; x <= xCount+1; x++)
            {
                std::cout << "-";
            }
            std::cout << "\n";

            for (int y = 0; y < yCount; y++)
            {
                std::cout << "|";
                
                for (int x = 0; x < xCount; x++)
                {
                    
                    float currentVal = g.Perlin2D(x, y);

                    if (currentVal > 0)
                    {
                        if (currentVal > top)
                        {
                            std::cout << "^";
                        }
                        else
                        {
                            if (g.ChanceRoll(chancePercentage) == false) std::cout << "@";
                            else std::cout << "~";
                        }
                    }
                    else
                    {
                        std::cout << " ";
                    }
                }

                std::cout << "|" << std::endl;
            }
            for (int x = 0; x <= xCount+1; x++)
            {
                std::cout << "-";
            }
            std::cout << "\n";
            break;

        case 2:
            

            std::cout << "Enter X iterations: " << std::flush;
            if (!(std::cin >> xCount) ){
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }

            std::cout << "Enter Y iterations: " << std::flush;
            if (!(std::cin >> yCount) ){
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }

            std::cout << "Enter Top Value: " << std::flush;
            if (!(std::cin >> top) ){
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }

            std::cout << "Enter Percentage Chance for ~ vs @: " << std::flush;
            if (!(std::cin >> chancePercentage) ){
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }

            std::cout << "\nValue Map: " << "\n\n";


            for (int x = 0; x <= xCount+1; x++)
            {
                std::cout << "-";
            }
            std::cout << "\n";

            for (int y = 0; y < yCount; y++)
            {
                
                std::cout << "|";
                
                for (int x = 0; x < xCount; x++)
                {

                    float currentVal = g.ValueNoise2D(x, y, g.NextInt());

                    if (currentVal > 0)
                    {
                        if (currentVal > top)
                        {
                            std::cout << "^";
                        }
                        else
                        {
                            if (g.ChanceRoll(chancePercentage) == false) std::cout << "@";
                            else std::cout << "~";
                        }
                    }
                    else
                    {
                        std::cout << " ";
                    }
                }

                std::cout << "|" << std::endl;

            }

            for (int x = 0; x <= xCount+1; x++)
            {
                std::cout << "-";
            }
            std::cout << "\n";

            break;

        case 3:
            
            
            
            


            std::cout << "Enter X iterations: " << std::flush;
            if (!(std::cin >> xCount)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }

            std::cout << "Enter Y iterations: " << std::flush;
            if (!(std::cin >> yCount)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }

            std::cout << "Enter Top Value: " << std::flush;
            if (!(std::cin >> top)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }

            std::cout << "Enter Percentage Chance for ~ vs @: " << std::flush;
            if (!(std::cin >> chancePercentage)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }

            std::cout << "Enter frequency: " << std::flush;
            if (!(std::cin >> freq)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }


            std::cout << "Enter Displacement: " << std::flush;
            if (!(std::cin >> displacement)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }

            std::cout << "Use Distance(1 for true, else false)?: " << std::flush;
            if (!(std::cin >> tmp)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            if (tmp == 1) useDistance = 1;


            std::cout << "\nVoronoi Map: " << "\n\n";

            for (int x = 0; x <= xCount+1; x++)
            {
                std::cout << "-";
            }
            std::cout << "\n";

            for (int y = 0; y < yCount; y++)
            {
                std::cout << "|";
                
                for (int x = 0; x < xCount; x++)
                {
                    double currentVal = g.Voronoi2D(x, y, freq, useDistance, displacement);
                    if (currentVal > 0)
                    {
                        if (currentVal > top)
                        {
                            std::cout << "^";
                        }
                        else
                        {
                            if (g.ChanceRoll(chancePercentage) == false) std::cout << "@";
                            else std::cout << "~";
                        }
                    }
                    else
                    {
                        std::cout << " ";
                    }
                }

                std::cout << "|" << std::endl;
            }
            for (int x = 0; x <= xCount+1; x++)
            {
                std::cout << "-";
            }
            std::cout << "\n";
            break;

        default:
            std::cout << "Incorrect entry! " << std::endl;
            break;
        };
    }
}




void ShowAlgorithms()
{
    int funcSelection = 0;
    int seedValue = 0;

    std::cout << std::flush << std::endl;
    system("CLS");
    std::cout << "\tALGORITHMS" << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;
    std::cout << "-2: Clear Screen" << std::endl;
    std::cout << "-1: Quit" << std::endl;
    std::cout << "1: xor8" << std::endl;
    std::cout << "2: xor16" << std::endl;
    std::cout << "3: xor17" << std::endl;
    std::cout << "4: xor23" << std::endl;
    std::cout << "5: xor32" << std::endl;
    std::cout << "6: xor128" << std::endl;
    std::cout << "7: Adapted Lehmer 32" << std::endl;
    std::cout << "8: Lehmer 64" << std::endl;
    std::cout << "9: wyhash" << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;

    while (funcSelection != -1)
    {
        std::cout << "\nEnter your function selection for algorithms(0 for help): " << std::flush;
        if (!(std::cin >> funcSelection)) {
            std::cin.clear(); //clear bad input flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
            funcSelection = -99;
        }

        switch (funcSelection)
        {

        case -2:
            std::cout << std::flush << std::endl;
            system("CLS");
            std::cout << "\tALGORITHMS" << std::endl;
            std::cout << "-----------------------------------------------------" << std::endl;
            std::cout << "-2: Clear Screen" << std::endl;
            std::cout << "-1: Quit" << std::endl;
            std::cout << "1: xor8" << std::endl;
            std::cout << "2: xor16" << std::endl;
            std::cout << "3: xor17" << std::endl;
            std::cout << "4: xor23" << std::endl;
            std::cout << "5: xor32" << std::endl;
            std::cout << "6: xor128" << std::endl;
            std::cout << "7: Adapted Lehmer 32" << std::endl;
            std::cout << "8: Lehmer 64" << std::endl;
            std::cout << "9: wyhash" << std::endl;
            std::cout << "-----------------------------------------------------" << std::endl;
            break;

        case -1:
            std::cout << std::flush << std::endl;
            system("CLS");
            break;

        case 0:
            std::cout << "\n-----------------------------------------------------" << std::endl;
            std::cout << "-2: Clear Screen" << std::endl;
            std::cout << "-1: Quit" << std::endl;
            std::cout << "1: xor8" << std::endl;
            std::cout << "2: xor16" << std::endl;
            std::cout << "3: xor17" << std::endl;
            std::cout << "4: xor23" << std::endl;
            std::cout << "5: xor32" << std::endl;
            std::cout << "6: xor128" << std::endl;
            std::cout << "7: Adapted Lehmer 32" << std::endl;
            std::cout << "8: Lehmer 64" << std::endl;
            std::cout << "9: wyhash" << std::endl;
            std::cout << "-----------------------------------------------------" << std::endl;
            std::cout << std::flush << std::endl;
            break;

        case 1:
            std::cout << "\nEnter Seed: " << std::flush;
            if (!(std::cin >> seedValue)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            std::cout << "xor8(" << seedValue << "): " << xor8(seedValue) << std::endl;
            break;

        case 2:
            
            std::cout << "\nEnter Seed: " << std::flush;
            if (!(std::cin >> seedValue)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            std::cout << "xor16(" << seedValue << "): " << xor16(seedValue) << std::endl;
            break;

        case 3:
            std::cout << "\nEnter Seed: " << std::flush;
            if (!(std::cin >> seedValue)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            std::cout << "xor17(" << seedValue << "): " << xor17(seedValue) << std::endl;
            break;

        case 4:
            std::cout << "\nEnter Seed: " << std::flush;
            if (!(std::cin >> seedValue)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            std::cout << "xor23(" << seedValue << "): " << xor23(seedValue) << std::endl;
            break;

        case 5:
            std::cout << "\nEnter Seed: " << std::flush;
            if (!(std::cin >> seedValue)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            std::cout << "xor32(" << seedValue << "): " << xor32(seedValue) << std::endl;
            break;

        case 6:
            std::cout << "\nEnter Seed: " << std::flush;
            if (!(std::cin >> seedValue)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            std::cout << "xor128(" << seedValue << "): " << xor128(seedValue) << std::endl;
            break;
        
        case 7:
            std::cout << "\nEnter Seed: " << std::flush;
            if (!(std::cin >> seedValue)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            std::cout << "AdaptedLehmer32(" << seedValue << "): " << AdaptedLehmer32(seedValue) << std::endl;
            break;

        case 8:
            std::cout << "\nEnter Seed: " << std::flush;
            if (!(std::cin >> seedValue)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            std::cout << "Lehmer64(" << seedValue << "): " << Lehmer64(seedValue) << std::endl;
            break;

        case 9:
            std::cout << "\nEnter Seed: " << std::flush;
            if (!(std::cin >> seedValue)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            std::cout << "wyhash(" << seedValue << "): " << wyhash(seedValue) << std::endl;
            break;



        default:
            std::cout << "Incorrect entry! " << std::endl;
            break;
        };
    }
}

template<typename T>
void GrngSetup(grng<T>& g)
{
    int funcSelection = 0;
    int seedValue = 0;

    std::cout << std::flush << std::endl;
    system("CLS");
    std::cout << "\tGRNG SETUP" << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;
    std::cout << "-2: Clear Screen" << std::endl;
    std::cout << "-1: Quit" << std::endl;
    std::cout << "1: xor8" << std::endl;
    std::cout << "2: xor16" << std::endl;
    std::cout << "3: xor17" << std::endl;
    std::cout << "4: xor23" << std::endl;
    std::cout << "5: xor32" << std::endl;
    std::cout << "6: xor128" << std::endl;
    std::cout << "7: Adapted Lehmer 32" << std::endl;
    std::cout << "8: Lehmer 64" << std::endl;
    std::cout << "9: wyhash" << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;

    while (funcSelection != -1)
    {
        std::cout << "\nEnter your function selection for grng setup(0 for help): " << std::flush;
        if (!(std::cin >> funcSelection)) {
            std::cin.clear(); //clear bad input flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
            funcSelection = -99;
        }

        switch (funcSelection)
        {

        case -2:
            std::cout << std::flush << std::endl;
            system("CLS");
            std::cout << "\tGRNG SETUP" << std::endl;
            std::cout << "-----------------------------------------------------" << std::endl;
            std::cout << "-2: Clear Screen" << std::endl;
            std::cout << "-1: Quit" << std::endl;
            std::cout << "1: xor8" << std::endl;
            std::cout << "2: xor16" << std::endl;
            std::cout << "3: xor17" << std::endl;
            std::cout << "4: xor23" << std::endl;
            std::cout << "5: xor32" << std::endl;
            std::cout << "6: xor128" << std::endl;
            std::cout << "7: Adapted Lehmer 32" << std::endl;
            std::cout << "8: Lehmer 64" << std::endl;
            std::cout << "9: wyhash" << std::endl;
            std::cout << "-----------------------------------------------------" << std::endl;
            break;

        case -1:
            std::cout << std::flush << std::endl;
            system("CLS");
            break;

        case 0:
            std::cout << "\n-----------------------------------------------------" << std::endl;
            std::cout << "-2: Clear Screen" << std::endl;
            std::cout << "-1: Quit" << std::endl;
            std::cout << "1: xor8" << std::endl;
            std::cout << "2: xor16" << std::endl;
            std::cout << "3: xor17" << std::endl;
            std::cout << "4: xor23" << std::endl;
            std::cout << "5: xor32" << std::endl;
            std::cout << "6: xor128" << std::endl;
            std::cout << "7: Adapted Lehmer 32" << std::endl;
            std::cout << "8: Lehmer 64" << std::endl;
            std::cout << "9: wyhash" << std::endl;
            std::cout << "-----------------------------------------------------" << std::endl;
            std::cout << std::flush << std::endl;
            break;

        case 1:
            std::cout << "\nEnter Seed for xor8: " << std::flush;
            if (!(std::cin >> seedValue)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            g.SetSeed(seedValue);
            g.SetAlgorithm(Random_Algorithm_xor8);
            break;

        case 2:
            std::cout << "\nEnter Seed for xor16: " << std::flush;
            if (!(std::cin >> seedValue)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            g.SetSeed(seedValue);
            g.SetAlgorithm(Random_Algorithm_xor16);
            break;

        case 3:
            std::cout << "\nEnter Seed for xor17: " << std::flush;
            if (!(std::cin >> seedValue)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            g.SetSeed(seedValue);
            g.SetAlgorithm(Random_Algorithm_xor17);
            break;

        case 4:
            std::cout << "\nEnter Seed for xor23: " << std::flush;
            if (!(std::cin >> seedValue)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            g.SetSeed(seedValue);
            g.SetAlgorithm(Random_Algorithm_xor23);
            break;

        case 5:
            std::cout << "\nEnter Seed for xor32: " << std::flush;
            if (!(std::cin >> seedValue)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            g.SetSeed(seedValue);
            g.SetAlgorithm(Random_Algorithm_xor32);
            break;

        case 6:
            std::cout << "\nEnter Seed for xor128: " << std::flush;
            if (!(std::cin >> seedValue)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            g.SetSeed(seedValue);
            g.SetAlgorithm(Random_Algorithm_xor128);
            break;

        case 7:
            std::cout << "\nEnter Seed for AdaptedLehmer32: " << std::flush;
            if (!(std::cin >> seedValue)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            g.SetSeed(seedValue);
            g.SetAlgorithm(Random_Algorithm_AdaptedLehmer32);
            break;

        case 8:
            std::cout << "\nEnter Seed for Lehmer64: " << std::flush;
            if (!(std::cin >> seedValue)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            g.SetSeed(seedValue);
            g.SetAlgorithm(Random_Algorithm_Lehmer64);
            break;

        case 9:
            std::cout << "\nEnter Seed for wyhash: " << std::flush;
            if (!(std::cin >> seedValue)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard
                std::cout << "Incorrect entry! " << std::endl;
                break;
            }
            g.SetSeed(seedValue);
            g.SetAlgorithm(Random_Algorithm_Wyhash);
            break;



        default:
            std::cout << "Incorrect entry! " << std::endl;
            break;
        };
    }
}

