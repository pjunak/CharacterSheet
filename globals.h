#ifndef GLOBALS_H
#define GLOBALS_H

#endif // GLOBALS_H

#include <QString>
#include <vector>

// Global error code
int errorCode = 0;

// Character stats structures
// Character name
struct character_name{
    QString title_before = "";
    QString first = "";
    QString middle = "";
    QString last = "";
    QString title_after = "";
};
// Character class levels
struct character_classes{
    int barbarian = 0;
    int bard = 0;
    int cleric = 0;
    int druid = 0;
    int fighter = 0;
    int monk = 0;
    int paladin = 0;
    int ranger = 0;
    int rouge = 0;
    int sorcerer = 0;
    int warlock = 0;
    int wizard = 0;
    int artificer = 0;
    int blood_hunter = 0;
};
// Character attributes
struct character_attributes{
    int STR = 10;
    int DEX = 10;
    int CON = 10;
    int INT = 10;
    int WIS = 10;
    int CHA = 10;
};
//Character proficiencies
struct character_proficiencies{
    std::vector<QString> weapons;
    std::vector<QString> armor;
    std::vector<QString> tools;
    std::vector<QString> languages;
};
// Chaaracter skill proficiencies
struct character_skill_proficiencies{
    int acrobatics = 0;
    int animal_handling = 0;
    int arcana = 0;
    int athletics = 0;
    int deception = 0;
    int history = 0;
    int insight = 0;
    int intimidation = 0;
    int investigation = 0;
    int medicine = 0;
    int nature = 0;
    int perception = 0;
    int performance = 0;
    int persuasion = 0;
    int religion = 0;
    int sleight_of_hand = 0;
    int stealth = 0;
    int survival = 0;
};
/**
 * @brief The character_data struct Struct for accesin other character structs in code
 */
struct character_data{
    character_name Name;
    character_classes Class;
    character_attributes Att;
    character_proficiencies Prof;
    character_skill_proficiencies Skill;
} Ch;
