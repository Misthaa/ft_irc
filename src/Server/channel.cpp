/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:22:03 by roguigna          #+#    #+#             */
/*   Updated: 2024/10/14 15:20:48 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "channel.hpp"

Channel::Channel()
{
	_channelName = "";
	_channelPassword = "";
	_channelTopic = "";
}

void Channel::start(std::string channelName, std::string channelPassword, Client client)
{
	_channelName = channelName;
	_channelPassword = channelPassword;
	_channelClient[client] = true;
}

void Channel::addClient(Client client)
{
	std::map<Client, bool>::iterator it = _channelClient.find(client);
	if (it != _channelClient.end())
		return ;
	_channelClient[client] = false;
}

void Channel::removeClient(Client client)
{
	std::map<Client, bool>::iterator it = _channelClient.find(client);
	if (it == _channelClient.end())
		return ;
	_channelClient.erase(it);
}

void Channel::sendChannelMsg(std::string msg)
{
	std::map<Client, bool>::iterator it = _channelClient.begin();
	while (it != _channelClient.end())
	{
		send(it->first.getClientSocket(), msg.c_str(), msg.size(), MSG_NOSIGNAL | MSG_DONTWAIT);
		it++;
	}
}

Channel::~Channel()
{
	_channelClient.clear();
}