#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <string>

// Function to generate all combinations of input values
void generateCombinations(std::vector<std::vector<int>> &options, std::vector<int> &current, const std::vector<std::vector<int>> &input_values, int depth)
{
    if (depth == input_values.size())
    {
        options.push_back(current);
        return;
    }

    for (int value : input_values[depth])
    {
        current.push_back(value);
        generateCombinations(options, current, input_values, depth + 1);
        current.pop_back();
    }
}

// Function to perform manual binary search on a list of integer vectors
std::vector<int> binarySearchAlgorithm(const std::vector<std::vector<int>> &options, const std::vector<int> &target, int &searchCount, bool isManual = false)
{
    // Manually perform what the binary_search method does
    int left = 0;
    int right = options.size() - 1;

    while (left <= right)
    {
        searchCount++;
        int mid = left + (right - left) / 2;

        if (options[mid] == target)
        {
            return options[mid];
        }
        else if (options[mid] < target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return {};
}

// Function to generate input values randomly
std::vector<std::vector<int>> generateRandomInputValues(int numSets)
{
    std::vector<std::vector<int>> input_values;

    for (int i = 0; i < numSets; i++)
    {
        std::vector<int> values;
        // Add exactly 2 values to each set
        values.push_back(std::rand());
        values.push_back(std::rand());

        input_values.push_back(values);
    }

    return input_values;
}

// Function to generate random target values from the input values
std::vector<int> generateRandomValues(const std::vector<std::vector<int>> &input_values, int numSets)
{
    std::vector<int> target;
    srand(static_cast<unsigned>(time(nullptr))); // Initialize the random number generator seed

    for (int i = 0; i < numSets; i++)
    {
        int randomIndex = rand() % input_values[i].size();
        target.push_back(input_values[i][randomIndex]);
    }

    return target;
}

void searchBinary(const std::vector<std::vector<int>> &input_values, const std::vector<int> &target)
{
    std::cout << "-------------Binary Search-------------" << std::endl;

    std::cout << "Randomly generated password: ";
    for (int value : target)
    {
        std::cout << value << "";
    }
    std::cout << std::endl;

    std::vector<std::vector<int>> options;
    std::vector<int> current;

    generateCombinations(options, current, input_values, 0);

    // Sort the generated combinations for binary search
    std::sort(options.begin(), options.end());

    int searchCount = 0;

    // Perform binary search
    std::vector<int> foundPassword = binarySearchAlgorithm(options, target, searchCount);

    if (!foundPassword.empty())
    {
        std::cout << "Password found using binary search: ";
        for (int value : foundPassword)
        {
            std::cout << value << "";
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "The password was NOT found." << std::endl;
    }

    std::cout << "Number of binary searches performed: " << searchCount << std::endl;
}

std::vector<int> linearSearch(const std::vector<std::vector<int>> &options, const std::vector<int> &target, int &searchCount)
{
    for (const std::vector<int> &option : options)
    {
        searchCount++;
        if (option == target)
        {
            return option; // Return the found password
        }
    }

    return {}; // Return an empty vector if the password is not found
}

void searchLinear(const std::vector<std::vector<int>> &input_values, const std::vector<int> &target)
{
    std::cout << "-------------Linear Search-------------" << std::endl;

    std::cout << "Randomly generated password: ";
    for (int value : target)
    {
        std::cout << value << "";
    }
    std::cout << std::endl;

    std::vector<std::vector<int>> options;
    std::vector<int> current;

    generateCombinations(options, current, input_values, 0);

    int searchCount = 0;

    // Perform linear search
    std::vector<int> foundPassword = linearSearch(options, target, searchCount);

    if (!foundPassword.empty())
    {
        std::cout << "Password found using linear search: ";
        for (int value : foundPassword)
        {
            std::cout << value << "";
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "The password was NOT found." << std::endl;
    }

    std::cout << "Number of linear searches performed: " << searchCount << std::endl;
}

int main()
{
    // Generate input_values randomly
    int numSets = std::rand() % 5 + 1; // Random number of sets (1 to 5 sets)

    std::vector<std::vector<int>> input_values = generateRandomInputValues(numSets);

    // Random variable to be compared
    std::vector<int> target = generateRandomValues(input_values, numSets);

    // Binary search is more efficient in large data sets
    // Can have processing cost of information
    searchBinary(input_values, target);

    // Linear search is more efficient in small data sets
    searchLinear(input_values, target);

    return 0;
}
