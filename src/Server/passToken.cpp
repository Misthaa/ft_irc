/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   passToken.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madegryc <madegryc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:30:14 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/16 21:55:51 by madegryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::passToken(std::string content, int i)
{
    (void)content;
    (void)i;
    
    // if (_client[i].getNickname() != "")
    // {
    //     sendError(_client[i], "462", "* PASS :You may not reregister");
    //     return ;
    // }
    // if (content == _password)
    // {
    //     std::string msg = "Welcome to the IRC server " + _client[i].getUser();
    //     servSend(_fds[i].fd, msg);
    // }
    // _client[i].setUser(content);
    // return ;
}