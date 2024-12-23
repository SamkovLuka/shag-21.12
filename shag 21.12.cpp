


#include <iostream>
using namespace std;



struct ViolationNode {
    string violation;
    ViolationNode* next;

    ViolationNode(const string& viol) : violation(viol), next(nullptr) {}
};


struct TreeNode {
    string carNumber;
    ViolationNode* violations;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const string& carNum, const string& violation)
        : carNumber(carNum), violations(new ViolationNode(violation)), left(nullptr), right(nullptr) {}
};


class TrafficDatabase {
private:
    TreeNode* root;
    TreeNode* addViolation(TreeNode* node, const string& carNumber, const string& violation) {
        if (!node) return new TreeNode(carNumber, violation);

        if (carNumber < node->carNumber) {
            node->left = addViolation(node->left, carNumber, violation);
        }
        else if (carNumber > node->carNumber) {
            node->right = addViolation(node->right, carNumber, violation);
        }
        else {
            ViolationNode* current = node->violations;
            while (current->next) current = current->next;
            current->next = new ViolationNode(violation);
        }
        return node;
    }


    void printDatabase(TreeNode* node) {
        if (!node) return;

        printDatabase(node->left);

        cout << "Car number: " << node->carNumber << "\nViolations:\n";
        ViolationNode* current = node->violations;
        while (current) {
            cout << "  - " << current->violation << endl;
            current = current->next;
        }
        cout << endl;

        printDatabase(node->right);
    }

    TreeNode* findCar(TreeNode* node, const string& carNumber) {
        if (!node || node->carNumber == carNumber) return node;

        if (carNumber < node->carNumber) {
            return findCar(node->left, carNumber);
        }
        else {
            return findCar(node->right, carNumber);
        }
    }


    void printRange(TreeNode* node, const string& low, const string& high) {
        if (!node) return;

        if (low < node->carNumber) {
            printRange(node->left, low, high);
        }

        if (low <= node->carNumber && node->carNumber <= high) {
            cout << "Car number: " << node->carNumber << "\nViolations:\n";
            ViolationNode* current = node->violations;
            while (current) {
                cout << "  - " << current->violation << endl;
                current = current->next;
            }
            cout << endl;
        }

        if (high > node->carNumber) {
            printRange(node->right, low, high);
        }
    }





public:
    TrafficDatabase() : root(nullptr) {}
    void add(const string& carNumber, const string& violation) {
        root = addViolation(root, carNumber, violation);
    }


    void print() {
        printDatabase(root);
    }

    void printByCarNumber(const string& carNumber) {
        TreeNode* node = findCar(root, carNumber);
        if (!node) {
            cout << "Car number " << carNumber << " not found.\n";
            return;
        }

        cout << "Car number: " << node->carNumber << "\nViolations:\n";
        ViolationNode* current = node->violations;
        while (current) {
            cout << "  - " << current->violation << endl;
            current = current->next;
        }
    }


    void printByRange(const string& low, const string& high) {
        printRange(root, low, high);
    }
};

int main() {
    TrafficDatabase db;
    db.add("AA1234BB", "Speeding");
    db.add("AA1234BB", "Illegal parking");
    db.add("AB5678CD", "Running a red light");
    db.add("AC9876EF", "Driving without insurance");
    cout << "Full database:\n";
    db.print();
    cout << "\nData for car AA1234BB:\n";
    db.printByCarNumber("AA1234BB");
    cout << "\nData for range AB0000CC to AC9999ZZ:\n";
    db.printByRange("AB0000CC", "AC9999ZZ");
}

