# Cricket Workload Tracker

🌟 Highlights
- Terminal-Based C++ Cricket Player Workload Tracker
- Made for Managers and Players to log in to save their sessions
- Managers can add and remove players from their roster and also manage each player's plans
- Players can view, edit, and record their sessions and injuries while following the plans set by their coaches
- The data is stored in JSON files, one per user, to reconstruct the user (Player or Coach) upon login and store away upon logout
- The password is stored in a Hashed method provided by the Bcrypt implementation in the program
etc.
ℹ️ Overview
I built a terminal-based C++ application to track cricket players' workloads and injury history for coaches managing a roster and players logging their own training data. The class structure is based on an inheritance hierarchy: a User base holding shared identity between Player and Coach, like username, email, and role, with Player and Coach classes built on top of it. Players can track sessions and injuries and view their training plan managed by the Coach. Coaches manage a roster of Player accounts and can assign or update plans directly. The element of the project I spent the most time on is user authentication. To hash the password, I used an open-source C++ implementation of the Bcrypt hashing algorithm, which helped ensure the security of the user's data. I also kept the user's password verification separate from the user's data. To implement data persistence, I use one JSON file per account with nlohmann/json, so logging out and back in and reconstructing a user works. Despite my foundational knowledge of C++ at the beginning of this project, I was able to gain experience building a product end-to-end and navigating the challenges along the way by using the resources I had access to. Overall, this project has taught me the difference between coding and architecting a project with real-world use cases, while giving me experience with industry-standard tools like Bcrypt and JSON.


✍️ Authors
Saathwik Bhamidipaty

🚀 Usage
<img width="2880" height="2118" alt="cricket_tracker_terminal_demo" src="https://github.com/user-attachments/assets/391bc2ef-3626-4f71-b138-57f1d0af00a1" />


⬇️ Installation
Clone the repository and run the code below in your terminal.
No external libraries need to be installed. json.hpp and the bcrypt/Blowfish source files are vendored directly in the repository, so this builds identically on macOS, Linux, or WSL with nothing but a C++14-capable compiler.
``` 
git clone https://github.com/BhamSaath/cricket-workload-tracker
cd cricket-workload-tracker
g++ -std=c++14 main.cpp auth.cpp Player.cpp Coach.cpp User.cpp bcrypt.cpp blowfish.cpp -o cricket
./cricket
```
