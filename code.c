#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Structure for Product (Linked List) */
struct Product {
    int id;
    char name[50];
    float price;
    struct Product *next;
};

/* Structure for Cart Stack */
struct CartStack {
    int id;
    char name[50];
    float price;
    struct CartStack *next;
};

/* Structure for Order Queue */
struct Order {
    int id;
    char name[50];
    float price;
    struct Order *next;
};

/* Global pointers */
struct Product *productList = NULL;
struct CartStack *cartTop = NULL;
struct Order *front = NULL, *rear = NULL;

/* Add product in sorted order */
void addProduct(int id, char name[], float price) {
    struct Product *newProduct = malloc(sizeof(struct Product));
    newProduct->id = id;
    strcpy(newProduct->name, name);
    newProduct->price = price;
    newProduct->next = NULL;

    if (productList == NULL || productList->id > id) {
        newProduct->next = productList;
        productList = newProduct;
    } else {
        struct Product *current = productList;
        while (current->next != NULL && current->next->id < id)
            current = current->next;

        newProduct->next = current->next;
        current->next = newProduct;
    }
}

/* Display products */
void displayProducts() {
    struct Product *temp = productList;
    printf("\nAvailable Products:\n");
    while (temp) {
        printf("[%d] %s - Rs. %.2f\n", temp->id, temp->name, temp->price);
        temp = temp->next;
    }
}

/* Add product to cart */
void addToCart(int id) {
    struct Product *temp = productList;
    while (temp && temp->id != id)
        temp = temp->next;

    if (temp) {
        struct CartStack *newItem = malloc(sizeof(struct CartStack));
        newItem->id = temp->id;
        strcpy(newItem->name, temp->name);
        newItem->price = temp->price;
        newItem->next = cartTop;
        cartTop = newItem;
        printf("%s added to cart.\n", temp->name);
    } else {
        printf("Invalid product ID!\n");
    }
}

/* Place order */
void placeOrder() {
    if (cartTop == NULL) {
        printf("Cart is empty! Cannot place order.\n");
        return;
    }

    float total = 0;
    printf("\nOrder Summary:\n");

    while (cartTop) {
        struct Order *newOrder = malloc(sizeof(struct Order));
        newOrder->id = cartTop->id;
        strcpy(newOrder->name, cartTop->name);
        newOrder->price = cartTop->price;
        newOrder->next = NULL;

        if (rear == NULL)
            front = rear = newOrder;
        else {
            rear->next = newOrder;
            rear = newOrder;
        }

        total += cartTop->price;
        printf("%s - Rs. %.2f\n", cartTop->name, cartTop->price);

        struct CartStack *temp = cartTop;
        cartTop = cartTop->next;
        free(temp);
    }

    printf("Total: Rs. %.2f\nOrder placed successfully!\n", total);
}

int main() {
    int choice, id;

    /* Sample products */
    addProduct(1, "Laptop", 50000);
    addProduct(2, "Smartphone", 20000);
    addProduct(3, "Headphones", 1500);
    addProduct(4, "Smartwatch", 5000);
    addProduct(5, "Tablet", 15000);
    addProduct(6, "Wireless Mouse", 800);
    addProduct(7, "Keyboard", 1200);

    while (1) {
        printf("\n1. View Products\n2. Add to Cart\n3. Place Order\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayProducts(); break;
            case 2:
                printf("Enter product ID: ");
                scanf("%d", &id);
                addToCart(id);
                break;
            case 3: placeOrder(); break;
            case 4: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}
