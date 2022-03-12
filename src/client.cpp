#include "client.h"


// Client constructor
//********************************************************
Client::Client(std::string id, const Server& server):id(id), server(&server)
{
    crypto::generate_key(public_key, private_key);
}
//********************************************************

// id getter
//********************************************************
std::string Client::get_id()
{
    return id;
}
//********************************************************

// return client wallet
//********************************************************
double Client::get_wallet() const
{
    return server->get_wallet(id);
}
//********************************************************

// public key getter
//********************************************************
std::string Client::get_publickey() const
{
    return public_key;
}
//********************************************************

// sign the client message with private key
//********************************************************
std::string Client::sign(std::string txt) const
{
    std::string signature = crypto::signMessage(private_key, txt);
    return signature;
}
//********************************************************

// transfer money from the client account to a client account
//********************************************************
bool Client::transfer_money(std::string receiver, double value)
{
    std::string trx{id + '-' + receiver + '-' + std::to_string(value)};
    std::string signature{sign(trx)};
    bool valid {server->add_pending_trx(trx, signature)};
    return valid;
}
//********************************************************

// generate the client nonce
//********************************************************
size_t Client::generate_nonce()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 9999);
    return dist(rng);
}
//********************************************************