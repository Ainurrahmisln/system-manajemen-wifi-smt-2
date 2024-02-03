#include <iostream>
#include <string>
#include <stack>
#include <queue>

using namespace std;

struct User {
    std::string username;
    std::string password;
    bool isActive;
};

struct Node {
    User data;
    Node* next;
};

// Fungsi untuk menambah pengguna ke dalam linked list
void addUser(Node*& head, const User& user) {
    Node* newNode = new Node();
    newNode->data = user;
    newNode->next = head;
    head = newNode;
}

// Fungsi untuk menampilkan data pengguna dalam linked list
void display(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        cout << "Username: " << current->data.username << ", Password: " << current->data.password << ", Status: " << (current->data.isActive ? "Aktif" : "Tidak Aktif") << endl;
        current = current->next;
    }
}

// Fungsi untuk mencari pengguna berdasarkan username dalam linked list
// Searching
Node* find(Node* head, const string& username) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data.username == username) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

// Fungsi untuk menghapus pengguna dari linked list
void remove(Node*& head, const string& username) {
    if (head == nullptr) {
        return;
    }

    // Jika pengguna berada di posisi pertama
    if (head->data.username == username) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* prev = nullptr;
    Node* current = head;

    while (current != nullptr) {
        if (current->data.username == username) {
            prev->next = current->next;
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Fungsi untuk mengurutkan pengguna dalam linked list berdasarkan username
// Sorting
void sorting(Node*& head) {
    if (head == nullptr || head->next == nullptr) {
        return;
    }

    Node* current = head;
    Node* index = nullptr;
    User temp;

    while (current != nullptr) {
        index = current->next;

        while (index != nullptr) {
            if (current->data.username > index->data.username) {
                temp = current->data;
                current->data = index->data;
                index->data = temp;
            }

            index = index->next;
        }

        current = current->next;
    }
}

int main() {
    stack<User> userStack;	 // Stack
    queue<User> userQueue;	// Queue
    Node* ptr = nullptr;   // Pinter

    int choice;

    do {
        cout << "==========  System User Manajemen Wifi ==========" << endl;
        cout << "=====================================================" << endl;
        cout << "1. Tambah Pengguna" << endl;
        cout << "2. Hapus Pengguna" << endl;
        cout << "3. Tampilkan Pengguna " << endl;
        cout << "4. Ubah Status Pengguna" << endl;
        cout << "0. Keluar" << endl;
        menu:
        cout << "Pilihan Anda: ";
        cin >> choice;
       

        switch (choice) {
            case 1: {
            	
                string username;
                string password;
				
				username:;
                cout << "Username: ";
                cin >> username;
                if (find(ptr, username) != nullptr) {
        		cout << "Username sudah digunakan. Tidak dapat menambahkan pengguna dengan username yang sama." << endl;
        		cout << endl;
        		goto username;
    			}
                cout << "Password: ";
                cin >> password;

                User newUser{username, password, true};
                userStack.push(newUser);
                userQueue.push(newUser);
                addUser(ptr, newUser);

				system("pause");
				system("cls");
                break;
            }
            case 2: {
                if (!userStack.empty()) {
                    userStack.pop();
                    userQueue.pop();

                    string username;
                    cout << "Username Pengguna yang akan dihapus: ";
                    cin >> username;
                    Node* userNode = find(ptr, username);
                    
                    if (userNode != nullptr){
                    remove(ptr, username);
                    cout << "Pengguna dihapus." << endl;
					} else {
						cout << "Pengguna tidak ditemukan." << endl;
					}
				} else {
                    cout << "Tidak ada pengguna." << endl;
                }
                system("pause");
				system("cls");
                break;
            }
            case 3: {
                cout << "Daftar Pengguna : " << endl;
                sorting(ptr);
				display(ptr);
				system("pause");
				system("cls");
                break;
            }
            case 4: {
                string username;
                cout << "Username Pengguna: ";
                cin >> username;

                Node* userNode = find(ptr, username);

                if (userNode != nullptr) {
                    userNode->data.isActive = !userNode->data.isActive;
                    cout << "Status Pengguna berhasil diperbarui." << endl;
                } else {
                    cout << "Pengguna tidak ditemukan." << endl;
                }
				system("pause");
				system("cls");
                break;
            }
            
            case 0: {
                cout << "Terima kasih. Program selesai." << endl;
                break;
            }
            default : {
            	if(choice != 0)
                {
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
                cout << endl;
				goto menu;
				}
                break;
            }
        }

        cout << endl;
    } while (choice != 0);

    

    return 0;
}
