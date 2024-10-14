/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:22:03 by roguigna          #+#    #+#             */
/*   Updated: 2024/10/14 14:21:04 by roguigna         ###   ########.fr       */
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

Channel::~Channel()
{
}