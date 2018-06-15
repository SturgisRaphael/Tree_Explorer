//
// Created by raphael on 4/19/18.
//


#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include "algortihms/LinearProgrammingSolver.h"
#include "utils/FileManager.h"
#include "algortihms/TreeGenerator.h"
#include "algortihms/instanceGenrator.h"
#include "utils/Tui.h"
#include "algortihms/gloutonSolver.h"

int main(int argc, char* argv[])
{
    if(argc <= 0)
    {
        cout << "Usage: " << endl;
        cout  << argv[0] << " 0\t-> console mode" << endl;
        cout  << argv[0] << " 1\t-> file production" << endl;
        exit(0);
    }
    if(atoi(argv[1]) == 0)
    {
        Tui console;
        console.run();
    }
    else if(atoi(argv[1]) > 0)
    {
//        if(atoi(argv[2]) < 20 && atoi(argv[2]) > 0)
//        {
//            cout << "\tOpt\t\tPL\t\tGT\t\topt" << endl;
//            for(int i = 0; i < atoi(argv[1]); i++)
//            {
//                auto tree = TreeGenerator::generateRandomTree(atoi(argv[2]));
//                auto atei = new AgentTreeExplorationInstance(tree, sqrt(atoi(argv[2])), sqrt(atoi(argv[2])));
//                double opt_frac = 0;
//                LinearProgrammingSolver solver = LinearProgrammingSolver();
//                AgentTreeExplorationSolution solution = solver.solver(atei, &opt_frac);
//                AgentTreeExplorationSolution opt = solver.optiSolver(atei);
//                AgentTreeExplorationSolution glouton = gloutonSolver::solver(atei);
//                cout << i << "\t" << opt_frac << "\t\t" << solution.getNumberOfEdgesExplored() << "\t\t" << glouton.getNumberOfEdgesExplored() << "\t\t" << opt.getNumberOfEdgesExplored() << endl;
//                delete(atei);
//            }
//        }
//        else
//        {
            for(int k = 1; k <= atoi(argv[3]); k++)
            {
                for(int B = 1; B <= atoi(argv[4]); B++)
                {
                    cout << "Tree size=" << atoi(argv[2]) << "\tk=" << k << "\tB=" << B << endl;
//                    cout << "Inst\tOpt\tPL\tGL\tDE_Opt\tDE PL\tDE GL\tOpt-PL\tOpt-GL" << endl;
                    double Opt_sum = 0, Pl_sum = 0, GL_sum = 0, DE_OPT_sum = 0, DE_PL_sum = 0, DE_GL_sum = 0, ratio_Opt_PL = 0, ratio_Opt_GL = 0, ratio_Opt_PL_min = 1, ratio_Opt_GL_min = 1;
                    for(int i = 0; i < atoi(argv[1]); i++)
                    {
                        srand(static_cast<unsigned int>(time(NULL) * (i + 1)));
                        auto tree = TreeGenerator::generateRandomTree(atoi(argv[2]));
                        auto atei = new AgentTreeExplorationInstance(tree, k, B);
                        double opt_frac = 0;
                        LinearProgrammingSolver solver = LinearProgrammingSolver();
                        AgentTreeExplorationSolution solution = solver.solver(atei, &opt_frac);
                        AgentTreeExplorationSolution glouton = gloutonSolver::solver(atei);
//                cout << i << "\t" << opt_frac << "\t" << solution.getNumberOfEdgesExplored() << "\t" << glouton.getNumberOfEdgesExplored() << "\t" << solver.doubellyCovered() << "\t" << solution.getNumberOfEdgesDoublellyExplored()
//                     << "\t" << glouton.getNumberOfEdgesDoublellyExplored() << "\t" << solution.getNumberOfEdgesExplored()/opt_frac << "\t" << glouton.getNumberOfEdgesExplored()/opt_frac << endl;
                        Opt_sum += opt_frac;
                        Pl_sum += solution.getNumberOfEdgesExplored();
                        GL_sum +=  glouton.getNumberOfEdgesExplored();
                        DE_OPT_sum += solver.doubellyCovered();
                        DE_PL_sum += solution.getNumberOfEdgesDoublellyExplored();
                        DE_GL_sum += glouton.getNumberOfEdgesDoublellyExplored();
                        ratio_Opt_PL += solution.getNumberOfEdgesExplored()/opt_frac;
                        ratio_Opt_GL += glouton.getNumberOfEdgesExplored()/opt_frac;

                        if(ratio_Opt_PL_min > solution.getNumberOfEdgesExplored()/opt_frac)
                            ratio_Opt_PL_min = solution.getNumberOfEdgesExplored()/opt_frac;
                        if(ratio_Opt_GL_min > glouton.getNumberOfEdgesExplored()/opt_frac)
                            ratio_Opt_GL_min = glouton.getNumberOfEdgesExplored()/opt_frac;
                        delete(atei);
                    }
                    cout << "mean_Opt\tmean_Pl\tmean_GL\tMean_DL_Opt\tMean_DL_PL\tMean_DL_Gl\tratio_opt_Pl\tratio_opt_GL\tOpt_covered\tPL_covered\tGl_covered\n"
                         << Opt_sum/atoi(argv[1]) << "\t" << Pl_sum/atoi(argv[1]) << "\t" << GL_sum/atoi(argv[1]) << "\t" << DE_OPT_sum/atoi(argv[1]) << "\t"
                         << DE_PL_sum/atoi(argv[1]) << "\t" << DE_GL_sum/atoi(argv[1]) << "\t" << ratio_Opt_PL/atoi(argv[1]) << "\t" << ratio_Opt_GL/atoi(argv[1])
                         << "\t" << Opt_sum/atoi(argv[1])/(atoi(argv[2]) - 1) << "\t" << Pl_sum/atoi(argv[1])/(atoi(argv[2]) - 1) << "\t" << GL_sum/atoi(argv[1])/(atoi(argv[2]) - 1) << endl;
                    cout << "\nmin ratio Pl/Opt\tmin ratio Gl/Opt\n" << ratio_Opt_PL_min << "\t" << ratio_Opt_GL_min << endl;
                    cout << "\n" << endl;
                }

            }


        //}
    }

	return 0;
}