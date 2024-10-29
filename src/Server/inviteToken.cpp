/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inviteToken.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:26:27 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/29 20:27:25 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::inviteToken(std::string content, int i)
{
    std::string nickname;
    std::string channelName;
    std::string msg;

    nickname = content.substr(0, content.find(" "));
    channelName = content.substr(content.find(" ") + 1);
    for (int j = 1; j < MAX_CLIENT; j++)
    {
        if (_client[j].getNickname() == nickname)
        {
            for (int k = 0; k < MAX_CHANNEL; k++)
            {
                if (_channel[k].getChannelName() == channelName)
                {
                    if (_channel[k].isClientInChannel(_client[i]) == false)
                    {
                        msg = ":localhost 442 " + _client[i].getNickname() + " " + channelName + " :You're not on this channel\n";
                        servSend(_fds[i].fd, msg);
                        return ;
                    }
                    if (_channel[k].getChannelOnInvite() == true && _channel[k].isOperator(_client[i]) == 0)
                    {
                        msg = ":localhost 482 " + _client[i].getNickname() + " " + channelName + " * INVITE :You must be operator to invite someone on this channel\n";
                        servSend(_fds[i].fd, msg);
                        return ;
                    }
                    std::map<Client&, bool>::iterator it = _channel[k].getChannelClient().find(_client[j]);
                    if (it != _channel[k].getChannelClient().end())
                    {
                        msg = ":localhost 443 " + nickname + " " + channelName + " :is already on channel\n";
                        servSend(_fds[i].fd, msg);
                        return ;
                    }
                    _channel[k].addInviteList(nickname);
                    msg = ":" + _client[i].getNickname() + " INVITE " + nickname + " " +  + " " + channelName;
                    servSend(_fds[j].fd, msg);
                    servSend(_fds[i].fd, msg);
                    return ;
                }
            }
            sendError(_client[i], "403", "IRCserv: INVITE :No such channel");
            return ;
        }
    }
    sendError(_client[i], "403", "IRCserv: INVITE :No such nickname");
    return ;
}