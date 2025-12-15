## Project Rumble ⚔️
---
![alt text](https://img.shields.io/badge/Unreal_Engine-5.6+-black?style=for-the-badge&logo=unrealengine)
![alt text](https://img.shields.io/badge/Language-C++-blue?style=for-the-badge&logo=cplusplus)
![alt text](https://img.shields.io/badge/Architecture-Server_Authoritative-red?style=for-the-badge)
![alt text](https://img.shields.io/badge/Pattern-Data_Driven-green?style=for-the-badge)

A 2-Player Co-op Action-Roguelike built with Unreal Engine 5.

This project serves as a technical showcase for advanced C++ gameplay programming, server-authoritative replication, and scalable data-driven architecture.

---
## 🎥 Gameplay Showcase

[![IMAGE ALT TEXT](http://img.youtube.com/vi/-zTRvWn5Gs4/maxresdefault.jpg)](http://www.youtube.com/watch?v=-zTRvWn5Gs4 "Video Title")
### Video Highlights:
- Lobby System & Synchronization (Ready Check).
- Server-Authoritative Combat & Shared XP.
- Synchronized Level-Up: Demonstrating the Global Pause system where the game waits for both players to make a selection.
- Ranged AI Behavior & Physics-based Projectiles.
---
## 🛠️ Technical Highlights

Unlike typical blueprint-heavy projects, Project Rumble relies on C++ for 95% of its core logic (Networking, AI, Physics, Stats), using Blueprints mostly and strictly for UI and Visual composition.
### 1. Multiplayer Architecture & Replication
Designed a robust Server-Authoritative framework to handle high-intensity co-op gameplay without desynchronization.
Synchronized State Management: Implemented a custom GameState to handle Shared XP and Difficulty Scaling. When one player collects XP, it is distributed to the entire team, promoting cooperative play.
Race-Condition Safe UI: Solved critical initialization timing issues in multiplayer using a Delegate-driven architecture. Clients wait for OnRep_PlayerState and OnStatsComponentReady signals before binding HUD elements, preventing null-pointer crashes on join.
Optimized Network Traffic: To reduce bandwidth in a bullet-hell scenario, visual feedback (Damage Numbers, Hit Sounds) utilizes Client RPCs targeting only the instigator, rather than expensive NetMulticast broadcasts.
### 2. Advanced AI System (C++ & Behavior Trees)
The AI system is built to handle hundreds of active units while maintaining performance.
Custom BT Services: Wrote efficient C++ services (FindNearestPlayer) that iterate through the GameState player array rather than using expensive GetAllActorsOfClass calls.
Spatial Optimization: Utilized custom Collision Channels to filter overlap queries at the physics engine level, avoiding costly Blueprint loops for target selection.
Ballistic Projectiles: Implemented Ranged AI (Cactus) using SuggestProjectileVelocity to calculate physics-based mortar trajectories that dynamically adjust to the player's distance.
### 3. Scalable Data-Driven Design
The game logic is decoupled from hard-coded values, allowing designers to balance the game via Data Tables without touching code.
Stat System via GameplayTags: Constructed a flexible Stat Component that handles Health, Damage, Luck, and Cooldowns using GameplayTags. This allows for modular stat modifiers (e.g., "+10% Fire Damage" items).
Dynamic Difficulty: Enemy stats (Health, Speed, Damage) are read from a Data Table and scaled at runtime based on a global DifficultyMultiplier, which increases over time and per player count.
### 4. Mathematical Algorithms
Exponential Luck Curve: Designed a custom RollForRarity algorithm using Exponential Decay.
Logic: As the player's Luck stat increases, the weight of "Common" items decreases exponentially, shifting probability to "Legendary" tiers. This creates a satisfying progression curve for late-game builds.
---
## 💻 Code Snippets

### A. Dynamic Rarity Calculation (Math & Algorithms)

Here is the core logic for the Luck system. It dynamically adjusts probability weights based on the player's stats to determine loot rarity.
code

```cpp
EUpgradeRarity UPRRewardManager::RollForRarity(float PlayerLuck) const
{
    // Scale Luck (e.g. 1000% -> 10.0f)
    const float ScaledLuck = PlayerLuck / 100.0f; 
    
    // 1. Exponential Decay: Shrink the weight of Common items
    // Formula: BaseWeight * e^(-DecayRate * Luck)
    float CurrentW_C = W_C_BASE * FMath::Exp(-K_COMMON * ScaledLuck);
    
    // 2. Calculate the "Shifted" weight 
    float TotalShiftAmount = (W_C_BASE - CurrentW_C);

    // 3. Conditional Boost: Break the curve for high-luck builds
    if (ScaledLuck >= LEGENDARY_BOOST_THRESHOLD)
    {
        float OverThresholdLuck = ScaledLuck - LEGENDARY_BOOST_THRESHOLD;
        // Apply linear bonus to Legendary weight for "Game Breaking" feel
        W_L_GAIN += OverThresholdLuck * 0.50f; 
    }

    // ... (Weighted Random Selection follows)
}
```
### B. Safe Multiplayer Initialization (Networking)

Handling execution order in multiplayer is critical. This pattern ensures Client UI never accesses null data during the connection phase.

```cpp
void APRCharacterBase::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();

    // The PlayerState has arrived on the Client.
    // We can now safely initialize the character and bind UI delegates.
    InitializeCharacter();
    
    // Force a UI refresh to sync visual bars with replicate data immediately
    if (UPRStatsComponent* Stats = GetStatsComponent())
    {
        Stats->ForceUpdateUI();
    }
}
```
---
## 🚀 Roadmap & Future Improvements

- [x] **Core Loop:** Combat, Leveling, Upgrades, Enemy Waves.
- [x] **Multiplayer:** Lobby, Host/Join, Replication.
- [ ] **Online Subsystem:** Integrate Steam/EOS for invite-based matchmaking (Architecture is currently ready via `IOnlineSessionInterface`).
- [ ] **Optimization:** Implement **Object Pooling** for projectiles and enemies to reduce Garbage Collection overhead.
- [ ] **Persistence:** Save/Load system for meta-progression (Gold/Unlocks).

---

- **Engine:** Unreal Engine 5.4
- **Language:** C++
- **Developer:** Enes [Soyadınız]

> **Note:** *This project is part of my professional portfolio demonstrating Full Networked Gameplay Programming capabilities.*
