/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nickToken.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madegryc <madegryc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 22:02:37 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/12 22:41:44 by madegryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::nickToken(std::string content, int i)
{
    std::string msg;
    int countWord = 0;

    countWord = std::count(content.begin(), content.end(), ' ') + 1;
    if (countWord != 1)
    {
        msg = ":localhost 461 * NICK :Not enough parameters";
        send(_fds[i].fd, msg.c_str(), msg.size(), 0);
        return;
    }
    if (_fds[i].fd == -1)
    {
        msg = ":localhost 451 * NICK :You have not registered";
        send(_fds[i].fd, msg.c_str(), msg.size(), 0);
        return;
    }
    if (content.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]-{}\\^") != 0)
    {
        msg = ":localhost 432 * NICK :Erroneous nickname";
        send(_fds[i].fd, msg.c_str(), msg.size(), 0);
        return;
    }
    
    // _fds[i].setNickname(content);
}