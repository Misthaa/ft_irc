/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:07:16 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/23 16:51:26 by roguigna         ###   ########.fr       */
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
		_buff[i] = "";
	}
	setPort(av[1]);
	setPassword(av[2]);
}

int Server::isClientExist(std::string nickname)
{
	for (int i = 1; i < MAX_CLIENT; i++)
	{
		if (_client[i].getNickname() == nickname)
			return i;
	}
	return 0;
}

bool Server::checkIsClient(int i)
{
	if (_client[i].getNickname() == "")
	{
		sendError(_client[i], "451", "* :You have not registered");
		return false;
	}
	if (_client[i].getUser() == "")
	{
		sendError(_client[i], "451", "* :You have not registered");
		return false;
	}
	if (_client[i].getCorrectPassword() == false)
	{
		sendError(_client[i], "451", "* :You have not registered");
		return false;
	}
	return true;
	
}

void Server::readData(std::string *BUFF, int i)
{
	std::string buff;
	std::string line;
	std::string token;
	std::string content;
	int 	indexContent;
	
	buff = normalizeSpaces(*BUFF);
	
	std::cout << "3'----------------\n" << buff << "----------------5'" << std::endl;
	if (buff.find("\n") == std::string::npos)
		return ;
	else
		*BUFF = "";
	while (buff[0])
	{
		if (buff.find("\n") == std::string::npos)
			line = buff.substr(0, buff.length());
		else    
			line = buff.substr(0, buff.find("\n"));
		if (line.find('\r') != std::string::npos)
			line = line.substr(0, line.find('\r')) + line.substr(line.find('\r') + 1);
		token = line.substr(0, line.find(" "));
		indexContent = line.find(" ");
		if (indexContent == -1)
			content = "";
		else
			content = line.substr(line.find(" ") + 1);
		std::cout << "Token: " << token << " --> Content: " << content << std::endl;
		if (token == "NICK")
			nickToken(content, i);
		else if (token == "USER")
			userToken(content, i);
		else if (token == "QUIT")
			quitToken(content, i);
		else if (token == "PASS")
			passToken(content, i);
		else if (token == "CAP" || token == "PING" || token == "PONG" || token == "WHO")
			 ;
		else if (checkIsClient(i))
		{
			if (token == "PRIVMSG")
				prvMessageToken(content, i);
			else if (token == "JOIN")
				joinToken(content, i);
			else if (token == "INVITE")
				inviteToken(content, i);
			else if (token == "TOPIC")
				topicToken(content, i);
			else if (token == "KICK")
				kickToken(content, i);
			else if (token == "PART")
				partToken(content, i);
			else if (token == "MODE")
				modeToken(content, i);
			else
			{
				std::string msg = ":localhost:" + _sPort + " 421 " + _client[i].getNickname() + " :Unknown command";
				servSend(_fds[i].fd, msg);
			}
		}
		if (buff.find('\n') == std::string::npos)
			break ;
		buff = buff.substr(buff.find('\n') + 1);
	}
}

void Server::sendError(Client& client, std::string errorCode,std::string errorMsg) {
	std::string msg;

	msg = ":localhost:" + _sPort + " " + errorCode + " " + client.getNickname() + " " + errorMsg;
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
	char BUFF[SIZE_MSG];
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
			int msg = recv(_fds[i].fd, BUFF, SIZE_MSG - 1, 0);
			std::cout << "msg : " << msg << std::endl;
			if (msg <= 0)
			{
				int clientSocket = _client[i].getClientSocket();
				close(clientSocket);
				_client[i].setNickname("");
				_client[i].setUser("");
				_buff[i] = "";
				_fds[i].revents = 0;
				_fds[i].fd = -1;
				_client[i].setClientSocket(-1);
				return (1);
			}
			BUFF[msg] = '\0';
			_buff[i] += BUFF;
			if (_client[i].getNickname() == "")
				std::cout << "CLIENT " << i << " : " << _buff[i] << std::endl;
			else
				std::cout << _client[i].getNickname() << " : " << _buff[i] << std::endl;
			readData(&_buff[i], i);
			BUFF[0] = '\0';
		}
		i++;
	}
	return 0;
}
