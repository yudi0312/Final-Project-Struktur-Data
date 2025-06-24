# Final Project Struktur Data Kelompok 6
## Sistem Rekomendasi Rute Transportasi

Nama | NRP
--- | ---
Putu Yudi Nandanjaya Wiraguna	| 5027241080
Daniswara Fausta Novanto | 5027241050
Revalina Erica Permatasari | 5027241007
Ahmad Wildan Fawwaz | 5027241001	
Angga Firmansyah | 5027241062	


## Deskripsi Proyek
Sistem rekomendasi rute transportasi berbasis preferensi pengguna yang diimplementasikan menggunakan C++ dengan struktur data Graph dan Tree serta prinsip Object-Oriented Programming (OOP).

## Fitur Utama

### 1. Representasi Graf Rute (12 poin)
- Implementasi graf berbobot menggunakan adjacency list
- Memodelkan lokasi sebagai node dan koneksi sebagai edge
- Bobot meliputi jarak (km), waktu (menit), dan biaya (Rp)

### 2. Algoritma Pencarian Rute Terbaik - Dijkstra (15 poin)
- Implementasi algoritma Dijkstra untuk shortest path
- Mendukung optimasi berdasarkan:
  - Jarak terpendek
  - Waktu tercepat
  - Biaya termurah
  - Multi-kriteria dengan bobot custom

### 3. Desain Berorientasi Objek (12 poin)
- **Encapsulation**: Data dan method dikapsulasi dalam kelas
- **Inheritance**: Struktur hierarki kelas yang jelas
- **Polymorphism**: Method virtual dan overriding
- **Abstraction**: Interface yang jelas untuk setiap komponen

### 4. Estimasi Waktu Tempuh & Biaya (10 poin)
- Kalkulasi otomatis total jarak, waktu, dan biaya
- Estimasi berdasarkan data bobot dari graf

### 5. Preferensi Dinamis Pengguna (15 poin)
- **Decision Tree**: Sistem rekomendasi berbasis pertanyaan
- **Multi-kriteria**: Bobot custom untuk setiap kriteria
- Interface interaktif untuk pengaturan preferensi

### 6. CRUD Lokasi & Rute (10 poin)
- Create: Tambah lokasi dan rute baru
- Read: Tampilkan graf dan informasi rute
- Update: Modifikasi data lokasi dan rute
- Delete: Hapus lokasi dan rute

### 7. Simulasi Perjalanan (6 poin)
- Output step-by-step perjalanan
- Informasi detail setiap segmen rute
- Total waktu dan biaya perjalanan

### 8. Struktur Data Tambahan (6 poin)
- **Priority Queue**: Untuk algoritma Dijkstra
- **Unordered Map**: Manajemen node dan data
- **Vector**: Penyimpanan path dan edges
- **Map**: Manajemen bobot dan preferensi

### 9. Visualisasi Teks (7 poin)
- Tampilan graf dalam format teks
- Visualisasi Decision Tree
- Output yang mudah dipahami

### 10. Input/Output File (7 poin)
- Simpan data ke file teks
- Muat data dari file eksternal
- Format data yang terstruktur

## Struktur Kelas

```
TransportationSystem (Main Class)
├── Graph
│   ├── Node (Lokasi)
│   └── Edge (Rute)
├── UserPreferences
│   └── DecisionTree
│       └── DecisionTreeNode
└── RouteResult
```

## Cara Kompilasi dan Menjalankan

```bash```
# Kompilasi
```make```

# Atau manual
```g++ -std=c++17 -Wall -Wextra -O2 -o transportation_system main.cpp TransportationSystem.cpp```

# Menjalankan
```./transportation_system```

## Menu Sistem

1. **Tampilkan Graf Lokasi** - Lihat semua lokasi dan rute
2. **Tambah Lokasi** - Menambah lokasi baru
3. **Tambah Rute** - Menambah rute antar lokasi
4. **Hapus Lokasi** - Menghapus lokasi dan semua rutenya
5. **Hapus Rute** - Menghapus rute spesifik
6. **Cari Rute Terbaik** - Pencarian rute optimal
7. **Set Preferensi Pengguna** - Atur kriteria optimasi
8. **Simulasi Perjalanan** - Simulasi step-by-step
9. **Simpan Data ke File** - Export data
10. **Muat Data dari File** - Import data
11. **Tampilkan Decision Tree** - Lihat struktur decision tree

## Data Default

Sistem dilengkapi dengan data default kota-kota di Indonesia:
- Jakarta, Bandung, Surabaya, Yogyakarta, Semarang, Malang, Solo, Cirebon
- Rute antar kota dengan data realistis jarak, waktu, dan biaya

## Algoritma dan Kompleksitas

- **Dijkstra Algorithm**: O((V + E) log V) dengan priority queue
- **Graph Representation**: Adjacency list untuk efisiensi memori
- **Decision Tree**: O(log n) untuk pencarian preferensi

## Teknologi yang Digunakan

- **Bahasa**: C++17
- **Struktur Data**: Graph (Adjacency List), Tree, Priority Queue, Map
- **Paradigma**: Object-Oriented Programming
- **File I/O**: Text-based storage format

## Contoh Penggunaan

```cpp
// Inisialisasi sistem
TransportationSystem system;
system.initializeDefaultData();

// Tambah lokasi baru
system.addLocation("Bali");

// Tambah rute
system.addRoute("Surabaya", "Bali", 350, 420, 150000);

// Set preferensi
system.setUserPreferences();

// Cari rute terbaik
system.findBestRoute("Jakarta", "Bali");

// Simulasi perjalanan
system.simulateJourney("Jakarta", "Bali");
```

## Penilaian

Total skor maksimal: 100 poin
- Implementasi Sistem & Dokumentasi: 50%
- Pemahaman (Tanya Jawab): 30%
- Demo Video: 20%


## Lisensi

Proyek ini dibuat untuk keperluan akademis - Final Project ET234203 Struktur Data dan Pemrograman Berorientasi Objek.

## Dokumentasi 

**Menu Sistem**

![image](https://github.com/user-attachments/assets/8d5265dd-0807-4dca-8579-d06d0063e5b8)

1. **Tampilkan Graf Lokasi** - Lihat semua lokasi dan rute

<img width="484" alt="image" src="https://github.com/user-attachments/assets/ab47831c-a612-44a4-ba53-a0efc3fc907f" />

2. **Tambah Lokasi** - Menambah lokasi baru

<img width="398" alt="image" src="https://github.com/user-attachments/assets/76610497-6b4f-4e3e-a44e-4ad97f520a69" />

3. **Tambah Rute** - Menambah rute antar lokasi

<img width="424" alt="image" src="https://github.com/user-attachments/assets/44af6da9-fd19-4d29-9d03-7467ab52f585" />

<img width="476" alt="image" src="https://github.com/user-attachments/assets/0c3f0d9f-5e64-4700-b6c6-5e8f7fd70ff3" />

4. **Hapus Lokasi** - Menghapus lokasi dan semua rutenya

<img width="413" alt="image" src="https://github.com/user-attachments/assets/b1f72e57-0d8e-4ecb-be2f-146be89995bf" />

<img width="461" alt="image" src="https://github.com/user-attachments/assets/031c36fd-fe3b-4f0e-9f0b-fe6de3875704" />

6. **Hapus Rute** - Menghapus rute spesifik



7. **Cari Rute Terbaik** - Pencarian rute optimal

<img width="392" alt="image" src="https://github.com/user-attachments/assets/a0502b31-b382-4d6f-abf9-8e8c2f83db37" />

7. **Set Preferensi Pengguna** - Atur kriteria optimasi

<img width="351" alt="image" src="https://github.com/user-attachments/assets/2893318b-8645-4db0-ae6b-00d9c81289fc" />

8. **Simulasi Perjalanan** - Simulasi step-by-step

<img width="530" alt="image" src="https://github.com/user-attachments/assets/77d6f9ab-1573-4eb6-b752-87ac60e3f306" />

9. **Simpan Data ke File** - Export data

![Image](https://github.com/user-attachments/assets/f8a8b5d5-43d2-402e-9988-a853c2e55427)

11. **Muat Data dari File** - Import data
12. **Tampilkan Decision Tree** - Lihat struktur decision tree

****

