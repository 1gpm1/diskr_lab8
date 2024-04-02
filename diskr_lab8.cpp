#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <Windows.h>

class Graph {
private:
    std::vector<std::vector<int>> adjacencyMatrix;
    int vertices;

public:
    Graph(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Файл не знайдено" << std::endl;
            return;
        }

        file >> vertices;
        adjacencyMatrix.resize(vertices, std::vector<int>(vertices));

        for (int i = 0; i < vertices; ++i) {
            for (int j = 0; j < vertices; ++j) {
                file >> adjacencyMatrix[i][j];
            }
        }

        file.close();
    }

    std::vector<int> DFS(int startVertex) {
        std::vector<bool> visited(vertices, false);
        std::stack<int> stack;
        std::vector<int> dfsOrder;
        stack.push(startVertex);

        while (!stack.empty()) {
            int currentVertex = stack.top();
            stack.pop();

            if (!visited[currentVertex]) {
                dfsOrder.push_back(currentVertex);
                std::cout << "Вершина: " << (currentVertex + 1) << ", DFS-номер: " << (currentVertex + 1);
                std::cout << ", Стек: ";
                std::stack<int> tempStack = stack;
                while (!tempStack.empty()) {
                    std::cout << tempStack.top() << " ";
                    tempStack.pop();
                }
                std::cout << std::endl;

                visited[currentVertex] = true;
                for (int i = 0; i < vertices; ++i) {
                    if (adjacencyMatrix[currentVertex][i] == 1 && !visited[i]) {
                        stack.push(i);
                    }
                }
            }
        }

        return dfsOrder;
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    try {
        Graph graph("graph.txt");
        std::cout << "Введіть початкову вершину:" << std::endl;
        int startVertex;
        std::cin >> startVertex;
        std::vector<int> dfsOrder = graph.DFS(startVertex - 1);
    }
    catch (...) {
        std::cerr << "Файл не знайдено" << std::endl;
    }

    return 0;
}
