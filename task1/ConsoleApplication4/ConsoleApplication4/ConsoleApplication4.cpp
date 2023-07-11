#include <iostream>
#include <fstream>
#include <string>

struct Resident {
    std::string name;
    int apartmentNumber;
};

struct Floor {
    int number;
    Resident residents[100];
    int residentCount;
};

void addResident(Floor& floor) {
    std::cout << "Enter resident name: ";
    std::string name;
    std::cin >> name;

    std::cout << "Enter apartment number: ";
    int apartmentNumber;
    std::cin >> apartmentNumber;

    Resident resident;
    resident.name = name;
    resident.apartmentNumber = apartmentNumber;

    floor.residents[floor.residentCount++] = resident;

    std::cout << "Resident added successfully.\n";
}

void removeResident(Floor& floor) {
    std::cout << "Enter apartment number: ";
    int apartmentNumber;
    std::cin >> apartmentNumber;

    Resident* residents = floor.residents;
    int residentCount = floor.residentCount;

    for (int i = 0; i < residentCount; i++) {
        if (residents[i].apartmentNumber == apartmentNumber) {
            // Remove resident by shifting elements
            for (int j = i; j < residentCount - 1; j++) {
                residents[j] = residents[j + 1];
            }

            floor.residentCount--;
            std::cout << "Resident removed successfully.\n";
            return;
        }
    }

    std::cout << "Resident not found.\n";
}

void addApartment(Floor& floor) {
    std::cout << "Enter floor number: ";
    int floorNumber;
    std::cin >> floorNumber;

    floor.number = floorNumber;

    std::cout << "Apartment added successfully.\n";
}

void removeApartment(Floor& floor) {
    floor.number = 0;
    floor.residentCount = 0;

    std::cout << "Apartment removed successfully.\n";
}

void assignResident(Floor& floor) {
    std::cout << "Enter resident name: ";
    std::string name;
    std::cin >> name;

    std::cout << "Enter apartment number: ";
    int apartmentNumber;
    std::cin >> apartmentNumber;

    Resident* residents = floor.residents;
    int residentCount = floor.residentCount;

    for (int i = 0; i < residentCount; i++) {
        if (residents[i].name == name) {
            residents[i].apartmentNumber = apartmentNumber;
            std::cout << "Resident assigned to apartment successfully.\n";
            return;
        }
    }

    std::cout << "Resident not found.\n";
}

void unassignResident(Floor& floor) {
    std::cout << "Enter resident name: ";
    std::string name;
    std::cin >> name;

    Resident* residents = floor.residents;
    int residentCount = floor.residentCount;

    for (int i = 0; i < residentCount; i++) {
        if (residents[i].name == name) {
            residents[i].apartmentNumber = 0;
            std::cout << "Resident unassigned from apartment successfully.\n";
            return;
        }
    }

    std::cout << "Resident not found.\n";
}

void saveData(const Floor& floor) {
    std::ofstream file("data.txt");

    if (file.is_open()) {
        file << floor.number << std::endl;
        file << floor.residentCount << std::endl;

        for (int j = 0; j < floor.residentCount; j++) {
            const Resident& resident = floor.residents[j];
            file << resident.name << std::endl;
            file << resident.apartmentNumber << std::endl;
        }

        file.close();
        std::cout << "Data saved successfully.\n";
    }
    else {
        std::cout << "Unable to save data.\n";
    }
}

void loadData(Floor& floor) {
    std::ifstream file("data.txt");

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
        std::cout << "Data loaded successfully.\n";
    }
    else {
        std::cout << "Unable to load data.\n";
    }
}

void generateReport(const Floor& floor) {
    std::cout << "Report for Floor " << floor.number << ":" << std::endl;

    for (int i = 0; i < floor.residentCount; i++) {
        const Resident& resident = floor.residents[i];
        std::cout << "Resident Name: " << resident.name << ", Apartment Number: " << resident.apartmentNumber << std::endl;
    }
}

void displayAllResidents(const Floor& floor) {
    std::cout << "All Residents:\n";

    for (int j = 0; j < floor.residentCount; j++) {
        const Resident& resident = floor.residents[j];
        std::cout << "Resident Name: " << resident.name << ", Apartment Number: " << resident.apartmentNumber << std::endl;
    }
}

void displayAllApartments(const Floor& floor) {
    std::cout << "All Apartments:\n";

    for (int j = 0; j < floor.residentCount; j++) {
        const Resident& resident = floor.residents[j];
        std::cout << "Apartment Number: " << resident.apartmentNumber << std::endl;
    }
}

void displayApartmentInfo(const Floor& floor, int apartmentNumber) {
    for (int i = 0; i < floor.residentCount; i++) {
        const Resident& resident = floor.residents[i];

        if (resident.apartmentNumber == apartmentNumber) {
            std::cout << "Apartment Number: " << resident.apartmentNumber << ", Resident Name: " << resident.name << std::endl;
            return;
        }
    }

    std::cout << "Apartment not found.\n";
}

void displayFloorApartments(const Floor& floor) {
    std::cout << "Apartments on Floor " << floor.number << ":" << std::endl;

    for (int i = 0; i < floor.residentCount; i++) {
        const Resident& resident = floor.residents[i];
        std::cout << "Apartment Number: " << resident.apartmentNumber << ", Resident Name: " << resident.name << std::endl;
    }
}

void displayApartmentsOfType(const Floor& floor, int type) {
    std::cout << "Apartments of Type " << type << ":" << std::endl;

    for (int i = 0; i < floor.residentCount; i++) {
        const Resident& resident = floor.residents[i];

        if (resident.apartmentNumber % 10 == type) {
            std::cout << "Apartment Number: " << resident.apartmentNumber << ", Resident Name: " << resident.name << std::endl;
        }
    }
}

int main() {
    Floor floor;
    floor.residentCount = 0;

    int choice;
    do {
        std::cout << "1. Add resident\n";
        std::cout << "2. Remove resident\n";
        std::cout << "3. Add apartment\n";
        std::cout << "4. Remove apartment\n";
        std::cout << "5. Assign resident to apartment\n";
        std::cout << "6. Unassign resident from apartment\n";
        std::cout << "7. Save data\n";
        std::cout << "8. Load data\n";
        std::cout << "9. Generate report for floor\n";
        std::cout << "10. Display all residents\n";
        std::cout << "11. Display all apartments\n";
        std::cout << "12. Display apartment info\n";
        std::cout << "13. Display floor apartments\n";
        std::cout << "14. Display apartments of type\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

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
            std::cout << "Enter apartment number: ";
            std::cin >> apartmentNumber;
            displayApartmentInfo(floor, apartmentNumber);
            break;
        case 13:
            displayFloorApartments(floor);
            break;
        case 14:
            int apartmentType;
            std::cout << "Enter apartment type: ";
            std::cin >> apartmentType;
            displayApartmentsOfType(floor, apartmentType);
            break;
        case 0:
            std::cout << "Exiting the program.\n";
            break;
        default:
            std::cout << "Invalid choice.\n";
            break;
        }

        std::cout << std::endl;
    } while (choice != 0);

    return 0;
}
