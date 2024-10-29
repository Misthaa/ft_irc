/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madegryc <madegryc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:20:39 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/29 15:02:46 by madegryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <string>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <cstdlib>

class Client
{
	public:
		Client();
		~Client();
		
		void start(char **av);
		void closeClient();
		
		const std::string &getNickname() const{ return _nickname; }
		const std::string &getUser() const { return _user; }
		std::string	&getUser() { return _user; }
		int  getClientSocket() const {return _clientSocket; }
		bool getCorrectPassword() const { return _correctPassword; }
		void setNickname(std::string nickname) { _nickname = nickname; }
		void setUser(std::string user) { _user = user; }
		void setClientSocket(int client) { _clientSocket = client; }
		void setCorrectPassword(bool correctPassword) { _correctPassword = correctPassword; }
	
		bool operator==(const Client &c) const { return _clientSocket == c.getClientSocket(); }
		bool operator!=(const Client &c) const { return _clientSocket != c.getClientSocket(); }
		bool operator<(const Client &c) const { return _clientSocket < c.getClientSocket(); }
		bool operator>(const Client &c) const { return _clientSocket > c.getClientSocket(); }
		
	private:
		int			_clientSocket;
		bool		_correctPassword;
		std::string	_nickname;
		std::string	_user;
};

#endif