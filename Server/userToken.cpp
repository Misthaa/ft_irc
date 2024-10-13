/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   userToken.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madegryc <madegryc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:14:07 by roguigna          #+#    #+#             */
/*   Updated: 2024/10/13 16:27:49 by madegryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::userToken(std::string content, int i)
{
    std::string msg;
    int countWord = 0;

    countWord = std::count(content.begin(), content.end(), ' ') + 1;
    if (countWord != 1)
    {
        servSend(_fds[i].fd, ":localhost speError * NICK :Not enough parameters");
        return;
    }
    if (_fds[i].fd == -1)
    {
        servSend(_fds[i].fd, ":localhost speError * NICK :You have not registered");
        return;
    }
    if (content.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]-{}\\^") != 0)
    {
        servSend(_fds[i].fd, ":localhost speError * NICK :Erroneous username");
        return;
    }
    _client[i].setUser(content);
    // std::string msg2 = "User : " + _client[i].getUser();
    // std::cout << msg2 << std::endl;
    // servSend(_fds[i].fd, msg2);
}