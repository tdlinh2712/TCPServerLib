#include <unistd.h>
#include "TcpServerController.h"
#include "TcpClientDBManager.h"
#include "TcpClient.h"

TcpClientDbManager::TcpClientDbManager(TcpServerController *tcp_ctrlr) {

    this->tcp_ctrlr = tcp_ctrlr;
}

TcpClientDbManager::~TcpClientDbManager() {


}

void
TcpClientDbManager::StartTcpClientDbMgrInit() {


}

void
TcpClientDbManager::AddClientToDB(TcpClient *tcp_client) {

    this->tcp_client_db.push_back(tcp_client);
}

void
TcpClientDbManager::DisplayClientDb() {

    std::list<TcpClient *>::iterator it;
    TcpClient *tcp_client;

    for (it = this->tcp_client_db.begin(); it != this->tcp_client_db.end(); ++it) {
        tcp_client = *it;
        tcp_client->Display();
    }
}

void 
TcpClientDbManager::CopyAllClientsTolist (std::list<TcpClient *> *list) {

    std::list<TcpClient *>::iterator it;
    TcpClient *tcp_client;

    for (it = this->tcp_client_db.begin(); it != this->tcp_client_db.end(); ++it) {
        tcp_client = *it;
        list->push_back(tcp_client);
    }
}

void TcpClientDbManager::Purge()
{
    std::list<TcpClient *>::iterator it;
    TcpClient *tcp_client, *next_tcp_client;

    for (it = this->tcp_client_db.begin(), tcp_client = *it;
         it != this->tcp_client_db.end();
         tcp_client = next_tcp_client)
    {

        next_tcp_client = *(++it);

        this->tcp_client_db.remove(tcp_client);
        close(tcp_client->comm_fd);
        delete tcp_client;
    }
}