/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madegryc <madegryc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:22:03 by roguigna          #+#    #+#             */
/*   Updated: 2024/10/16 17:14:14 by madegryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "channel.hpp"

Channel::Channel()
{
	_channelName = "";
	_channelPassword = "";
	_channelTopic = "";
}

void Channel::start(std::string channelName, std::string channelPassword, Client &client)
{
	_channelName = channelName;
	_channelPassword = channelPassword;
	// _channelClient[client] = true;
	(void)client;
	_channelClient.insert(std::pair<Client&, bool>(client, true));
	std::cout << "Channel " << _channelName << " created" << std::endl;
}

void Channel::addClient(Client &client)
{
	if (isClientInChannel(client) == true)
		return ;
	_channelClient.insert(std::pair<Client&, bool>(client, true));
	std::cout << "Client " << client.getNickname() << " joined channel " << _channelName << std::endl;
}

void Channel::removeClient(Client &client)
{
	std::map<Client&, bool>::iterator it = _channelClient.begin();
	while (it != _channelClient.end())
	{
		if (it->first.getNickname() == client.getNickname())
		{
			_channelClient.erase(it);
			return ;
		}
		it++;
	}
}

int Channel::isOperator(Client &client)
{
	std::map<Client&, bool>::iterator it = _channelClient.begin();
	while (it != _channelClient.end())
	{
		if (it->first == client)
			break;
		it++;
	}
	if (it == _channelClient.end())
		return 0;
	if (it->second == true)
		return 1;
	return 0;
}

void Channel::addInviteList(std::string *channelInviteList)
{
	for (int i = 0; i < 100; i++)
	{
		if (channelInviteList[i] == "")
			_channelInviteList[i] = channelInviteList[i];
		break;
	}
}

bool Channel::isClientInChannel(Client &client)
{
    for (std::map<Client&, bool>::iterator it = _channelClient.begin(); it != _channelClient.end(); it++)
    {
        if (it->first.getNickname() == client.getNickname())
            return true;
    }
    return false;
}

void Channel::sendChannelMsg(std::string msg, std::string nickname)
{
	std::map<Client&, bool>::iterator it = _channelClient.begin();
	std::string sendMsg;
	while (it != _channelClient.end())
	{
		sendMsg = _channelName + " " + nickname + " : " + msg;
		sendMsg += "\n\r";
		send(it->first.getClientSocket(), sendMsg.c_str(), sendMsg.size(), MSG_NOSIGNAL | MSG_DONTWAIT);
		it++;
	}	
}

Channel::~Channel()
{
	_channelClient.clear();
}