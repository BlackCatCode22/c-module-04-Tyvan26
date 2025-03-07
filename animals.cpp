#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// Define Animal class and its subclasses (Hyena, Lion, Tiger, Bear)
class Animal {
public:
    string name;
    int age;
    string species;

    Animal(const string& name, int age, const string& species)
        : name(name), age(age), species(species) {}

    virtual void displayInfo() const {
        cout << "Name: " << name << ", Age: " << age << ", Species: " << species << endl;
    }

    virtual ~Animal() {}
};

class Hyena : public Animal {
public:
    Hyena(const string& name, int age) : Animal(name, age, "Hyena") {}
    void displayInfo() const override {
        cout << "Hyena - Name: " << name << ", Age: " << age << endl;
    }
};

class Lion : public Animal {
public:
    Lion(const string& name, int age) : Animal(name, age, "Lion") {}
    void displayInfo() const override {
        cout << "Lion - Name: " << name << ", Age: " << age << endl;
    }
};

class Tiger : public Animal {
public:
    Tiger(const string& name, int age) : Animal(name, age, "Tiger") {}
    void displayInfo() const override {
        cout << "Tiger - Name: " << name << ", Age: " << age << endl;
    }
};

class Bear : public Animal {
public:
    Bear(const string& name, int age) : Animal(name, age, "Bear") {}
    void displayInfo() const override {
        cout << "Bear - Name: " << name << ", Age: " << age << endl;
    }
};

// Function to split a string by spaces
vector<string> splitBySpace(const string& str) {
    vector<string> result;
    stringstream ss(str);
    string word;
    while (ss >> word) {
        result.push_back(word);
    }
    return result;
}

int main() {
    string myText = "";
    vector<Animal*> animals;  // Vector to store all animals
    map<string, int> speciesCount;  // Map to count species

    // Open the input file
    ifstream MyFile("arrivingAnimals.txt");
    if (!MyFile) {
        cerr << "Error: Could not open the input file!" << endl;
        return 1;  // Exit if the input file can't be opened
    }
    cout << "Input file opened successfully." << endl;

    // Open the output file
    ofstream outputFile("newAnimals.txt");
    if (!outputFile) {
        cerr << "Error: Could not open the output file!" << endl;
        return 1;  // Exit if the output file can't be opened
    }
    cout << "Output file opened successfully." << endl;

    // Read the input file line by line
    while (getline(MyFile, myText)) {
        cout << "Processing line: " << myText << endl;

        vector<string> parts;
        stringstream ss(myText);
        string item;
        while (getline(ss, item, ',')) {
            item.erase(0, item.find_first_not_of(" \t"));
            item.erase(item.find_last_not_of(" \t") + 1);
            parts.push_back(item);
        }

        if (parts.size() >= 3) {
            string name = parts[0];
            int age = stoi(parts[1]);
            string species = parts[2];

            Animal* animal = nullptr;
            if (species == "Hyena") {
                animal = new Hyena(name, age);
            } else if (species == "Lion") {
                animal = new Lion(name, age);
            } else if (species == "Tiger") {
                animal = new Tiger(name, age);
            } else if (species == "Bear") {
                animal = new Bear(name, age);
            }

            if (animal != nullptr) {
                animals.push_back(animal);
                speciesCount[species]++;
            }
        }
    }

    // Writing data to the output file
    outputFile << "\n--- Animal Details ---\n";
    for (const auto& animal : animals) {
        outputFile << "Name: " << animal->name << ", Age: " << animal->age << ", Species: " << animal->species << endl;
    }

    outputFile << "\n--- Species Count ---\n";
    for (const auto& species : speciesCount) {
        outputFile << species.first << ": " << species.second << endl;
    }

    // Clean up dynamic memory
    for (auto animal : animals) {
        delete animal;
    }

    // Close files
    MyFile.close();
    outputFile.close();

    cout << "Program completed successfully." << endl;
    return 0;
}
