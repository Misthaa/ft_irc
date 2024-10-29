/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:05:21 by roguigna          #+#    #+#             */
/*   Updated: 2024/10/29 15:56:20 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>
# include <map>
# include "client.hpp"

# define MAX_CLIENT 100

class Channel
{
	public:
		Channel();
		~Channel();

		void start(std::string channelName, std::string channelPassword, Client &channelClient);
		void addClient(Client &client);
		void removeClient(Client &client);
		void clear();
		void sendChannelMsg(std::string msg, std::string nickname);
		void sendToAll(std::string msg);
		void setChannelTopic(std::string channelTopic) { _channelTopic = channelTopic; };
		std::string getChannelTopic() { return _channelTopic; };
		bool isClientInChannel(Client &client);
		bool isInvited(std::string nickname);
		void deleteInviteList(std::string nickname);
		bool isEmptyChan();


		std::string getChannelName() { return _channelName; }
		std::string getChannelPassword() { return _channelPassword; }
		std::string *getInviteList() { return _channelInviteList; }
		std::map<Client &, bool> &getChannelClient() { return _channelClient; }
		void setChannelName(std::string channelName) { _channelName = channelName; }
		void setChannelPassword(std::string channelPassword) { _channelPassword = channelPassword; }
		void addInviteList(std::string channelInviteList);
		int isOperator(Client &client);
		int getUserLimit() { return _userLimit; }
		void setUserLimit(int userLimit) { _userLimit = userLimit; }
		void setOperator(Client &client, bool op);
		void setChangeTopic(bool changeTopic) { _changeTopic = changeTopic; }
		bool getChangeTopic() { return _changeTopic; }
		void setChannelOnInvite(bool channelOnInvite) { _channelOnInvite = channelOnInvite; }
		bool getChannelOnInvite() { return _channelOnInvite; }
		
	private:
		int			_userLimit;
		bool		_changeTopic;
		bool		_channelOnInvite;
		std::string _channelName;
		std::string _channelPassword;
		std::string _channelTopic;
		std::string	_channelInviteList[MAX_CLIENT];
		std::map<Client &, bool> _channelClient;
};

#endif