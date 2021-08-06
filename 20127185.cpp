#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <sys/stat.h>

using namespace std;
struct Node
{
    string data;
    struct Node *left;
    struct Node *right;
};
Node *newnode, *root, *start;

void question(Node *root, Node *prev);
void Deserialize(Node *&root, fstream &file);
void updatetree(Node *fin, Node *&prefin);
void finalquestion(Node *root, Node *prev);
void dot(int n);
void gameReady();

void gameReady()
{
    cout << "Animal guessing game" << endl;
    system("pause");
}
void Serialize(Node *&root, fstream &file)
{
    if (root == NULL)
        file << "#" << endl;
    else
    {
        file << root->data << endl;
        Serialize(root->left, file);
        Serialize(root->right, file);
    }
}

void Deserialize(Node *&root, fstream &file)
{
    string str;
    if (!file.eof())
    {
        getline(file, str);
        cin.clear();
    }
    else
        return;
    if (str != "#")
    {
        root = new Node;
        root->data = str;
        Deserialize(root->left, file);
        Deserialize(root->right, file);
    }
    else
    {
        root = NULL;
    }
}

// void preorder(Node *root)
// {
//     if (root == NULL)
//         return;
//     else
//     {
//         cout << root->data << endl;
//         preorder(root->left);
//         preorder(root->right);
//     }
// }

void updatetree(Node *fin, Node *&prefin)
{
    string data, qn;
    cout << "\n\n\t\t\t\t\t****I ACCEPT MY DEFEAT****" << endl;
    cout << "What's your animal?"
         << "\t";
    cin.ignore();
    getline(cin, data);
    cout << "Now, type a characteristic question for your animal which return your animal " << data << " for yes, and return " << fin->data << " for no" << endl;
    getline(cin, qn);
    Node *datanode, *qnnode;
    datanode = new Node;
    datanode->data = data;
    datanode->left = NULL;
    datanode->right = NULL;

    qnnode = new Node;
    qnnode->data = qn;
    qnnode->left = datanode;
    qnnode->right = fin;

    if (prefin->left == fin)
    {
        prefin->left = qnnode;
    }

    else if (prefin->right == fin)
    {
        prefin->right = qnnode;
    }
    fstream file;
    file.open("data.txt", ios::out);
    Serialize(start, file);
    cout << "Updated successfully" << endl
         << endl
         << endl;
    string reply;
    cout << "Do you want to play again?";
    cin >> reply;
    if (reply == "yes" || reply == "YES" || reply == "Yes" || reply == "y" || reply == "Y")
    {
        cout << "Rebooting the system";
        dot(2);
        system("CLS");
        question(start, NULL);
    }
    else if (reply == "no" || reply == "NO" || reply == "No" || reply == "n" || reply == "N")
    {

        cout << "Thanks for playing with me, i think we had a good time. See you soon. Bye bye" << endl;
    }
    system("pause");
}

void finalquestion(Node *root, Node *prev)
{
    string reply;
    cout << "Is your animal '" << root->data << "' ?"
         << "\t";
    cin >> reply;
    if (reply == "yes" || reply == "YES" || reply == "Yes" || reply == "y" || reply == "Y")
    {

        cout << "\n\n\t\t\t\tYAAAAAAAAAAAAAAAAAAAH!!! I found out, Huraaaaay" << endl;
        cout << "\t\t\t\t\t      Thanks for playing" << endl
             << "\n\nDo you want to play again?";
        cin >> reply;
        if (reply == "yes" || reply == "YES" || reply == "Yes" || reply == "y" || reply == "Y")
        {
            cout << "Rebooting the system";
            dot(2);
            system("CLS");
            question(start, prev);
        }
        else if (reply == "no" || reply == "NO" || reply == "No" || reply == "n" || reply == "N")
        {
    
            cout << "Thanks for playing with me, i think we had a good time. See you soon. Bye bye" << endl;
        }
    }
    else if (reply == "no" || reply == "NO" || reply == "No" || reply == "n" || reply == "N")
        updatetree(root, prev);
    else
    {
        cout << "Sorry, please enter a valid datawer Yes or No" << endl;
        finalquestion(root, prev);
    }
}

void question(Node *root, Node *prev)
{
    string reply;
    if (root->left != NULL && root->right != NULL)
    {
        cout << root->data << endl;
        cin >> reply;
        if (reply == "yes" || reply == "YES" || reply == "Yes" || reply == "y" || reply == "Y")
            question(root->left, root);
        else if (reply == "no" || reply == "NO" || reply == "No" || reply == "n" || reply == "N")
            question(root->right, root);
        else
        {
            cout << "Sorry, please enter a valid datawer Yes or No" << endl;
            question(root, prev);
        }
    }
    else
    {
        finalquestion(root, prev);
    }
}

void dot(int n)
{
    for (int i = 0; i <= n; i++)
    {
        cout << ".";
        Sleep(900);
    }
    cout << endl;
}

int main()
{
    fstream file;
    struct stat buffer;
    int present = stat("data.txt", &buffer);
    if (present == 0)
    {
        file.open("data.txt", ios::in);
        Deserialize(start, file);
        file.close();
        gameReady();
        cout << "Initiating the GAME";
        dot(3);
        system("CLS");
        question(start, NULL);
        file.open("data.txt", ios::out);
        Serialize(start, file);
        file.close();
    }
    else
    {

        cout << "FILE NOT FOUND, Please ensure the file \"data.txt\" is present in the current directory" << endl;
    }
    return 0;
}