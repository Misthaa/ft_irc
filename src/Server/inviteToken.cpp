/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inviteToken.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madegryc <madegryc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:26:27 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/15 16:25:04 by madegryc         ###   ########.fr       */
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
                    std::map<Client&, bool>::iterator it = _channel[k].getChannelClient().find(_client[i]);
                    if (it != _channel[k].getChannelClient().end())
                    {
                        sendError(_client[i], "403", "* INVITE :You're already on this channel");
                        return ;
                    }
                    // _channel[k].addClient(_client[i]);
                    // if (_channel[k].isOperator(_client[i]) == 0)
                    // {
                    //     sendError(_client[i], "403", "* INVITE :You're not operator of this channel");
                    //     return ;
                    // }
                    _channel[k].addInviteList(&content);
                    std::string msg = "You have been invited to channel " + channelName;
                    servSend(_fds[j].fd, msg);
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