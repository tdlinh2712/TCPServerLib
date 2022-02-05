#ifndef __TCPSERVER__
#define __TCPSERVER__

#include <stdint.h>
#include <string>
#include <pthread.h>

class TcpNewConnectionAcceptor;
class TcpClientServiceManager;
class TcpClientDbManager;
class TcpClient;

/* Server States */
#define TCP_SERVER_INITIALIZED (0)
#define TCP_SERVER_RUNNING (1)
#define TCP_SERVER_NOT_ACCEPTING_NEW_CONNECTIONS (2)
#define TCP_SERVER_NOT_LISTENING_CLIENTS (3)
#define TCP_SERVER_CREATE_MULTI_THREADED_CLIENT (4)
#define TCP_SERVER_STATE_MAX (5)

class TcpServer {

private:
    TcpNewConnectionAcceptor *tcp_new_conn_acc;
    TcpClientDbManager *tcp_client_db_mgr;
    TcpClientServiceManager *tcp_client_svc_mgr;

public:
    /* State Variables */
    uint32_t ip_addr;
    uint16_t port_no;
    std::string name;
    uint32_t state_flags;

    /* Constructors and Destructors */
    TcpServer(std::string ip_addr,  uint16_t port_no, std::string name);
    ~TcpServer();
    void Start();
    void Stop();
    uint32_t GetStateFlags();
    void SetAcceptNewConnectionStatus(bool);
    void SetClientCreationMode(bool);
    void SetListenAllClientsStatus(bool);
    void SetServerNotifCallbacks(void (*client_connected)(const TcpClient *), 
                                                    void (*client_disconnected)(const TcpClient *),
                                                    void (*client_msg_recvd)(const TcpClient *, unsigned char *, uint16_t),
                                                    void (*client_ka_pending)(const TcpClient *) );
    
    /* To Pass the Request to ClientDBMgr , This is Asynchronous*/
    void CreateNewClientRequestSubmission(TcpClient *tcp_client);
    void CreateDeleteClientRequestSubmission(TcpClient *tcp_client);

    /* To Pass the Request to TcpClientServiceMgr, this is Synchronous */
    void ClientFDStartListen(TcpClient *tcp_client);
    TcpClient* ClientFDStopListen(uint32_t , uint16_t);
    void AbortClient(uint32_t , uint16_t);
    void StopListeningAllClients();
};


#endif
