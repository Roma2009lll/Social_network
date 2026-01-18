#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
struct FriendNode {
    struct User* user;
    struct FriendNode* next;

};
struct User {
    int id;
    int age;
    char username[50];
    char email[50];
    char bio[200];
    char password[20];
    struct FriendNode* friends;
    int friends_count;
    struct Post* posts;
    int posts_count;
    struct MassegeQueue* messege;



};

struct HashNode {
    struct User* user;
    struct HashNode* next;

};
struct Post {
    int post_id;
    char content[500];
    time_t timestamp;
    int likes;
    struct Post* left;
    struct Post* right;

};

struct HistoryNode {
    struct User* user;
    struct HistoryNode* next;

};
struct Message {
    int id;
    struct User* send;
    struct User* keep;
    char text[200];
    time_t timestamp;
    int read;
    struct Message* next;

};
struct MassegeQueue {
    struct Message* rear;
    struct Message* front;
    int count;

};





struct User* users = NULL;
int user_count = 0;
struct User* current_user = NULL;
struct HashNode* hash_table[100];
int next_post_id = 1;
struct HistoryNode* history_stack = NULL;
int next_message_id = 0;
int pasword_cheak(const char* pasword);
int hash(unsigned char* str);
void show_menu(void);
void register_user(void);
void hash_insert(struct User* user);
struct HashNode* hash_search(const char* name);
void login_user();
void logout();
void add_post(void);
void show_posts(void);
void show_friend_posts(void);
struct Post* insert_to_tree(struct Post* root, struct Post* new_post);
void print_posts(struct Post* root);
void push_history(struct User* user);
struct User* pop();
void go_back();
void show_history();
void delete_history();
void send_massege();
void show_masseges();
void read_massege();









int pasword_cheak(const char* pasword) {


    if (strlen(pasword) == 0 || strlen(pasword) < 14) {
        return 0;

    }
    int is = 0;
    char* p00 = strchr(pasword, '#');
    char* p01 = strchr(pasword, '_');
    char* p02 = strchr(pasword, '?');
    if (p00 != NULL || p01 != NULL || p02 != NULL) {
        is = 1;
    }
    if (is == 0) {
        return 0;

    }


    char* p1 = pasword;
    int lower = 0, higher = 0, digit = 0;
    while (*p1) {
        if (isdigit(*p1)) {
            digit++;

        }
        else if (islower(*p1)) {
            lower++;

        }
        else if (isupper(*p1)) {
            higher++;

        }
        p1++;
    }
    if (lower > 0 && higher > 0 && digit > 0) {
        return 1;

    }
    else {
        return 0;


    }



}
int hash(unsigned char* str) {
    int hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c;

    return hash % 100;
}
void show_menu() {
    printf("\n=== SOCIAL NETWORK ===\n");

    if (current_user != NULL) {
        printf("Logged in as: @%s (ID: %d)\n\n",
            current_user->username, current_user->id);
    }

    printf("[1] Register\n");
    printf("[2] Login\n");

    if (current_user != NULL) {
        printf("[4] Logout\n");
        printf("[5] Add friend\n");
        printf("[6] Show friends\n");
        printf("[8] Create Post\n");        
        printf("[9] My Posts\n"); 
        printf("[10] Friend's Posts\n");
        printf("[11] View profile\n");
        printf("[12] Back\n");
        printf("[13] Delete history\n");
        printf("[14] Send Message\n");
        printf("[15] Inbox\n");
        printf("[16] Read Message\n");
    }

    printf("[3] Find user\n");
    printf("[0] Exit\n");
    printf("Enter choice: ");
}
void register_user() {

    struct User* ptr = realloc(users, (user_count + 1) * sizeof(struct User));
    if (ptr == NULL) {
        printf("Memory allocation filed\n");
        return;

    }
    users = ptr;
    printf("Enter username ");
    gets_s(users[user_count].username, 50);
    if (strlen(ptr->username) == 0) {
        printf("Eror\n");
        return;


    }
    while (1) {
        char temp[20] = "";
        printf("Enter pasword(min 14 symb) ");
        gets_s(temp, 20);
        int true = pasword_cheak(temp);
        if (true == 1) {
            strcpy(users[user_count].password, temp);
            break;
        }
        else {
            printf("Not save pasword\nTry again\n");

        }
    }
    printf("Enter email ");
    gets_s(users[user_count].email, 50);
    printf("Enter your bio\n");
    gets_s(users[user_count].bio, 200);
    users[user_count].id = user_count + 1;
    users[user_count].friends = NULL;
    users[user_count].friends_count = 0;
    users[user_count].posts = NULL;
    users[user_count].posts_count = 0;
    users[user_count].messege=malloc(sizeof(struct MassegeQueue));
    users[user_count].messege->front = NULL;
    users[user_count].messege->rear = NULL;
    users[user_count].messege->count = 0;
    printf("Success! Your ID: %d\n", users[user_count].id);

    user_count++;
    hash_insert(&users[user_count - 1]);
    




}
void hash_insert(struct User* users) {

    int index = hash(users->username);
    struct HashNode* NewNode = (struct HashNode*)malloc(sizeof(struct HashNode));
    NewNode->user = users;
    NewNode->next = hash_table[index];
    hash_table[index] = NewNode;




}
struct HashNode* hash_search(const char* name) {
    int index_f = hash(name);
    struct HashNode* current = hash_table[index_f];
    while (current != NULL) {
        if (strcmp(current->user->username, name) == 0) {
            return current;

        }
        else {
            current = current->next;

        }
    }

    return NULL;






}
void login() {
    char log_name[50] = "";
    
    printf("Enter user name ");
    gets_s(log_name, 50);
    struct HashNode* user_namet = hash_search(log_name);
    if (user_namet == NULL) {
        printf("User not found\n");
        return;

    }
    
    int count = 3;
    while (count > 0) {
        char log_password[20] = "";
        printf("Enter password ");
        gets_s(log_password, 20);
        if (strcmp(user_namet->user->password, log_password) == 0) {
            printf("Access granted\n");
            break;
        }
        else {
            printf("Wrong password\nTry again\n");

        }
        count--;

    }
    if (count == 0) {
        return;
    }
    current_user = user_namet->user;


    
}
void logout() {
    int count = 3;
    while (count > 0) {
        char log_password[20] = "";
        printf("Enter password ");
        gets_s(log_password, 20);
        if (strcmp(current_user->password, log_password) == 0) {
            printf("Access granted\n");
            break;
        }
        else {
            printf("Wrong password\nTry again\n");

        }
        count--;

    }
    if (count == 0) {
        return;
    }
    current_user = NULL;
    

}

void add_friend() {
    char friend_name[50] = "";
    if (current_user == NULL) {
        printf("Login first!\n");
        return;

    }
    printf("Enter friend name ");
    gets_s(friend_name, 50);
    struct HashNode* temp = hash_search(friend_name);
    if (temp == NULL) {
        printf("User not found\n");
        return;

    }

    if (strcmp(friend_name, current_user->username) == 0) {
        printf("You can add yourself\n");
        return;
    }
    struct FriendNode* check = current_user->friends;
    while (check!= NULL) {
        if (strcmp(check->user->username, friend_name) == 0) {
            printf("Already friends\n");
            return;

        }
        check = check->next;


    }
    struct FriendNode* NewFriend = (struct FriendNode*)malloc(sizeof(struct FriendNode));
    NewFriend->user = temp->user;
    NewFriend->next = current_user->friends;
    current_user->friends = NewFriend;
    current_user->friends_count++;

    struct FriendNode* NewFriend2 = (struct FriendNode*)malloc(sizeof(struct FriendNode));
    NewFriend2->user = current_user;
    NewFriend2->next = temp->user->friends;
    temp->user->friends = NewFriend2;
    temp->user->friends_count++;
    printf("You are now friends with %s!", friend_name);

     

}
void show_frinds() {
    if (current_user->friends_count == 0) {
        printf("You have no friends yet :(\n");
        return;
    }

    printf("Your friends (%d):\n", current_user->friends_count);
    struct FriendNode* temp = current_user->friends; 
    while (temp != NULL) {
        printf("- @%s (ID: %d)\n", temp->user->username, temp->user->id);
        temp = temp->next;
    }
   



}
void show_profile();



void add_post() {
    if (current_user == NULL) {
        printf("Login first!\n");
        return;

    }
    char content[500];
    printf("Start typing\n");
    gets_s(content, 500);
    if (strlen(content) == 0) {
        printf("Eror\n");
        return;

    }
    struct Post* NewPost = (struct Post*)malloc(sizeof(struct Post));
    NewPost->post_id = next_post_id++;
    strcpy(NewPost->content, content);
    NewPost->timestamp = time(NULL);
    NewPost->likes = 0;
    NewPost->left = NULL;
    NewPost->right = NULL;
    current_user->posts = insert_to_tree(current_user->posts, NewPost);
    current_user->posts_count++;

}
struct Post* insert_to_tree(struct Post* root, struct Post* NewPost) {
    if (root == NULL) {
        return NewPost; 

    }
    if (NewPost->timestamp > root->timestamp) {
        root->right = insert_to_tree(root->right, NewPost);
    }
    else {
        root->left = insert_to_tree(root->left, NewPost);

    }
    return root;
}
void show_posts() {
    if (current_user == NULL) {
        printf("Login first!\n");
        return;

    }
    if (current_user->posts_count == 0) {
        printf("You have no posts yet\n");
        return;

    }
    printf("\n=== Your Posts (%d) ===\n", current_user->posts_count);
    print_posts(current_user->posts);
}
void print_posts(struct Post* root) {
    if (root == NULL) {
        return;

    }
    print_posts(root->right);
    char time_str[100];
    struct tm* timeinfo = localtime(&root->timestamp);
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", timeinfo);

    printf("\nPost %d %s\n", root->post_id, time_str);
    printf("%s\n", root->content);
    printf(" %d likes\n", root->likes);

    
    print_posts(root->left);



}
void show_friend_posts() {
    char friend_name[50] = "";
    if (current_user == NULL) {
        printf("Login first!\n");
        return;

    }
    printf("Enter friend name ");
    gets_s(friend_name, 50);
    struct HashNode* temp = hash_search(friend_name);
    if (temp == NULL) {
        printf("User not found\n");
        return;

    }
    printf("=== Posts of @%s ===\n", friend_name);
    print_posts(temp->user->posts);


}

void push_history(struct User* user) {
    struct HistoryNode* NewHistory = (struct HistoryNode*)malloc(sizeof(struct HistoryNode));
    NewHistory->user = user;
    NewHistory->next = history_stack;
    history_stack = NewHistory;

   

}
struct User* pop() {
    if (history_stack == NULL) {
        printf("Stack Underflow\n");
        return NULL;

    }
    struct HistoryNode* temp = history_stack;

    struct User* user = temp->user;
    history_stack=history_stack->next;
    free(temp);
    return user;



}
void show_profile() {
    char user_prof[50] = "";
    if (current_user == NULL) {
        printf("Login first!\n");
        return;

    }
    printf("Enter username ");
    gets_s(user_prof, 50);

    struct HashNode* prof = hash_search(user_prof);
    if (prof == NULL) {
        printf("User not found\n");
        return;

    }
    push_history(prof->user);
    printf("Info\n");
    printf("Username %s\n", prof->user->username);
    printf("User id:%d\n", prof->user->id);

    struct FriendNode* temp = current_user->friends;


    while (temp != NULL) {
        if (strcmp(temp->user->username, prof->user->username) == 0) {
            printf("You are friends\n");
            return;

        }
        temp = temp->next;


    }
    printf("You are not friends\n");
    return;




}
void go_back() {
    if (current_user == NULL) {
        printf("Login first!\n");
        return;

    }
    if (history_stack == NULL) {
        printf("Stack is empty\n");
        return;


    }
    struct User* temp = pop();
    if (temp == NULL) {
        printf("No history yet\n");
        return;


    }
    printf("Info\n");
    printf("Username %s\n",temp->username);
    printf("User id:%d\n", temp->id);

    struct FriendNode* tmp = current_user->friends;
    
    while (tmp != NULL) {
        if (strcmp(tmp->user->username, temp->username) == 0) {
            printf("You are friends\n");
            return;
        }
        tmp = tmp->next;

    }




    printf("You are not friends\n");
    return;

  

}
void show_history() {
    if (current_user == NULL) {
        printf("Login first!\n");
        return;

    }
    if (history_stack == NULL) {
        printf("Stack is empty\n");
        return;


    }
    struct HistoryNode* temp = history_stack;
    printf("--- History (Top to Bottom) ---\n");
    while (temp != NULL) {
        printf("Username: %s\n", temp->user->username);
        temp = temp->next;

    }
    printf("-------------------------------\n");
    


}
void delete_history() {
    if (current_user == NULL) {
        printf("Login first!\n");
        return;

    }
    if (history_stack == NULL) {
        printf("Stack is empty\n");
        return;


    }
   
    while (history_stack != NULL) {
        struct HistoryNode* temp = history_stack;
        history_stack = history_stack->next;
        free(temp);

    }
    printf("History cleared!\n");
}

void send_massege() {
    char name_kepp[50] = "";
    char text[256] = "";
    if (current_user == NULL) {
        printf("Login first!\n");
        return;

    }
    printf("Enter username of the kepper\n");
    gets_s(name_kepp, 50);
    struct HashNode* temp = hash_search(name_kepp);
    if (temp == NULL) {
        printf("User not find\n");
        return;

    }
    printf("Enter your massege\n");
    gets_s(text, 256);
    struct Message* NewMessage = (struct Message*)malloc(sizeof(struct Message));
    NewMessage->id = ++next_message_id;
    NewMessage->send = current_user;
    NewMessage->keep = temp->user;
    strcpy(NewMessage->text, text);
    NewMessage->timestamp = time(NULL);
    NewMessage->read = 0;
    NewMessage->next = NULL;

    if (temp->user->messege->rear == NULL) {
        temp->user->messege->rear = NewMessage;
        temp->user->messege->front = NewMessage;
        temp->user->messege->count++;
    }
    else {
        temp->user->messege->rear->next = NewMessage;
        temp->user->messege->rear = NewMessage;
        temp->user->messege->count++;

    }
    printf("Message sent to @%s!", name_kepp);


}
void show_masseges() {
    if (current_user == NULL) {
        printf("Login first!\n");
        return;

    }
    if (current_user->messege->front == NULL) {
        printf("Indox is empty\n");
        return;

    }
    struct Message* temp = current_user->messege->front; 
    while (temp != NULL) {
        printf("%s\n\nSend from %s\n", temp->text,temp->send->username);
        temp = temp->next;

    }



}
void read_massege() {
    if (current_user == NULL) {
        printf("Login first!\n");
        return;

    }
    if (current_user->messege->front == NULL) {
        printf("Indox is empty\n");
        return;

    }
    struct Message* temp = current_user->messege->front;
    current_user->messege->front = current_user->messege->front->next;
    if (current_user->messege->front == NULL) {
        current_user->messege->rear = NULL;

    }
    current_user->messege->front->read=1;
    current_user->messege->count--;
    free(temp);

}


void dfs_helper(struct User* user, int level, int max_level, int visited[]) {
    if (level > max_level) {
        return;

    }
    visited[user->id] = 1;
    for (int i = 0; i < level; i++) {
        printf("  ");

    }
    printf("%s\n", user->username);
    struct FriendNode* temp = user->friends;
    while (temp != NULL) {
        struct User* cur = temp->user;
        if (visited[cur->id] == 0) {
            dfs_helper(cur, level + 1, max_level, visited);

        }
        temp = temp->next;



    }


}
void show_network() {
    if (current_user == NULL) {
        printf("Login first!\n");
        return;

    }
    int max_level;
    printf("How many levels? (1-5): ");
    scanf_s("%d", &max_level);
    int visited[1000] = { 0 };  
    printf("\n=== Your Network (DFS) ===\n");
    dfs_helper(current_user, 0, max_level, visited);
}


void save_users() {
    FILE* fp = fopen("users.txt", "w");
    if (fp == NULL) {
        printf("Error creating file\n");
        return;


    }
    for (int i = 0; i < user_count; i++) {
        fprintf(fp, "%s|%s|%s|%s|%d\n",
            users[i].username,
            users[i].password,
            users[i].email,
            users[i].bio,
            users[i].id);
    }
    fclose(fp);
    printf("Users saved!\n");
}
void load_users() {
    FILE* fp = fopen("users.txt", "r");
    if (fp == NULL) {
        printf("Error creating file\n");
        return;


    }
    char line[1000] = "";
    while (fgets(line, 1000, fp) != NULL) {
        struct User* user= realloc(users, (user_count + 1) * sizeof(struct User));
        users = user;
        char* token = strtok(line, "|");
        strcpy(users[user_count].username, token);
        token = strtok(NULL, "|");
        strcpy(users[user_count].password, token);
        token = strtok(NULL, "|");
        strcpy(users[user_count].email, token);
        token = strtok(NULL, "|");
        strcpy(users[user_count].bio, token);
        token = strtok(NULL, "|");
        user[user_count].id = atoi(token);  
        users[user_count].friends = NULL;
        users[user_count].friends_count = 0;
        users[user_count].posts = NULL;
        users[user_count].posts_count = 0;
        users[user_count].messege = malloc(sizeof(struct MassegeQueue));
        users[user_count].messege->front = NULL;
        users[user_count].messege->rear = NULL;
        users[user_count].messege->count = 0;
        hash_insert(&users[user_count]);

        user_count++;

    }
    fclose(fp);
    printf(" Loaded %d users\n", user_count);

}
void save_friends() {
    FILE* fp = fopen("friends.txt", "w");
    if (fp == NULL) {
        printf("Error creating file\n");
        return;


    }
    for (int i = 0; i < user_count; i++) {
        struct FriendNode* temp = users[i].friends;
        while (temp != NULL) {
            if (users[i].id < temp->user->id) {
                fprintf(fp, "%d|%d\n",
                    users[i].id,
                    temp->user->id);
            }
            temp = temp->next;

        }

        
    }
    fclose(fp);

}
void load_friends() {
    FILE* fp = fopen("friends.txt", "r");
    if (fp == NULL) {
        printf("Error creating file\n");
        return;


    }
    char line[500] = "";
    while (fgets(line, sizeof(line), fp) != NULL) {
        int user_id1, user_id2;
        sscanf(line, "%d|%d", &user_id1, &user_id2);
        struct User* user1 = NULL;
        struct User* user2 = NULL;
        for (int i = 0; i < user_count; i++) {
            if (users[i].id == user_id1) {
                user1 = &users[i];
            }
            if (users[i].id == user_id2) {
                user2 = &users[i];
            }

        }
        if (user1 == NULL || user2 == NULL) continue;


        struct FriendNode* friend1 = (struct FriendNode*)malloc(sizeof(struct FriendNode));
        friend1->user = user2;
        friend1->next = user1->friends;
        user1->friends= friend1;
        user1->friends_count++;




        struct FriendNode* friend2 = (struct FriendNode*)malloc(sizeof(struct FriendNode));
        friend2->user = user1;
        friend2->next = user2->friends;
        user2->friends = friend2;
        user2->friends_count++;

    }
    fclose(fp);




}
void sace_post_help(FILE* fp,struct Post* root,int id) {
    if (root == NULL) {
        return;


    }
    sace_post_help(fp, root->left,id);
    fprintf(fp, "%d|%d|%s|%ld|%d\n",
        root->post_id,
        id,
        root->content,
        (long)root->timestamp,
        root->likes);
    sace_post_help(fp, root->right, id);
}
void save_post_main() {
    FILE* fp = fopen("friends.txt", "w");
    if (fp == NULL) {
        printf("Error creating file\n");
        return;


    }
    for (int i = 0; i < user_count; i++) {
        sace_post_help(fp, users[i].posts, users[i].id);


    }
    fclose(fp);

}
void load_posts() {
    FILE* fp = fopen("posts.txt", "r");
    if (fp == NULL) {
        printf("Error creating file\n");
        return;


    }
    char line[3000] = "";
    while (fgets(line, sizeof(line), fp) != NULL) {
        int post_id, user_id, likes;
        long timestamp;
        char content[500];
        char* token = strtok(line, "|");
        post_id = atoi(token);
        token = strtok(NULL, "|");
        user_id = atoi(token);
        token = strtok(NULL, "|");
        strcpy(content, token);
        token = strtok(NULL, "|");
        timestamp = atol(token);
        token = strtok(NULL, "|");
        likes = atoi(token);
        struct User* user0 = NULL;
        for (int i = 0; i < user_count; i++) {
            if (users[i].id == user_id) {
                user0 = &users[i];

            }

        }
        struct Post* NewPost = (struct Post*)malloc(sizeof(struct Post));
        NewPost->post_id = post_id;
        NewPost->likes = likes;
        NewPost->timestamp = timestamp;
        strcpy(NewPost->content, content);
        NewPost->left = NULL;
        NewPost->right = NULL;
        user0->posts_count++;

    }
    fclose(fp);

}
void load_data() {
    load_users();
    load_friends();
    load_posts();




}

int main() {
    for (int i = 0; i < 100; i++) {
        hash_table[i] = NULL;
    }
    int choice = 0;
    char username[50];
    load_data();

   
    while (1) {
        show_menu();
        scanf_s("%d", &choice);
        getchar();
        switch (choice) {
        case 1:
            register_user();

            break;
        case 2:
            login();
            break;



        case 3:

            printf("Enter username to search: ");
            gets_s(username, 50);

            struct HashNode* found = hash_search(username);
            if (found != NULL) {
                printf("User found!\n");
                printf("ID: %d\n", found->user->id);
                printf("Username: %s\n", found->user->username);
                printf("Email: %s\n", found->user->email);

            }
            else {
                printf("User not found!\n");
            }
            break;

        case 4:
            logout();
            break;
        case 5:
            add_friend();
            break;

        case 6:
            show_frinds();
            break;
        case 8:
            add_post();
            break;

        case 9:
            show_posts();
            break;

        case 10:
            show_friend_posts();
            break;
        case 11:
            show_profile();
            break;
        case 12:
            go_back();
            break;
        case 13:
            delete_history();
            break;
        case 14:
            send_massege();
            break;
        case 15:
            show_masseges();
            break;
        case 16:
            read_massege();
            break;
        case 0:
            save_users();
            save_friends();
            save_post_main();
            return 0;


        }

    }

}
