#include<iostream>
#include<assert.h>
#include<string>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include <Windows.h>
//#include <nlohmann/json.hpp>

//using json = nlohmann::json;
using namespace std;

template<class T>
class Stack {
    T* data;
    size_t size = 0;
public:

    Stack() :data(NULL), size(NULL) {}

    void Push(const T& newdata) {
        auto newarray = new T[size + 1]{};
        for (int i = 0; i < size; i++) {
            newarray[i] = data[i];
        }
        newarray[size] = newdata;
        if (size != 0) {
            delete[]data;
        }
        data = newarray;
        newarray = nullptr;
        ++size;
    }
    void Pop(int index = -1) {
        if (index != -1) {
            auto newitems = new T[size - 1]{};
            for (int i = 0; i < index; i++) {
                newitems[i] = data[i];
            }
            int index1 = index + 1;
            int index2 = index;
            for (int i = 0; i < size - (index + 1); i++) {
                newitems[index2] = data[index1];
                index1++;
                index2++;
            }
            data = newitems;
            newitems = nullptr;
            size -= 1;
        }
        else {
            auto newitems = new T[size - 1]{};
            for (int i = 0; i < size - 1; i++) {
                newitems[i] = data[i];
            }
            data = newitems;
            newitems = nullptr;
            size -= 1;
        }
    }
    int Peek()const {
        assert(size > 0 && "Empty Stack");
        return data[size - 1];
    }
    void Clear() {
        if (this->data == NULL || this->size == NULL) {
            return;
        }
        delete[]data;
        this->data = NULL;
        this->size = NULL;
    }
    void Show()const {
        for (int i = 0; i < size; i++) {
            cout << data[i] << endl;
        }
    }
    size_t GetSize()const {
        return size;
    }
    auto& operator[](int index) {
        assert(index >= 0 && index <= size && "Invalid Index");
        return data[index];
    }

};


class Food {
    string name;
    double price;
    int id;
    int count;
public:
    static int staticId;
    Food() = default;
    Food(const string& name, const double& price, const int& count) {
        SetId(++staticId);
        SetName(name);
        SetPrice(price);
        SetCount(count);
    }
    void SetId(const int& id) {
        this->id = id;
    }
    void SetCount(const int& count) {
        if (count < 0) {
            throw exception("Count of product should be greater than 0 ");
        }
        else {
            this->count = count;
        }
    }
    void SetName(const string& name) {
        assert(!name.empty() && "Name of product is null");
        
            this->name = name;
    }

    void SetPrice(const double& price) {
        assert(price >= 0 && "Price of product should be more than 0");
        this->price = price;
    }
    double GetPrice()const {
        return price;
    }
    int GetCount()const {
        return count;
    }

    int GetId()const {
        return id;
    }
    string GetName()const {
        return name;
    }
    friend ostream& operator<<(ostream& out, const Food& products);
};

int Food::staticId = 0;

ostream& operator<<(ostream& out, const Food& products) {
    out << "Id: " << products.GetId() << endl << endl;
    out << "Name of the product: " << products.name << endl;
    out << "Price of the product: " << products.price << endl;
    out << "Count of tthe product: " << products.count << endl;
    return out;
}

class Meal {
    int id;
    double price;
    Stack<Food>products;
    string name;
    double allCalories;
public:
    static int staticId;
    Meal() = default;
    Meal(const double& price, const string& name) {
        SetId(++staticId);
        SetName(name);
        SetPrice(price);
    }
    void SetName(const string& name) {
        assert(!name.empty() && "Name of meal is null");
        this->name = name;
    }
    void SetPrice(const double& price) {
        assert(price > 0 && "Price of meal should be more than 0");
        this->price = price;
    }
    void SetId(const int& id) {
        this->id = id;
    }
    int GetId()const {
        return id;
    }
    double GetPrice()const {
        return price;
    }
    string GetName()const {
        return name;
    }
    void AddProduct(Food& product) {
        products.Push(product);
    }

    Food* GetProductById(int id) {
        for (int i = 0; i < products.GetSize(); i++) {
            if (products[i].GetId() == id) {
                return &products[id];
            }
        }
    }
    void UpdateProduct() {
        cout << "Enter id of meal: " << endl;
        int id;
        cin >> id;
        auto products = GetProductById(id);
        cout << "1.Ingredient name \n";
        cout << "2.Ingredient price  \n";
        cout << "3.Ingredient count \n\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            cin.ignore();
            cin.clear();
            cout << "Enter name: ";
            string name;
            getline(cin, name);
            products->SetName(name);
        }
        else if (choice == 2) {
            cout << "Enter price: ";
            double price;
            cin >> price;
            products->SetPrice(price);
        }
        else if (choice == 3) {
            cout << "Enter count: ";
            int count;
            cin >> count;
            products->SetCount(count);
        }


    }
    void ShowIngredientofMEal() {
        products.Show();
    }
    friend ostream& operator<<(ostream& out, Meal& meal) {
        out << "Id: " << meal.GetId() << endl << endl;
        out << "Name of meal: " << meal.name << endl << endl;
        meal.products.Show();
        return out;
    }
};
int Meal::staticId = 0;

class Kitchen :public Meal {
public:
    Stack<Meal>meals;
    static int notificationCount;

    Kitchen() = default;
    

    void AddMeal(Meal& meal) {
        meals.Push(meal);
    }
    void Show()const {
        meals.Show();
    }
    void ShowName() {
        for (int i = 0; i < meals.GetSize(); i++) {
            cout << meals[i].GetId() << ". " << meals[i].GetName() << " - " << meals[i].GetPrice() << " $" << endl << endl;
        }
    }
    void ShowMealById(int id) {
        for (int i = 0; i < meals.GetSize(); i++) {
            if (meals[i].GetId() == id) {
                cout << meals[i] << endl;
            }
        }
    }
    Meal* GetMealById(int id) {
        for (int i = 0; i < meals.GetSize(); i++) {
            if (meals[i].GetId() == id) {
                return &meals[i];
            }
        }
    }
    void MealsPop(int index) {
        meals.Pop(index);
    }

    int GetMealCount() {
        return meals.GetSize();
    }
    void AddMeal() {
        cin.ignore();
        cin.clear();
        cout << "Enter name : ";
        string name;
        cin >> name;
        // getline(cin, name);

        cout << "Enter price: ";
        double price;
        cin >> price;
        cout << endl;
        Meal newMeal(price, name);
        cout << "P R O D U C T   C O U N T: ";
        int count;
        cin >> count;
        for (int i = 0; i < count; i++) {
            cout << "Enter " << i << " product name: ";
            string productName;
            getline(cin, productName);
            cout << "Enter " << i << " product price: ";
            double price;
            cin >> price;
            cout << "Enter " << i << " product count: ";
            int count;
            cin >> count;
            Food prdct(name, price, count);
            newMeal.AddProduct(prdct);
        }
        meals.Push(newMeal);
        cout << "Meal added successfully :)" << endl;
    };
    void UptadeMeals(int id) {
        auto meal = GetMealById(id);
        cout << "1. Name\n";
        cout << "2. Price\n";
        cout << "3. Products\n\n";
        cout << "Enter select: ";
        int select;
        cin >> select;
        if (select == 1) {
            cin.ignore();
            cin.clear();
            cout << "Enter meal name: ";
            string name;
            getline(cin, name);
            meal->SetName(name);
        }
        else if (select == 2) {
            cout << "Enter meal price: ";
            double price;
            cin >> price;
            meal->SetPrice(price);
        }
        else if (select == 3) {
            meal->ShowIngredientofMEal();
            meal->UpdateProduct();
        }
    }
};


class Warehouse {
    Stack<Food>goods;
public:
    Warehouse() = default;
    void AddIngredient(Food& product) {
        goods.Push(product);
    }
    void Show() {
        int id = 1;
        cout << "~~~~~  A L L   P R O D U C T S ~~~~~" << endl << endl;
        for (int i = 0; i < goods.GetSize(); i++) {
            cout << "Id: " << id++ << endl << endl;
            cout << goods[i] << endl << endl;
        }
    }
    auto* GetProductById(int index) {
        for (int i = 0; i < goods.GetSize(); i++) {
            if (goods[i].GetId() == index) {
                return &goods[i];
            }
        }
    }
    int GetFoodCount() {
        return goods.GetSize();
    }
    bool FoodCount(int index, int count) {
        auto product = GetProductById(index);
        int temp = product->GetCount() - count;
        if (temp >= 0) {
            goods[index].SetCount(temp);
            return true;
        }
        return false;
    }
    void DeleteIngredientById(int index = -1) {
        goods.Pop(index);
    }
    void ShowFoodCount() {
        for (int i = 0; i < goods.GetSize(); i++) {
            cout << goods[i].GetId() << " - " << goods[i].GetName() << " count " << goods[i].GetCount() << endl << endl;
        }
    }
    
};

class User {
    string tableNo;
    Stack<Kitchen>menu;
public:
    User() = default;
    User(const string& tableNo) {
        SetTable(tableNo);
    }
    void SetTable(const string& tableNo) {
        assert(!tableNo.empty() && "Table should not be empty");
        this->tableNo = tableNo;
    }
    string GetTableNo()const {
        return tableNo;
    }
    void AddMenu(Kitchen& kitchen) {
        menu.Push(kitchen);
    }
    void ShowMenu() {
        for (int i = 0; i < menu.GetSize(); i++) {
            menu[i].ShowName();
        }
    }
};

class MyException {
    string message;
public:
    MyException(string message) { 
        this->message = message; 
    }
    string Message() const { 
        return message;
    }
};

class NullReferenceException : public MyException {
public:
    NullReferenceException(string message) : MyException(message) {}
};

class OutOfRangeException : public MyException {
public:
    OutOfRangeException(string message) : MyException(message) {}
};

class ArgumentException : public MyException {
public:
    ArgumentException(string message) : MyException(message) {}
};

class ArgumentNullException : public ArgumentException {
public:
    ArgumentNullException(string message) : ArgumentException(message) {}
};

class ArgumentInvalidException : public ArgumentException {
public:
    ArgumentInvalidException(string message) : ArgumentException(message) {}
};



void main() {
    Food food1("Tomato", 0.7, 20);
    Food food2("Olive", 0.3, 35);
    Food food3("Mushroom", 1.2, 20);
    Food food4("Flour", 1.8, 40);
    Food food5("Cheese", 2.1, 15);
    Food food6("Cucumber", 1.0, 18);
    Warehouse stock;
    stock.AddIngredient(food1);
    stock.AddIngredient(food2);
    stock.AddIngredient(food3);
    stock.AddIngredient(food4);
    stock.AddIngredient(food5);
    Meal pizza(20, "Vegetarian Pizza");
    pizza.AddProduct(food1);
    pizza.AddProduct(food2);
    pizza.AddProduct(food3);
    pizza.AddProduct(food4);
    pizza.AddProduct(food5);
    Meal salad(9, "Mushroom salad");
    salad.AddProduct(food1);
    salad.AddProduct(food2);
    salad.AddProduct(food5);
    Kitchen k;
    k.AddMeal(pizza);
    k.AddMeal(salad);
    User c("T-20");
    c.AddMenu(k);

    double totalPrice = 0;

    while (true) {

        system("cls");
        system("Color 3E");

        cout << "\t\t  ~~~~~W E L C O M E~~~~~\n";
        cout << "\t\t~~~~~E M E N   C A F E~~~~~\n";
        cout << "\t~~~~~Choice: \n";
        cout << "\t{1}~~~~~Admin\n";
        cout << "\t{2}~~~~User\n\n";
        cout << "\tEnter your choice: ";
        string choice;
        cin >> choice;

        if (choice == "1") {
            system("cls");
            cout << "PLEASE LOGIN " << endl;
            while (true) {
                cin.ignore();
                cin.clear();
                cout << "Enter username: ";
                string username;
                getline(cin, username);
                system("cls");
                cout << "Enter password: ";
                string password;
                getline(cin, password);
                cout << endl;
                if (username == "Nigar") {
                    if (password == "1r2a3g4i5N6") {
                        system("cls");
                        cout << "~~~~~~~~~~~~~~~~~ W E L C O M E   A D M I N ~~~~~~~~~~~~~~~~~" << endl;
                        cout << "1. K I T C H E N \n\n";
                        cout << "2. S T O C K   \n\n";
                        cout << "3. F I N I S H \n\n\n";
                        cout << "Enter your choice: ";
                        int adminChoice = 0;
                        cin >> adminChoice;
                        if (adminChoice == 1) {
                            system("cls");
                            cout << "~~~~~~~  K I T C H E N  ~~~~~~~" << endl;
                            k.ShowName();
                            cout << "1. Delete meal \n\n";
                            cout << "2. Update meal\n\n";
                            cout << "3. Add meal\n\n\n";
                            cout << "Enter your choice : ";
                            int changeMealChoice;
                            cin >> changeMealChoice;
                            if (changeMealChoice == 1) {
                                while (true) {
                                    cout << "Enter ID of meal: ";
                                    int id;
                                    cin >> id;
                                    if (k.GetMealCount() >= id) {
                                        --id;
                                        k.MealsPop(id);
                                        system("cls");
                                        k.ShowName();
                                        cout << "Meal deleted successfully!!!" << endl;
                                        break;
                                    }
                                    else {
                                        cout << "Meal does not found!" << endl;
                                    }
                                }
                            }
                            else if (changeMealChoice == 2) {
                                k.UpdateProduct();
                                k.Show();
                            }
                            else if (changeMealChoice == 3) {
                                k.ShowName();
                                k.AddMeal();
                            }
                        }
                        else if (adminChoice == 2) {
                            system("cls");
                            cout << "~~~~~~ S T O C K ~~~~~~\n\n";
                            cout << "1. Show Ingredients\n\n";
                            cout << "2. Add Ingredients\n\n";
                            cout << "3. Update ingredients count\n\n";
                            cout << "4. Delete Ingredients\n\n";
                            cout << "5. BACK\n\n\n";
                            cout << "Your choice: ";
                            int changeIngredients;
                            cin >> changeIngredients;
                            if (changeIngredients == 1) {
                                system("cls");
                                stock.Show();
                                system("pause");
                            }
                            else if (changeIngredients == 2) {
                                system("cls");
                                cin.ignore();
                                cin.clear();
                                cout << "Enter name of ingredient: ";
                                string name;
                                getline(cin, name);
                                cout << "Enter price of  ingredient: ";
                                double price;
                                cin >> price;
                                cout << "Enter count of ingredient: ";
                                int count;
                                cin >> count;
                                Food p(name, price, count);
                                stock.AddIngredient(p);
                                system("cls");
                                cout << "Ingredient added successfully :)" << endl;
                                system("pause");
                                system("cls");
                            }
                            else if (changeIngredients == 3) {
                                system("cls");
                                stock.ShowFoodCount();
                                cout << "Enter id of ingredient: ";
                                int id1;
                                cin >> id1;
                                Food* p = stock.GetProductById(id1);
                                cout << "Enter new count: ";
                                int count;
                                cin >> count;
                                p->SetCount(count);
                                cout << "Count uptaded successfully :)" << endl;
                                system("pause");
                                system("cls");
                            }
                            else if (changeIngredients == 4) {
                                system("cls");
                                stock.Show();
                                cout << "Which ingredient did you choose? ";
                                int id;
                                cin >> id;
                                --id;
                                stock.DeleteIngredientById(id);
                                system("cls");
                                cout << "Ingredient deleted successfully..." << endl;
                                system("pause");
                                system("cls");
                            }
                            
                            else if (changeIngredients == 5) {
                                break;
                            }
                            else {
                                cout << "Invalid choice!!!" << endl;
                                system("pause");
                                system("cls");
                            }

                        }
                        else if (adminChoice == 3) {
                            system("cls");
                            cout << "\n";
                            cout << "You finished your choice, if you want try again something\n\n" << "Click 'Enter' button to start again !!!\n\n\n";
                            break;  
                        }
                    }

                    else {
                        cout << "Wrong password!!!" << endl;
                    }
                }

                else {
                    cout << "Wrong username!!!" << endl;
                }
            }
        }


        else if (choice == "2") {
            system("cls");
            cout << "\tYou have to login...\n";
            string username;
            cout << "Enter username: ";
            cin >> username;
            Sleep(1000);
            system("cls");
            c.ShowMenu();
            cout << "Enter your meal choice to view: ";
            int mealChoice;
            cin >> mealChoice;
            cout << endl;
            k.ShowMealById(mealChoice);
            cout << "1. Order;\n";
            cout << "2. Add ingredients;\n\n";
            cout << "Enter your choice: ";
            int userChoice;
            cin >> userChoice;
            if (userChoice == 1) {
                cout << "Enter meal count: ";
                int count;
                cin >> count;
                if (count > 0) {
                    auto meal = k.GetMealById(mealChoice);
                    totalPrice += count * meal->GetPrice();
                    cout << "Total price: " << totalPrice << " $" << endl;
                    cout << "1. Continue;\n";
                    cout << "2. Finish;\n\n";
                    cout << "Select : ";
                    int select;
                    cin >> select;
                    if (select == 1) {
                    }
                }
            }
            else if (userChoice == 2) {
                cout << endl;
                cout << "1.Show ingredients\n ";
                stock.Show();
                cout << "Enter ingredients id: ";
                int id;
                cin >> id;
                auto product = stock.GetProductById(id);
                cout << product << endl;
                cout << "Enter " << product->GetName() << " count: ";
                double count;
                cin >> count;
                if (stock.FoodCount(id, count)) {
                    auto meal = k.GetMealById(mealChoice);
                    meal->AddProduct(*product);
                    totalPrice += meal->GetPrice();
                    totalPrice += product->GetPrice() * count;
                    cout << "\n" << meal << endl;
                    cout << "Ingredients added successfully :)" << endl << endl;
                    cout << "Total price: " << totalPrice << " $" << endl;
                }
                else {
                    auto meal = k.GetMealById(mealChoice);
                    totalPrice += meal->GetPrice();
                    cout << "Ingredients is out of stock" << endl;
                }
            }
            else {
                cout << "Your choice is impossible!!!\n";
            }
        }
        else {
            cout << "Invalid choice!!!\nPlease try again!" << endl;
        }
        system("pause");
    }
}

