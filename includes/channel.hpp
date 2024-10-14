/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:05:21 by roguigna          #+#    #+#             */
/*   Updated: 2024/10/14 13:56:42 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>
# include <map>
# include "client.hpp"

class Channel
{
	public:
		Channel();
		~Channel();

		void start(std::string channelName, std::string channelPassword, Client channelClient);
		void addClient(Client client);
		std::string getChannelName() { return _channelName; }
		std::string getChannelPassword() { return _channelPassword; }
		void setChannelName(std::string channelName) { _channelName = channelName; }
		void setChannelPassword(std::string channelPassword) { _channelPassword = channelPassword; }
		
	private:
		std::string _channelName;
		std::string _channelPassword;
		std::string _channelTopic;
		std::string _channelInviteList[100];
		std::map<Client, bool> _channelClient;
};

#endif