#include "cappuccino.h"

Cappuccino::Cappuccino()
{
    ingredients.push_back(new Espresso{2});
    ingredients.push_back(new Milk{2});
    ingredients.push_back(new MilkFoam{1});
}

// Cappuccino::Cappuccino(const Cappuccino& other)
// {
//     for (const auto& i : other.ingredients)
//         ingredients.push_back(i->clone());
// }

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