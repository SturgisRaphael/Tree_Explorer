//
// Created by raphael on 5/31/18.
//

#ifndef TREE_EXPLORER_TUI_H
#define TREE_EXPLORER_TUI_H


#include "../structures/Tree.h"
#include "../structures/AgentTreeExplorationInstance.h"
#include "../algortihms/TreeGenerator.h"

class Tui {
private:
    Tree<int> *tree = nullptr;
    AgentTreeExplorationInstance *atei = nullptr;
    std::istream& input = cin;

public:
    Tui();

    Tui(istream &input);

    Tree<int> *getTree() const;

    AgentTreeExplorationInstance *getAtei() const;

    void run();

private:
    void printWelcome();

    void help();

    void clean_exit();

    void loadFile(basic_string<char> &basic_string);

    void solve(basic_string<char> &solver_type);

    void generateRandomTree(int nb_vertex);

    void print(string to_print);

    void generation(vector<string> args);

    void solve_Aleat(int nb_nodes, int k, int B);
};


#endif //TREE_EXPLORER_TUI_H
