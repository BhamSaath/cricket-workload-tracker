# Cricket Workload & Injury Management System

A lightweight, zero-dependency C++ command-line application designed for cricket teams. This system provides a local, file-based architecture for coaches and players to track training sessions, manage workloads, assign development plans, and monitor injury recovery times.

Designed with portability in mind, this application requires no external database servers or cryptographic libraries, relying entirely on standard C++ libraries and local JSON data structures.

---

## 1. System Overview

Managing physical workload is critical in modern cricket, particularly for high-impact roles like fast bowling. Over-training leads to stress fractures, while under-training results in poor match readiness.

This application digitizes the tracking process. It establishes a secure, dual-role terminal interface where players can log daily activities and injuries, and coaches can monitor team-wide health and assign structured regimens.

### Technical Philosophy: Zero-Dependency Build

A core design requirement was cross-platform portability without complex build systems (like CMake) or heavy external libraries (like OpenSSL or Bcrypt).

* **Authentication:** Handled via a custom deterministic mathematical hashing algorithm (utilizing bitwise XOR and prime multiplication) to secure credentials locally.
* **Storage:** Handled via flat-file JSON storage (`nlohmann/json`), ensuring data is easily readable, portable, and version-controllable without an SQL server.

---

## 2. Core Features

### Role-Based Access Control

The system initializes with a dual-authentication layer distinguishing between administrative users (Coaches) and standard users (Players).

#### Coach Module

* **Roster Management:** Dynamically add or remove players from the active squad roster.
* **Workload Monitoring:** Access read-only views of individual player training sessions, match logs, and recovery periods.
* **Plan Assignment:** Push structured training regimens (drills, exercises, and target matches) to specific players.
* **Injury Oversight:** Monitor reported injuries, severity levels, and projected return-to-play timelines across the squad.

#### Player Module

* **Role Specialization:** Player profiles are strictly typed via Enums (Fast Bowler, Spinner, Batsman, Wicket Keeper, Fast All-Rounder, Spin All-Rounder) to contextualize workload data.
* **Session Logging:** Input daily activity, categorized by `SessionType` (Training, Match, Recovery), alongside duration metrics and qualitative notes.
* **Injury Reporting:** Log physical issues using a standardized severity index (Mild, Moderate, Severe) and input expected recovery windows.
* **Plan Retrieval:** View assigned tactical and physical training regimens set by the coaching staff.

---

## 3. Technical Architecture

The application is built using Object-Oriented C++14, relying heavily on inheritance and localized namespaces.

### Class Structure

* **`User` (Base Class):** Handles shared attributes (`username`, `email`, `role`) and authentication logic.
* **`Coach` (Derived):** Extends `User`. Contains `std::vector<Player::Player>` to maintain state of the assigned squad. Methods focus on squad iteration and file parsing.
* **`Player` (Derived):** Extends `User`. Maintains discrete vectors for `Session` and `Injury` objects, and a `Plan` struct for current assignments.

### Data Persistence Model

State is maintained via file I/O operations triggered automatically upon any state mutation (e.g., adding a session, removing a player). Data is serialized to `[username]_data.json` files.

*Example Player Schema:*

```json
{
    "username": "j_anderson",
    "role": "player",
    "position": 0,
    "age": 24,
    "sessions": [
        {
            "date": "2023-10-12",
            "duration": "120 mins",
            "type": 0,
            "notes": "Net session, focused on outswing."
        }
    ],
    "injuries": []
}

```

### Custom Hashing Implementation

To avoid linking errors associated with missing local cryptographic libraries, the application uses an internal hashing loop for password verification. The algorithm initiates with a prime seed (`2166136261U`), processes the password string via bitwise XOR operations against each character, and multiplies by a secondary prime (`16777619U`) to ensure deterministic, irreversible hex string outputs.

---

## 4. Installation & Build Instructions

### Prerequisites

* A C++ compiler supporting the C++14 standard (`g++` or `clang++`).
* macOS, Linux, or WSL (Windows Subsystem for Linux) terminal environment.

### Source Code Compilation

1. Clone the repository to your local machine.
2. Ensure `json.hpp` is present in the root directory alongside the source files.
3. Open your terminal, navigate to the project directory, and execute the following compiler command:

```bash
clang++ -std=c++14 main.cpp auth.cpp Player.cpp Coach.cpp User.cpp -o cricket

```

*Note: The `-o cricket` flag designates the compiled executable name. No external linker flags (e.g., `-lssl`) are required.*

### Execution

Run the compiled binary directly from the terminal:

```bash
./cricket

```

---

## 5. Usage Walkthrough

1. **System Boot:** Upon running `./cricket`, you are prompted to either Register or Login.
2. **Registration:** Provide a username, password, email, and select your role. The system will securely hash the password and append the credentials to `credentials.txt`.
3. **Data Initialization:** * If logging in as a new Player, the system instantiates a `Player` object and prompts for age and specific cricket role, generating your initial JSON profile.
* If logging in as a Coach, you are granted access to the squad management terminal to begin parsing existing player files into your roster.


4. **Operations:** Use the numerical menu system to interact with the objects (e.g., press `1` to Add Session, press `2` to View Assigned Plan). All changes trigger a `saveToJson()` event, safely writing the state to disk before exiting.

---

## 6. Future Development Roadmap

Workload Metrics (ACWR): Implement an automated formula to calculate the Acute-to-Chronic Workload Ratio (ACWR). By comparing a player’s short-term (7-day) workload against their long-term (28-day) average, the system can flag over-training risks before injuries occur.

Concurrent AI Insights Integration: Transition the system's analytical engine to leverage external Large Language Model (LLM) APIs asynchronously.

Architecture: Implement a multi-threaded or asynchronous connection pool (asyncio/httpx paradigm) to concurrently pass batch data packets (player workloads, injury logs, and positions) to an AI endpoint.

Delivery: Generate parallel, real-time automated coaching tips, specialized drills, and custom recovery schedules without blocking the core application UI thread or exceeding token-per-minute (TPM) rate limits.

Data Visualization Interface: Export local JSON datasets to a lightweight frontend or plotting script to render rolling 4-week workload charts, keeping a clear visual record of squad fatigue.

Strict Input Sanitization: Expand std::cin validation hooks across the terminal menus to handle unexpected data types gracefully, eliminating edge-case terminal loops when users enter strings into numerical fields.
