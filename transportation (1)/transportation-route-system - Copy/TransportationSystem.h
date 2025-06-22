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

// Kelas Edge untuk merepresentasikan rute
class Edge {
private:
    string destination;
    double distance;
    double time;
    double cost;
    
public:
    Edge(const string& dest, double dist, double t, double c);
    
    // Getters
    string getDestination() const { return destination; }
    double getDistance() const { return distance; }
    double getTime() const { return time; }
    double getCost() const { return cost; }
    
    // Setters
    void setDistance(double dist) { distance = dist; }
    void setTime(double t) { time = t; }
    void setCost(double c) { cost = c; }
    
    // Method untuk menghitung bobot berdasarkan kriteria
    double getWeight(OptimizationCriteria criteria, const map<OptimizationCriteria, double>& weights) const;
    
    void display() const;
};

// Kelas Node untuk merepresentasikan lokasi
class Node {
private:
    string name;
    vector<Edge> edges;
    
public:
    // Default constructor
    Node() : name("") {}
    
    // Constructor dengan parameter
    Node(const string& n) : name(n) {}
    
    string getName() const { return name; }
    void setName(const string& n) { name = n; }
    vector<Edge>& getEdges() { return edges; }
    const vector<Edge>& getEdges() const { return edges; }
    
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
    
    DecisionTreeNode(const string& q = "", bool leaf = false) 
        : question(q), leftChild(nullptr), rightChild(nullptr), isLeaf(leaf) {}
    
    ~DecisionTreeNode() {
        delete leftChild;
        delete rightChild;
    }
};

class DecisionTree {
private:
    DecisionTreeNode* root;
    
public:
    DecisionTree();
    ~DecisionTree() { delete root; }
    
    OptimizationCriteria getRecommendation();
    void displayTree(DecisionTreeNode* node = nullptr, int depth = 0);
    DecisionTreeNode* getRoot() { return root; }
    
private:
    void buildTree();
    OptimizationCriteria traverseTree(DecisionTreeNode* node);
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
    void addEdge(const string& from, const string& to, double distance, double time, double cost);
    bool removeEdge(const string& from, const string& to);
    
    RouteResult dijkstra(const string& start, const string& end, OptimizationCriteria criteria, 
                        const map<OptimizationCriteria, double>& weights);
    
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
    
    // CRUD Operations
    void addLocation(const string& name);
    void removeLocation(const string& name);
    void addRoute(const string& from, const string& to, double distance, double time, double cost);
    void removeRoute(const string& from, const string& to);
    
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
};

#endif
