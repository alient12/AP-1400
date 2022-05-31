#ifndef Q4_H
#define Q4_H

namespace q4
{
    struct Vector2D
    {
    double x{};
    double y{}; 
    };

    struct Sensor
    {
        Vector2D pos;
        double accuracy;    
    };

    // inline Vector2D kalman_filter(std::vector<Sensor> sensors)
    // {
    //     double x_k{};
    //     double p_k{};
    //     for (auto sensor : sensors)
    //     {
    //         double p_k_1{p_k + sensor.accuracy};
    //         double k{p_k_1 / (p_k_1 + sensor.accuracy)};
    //         x_k = x_k + k * (sensor.pos.x - x_k);
    //         p_k = (1 - k) * p_k_1;
    //     }
    // }
}


#endif //Q4_H