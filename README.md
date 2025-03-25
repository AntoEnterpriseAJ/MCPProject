# MCPProject 🐧❄️

## Game Overview

MCPProject is a multiplayer battle game developed in C++ that reimagines the classic Battle City concept with a playful penguin-themed twist. Players control penguin characters battling across a destructible map, using icicles as projectiles and strategic power-ups to outmaneuver their opponents.

## 🎮 Game Mechanics

### Players
- Players are represented by penguins
- Each player starts with 100 HP
- Players have 3 respawn opportunities
- Player who eliminates another player receives 100 points

### Map Elements
Three types of blocks:
1. **Brick Blocks**: Destructible after 3 hits
2. **Unbreakable Blocks**: Permanent, cannot be destroyed
3. **Bush Blocks**: Allows players to pass through

## 🚀 Power-Ups

### Special Keybinds
- **Key 1 - Damage Boost** (200 points)
  - Reduces kill requirement from 4 to 3 hits
- **Key 2 - Cooldown Reduction** (400 points)
  - Decreases shooting cooldown

### Random Map Power-Ups
1. **Heal Power-Up**: Restores player health to 100
2. **Speed Power-Up**: Increases player movement speed

## 🏆 Scoring System

### Win Condition
- Last penguin standing wins!

### Score Point Distribution
- 4 Players:
  - 1st Place: 3 points
  - 2nd Place: 2 points
  - 3rd Place: 1 point
  - 4th Place: 0 points

- 3 Players:
  - 1st Place: 2 points
  - 2nd Place: 1 point
  - 3rd Place: 0 points

- 2 Players:
  - 1st Place: 1 point
  - 2nd Place: 0 points

## 💾 User Management
- Player accounts stored in database
- Tracks:
  - Username
  - Password
  - Cumulative Score Points

## 🌐 Multiplayer
- Client-Server architecture
- Supports multiple concurrent players

## 🛠 Tech Stack
- Language: C++
- Networking: Client-Server Model
- Database: SQLite

## 🤝 Contributing
- **Jeleriu Antonio Emanuel**
- **Moroianu Madalin-Andrei**
- **Ghiujan Costin-Daniel**
- **Gelegram Alexandru**
