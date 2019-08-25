#include <string>
#include <random>
#include <iostream>

class RandomGenerator
{
public:
    // constructor
    RandomGenerator();

    // generate a number in the specified range [minValue, maxValue]
    inline int RandomInt(int minValue=std::numeric_limits<int>::min(), int maxValue=std::numeric_limits<int>::max());
    inline double RandomDouble(double minValue=std::numeric_limits<double>::min(), double maxValue=std::numeric_limits<double>::max());

    // generate a random string of the specified length
    std::string RandomString(size_t length);

private:
    // engine for random generation
    std::default_random_engine generator;

    // distribution to apply to the generator
    std::uniform_real_distribution<> uniDbl;
};

RandomGenerator::RandomGenerator()
{
    // seed the generator from the system random device
    std::random_device rd;
    generator.seed(rd());
};

int RandomGenerator::RandomInt(int minValue, int maxValue)
{
    // generate a [0, 1] double and scale to range, casting to numeric type
    double randomValue = uniDbl(generator);
    double range = (maxValue - minValue + 1); // +1 to give maxValue equal chance of getting selected
    return static_cast<int>((randomValue * range) + minValue);
};

double RandomGenerator::RandomDouble(double minValue, double maxValue)
{
    // generate a [0, 1] double and scale to range, casting to numeric type
    double randomValue = uniDbl(generator);
    double range = (maxValue - minValue);
    return static_cast<double>((randomValue * range) + minValue);
};

std::string RandomGenerator::RandomString(size_t length)
{
    // allocate a string of the given length
    std::string str(length, 0);
    //printf("Length: %zd\n", length);

    static const char charset[] = "abcdefghijklmnopqrstuvwxyz";
    const int max_index = sizeof(charset) - 1;

    std::cout << max_index << std::endl;

    for (auto& ch : str)  // requires C++11, compile with `$ g++ -std=c++11`
    // equivalent to this in C++98 using an iterator:
    //for (std::string::iterator it = str.begin(); it != str.end(); ++it)
    {
        // choose a random character from charset
        const size_t index = RandomInt(0, max_index);
        printf("Index: %zd\n", index);
        ch = charset[index];
    }

    return str;
};

int main(int argc, const char * argv[])
{
    printf("Testing RandomGenerator::RandomString(size_t length):\n");
    RandomGenerator randomGenerator;

    // generate random strings of various lengths
    for (size_t length = 10; length <= 20; ++length)
    {
        std::string str = randomGenerator.RandomString(length);
        std::cout << "Pre c_str(): " << str << "\n";
        printf("Generated string: %s\n", str.c_str());
    }

    return 0;
};
