#include <iostream>
#include <fstream>
#include <vector>

// Function to print the content of a vector
void printVector(const std::vector<int>& vec) {
    for (const auto& num : vec) {
        std::cout << num << ' ';
    }
    std::cout << '\n';
}

// Function to ask for the values in the array of user-specified size
void fillVector(std::vector<int>& vec) {
    for (auto& num : vec) {
        std::cout << "Enter a number: ";
        std::cin >> num;
    }
}

// Function to save the content of a vector to a binary file
void saveVectorToBinaryFile(const std::vector<int>& vec, const std::string& fileName) {
    std::ofstream outputFile(fileName, std::ios::binary);
    if (!outputFile) {
        std::cerr << "Unable to open the output file.\n";
        return;
    }
    for (const auto& num : vec) {
        outputFile.write(reinterpret_cast<const char*>(&num), sizeof(num));
    }
    outputFile.close();
}

// Function to load the content of a vector from a binary file
void loadVectorFromBinaryFile(std::vector<int>& vec, const std::string& fileName) {
    std::ifstream inputFile(fileName, std::ios::binary);
    if (!inputFile) {
        std::cerr << "Unable to open the input file.\n";
        return;
    }
    vec.clear();
    int num;
    while (inputFile.read(reinterpret_cast<char*>(&num), sizeof(num))) {
        vec.push_back(num);
    }
    inputFile.close();
}

int main() {
    int size;
    std::cout << "Enter the size of the array: ";
    std::cin >> size;

    std::vector<int> vec(size);
    fillVector(vec);

    std::cout << "Vector content: ";
    printVector(vec);

    std::string fileName = "vectorData.bin";
    saveVectorToBinaryFile(vec, fileName);

    vec.clear();
    loadVectorFromBinaryFile(vec, fileName);

    std::cout << "Vector content after loading from the binary file: ";
    printVector(vec);

    return 0;
}