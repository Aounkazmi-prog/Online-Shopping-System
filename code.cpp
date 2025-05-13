
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
using namespace std;

const int totalProducts = 100;
const int totalCategories = 10;
bool flag = true;

class Product {
public:
    string name;
    float price;

    Product() {
        name = "";
        price = 0;
    }
    Product(string name, float price) {
        this->name = name;
        this->price = price;
    }
};

class Category {
public:
    string name;
    Product products[totalProducts];
    int productCount;
    Category() {
        name = "";
        productCount = 0;

    }
    Category(string name) {
        this->name = name;
        productCount = 0;
    }

    void addProduct(const Product& product) {
        if (productCount < totalProducts) {
            products[productCount++] = product;
        }
    }

    void editProduct(size_t index, const Product& product) {
        if (index < productCount) {
            products[index] = product;
        }
        else {
            cout << "Please enter index in the range " << endl;
        }
    }

    void deleteProduct(int index) {
        if (index < productCount) {
            for (int i = index; i < productCount - 1; ++i) {
                products[i] = products[i + 1];
            }
            productCount--;
        }
    }

    void displayProducts() const {
        for (size_t i = 0; i < productCount; ++i) {
            cout << i + 1 << ". " << products[i].name;
            cout<< " (Rs. " << products[i].price << ")";
            cout << endl;
        }
            cout << "0. Go back to Category List" << endl;
    }

    int selectProduct(Product cartItems[], int& cartItemCount) const {
        int choice;
        char chk;

        system("cls");
        system("color 70");

        cout << endl << name << ":"<<endl;
        displayProducts();

        while (true) {
            cout << endl;
            cout << "Your Choice: ";
            cin >> choice;
            Beep(550, 300);
            if (choice < 0 || choice > productCount) {
                cout << "Invalid input. Please try again."<<endl;
            }
            else if (choice == 0) {
                cout << "Returning to categories..." << endl;
                Sleep(1000);
                break;
            }
            else {
                cartItems[cartItemCount++] = products[choice - 1];
                cout << "Added to cart! Press 'Y' to add another item or any other key to go back to categories: ";
                cin >> chk;
                if (chk != 'y' && chk != 'Y') {
                    break;
                }
            }
        }

        return 0; 
    }

};

class Store {
private:

    Category categories[totalCategories];
    int categoryCount;
    float cart; 
    string adminPassword; 
    Product cartItems[totalProducts];
    int cartItemCount = 0;


public:
    Store() {
        cart = 0;
        adminPassword = "oop";
        categoryCount = 0;
        loadProductsFromFile();
    } 
    void viewCart() {
        system("cls");
        system("color F0");

        if (cartItemCount == 0) {
            cout << "Your cart is empty."<<endl;
            Sleep(1500);
            return;
        }

        float total = 0;

        cout << "--------------- Your Cart ---------------"<<endl;
        for (int i = 0; i < cartItemCount; ++i) {
            cout << i + 1 << ". " << cartItems[i].name << " - Rs. " << cartItems[i].price << endl;
            total += cartItems[i].price;
        }
        cout << "-----------------------------------------" << endl;;
        cout << "Total Bill: Rs. " << total << endl;

        char choice;
        cout <<endl<< "Do you want to remove an item? (Y/N): ";
        cin >> choice;

        if (choice == 'Y' || choice == 'y') {
            int removeIndex;
            cout << "Enter the number of the item to remove: ";
            cin >> removeIndex;

            if (removeIndex >= 1 && removeIndex <= cartItemCount) {
                for (int i = removeIndex - 1; i < cartItemCount - 1; ++i) {
                    cartItems[i] = cartItems[i + 1];
                }
                cartItemCount--;
                cout << "Item removed.";
                cout << endl;
            }
            else {
                cout << "Invalid item number." << endl;;
            }
            Sleep(1500);
            viewCart();  
        }
        else {
            cout << endl;
            cout << "Do you want to proceed to checkout? (Y/N): ";
            cin >> choice;

            if (choice == 'Y' || choice == 'y') {
                cart = total;
                saveDeliveryInfo();
            }
        }
    }

    void addCategory(const Category& category) {
        if (categoryCount < totalCategories) {
            categories[categoryCount++] = category;
        }
    }

    void displayCategories() {
        int choice;

        while (true) {
            system("cls");
            system("color B0"); 

            cout << "---------------------- CATEGORIES ----------------------"<<endl;
            cout << "Choose a category to explore:"<<endl;

            for (size_t i = 0; i < categoryCount; ++i) {
                cout << "\tPress " << i + 1 << " for " << categories[i].name << endl;
            }
            cout << "\tPress 0 to go back to the main menu"<<endl;
            cout << endl<<"-------------------------------------------------------"<<endl;

            cout << "Your choice: ";
            cin >> choice;
            Beep(550, 300);
            if ( choice < 0 || choice > categoryCount) {
                
                cout << endl<<"Invalid input. Please enter a valid category number ."<<endl;
                Sleep(1500);
            }
            else if (choice == 0) {
                cout << endl;
                cout << "Returning to main menu..."<<endl;
                Sleep(1500);
                break;  
            }
            else {
                categories[choice - 1].selectProduct(cartItems, cartItemCount);

            }
        }
    }

    void displayLoadingScreen() {
        system("cls");
        system("color 70"); 

        string loadingMessage = "Loading, please wait...";
        char x = 219;

        cout << endl<<endl<<endl;
        cout << "\t\t\t\t\t\t" << loadingMessage << endl;
        cout << "\t\t\t\t\t";

        for (int i = 0; i < 35; i++) {
            cout << x;
            Sleep(55); 
        }

        cout << endl;
        cout << "\t\t\t\t\t";
       cout<<"Loading complete !" << endl;
        Sleep(500);
        system("cls"); 
    }

    void saveDeliveryInfo() {
        string name, address, mobile;

        system("cls");
        system("color E0");

        cout << endl << endl << endl;
        cout << "\t\t\t -----------------------------------------" << endl;
        cout << "\t\t\t|                                         |" << endl;
        cout << "\t\t\t|    Thank you for shopping with us!      |" << endl;
        cout << "\t\t\t|                                         |" << endl;
        cout << "\t\t\t|    To deliver your order smoothly,      |" << endl;
        cout << "\t\t\t|      our suppliers need your details.   |" << endl;
        cout << "\t\t\t|                                         |" << endl;
        cout << "\t\t\t-------------------------------------------" << endl << endl;
        Sleep(500);

        cout << "Enter your mobile phone number: ";
        cin >> mobile;

        cin.ignore();

        cout << "Enter your address: ";
        getline(cin, address);

        cout << "Enter your name: ";
        getline(cin, name);

        ofstream file("record.csv", ios::app);
        if (file.is_open()) {
            file << name << "," << address << "," << mobile << "," << cart << endl;
            file.close();
        }
        else {
            cerr << "Error opening file." << endl;
        }

        system("cls");
        cout << endl << endl;
        cout << "\t Dear " << name << ", your order has been placed successfully!" << endl;
        cout << "\t Your Total Bill: Rs. " << cart << endl;
        cout << endl << "\t Get your cash ready , our delivery partner" << endl;
        cout << "\t   will arrive at your doorstep within **30 minutes**!" << endl;
        cout << endl << "\tThank you for trusting us. We hope to serve you again!" << endl;
        Sleep(3500);

        cartItemCount = 0;
        cart = 0;

        char choice;
        cout << endl << endl << "Press 'E' to Exit: ";
        cin >> choice;

        if (choice == 'E' || choice == 'e') {
            cout << endl << "Exiting the program. Have a great day!" << endl;
            Sleep(1500);
            exit(0);
        }
        else {
            exit(0);
        }
    }

    void saveProductsToFile() {
        ofstream file("products.dat", ios::binary);
        if (!file.is_open()) {
            cerr << "Error saving products to file." << endl;
            return;
        }

        file.write((char*)&categoryCount, sizeof(categoryCount));

        for (int i = 0; i < categoryCount; i++) {
            
            size_t nameLength = categories[i].name.size();
            file.write((char*)&nameLength, sizeof(nameLength));
            file.write(categories[i].name.c_str(), nameLength);

            file.write((char*)&categories[i].productCount, sizeof(categories[i].productCount));

            for (int j = 0; j < categories[i].productCount; j++) {
             
                size_t productNameLength = categories[i].products[j].name.size();
                file.write((char*)&productNameLength, sizeof(productNameLength));
                file.write(categories[i].products[j].name.c_str(), productNameLength);

                file.write((char*)&categories[i].products[j].price, sizeof(float));
            }
        }
        file.close();
    }

    void loadProductsFromFile() {
        ifstream file("products.dat", ios::binary);
        if (!file.is_open()) {
            populateStore();
            return;
        }

        file.read((char*)&categoryCount, sizeof(categoryCount));

        for (int i = 0; i < categoryCount; i++) {
            size_t nameLength;
            file.read((char*)&nameLength, sizeof(nameLength));
            char* nameBuffer = new char[nameLength + 1];
            file.read(nameBuffer, nameLength);
            nameBuffer[nameLength] = '\0';
            categories[i].name = nameBuffer;
            delete[] nameBuffer;
            file.read((char*)&categories[i].productCount, sizeof(categories[i].productCount));
            for (int j = 0; j < categories[i].productCount; j++) {
                size_t productNameLength;
                file.read((char*)&productNameLength, sizeof(productNameLength));
                char* productNameBuffer = new char[productNameLength + 1];
                file.read(productNameBuffer, productNameLength);
                productNameBuffer[productNameLength] = '\0';

                float price;
                file.read((char*)&price, sizeof(float));

                categories[i].products[j] = Product(string(productNameBuffer), price);
                delete[] productNameBuffer;
            }
        }
        file.close();
    }
    void populateStore() {

        Category electronics("Electronics");
        electronics.addProduct(Product("Smartphone", 20000));
        electronics.addProduct(Product("Laptop", 50000));
        electronics.addProduct(Product("Headphones", 3000));
        electronics.addProduct(Product("Smartwatch", 8000));
        electronics.addProduct(Product("Television", 25000));
        electronics.addProduct(Product("Camera", 15000));
        electronics.addProduct(Product("Tablet", 12000));
        electronics.addProduct(Product("Bluetooth Speaker", 2500));
        electronics.addProduct(Product("Power Bank", 1500));
        addCategory(electronics);

        Category groceries("Groceries");
        groceries.addProduct(Product("Apple", 150));
        groceries.addProduct(Product("Milk", 50));
        groceries.addProduct(Product("Bread", 40));
        groceries.addProduct(Product("Eggs (Dozen)", 120));
        groceries.addProduct(Product("Rice (1kg)", 100));
        groceries.addProduct(Product("Sugar (1kg)", 60));
        groceries.addProduct(Product("Tomatoes (1kg)", 80));
        groceries.addProduct(Product("Potatoes (1kg)", 70));
        groceries.addProduct(Product("Butter", 250));
        groceries.addProduct(Product("Cheese", 400));
        groceries.addProduct(Product("Bananas (1kg)", 120));
        groceries.addProduct(Product("Orange (1kg)", 150));
        addCategory(groceries);

        Category fashion("Fashion");
        fashion.addProduct(Product("T-shirt", 500));
        fashion.addProduct(Product("Jeans", 1500));
        fashion.addProduct(Product("Sweater", 1200));
        fashion.addProduct(Product("Jacket", 2500));
        fashion.addProduct(Product("Socks (Pack of 3)", 300));
        fashion.addProduct(Product("Shoes", 2000));
        fashion.addProduct(Product("Watch", 3500));
        fashion.addProduct(Product("Hat", 600));
        addCategory(fashion);

        Category homeAppliances("Home Appliances");
        homeAppliances.addProduct(Product("Refrigerator", 25000));
        homeAppliances.addProduct(Product("Washing Machine", 15000));
        homeAppliances.addProduct(Product("Microwave", 8000));
        homeAppliances.addProduct(Product("Vacuum Cleaner", 5000));
        homeAppliances.addProduct(Product("Air Conditioner", 35000));
        homeAppliances.addProduct(Product("Blender", 2000));
        homeAppliances.addProduct(Product("Mixer", 1500));
        homeAppliances.addProduct(Product("Electric Kettle", 1000));
        addCategory(homeAppliances);

        Category beautyCare("Beauty & Personal Care");
        beautyCare.addProduct(Product("Shampoo", 350));
        beautyCare.addProduct(Product("Conditioner", 400));
        beautyCare.addProduct(Product("Toothpaste", 150));
        beautyCare.addProduct(Product("Face Cream", 800));
        beautyCare.addProduct(Product("Perfume", 1200));
        beautyCare.addProduct(Product("Lipstick", 500));
        beautyCare.addProduct(Product("Sunscreen", 600));
        beautyCare.addProduct(Product("Shaving Kit", 700));
        addCategory(beautyCare);

        Category sportsOutdoors("Sports & Outdoors");
        sportsOutdoors.addProduct(Product("Football", 800));
        sportsOutdoors.addProduct(Product("Basketball", 1000));
        sportsOutdoors.addProduct(Product("Tennis Racket", 1500));
        sportsOutdoors.addProduct(Product("Running Shoes", 2500));
        sportsOutdoors.addProduct(Product("Yoga Mat", 500));
        sportsOutdoors.addProduct(Product("Camping Tent", 5000));
        sportsOutdoors.addProduct(Product("Fishing Rod", 2000));
        sportsOutdoors.addProduct(Product("Cycling Helmet", 1500));
        addCategory(sportsOutdoors);

        Category books("Books");
        books.addProduct(Product("Fiction Book", 400));
        books.addProduct(Product("Science Book", 600));
        books.addProduct(Product("History Book", 350));
        books.addProduct(Product("Programming Book", 800));
        books.addProduct(Product("Novel", 500));
        books.addProduct(Product("Biography", 700));
        books.addProduct(Product("Cookbook", 400));
        books.addProduct(Product("Children's Book", 300));
        addCategory(books);

        Category toys("Toys");
        toys.addProduct(Product("Action Figure", 600));
        toys.addProduct(Product("Building Blocks", 1000));
        toys.addProduct(Product("Doll", 500));
        toys.addProduct(Product("Board Game", 800));
        toys.addProduct(Product("Remote-Controlled Car", 1500));
        toys.addProduct(Product("Puzzle", 300));
        toys.addProduct(Product("Stuffed Animal", 400));
        toys.addProduct(Product("Toy Train", 700));
        addCategory(toys);

        Category health("Health");
        health.addProduct(Product("Multivitamins", 800));
        health.addProduct(Product("Protein Powder", 2000));
        health.addProduct(Product("Omega-3", 1200));
        health.addProduct(Product("Bandages (Box)", 100));
        health.addProduct(Product("Cough Syrup", 250));
        health.addProduct(Product("Face Mask", 50));
        health.addProduct(Product("Hand Sanitizer", 150));
        addCategory(health);

        Category furniture("Furniture");
        furniture.addProduct(Product("Sofa", 15000));
        furniture.addProduct(Product("Dining Table", 12000));
        furniture.addProduct(Product("Bookshelf", 5000));
        furniture.addProduct(Product("Wardrobe", 10000));
        furniture.addProduct(Product("Bed", 20000));
        furniture.addProduct(Product("Chair", 1500));
        furniture.addProduct(Product("Coffee Table", 4000));
        furniture.addProduct(Product("Desk", 6000));
        addCategory(furniture);
        saveProductsToFile();
    }

   
    void adminMenu() {
        string inputPassword;
        string adminPassword;
        ifstream readPass("admin_password.txt");

        if (readPass.is_open()) {
            getline(readPass, adminPassword);
            readPass.close();
        }
        else {
            adminPassword = "oop";
            ofstream createFile("admin_password.txt");
            createFile << adminPassword;
            createFile.close();
        }

        while (true) {
            system("cls");
            system("color E0");
            cout << "======================================================" << endl;
            cout << "                   ADMIN LOGIN PANEL                 " << endl;
            cout << "======================================================" << endl;
            cout << endl << "Please enter the admin password to continue." << endl << endl;
            cout << "Password: ";
            cin >> inputPassword;

            if (inputPassword != adminPassword) {
                cout << endl << "------------------------------------------------------" << endl;
                cout << "Incorrect password. Access Denied." << endl;
                cout << "------------------------------------------------------" << endl;
                char retryChoice;
                cout << endl << "Do you want to try again? (Y/N): ";
                cin >> retryChoice;

                if (retryChoice == 'n' || retryChoice == 'N') {
                    cout << endl << "Exiting admin menu..." << endl;
                    Sleep(1500);
                    return;
                }
            }
            else {
                break;
            }
        }
   
        while (true) {
            system("cls");
            system("color 3F");

            int choice;
            cout << "======================================================" << endl;
            cout << "                      ADMIN MENU                      " << endl;
            cout << "======================================================" << endl;
            cout << "1. Add Product"<<endl;
            cout << "2. Edit Product" << endl;
            cout << "3. Delete Product" << endl;
            cout << "4. View Customer Information" << endl;
            cout << "5. Change Password" << endl;
            cout << "6. Exit Admin Menu" << endl;
            cout << "7. View Customer Feedbacks"<<endl;
            cout << "------------------------------------------------------" << endl;
            cout << "Your Choice: ";
            cin >> choice;
            Beep(550, 300);
            if (choice == 1) {
                addProduct();
               Sleep(1450);
            }
            else if (choice == 2) {
                editProduct();
                Sleep(1450);
            }
            else if (choice == 7) {
                viewCustomerFeedbacks();
                Sleep(3500);
            }
            else if (choice == 3) {
                deleteProducts();
                Sleep(1450);
            }
            else if (choice == 4) {
                customerInformation();
                Sleep(3500);
            }
            else if (choice == 5) {
                passwordChange();
                Sleep(1450);
            }
            else if (choice == 6) {
                cout << endl;
                cout << "Exiting Admin Menu..." << endl;
                Sleep(1450);
                return;
            }
            else {
                cout << endl;
                cout << "Invalid input. Please enter a number between 1 and 6." << endl;
                Sleep(1450);
                break;

            }
        }

    }

    void viewCustomerFeedbacks() {
        system("cls");
        system("color 70");

        ifstream file("ratings.txt");

        if (!file.is_open()) {
            cout << "No feedback found or failed to open ratings.txt"<<endl;
            Sleep(2000);
            return;
        }

        string line;
        int count = 1;
        cout << endl;
        cout << "\t\t  --- Customer Feedbacks ---";
          cout << endl << endl;
        while (getline(file, line)) {
            cout << count++ << ". " << line << endl;
        }

        file.close();
        
    }

    void addProduct() {
        int categoryIndex;
        string productName;
        float productPrice;

        cout << "Enter the category index to add a product: ";
        cin >> categoryIndex;
        if (categoryIndex < 0 || categoryIndex > categoryCount) {
            cout << "Invalid category index.";
            cout << endl;
            return;
        }

        cout << "Enter the product name: ";
        cin.ignore();
        getline(cin, productName);
        cout << "Enter the product price: ";
        cin >> productPrice;

        categories[categoryIndex-1].addProduct(Product(productName, productPrice));
        saveProductsToFile();
        cout << "Product added successfully.";
        cout << endl;
    }

    void editProduct() {
        int categoryIndex;
        int  productIndex;
        string productName;
        float productPrice;

        cout << "Enter the category index to edit a product: ";
        cin >> categoryIndex;
        if (categoryIndex < 0 || categoryIndex > categoryCount) {
            cout << "Invalid category index.";
            cout << endl;
            return;
        }

        cout << "Enter the product index to edit: ";
        cin >> productIndex;
        if (productIndex < 1 || productIndex > categories[categoryIndex].productCount) {
            cout << "Invalid product index.";
            cout << endl;
            return;
        }

        cout << "Enter the new product name: ";
        cin.ignore();
        getline(cin, productName);

        cout << "Enter the new product price: ";
        cin >> productPrice;

        categories[categoryIndex-1].editProduct(productIndex - 1, Product(productName, productPrice));
        saveProductsToFile();
        cout << "Product edited successfully."<<endl;
    }
    void deleteProducts() {
        int productIndex;
        int categoryIndex;

        cout << "Enter the category index to delete a product: ";
        cin >> categoryIndex;
        Beep(550, 300);
        if (categoryIndex < 1 || categoryIndex > categoryCount) { 
            cout << "Invalid category index." << endl;
            return;
        }

        cout << "Enter the product index to delete: ";
        cin >> productIndex;
        Beep(550, 300);
        if (productIndex < 1 || productIndex > categories[categoryIndex - 1].productCount) {  
            cout << "Invalid product index." << endl;
            return;
        }

        categories[categoryIndex - 1].deleteProduct(productIndex - 1);  
        saveProductsToFile();
        cout << "Product deleted successfully." << endl;
    }

   
    void customerInformation() const {
        ifstream file("record.csv");
        string line;
        cout << "Customer Information:"<<endl;
        while (getline(file, line)) {
            cout << line << endl;
        }
    }

    void passwordChange() {
        string newPassword;
        string confirmPassword;

        cout << "Enter the new password: ";
        cin >> newPassword;

        cout << "Confirm the new password: ";
        cin >> confirmPassword;

        if (newPassword == confirmPassword) {
            ofstream writePass("admin_password.txt");
            if (writePass.is_open()) {
                writePass << newPassword;
                writePass.close();
                cout << "Password changed successfully."<<endl;
            }
            else {
                cout << "Error saving the new password."<<endl;
            }
        }
        else {
            cout << "Passwords do not match. Try again."<<endl;
        }
    }

};
void typeText(const string& text, int delay = 30) {
    for (int i = 0; text[i] != '\0'; i++) {
        cout << text[i];
        Sleep(delay);
    }

    cout << endl;
}
class Feedback {
protected:
    string userName;
    string comment;
public:
    Feedback() {
        userName = "Anonymous";
        comment = "";
    }

    virtual void getFeedback() {
        cout << "Enter your name or simply press Enter if you want to keep your identity hidden : ";
        getline(cin, userName);
        if (userName == "") {
            userName = "Anonymous";
        }

        cout << "Enter any comments about your shopping experience: ";
        getline(cin, comment);
    }

    virtual void displayFeedback() const {
        cout << "Feedback by " << userName << ":" << endl;
        cout<< comment << endl;
    }

   
};
class Rating : public Feedback {
private:
    int stars;  
public:
    Rating() {
        stars = 0;
    }

    void getFeedback() override {
      
        system("color 9F");
        cout << "\n\n\t\t\t";
        typeText("We'd love your feedback!", 40);
        cout << "\t\t\t";
        typeText("---------------------------------", 15);
        cout << "\t\t\t";
        typeText("Please tell us about your experience.", 35);
        cout << endl << endl;
        typeText("Enter your name: ", 30);
        getline(cin, userName);

        typeText("Write your feedback/comment: ", 30);
        getline(cin, comment);

        while (true) {
            typeText("Rate your shopping experience (1 to 5 stars): ", 30);
            cin >> stars;

            if (stars >= 1 && stars <= 5) {
                break;
            }
            typeText("Invalid input. Please enter a value between 1 and 5.", 25);
        }

        cin.ignore();  
    }


    /*void displayFeedback() const override {
        Feedback::displayFeedback();
        cout << "Rating: " << string(stars, '*') << " (" << stars << " stars)";
        cout << endl;
    }*/

    void saveToFile() const {
        ofstream file("ratings.txt", ios::app);
        if (file.is_open()) {
            file << userName << "," << stars << "," << comment << endl;
            file.close();
        }
        else {
            cout << "Error saving rating to file.";
            cout << endl;
        }
    }
};



int main() {
    
    Store store;
    bool flag = true;
   store.populateStore();

    while (flag) {
        store.displayLoadingScreen();
        system("cls");

        system("color 70"); 
        cout << "\n\n\t\t\t\t";
        typeText("Welcome to Our Online Store!", 50);
        cout << "\t\t\t\t";
        typeText("------------------------------------", 10);
        cout << "\t\t\t\t  ";
        typeText("Your one-stop shop for all your needs.", 30);
        cout << endl << endl;

        cout << "\t\t\t\tSelect an option to continue:";
        cout << endl << endl;
        cout << "\t\t\t\t1. Browse Categories and Shop"<<endl;
        cout << "\t\t\t\t2. Admin Login (For Store Management)"<<endl;
        cout << "\t\t\t\t3. Exit the Store"<<endl;
        cout << "\t\t\t\t4. View Cart & Checkout" << endl;
        cout << "\t\t\t\t5. Rate Our Online Shopping Experience "<<endl;

        cout << endl << endl;
        cout << "\t\t\t\tEnter your choice (1, 2,3 or 4): ";

        int choice;
        cin >> choice;
        Beep(550, 300);

        if (choice == 3) {
            cout << endl;
            typeText("Thank you for visiting our store!We hope to see you again soon.", 35);
            return 0;
        }
        else if (choice == 2) {
            store.adminMenu();
        }
        else if (choice == 4) {
            store.viewCart();
            break;
        }
        else if (choice == 5) {
            system("cls");
            cin.ignore(); 
            Rating rate;
            rate.getFeedback();
            rate.displayFeedback();
            rate.saveToFile();
            cout << endl;
            cout << "Thank you for your valuable feedback!" << endl;;
            Sleep(2500);
        }


        else if (choice == 1) {
            store.displayCategories();
        }

        else {
            cout << endl;
            cout << "Invalid choice! Please select a valid option (1, 2, or 3)." << endl;
            Sleep(1500);
        }
    }
}



