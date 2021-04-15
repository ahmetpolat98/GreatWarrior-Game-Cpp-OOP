#include <iostream>
#include <string>
#include "GreatWarrior.h"

using namespace std;

Land::Land(string in_name, string in_holding)
    :name(in_name), holding(in_holding)
    {
        next = NULL;
        if (holding == "village")
            holding_enum = village;
        else if (holding == "city")
            holding_enum = city;       
        else if (holding == "castle")
            holding_enum = castle;
        else{
            cout << name << " not assigned holding" << endl;//
            holding_enum = castle; 
        }                   
    }

Land::Land(const Land& copy_land)
    :name(copy_land.name), holding(copy_land.holding)
    {
        next = NULL;
        holding_enum = copy_land.holding_enum;
    }
//

Character::Character(string in_name, int in_man_power, int in_gold, int in_num_of_lands)
    :name(in_name), man_power(in_man_power), gold(in_gold), num_of_lands(in_num_of_lands)
    {lands = NULL;}

Character::Character(const Character& copy_character)
    :name(copy_character.name), man_power(copy_character.man_power), gold(copy_character.gold), num_of_lands(copy_character.num_of_lands)
    {lands = copy_character.lands;}//

void Character::addLand(const Land& add_land){
    if(lands == NULL){
        lands = new Land(add_land);
    }
    else{
        Land *iter = lands;
        while (iter->next != NULL)
        {
            iter = iter->next;
        }
        iter->next = new Land(add_land);
    } 
    num_of_lands++;
}

void Character::getTaxes(){
    Land *iter = lands;
    while (iter)
    {
        gold += iter->holding_enum;
        iter = iter->next;
    }
}

Land Character::removeLand(string del_land){

    string re_name,re_holding;
    
    //remove head   
    if(lands->name == del_land){
        Land *temp = lands;
        lands = lands->next;

        re_name = temp->name;
        re_holding = temp->holding;

        temp->next = NULL;
        delete temp;
        num_of_lands--;
        return Land(re_name, re_holding);
    }
    else{
        Land *iter = lands;
        while (iter->next != NULL && iter->next->name != del_land){
            iter = iter->next;
        }
        //stop before the node we want to delete
        if (iter->next->name == del_land){
            Land *temp_del = iter->next;
            iter->next = iter->next->next;

            re_name = temp_del->name;
            re_holding = temp_del->holding;

            temp_del->next = NULL;
            delete temp_del;
            num_of_lands--;
            return Land(re_name, re_holding);
        }
        else{
            cout << "Land not found" << endl ;//
            return Land();
        }
    }
}

void Character::removeLandRandom(int x){
    if(x == 0){
        Land *temp = lands;
        lands = lands->next;

        temp->next = NULL;
        delete temp;
    }
    else{
        Land *iter = lands;
        for (int i = 1; i < x; i++)
        {
            iter = iter->next;
        }
        Land *temp_del = iter->next;
        iter->next = iter->next->next;
        
        temp_del->next = NULL;
        delete temp_del;
    }
    num_of_lands--;
}

bool Character::isItYourLand(string get_land){
    Land *iter = lands;
    while (iter)
    {
        if (iter->name == get_land)
        {
            return true;
        }
        iter = iter->next;
    }
    return false;
}

// Character::~Character(){
//     while(lands){
//         Land* iter = lands;
//         lands = lands->next;
//         delete lands;
//     }
// }

//

CharacterList::CharacterList()
    :characters(nullptr), size(0){}

void CharacterList::addCharacter(const Character& add_char){
    size++;
    Character* temp = new Character[size];
    for(int i = 0; i < size - 1; i++){
        temp[i] = characters[i];
    }
    temp[size-1].name = add_char.name;
    temp[size-1].man_power = add_char.man_power;
    temp[size-1].gold = add_char.gold;
    temp[size-1].num_of_lands = add_char.num_of_lands;
    temp[size-1].lands = add_char.lands;
    
    if(characters != nullptr){
        delete []characters;
    }
    characters = temp;
    //delete [] temp;
}

void CharacterList::delCharacter(string del_name){  
    int num = 0, i;
    while (characters[num].name != del_name)
    {
        num++;
        if (num > size)// >=
        {
            cout << "Name is not found" << endl;
            return;
        } 
    }
    size--;
    Character* temp = new Character[size];
    for (i = 0; i < num; i++)
    {
        temp[i] = characters[i];
    }
    for (; i < size; i++)
    {
        temp[i] = characters[i+1];
    }
    delete [] characters;
    characters = temp;
    //delete [] temp;
}

Character& CharacterList::getPlayer(string char_name){
    for (int i = 0; i < size; i++)
    {
        if (characters[i].name == char_name)
        {
            return characters[i];
        }       
    }
    cout << "Player not found" << endl;  
    return characters[size-1];
}

string CharacterList::getLandOwner(string get_land){
    for (int i = 0; i < size; i++)
    {
        if(characters[i].isItYourLand(get_land))
            return characters[i].name;      
    }
    cout << get_land <<"'s owner not found" << endl;
    return " ";
}

bool CharacterList::isThereAnyPlayer(string player_name){
    bool flag = false;
    for (int i = 0; i < size; i++)
    {
        if(characters[i].name != player_name){
            flag = true;
            break;
        }
    }
    return flag;
}

// CharacterList::~CharacterList(){
//     delete [] characters;
// }