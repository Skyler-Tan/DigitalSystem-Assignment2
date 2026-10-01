#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Movie {
    string title;
    string genre;
    string synopsis;
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

        size_t sep1 = line.find('|');
        if (sep1 == string::npos) continue;
        size_t sep2 = line.find('|', sep1 + 1);
        if (sep2 == string::npos) continue;  

        movies.push_back({
            line.substr(0, sep1),
            line.substr(sep1 + 1, sep2 - sep1 - 1),
            line.substr(sep2 + 1)

        });
    }

    return movies;
}



int main() {
    
    int choice;

    vector<Movie> movies = loadMovies("movies.txt");

    cout << "\nWelcome to the Netflix Movie Selector!\n";
    cout << "\nPlease select a searching option:\n";
    cout << "1. Search movie name\n";
    cout << "2. Search by genre\n";
    cout << "3. Exit\n";
    cout << "\nEnter your choice: ";
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