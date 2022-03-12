#include "server.h"

Server::Server()
{
    return;
}

std::shared_ptr<Client> Server::add_client(std::string id)
{
    bool repeated_id_f{false};

    // check id exist
    for (const auto&[pclient, wallet] : clients)
    {
        if (id == pclient->get_id())
        {
            // id exists already
            repeated_id_f = true;
            break;
        }
    }
    if (repeated_id_f)
    {
        // attach 4 digit random int to end of id
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist(1000, 9999);
        id += std::to_string(dist(rng));
    }
    std::shared_ptr<Client> pclient{new Client{id, *this}};
    clients[pclient] = 5.0;
    return pclient;
}

std::shared_ptr<Client> Server::get_client(std::string id) const
{
    for (const auto&[pclient, wallet] : clients)
    {
        if (id == pclient->get_id())
        {
            return pclient;
        }
    }
    // client not found return nullptr
    return nullptr;
}

double Server::get_wallet(std::string id) const
{
    std::shared_ptr<Client> pclient{get_client(id)};
    double wallet{};

    auto search = clients.find(pclient);
    if (search != clients.end()) {
        wallet = search->second;
    } else {
        // throw error id not found!!!!!!!!!!!!!!!!!!!
        std::cout << "Not found\n";
    }

    return wallet;
}

bool Server::parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value)
{
    // parse trx
    auto inx0{trx.find('-')};
    if (inx0 == std::string::npos)
        throw std::runtime_error("Not a standard transaction");
    auto inx1{trx.rfind('-')};
    if (inx0 == inx1)
        throw std::runtime_error("Not a standard transaction");
    sender = trx.substr(0, inx0);
    receiver = trx.substr(inx0 + 1, inx1 - inx0 - 1);
    value = std::stod(trx.substr(inx1 + 1));
    return true;
}

void show_wallets(const Server& server)
{
    std::map<std::shared_ptr<Client>, double>* pserver = (std::map<std::shared_ptr<Client>, double>*)&server;
    std::cout << std::string(20, '*') << std::endl;
 	for(const auto& client: *pserver)
 		std::cout << client.first->get_id() <<  " : "  << client.second << std::endl;
 	std::cout << std::string(20, '*') << std::endl;
}