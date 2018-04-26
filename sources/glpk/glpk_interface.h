//
// Created by raphael on 4/22/18.
//

#ifndef TREE_EXPLORER_GLPK_INTERFACE_H
#define TREE_EXPLORER_GLPK_INTERFACE_H

#include <glpk.h>
#include <string>

using namespace std;
class glpk_interface {
private:
	glp_prob *root;

public:
	enum glp_opti_dir {min = 1, max = 2};
	enum glp_var_dir {free = 1, lower = 2, upper = 3, double_bound = 4, fixed
		= 5};

	glpk_interface();

	glp_prob *getRoot() const;

	void createProblem();

	void setProbName(const char *str);

	void setObjDir(glp_opti_dir dir);
	void setObjCoef(int index, double coef);

	void addRows(int numberRows);
	void setRowName(int index, const char *str);
	void setRowBnds(int index, glp_var_dir dir, double lbnds, double ubnds);

	void addCols(int numberRows);
	void setColName(int index, const char *str);
	void setColBnds(int index, glp_var_dir dir, double lbnds, double ubnds);

	void loadMatrix(int size, const int *ia, const int *ja, const double *ar);

	void simplex(const glp_smcp *ptr);

	double getObjVal();
	double getColPrim(int index);

	void writeMPS(const char *fname);

	void writeSol(const char *fname);

	void printSol(const char *fname);

	double getRowDual(int index);

	virtual ~glpk_interface();
};


#endif //TREE_EXPLORER_GLPK_INTERFACE_H
