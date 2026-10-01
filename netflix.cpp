#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Movie {
    string title;
    string genre;
    int year;
    int duration;
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

        size_t p1 = line.find('|');
        size_t p2 = (p1 == string::npos) ? string::npos : line.find('|', p1 + 1);
        size_t p3 = (p2 == string::npos) ? string::npos : line.find('|', p2 + 1);
        size_t p4 = (p3 == string::npos) ? string::npos : line.find('|', p3 + 1);

        if (p4 == string::npos) continue; 
 
        try {

            Movie m;
            m.title    = line.substr(0, p1);
            m.genre    = line.substr(p1 + 1, p2 - p1 - 1);
            m.year     = stoi(line.substr(p2 + 1, p3 - p2 - 1));
            m.duration = stoi(line.substr(p3 + 1, p4 - p3 - 1));
            m.synopsis = line.substr(p4 + 1);
            movies.push_back(m);

        } catch (...) {

            continue;  

        }
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