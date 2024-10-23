/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madegryc <madegryc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:07:52 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/22 19:59:14 by madegryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
# define BOT_HPP

# include <iostream>
# include <string>
# include <sys/socket.h>
# include <poll.h>
# include <unistd.h>
# include <sstream>
#include <map>  
# include "client.hpp"

class bot
{
    public:
        bot(std::string nickname, std::string port, std::string password);
        ~bot();
        
        void run();
        void readDataBot();
        void priceIsRight(std::string content, std::string player);
        bool isNewPlayer(std::string player);
        void addPlayer(std::string player);
    private:
        int _clientSocket;
        std::string _nickname;
        std::string _port;
        std::string _password;
        pollfd _fds;
        std::map<std::string, int> _playerMap;
};

#endif