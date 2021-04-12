// Lists - Play songs from a playlist

#include <iostream>
#include <list>
#include <string>
#include <cctype>
#include <iomanip>
#include <limits>

class Song {
    friend std::ostream &operator<<(std::ostream &os, const Song &s);

    std::string name;
    std::string artist;
    int rating;
public:
    // Constructors
    Song() = default;
    Song(std::string name, std::string artist, int rating)
            : name{name}, artist{artist}, rating{rating} {}

    // Getters
    std::string get_name() const {
        return name;
    }

    std::string get_artist() const {
        return artist;
    }
    
    int get_rating() const {
        return rating;
    }
    
    bool operator<(const Song &rhs) const  {
        return this->name < rhs.name;
    }
    
    bool operator==(const Song &rhs) const  {
        return this->name == rhs.name;
    }
};

std::ostream &operator<<(std::ostream &os, const Song &s) {
    os << std::setw(20) << std::left << s.name
       << std::setw(30) << std::left << s.artist
       << std::setw(2) << std::left << s.rating;
       return os;
}

void display_menu() {
    std::cout << "\nF - Play First Song" << std::endl;
    std::cout << "N - Play Next song" << std::endl;
    std::cout << "P - Play Previous song" << std::endl;
    std::cout << "A - Add and play a new Song at current location" << std::endl;
    std::cout << "L - List the current playlist" << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "Enter a selection (Q to quit): ";
}

void play_current_song(const Song &song) {
    std::cout << "Playing: " << std::endl;
    std::cout << song << std::endl;
}

void display_playlist(const std::list<Song> &playlist, const Song &current_song) {
    for (const Song &song: playlist) {
        std::cout << song << std::endl;
    }
    std::cout << "Current song: " << std::endl;
    std::cout << current_song << std::endl;
}

int main() {

    // list of songs
    std::list<Song> myPlaylist {
        { "I Miss You", "Blink 182", 5 },
        { "Hakuna Matata", "Lion King", 5 },
        { "Mizz Bizz", "Paramore", 4 },
        { "Dookie", "Green Day", 5 },
        { "The Downfall of Us All", "A Day To Remember", 4 },
        { "Empty Space", "The Story So Far", 3 } };

    // assign iterator to the beginning of the list
    std::list<Song>::iterator currentSong = myPlaylist.begin();
    // displays current song of playlist
    display_playlist(myPlaylist, *currentSong);
    
    char selection{};
    do {
        // display menu options for the user & grab selection from user
        display_menu();
        std::cin >> selection;
        selection = std::toupper(selection);
        // check user's option
        if (selection == 'F') {
            std::cout << "Playing first song" << std::endl;
            currentSong = myPlaylist.begin();
            play_current_song(*currentSong);
        }
        else if (selection == 'N') {
            std::cout << "Playing next song" << std::endl;
            currentSong++;
            if (currentSong == myPlaylist.end()) {
                std::cout << "Wrapping to start of playlist" << std::endl;
                currentSong = myPlaylist.begin();
            }
            play_current_song(*currentSong);
        }
        else if (selection == 'P') {
            std::cout << "Playing previous song" << std::endl;
            if (currentSong == myPlaylist.begin()) {
                std::cout << "Wrapping to end of playlist" << std::endl;
                currentSong = myPlaylist.end();
            }
            currentSong--;
            play_current_song(*currentSong);
        } else if (selection == 'A') {
            std::string name, artist;
            int rating;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "Adding and playing new song" << std::endl;
            std::cout << "Enter song name:";
            getline(std::cin, name);
            std::cout << "Enter song artist: ";
            getline(std::cin, artist);
            std::cout << "Enter your rating (1-5): ";
            std::cin >> rating;
            myPlaylist.insert(currentSong, Song{name, artist, rating});
            currentSong--;
            play_current_song(*currentSong);
        } else if (selection == 'L') {
            std::cout << std::endl;
            display_playlist(myPlaylist, *currentSong);            
        } else if (selection == 'Q')
            std::cout << "Quitting" << std::endl;
        else
            std::cout << "Illegal choice, try again...";
        // check user's option until Q for quit
    } while (selection != 'Q');

    std::cout << "Thanks for listening!" << std::endl;
    return 0;
}