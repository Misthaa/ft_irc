/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madegryc <madegryc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:20:39 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/15 19:08:57 by madegryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <string>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <cstdlib>

class Client
{
    public:
        Client();
        ~Client();
        void start(char **av);
        
        const std::string &getNickname() const{ return _nickname; }
        std::string &getUser() { return _user; }
        int  getClientSocket() const {return _clientSocket; }
        void setNickname(std::string nickname) { _nickname = nickname; }
        void setUser(std::string user) { _user = user; }
        void setClientSocket(int client) { _clientSocket = client; }
    
        bool operator==(const Client &c) const { return _clientSocket == c.getClientSocket(); }
        bool operator!=(const Client &c) const { return _clientSocket != c.getClientSocket(); }
        bool operator<(const Client &c) const { return _clientSocket < c.getClientSocket(); }
        bool operator>(const Client &c) const { return _clientSocket > c.getClientSocket(); }
        
    private:
        int _clientSocket;
        std::string _nickname;
        std::string _user;
};

#endif