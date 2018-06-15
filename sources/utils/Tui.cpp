//
// Created by raphael on 5/31/18.
//

#include <iostream>
#include <cstring>
#include <sstream>
#include <algorithm>
#include "Tui.h"
#include "FileManager.h"
#include "../algortihms/LinearProgrammingSolver.h"

void Tui::run() {
    printWelcome();

    bool quit = false;
    string line, cmd;
    
    while(!quit){
        vector<string> args;
        cout << ">";
        getline(cin, line);

        istringstream iss(line);

        iss >> cmd;
        while (iss)
        {
            string tmp;
            iss >> tmp;
            args.push_back(tmp);
        }

        if(cmd == "quit" || cmd == "q")
        {
            clean_exit();
            quit = true;
        } else if((cmd == "load" || cmd == "l") && args.size() >= 1)
        {
            loadFile(args[0]);
        }
        else if((cmd == "solve") && args.size() >= 1)
        {
            solve(args[0]);
        }
        else if((cmd == "print") && args.size() >= 1)
        {
            print(args[0]);
        }
        else if((cmd == "generate") && args.size() >= 1)
        {
            generation(args);
        }
        else if((cmd == "master") && args.size() >= 3)
        {
            solve_Aleat(atoi(args[0].c_str()), atoi(args[1].c_str()), atoi(args[2].c_str()));
        }
        else if((cmd == "master") && args.size() >= 1)
        {
            int n = atoi(args[0].c_str());
            solve_Aleat(atoi(args[0].c_str()), 5, 5);
            //solve_Aleat(atoi(args[0].c_str()), sqrt(n), sqrt(n));
        }
        else
            help();
    }
}

void Tui::printWelcome() {
    cout << "Hello !" << endl;
}

void Tui::help() {
    cout << "Usage :" << endl;
    cout << "\tq, quit: \t\t quit the program" << endl;
    cout << "\tl, load:\t[file_path]\tload file" << endl;
    cout << "\tsolve:\t\tsolves the probleme loaded" << endl;
}

void Tui::clean_exit() {
    delete(tree);
    delete(atei);
}

Tui::Tui() {}

void Tui::loadFile(basic_string<char> &basic_string) {
    delete(atei);
    atei = FileManager::readInstanceFromFile(basic_string);
}

void Tui::solve(basic_string<char> &solver_type) {
    if(atei != nullptr) {
        cout << "Linear Program:" << endl;

        LinearProgrammingSolver solver = LinearProgrammingSolver();
        AgentTreeExplorationSolution solution = solver.solver(atei, nullptr);
    }
    else{
        cout << "No Instances to solve!" << endl;
    }
}

Tui::Tui(istream &input) : input(input) {}

Tree<int> *Tui::getTree() const {
    return tree;
}

AgentTreeExplorationInstance *Tui::getAtei() const {
    return atei;
}

void Tui::generateRandomTree(int nb_vertex) {
    int index = 0, name = 0;
    //tree = TreeGenerator::generateEquiProbabelBinaryTree(nb_vertex, &index, &name);
    tree = TreeGenerator::generateRandomTree(nb_vertex);
}

void Tui::print(string to_print) {
    if(to_print == "tree")
        cout << *tree << endl;
    else if(to_print == "instance")
        cout << *atei << endl;
    else
        help();
}

void Tui::generation(vector<string> args) {
    if(args[0] == "tree" && args.size() >= 2)
    {
        generateRandomTree(atoi(args[1].c_str()));

    }
    else if (args[0] == "atei" && args.size() >= 3)
    {
        atei = new AgentTreeExplorationInstance(tree, atoi(args[1].c_str()), atoi(args[2].c_str()));
    }
}

void Tui::solve_Aleat(int nb_nodes, int k, int B) {
    generateRandomTree(nb_nodes);
    atei = new AgentTreeExplorationInstance(tree, k, B);
    cout << *atei << endl;
    solve((basic_string<char> &) "");
    delete(atei);
}

