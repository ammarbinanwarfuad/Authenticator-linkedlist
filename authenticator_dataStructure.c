#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// User structure
struct User {
    char username[100];
    char password[100];
    struct User* friends; // Linked list to store friends
    struct User* next;    // Pointer to the next user in the linked list
};

// Global variables
struct User* userList = NULL; // Head of the linked list
struct User* currentUser = NULL;

// Function prototypes
void menu();
void signUp();
void signIn();
void exitProgram();

void userMenu();
void addFriend();
void displayFriend();
void deleteFriend();
void searchUser();
void updateUserData();
void viewAllUsers();

// Function to display the main menu
void menu() {
    int choice;

    while (1) {
        printf("\n*****Login Authentication SYSTEM*****\n");
        printf("1. Sign Up\n");
        printf("2. Sign In\n");
        printf("3. Exit\n\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                signUp();
                break;
            case 2:
                signIn();
                break;
            case 3:
                exitProgram();
                break;
            default:
                printf("Invalid choice\n");
        }
    }
}

// Function to handle user sign up
void signUp() {
    struct User* newUser = (struct User*)malloc(sizeof(struct User));

    printf("Enter username: ");
    scanf("%s", newUser->username);

    printf("Enter password: ");
    scanf("%s", newUser->password);

    newUser->friends = NULL; // Initialize friends linked list
    newUser->next = NULL;    // Initialize next pointer

    // Add user to the linked list
    if (userList == NULL) {
        userList = newUser;
    } else {
        struct User* temp = userList;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newUser;
    }

    printf("User signed up successfully!\n");
}

// Function to handle user sign in
void signIn() {
    char username[100], password[100];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    // Validate credentials
    struct User* temp = userList;
    while (temp != NULL) {
        if (strcmp(temp->username, username) == 0 && strcmp(temp->password, password) == 0) {
            currentUser = temp;
            printf("Login successful!\n");
            userMenu(); // Call user-specific menu
            return;
        }
        temp = temp->next;
    }

    printf("Invalid username or password!\n");
}

// Function to handle program exit
void exitProgram() {
    // Free allocated memory for the user list before exiting
    struct User* temp;
    while (userList != NULL) {
        temp = userList;
        userList = userList->next;
        free(temp);
    }
    exit(0);
}

// Function to handle user-specific menu after login
void userMenu() {
    int choice;

    while (1) {
        printf("\n*****USER MENU*****\n");
        printf("1. Add Friend\n");
        printf("2. Display Friends\n");
        printf("3. Delete Friend\n");
        printf("4. Search User\n");
        printf("5. Update User Data\n");
        printf("6. View All Users\n");
        printf("7. Logout\n\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addFriend();
                break;
            case 2:
                displayFriend();
                break;
            case 3:
                deleteFriend();
                break;
            case 4:
                searchUser();
                break;
            case 5:
                updateUserData();
                break;
            case 6:
                viewAllUsers();
                break;
            case 7:
                currentUser = NULL; // Logout the current user
                return;
            default:
                printf("Invalid choice\n");
        }
    }
}

// Function to add a user as a friend
void addFriend() {
    char friendUsername[100];
    printf("Enter username to add as a friend: ");
    scanf("%s", friendUsername);

    struct User* temp = userList;

    while (temp != NULL) {
        if (strcmp(temp->username, friendUsername) == 0) {
            // Checking if the user is not adding itself as a friend
            if (temp != currentUser) {
                struct User* newFriend = (struct User*)malloc(sizeof(struct User));
                strcpy(newFriend->username, temp->username);
                newFriend->next = currentUser->friends;
                currentUser->friends = newFriend;
                printf("Friend added successfully!\n");
                return;
            } else {
                printf("Cannot add yourself as a friend!\n");
                return;
            }
        }
        temp = temp->next;
    }

    printf("User not found!\n");
}

// Function to display a user's friends
void displayFriend() {
    struct User* temp = currentUser->friends;

    printf("\n*****FRIEND LIST*****\n");

    while (temp != NULL) {
        printf("Username: %s\n", temp->username);
        temp = temp->next;
    }
}

// Function to delete a friend from the user's friend list
void deleteFriend() {
    char friendUsername[100];
    printf("Enter username to delete from friends: ");
    scanf("%s", friendUsername);

    struct User* temp = currentUser->friends;
    struct User* prev = NULL;

    while (temp != NULL) {
        if (strcmp(temp->username, friendUsername) == 0) {
            if (prev != NULL) {
                prev->next = temp->next;
            } else {
                currentUser->friends = temp->next;
            }
            free(temp);
            printf("Friend deleted successfully!\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    printf("Friend not found!\n");
}

// Function to search for a user by username
void searchUser() {
    char friendUsername[100];
    printf("Enter username to search: ");
    scanf("%s", friendUsername);

    struct User* temp = userList;

    while (temp != NULL) {
        if (strcmp(temp->username, friendUsername) == 0) {
            printf("Username: %s\n", temp->username);
            return;
        }
        temp = temp->next;
    }

    printf("User not found!\n");
}

// Function to update user data (username or password)
void updateUserData() {
    int choice;
    printf("1. Update username\n");
    printf("2. Update password\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter new username: ");
            scanf("%s", currentUser->username);
            printf("Username updated successfully!\n");
            break;
        case 2:
            printf("Enter new password: ");
            scanf("%s", currentUser->password);
            printf("Password updated successfully!\n");
            break;
        default:
            printf("Invalid choice!\n");
    }
}

// Function to view details of all users in the system
void viewAllUsers() {
    struct User* temp = userList;

    printf("\n*****ALL USERS*****\n");

    while (temp != NULL) {
        printf("Username: %s\n", temp->username);
        // Add any other details you want to display
        temp = temp->next;
    }
}

int main() {
    menu(); // Start the main menu
    return 0;
}
