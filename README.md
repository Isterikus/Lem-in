# Lem-in

Our six project in UNIT Factory.

The goal of this project is to find the quickest way to get n ants across the farm.

At the beginning of the game, all the ants are in the room ##start. The goal is to bring them to the room ##end with as few
turns as possible. Each room can only contain one ant at a time. (except at ##start and ##end which can contain as many ants
as necessary.)

At each turn you can move each ant only once and through a tube (the room at the receiving end must be empty).

Program get data from standart output in the following format: number_of_ants, the_rooms, the_links.

The ant farm is defined by the following links:
5                      - number of ants
##start                - mean all ants will be in room described in next line
1 23 3                 - room describing mean (1) == (room name, can be string), (23) == X coordinate, (3) == Y coord
2 16 7
#comment               - just comment
3 16 3
7 4 8
##end                  - mean all ants must be in this room after moving
0 9 5
0-3                    - tube between tho rooms, mean room 0 is connected with room 4
1-3
7-3
7-2

Example of work:
![Example](https://cloud.githubusercontent.com/assets/17950689/24323370/20331ee4-117d-11e7-98f1-1c847d57c886.jpg)

Where output contain farm and my info, such as:

Table, where for each room there is line which shows with which rooms this is connected.

Then it shows all possible ways from ##start to ##end.

Notice that this two thing don't use rooms name. It use rooms index which start from 0 to n.

Then goes solution which mean:

L4-3 == Ant number 4 goes to room 3.

Each new turn is started from a newline.

You can test valid and invalid maps from 'maps' folder.
