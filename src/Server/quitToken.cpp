/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quitToken.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madegryc <madegryc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:02:56 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/16 21:54:43 by madegryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::quitToken(std::string content, int i)
{
    (void)content;
    for (int j = 0; j < MAX_CHANNEL; j++)
    {
        if (_channel[j].isClientInChannel(_client[i]) == true)
        {
            _channel[j].removeClient(_client[i]);
        }
    }
    close(_fds[i].fd);
    _fds[i].fd = -1;
    _client[i].setNickname("");
    _client[i].setUser("");
    _client[i].setClientSocket(-1);
    return ;
}