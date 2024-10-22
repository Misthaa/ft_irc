/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nickToken.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 22:02:37 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/21 10:58:27 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::nickToken(std::string content, int i)
{
    int countWord = 0;

    countWord = std::count(content.begin(), content.end(), ' ') + 1;
    content = content.substr(0, content.find(" "));
    if (countWord < 1)
    {
        sendError(_client[i], "461", "* NICK :Not enough parameters");
        return;
    }
    if (_fds[i].fd == -1)
    {
        sendError(_client[i], "451", "* NICK :You have not registered");
        return;
    }
    if (content.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]-{}\\^") != 0)
    {
        sendError(_client[i], "432", "* NICK :Erroneous username");
        return;
    }
    for (int j = 1; j < MAX_CLIENT; j++)
    {
        if (_client[j].getNickname() == content)
        {
            sendError(_client[i], "433", "* NICK : Nickname is already in use");
            return ;
        }
    }
    std::string msg;
    if (_client[i].getNickname() == "")
    {
        msg = ":localhost:" + _sPort + " 001 " + content + " :Welcome to the IRC network, " + content;
        servSend(_fds[i].fd, msg);
    }
    msg = ":" + _client[i].getNickname() + "!@localhost:" +  " NICK :" + content;
    _client[i].setNickname(content);
    servSend(_fds[i].fd, msg);
}