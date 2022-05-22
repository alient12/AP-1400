#include "espresso_based.h"


EspressoBased::~EspressoBased()
{
    for(const auto& i : ingredients)
        delete i;
    ingredients.clear();
}

EspressoBased::EspressoBased(const EspressoBased& other)
{
    for (const auto& i : other.ingredients)
    {
        auto s = i->get_name();
        auto u = i->get_units();
        if (s == "Cinnamon")
            ingredients.push_back(new Cinnamon{u});
        else if (s == "Chocolate")
            ingredients.push_back(new Chocolate{u});
        else if (s == "Sugar")
            ingredients.push_back(new Sugar{u});
        else if (s == "Cookie")
            ingredients.push_back(new Cookie{u});
        else if (s == "Espresso")
            ingredients.push_back(new Espresso{u});
        else if (s == "Milk")
            ingredients.push_back(new Milk{u});
        else if (s == "MilkFoam")
            ingredients.push_back(new MilkFoam{u});
        else if (s == "Water")
            ingredients.push_back(new Water{u});
    }
    
}

void EspressoBased::operator=(const EspressoBased& other)
{
    if (this == &other)
        return;
    for (const auto& i : ingredients)
        delete i;
    ingredients.clear();
    for (const auto& i : other.ingredients)
    {
        auto s = i->get_name();
        auto u = i->get_units();
        if (s == "Cinnamon")
            ingredients.push_back(new Cinnamon{u});
        else if (s == "Chocolate")
            ingredients.push_back(new Chocolate{u});
        else if (s == "Sugar")
            ingredients.push_back(new Sugar{u});
        else if (s == "Cookie")
            ingredients.push_back(new Cookie{u});
        else if (s == "Espresso")
            ingredients.push_back(new Espresso{u});
        else if (s == "Milk")
            ingredients.push_back(new Milk{u});
        else if (s == "MilkFoam")
            ingredients.push_back(new MilkFoam{u});
        else if (s == "Water")
            ingredients.push_back(new Water{u});
    }
}
