#ifndef MOCHA_H
#define MOCHA_H

#include "espresso_based.h"
#include "sub_ingredients.h"
#include "ingredient.h"
#include <vector>
#include <string>
#include <iostream>

class Mocha: public EspressoBased
{
public:
    Mocha();
    Mocha(const Mocha& cap);
	virtual ~Mocha();
    virtual void operator=(const Mocha& cap);

    virtual std::string get_name();
    virtual double price();

    void add_side_item(Ingredient* side);
    std::vector<Ingredient*>& get_side_items();

private:
    std::vector<Ingredient*> side_items;

};


#endif // MOCHA_H