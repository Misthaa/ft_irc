/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinToken.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:00:02 by roguigna          #+#    #+#             */
/*   Updated: 2024/10/17 20:20:15 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::joinToken(std::string content, int i)
{
    int countWord = 0;
    int existantChannel = 0;
    int channelIndex = 0;
    std::string msg;
    
    countWord = std::count(content.begin(), content.end(), ' ') + 1;
    if (countWord < 1)
    {
        sendError(_client[i], "461", "* JOIN :Not enough parameters");
        return;
    }
    if (_client[i].getNickname() == "" || _client[i].getUser() == "")
    {
        sendError(_client[i], "451", "* JOIN :You have not registered");
        return;
    }
    if (content.find_first_of("#") != 0)
    {
        sendError(_client[i], "461", "* JOIN :Not a channel");
        return;
    }
    while (channelIndex < MAX_CHANNEL)
    {
        if (_channel[channelIndex].getChannelName() == content)
        {
            _channel[channelIndex].addClient(_client[i]);
            msg = ":" + _client[i].getNickname() + "!" + _client[i].getUser() + "@localhost JOIN :" + content + "\n";
            _channel[channelIndex].sendToAll(msg);
            existantChannel = 1;
            break ; 
        }
        channelIndex++;
    }
    if (existantChannel == 0)
    {
        channelIndex = 0;
        while (channelIndex < MAX_CHANNEL)
        {
            if (_channel[channelIndex].getChannelName() == "")
            {
                _channel[channelIndex].start(content, "", _client[i]);
                msg = ":" + _client[i].getNickname() + "!" + _client[i].getUser() + "@localhost JOIN :" + content + "\n";
                _channel[channelIndex].sendToAll(msg);
                break;
            }
            i++;
        }
    }
    msg = ":localhost 353 " + _client[i].getNickname() + " = " + content + " :";
	for (std::map<Client&, bool>::iterator it = _channel[channelIndex].getChannelClient().begin(); it != _channel[channelIndex].getChannelClient().end(); it++)
        msg += it->first.getNickname() + " ";
	msg += "\n";
	msg += ":localhost 366 " + _client[i].getNickname() + " " + _channel[channelIndex].getChannelName() + " :End of /NAMES list\n";
	msg += ":localhost 332 " + _client[i].getNickname() + " " + _channel[channelIndex].getChannelName() + " :" + _channel[channelIndex].getChannelTopic() + "\n";
	_channel[channelIndex].sendToAll(msg);
    // msg = ":" + _client[i].getNickname() + "!" + _client[i].getUser() + "@localhost JOIN :" + content + "\n";
    // _channel[channelIndex].sendToAll(msg);
}