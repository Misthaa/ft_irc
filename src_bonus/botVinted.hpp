/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   botVinted.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madegryc <madegryc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:07:52 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/22 19:59:14 by madegryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOTVINTED_HPP
# define BOTVINTED_HPP

# include <iostream>
# include <string>
# include <sys/socket.h>
# include <poll.h>


# include "client.hpp"

class botVinted
{
    public:
        botVinted(std::string nickname, std::string port, std::string password);
        ~botVinted();
        
        void run();
        void readDataBot();

    private:
        int _clientSocket;
        std::string _nickname;
        std::string _port;
        std::string _password;
        pollfd _fds;
};

#endif