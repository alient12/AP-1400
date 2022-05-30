#ifndef Q3_H
#define Q3_H

#include <queue>

namespace q3
{
    struct Flight
    {
        std::string flight_number;
        size_t duration;
        size_t connections;
        size_t connection_times;
        size_t price;
        bool operator<(const Flight& other) const
        {
            return duration + connection_times + 3*price > other.duration + other.connection_times + 3*other.price;
        }
    };

    inline std::priority_queue<Flight> gather_flights(std::string filename)
    {
        std::priority_queue<Flight> flights;
        std::regex rx(R"(\d+- flight_number:(\w+) - duration:(.+) - connections:(\d+) - connection_times:(.+) - price:(\d+)\s*)");
        std::regex rx_duration(R"((\d+)h(\d+)?m?)");
        std::ifstream file(filename);
        std::string line;
        while (std::getline(file, line))
        {
            std::smatch match;
            if (std::regex_match(line, match, rx))
            {
                Flight f;
                f.flight_number = std::string(match[1]);

                std::smatch match_duration;
                std::string duration = std::string(match[2]);   
                std::regex_match(duration, match_duration, rx_duration);
                f.duration = std::stoi(match_duration[1]) * 60 + (match_duration[2].length() ? std::stoi(match_duration[2]) : 0);

                f.connections = std::stoi(match[3]);

                std::string connection_times = std::string(match[4]);
                std::regex rx_connection_times(R"((\d+)h((\d+)m)?)");
                std::smatch match_connection_times;
                f.connection_times = 0;
                while(std::regex_search(connection_times, match_connection_times, rx_connection_times))
                {
                    f.connection_times += std::stoi(match_connection_times[1]) * 60 + (match_connection_times[3].length() ? std::stoi(match_connection_times[3]) : 0);
                    connection_times = match_connection_times.suffix().str();
                }

                f.price = std::stoi(match[5]);
                flights.push(f);
            }
        }
        return flights;
    }
}

#endif //Q3_H