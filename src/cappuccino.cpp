#include "cappuccino.h"

Cappuccino::Cappuccino()
{
    ingredients.push_back(new Espresso{2});
    ingredients.push_back(new Milk{2});
    ingredients.push_back(new MilkFoam{1});
}

Cappuccino::Cappuccino(const Cappuccino& other)
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
    for (const auto& i : other.side_items)
    {
        auto s = i->get_name();
        auto u = i->get_units();
        if (s == "Cinnamon")
            side_items.push_back(new Cinnamon{u});
        else if (s == "Chocolate")
            side_items.push_back(new Chocolate{u});
        else if (s == "Sugar")
            side_items.push_back(new Sugar{u});
        else if (s == "Cookie")
            side_items.push_back(new Cookie{u});
        else if (s == "Espresso")
            side_items.push_back(new Espresso{u});
        else if (s == "Milk")
            side_items.push_back(new Milk{u});
        else if (s == "MilkFoam")
            side_items.push_back(new MilkFoam{u});
        else if (s == "Water")
            side_items.push_back(new Water{u});
    }
}

void Cappuccino::operator=(const Cappuccino& other)
{
    if (this == &other)
        return;
    for (const auto& i : side_items)
        delete i;
    side_items.clear();
    for (const auto& i : other.side_items)
    {
        auto s = i->get_name();
        auto u = i->get_units();
        if (s == "Cinnamon")
            side_items.push_back(new Cinnamon{u});
        else if (s == "Chocolate")
            side_items.push_back(new Chocolate{u});
        else if (s == "Sugar")
            side_items.push_back(new Sugar{u});
        else if (s == "Cookie")
            side_items.push_back(new Cookie{u});
        else if (s == "Espresso")
            side_items.push_back(new Espresso{u});
        else if (s == "Milk")
            side_items.push_back(new Milk{u});
        else if (s == "MilkFoam")
            side_items.push_back(new MilkFoam{u});
        else if (s == "Water")
            side_items.push_back(new Water{u});
    }
}

Cappuccino::~Cappuccino()
{
    for(const auto& i : side_items)
        delete i;
    side_items.clear();
}

double Cappuccino::price()
{
    double price = 0;
    for(auto ingredient : ingredients)
    {
        price += ingredient->price();
    }
    for(auto ingredient : side_items)
    {
        price += ingredient->price();
    }
    return price;
}

std::string Cappuccino::get_name()
{
    return "Cappuccino";
}

void Cappuccino::add_side_item(Ingredient* side)
{
    side_items.push_back(side);
}

std::vector<Ingredient*>& Cappuccino::get_side_items()
{
    return side_items;
}