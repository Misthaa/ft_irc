/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   userToken.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:14:07 by roguigna          #+#    #+#             */
/*   Updated: 2024/10/17 20:07:53 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::userToken(std::string content, int i)
{
    int countWord = 0;

    countWord = std::count(content.begin(), content.end(), ' ') + 1;
    content = content.substr(0, content.find(" "));
    if (countWord < 1)
    {
        sendError(_client[i], "461", "* USER :Not enough parameters");
        return;
    }
    if (_fds[i].fd == -1)
    {
        sendError(_client[i], "461", "* USER :You have not registered");
        return;
    }
    if (content.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]-{}\\^#") != 0)
    {
        sendError(_client[i], "432", "* USER :Erroneous username");
        return;
    }
    for (int j = 1; j < MAX_CLIENT; j++)
    {
        if (_client[i].getUser() == content)
        {
            sendError(_client[i], "462", "Unauthorized command (already registered)");
            return ;
        }
    }
    _client[i].setUser(content);
    std::string msg = "user : " + _client[i].getUser();
    servSend(_fds[i].fd, msg);
}