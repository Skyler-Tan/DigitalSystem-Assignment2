#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;


struct Movie {
    string title;
    string genre;
    int year;
    int duration;
    string synopsis;
};
void clearScreen();
void exitScreen();
int titleScreen();

void searchMovieByName(const vector<Movie>& movies);
void searchByGenre(const vector<Movie>& movies);

string toLowerCase(const string& text) {
    string result = text;
    transform(result.begin(), result.end(), result.begin(), [](unsigned char character) {
        return static_cast<char>(tolower(character));
    });
    return result;
}



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

<<<<<<< HEAD
void searchMovieByName(const vector<Movie>& movies) {

    string searchName;

    cout << "\nEnter movie name: ";
    cin.ignore();
    getline(cin, searchName);
    string normalizedSearchName = toLowerCase(searchName);

    bool found = false;

    for (const Movie& movie : movies) {

        if (toLowerCase(movie.title) == normalizedSearchName) {

            cout << "\nMovie found!\n";
            cout << "Title: " << movie.title << endl;
            cout << "Genre: " << movie.genre << endl;

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nMovie not found.\n";
    }

    cout << "\nPress Enter to continue...";
    cin.get();
}

void searchByGenre(const vector<Movie>& movies) {

    string searchGenre;

    cout << "\nEnter genre: ";
    cin.ignore();
    getline(cin, searchGenre);
    string normalizedSearchGenre = toLowerCase(searchGenre);

    bool found = false;

    cout << "\nMovies in genre: " << searchGenre << "\n";
    cout << "--------------------------------\n";

    for (const Movie& movie : movies) {

        if (toLowerCase(movie.genre) == normalizedSearchGenre) {

            cout << movie.title << endl;

            found = true;
        }
    }

    if (!found) {
        cout << "No movies found for this genre.\n";
    }

    cout << "\nPress Enter to continue...";
    cin.get();
}
=======

>>>>>>> origin/main

int main() {
    
    int choice;

    vector<Movie> movies = loadMovies("movies.txt");

    do {
        clearScreen();
        choice = titleScreen();

        //search movie name
        if (choice == 1) {
            searchMovieByName(movies);
        } else if (choice == 2) {
            searchByGenre(movies);
        } else if (choice == 3) {
            exitScreen();
        } else {
            cout << "Invalid choice. Please try again.\n";
            cin.ignore();
            cin.get();
        }
    } while (choice != 3);
    }

// \033[2J clears the screen, \033[H moves the cursor to the top-left (1,1)
void clearScreen(){
    cout << "\033[2J\033[H";
}

int titleScreen(){
    clearScreen();
    cout << "\n\t<================     Welcome to the Netflix Movie Selector!     ================>\n";
    cout << "\n\t\tPlease select a searching option:\n";
    cout << "\n\t\t\t1. \tSearch movie name\n";
    cout << "\t\t\t2. \tSearch by genre\n";
    cout << "\t\t\t3. \tExit\n";
    cout << "\n\tEnter your choice: ";
    int choice;
    cin >> choice;
    return choice;
}
void exitScreen(){
    clearScreen();
    cout << "\n\t<================     Thank you for using the Netflix Movie Selector!     ================>\n";
    cout << "\n\t\t\t\tGoodbye!\n\n\n";
}
