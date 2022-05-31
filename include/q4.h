#ifndef Q4_H
#define Q4_H

#include <numeric>

namespace q4
{
    struct Vector2D
    {
        double x{};
        double y{};
        Vector2D operator+(const Vector2D& rhs) const
        {
            return {x + rhs.x, y + rhs.y};
        };
        Vector2D operator*(double rhs) const
        {
            return {x * rhs, y * rhs};
        };
    };


    struct Sensor
    {
        Vector2D pos;
        double accuracy;    
    };

    inline Vector2D kalman_filter(std::vector<Sensor> sensors)
    {
        Vector2D avg{0, 0};
        auto sensor_sum = std::accumulate(
            sensors.begin(), sensors.end(), Sensor{{0, 0}, 0}, 
            [] (Sensor old, Sensor s)
            {
                double acc = old.accuracy + s.accuracy;
                Sensor result{old.pos + s.pos * s.accuracy, acc};
                return result;
            });

        avg.x = sensor_sum.pos.x / sensor_sum.accuracy;
        avg.y = sensor_sum.pos.y / sensor_sum.accuracy;
        return avg;
    }
}


#endif //Q4_H