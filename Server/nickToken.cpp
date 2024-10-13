/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nickToken.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madegryc <madegryc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 22:02:37 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/13 17:25:50 by madegryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::nickToken(std::string content, int i)
{
    int countWord = 0;

    countWord = std::count(content.begin(), content.end(), ' ') + 1;
    if (countWord != 1)
    {
        servSend(_fds[i].fd, ":localhost 461 * NICK :Not enough parameters");
        return;
    }
    if (_fds[i].fd == -1)
    {
        servSend(_fds[i].fd, ":localhost 451 * NICK :You have not registered");
        return;
    }
    if (content.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]-{}\\^") != 0)
    {
        servSend(_fds[i].fd, ":localhost 432 * NICK :Erroneous nickname");
        return;
    }
    _client[i].setNickname(content);
    std::string msg = "name : " + _client[i].getNickname();
    std::cout << msg << std::endl;
    servSend(_fds[i].fd, msg);
}