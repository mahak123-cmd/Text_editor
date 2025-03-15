#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

vector<string> textBuffer;
vector<vector<string>> history;

void saveHistory() {
    history.push_back(textBuffer);
}

void createNewFile() {
    textBuffer.clear();
    history.clear();
    cout << "New document created.\n";
}

void openFile() {
    string filename, line;
    cout << "Enter filename to open: ";
    cin >> filename;
    ifstream file(filename);
    if (!file) {
        cout << "File not found!\n";
        return;
    }
    textBuffer.clear();
    while (getline(file, line)) {
        textBuffer.push_back(line);
    }
    file.close();
    history.clear();
    saveHistory();
    cout << "File opened successfully.\n";
}

void saveFile() {
    string filename;
    cout << "Enter filename to save: ";
    cin >> filename;
    ofstream file(filename);
    for (const auto &line : textBuffer) {
        file << line << endl;
    }
    file.close();
    cout << "File saved successfully.\n";
}

void editText() {
    string line;
    cout << "Enter text (type END to stop):\n";
    saveHistory();
    cin.ignore();
    while (true) {
        getline(cin, line);
        if (line == "END") break;
        textBuffer.push_back(line);
    }
}

void searchAndReplace() {
    string searchText, replaceText;
    cout << "Enter text to search: ";
    cin.ignore();
    getline(cin, searchText);
    cout << "Enter replacement text: ";
    getline(cin, replaceText);
    saveHistory();
    for (auto &line : textBuffer) {
        size_t pos;
        while ((pos = line.find(searchText)) != string::npos) {
            line.replace(pos, searchText.length(), replaceText);
        }
    }
    cout << "Text replaced successfully.\n";
}

void undo() {
    if (!history.empty()) {
        textBuffer = history.back();
        history.pop_back();
        cout << "Undo successful.\n";
    } else {
        cout << "No changes to undo.\n";
    }
}

void displayText() {
    cout << "\nCurrent Document:\n";
    for (const auto &line : textBuffer) {
        cout << line << endl;
    }
    cout << "\n";
}

int main() {
    int choice;
    do {
        cout << "\nText Editor Menu:";
        cout << "\n1. Create New File\n2. Open File\n3. Save File\n4. Edit Text\n5. Search and Replace\n6. Undo\n7. Display Document\n8. Exit\nChoose an option: ";
        cin >> choice;
        
        switch (choice) {
            case 1: createNewFile(); break;
            case 2: openFile(); break;
            case 3: saveFile(); break;
            case 4: editText(); break;
            case 5: searchAndReplace(); break;
            case 6: undo(); break;
            case 7: displayText(); break;
            case 8: cout << "Exiting the text editor.\n"; break;
            default: cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 8);
    
    return 0;
}
