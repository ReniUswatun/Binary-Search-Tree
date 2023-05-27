#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SIZE_ALL 64
#define SIZE_MENU_PRINT 7
#define STRING char *
#define NODE Node *

typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
} Node;

enum choice
{
    INSERT = 1,
    RANDOM,
    PREORDER,
    INORDER,
    POSTORDER,
    DELETE,
    KELUAR
};

typedef enum NodePosition
{
    LEFT,
    RIGHT,
    NO_POS
} Position;

NODE temp;

void system_clear();
void printline();
void the_time();
void displayBinaryTree(NODE node, int index, Position pos);
void print_menu();
NODE createNode(int data);
int insert_choice();
void insertNode(NODE temp, NODE node);
void DataOlah();
void inOrder(NODE treePtr);
void preOrder(NODE treePtr);
void postOrder(NODE treePtr);
NODE deleteNode(NODE treePtr, int key);

NODE tree = NULL;

int main()
{
    int pil;
    int insert;
    int data1;
    int item;
    srand(time(NULL));
    system_clear();
    printline();
    the_time();

    if (tree == NULL)
    {
        puts("No Data in There");
    }
    else
    {
        puts("The Data");
        displayBinaryTree(tree, 0, NO_POS);
    }

    print_menu();
    printf("Masukkan Menu Pilihan -> ");
    scanf("%d", &pil);

    switch (pil)
    {
    case INSERT:
        while (tree == NULL)
        {
            int pilihan = insert_choice();
            tree = createNode(pilihan);
            DataOlah();
        }
        int pilihan = insert_choice();
        insertNode(tree, createNode(pilihan));
        DataOlah();
        break;

    case RANDOM:
        item = rand() % 99;
        if (tree == NULL)
        {
            tree = createNode(item);
        }
        else
        {
            insertNode(tree, createNode(item));
        }
        DataOlah();
        break;

    case PREORDER:
        system_clear();
        printline();
        printf("%*s", 43, "The PREORDER Transversal\n");
        printline();
        preOrder(tree);
        printf("\n\n\n");
        puts("Tunggu! Otomatis ke main menu");
        sleep(1);
        main();
        break;

    case INORDER:
        system_clear();
        printline();
        printf("%*s", 43, "The INORDER Transversal\n");
        printline();
        inOrder(tree);
        printf("\n\n\n");
        puts("Tunggu! Otomatis ke main menu");
        sleep(1);
        main();
        break;

    case POSTORDER:
        system_clear();
        printline();
        printf("%*s", 43, "The POSTORDER Transversal\n");
        printline();
        postOrder(tree);
        printf("\n\n\n");
        puts("Tunggu! Otomatis ke main menu");
        sleep(1);
        main();
        break;

    case DELETE:
        printf("\n Ketik data apa yang ingin di delete -> ");
        scanf(" %d", &data1);
        tree = deleteNode(tree, data1);
        DataOlah();
        break;

    case KELUAR:
        printf("Terima Kasih");
        exit(0);
        break;

    default:
        printf("Pilihan yang dimasukkan salah");
        main();
        break;
    }
}

void print_menu()
{
    const STRING menu[SIZE_MENU_PRINT] = {
        "Insert Number (the first insert will be root)",
        "Insert Random",
        "Read The Preorder Transversal",
        "Read The Inorder Transversal",
        "Read The Postorder Transversal",
        "Delete",
        "Keluar program"};
    printline();
    for (int a = 0; a < SIZE_MENU_PRINT; a++)
    {
        printf("| %d. %-*s|\n", (a + 1), SIZE_ALL - 5, menu[a]);
    }
    printline();
}

void system_clear()
{
    if (system("cls"))
        system("clear");
}

void printline()
{
    for (int a = SIZE_ALL; a > 0; a--)
    {
        printf("=");
    }
    puts("");
}

void the_time()
{
    time_t biggest = time(NULL);

    printf("%s", ctime(&biggest));
    printline();
}

void displayBinaryTree(NODE node, int index, Position pos)
{
    if (node == NULL)
        return;

    for (int a = 0; a < index; a++)
    {
        if (a == (index - 1))

            printf("_ ");

        else if (a == (index - 2))

            printf("|");

        else

            printf(" ");
    }

    printf(" %d ", node->data);
    printf("(%s)\n", pos == NO_POS ? "ROOT" : (pos == LEFT ? "LEFT" : "RIGHT"));

    displayBinaryTree(node->left, (index + 3), LEFT);
    displayBinaryTree(node->right, (index + 3), RIGHT);
}

NODE createNode(int data)
{
    NODE newnode = malloc(sizeof(Node));

    if (newnode != NULL)
    {
        newnode->data = data;
        newnode->left = NULL;
        newnode->right = NULL;
        puts("success create a new node");
    }
    else
    {
        printf("%d not inserted. No memory available.\n", data);
    }

    return newnode;
}

int insert_choice()
{
    int b;
    puts("Masukkan Angka Ke Binary Tree");
    printf(">> ");
    scanf("%d", &b);
    return b;
}

void insertNode(NODE temp, NODE node)
{
    NODE current = temp;
    Position InsertPosition;

    while (current != NULL)
    {
        if (node->data <= current->data)
        {
            if (current->left == NULL)
            {
                InsertPosition = LEFT;
                break;
            }
            else
            {
                current = current->left;
            }
        }
        else
        {
            if (current->right == NULL)
            {
                InsertPosition = RIGHT;
                break;
            }
            else
            {
                current = current->right;
            }
        }
    }

    if (InsertPosition == LEFT)
    {
        current->left = node;
    }
    else
    {
        current->right = node;
    }
}

void DataOlah()
{
    printf("Data Berhasi Diolah");
    main();
}

void inOrder(NODE treePtr)
{
    // system_clear();

    if (treePtr == NULL)
    {
        return;
    }
    inOrder(treePtr->left);
    printf("-> %d ", treePtr->data);
    inOrder(treePtr->right);
}

void preOrder(NODE treePtr)
{
    if (treePtr == NULL)
    {
        return;
    }
    printf("-> %d ", treePtr->data);
    preOrder(treePtr->left);
    preOrder(treePtr->right);
}

void postOrder(NODE treePtr)
{
    if (treePtr == NULL)
    {
        return;
    }
    postOrder(treePtr->left);
    postOrder(treePtr->right);
    printf("-> %d ", treePtr->data);
}

NODE findNode(NODE root, int data)
{
    if (data == root->data)
        return root;
    else if (data > root->data)
        return findNode(root->right, data);
    else if (data < root->data)
        return findNode(root->left, data);
}

int findMin(NODE root)
{
    if (root->left == NULL)

        return root->data;
    else
        return findMin(root->left);
}

int findMax(NODE root)
{
    if (root->right == NULL)
    {
        return root->data;
    }
    else
        return findMax(root->right);
}

NODE deleteNode(NODE treePtr, int key)
{
    if (treePtr == NULL)
        return treePtr;

    if (key < treePtr->data)
        treePtr->left = deleteNode(treePtr->left, key);

    else if (key > treePtr->data)
        treePtr->right = deleteNode(treePtr->right, key);

    else
    {
        if (treePtr->left == NULL)
        {
            NODE temp = treePtr->right;
            free(treePtr);
            return temp;
        }
        else if (treePtr->right == NULL)
        {
            NODE temp = treePtr->left;
            free(treePtr);
            return temp;
        }

        NODE temp = findNode(treePtr, findMin(treePtr->right));

        treePtr->data = temp->data;

        treePtr->right = deleteNode(treePtr->right, temp->data);
    }
    return treePtr;
}

/*Merupakan program biner
dengan menu insert dan delete dan membaca pre in dan post*/
