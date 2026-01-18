# Social Network in C

A console-based social networking application built from scratch in pure C, implementing fundamental data structures and algorithms.

## 🎯 Overview

This project is a fully functional social network that demonstrates practical implementation of core computer science concepts including data structures, algorithms, memory management, and file I/O operations.

**Project Duration:** ~5 months  
**Lines of Code:** ~1500+  
**Language:** C (C99 standard)

## ✨ Features

### User Management
- **User Registration** with secure password validation
  - Minimum 14 characters
  - Must contain: uppercase, lowercase, digits, special characters (#, _, ?)
- **Login/Logout** system with authentication
- **User Search** with O(1) average time complexity (Hash Table)

### Social Features
- **Friend System**
  - Add/remove friends (bidirectional relationships)
  - View friends list
  - Friend network visualization (DFS traversal)
- **Posts**
  - Create text posts
  - View own posts (chronologically sorted)
  - View friends' posts
- **Messaging**
  - Send messages to other users
  - Message inbox with FIFO queue
  - Read and delete messages
- **Profile History**
  - Track viewed profiles
  - Navigate back through history (Stack-based)

### Data Persistence
- **Save to files:** All user data, friendships, posts, and messages
- **Load from files:** Automatic data restoration on startup
- **File formats:** Plain text with pipe-delimited fields

## 🏗️ Technical Architecture

### Data Structures Implemented

| Structure | Usage | Time Complexity |
|-----------|-------|-----------------|
| **Hash Table** | User lookup by username | O(1) average |
| **Linked List** | Friends list for each user | O(n) |
| **Binary Search Tree** | Posts sorted by timestamp | O(log n) average |
| **Stack** | Profile browsing history | O(1) |
| **Queue** | Message inbox (FIFO) | O(1) |

### Key Algorithms
- **DFS (Depth-First Search):** Network visualization (multi-level friend connections)
- **BST Traversal:** In-order and reverse in-order for post display
- **Hash Function:** djb2 algorithm for username hashing
- **Collision Resolution:** Chaining with linked lists

## 📁 File Structure
```
social_network/
├── main.c                 # Main program file (~1500 lines)
├── users.txt             # User data storage
├── friends.txt           # Friendship relationships
├── posts.txt             # All user posts
└── README.md             # This file
```

## 🔧 Technologies & Concepts

### Memory Management
- Dynamic memory allocation (`malloc`, `realloc`, `free`)
- Proper memory cleanup (no memory leaks)
- Pointer manipulation (multi-level pointers)

### Advanced C Concepts
- Struct composition and relationships
- Function pointers
- Recursion (BST operations, DFS)
- File I/O operations
- String parsing (`strtok`, `sscanf`)
- Time handling (`time.h`)

## 🚀 Getting Started

### Prerequisites
- C compiler (GCC, Clang, or MSVC)
- Standard C library

### Compilation

**Using GCC:**
```bash
gcc main.c -o social_network
```

**Using MSVC:**
```bash
cl main.c
```

### Running
```bash
./social_network
```

## 📖 Usage

### Main Menu
```
=== SOCIAL NETWORK ===
[1] Register
[2] Login
[3] Find user
[0] Exit
```

### After Login
```
Logged in as: @username (ID: 1)

[4] Logout
[5] Add friend
[6] Show friends
[8] Create Post
[9] My Posts
[10] Friend's Posts
[11] View profile
[12] Back (History)
[13] Delete history
[14] Send Message
[15] Inbox
[16] Read Message
```

## 🎓 Learning Outcomes

Through this project, I gained hands-on experience with:

- ✅ **Data Structures:** Practical implementation of Hash Tables, Linked Lists, Trees, Stacks, and Queues
- ✅ **Memory Management:** Manual allocation, reallocation, and deallocation
- ✅ **Algorithms:** Search, traversal, and sorting algorithms
- ✅ **Pointer Mastery:** Multi-level pointers, pointer arithmetic, function pointers
- ✅ **Recursion:** Tree traversals and graph algorithms
- ✅ **File I/O:** Data persistence and serialization
- ✅ **Software Design:** Modular code organization and separation of concerns

## 🐛 Known Limitations

- Single-user session (no concurrent users)
- Console-based UI only
- Limited input validation for bio/email fields with special characters
- No encryption for passwords (stored in plain text)
- File-based storage (no database)

## 🔮 Future Enhancements

- [ ] BFS algorithm for shortest path between users
- [ ] Friend recommendations (friends of friends)
- [ ] Post likes and comments
- [ ] Graph visualization of social network
- [ ] Encrypted password storage
- [ ] Multi-threaded support
- [ ] Migration to C++ with STL

## 📊 Project Statistics

- **Total Functions:** 30+
- **Lines of Code:** ~1500
- **Data Structures:** 8 custom types
- **Algorithms:** 5+ (DFS, BST operations, Hash table, etc.)
- **Time Complexity:** O(1) to O(n log n) depending on operation

## 👨‍💻 Author

**Student:** 1st Year  
**Major:** Computational Intelligence and Smart Systems  
**Institution:** [Your University]  
**Contact:** [Your Email]

## 📝 License

This project was created for educational purposes as part of a Data Structures and Algorithms course.

## 🙏 Acknowledgments

Special thanks to my mentor for guidance on:
- Data structure selection and implementation
- Algorithm optimization techniques
- Best practices in C programming
- Code review and debugging strategies

---

**Note:** This project represents approximately 5 months of learning and development, progressing from basic C concepts to advanced data structure implementation.
