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

int main() {
    TransportationSystem system;
    
    // Inisialisasi data awal
    system.initializeDefaultData();
    
    int choice;
    string from, to, location, route;
    double distance, time, cost;
    
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
                system.addLocation(location);
                cout << "Lokasi berhasil ditambahkan!" << endl;
                break;
                
            case 3:
                cout << "Lokasi asal: ";
                getline(cin, from);
                cout << "Lokasi tujuan: ";
                getline(cin, to);
                cout << "Jarak (km): ";
                cin >> distance;
                cout << "Waktu (menit): ";
                cin >> time;
                cout << "Biaya (Rp): ";
                cin >> cost;
                
                system.addRoute(from, to, distance, time, cost);
                cout << "Rute berhasil ditambahkan!" << endl;
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
                cout << "Terima kasih telah menggunakan sistem!" << endl;
                return 0;
                
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    }
    
    return 0;
}
