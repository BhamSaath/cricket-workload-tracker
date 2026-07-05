# Cricket Workload Tracker

A terminal based C++ application that tracks cricket player workloads and injury history. Coaches manage rosters and monitor training progress. Players log their own training data and injury reports.

## What It Provides

The system offers a complete workload management solution with two main user roles. Coaches oversee multiple players and adjust training plans. Players track their sessions, report injuries, and view personalized training programs.

The tool runs entirely in the terminal with a clean command line interface. Users authenticate using secure password hashing before accessing their dashboard.

## Key Features

**Player Dashboard**
Players can log training sessions with dates, duration, and session type (training, match, or recovery). Detailed notes accompany each session. Injuries get reported with severity levels and recovery time estimates. Training plans display in dedicated sections. Complete session and injury history saves in one place.

**Coach Dashboard**
Coaches monitor all players on their roster in real time. Individual player details, session history, and training plans appear on demand. Training programs get created and modified for each player. Players can be removed from the roster when needed.

**Secure Authentication**
The system requires a username and password to access. Passwords get hashed using bcrypt before storage. The application prevents duplicate usernames during account creation.

**Data Persistence**
Data saves to JSON files automatically. Player and coach information persists between sessions. All training records and injury reports remain safe in the local database.

## Getting Started

### Requirements

A C++ compiler supporting C++11 or later is required. The project includes the nlohmann JSON library for data handling. Bcrypt hashing happens through included cryptographic headers.

### Installation

Clone the repository:

```bash
git clone https://github.com/bhamsaath/cricket-workload-tracker.git
cd cricket-workload-tracker
```

Compile the program:

```bash
g++ main.cpp Player.cpp Coach.cpp User.cpp auth.cpp bcrypt.cpp blowfish.cpp -o cricket-tracker
```

Run the executable:

```bash
./cricket-tracker
```

## How It Works

### For Players

The program starts with a login or account creation screen. New players enter their name, age, and position (Fast Bowler, Spinner, Batsman, Wicket Keeper, or All Rounder).

The player dashboard provides these options:
* Add new training sessions by date and type
* Log session notes for future reference
* Report injuries when they occur
* View training plans
* Check all previous sessions and injuries
* See the player profile

### For Coaches

Coaches create an account and select their role during signup. The system assigns a coach ID automatically.

The coach dashboard includes:
* Complete details for any player
* Session history for performance tracking
* Existing training plans for review
* New training plan creation with exercises, drills, and matches
* Plan modification for individual players
* Player roster removal

### Authentication Process

During login, the system checks the username and password against stored credentials. The bcrypt hashing algorithm verifies passwords securely. Invalid credentials produce an error message. Successful authentication redirects users to their role specific dashboard.

## Project Structure

**Main Components**

Player.h and Player.cpp define the player class with methods to add sessions, report injuries, and manage training plans.

Coach.h and Coach.cpp handle coach functionality including roster management and player plan updates.

User.h and User.cpp provide the base user class that both players and coaches inherit from.

auth.h and auth.cpp manage user authentication and credential verification.

bcrypt.h, bcrypt.cpp, and blowfish.cpp implement secure password hashing using the bcrypt algorithm.

main.cpp contains the terminal interface and menu system for both user roles.

**Data Storage**

The program uses JSON files for data persistence. Player data stores in individual JSON files by username. Coach roster information saves similarly for persistence across sessions.

**Security Implementation**

Passwords never save in plain text. The bcrypt algorithm hashes passwords with a salt before storage. The system prevents username collisions during account creation. Authentication compares hashed passwords during login attempts.

## File Formats

### Player JSON Structure

The application stores player data including name, age, position, training sessions, injuries, and current training plan. Each session records the date, duration, type, and notes. Injuries track type, severity level, recovery time, and description.

### Coach JSON Structure

Coach files contain name, coach ID, and a list of managed players. Player information links to individual player JSON files by username.

## Usage Examples

**Creating a Player Account**

1. Run the program
2. Select "Create Account"
3. Enter a username
4. Create a password
5. Select "player" as the role
6. Provide name, age, and playing position
7. Access the player dashboard

**Adding a Training Session**

1. From the player dashboard, select "Add Sessions"
2. Enter the date in YYYY-MM-DD format
3. Specify duration (example: 2 hours)
4. Choose session type (0 for training, 1 for match, 2 for recovery)
5. Add session notes
6. Session saves automatically

**Managing Player Plans as a Coach**

1. Log in with a coach account
2. From the dashboard, select "Manage Player Plan"
3. Choose the player to work with
4. Enter plan name and description
5. Add exercises, drills, and match schedules
6. The plan updates and saves for that player

## Known Limitations

The application runs only in terminal environments. Sessions cannot be modified or deleted (only added). Player and coach data store locally without cloud backup. Injury severity levels are fixed as Mild, Moderate, and Severe. All input happens through text commands in the terminal.

## Future Enhancements

AI integration can provide real time training suggestions. Export functionality will allow reports to be saved as PDFs. Advanced analytics can show workload trends over time. A web based interface could replace the terminal system. Mobile app support would improve accessibility.

## Technology Stack

C++ handles all core logic and data structures. The nlohmann JSON library manages data serialization and storage. Bcrypt provides cryptographic password hashing. The blowfish cipher backs the bcrypt implementation.

## License

This project uses the MIT License. The code can be used, modified, and distributed freely with proper attribution.

## Contributing

Bug reports and feature requests can be submitted through GitHub issues. Pull requests go through review before merging. Existing code style should be followed when contributing.

## Support

The Known Limitations section addresses common issues. GitHub issues contain questions and solutions. The code includes detailed comments explaining key functions. Ensure the compiler version supports C++11 features.

## About This Project

This terminal application provides coaches and players with a simple tool for managing training workloads. The project demonstrates secure authentication, data persistence with JSON, and object oriented design in C++. Bcrypt implementation represents the most complex element, handling cryptographic hashing safely and efficiently.
