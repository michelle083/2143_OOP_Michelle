# P04 - RPSLS Program
## Michelle Orru
### Description: create a rock, paper, scissors, lizard, spock game




### Files

|   #   |    File    | Description                      |
| :---: |  --------  | -------------------------------- |
|   1   | [banner.txt](https://github.com/michelle083/2143_OOP_Michelle/blob/main/Assignments/P04/banner.txt) |                                  |
|   2   | [main.cpp](https://github.com/michelle083/2143_OOP_Michelle/blob/main/Assignments/P04/main.cpp)  | Main driver of my list program   |
|   3   | [emojis.h](https://github.com/michelle083/2143_OOP_Michelle/blob/main/Assignments/P04/emojis.h) | Header file with emojis|


### Instructions

- This program does not require any non standard libraries

### Example Command
```cpp
#define ROCK2 u8"\U0001F5FB"
#define PAPER2 u8"\U0001F4C3"
#define SCISSORS2 u8"\U0001F52A"
#define LIZARD2 u8"\U0001F438"
#define SPOCK2 u8"\U0001F596"

struct Hands {
    const string rock = ROCK2;
    const string paper = PAPER2;
    const string scissors = SCISSORS2;
    const string lizard = LIZARD2;
    const string spock = SPOCK2;

    static map< string, string > Emojis;  // stl map
    //         name  , emoji

    static map< string, string > Names;  // stl map
    //         emoji  , name

    static string RandHand() {
        auto it = Emojis.begin();  // iterator to front of map

        std::advance(it, rand() % Emojis.size());  // advance some random amnt
                                                   //   of steps

        string random_hand = it->second;  // grab emoji from map

        return random_hand;  // return rand emoji
    }

    static string Rock() {
        return Emojis["rock"];
    }
    static string Paper() {
        return Emojis["paper"];
    }
    static string Scissors() {
        return Emojis["scissors"];
    }
    static string Lizard() {
        return Emojis["lizard"];
    }
    static string Spock() {
        return Emojis["spock"];
    }
};
```





