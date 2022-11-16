# P05 - BolNiverse Fight Club Program
## Michelle Orru
### Description:

Write a program that creates the appropriate number of characters based on the input file, and proceeds to manage battles between attackers and defenders choosing the appropriate character to fight based on the above rules. You will use run time polymorphism to switch between attacking characters and defending characters. This means you should only have two pointers to manage battles. Attackers, defenders, and expired will be in separate queues based on status. When the attacking or defending queues become empty, the battle is over and the side with characters remaining wins.


### Files

|   #   |    File    | Description                      |
| :---: |  --------  | -------------------------------- |
|   1   | [banner.txt](https://github.com/michelle083/2143_OOP_Michelle/blob/main/Assignments/P05/banner.txt) |                                  |
|   2   | [main.cpp](https://github.com/michelle083/2143_OOP_Michelle/blob/main/Assignments/P05/main.cpp)  | Main driver of my list program   |


### Instructions

There are a few other odd rules that I will list here:

Attacking force can be any size from a few to thousands.
Defending force can have 1 of each character type for every 100 attackers.
Attacking force can heal only during battle.
Defending force can heal at any time.
Any character that reaches zero hit points expires and is removed from the game.
Defending force can swap out characters of the same type in the middle of any battle when it is their turn to attack. This will be used in place of an attack.
You will still have a base character that gets extended by different variations. Each variation will have slightly different abilities that will be explained more a little later. The attacking characters will have the following:

Hit Points (life points) : How many points until expiration
Attack Strength : Points damage against who they are fighting. Values similar to the following:
Recovery speed : regains x number of hit points per round
All the attackers will be read from an input file into a queue of some sort. When an attacker has lost all of its hit points, it is removed from the queue. The game ends when either the attacker queue is empty, or the BolniVerse fighters queue is empty.

### Example Command

- None for now. 

