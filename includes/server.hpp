/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:07:14 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/21 17:48:11 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <string>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <cstdlib>
# include <poll.h>
# include <cstring>
# include <algorithm>
# include <stdexcept>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>

#include "client.hpp"
#include "channel.hpp"

# define MAX_CLIENT  100
# define MAX_CHANNEL 100


class Server
{
    public:
        Server();
        ~Server();
        void start(char **av);
        int getServerSocket() { return _serverSocket; }
        int acceptClient();
        void setPassword(std::string password);
        void setPort(char *port);
    private:
        int _serverSocket;
        pollfd _fds[MAX_CLIENT + 1];
        Client _client[MAX_CLIENT];
        Channel _channel[MAX_CHANNEL];
        
        char   BUFF[MAX_CLIENT][1024];
        std::string _password;
        std::string  _sPort;
        int _port;
        // void readData(std::string token, std::string content, int i);
        void readData(char *BUFF, int i);
        void newClient();
        
        void nickToken(std::string content, int i);
        void userToken(std::string content, int i);
        void prvMessageToken(std::string content, int i);
        void prvMessage(std::string content, int i);
        void channelMessage(std::string content, int i);
        bool checkIsClient(int i);
        void joinToken(std::string content, int i);
        void inviteToken(std::string content, int i);
        void topicToken(std::string content, int i);
        void kickToken(std::string content, int i);
        void passToken(std::string content, int i);
        void quitToken(std::string content, int i);
        void partToken(std::string content, int i);
        void modeToken(std::string content, int i);
        int  execMode(std::string mode, std::string infos, int channelIndex, int clientIndex);
        int  isClientExist(std::string nickname);


        void servSend(int fd, std::string msg);
        void sendError(Client& client, std::string errorCode, std::string errorMsg);

};


//utils :   
std::string	ft_clearString(const std::string &str);
int ft_stoi(const std::string &str);

#endif