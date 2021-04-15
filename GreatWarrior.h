//////////////////////////////////
/*          Ahmet Polat        */
/*          150170109          */
/*          08/04/2021         */
//////////////////////////////////
#ifndef GREATWARRIOR_H
#define GREATWARRIOR_H

#include <iostream>
#include <string>

using namespace std;

class Land{
    friend class Character;

    private:
        string const name;
        enum holding_type{
            village = 5, //equal gold value
            castle = 7,
            city = 10
        };
        holding_type holding_enum;
        string const holding;
        Land *next;

    public:
        Land(string = " ", string = " ");
        Land(const Land&);
        //~Land();

        //getters
        string getName() const{
            return name;
        }
        string getHolding() const{
            return holding;
        }
        Land* getNext() const{
            return next;
        }      
};

class Character{
    friend class CharacterList;
    private:
        string name;
        int man_power;
        int gold;
        int num_of_lands;
        Land *lands;
        
    public:
        Character(string = " ", int = 0, int = 0, int = 0);
        Character(const Character&);
        //~Character();
        void getTaxes();
        void addLand(const Land&);
        Land removeLand(string);
        void removeLandRandom(int);
        bool isItYourLand(string);

        //getters
        string getName() const{
            return name;
        }
        int getManPower() const{
            return man_power;
        }
        int getGold() const{
            return gold;
        }
        int getNumOfLands() const{
            return num_of_lands;
        }
        Land* getLands() const{
            return lands;
        }
        //setters
        void setName(string name){
            this->name = name;
        }
        void setManPower(int man_power){
            this->man_power = man_power;
        }
        void setGold(int gold){
            this->gold = gold;
        }     
};

class CharacterList{
    private:
        Character* characters;
        int size;

    public:
        CharacterList();
        //~CharacterList();
        void addCharacter(const Character&);
        void delCharacter(string);
        Character& getPlayer(string);
        string getLandOwner(string);
        bool isThereAnyPlayer(string);

        //getters
        string getCharactersName(int num) const{
            return characters[num].getName();
        }
        int getSize() const{
            return size;
        }
        Character* getCharacters() const{
            return characters;
        }
};

#endif