#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Movie {
    string title;
    string genre;
};

vector<Movie> loadMovies(const string& filename) {

    vector<Movie> movies;

    ifstream in(filename);

    if (!in) {

        cerr << "Could not open " << filename << "\n";
        return movies;

    }

    string line;
    while (getline(in, line) && movies.size() < 100) {

        size_t sep = line.find('|');
        if (sep == string::npos) continue;
        movies.push_back({line.substr(0, sep), line.substr(sep + 1)});

    }
    
    return movies;
}

int main() {
    
    int choice;

    vector<Movie> movies = loadMovies("movies.txt");

    cout << "Welcome to the Netflix Movie Selector!\n";
    cout << "Please select a searching option:\n";
    cout << "1. Search movie name\n";
    cout << "2. Search by genre\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    
    if (choice == 1) {
        


    } else if (choice == 2) {
        


    } else if (choice == 3) {

        cout << "Exiting the program. Goodbye!\n";

    } else {

        cout << "Invalid choice. Please try again.\n";

    }

    return 0;
}