# DeadWell - A Repairable Well System for DayZ

DeadWell is a lightweight and immersive server-side mod for DayZ that introduces a new mechanic: wells can now break, be repaired, and even transmit cholera if not maintained. Designed to add depth to survival gameplay, this mod makes players think twice before relying on wells as an unlimited water source.

---

## Features

- **Broken Wells**: All wells start broken by default (configurable).
- **Repair System**: Players can repair wells using a tool. Once repaired, the well works for a set time before breaking again.
- **Tool Damage**: Repairing a well damages (or destroys) the tool used.
- **Cholera Transmission**: Drinking from a broken well can give players cholera (chance configurable).
- **Persistent System**: Well states persist across server restarts using JSON configuration.
- **Dynamic Messaging**: Players are informed when trying to use or repair a well via custom messages.

---

## Configuration

The mod stores its configuration in:

ServerProfile/DeadWell/DeadWellConfig.json

### Config Fields

| Field | Description |
|-------|-------------|
| `wellsDisabledDefault` | If `true`, all wells start broken unless otherwise defined. |
| `toolDamage` | Amount of damage done to the tool when fixing a well. `100` = destroyed. |
| `timeUntilBrokenAgain` | Time in seconds before a well becomes broken again (e.g. `7200` = 2 hours). |
| `enableWellTransferCholera` | If `true`, cholera can be transmitted via broken wells. |
| `choleraChance` | Chance (0–100) of contracting cholera when drinking from a broken well. |
| `messageCantDrink` | Message shown when a player tries to drink from a broken well. |
| `messageFixed` | Message shown when a player successfully repairs a well. |
| `RepairableWells` | List of saved well locations with their repair state and timestamps. |

---

## Server Installation

1. Place the mod folder in your DayZ server's `@YourMods` directory.
2. Add the mod to your server launch parameters:

-mod=@DeadWell

3. Run the server once to generate the default configuration file at:

4. Adjust the configuration to suit your needs.
5. Restart the server.

---

## How It Works

- On server start, each well loads its state from `DeadWellConfig.json`.
- If no config is found or the version is outdated, a new config is generated.
- Players trying to drink from a broken well will be blocked and shown a warning message.
- Players can repair wells using tools (tool handling logic is handled in your own action script).
- Repaired wells function for a configurable amount of time before breaking again.
- If cholera is enabled and a player drinks from a broken well, they have a chance to become infected.

---

## Future Enhancements (Suggestions)

- Custom UI prompt or context action to repair wells.
- Admin debug commands for setting well states.
- Optional logs or stats on well usage.
- Expanded diseases (not just cholera).

---

## Credits

Created by **[CostaGeoDev]**  
Tested on DayZ SA Dedicated Server (1.24+)

---

## License

This project is free to use and modify for DayZ server communities. Please credit the original author if redistributing.

---