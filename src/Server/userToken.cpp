/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   userToken.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madegryc <madegryc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:14:07 by roguigna          #+#    #+#             */
/*   Updated: 2024/10/29 21:39:25 by madegryc         ###   ########.fr       */
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
        sendError(_client[i], "461", "IRCserv: USER :Not enough parameters");
        return;
    }
    if (_fds[i].fd == -1)
    {
        sendError(_client[i], "461", "IRCserv: USER :You have not registered");
        return;
    }
    if (content.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]-{}\\^#") != 0)
    {
        sendError(_client[i], "432", "IRCserv: USER :Erroneous username");
        return;
    }
    if (_client[i].getUser() != "")
    {
        sendError(_client[i], "462", "Unauthorized command (already registered)");
        return ;
    }
    _client[i].setUser(content);
    std::string msg = "Correct User, " + _client[i].getUser();
    servSend(_fds[i].fd, msg);
    if (_client[i].getNickname() != "" && _client[i].getCorrectPassword() == true)
    {
        msg = ":localhost:" + _sPort + " 001 " + _client[i].getNickname() + " :Welcome to IRC " + _client[i].getNickname() + "!";
        servSend(_fds[i].fd, msg);
    }
}