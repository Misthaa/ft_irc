/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:07:16 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/15 19:33:25 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

Server::Server()
{
	_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	std::cout << "Server socket: " << _serverSocket << std::endl;
}

Server::~Server()
{
	close(_serverSocket);
	std::cout << "Server socket closed" << std::endl;
}

void Server::setPort(char *port)
{
	std::string str = port;
	if (port == NULL)
		throw std::invalid_argument("Port is NULL");
	else if (std::atoi(port) == 0)
		throw std::invalid_argument("Port is not a number");
	else if (str.length() > 5 && str.length() < 4)
		throw std::invalid_argument("Port must be between 4 and 5 characters");
	else if (std::atoi(port) < 1024)
		throw std::invalid_argument("Port is too low, must be between 1024 and 65535");
	else if (std::atoi(port) > 65535)
		throw std::invalid_argument("Port is too high, must be between 1024 and 65535");
	else
	{
		_port = std::atoi(port);
		_sPort = port;
	}
	
}

void Server::setPassword(std::string password)
{
	if (password.empty())
		throw std::invalid_argument("Password is empty");
	else if (password.size() < 4)
		throw std::invalid_argument("Password is too short, must be between 4 and 16 characters");
	else if (password.size() > 16)
		throw std::invalid_argument("Password is too long, must be between 4 and 16 characters");
	else
		_password = password;
}

void Server::start(char **av)
{
	struct sockaddr_in serverAddr;

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(std::atoi(av[1]));
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	if (bind(_serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
	{
		close(_serverSocket);
		throw std::runtime_error("Bind failed");
	}
	if (listen(_serverSocket, MAX_CLIENT) < 0)\
	{
		close(_serverSocket);
		throw std::runtime_error("Listen failed");
	}
	fcntl(_serverSocket, F_SETFL, O_NONBLOCK);
	for (int i = 0; i < MAX_CLIENT; i++)
	{
		_fds[i].fd = -1;
		_fds[i].events = 0;
		_fds[i].revents = 0;
		_client[i].setNickname("");
		_client[i].setUser("");
		_client[i].setClientSocket(-1);
	}
	setPort(av[1]);
	setPassword(av[2]);
}

void Server::readData(char *BUFF, int i)
{
	std::string buff = BUFF;
	std::string line;
	std::string token;
	std::string content;
	
	while (BUFF[0])
	{
		if (buff.find("\n") == std::string::npos)
			line = buff.substr(0, buff.length());
		else    
			line = buff.substr(0, buff.find("\n"));
		if (line.find('\r') != std::string::npos)
			line = line.substr(0, line.find('\r')) + line.substr(line.find('\r') + 1);
		token = line.substr(0, line.find(" "));
		content = line.substr(line.find(" ") + 1);
		std::cout << "Line: " << line << std::endl;
		std::cout << "Token: " << token << std::endl;
		std::cout << "Content: " << content << std::endl;
		if (token == "NICK")
		{
			nickToken(content, i);
		}
		if (token == "USER")
		{
			userToken(content, i);
		}
		if (token == "PRIVMSG")
		{
			prvMessageToken(content, i);
		}
		if (token == "JOIN")
		{
			joinToken(content, i);
		}
		if (token == "INVITE")
		{
			inviteToken(content, i);
		}
		if (token == "TOPIC")
		{
			topicToken(content, i);
		}
        if (token == "KICK")
        {
            kickToken(content, i);
        }
		buff = buff.substr(buff.find('\n') + 1);
		if (buff.find('\n') == std::string::npos)
			break ;
	}
}

void Server::sendError(Client& client, std::string errorCode,std::string errorMsg) {
	std::string msg;

	msg = ":localhost:" + _sPort + " " + errorCode + " " + client.getNickname() + " " + errorMsg;
	std::cout << msg << std::endl;
	servSend(client.getClientSocket(), msg);
}

void Server::servSend(int fd, std::string msg) {
	msg += "\r\n";
	std::cout << fd << std::endl;
	send(fd, msg.c_str(), msg.size(), MSG_NOSIGNAL | MSG_DONTWAIT);
}

void Server::newClient()
{
	std::cout << "New client is here!" << std::endl;
	int client = accept(_serverSocket, NULL, NULL);
	for (int i = 1; i < MAX_CLIENT; i++)
	{
		if (_fds[i].fd == -1)
		{
			_fds[i].fd = client;
			_fds[i].events = POLLIN;
			_client[i].setClientSocket(client);
			return;
		}
	}
}

int Server::acceptClient()
{
	_fds[0].revents = 0;
	_fds[0].events = POLLIN;
	_fds[0].fd = _serverSocket;

	int i = 1;
	if (poll(_fds, MAX_CLIENT, 100) <= 0)
		return 1;
	if (_fds[0].revents & POLLIN)
		newClient();
	while (i < MAX_CLIENT)
	{
		if (_fds[i].revents & POLLIN)
		{
			int msg = recv(_fds[i].fd, BUFF[i], 1024, 0);
			if (msg <= 0)
			{
				int clientSocket = _client[i].getClientSocket();
				close(clientSocket);
				_client[i].setNickname("");
				_client[i].setUser("");
				_fds[i].revents = 0;
				_fds[i].fd = -1;
				_client[i].setClientSocket(-1);
				return (1);
			}
			BUFF[i][msg - 1] = '\0';
			std::string token = BUFF[i];
			std::string content = BUFF[i];
			if (_client[i].getNickname() == "")
				std::cout << "CLIENT " << i << " : " << BUFF[i] << std::endl;
			else
				std::cout << _client[i].getNickname() << " : " << BUFF[i] << std::endl;
			token = token.substr(0, token.find(" "));
			content = content.substr(content.find(" ") + 1);
			// readData(token, content, i);
			readData(BUFF[i], i);
		}
		i++;
	}
	return 0;
}
