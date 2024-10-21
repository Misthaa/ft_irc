/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topicToken.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:54:28 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/21 10:25:21 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::topicToken(std::string content, int i)
{
    std::string channelName;
    std::string topic;

    channelName = content.substr(0, content.find(" "));
    topic = content.substr(content.find(" ") + 1);
    for (int j = 0; j < MAX_CHANNEL; j++)
    {
        if (channelName == _channel[j].getChannelName())
        {
            if (_channel[j].isOperator(_client[i]) == 0)
            {
                sendError(_client[i], "482", "* TOPIC :You're not operator of this channel");
                return ;
            }
            _channel[j].setChannelTopic(topic);
            std::string msg = ":localhost TOPIC " + channelName + " " + topic + "\n";
            _channel[j].sendToAll(msg);
            return ;
        }
    }
    sendError(_client[i], "403", "* TOPIC :No such channel");
    return ;
}