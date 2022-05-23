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

using namespace ftxui;

Element ColorTile(int red, int green, int blue) {
return text("") | size(WIDTH, GREATER_THAN, 14) |
        size(HEIGHT, GREATER_THAN, 7) | bgcolor(Color::RGB(red, green, blue));
}

Element ColorString(int red, int green, int blue) {
return text("RGB = (" +                    //
            std::to_string(red) + "," +    //
            std::to_string(green) + "," +  //
            std::to_string(blue) + ")"     //
);
}


void EspressoBased::brew()
{
    using namespace std::chrono_literals;

    std::string reset_position;
    for (float percentage = 0.0f; percentage <= 1.0f; percentage += 0.02f) {
        std::string data_downloaded =
            std::to_string(int(percentage * 100)) + "/100";
        auto document = hbox({
            text("Brewing:"),
            gauge(percentage) | flex,
            text(" " + data_downloaded),
        });
        auto screen = Screen(100, 1);
        Render(screen, document);
        std::cout << reset_position;
        screen.Print();
        reset_position = screen.ResetPosition();

        std::this_thread::sleep_for(0.01s);
    }
    std::cout << std::endl;
    
    
    int red = 0;
    int green = 0;
    int blue = 100;
    auto slider_red = Slider("Red  :", &red, 0, 255, 1);
    auto slider_green = Slider("Green:", &green, 0, 255, 1);
    auto slider_blue = Slider("Blue :", &blue, 0, 255, 1);
    
    auto container = Container::Vertical({

    });
    
    auto renderer = Renderer(container, [&] {
        return hbox({
                separatorEmpty(),
                separatorHeavy(),
                vbox({
                    ColorTile(red, green, blue) | size(HEIGHT, LESS_THAN, 1),
                    ColorTile(red + 100, green, blue) | size(HEIGHT, LESS_THAN, 4),
                }) | xflex,
            }) |
            border | size(WIDTH, LESS_THAN, 15) | size(HEIGHT, GREATER_THAN, 8);
    });
    auto screen = ScreenInteractive::TerminalOutput();
    screen.Loop(renderer);
    
}

void EspressoBased::coffie_maker()
{
    int red = 0;
    int green = 0;
    int blue = 100;
    auto slider_red = Slider("Red  :", &red, 0, 255, 1);
    auto slider_green = Slider("Green:", &green, 0, 255, 1);
    auto slider_blue = Slider("Blue :", &blue, 0, 255, 1);
    
    auto container = Container::Vertical({
        slider_red,
        slider_green,
        slider_blue,
    });
    
    auto renderer = Renderer(container, [&] {
        return hbox({
                ColorTile(red, green, blue) | size(HEIGHT, LESS_THAN, 1),
                separator(),
                ColorTile(red + 100, green, blue) | size(HEIGHT, LESS_THAN, 1),
                separator(),
                vbox({
                    slider_red->Render(),
                    separator(),
                    slider_green->Render(),
                    separator(),
                    slider_blue->Render(),
                    separator(),
                    ColorString(red, green, blue),
                    separator(),
                    ColorTile(red, green, blue) | size(HEIGHT, LESS_THAN, 1),
                }) | xflex,
            }) |
            border | size(WIDTH, LESS_THAN, 80);
    });
    auto screen = ScreenInteractive::TerminalOutput();
    screen.Loop(renderer);
    
}