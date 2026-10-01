#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <limits>
#include <iomanip>
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

void displayMovie(const Movie& movie) {
    cout << "Title: " << movie.title << endl;
    cout << "Genre: " << movie.genre << endl;
    cout << "Year: " << movie.year << endl;
    cout << "Duration: " << movie.duration << " minutes" << endl;
    cout << "Synopsis: " << movie.synopsis << endl;
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

void searchMovieByName(const vector<Movie>& movies) {

    string searchName;

    const int perPage = 20;
    int totalMovies = static_cast<int>(movies.size());
    int totalPages = (totalMovies + perPage - 1) / perPage;
    if (totalPages < 1) totalPages = 1;
    int page = 0;
    bool done = false;

    cin.ignore();

    while (!done) {

        clearScreen();

        int start = page * perPage;
        int end = min(start + perPage, totalMovies);

        cout << "\n  ALL MOVIES  -  Page " << (page + 1) << " of " << totalPages
             << "   (showing " << (totalMovies == 0 ? 0 : start + 1) << "-" << end
             << " of " << totalMovies << ")\n";
        cout << "  " << string(84, '=') << "\n";
        cout << "  " << right << setw(4) << "No."
             << "  " << left << setw(40) << "Title"
             << setw(18) << "Genre"
             << setw(6) << "Year"
             << setw(10) << "Duration" << "\n";
        cout << "  " << string(84, '-') << "\n";

        for (int i = start; i < end; i++) {
            string shownTitle = movies[i].title;
            if (shownTitle.size() > 38) shownTitle = shownTitle.substr(0, 35) + "...";
            string shownGenre = movies[i].genre;
            if (shownGenre.size() > 16) shownGenre = shownGenre.substr(0, 13) + "...";

            cout << "  " << right << setw(4) << (i + 1)
                 << "  " << left << setw(40) << shownTitle
                 << setw(18) << shownGenre
                 << setw(6) << movies[i].year
                 << setw(10) << (to_string(movies[i].duration) + " min") << "\n";
        }

        cout << "  " << string(84, '=') << "\n";
        cout << "  [N] Next page    [P] Previous page    [0] Back to menu\n";
        cout << "\n  Or type a movie name to view its details: ";
        getline(cin, searchName);
        string normalizedSearchName = toLowerCase(searchName);

        if (searchName == "0") {
            done = true;
        } else if (normalizedSearchName == "n") {
            if (page < totalPages - 1) page++;
        } else if (normalizedSearchName == "p") {
            if (page > 0) page--;
        } else {

            bool found = false;

            for (const Movie& movie : movies) {

                if (toLowerCase(movie.title) == normalizedSearchName) {

                    cout << "\nMovie found!\n";
                    displayMovie(movie);

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
    }
}

void searchByGenre(const vector<Movie>& movies) {

    string searchGenre;

    // collect each genre once (case-insensitive), sorted A-Z
    vector<string> genres;
    for (const Movie& movie : movies) {
        bool exists = false;
        for (const string& g : genres) {
            if (toLowerCase(g) == toLowerCase(movie.genre)) {
                exists = true;
                break;
            }
        }
        if (!exists) genres.push_back(movie.genre);
    }
    sort(genres.begin(), genres.end(), [](const string& a, const string& b) {
        return toLowerCase(a) < toLowerCase(b);
    });

    // work out an even column width so every genre lines up
    size_t longest = 0;
    for (const string& g : genres) {
        if (g.size() > longest) longest = g.size();
    }
    int colWidth = static_cast<int>(to_string(genres.size()).size() + 2 + longest) + 4;
    int perRow = 100 / colWidth;
    if (perRow > 4) perRow = 4;
    if (perRow < 1) perRow = 1;

    cin.ignore();

    bool backToMenu = false;

    while (!backToMenu) {

        clearScreen();

        cout << "\n  SELECT A GENRE\n";
        cout << "  " << string(colWidth * perRow, '=') << "\n\n";

        for (size_t i = 0; i < genres.size(); i++) {
            if (i % perRow == 0) cout << "  ";
            string label = to_string(i + 1) + ". " + genres[i];
            cout << left << setw(colWidth) << label;
            if ((i + 1) % perRow == 0 || i + 1 == genres.size()) cout << "\n";
        }

        cout << "\n  " << string(colWidth * perRow, '=') << "\n";
        cout << "  Enter genre number or name (0 to go back): ";
        getline(cin, searchGenre);
        string normalizedSearchGenre = toLowerCase(searchGenre);

        if (searchGenre == "0") {
            backToMenu = true;
            continue;
        }

        // find which genre was chosen (by number or by name)
        int selected = -1;
        bool isNumber = !searchGenre.empty() && searchGenre.size() < 6;
        for (char c : searchGenre) {
            if (!isdigit(static_cast<unsigned char>(c))) isNumber = false;
        }

        if (isNumber) {
            int n = stoi(searchGenre);
            if (n >= 1 && n <= static_cast<int>(genres.size())) selected = n - 1;
        } else {
            for (size_t i = 0; i < genres.size(); i++) {
                if (toLowerCase(genres[i]) == normalizedSearchGenre) {
                    selected = static_cast<int>(i);
                    break;
                }
            }
        }

        if (selected == -1) {
            cout << "\n  Genre not found. Press Enter to continue...";
            cin.get();
            continue;
        }

        // gather every movie in the chosen genre
        string chosenGenre = genres[selected];
        vector<int> matches;
        for (size_t i = 0; i < movies.size(); i++) {
            if (toLowerCase(movies[i].genre) == toLowerCase(chosenGenre)) {
                matches.push_back(static_cast<int>(i));
            }
        }

        bool backToGenres = false;

        while (!backToGenres) {

            clearScreen();

            cout << "\n  MOVIES IN GENRE: " << chosenGenre << "  (" << matches.size() << " found)\n";
            cout << "  " << string(72, '=') << "\n";
            cout << "  " << right << setw(4) << "No."
                 << "  " << left << setw(46) << "Title"
                 << setw(6) << "Year"
                 << setw(10) << "Duration" << "\n";
            cout << "  " << string(72, '-') << "\n";

            for (size_t i = 0; i < matches.size(); i++) {
                const Movie& movie = movies[matches[i]];
                string shownTitle = movie.title;
                if (shownTitle.size() > 44) shownTitle = shownTitle.substr(0, 41) + "...";

                cout << "  " << right << setw(4) << (i + 1)
                     << "  " << left << setw(46) << shownTitle
                     << setw(6) << movie.year
                     << setw(10) << (to_string(movie.duration) + " min") << "\n";
            }

            cout << "  " << string(72, '=') << "\n";
            cout << "  Enter movie number to view details (0 to go back): ";
            getline(cin, searchGenre);

            if (searchGenre == "0") {
                backToGenres = true;
                continue;
            }

            bool validNumber = !searchGenre.empty() && searchGenre.size() < 6;
            for (char c : searchGenre) {
                if (!isdigit(static_cast<unsigned char>(c))) validNumber = false;
            }

            int n = validNumber ? stoi(searchGenre) : -1;

            if (n >= 1 && n <= static_cast<int>(matches.size())) {
                clearScreen();
                cout << "\n  MOVIE DETAILS\n";
                cout << "  " << string(72, '=') << "\n\n";
                displayMovie(movies[matches[n - 1]]);
                cout << "\n  " << string(72, '=') << "\n";
                cout << "\nPress Enter to continue...";
                cin.get();
            } else {
                cout << "\n  Invalid choice. Press Enter to continue...";
                cin.get();
            }
        }
    }
}

int main() {
    
    int choice;

    vector<Movie> movies = loadMovies("movies.txt");

    do {
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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Press Enter to continue...";
            cin.get();
        }
    } while (choice != 3);
    return 0;
}

void clearScreen(){
    cout << "\033[2J\033[H";   
}

int titleScreen(){
    clearScreen();

    const int innerWidth = 60;
    const string red   = "\033[1;31m";
    const string white = "\033[1;37m";
    const string grey  = "\033[0;90m";
    const string reset = "\033[0m";

    const string lines[] = {
        "",
        R"( _   _  _____  _____  _____  _      ___ __  __)",
        R"(| \ | || ____||_   _||  ___|| |    |_ _|\ \/ /)",
        R"(|  \| ||  _|    | |  | |_   | |     | |  \  / )",
        R"(| |\  || |___   | |  |  _|  | |___  | |  /  \ )",
        R"(|_| \_||_____|  |_|  |_|    |_____||___|/_/\_\)",
        "",
        "M O V I E   S E L E C T O R",
        "",
        "Welcome! Please select a searching option:",
        "",
        "[1]  Search movie name",
        "[2]  Search by genre",
        "[3]  Exit",
        ""
    };
    const int totalLines = sizeof(lines) / sizeof(lines[0]);

    cout << "\n\n";
    cout << "\t" << red << "+" << string(innerWidth, '=') << "+" << reset << "\n";

    for (int i = 0; i < totalLines; i++) {
        const string& text = lines[i];

        // lines 11-13 are the menu options: same left margin so they line up
        bool isMenu = (i >= 11 && i <= 13);
        int padLeft  = isMenu ? 19 : (innerWidth - static_cast<int>(text.size())) / 2;
        int padRight = innerWidth - static_cast<int>(text.size()) - padLeft;

        cout << "\t" << red << "|" << reset << string(padLeft, ' ');

        if (isMenu) {
            cout << red << text.substr(0, 3) << white << text.substr(3);   // red [1], white label
        } else if (i >= 1 && i <= 5) {
            cout << red << text;                                            // NETFLIX banner
        } else if (i == 7) {
            cout << white << text;                                          // subtitle
        } else {
            cout << grey << text;
        }

        cout << reset << string(padRight, ' ') << red << "|" << reset << "\n";

        // thin divider under the subtitle
        if (i == 7) {
            cout << "\t" << red << "|" << grey << string(innerWidth, '-') << red << "|" << reset << "\n";
        }
    }

    cout << "\t" << red << "+" << string(innerWidth, '=') << "+" << reset << "\n";
    cout << "\n\t" << white << "Enter your choice: " << reset;

    int choice;
    if (!(cin >> choice)) {
        if (cin.eof()) {
            return 3;
        }
        cin.clear();
        return 0;
    }
    return choice;
}
void exitScreen(){
    clearScreen();

    const int innerWidth = 60;
    const string red   = "\033[1;31m";
    const string white = "\033[1;37m";
    const string grey  = "\033[0;90m";
    const string reset = "\033[0m";

    const string lines[] = {
        "",
        "N E T F L I X   M O V I E   S E L E C T O R",
        "",
        "Thank you for using the Netflix Movie Selector!",
        "We hope you found something great to watch.",
        "",
        "*  *  *   Grab some popcorn & enjoy the show!   *  *  *",
        "",
        "G O O D B Y E !",
        ""
    };

    cout << "\n\n";
    cout << "\t" << red << "+" << string(innerWidth, '=') << "+" << reset << "\n";

    for (const string& text : lines) {
        int left  = (innerWidth - static_cast<int>(text.size())) / 2;
        int right = innerWidth - static_cast<int>(text.size()) - left;
        string color = (text == lines[1] || text == lines[8]) ? red : white;

        cout << "\t" << red << "|" << reset
             << string(left, ' ') << color << text << reset << string(right, ' ')
             << red << "|" << reset << "\n";

        // thin divider under the title line
        if (text == lines[1]) {
            cout << "\t" << red << "|" << grey << string(innerWidth, '-') << red << "|" << reset << "\n";
        }
    }

    cout << "\t" << red << "+" << string(innerWidth, '=') << "+" << reset << "\n";
    cout << "\n\n";
}
