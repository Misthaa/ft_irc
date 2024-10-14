/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prvMsgToken.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madegryc <madegryc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:28:33 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/14 16:41:30 by madegryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::channelMessage(std::string content, int i)
{
    (void)content;
    (void)i;
    // std::string channelName;
    // std::string message;

    // channelName = content.substr(0, content.find(" "));
    // message = content.substr(content.find(" ") + 1);
    // for (int j = 1; j < MAX_CLIENT; j++)
    // {
    //     if (_client[j].getChannel() == channelName)
    //     {
    //         std::string msg = _client[i].getNickname() + " : " + message;
    //         servSend(_fds[j].fd, msg);
    //     }
    // }
    return ;
}

void Server::prvMessage(std::string content, int i)
{
    std::string nickname;
    std::string message;

    nickname = content.substr(0, content.find(" "));
    message = content.substr(content.find(" ") + 1);
    for (int j = 1; j < MAX_CLIENT; j++)
    {
        if (_client[j].getNickname() == nickname)
        {
            std::string msg = _client[i].getNickname() + " : " + message;
            servSend(_fds[j].fd, msg);
            return ;
        }
    }
    sendError(_client[i], "401", "* PRIVMSG :No such nickname");
}

void Server::prvMessageToken(std::string content, int i)
{
    if (content[0] == '#')
        channelMessage(content, i);
    else
        prvMessage(content, i);
}