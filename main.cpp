//////////////////////////////////
/*          Ahmet Polat        */
/*          150170109          */
/*          08/04/2021         */
//////////////////////////////////

#include <iostream>
#include <fstream>
#include "GreatWarrior.h"
#include "GreatWarrior.cpp"

#include <time.h>

 

/*	Define necessary classes and attributes in GreatWarrior.h and GreatWarrior.cpp */

/*	= Fill in the blanks in this main.cpp file. The parts that you need to implemented are specified below.
    = Please write your code between ///// FILL HERE ///// lines.
    = The expressions you need to print out with cout operation are given in necessary format.
    = You can use them directly by filling the variable parts.
*/

void listCharacters(CharacterList&);
void listLands(CharacterList&);
void readData(string, CharacterList&);
void printGameMenu();
bool endOfTurn(Character&, int, CharacterList&);

int main() {
    cout << "Welcome to the Great Warriors. Create your character and attack other lands to be a great warrior.\n" << endl;

    CharacterList charList;             // list object to store the characters

    string fileName = "characters.txt"; // read characters.txt file
    readData(fileName, charList);

    /* creating player's character */
    string name, land, general;
    cout << "Enter your name: ";
    cin >> name;

    cout << "Enter name of your capital: ";
    cin >> land;

    cout << "Enter name of your general: ";
    cin >> general;


    ///// FILL HERE /////

    /*  Create your constant general object and your own character object,
        then add your character into characters list */

    const Character our_general(general);
    Character player(name, 3, 20);

    Land first_land(land, "village");
    player.addLand(first_land);

    charList.addCharacter(player);
    ///// FILL HERE /////


    // In-game loop 
    int choice = 0, round = 0;
    while (choice != 6) {
        printGameMenu();

        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "You have rested in your palace." << endl;
            cout << "You've talked with your general " << our_general.getName() << "." << endl;

            round++;
            break;
        }
        case 2: {
            listLands(charList);
            cout << "Enter name of the land to attack." << endl;

            string land;
            cin >> land;

            ///// FILL HERE /////

            /*	Get the attacked player and execute the attack considering the manpower each side has:

                -	If you won, attacked side will lose all manpower and the attacked land will be yours. 
                    You will also lose some manpower (as much as attacked lose).
                    Print this: cout << "You've won the battle and conquered " << land << "." << endl;

                -	If you lose, you will lose all your manpower.
                    Print this: cout << "You've lost the battle and " << __number of manpower you lost__ << " manpower." << endl;
            */
            string attacked_char_name;
            int player_manpower, attacked_manpower;
            int player_last_manpower;

            attacked_char_name = charList.getLandOwner(land);
            // Character attacked_char = charList.getPlayer(attacked_char_name);

            player_manpower = charList.getPlayer(player.getName()).getManPower();
            attacked_manpower = charList.getPlayer(attacked_char_name).getManPower();

            //player lose war
            if(player_manpower < attacked_manpower){
                player_last_manpower = 0;
                charList.getPlayer(player.getName()).setManPower(player_last_manpower);
                cout << "You've lost the battle and " << player_manpower << " manpower." << endl;
            }
            else{//player win
                player_last_manpower = player_manpower - attacked_manpower;

                charList.getPlayer(attacked_char_name).setManPower(0);
                charList.getPlayer(player.getName()).setManPower(player_last_manpower);

                charList.getPlayer(player.getName()).addLand(charList.getPlayer(attacked_char_name).removeLand(land));
                cout << "You've won the battle and conquered " << land << "." << endl;

                if(charList.getPlayer(attacked_char_name).getNumOfLands() == 0){
                    charList.delCharacter(attacked_char_name);
                }
            }

            ///// FILL HERE /////

            round++;
            break;
        }
        case 3:
            cout << "How much manpower do you need? (1 manpower=5 gold)" << endl;

            int order;
            cin >> order;

            ///// FILL HERE /////

            /* Check if you have enough money to get the requested manpower:

                - 	If you have, you got the manpower you want.
                    Print this: cout << "Order successful. You have " << __number of manpower you have after purchase__ << " manpower." << endl;

                -	If you do not, print this: cout << "You do not have enough money." << endl;
            */
            int required_money;
            required_money = order * 5;
            int owned_money, owned_manpower; 
            int last_money, last_manpower;

            owned_money = charList.getPlayer(player.getName()).getGold();
            owned_manpower = charList.getPlayer(player.getName()).getManPower();

            if (owned_money >= required_money){
                last_money = owned_money - required_money;
                last_manpower = owned_manpower + order;

                charList.getPlayer(player.getName()).setGold(last_money);
                charList.getPlayer(player.getName()).setManPower(last_manpower);

                cout << "Order successful. You have " << charList.getPlayer(player.getName()).getManPower() << " manpower." << endl;
            }
            else{
                cout << "You do not have enough money." << endl;
            }
            ///// FILL HERE /////

            round++;
            break;
        case 4:
            listCharacters(charList);
            break;
        case 5:
            listLands(charList);
            break;
        case 6:
            return 0;
        default:
            cout << "You entered an invalid value. Try again." << endl;
        }

        ///// FILL HERE /////

        /*	Check if the game is over in two cases:

            -	Call the endOfTurn function which is defined below in the code.
                endOfTurn function executes the necessary end of turn process and
                returns a bool value which indicates if you can continue the game or not.

            -	Terminate the program if you are the only great warrior left.
                Print this: cout << __your player name__ << " is the only great warrior now." << endl;
        */

        if (!endOfTurn(player, round, charList)){
            return 0;
        }
        if (!charList.isThereAnyPlayer(player.getName())){
            cout << player.getName() << " is the only great warrior now." << endl;
            return 0;
        }        

        ///// FILL HERE /////
    }
}

void readData(string fileName, CharacterList& charList) {

    fstream dataFile(fileName.c_str());

    if (dataFile.is_open()) {

        string word;
        while (dataFile >> word) {

            string name, title;
            int money, manpower, numOfLands;

            name = word;
            dataFile >> manpower;
            dataFile >> money;
            dataFile >> numOfLands;

            ///// FILL HERE /////

            /* Create a new character with read data */
            Character new_char(name,manpower,money);

            ///// FILL HERE /////

            string landName, holding;

            for (int i = 0; i < numOfLands; i++) {
                dataFile >> landName;
                dataFile >> holding;

                ///// FILL HERE /////

                /* Create a new land object with read data and assign the land to the character you have created */
                Land new_land(landName,holding);
                new_char.addLand(new_land);
                ///// FILL HERE /////
            }

            ///// FILL HERE /////

            /* Add the character into character list */
            charList.addCharacter(new_char);
            ///// FILL HERE /////

        }

        dataFile.close();
    }
    else cout << "Unable to open the file" << endl;
    return;
}

void printGameMenu() {
    cout << endl;
    cout << "1. Stay in your palace" << endl;
    cout << "2. Attack to a land" << endl;
    cout << "3. Buy manpower" << endl;
    cout << "4. List characters" << endl;
    cout << "5. List lands" << endl;
    cout << "6. Exit" << endl;
    cout << endl;
}

void listCharacters(CharacterList& charList) {
    cout << endl;

    ///// FILL HERE /////

    /* Print out the names of each character in character list in a loop */
    int size_of_charlist = charList.getSize();
    for (int i = 0; i < size_of_charlist; i++)
    {
        cout << charList.getCharactersName(i) << endl;
    }
    
    ///// FILL HERE /////
}

void listLands(CharacterList& charList) {
    cout << endl;

    ///// FILL HERE /////

    /*	Loop over each character in characters list and print out their lands in following format:
        cout << __name of land__ << " " << __type of land__ << " owned by " << __name of player__ << endl;
        (i.e. Gotham city owned by Batman)
    */
    
    int size_of_charlist = charList.getSize();
    Character* chars = charList.getCharacters();
    for (int i = 0; i < size_of_charlist; i++)
    {
        Land *iter = chars[i].getLands();
        while (iter)
        {
            cout << iter->getName() << " " << iter->getHolding() << " owned by " << charList.getLandOwner(iter->getName()) << endl;
            iter = iter->getNext();
        }      
    }    

    ///// FILL HERE /////
    cout << endl;
}


bool endOfTurn(Character& player, int round, CharacterList& charList) { //return a bool value that indicates if the game is over or not.

    ///// FILL HERE /////

    /* End of turn evaluations:
        -	Collect taxes and feed soldiers

        -	Check the number of lands you have and if you do not have any lands left, the game is over
            Print this:	cout << "You are no longer a great warrior. You survived " << round << " turns." << endl;
                        cout << endl;
                        cout << "GAME OVER." << endl;

        -	Check the number of manpower you have and if you do not have any manpower left, you lose one of your lands randomly.
            Print this:	cout << "You lost one of your lands to rebellions since you don't have enough army." << endl;

        -	Check the amount of money you have, if you do not have enough money to feed your soldiers you lose
            the soldiers that you cannot feed. 1 gold for each soldier is needed. If you have 5 gold and 6 soldiers 1 soldier will
            run away from your army.
            Print this: cout << __number of runaway soldiers__ << " soldiers run away from your army because you don't have enough gold to feed them." << endl;

        -	At last, print your status in the following format:
            cout << "Turn " << round << ": " << " " << __name of your player__ << " has " << __number of lands you have__
        << " land(s), " << __number of manpower you have__ << " manpower and " << __number of golds you have__ << " golds." << endl;

    */

    charList.getPlayer(player.getName()).getTaxes();

    if(charList.getPlayer(player.getName()).getNumOfLands() <= 0){
        cout << "You are no longer a great warrior. You survived " << round << " turns." << endl;
        cout << endl;
        cout << "GAME OVER." << endl;
        return false;
    }
    
    if(charList.getPlayer(player.getName()).getManPower() <= 0){
        srand(time(NULL));

        int randomNum = rand() % charList.getPlayer(player.getName()).getNumOfLands();
        charList.getPlayer(player.getName()).removeLandRandom(randomNum);

        cout << "You lost one of your lands to rebellions since you don't have enough army." << endl;
    }

    int player_money, player_manpower, last_money, last_manpower;

    player_money = charList.getPlayer(player.getName()).getGold();
    player_manpower = charList.getPlayer(player.getName()).getManPower();

    if (player_money < player_manpower){
        int runaway_soldier = player_manpower - player_money;
        last_money = 0;
        last_manpower = player_manpower - runaway_soldier;

        charList.getPlayer(player.getName()).setGold(last_money);
        charList.getPlayer(player.getName()).setManPower(last_manpower);
        cout << runaway_soldier << " soldiers run away from your army because you don't have enough gold to feed them." << endl;
    }
    else{
        last_money = player_money - player_manpower;
        charList.getPlayer(player.getName()).setGold(last_money);
    }
    
    cout << "Turn " << round << ": " << " " << player.getName() << " has " << charList.getPlayer(player.getName()).getNumOfLands() << " land(s), " << charList.getPlayer(player.getName()).getManPower() << " manpower and " << charList.getPlayer(player.getName()).getGold() << " golds." << endl;

    return true;



    ///// FILL HERE /////

}


