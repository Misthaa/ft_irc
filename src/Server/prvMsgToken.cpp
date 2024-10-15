/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prvMsgToken.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:28:33 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/15 13:58:27 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::channelMessage(std::string content, int i)
{
    std::string channelName;
    std::string message;

    channelName = content.substr(0, content.find(" "));
    message = content.substr(content.find(" ") + 1);
    std::cout << "channelName : " << channelName << std::endl;
    for (int j = 0; j < MAX_CHANNEL; j++)
    {
        if (channelName == _channel[j].getChannelName())
        {
	        // std::map<Client&, bool>::iterator it =  _channel[j].getChannelClient().find(_client[i]);
            std::map<Client&, bool>::iterator it = _channel[j].getChannelClient().begin();
            while (it != _channel[j].getChannelClient().end())
            {
                if (it->first.getNickname() == _client[i].getNickname())
                {
                    std::string msg = _client[i].getNickname() + " je susi la : " + message;
                    _channel[j].sendChannelMsg(message);
                    return ;
                }
            }
            sendError(_client[i], "403", "* PRIVMSG :You're not on this channel");
            return ;
        }   
    }
    sendError(_client[i], "403", "* PRIVMSG :No such channel");
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