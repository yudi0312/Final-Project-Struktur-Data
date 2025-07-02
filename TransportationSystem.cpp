#include "TransportationSystem.h"
#include <iostream>
#include <cfloat>
#include <cmath> // Tambahkan ini agar sqrt dikenali
#include <set>

// Implementasi Edge


double Edge::getWeight(OptimizationCriteria criteria, const map<OptimizationCriteria, double>& weights) const {
    switch (criteria) {
        case OptimizationCriteria::DISTANCE:
            return distance;
        case OptimizationCriteria::TIME:
            return time;
        case OptimizationCriteria::COST:
            return cost;
        case OptimizationCriteria::MULTI_CRITERIA:
            double totalWeight = 0;
            auto it = weights.find(OptimizationCriteria::DISTANCE);
            if (it != weights.end()) totalWeight += distance * it->second;
            
            it = weights.find(OptimizationCriteria::TIME);
            if (it != weights.end()) totalWeight += time * it->second;
            
            it = weights.find(OptimizationCriteria::COST);
            if (it != weights.end()) totalWeight += cost * it->second;
            
            return totalWeight;
    }
    return distance; // default
}

void Edge::display() const {
    cout << "-> " << destination 
         << " (Jarak: " << distance << "km, "
         << "Waktu: " << time << "min, "
         << "Biaya: Rp" << cost << ")" << endl;
}

// Implementasi Node
void Node::addEdge(const Edge& edge) {
    edges.push_back(edge);
}

bool Node::removeEdge(const string& destination) {
    auto it = find_if(edges.begin(), edges.end(),
        [&destination](const Edge& e) { return e.getDestination() == destination; });
    
    if (it != edges.end()) {
        edges.erase(it);
        return true;
    }
    return false;
}

void Node::display() const {
    cout << "Lokasi: " << name << endl;
    for (const auto& edge : edges) {
        cout << "  ";
        edge.display();
    }
}

// Implementasi DecisionTree
DecisionTree::DecisionTree() {
    buildTree();
}

void DecisionTree::buildTree() {
    root = new DecisionTreeNode("Apakah Anda lebih mengutamakan efisiensi waktu?");
    
    // Left branch (Ya - prioritas waktu)
    root->leftChild = new DecisionTreeNode("Apakah budget Anda terbatas?");
    root->leftChild->leftChild = new DecisionTreeNode("", true);
    root->leftChild->leftChild->result = OptimizationCriteria::MULTI_CRITERIA;
    root->leftChild->rightChild = new DecisionTreeNode("", true);
    root->leftChild->rightChild->result = OptimizationCriteria::TIME;
    
    // Right branch (Tidak - pertimbangan lain)
    root->rightChild = new DecisionTreeNode("Apakah Anda lebih mengutamakan biaya murah?");
    root->rightChild->leftChild = new DecisionTreeNode("", true);
    root->rightChild->leftChild->result = OptimizationCriteria::COST;
    root->rightChild->rightChild = new DecisionTreeNode("", true);
    root->rightChild->rightChild->result = OptimizationCriteria::DISTANCE;
}

OptimizationCriteria DecisionTree::getRecommendation() {
    return traverseTree(root);
}

OptimizationCriteria DecisionTree::traverseTree(DecisionTreeNode* node) {
    if (node->isLeaf) {
        return node->result;
    }
    
    cout << node->question << " (y/n): ";
    char answer;
    cin >> answer;
    
    if (answer == 'y' || answer == 'y') {
        return traverseTree(node->leftChild);
    } else {
        return traverseTree(node->rightChild);
    }
}

void DecisionTree::displayTree(DecisionTreeNode* node, int depth) {
    if (node == nullptr) {
        node = root;
    }
    
    for (int i = 0; i < depth; i++) {
        cout << "  ";
    }
    
    if (node->isLeaf) {
        cout << "-> Rekomendasi: ";
        switch (node->result) {
            case OptimizationCriteria::DISTANCE:
                cout << "Jarak Terpendek" << endl;
                break;
            case OptimizationCriteria::TIME:
                cout << "Waktu Tercepat" << endl;
                break;
            case OptimizationCriteria::COST:
                cout << "Biaya Termurah" << endl;
                break;
            case OptimizationCriteria::MULTI_CRITERIA:
                cout << "Multi-kriteria (Seimbang)" << endl;
                break;
        }
    } else {
        cout << node->question << endl;
        if (node->leftChild) {
            for (int i = 0; i <= depth; i++) cout << "  ";
            cout << "Ya:" << endl;
            displayTree(node->leftChild, depth + 2);
        }
        if (node->rightChild) {
            for (int i = 0; i <= depth; i++) cout << "  ";
            cout << "Tidak:" << endl;
            displayTree(node->rightChild, depth + 2);
        }
    }
}

// Implementasi UserPreferences
UserPreferences::UserPreferences() : primaryCriteria(OptimizationCriteria::DISTANCE) {
    weights[OptimizationCriteria::DISTANCE] = 0.4;
    weights[OptimizationCriteria::TIME] = 0.4;
    weights[OptimizationCriteria::COST] = 0.2;
    decisionTree = new DecisionTree();
}

double UserPreferences::getWeight(OptimizationCriteria criteria) const {
    auto it = weights.find(criteria);
    return (it != weights.end()) ? it->second : 0.0;
}

void UserPreferences::setPreferencesInteractively() {
    cout << "\n=== PENGATURAN PREFERENSI PENGGUNA ===" << endl;
    cout << "1. Jarak Terpendek" << endl;
    cout << "2. Waktu Tercepat" << endl;
    cout << "3. Biaya Termurah" << endl;
    cout << "4. Multi-kriteria (Custom)" << endl;
    cout << "5. Gunakan Decision Tree" << endl;
    cout << "Pilihan: ";
    
    int choice;
    cin >> choice;
    
    switch (choice) {
        case 1:
            primaryCriteria = OptimizationCriteria::DISTANCE;
            break;
        case 2:
            primaryCriteria = OptimizationCriteria::TIME;
            break;
        case 3:
            primaryCriteria = OptimizationCriteria::COST;
            break;
        case 4:
            primaryCriteria = OptimizationCriteria::MULTI_CRITERIA;
            cout << "Masukkan bobot untuk jarak (0-1): ";
            double distWeight;
            cin >> distWeight;
            weights[OptimizationCriteria::DISTANCE] = distWeight;
            
            cout << "Masukkan bobot untuk waktu (0-1): ";
            double timeWeight;
            cin >> timeWeight;
            weights[OptimizationCriteria::TIME] = timeWeight;
            
            cout << "Masukkan bobot untuk biaya (0-1): ";
            double costWeight;
            cin >> costWeight;
            weights[OptimizationCriteria::COST] = costWeight;
            break;
        case 5:
            setPreferencesUsingDecisionTree();
            break;
        default:
            cout << "Pilihan tidak valid, menggunakan jarak sebagai default." << endl;
            primaryCriteria = OptimizationCriteria::DISTANCE;
    }
    
    cout << "Preferensi berhasil diatur!" << endl;
}

void UserPreferences::setPreferencesUsingDecisionTree() {
    cout << "\n=== DECISION TREE UNTUK PREFERENSI ===" << endl;
    primaryCriteria = decisionTree->getRecommendation();
    
    if (primaryCriteria == OptimizationCriteria::MULTI_CRITERIA) {
        weights[OptimizationCriteria::DISTANCE] = 0.3;
        weights[OptimizationCriteria::TIME] = 0.4;
        weights[OptimizationCriteria::COST] = 0.3;
    }
}

// Implementasi Graph
void Graph::addNode(const string& name) {
    if (nodes.find(name) == nodes.end()) {
        nodes[name] = Node(name);
    }
}

bool Graph::removeNode(const string& name) {
    auto it = nodes.find(name);
    if (it != nodes.end()) {
        // 1. Hapus semua edge dari node lain ke node ini
        for (auto& [otherName, node] : nodes) {
            if (otherName != name) {
                node.removeEdge(name);
            }
        }

        // 2. Hapus node-nya sendiri (otomatis menghapus edge dari node tersebut ke node lain)
        nodes.erase(it);

        return true;
    }
    return false;
}


void Graph::addEdge(const string& from, const string& to, double distance, double time, double cost, RouteType type) {
    addNode(from);
    addNode(to);

    nodes[from].addEdge(Edge(to, distance, time, cost, type));
    nodes[to].addEdge(Edge(from, distance, time, cost, type)); // Tambahkan dua arah
}


bool Graph::removeEdge(const string& from, const string& to) {
    bool removed1 = false, removed2 = false;
    
    auto it1 = nodes.find(from);
    if (it1 != nodes.end()) {
        removed1 = it1->second.removeEdge(to);
    }
    
    auto it2 = nodes.find(to);
    if (it2 != nodes.end()) {
        removed2 = it2->second.removeEdge(from);
    }
    
    return removed1 || removed2;
}

    RouteResult Graph::dijkstra(const string& start, const string& end,
                            OptimizationCriteria criteria,
                            const map<OptimizationCriteria, double>& weights) const {
        RouteResult result;
        
        if (nodes.find(start) == nodes.end() || nodes.find(end) == nodes.end()) {
            return result;
        }
        
        // Priority queue untuk Dijkstra (weight, node, path)
        priority_queue<pair<double, pair<string, vector<string>>>, 
                    vector<pair<double, pair<string, vector<string>>>>,
                    greater<pair<double, pair<string, vector<string>>>>> pq;
        
        map<string, double> distances; //jarak terkecil
        map<string, vector<string>> paths; //menyimpan rute terbaik
        map<string, pair<double, pair<double, double>>> routeInfo; // distance, time, cost
        
        // Inisialisasi semua node dengan jarak tak terhingga
        for (const auto& pair : nodes) {
            distances[pair.first] = DBL_MAX;
        }
        distances[start] = 0;
        
        pq.push({0, {start, {start}}});
        
        while (!pq.empty()) {
            double currentDist = pq.top().first; //bobot awal
            string currentNode = pq.top().second.first; //node sekarang
            vector<string> currentPath = pq.top().second.second; //rute terjauh
            pq.pop();
            
            if (currentDist > distances[currentNode]) continue;
            
            if (currentNode == end) {
                result.found = true;
                result.path = currentPath;
                result.totalWeight = currentDist;
                
                // Hitung total distance, time, cost
                for (size_t i = 0; i < currentPath.size() - 1; i++) {
                    const string& from = currentPath[i];
                    const string& to = currentPath[i + 1];
                    
                    for (const auto& edge : nodes.at(from).getEdges()) {
                        if (edge.getDestination() == to) {
                            result.totalDistance += edge.getDistance();
                            result.totalTime += edge.getTime();
                            result.totalCost += edge.getCost();
                            break;
                        }
                    }
                }
                break;
            }
            
            for (const auto& edge : nodes.at(currentNode).getEdges()) {
                string neighbor = edge.getDestination();
                double weight = edge.getWeight(criteria, weights);
                double newDist = currentDist + weight;
                
                if (newDist < distances[neighbor]) {
                    distances[neighbor] = newDist;
                    vector<string> newPath = currentPath;
                    newPath.push_back(neighbor);
                    pq.push({newDist, {neighbor, newPath}});
                }
            }
        }
        
        return result;
    }

void Graph::display() const {
    std::cout << "=== GRAF LOKASI DAN RUTE ===" << std::endl;

    for (const auto& [name, node] : nodes) {
        std::cout << "Lokasi: " << name << " (" << node.getX() << ", " << node.getY() << ")" << std::endl;

        // Gunakan set untuk menghindari edge ke tujuan yang sama lebih dari sekali dari node yang sama
        std::set<std::string> printed;

        for (const auto& edge : node.getEdges()) {
            const std::string& dest = edge.getDestination();

            // Hanya cetak edge satu kali per tujuan
            if (!nodes.count(dest) || printed.count(dest)) continue;

            std::cout << "  -> " << dest
                      << " (Jarak: " << edge.getDistance() << "km, "
                      << "Waktu: " << edge.getTime() << "min, "
                      << "Biaya: Rp" << static_cast<long long>(edge.getCost()) << ")"
                      << " [" << routeTypeToString(edge.getRouteType()) << "]"
                      << std::endl;

            printed.insert(dest);
        }
    }
}






bool Graph::hasNode(const string& name) const {
    return nodes.find(name) != nodes.end();
}

void Graph::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Tidak dapat membuka file untuk menulis!" << std::endl;
        return;
    }

    file << "NODES" << std::endl;
    for (const auto& pair : nodes) {
        file << pair.first << "," << pair.second.getX() << "," << pair.second.getY() << std::endl;
    }

    file << "EDGES" << std::endl;
    std::set<std::pair<std::string, std::string>> written;

    for (const auto& pair : nodes) {
        const std::string& from = pair.first;
        for (const auto& edge : pair.second.getEdges()) {
            const std::string& to = edge.getDestination();

            // Lewati edge jika simpul tujuan sudah tidak ada
            if (nodes.find(to) == nodes.end()) continue;

            std::string a = std::min(from, to);
            std::string b = std::max(from, to);

            if (written.count({a, b}) == 0) {
                file << from << "," << to << ","
                     << edge.getDistance() << ","
                     << edge.getTime() << ","
                     << edge.getCost() << ","
                     << routeTypeToString(edge.getRouteType()) << std::endl;

                written.insert({a, b});
            }
        }
    }

    file.close();
    std::cout << "Data berhasil disimpan ke " << filename << std::endl;
}


void Graph::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Tidak dapat membuka file untuk membaca!" << endl;
        return;
    }
    
    nodes.clear();
    string line;
    bool readingNodes = false, readingEdges = false;
    
    while (getline(file, line)) {
        if (line == "NODES") {
            readingNodes = true;
            readingEdges = false;
            continue;
        } else if (line == "EDGES") {
            readingNodes = false;
            readingEdges = true;
            continue;
        }
        
        if (readingNodes && !line.empty()) {
            stringstream ss(line);
        string name, xStr, yStr;
        getline(ss, name, ',');
    getline(ss, xStr, ',');
    getline(ss, yStr);

    addNode(name);
    if (!xStr.empty() && !yStr.empty()) {
        double x = stod(xStr);
        double y = stod(yStr);
        nodes[name].setCoordinates(x, y);
    }
        } else if (readingEdges && !line.empty()) {
            stringstream ss(line);
            string from, to, distStr, timeStr, costStr;
            
            getline(ss, from, ',');
            getline(ss, to, ',');
            getline(ss, distStr, ',');
            getline(ss, timeStr, ',');
            getline(ss, costStr);
            
            double distance = stod(distStr);
            double time = stod(timeStr);
            double cost = stod(costStr);
            
            // Hanya tambahkan satu arah untuk menghindari duplikasi
            addEdge(from, to, distance, time, cost, RouteType::BIASA);
            addEdge(to, from, distance, time, cost, RouteType::BIASA); // ← Selalu tambahkan dua arah

        }
    }
    
    file.close();
    cout << "Data berhasil dimuat dari " << filename << endl;
}

// Implementasi TransportationSystem
TransportationSystem::TransportationSystem() {}

void TransportationSystem::addLocation(const string& name) {
    graph.addNode(name);
}

void TransportationSystem::removeLocation(const string& name) {
    if (graph.removeNode(name)) {
        cout << "Lokasi " << name << " berhasil dihapus!" << endl;
    } else {
        cout << "Lokasi " << name << " tidak ditemukan!" << endl;
    }
}

// Tetap gunakan Phytagoras HANYA jika koordinat sudah diset
void TransportationSystem::addRoute(const string& from, const string& to, RouteType type) {
    const auto& nodes = graph.getNodes();
    if (!graph.hasNode(from) || !graph.hasNode(to)) return;

    double x1 = nodes.at(from).getX();
    double y1 = nodes.at(from).getY();
    double x2 = nodes.at(to).getX();
    double y2 = nodes.at(to).getY();

    if ((x1 == 0 && y1 == 0) && (x2 == 0 && y2 == 0)) {
        std::cerr << "Koordinat kosong! Tidak bisa menghitung jarak otomatis.\n";
        return;
    }

    double dx = x2 - x1;
    double dy = y2 - y1;
    double distance = std::sqrt(dx * dx + dy * dy); // km

    // Faktor berdasarkan jenis rute
    double timePerKm, costPerKm;

    switch (type) {
        case RouteType::TOL:
            timePerKm = 6.0; costPerKm = 25000; break;
        case RouteType::RUSAK:
            timePerKm = 15.0; costPerKm = 22000; break;
        case RouteType::GUNUNG:
            timePerKm = 20.0; costPerKm = 18000; break;
        case RouteType::BIASA:
        default:
            timePerKm = 10.0; costPerKm = 20000; break;
    }

    double time = distance * timePerKm;
    double cost = distance * costPerKm;

    graph.addEdge(from, to, distance, time, cost, type);
    graph.addEdge(to, from, distance, time, cost, type); 
}




void TransportationSystem::removeRoute(const string& from, const string& to) {
    bool removed1 = graph.removeEdge(from, to);
    bool removed2 = graph.removeEdge(to, from);

    if (removed1 || removed2) {
        cout << "Rute antara " << from << " dan " << to << " berhasil dihapus!" << endl;
    } else {
        cout << "Rute tidak ditemukan!" << endl;
    }
}


void TransportationSystem::findBestRoute(const string& from, const string& to) {
    if (!graph.hasNode(from)) {
        cout << "Lokasi asal '" << from << "' tidak ditemukan!" << endl;
        return;
    }
    
    if (!graph.hasNode(to)) {
        cout << "Lokasi tujuan '" << to << "' tidak ditemukan!" << endl;
        return;
    }
    
    lastRoute = graph.dijkstra(from, to, preferences.getPrimaryCriteria(), preferences.getWeights());
    
    if (lastRoute.found) {
        cout << "\n=== RUTE TERBAIK DITEMUKAN ===" << endl;
        cout << "Dari: " << from << " ke " << to << endl;
        cout << "Rute: ";
        for (size_t i = 0; i < lastRoute.path.size(); i++) {
            cout << lastRoute.path[i];
            if (i < lastRoute.path.size() - 1) cout << " -> ";
        }
        cout << endl;
        
        cout << fixed << setprecision(2);
        cout << "Total Jarak: " << lastRoute.totalDistance << " km" << endl;
        cout << "Total Waktu: " << lastRoute.totalTime << " menit" << endl;
        cout << "Total Biaya: Rp " << lastRoute.totalCost << endl;
        
        string criteriaName;
        switch (preferences.getPrimaryCriteria()) {
            case OptimizationCriteria::DISTANCE:
                criteriaName = "Jarak";
                break;
            case OptimizationCriteria::TIME:
                criteriaName = "Waktu";
                break;
            case OptimizationCriteria::COST:
                criteriaName = "Biaya";
                break;
            case OptimizationCriteria::MULTI_CRITERIA:
                criteriaName = "Multi-kriteria";
                break;
        }
        cout << "Optimasi berdasarkan: " << criteriaName << endl;
    } else {
        cout << "Rute dari " << from << " ke " << to << " tidak ditemukan!" << endl;
    }
}

void TransportationSystem::simulateJourney(const string& from, const string& to) {
    findBestRoute(from, to);
    
    if (lastRoute.found) {
        cout << "\n=== SIMULASI PERJALANAN ===" << endl;
        cout << "Memulai perjalanan dari " << from << " menuju " << to << endl;
        cout << "----------------------------------------" << endl;
        
        double cumulativeDistance = 0, cumulativeTime = 0, cumulativeCost = 0;
        
        for (size_t i = 0; i < lastRoute.path.size() - 1; i++) {
            const string& currentLoc = lastRoute.path[i];
            const string& nextLoc = lastRoute.path[i + 1];
            
            // Cari edge yang sesuai
            for (const auto& edge : graph.getNodes().at(currentLoc).getEdges()) {
                if (edge.getDestination() == nextLoc) {
                    cumulativeDistance += edge.getDistance();
                    cumulativeTime += edge.getTime();
                    cumulativeCost += edge.getCost();
                    
                    cout << "Langkah " << (i + 1) << ": " << currentLoc << " -> " << nextLoc << endl;
                    cout << "  Jarak: " << edge.getDistance() << " km" << endl;
                    cout << "  Waktu: " << edge.getTime() << " menit" << endl;
                    cout << "  Biaya: Rp " << edge.getCost() << endl;
                    cout << "  Kumulatif - Jarak: " << cumulativeDistance << " km, "
                         << "Waktu: " << cumulativeTime << " menit, "
                         << "Biaya: Rp " << cumulativeCost << endl;
                    cout << "----------------------------------------" << endl;
                    break;
                }
            }
        }
        
        cout << "Perjalanan selesai! Anda telah tiba di " << to << endl;
        cout << "Total perjalanan:" << endl;
        cout << "- Jarak: " << cumulativeDistance << " km" << endl;
        cout << "- Waktu: " << cumulativeTime << " menit" << endl;
        cout << "- Biaya: Rp " << cumulativeCost << endl;
    }
}

void TransportationSystem::setUserPreferences() {
    preferences.setPreferencesInteractively();
}

void TransportationSystem::displayGraph() {
    graph.display();
}

void TransportationSystem::displayDecisionTree() {
    cout << "\n=== DECISION TREE UNTUK PREFERENSI ===" << endl;
    preferences.getDecisionTree()->displayTree();
}

void TransportationSystem::saveToFile(const string& filename) {
    graph.saveToFile(filename);
}

void TransportationSystem::loadFromFile(const string& filename) {
    graph.loadFromFile(filename);
}

void TransportationSystem::initializeDefaultData() {
    // Tambah lokasi-lokasi default
    addLocation("Jakarta");
    addLocation("Bandung");
    addLocation("Surabaya");
    addLocation("Yogyakarta");
    addLocation("Semarang");
    addLocation("Malang");
    addLocation("Solo");
    addLocation("Cirebon");

    auto& nodes = graph.getNodesMutable();
    nodes.at("Jakarta").setCoordinates(10, 10);
    nodes.at("Bandung").setCoordinates(20, 15);
    nodes.at("Cirebon").setCoordinates(25, 10);
    nodes.at("Semarang").setCoordinates(40, 15);
    nodes.at("Yogyakarta").setCoordinates(35, 25);
    nodes.at("Solo").setCoordinates(40, 30);
    nodes.at("Surabaya").setCoordinates(55, 30);
    nodes.at("Malang").setCoordinates(50, 40);

    // Tambah rute-rute default dengan jenis jalan
    addRoute("Jakarta", "Bandung", RouteType::TOL);
    addRoute("Jakarta", "Cirebon", RouteType::BIASA);
    addRoute("Jakarta", "Semarang", RouteType::TOL);
    addRoute("Bandung", "Yogyakarta", RouteType::RUSAK);
    addRoute("Cirebon", "Semarang", RouteType::BIASA);
    addRoute("Semarang", "Yogyakarta", RouteType::BIASA);
    addRoute("Semarang", "Solo", RouteType::GUNUNG);
    addRoute("Yogyakarta", "Solo", RouteType::BIASA);
    addRoute("Solo", "Surabaya", RouteType::TOL);
    addRoute("Yogyakarta", "Malang", RouteType::RUSAK);
    addRoute("Surabaya", "Malang", RouteType::GUNUNG);

    cout << "Data default berhasil dimuat!" << endl;
    cout << "Sistem siap digunakan dengan " << graph.getNodes().size() << " lokasi." << endl;
}


void TransportationSystem::setLocationCoordinates(const string& name, double x, double y) {
    if (graph.hasNode(name)) {
        graph.getNodesMutable().at(name).setCoordinates(x, y);
    }
}
