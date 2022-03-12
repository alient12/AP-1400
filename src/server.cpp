#include "server.h"

std::vector<std::string> pending_trxs{};

// Server constructor
//********************************************************
Server::Server()
{
    return;
}
//********************************************************

// adds client to server
//********************************************************
std::shared_ptr<Client> Server::add_client(std::string id)
{
    bool repeated_id_f{false};

    // check id
    for (const auto&[pclient, wallet] : clients)
        if (id == pclient->get_id())
        {
            // id exists already
            repeated_id_f = true;
            break;
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
//********************************************************

// get client from server by id; returns null pointer if not found
//********************************************************
std::shared_ptr<Client> Server::get_client(std::string id) const
{
    for (const auto&[pclient, wallet] : clients)
        if (id == pclient->get_id()) return pclient;
    // client not found return nullptr
    return nullptr;
}
//********************************************************

// get client wallet from server by id
//********************************************************
double Server::get_wallet(std::string id) const
{
    std::shared_ptr<Client> pclient{get_client(id)};
    double wallet{};

    auto search = clients.find(pclient);
    if (search != clients.end())
        wallet = search->second;
    else
        throw std::runtime_error("invalid id");
    return wallet;
}
//********************************************************

// parse transactions string and return true if succed
//********************************************************
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
//********************************************************

// adds transactions to pending list if valid
//********************************************************
bool Server::add_pending_trx(std::string trx, std::string signature) const
{
    std::string sender{}, receiver{};
    double value;
    parse_trx(trx, sender, receiver, value);
    
    // check if receiver exists
    if (get_client(receiver) == nullptr) return false;
    
    double wallet{get_wallet(sender)};
    bool authentic = crypto::verifySignature(get_client(sender)->get_publickey(), trx, signature);

    // check wallet and signature
    if (wallet >= value && authentic)
    {
        pending_trxs.push_back(trx);
        return true;
    }
    return false;
}
//********************************************************

// run mining process, finish when succed
//********************************************************
size_t Server::mine()
{
    std::string mempool{};
    std::string miner{};
    size_t miner_nonce{};
    bool is_mining_f{true};
    
    // generating mempool
    for (auto trx : pending_trxs) mempool += trx;
    
    // mining
    while (is_mining_f)
    {
        for (const auto&[pclient, wallet] : clients)
        {
            size_t nonce{pclient->generate_nonce()};
            std::string final_string{mempool + std::to_string(nonce)};
            std::string hash{crypto::sha256(final_string)};
            if (hash.substr(0, 10).find("000") != std::string::npos)
            {
                miner = pclient->get_id();
                miner_nonce = nonce;
                std::cout << "miner: " << miner << std::endl;
                is_mining_f = false;
                break;
            }
        }
    }
    
    // applying transactions
    for (auto trx : pending_trxs)
    {
        std::string sender{}, receiver{};
        double value;
        parse_trx(trx, sender, receiver, value);
        clients[get_client(sender)] -= value;
        clients[get_client(receiver)] += value;
    }
    pending_trxs.clear();
    
    // bonus to miner
    clients[get_client(miner)] += 6.25;
    return miner_nonce;
}
//********************************************************

// show server clients wallets
//********************************************************
void show_wallets(const Server& server)
{
    std::map<std::shared_ptr<Client>, double>* pserver = (std::map<std::shared_ptr<Client>, double>*)&server;
    std::cout << std::string(20, '*') << std::endl;
 	for(const auto& client: *pserver)
 		std::cout << client.first->get_id() <<  " : "  << client.second << std::endl;
 	std::cout << std::string(20, '*') << std::endl;
}
//********************************************************