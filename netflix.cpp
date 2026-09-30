#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void clearScreen();
void exitScreen();
int titleScreen(int choice);

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

    do {
        clearScreen();
        choice =titleScreen(choice);

        //search movie name
        if (choice == 1) {
            cout << "\n\nchoose 1 successful.\n";
            cin.get();
            cout << "Press enter to continue...";
            cin.ignore(); // Clear the input buffer
            

        //search by genre
        } else if (choice == 2) {
            cout << "\n\nchoose 2 successful.\n"; 
            cin.get();
            cout << "Press enter to continue...";
            cin.ignore(); 
            
        //exit
        } else if (choice == 3) {
            exitScreen();

        //error handling for invalid input
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }while (choice != 3);
    return 0;
}

// \033[2J clears the screen, \033[H moves the cursor to the top-left (1,1)
void clearScreen() {
    cout << "\033[2J\033[H";
}

int titleScreen(int choice) {
    clearScreen();
    cout << "\n\t<================     Welcome to the Netflix Movie Selector!     ================>\n";
    cout << "\n\t\tPlease select a searching option:\n";
    cout << "\n\t\t\t1. \tSearch movie name\n";
    cout << "\t\t\t2. \tSearch by genre\n";
    cout << "\t\t\t3. \tExit\n";
    cout << "\n\tEnter your choice: ";
    cin >> choice;
    return choice;
}
void exitScreen() {
    clearScreen();
    cout << "\n\t<================     Thank you for using the Netflix Movie Selector!     ================>\n";
    cout << "\n\t\t\t\tGoodbye!\n\n\n";
}