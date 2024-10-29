/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quitToken.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:02:56 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/29 21:53:09 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::quitToken(int i)
{
    for (int j = 0; j < MAX_CHANNEL; j++)
    {
        if (_channel[j].isClientInChannel(_client[i]) == true)
            _channel[j].removeClient(_client[i], "quit");
    }
    _client[i].closeClient();
    _fds[i].fd = -1;
    _fds[i].events = 0;
    _fds[i].revents = 0;
    return ;
}