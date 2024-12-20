/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nickToken.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madegryc <madegryc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 22:02:37 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/29 15:10:45 by madegryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::nickToken(std::string content, int i)
{
    int nbWord = 0;

    nbWord = countWord(content);
    content = content.substr(0, content.find(" "));
    if (nbWord < 1)
    {
        sendError(_client[i], "461", "IRCserv:  NICK :Not enough parameters");
        return;
    }
    if (_fds[i].fd == -1)
    {
        sendError(_client[i], "451", "IRCserv:  NICK :You have not registered");
        return;
    }
    if (content.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]-{}\\^") != 0)
    {
        sendError(_client[i], "432", "IRCserv: NICK :Erroneous username");
        return;
    }
    for (int j = 1; j < MAX_CLIENT; j++)
    {
        if (_client[j].getNickname() == content)
        {
            sendError(_client[i], "433", "IRCserv:  NICK : Nickname is already in use");
            return ;
        }
    }
    std::string msg;
    std::cout << "NICK: " << _client[i].getNickname() << std::endl;
    if (_client[i].getNickname() == "")
    {
        if (_client[i].getUser() != "" && _client[i].getCorrectPassword() == true)
        {
            msg = ":localhost:" + _sPort + " 001 " + content + " :Welcome to IRC " + content + "!";
            servSend(_fds[i].fd, msg);
        }
        else
        {
            msg = ":localhost:" + _sPort + " 001 " + content + " :Registered nickname " + content;
            servSend(_fds[i].fd, msg);
        }
    }
    else
    {
        msg = ":" + _client[i].getNickname() + "!@localhost:" +  " NICK :" + content;
        servSend(_fds[i].fd, msg);
    }
    _client[i].setNickname(content);
}