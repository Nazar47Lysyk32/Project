#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Resident {
    string name;
    int apartmentNumber;
};

struct Floor {
    int number;
    Resident residents[100];
    int residentCount;
};

void addResident(Floor& floor) {
    cout << "Enter resident name: "; //Введіть ім'я мешканця:
    string name;
    cin >> name;

    cout << "Enter apartment number: "; //Введіть номер квартири:
    int apartmentNumber;
    cin >> apartmentNumber;

    Resident resident;
    resident.name = name;
    resident.apartmentNumber = apartmentNumber;

    floor.residents[floor.residentCount++] = resident;

    cout << "Resident added successfully.\n"; //Резидент додано успішно.
}

void removeResident(Floor& floor) {
    cout << "Enter apartment number: "; //Введіть номер квартири:
    int apartmentNumber;
    cin >> apartmentNumber;

    Resident* residents = floor.residents;
    int residentCount = floor.residentCount;

    for (int i = 0; i < residentCount; i++) {
        if (residents[i].apartmentNumber == apartmentNumber) {
            // Remove resident by shifting elements
            for (int j = i; j < residentCount - 1; j++) {
                residents[j] = residents[j + 1];
            }

            floor.residentCount--;
            cout << "Resident removed successfully.\n";  //Мешканця успішно видалено.
            return;
        }
    }

    cout << "Resident not found.\n"; //Мешканець не знайдений
}

void addApartment(Floor& floor) {
    cout << "Enter floor number: "; //Введіть номер поверху :
    int floorNumber;
    cin >> floorNumber;

    floor.number = floorNumber;

    cout << "Apartment added successfully.\n"; //Квартира успішно додана
}

void removeApartment(Floor& floor) {
    floor.number = 0;
    floor.residentCount = 0;

    cout << "Apartment removed successfully.\n"; //Квартира успішно видалена.
}

void assignResident(Floor& floor) {
    cout << "Enter resident name: "; //Введіть ім'я мешканця:
    string name;
    cin >> name;

    cout << "Enter apartment number: "; //Введіть номер квартири:
    int apartmentNumber;
    cin >> apartmentNumber;

    Resident* residents = floor.residents;
    int residentCount = floor.residentCount;

    for (int i = 0; i < residentCount; i++) {
        if (residents[i].name == name) {
            residents[i].apartmentNumber = apartmentNumber;
            cout << "Resident assigned to apartment successfully.\n"; //Мешканець успішно закріплений за квартирою.
            return;
        }
    }

    cout << "Resident not found.\n"; //Мешканець не знайдений
}

void unassignResident(Floor& floor) {
    cout << "Enter resident name: "; //Введіть ім'я мешканця:
    string name;
    cin >> name;

    Resident* residents = floor.residents;
    int residentCount = floor.residentCount;

    for (int i = 0; i < residentCount; i++) {
        if (residents[i].name == name) {
            residents[i].apartmentNumber = 0;
            cout << "Resident unassigned from apartment successfully.\n"; //Мешканець успішно вилучений з квартири.
            return;
        }
    }

    cout << "Resident not found.\n"; //Мешканець не знайдений
}

void saveData(const Floor& floor) {
    ofstream file("data.txt");

    if (file.is_open()) {
        file << floor.number << endl;
        file << floor.residentCount << endl;

        for (int j = 0; j < floor.residentCount; j++) {
            const Resident& resident = floor.residents[j];
            file << resident.name << endl;
            file << resident.apartmentNumber << endl;
        }

        file.close();
        cout << "Data saved successfully.\n"; //Дані успішно збережено.
    }
    else {
        cout << "Unable to save data.\n"; //Не вдалося зберегти дані
    }
}

void loadData(Floor& floor) {
    ifstream file("data.txt");

    if (file.is_open()) {
        file >> floor.number;
        int residentCount;
        file >> residentCount;
        floor.residentCount = residentCount;

        for (int j = 0; j < residentCount; j++) {
            Resident& resident = floor.residents[j];
            file >> resident.name;
            file >> resident.apartmentNumber;
        }

        file.close();
        cout << "Data loaded successfully.\n"; //Дані успішно завантажено.
    }
    else {
        cout << "Unable to load data.\n"; //Не вдалося завантажити дані.
    }
}

void generateReport(const Floor& floor) {
    cout << "Report for Floor " << floor.number << ":" << endl;

    for (int i = 0; i < floor.residentCount; i++) {
        const Resident& resident = floor.residents[i];
        cout << "Resident Name: " << resident.name << ", Apartment Number: " << resident.apartmentNumber << endl;
    }
}

void displayAllResidents(const Floor& floor) {
    cout << "All Residents:\n";

    for (int j = 0; j < floor.residentCount; j++) {
        const Resident& resident = floor.residents[j];
        cout << "Resident Name: " << resident.name << ", Apartment Number: " << resident.apartmentNumber << endl;
    }
}

void displayAllApartments(const Floor& floor) {
    cout << "All Apartments:\n";

    for (int j = 0; j < floor.residentCount; j++) {
        const Resident& resident = floor.residents[j];
        cout << "Apartment Number: " << resident.apartmentNumber << endl;
    }
}

void displayApartmentInfo(const Floor& floor, int apartmentNumber) {
    for (int i = 0; i < floor.residentCount; i++) {
        const Resident& resident = floor.residents[i];

        if (resident.apartmentNumber == apartmentNumber) {
            cout << "Apartment Number: " << resident.apartmentNumber << ", Resident Name: " << resident.name << endl;
            return;
        }
    }

    cout << "Apartment not found.\n"; //Квартира не знайдена
}

void displayFloorApartments(const Floor& floor) {
    cout << "Apartments on Floor " << floor.number << ":" << endl;

    for (int i = 0; i < floor.residentCount; i++) {
        const Resident& resident = floor.residents[i];
        cout << "Apartment Number: " << resident.apartmentNumber << ", Resident Name: " << resident.name << endl;
    }
}

void displayApartmentsOfType(const Floor& floor, int type) {
    cout << "Apartments of Type " << type << ":" << endl;// тип Квартири

    for (int i = 0; i < floor.residentCount; i++) {
        const Resident& resident = floor.residents[i];

        if (resident.apartmentNumber % 10 == type) {
            cout << "Apartment Number: " << resident.apartmentNumber << ", Resident Name: " << resident.name << endl;
        }
    }
}

int main() {
    Floor floor;
    floor.residentCount = 0;

    int choice;
    do {
        cout << "1. Add resident\n"; //Додати резидента
        cout << "2. Remove resident\n"; //Видалити резидента
        cout << "3. Add apartment\n"; //Додати квартиру
        cout << "4. Remove apartment\n"; //Зняти квартиру
        cout << "5. Assign resident to apartment\n"; //записати мешканця в квартиру
        cout << "6. Unassign resident from apartment\n"; //Виписати мешканця з квартири
        cout << "7. Save data\n"; //Зберегти дані
        cout << "8. Load data\n"; //Завантажити дані
        cout << "9. Generate report for floor\n"; //Сформувати звіт для поверху
        cout << "10. Display all residents\n"; //відобразити всіх жителів
        cout << "11. Display all apartments\n"; //Показати всі квартири
        cout << "12. Display apartment info\n"; //Показати інформацію про квартиру
        cout << "13. Display floor apartments\n"; //Відображення поверхових квартир
        cout << "14. Display apartments of type\n"; //Відображення квартир типу
        cout << "0. Exit\n"; //Вихід
        cout << "Enter your choice: "; //Введіть свій вибір
        cin >> choice;

        switch (choice) {
        case 1:
            addResident(floor);
            break;
        case 2:
            removeResident(floor);
            break;
        case 3:
            addApartment(floor);
            break;
        case 4:
            removeApartment(floor);
            break;
        case 5:
            assignResident(floor);
            break;
        case 6:
            unassignResident(floor);
            break;
        case 7:
            saveData(floor);
            break;
        case 8:
            loadData(floor);
            break;
        case 9:
            generateReport(floor);
            break;
        case 10:
            displayAllResidents(floor);
            break;
        case 11:
            displayAllApartments(floor);
            break;
        case 12:
            int apartmentNumber;
            cout << "Enter apartment number: "; //Введіть номер квартири:
            cin >> apartmentNumber;
            displayApartmentInfo(floor, apartmentNumber);
            break;
        case 13:
            displayFloorApartments(floor);
            break;
        case 14:
            int apartmentType;
            cout << "Enter apartment type: "; //Введіть тип квартири:
            cin >> apartmentType;
            displayApartmentsOfType(floor, apartmentType);
            break;
        case 0:
            cout << "Exiting the program.\n"; //Вихід з програми
            break;
        default:
            cout << "Invalid choice.\n"; //Невірний вибір
            break;
        }

        cout << endl;
    } while (choice != 0);

    return 0;
}