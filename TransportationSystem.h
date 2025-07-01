#ifndef TRANSPORTATION_SYSTEM_H
#define TRANSPORTATION_SYSTEM_H

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <climits>
#include <iomanip>
#include <unordered_map>

using namespace std;

// Forward declarations
class Node;
class Edge;
class Graph;
class DecisionTree;
class UserPreferences;

// Enum untuk kriteria optimasi
enum class OptimizationCriteria {
    DISTANCE,
    TIME,
    COST,
    MULTI_CRITERIA
};
inline string criteriaToString(OptimizationCriteria criteria) {
    switch (criteria) {
        case OptimizationCriteria::DISTANCE: return "Jarak";
        case OptimizationCriteria::TIME: return "Waktu";
        case OptimizationCriteria::COST: return "Biaya";
        case OptimizationCriteria::MULTI_CRITERIA: return "Gabungan";
        default: return "Tidak diketahui";
    }
}

// Enum jenis rute
// Enum jenis rute
enum class RouteType {
    BIASA,
    TOL,
    RUSAK,
    GUNUNG
};

// Konversi enum ke string
inline string routeTypeToString(RouteType type) {
    switch (type) {
        case RouteType::TOL: return "TOL";
        case RouteType::RUSAK: return "RUSAK";
        case RouteType::GUNUNG: return "GUNUNG";
        default: return "BIASA";
    }
}

// Konversi string ke enum
inline RouteType stringToRouteType(const string& str) {
    if (str == "TOL") return RouteType::TOL;
    if (str == "RUSAK") return RouteType::RUSAK;
    if (str == "GUNUNG") return RouteType::GUNUNG;
    return RouteType::BIASA;
}

// Kelas Edge
class Edge {
private:
    string destination;
    double distance;
    double time;
    double cost;
    RouteType type;

public:
    Edge(const string& dest, double dist, double t, double c, RouteType type = RouteType::BIASA)
        : destination(dest), distance(dist), time(t), cost(c), type(type) {}

    // Getters
    string getDestination() const { return destination; }
    double getDistance() const { return distance; }
    double getTime() const { return time; }
    double getCost() const { return cost; }
    RouteType getRouteType() const { return type; }

    // Setters
    void setDistance(double dist) { distance = dist; }
    void setTime(double t) { time = t; }
    void setCost(double c) { cost = c; }
    void setRouteType(RouteType t) { type = t; }

    // Bobot untuk Dijkstra
    double getWeight(OptimizationCriteria criteria, const map<OptimizationCriteria, double>& weights) const;

    void display() const;
};


// Kelas Node untuk merepresentasikan lokasi
class Node {
private:
    string name;
    vector<Edge> edges;
    double x = 0 , y = 0;  
    
public:
    // Default constructor
    Node() : name("") {}
    
    // Constructor dengan parameter
    Node(const string& n, double x = 0, double y = 0) : name(n), x(x), y(y) {}
    
    string getName() const { return name; }
    void setName(const string& n) { name = n; }
    vector<Edge>& getEdges() { return edges; }
    const vector<Edge>& getEdges() const { return edges; }
    double getX() const { return x; }
    double getY() const { return y; }
    
    void setCoordinates(double xCoord, double yCoord) { x = xCoord; y = yCoord; }
    void addEdge(const Edge& edge);
    bool removeEdge(const string& destination);
    void display() const;
};

// Struktur untuk hasil pencarian rute
struct RouteResult {
    vector<string> path;
    double totalDistance;
    double totalTime;
    double totalCost;
    double totalWeight;
    bool found;
    
    RouteResult() : totalDistance(0), totalTime(0), totalCost(0), totalWeight(0), found(false) {}
};

// Kelas untuk Decision Tree    
class DecisionTreeNode {
public:
    string question;
    string criteria;
    DecisionTreeNode* leftChild;
    DecisionTreeNode* rightChild;
    bool isLeaf;
    OptimizationCriteria result;

    // Konstruktor
    DecisionTreeNode(const string& q = "", bool leaf = false) 
        : question(q), leftChild(nullptr), rightChild(nullptr), isLeaf(leaf) {}

    // Destruktor
    ~DecisionTreeNode() {
        delete leftChild;
        delete rightChild;
    }
};

class DecisionTree {
private:
    DecisionTreeNode* root;
    void buildTree();
    OptimizationCriteria traverseTree(DecisionTreeNode* node);
    
public:
    DecisionTree();
    ~DecisionTree() { delete root; }
    
    OptimizationCriteria getRecommendation();
    void displayTree(DecisionTreeNode* node = nullptr, int depth = 0);
    DecisionTreeNode* getRoot() { return root; }
};

// Kelas untuk preferensi pengguna
class UserPreferences {
private:
    OptimizationCriteria primaryCriteria;
    map<OptimizationCriteria, double> weights;
    DecisionTree* decisionTree;
    
public:
    UserPreferences();
    ~UserPreferences() { delete decisionTree; }
    
    void setPrimaryCriteria(OptimizationCriteria criteria) { primaryCriteria = criteria; }
    OptimizationCriteria getPrimaryCriteria() const { return primaryCriteria; }
    
    void setWeight(OptimizationCriteria criteria, double weight) { weights[criteria] = weight; }
    double getWeight(OptimizationCriteria criteria) const;
    const map<OptimizationCriteria, double>& getWeights() const { return weights; }
    
    void setPreferencesInteractively();
    void setPreferencesUsingDecisionTree();
    
    DecisionTree* getDecisionTree() { return decisionTree; }
};

// Kelas utama Graph
class Graph {
private:
    unordered_map<string, Node> nodes;
    
public:
    void addNode(const string& name);
    bool removeNode(const string& name);
    void addEdge(const string& from, const string& to, double distance, double time, double cost, RouteType type = RouteType::BIASA);
    bool removeEdge(const string& from, const string& to);

    unordered_map<string, Node>& getNodesMutable() { return nodes; }

    
    RouteResult dijkstra(const string& start, const string& end,
                     OptimizationCriteria criteria,
                     const map<OptimizationCriteria, double>& weights) const;

    
    void display() const;
    bool hasNode(const string& name) const;
    const unordered_map<string, Node>& getNodes() const { return nodes; }
    
    // File I/O
    void saveToFile(const string& filename) const;
    void loadFromFile(const string& filename);
};

// Kelas utama sistem transportasi
class TransportationSystem {
private:
    Graph graph;
    UserPreferences preferences;
    RouteResult lastRoute;
    
public:
    TransportationSystem();
    
    Graph& getGraphMutable() { return graph; }
    UserPreferences& getUserPreferences() { return preferences; }
    const UserPreferences& getUserPreferences() const { return preferences; }

    // CRUD Operations
    void addLocation(const string& name);
    void removeLocation(const string& name);
    void addRoute(const std::string& from, const std::string& to, RouteType type);
    void removeRoute(const string& from, const string& to);
    
    const Graph& getGraph() const { return graph; }

    RouteResult getLastRoute() const { return lastRoute; }
    
    // Route finding
    void findBestRoute(const string& from, const string& to);
    void simulateJourney(const string& from, const string& to);
    
    // User preferences
    void setUserPreferences();
    
    // Display functions
    void displayGraph();
    void displayDecisionTree();
    
    // File I/O
    void saveToFile(const string& filename);
    void loadFromFile(const string& filename);
    
    // Initialization
    void initializeDefaultData();
    
    void setLocationCoordinates(const string& name, double x, double y);
};

#endif
