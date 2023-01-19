#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*functions define*/
void executeChoice(int choice,int level);
void viewItems();
void insertItem();
void addCustomer();
void updateItem();
void deleteItem();
void viewCustomers();
void deleteCustomer();
void viewEmployers();
void addEmployer();
void deleteEmployer();
void orderItemsById();
void searchItem();


// Items struct
typedef struct Item {
    int id;
    char name[20];
    float price;
    bool exist;
}Item;

//employer struct
typedef struct Employer
{
    char username[15];
    char password[15];
    int level;
    char fullname[20];
}Employer;

// Define struct for customers
typedef struct Customer {
    int id;
    char name[20];
    char address[20];
    char phone[20];
}Customer;

typedef struct Node {
    Item item;
    struct Node* next;
}Node;


/*========================================READBIN FUNCTION==========================================*/
void readBinFile(char* fileName, void* structType, int structSize) {
    FILE* fp = fopen(fileName, "rb");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    //printf("tyep: %s siezed: %d", fileName);
    while (fread(structType, structSize, 1, fp) != 0) {
        if (fileName == "items.bin") {
            Item* temp = (Item*)structType;
            printf("ID: %d\n", temp->id);
            printf("Name: %s\n", temp->name);
            printf("Price: %.2f\n", temp->price);
            printf("exist: %s\n", temp->exist ? "true" : "false");
        }
        else if (fileName == "employers.bin") {
            Employer* temp = (Employer*)structType;
            printf("Username: %s\n", temp->username);
            printf("Password: %s\n", temp->password);
            printf("Level: %d\n", temp->level);
        }
        else if (fileName == "customers.bin") {
            Customer* temp = (Customer*)structType;
            printf("ID: %d\n", temp->id);
            printf("Name: %s\n", temp->name);
            printf("Address: %s\n", temp->address);
            printf("Phone: %s\n", temp->phone);
        }
        else
        {
            printf("Invalid struct type.\n");
            break;
        }
    }
    printf("End of file.\n");
    fclose(fp);
}

/*========================================END FUNCTION==========================================*/
/*========================================START FUNCTION==========================================*/

void createFiles() {
    // Check if customer file exists, create it if it doesn't
    FILE* fp = fopen("customers.bin", "rb");
    if (fp == NULL) {
        fp = fopen("customers.bin", "wb");
    }
    fclose(fp);

    fp = fopen("items.bin", "rb");
    if (fp == NULL) {
        fp = fopen("items.bin", "wb");
    }
    fclose(fp);

    // Check if employer file exists, create it if it doesn't
    fp = fopen("employers.bin", "rb");
    if (fp == NULL) {
        fp = fopen("employers.bin", "wb");

        // If employer file is empty, add admin username and password
        Employer temp;
        int adminExist = 0;
        while (fread(&temp, sizeof(temp), 1, fp) != 0) {
            if (temp.level == 3) {
                adminExist = 1;
                break;
            }
        }
        if (adminExist == 0) {
            Employer admin;
            strcpy(admin.username, "admin");
            strcpy(admin.password, "admin");
            admin.level = 3;
            fwrite(&admin, sizeof(admin), 1, fp);
        }
    }
    fclose(fp);

}

/*===============================================================================================*/
/*========================================LOGIN FUNCTION==========================================*/

int checkLogin(char* username, char* password) {
    // Open the login details file in binary read mode
    FILE* fp = fopen("employers.bin", "rb");
    //printf("\nwe get: %s,%s\n", username, password);
    // Read the login information from the file
    Employer temp;
    while (fread(&temp, sizeof(temp), 1, fp) != 0) {
        // Check if the entered username and password match the information in the file
        if (strcmp(temp.username, username) == 0 && strcmp(temp.password, password) == 0) {
            // If a match is found, return the level of the manager
            printf("\nlogin success\n");
            return temp.level;
        }
    }
    fclose(fp);
}

/*===============================================================================================*/
/*========================================MENU FUNCTIONS==========================================*/


int menuOptions(int level){
    int choice;
    if (level != -1) {
        printf("Choose your choice:\n");
        if (level == 1) {
            printf("1. View items\n"
                "2. Add new item\n"
                "3. Add new customer\n");
        }
        else if (level == 2) {
            printf("1. View items\n"
                "2. Add new item\n"
                "3. Add new customer\n"
                "4. Update item\n"
                "5. Delete item\n");
        }
        else if (level == 3) {
            printf("1. View items\n"
                "2. Add new item\n"
                "3. Add new customer\n"
                "4. Update item\n"
                "5. Delete item\n"
                "6. View customer\n"
                "7. Update customer\n"
                "8. Delete customer\n"
                "9. view employers\n"
                "10. Add employers\n"
                "11. Delete employers\n"
                "12. Search item\n");
        }
        scanf("%d", &choice);
        executeChoice(choice, level);
        return(choice);
    }
}


void executeChoice(int choice, int level) {
    switch (choice) {
    case 1:
        if (level == 1 || level == 2 || level == 3) {
            printf("choosing viewitem.\n");
            viewItems();
            break;
        }
        else {
            printf("Invalid choice for your authorization level.\n");
            break;
        }
    case 2:
        if (level == 1 || level == 2 || level == 3) {
            printf("choosing inseritem.\n");
            insertItem();
            break;
        }
        else {
            printf("Invalid choice for your authorization level.\n");
            break;
        }
    case 3:
        if (level == 1 || level == 2 || level == 3) {
            printf("choosing addcustomer.\n");
            addCustomer();
            break;
        }
        else {
            printf("Invalid choice for your authorization level.\n");
            break;
        }
    case 4:
        if (level == 2 || level == 3) {
            printf("choosing updateitem.\n");
            updateItem();
            break;
        }
        else {
            printf("Invalid choice for your authorization level.\n");
            break;
        }
    case 5:
        if (level == 2 || level == 3) {
            printf("choosing deleteitem.\n");
            deleteItem();
            break;
        }
        else {
            printf("Invalid choice for your authorization level.\n");
            break;
        }
    case 6:
        if (level == 3) {
            printf("choosing viewcustomer\n");
            viewCustomers();
            break;
        }
        else {
            printf("Invalid choice for your authorization level.\n");
            break;
        }
    case 7:
        if (level == 3) {
            printf("choosing updatecustomer.\n");
            //updateCustomer();
            break;
        }
        else {
            printf("Invalid choice for your authorization level.\n");
            break;
        }
    case 8:
        if (level == 3) {
            printf("choosing delete customer.\n");
            deleteCustomer();
            break;
        }
        else {
            printf("Invalid choice for your authorization level.\n");
            break;
        }
    case 9:
        if (level == 3) {
            printf("choosing view employers.\n");
            viewEmployers();
            break;
        }
        else {
            printf("Invalid choice for your authorization level.\n");
            break;
        }
    case 10:
        if (level == 3) {
            printf("choosing add employer.\n");
            addEmployer();
            break;
        }
        else {
            printf("Invalid choice for your authorization level.\n");
            break;
        }
    case 11:
        if (level == 3) {
            printf("choosing Delete.\n");
            deleteEmployer();
            break;
        }
        else {
            printf("Invalid choice for your authorization level.\n");
            break;
        }
    case 12:
        if (level == 3) {
            printf("choosing Search item.\n");
            searchItem();
            break;
        }
        else {
            printf("Invalid choice for your authorization level.\n");
            break;
        }
    case -1:
    {
        printf("Good bye dear user.\n");
        break;
    }
    default:
        printf("Invalid choice. Please enter a valid choice.\n");
        break;
    }
}

/*========================================ITEMS FUNCTION==========================================*/
// Function to insert items into the itesm file
/*================================================================================================*/

void searchItem() {
    int sid;
    printf("please enter id:");
    scanf("%d", &sid);
    FILE* fp = fopen("items.bin", "rb");

    // Create a head node for the linked list
    Node* head = NULL;
    Node* current = NULL;
    Item item;
    // Sort list by ID
    while (fread(&item, sizeof(item), 1, fp) == 1) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->item = item;
        newNode->next = NULL;

        // Insert the node into the linked list
        if (head == NULL) {
            head = newNode;
        }
        else {
            current = head;
            while (current->next != NULL) {
                if (current->item.id == sid) {
                    printf("Item ID: %d\n", current->item.id);
                    printf("Item name: %s\n", current->item.name);
                    printf("Item price: %f\n", current->item.price);
                    printf("Item exist: %d\n", current->item.exist);
                }
                current = current->next;
            }
            current->next = newNode;
        }
    }

    // Close the file
    fclose(fp);
}

//Function to view items from the items file
void viewItems() {
    // Open the details file in binary read mode
    FILE* fp = fopen("items.bin", "rb");
    // Read and print the item information from the file
    Item temp;
    if (fread(&temp, sizeof(temp), 1, fp) == 0)
        printf("empty project");
    else
        readBinFile("items.bin", &temp, sizeof(temp));
  
    // Close the file
    fclose(fp);
}

void insertItem() {
    // Create an item struct    
    Item item;

    // Get user input for item properties
    printf("Enter item ID: ");
    scanf("%d", &item.id);
    printf("Enter item name: ");
    scanf("%s", item.name);
    printf("Enter item price: ");
    scanf("%f", &item.price);
    printf("Enter item exist (1 for true, 0 for false): ");
    int existStatus;
    scanf("%d", &existStatus);
    item.exist = existStatus ? true : false;

    // Open the details file in binary append mode
    FILE* fp = fopen("items.bin", "ab");
    // Write the item struct to the file
    fwrite(&item, sizeof(item), 1, fp);
    // Close the file
    fclose(fp); 
    orderItemsById();
    //sortItemsById();
}

void orderItemsById() {
    // Create a head node for the linked list
    Node* head = NULL;

    // Open the items file in binary read mode
    FILE* fp = fopen("items.bin", "rb");

    // Read each item from the file
    Item item;
    Node* current = NULL;
    while (fread(&item, sizeof(item), 1, fp) == 1) {
        // Create a new node for the item
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->item = item;
        newNode->next = NULL;

        // Insert the node into the linked list in the correct position
        if (head == NULL || item.id < head->item.id) {
            // Insert at the beginning of the list
            newNode->next = head;
            head = newNode;
        }
        else {
            // Insert after the head
            current = head;
            while (current->next != NULL && current->next->item.id < item.id) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }
    // Close the file to start write into
    //fclose(fp);
    fp = fopen("items.bin", "wb");

    // Iterate through the linked list and write each item to the file
    current = head;
    while (current != NULL) {
        fwrite(&current->item, sizeof(current->item), 1, fp);
        current = current->next;
    }

    // Close the file
    fclose(fp);
}

void updateItem() {
    // Open the original binary file in read mode
    FILE* fp = fopen("items.bin", "rb");
    // Create a new binary file to store the updated information
    FILE* temp = fopen("temp.bin", "wb");

    // Create an item structs
    Item item, updatedItem;
    int id;
    // Get user input for item properties
    printf("Enter item ID to update: ");
    scanf("%d", &updatedItem.id);
    printf("Enter item name: ");
    scanf("%s", updatedItem.name);
    printf("Enter item price: ");
    scanf("%f", &updatedItem.price);
    printf("Enter item exist (1 for true, 0 for false): ");
    int existStatus;
    scanf("%d", &existStatus);
    updatedItem.exist = existStatus ? true : false;
    
    
    while (fread(&item, sizeof(item), 1, fp)) {
        // If the item's ID matches the ID of the item to be updated, write the updated information to the new file
        if (item.id == updatedItem.id) {
            fwrite(&updatedItem, sizeof(updatedItem), 1, temp);
        }
        else {
            // Otherwise, write the original information to the new file
            fwrite(&item, sizeof(item), 1, temp);
        }
    }
    // Close the original and new binary files
    fclose(fp);
    fclose(temp);
    // Delete the original binary file and rename the new file to the original file name
    remove("items.bin");
    rename("temp.bin", "items.bin");
}

void deleteItem() {
    // Open the items binary file in read mode
    FILE* fp = fopen("items.bin", "rb");
    // Create a temporary binary file to store the updated information
    FILE* temp = fopen("temp.bin", "wb");
    // Read the item structs from the file
    Item tempItem;
    int id;
    // Get user input for item properties
    printf("Enter item ID to delete: ");
    scanf("%d", &id);

    while (fread(&tempItem, sizeof(tempItem), 1, fp) == 1) {
        // If the item ID matches the ID of the item to be deleted, skip writing the item to the temporary file
        if (tempItem.id != id) {
            fwrite(&tempItem, sizeof(tempItem), 1, temp);
        }
    }
    // Close the items file and temporary file
    fclose(fp);
    fclose(temp);
    // Delete the original items file and rename the temporary file to the original file name
    remove("items.bin");
    rename("temp.bin", "items.bin");
}

/*========================================Customers Functions==========================================*/
// Function to insert items into the itesm file
/*=====================================================================================================*/

void viewCustomers() {
    // Open the details file in binary read mode
    FILE* fp = fopen("customers.bin", "rb");
    // Read and print the item information from the file
    Customer temp;
    if (fread(&temp, sizeof(temp), 1, fp) == 0)
        printf("empty project");
    else
        readBinFile("customers.bin", &temp, sizeof(temp));

    // Close the file
    fclose(fp);
}

void addCustomer() {
    // Keep track of the last customer ID
    int lastCustomerID = 0;

    Customer customer;
    // Get the last customer ID from the file
    FILE* fp = fopen("customers.bin", "rb");
    while (fread(&customer, sizeof(customer), 1, fp)) {
        if (customer.id > lastCustomerID) {
            lastCustomerID = customer.id;
        }
    }
    // close reading to start write
    fclose(fp);

    // Assign the next customer ID
    customer.id = lastCustomerID + 1;

    printf("Enter customer name: ");
    scanf("%s", customer.name);
    printf("Enter customer address: ");
    scanf("%s", customer.address);
    printf("Enter customer phone number: ");
    scanf("%s", customer.phone);

    // Open the customers file in binary append mode
    fp = fopen("customers.bin", "ab");
    // Write the customer struct to the file
    fwrite(&customer, sizeof(customer), 1, fp);
    // Close the file
    fclose(fp);
}

void deleteCustomer() {
    // Open the items binary file in read mode
    FILE* fp = fopen("customers.bin", "rb");
    // Create a temporary binary file to store the updated information
    FILE* temp = fopen("temp.bin", "wb");
    // Read the item structs from the file
    Customer tempCustomer;
    int id;
    // Get user input for item properties
    printf("Enter customer ID to delete: ");
    scanf("%d", &id);
    //fread(&tempCustomer, sizeof(tempCustomer), 1, fp);
    
    while (fread(&tempCustomer, sizeof(tempCustomer), 1, fp) == 1) {
        // If the item ID matches the ID of the item to be deleted, skip writing the item to the temporary file

        if (tempCustomer.id != id) {
            fwrite(&tempCustomer, sizeof(tempCustomer), 1, temp);
        }
    }
    // Close the items file and temporary file
    fclose(fp);
    fclose(temp);
    // Delete the original items file and rename the temporary file to the original file name
    remove("customers.bin");
    rename("temp.bin", "customers.bin");
}

/*========================================Employers FUNCTION======================================*/
// Function to insert items into the itesm file
/*================================================================================================*/

void viewEmployers() {
    // Open the employers file in binary read mode
    FILE* fp = fopen("employers.bin", "rb");
    // Read and print the item information from the file
    Employer temp;
    if (fread(&temp, sizeof(temp), 1, fp) == 0)
        printf("empty project\n");
    else
        readBinFile("employers.bin", &temp, sizeof(temp));

    // Close the file
    fclose(fp);
}

void addEmployer() {
    Employer employer;

    printf("Enter full name employer: ");
    scanf("%s", employer.fullname);
    printf("Enter username employer: ");
    scanf("%s", employer.username);
    printf("Enter password employer: ");
    scanf("%s", employer.password);
    printf("Enter level employer: ");
    scanf("%d", &employer.level);

    // Open the customers file in binary append mode
    FILE* fp = fopen("employers.bin", "ab");
    // Write the customer struct to the file
    fwrite(&employer, sizeof(employer), 1, fp);
    // Close the file
    fclose(fp);
}

void deleteEmployer() {
    // Open the items binary file in read mode
    FILE* fp = fopen("employers.bin", "rb");
    // Create a temporary binary file to store the updated information
    FILE* temp = fopen("temp.bin", "wb");
    // Read the item structs from the file
    Employer tempEmployer;
    char username[20];
    // Get user input for item properties
    printf("Enter employer username to delete: ");
    scanf("%s", username);


    while (fread(&tempEmployer, sizeof(tempEmployer), 1, fp) == 1) {
        // If the item ID matches the ID of the item to be deleted, skip writing the item to the temporary file
        printf("%s:\n", strcmp(tempEmployer.username, username) ? "no" : "yes"); //strcmp(tempEmployer.username, username)
        if (strcmp(tempEmployer.username, username)) {
            printf("i want delete '%s' and compare to '%s':\n", username, tempEmployer.username);
            fwrite(&tempEmployer, sizeof(tempEmployer), 1, temp);
        }
        else
            printf("'%s' equal '%s':\n", username, tempEmployer.username);

    }
    // Close the items file and temporary file
    fclose(fp);
    fclose(temp);
    // Delete the original items file and rename the temporary file to the original file name
    remove("employers.bin");
    rename("temp.bin", "employers.bin");

}

int main() {
    // Check the files exists
    createFiles();
    // Get login details from the user
    char username[15], password[15];
    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);


    // Check the login details
    int level = checkLogin(username, password);
    // If login is successful, display menu options based on level until inser -1
    int choice = 0;
    while(choice != -1)
        choice = menuOptions(level);

    return 0;
}
