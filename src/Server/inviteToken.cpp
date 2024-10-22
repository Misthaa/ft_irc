/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inviteToken.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:26:27 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/22 10:50:08 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::inviteToken(std::string content, int i)
{
    std::string nickname;
    std::string channelName;

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
                    std::map<Client&, bool>::iterator it = _channel[k].getChannelClient().find(_client[j]);
                    if (it != _channel[k].getChannelClient().end())
                    {
                        sendError(_client[i], "403", "* INVITE :You're already on this channel");
                        return ;
                    }
                    _channel[k].addInviteList(nickname);
                    std::string msg = ":" + _client[i].getNickname() + " INVITE " + nickname + " " +  + " " + channelName + "\n";
                    servSend(_fds[j].fd, msg);
                    servSend(_fds[i].fd, msg);
                    return ;
                }
            }
            sendError(_client[i], "403", "* INVITE :No such channel");
            return ;
        }
    }
    sendError(_client[i], "403", "* INVITE :No such nickname");
    return ;
}