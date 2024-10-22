/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   userToken.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:14:07 by roguigna          #+#    #+#             */
/*   Updated: 2024/10/22 18:04:09 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::userToken(std::string content, int i)
{
    int nbWord = 0;

    nbWord = countWord(content);
    content = content.substr(0, content.find(" "));
    if (nbWord < 1)
    {
        sendError(_client[i], "461", "* USER :Not enough parameters");
        return;
    }
    if (_fds[i].fd == -1)
    {
        sendError(_client[i], "461", "* USER :You have not registered");
        return;
    }
    if (content.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]-{}\\^#") != 0)
    {
        sendError(_client[i], "432", "* USER :Erroneous username");
        return;
    }
    for (int j = 1; j < MAX_CLIENT; j++)
    {
        if (_client[i].getUser() == content)
        {
            sendError(_client[i], "462", "Unauthorized command (already registered)");
            return ;
        }
    }
    _client[i].setUser(content);
    std::string msg = "user : " + _client[i].getUser();
    servSend(_fds[i].fd, msg);
    if (_client[i].getNickname() != "" && _client[i].getCorrectPassword() == true)
    {
        msg = ":localhost:" + _sPort + " 001 " + _client[i].getNickname() + " :Welcome to IRC " + _client[i].getNickname() + "!";
        servSend(_fds[i].fd, msg);
    }
}