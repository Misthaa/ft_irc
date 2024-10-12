/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madegryc <madegryc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:07:14 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/12 22:36:09 by madegryc         ###   ########.fr       */
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

#include "../Client/client.hpp"

# define MAX_CLIENT 100

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
        std::string _password;
        int _port;
        void readData(std::string token, std::string content, int i);
        void nickToken(std::string content, int i);
};

#endif