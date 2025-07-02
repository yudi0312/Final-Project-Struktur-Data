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
```g++ -std=c++17 -Wall -O2 -o visualizer visualizer.cpp TransportationSystem.cpp -lsfml-graphics -lsfml-window -lsfml-system```

# Menjalankan
```./transportation_system```

```./visualizer```

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


## Dokumentasi Sistem

### Menu Utama

![Menu Sistem](https://github.com/user-attachments/assets/8d5265dd-0807-4dca-8579-d06d0063e5b8)

---

### 1. Tampilkan Graf Lokasi  
Melihat semua lokasi dan rute yang tersedia dalam sistem.

![Tampilkan Graf Lokasi](https://github.com/user-attachments/assets/fec66d5d-d651-48dd-a70a-b822b38abd80)

---

### 2. Tambah Lokasi  
Menambahkan lokasi baru ke dalam graf.

| Form Input Lokasi | Data Lokasi Setelah Ditambah |
|------------------|-----------------------------|
| ![Tambah Lokasi](https://github.com/user-attachments/assets/256128df-c6f1-4274-8383-45e154e5b9b6) | ![Lokasi Ditambahkan](https://github.com/user-attachments/assets/1788f506-e11b-4f7f-be3b-dcb22562be27) |

---

### 3. Tambah Rute  
Menambahkan rute antar dua lokasi yang sudah ada.

| Form Input Rute | Data Rute Setelah Ditambah |
|------------------|-----------------------------|
| ![Form Tambah Rute](https://github.com/user-attachments/assets/d47b2aff-776f-4948-8448-b0e3df99e4b8) | ![Rute Ditambahkan](https://github.com/user-attachments/assets/f4069f4c-d9ab-49b6-879d-7c37d28a2fde) |

---

### 4. Hapus Lokasi  
Menghapus lokasi tertentu beserta seluruh rutenya.

| Form Hapus Lokasi | Data Setelah Dihapus |
|-------------------|----------------------|
| ![Form Hapus Lokasi](https://github.com/user-attachments/assets/b1f72e57-0d8e-4ecb-be2f-146be89995bf) | ![Setelah Lokasi Dihapus](https://github.com/user-attachments/assets/a4ee993b-443b-46e7-94d2-aebb295d9eca) |

---

### 5. Hapus Rute  
Menghapus rute spesifik antar dua lokasi.

| Form Hapus Rute | Rute Setelah Dihapus |
|-----------------|----------------------|
| ![Form Hapus Rute](https://github.com/user-attachments/assets/9b10e14c-bd8d-438e-87e7-2ae401d8f613) | ![Rute Sudah Dihapus](https://github.com/user-attachments/assets/1ec7e8cc-b36a-4c99-aee8-79f8af38fdf5) |

---

### 6. Cari Rute Terbaik  
Mencari rute optimal berdasarkan kriteria yang dipilih.

![Cari Rute Terbaik](https://github.com/user-attachments/assets/a0502b31-b382-4d6f-abf9-8e8c2f83db37)

---

### 7. Set Preferensi Pengguna  
Mengatur kriteria optimasi: waktu, jarak, biaya, dll.

![Set Preferensi](https://github.com/user-attachments/assets/2893318b-8645-4db0-ae6b-00d9c81289fc)

---

### 8. Simulasi Perjalanan  
Menampilkan simulasi perjalanan secara bertahap dari titik awal ke tujuan.

![Simulasi Perjalanan](https://github.com/user-attachments/assets/77d6f9ab-1573-4eb6-b752-87ac60e3f306)

---

### 9. Simpan Data ke File  
Ekspor data lokasi dan rute ke file eksternal.

![Simpan Data](https://github.com/user-attachments/assets/69625b19-f87f-451d-97d7-64215a5b5970)

---

### 10. Muat Data dari File  
Impor data lokasi dan rute dari file eksternal.

![Muat Data](https://github.com/user-attachments/assets/62aa5916-72f5-4283-ad61-46b49e87b496)

---

### 11. Tampilkan Decision Tree  
Menampilkan struktur decision tree dari sistem yang digunakan.

![Decision Tree](https://github.com/user-attachments/assets/26cb6942-3e8c-4e8d-a701-b169b105da06)

---

### 12. Visualisasi  
Menampilkan representasi graf jaringan lokasi dan rute secara visual.

![Visualisasi Graf](https://github.com/user-attachments/assets/d340962b-aefc-41a6-adda-60737f18783f)


****
