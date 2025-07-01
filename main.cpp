#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <climits>
#include <iomanip>
#include "TransportationSystem.h"

using namespace std;

void displayMenu() {
    cout << "\n=== SISTEM REKOMENDASI RUTE TRANSPORTASI ===" << endl;
    cout << "1. Tampilkan Graf Lokasi" << endl;
    cout << "2. Tambah Lokasi" << endl;
    cout << "3. Tambah Rute" << endl;
    cout << "4. Hapus Lokasi" << endl;
    cout << "5. Hapus Rute" << endl;
    cout << "6. Cari Rute Terbaik" << endl;
    cout << "7. Set Preferensi Pengguna" << endl;
    cout << "8. Simulasi Perjalanan" << endl;
    cout << "9. Simpan Data ke File" << endl;
    cout << "10. Muat Data dari File" << endl;
    cout << "11. Tampilkan Decision Tree" << endl;
    cout << "0. Keluar" << endl;
    cout << "Pilihan: ";
}

RouteType selectRouteType() {
    int opsi;
    cout << "\nJenis Rute:\n";
    cout << "1. Biasa (kecepatan sedang, biaya sedang)\n";
    cout << "2. Tol (cepat tapi mahal)\n";
    cout << "3. Rusak (lambat dan mahal)\n";
    cout << "4. Gunung (sangat lambat, biaya rendah)\n";
    cout << "Pilih jenis rute (1-4): ";
    cin >> opsi;
    cin.ignore();

    switch (opsi) {
        case 2: return RouteType::TOL;
        case 3: return RouteType::RUSAK;
        case 4: return RouteType::GUNUNG;
        default: return RouteType::BIASA;
    }
}

int main() {
    TransportationSystem system;
    system.initializeDefaultData();

    int choice;
    string from, to, location;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                system.displayGraph();
                break;

            case 2:
                cout << "Masukkan nama lokasi baru: ";
                getline(cin, location);
                double x, y;
                cout << "Masukkan koordinat x: ";
                cin >> x;
                cout << "Masukkan koordinat y: ";
                cin >> y;
                cin.ignore();
                system.addLocation(location);
                system.setLocationCoordinates(location, x, y);
                cout << "Lokasi berhasil ditambahkan!\n";
                break;

            case 3:
                cout << "Lokasi asal: ";
                getline(cin, from);
                cout << "Lokasi tujuan: ";
                getline(cin, to);
                system.addRoute(from, to, selectRouteType());
                cout << "Rute berhasil ditambahkan!\n";
                break;

            case 4:
                cout << "Masukkan nama lokasi yang akan dihapus: ";
                getline(cin, location);
                system.removeLocation(location);
                break;

            case 5:
                cout << "Lokasi asal: ";
                getline(cin, from);
                cout << "Lokasi tujuan: ";
                getline(cin, to);
                system.removeRoute(from, to);
                break;

            case 6:
                cout << "Lokasi asal: ";
                getline(cin, from);
                cout << "Lokasi tujuan: ";
                getline(cin, to);
                system.findBestRoute(from, to);
                break;

            case 7:
                system.setUserPreferences();
                break;

            case 8:
                cout << "Lokasi asal: ";
                getline(cin, from);
                cout << "Lokasi tujuan: ";
                getline(cin, to);
                system.simulateJourney(from, to);
                break;

            case 9:
                system.saveToFile("transportation_data.txt");
                break;

            case 10:
                system.loadFromFile("transportation_data.txt");
                break;

            case 11:
                system.displayDecisionTree();
                break;

            case 0:
                cout << "Terima kasih telah menggunakan sistem!\n";
                return 0;

            default:
                cout << "Pilihan tidak valid!\n";
        }
    }

    return 0;
}
