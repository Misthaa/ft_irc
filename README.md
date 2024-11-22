# `ft_irc`

## 📋 Description
**`ft_irc`** est un projet basé sur les spécifications du protocole **IRC (Internet Relay Chat)**. L'objectif est de créer un serveur IRC capable de gérer les connexions multiples, les canaux de discussion, les commandes d'administration, ainsi que la communication entre clients, en respectant les standards du protocole.

Ce projet a été développé dans le cadre de l'école **42**, avec pour but d'acquérir une compréhension approfondie des protocoles réseaux et des sockets en C++.

## 🚀 Fonctionnalités
- **Connexion simultanée** de plusieurs clients.
- **Gestion des canaux** (création, suppression, rejoindre/partir).
- **Authentification utilisateur** (mots de passe).
- **Commandes IRC standard** : `/nick`, `/join`, `/part`, `/topic`, `/kick`, `/mode`, etc.
- **Communication privée** entre utilisateurs via `/PRIVMSG`.
- **Notifications d'événements** (entrée/sortie d'un canal, changement de pseudo).

- **Bonus** : Bot pour jouer au juste prix (Sur des vetements new waves)

## 🛠️ Technologies utilisées
- **Langage** : C++
- **Bibliothèques** : sockets Unix pour les communications réseau.
- **Protocoles** : Implémentation conforme au protocole **IRC** RFC/HexChat.

## 📦 Installation

### Prérequis
Assure-toi d'avoir installé les éléments suivants :
- Un compilateur **C++ (c++)**
- Un environnement Unix/Linux (testé sur Ubuntu/Debian)
- **Make**

### Instructions
Clone le dépôt du projet et compile-le avec `make` :
```bash
git clone https://github.com/Misthaa/ft_irc ft_irc
cd ft_irc
make
```

## 🏃 Usage
Pour lancer le serveur, exécute la commande suivante :
```bash
./ircserv <port> <password>
```

- **port** : Le port sur lequel le serveur écoute (par exemple, `6667`).
- **password** : Mot de passe pour se connecter au serveur.

### Exemple
```bash
./ircserv 6667 monmotdepasse
```

Ensuite, connecte-toi au serveur avec un client IRC comme **Netcat** ou HexChat :
```bash
nc localhost 6667
```

## 🧪 Tests
Pour tester les différentes fonctionnalités :
1. Lance le serveur.
2. Utilise plusieurs clients IRC pour tester les commandes (via terminaux séparés).
3. Essaie les commandes comme `/nick`, `/join`, `/msg`, `/part`, etc.

## 📝 Commandes supportées
Voici les commandes implémentées :
| Commande     | Description                          |
|--------------|--------------------------------------|
| `NICK`       | Changer de pseudo                    |
| `USER`       | Changer de user                      |
| `PASS`       | Appliquer le mot de passe du serveur |
| `QUIT`       | Supprimer l'utilisateur              |
| `JOIN`       | Créer/Rejoindre un channel           |
| `PRIVMSG`    | Envoyer un message privée            |
| `PRIVMSG #`  | Envoyer un message dans un channel   |
| `INVITE`     | Inviter quelau'un dans un channel    |
| `TOPIC`      | Afficher/Changer le topic            |
| `KICK`       | Enlever l'utilisateur d'un channel   |
| `PART`       | Quitter un channel                   |
| `MODE`       | Utilisable par un modérateur de chan |
| `MODE i`     | Mettre le channel sur invitation     |
| `MODE l`     | Changer la limite de user du channel |
| `MODE o`     | Ajouter/Enlever un modérateur        |
| `MODE k`     | Mettre/Enlever un password de chan   |
| `MODE t`     | Changer restrcition changement topic |

## Bonus

Pour les bonus demandé de IRC, il fallait :

- **Fonctionnement d'envoi de fichier**
- **Bot fonctionnel**

Pour faire fonctionner le bot :

```
make bonus
./bot <name> <port> <password>
PRIVMSG bot PLAY
```

## 🤝 Autheurs
- **Mathis, madegryc**
- **Romain, roguigna**
