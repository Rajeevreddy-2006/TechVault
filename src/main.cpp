#include <iostream>
#include <string>

// Core system
#include "../include/Encryptor.h"
#include "../include/Logger.h"
#include "../include/Storage.h"
#include "../include/VaultManager.h"

// Factory
#include "../include/VaultItemFactory.h"

// ---------------- Utility: Safe integer input ----------------
bool readInt(int& value) {
    std::cin >> value;
    if (std::cin.fail()) {
        std::cin.clear();                 // clear error state
        std::cin.ignore(10000, '\n');     // discard bad input
        return false;
    }
    std::cin.ignore(10000, '\n');         // clear newline
    return true;
}

// ---------------- UI: Banner ----------------
void showBanner() {
    std::cout << R"(
====================================================
 ████████╗███████╗ ██████╗██╗  ██╗██╗   ██╗ █████╗ ██╗   ██╗██╗     ████████╗
 ╚══██╔══╝██╔════╝██╔════╝██║  ██║██║   ██║██╔══██╗██║   ██║██║     ╚══██╔══╝
    ██║   █████╗  ██║     ███████║██║   ██║███████║██║   ██║██║        ██║   
    ██║   ██╔══╝  ██║     ██╔══██║╚██╗ ██╔╝██╔══██║██║   ██║██║        ██║   
    ██║   ███████╗╚██████╗██║  ██║ ╚████╔╝ ██║  ██║╚██████╔╝███████╗   ██║   
    ╚═╝   ╚══════╝ ╚═════╝╚═╝  ╚═╝  ╚═══╝  ╚═╝  ╚═╝ ╚═════╝ ╚══════╝   ╚═╝   

              🔐 Secure Vault Management System
====================================================
)";
}

// ---------------- UI: Menu ----------------
void showMenu() {
    std::cout << "\n📋 Main Menu\n";
    std::cout << "---------------------------------\n";
    std::cout << "📁 1. Add File Item\n";
    std::cout << "🔑 2. Add Password Item\n";
    std::cout << "💻 3. Add Snippet Item\n";
    std::cout << "📜 4. Show Vault Items\n";
    std::cout << "💾 5. Save Vault\n";
    std::cout << "🔄 6. Load & Reconstruct Vault\n";
    std::cout << "🔍 7. Search Item by Name\n";
    std::cout << "❌ 8. Delete Item by Name\n";
    std::cout << "🚪 0. Exit\n";
    std::cout << "---------------------------------\n";
    std::cout << "Enter choice: ";
}

int main() {
    // ---------- Encryption ----------
    XOREncryptor encryptor('K');

    // ---------- Logger ----------
    ConsoleLogger consoleLogger;

    // ---------- Storage ----------
    LocalStorage localStorage(&consoleLogger);

    // ---------- Vault Manager ----------
    VaultManager manager(&localStorage, encryptor);

    showBanner();

    int choice = -1;

    while (choice != 0) {
        showMenu();

        if (!readInt(choice)) {
            std::cout << "[ERROR] Please enter a valid number.\n";
            continue;
        }

        switch (choice) {
            case 1:
            case 2:
            case 3: {
                VaultItem* item =
                    VaultItemFactory::create(choice, encryptor);

                if (item) {
                    manager.addItem(item);
                    std::cout << "[SUCCESS] Item added successfully.\n";
                } else {
                    std::cout << "[ERROR] Item creation failed.\n";
                }
                break;
            }

            case 4:
                manager.showAll();
                break;

            case 5:
                manager.saveAll();
                std::cout << "[SUCCESS] Vault saved.\n";
                break;

            case 6:
                manager.loadAndReconstruct();
                std::cout << "[SUCCESS] Vault reconstructed.\n";
                break;

            case 7: {
                std::string name;
                std::cout << "Enter item name to search: ";
                std::getline(std::cin, name);

                if (name.empty()) {
                    std::cout << "[ERROR] Name cannot be empty.\n";
                    break;
                }

                manager.searchByName(name);
                break;
            }

            case 8: {
                std::string name;
                std::cout << "Enter item name to delete: ";
                std::getline(std::cin, name);

                if (name.empty()) {
                    std::cout << "[ERROR] Name cannot be empty.\n";
                    break;
                }

                std::string confirm;
                std::cout << "Are you sure you want to delete? (y/n): ";
                std::getline(std::cin, confirm);

                if (confirm != "y" && confirm != "Y") {
                    std::cout << "Delete cancelled.\n";
                    break;
                }

                manager.deleteByName(name);
                break;
            }

            case 0:
                std::cout << "\n👋 Exiting TechVault. Goodbye!\n";
                break;

            default:
                std::cout << "[ERROR] Invalid choice. Try again.\n";
        }
    }
    
    return 0;
}
