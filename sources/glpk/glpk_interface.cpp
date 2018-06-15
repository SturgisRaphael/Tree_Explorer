//
// Created by raphael on 4/22/18.
//

#include "glpk_interface.h"

glpk_interface::glpk_interface() {
	root = glp_create_prob();
	glp_term_out(GLP_OFF);
}

glp_prob *glpk_interface::getRoot() const {
	return root;
}

void glpk_interface::setProbName(const char *str) {
	glp_set_prob_name(root, str);
}

void glpk_interface::setObjDir(glp_opti_dir dir) {
	switch(dir){
		case min:
			glp_set_obj_dir(this->root, GLP_MIN);
			break;
		case max:
			glp_set_obj_dir(this->root, GLP_MAX);
			break;
	}

}

void glpk_interface::setObjCoef(int index, double coef) {
	glp_set_obj_coef(root, index, coef);
}

void glpk_interface::addRows(int numberRows) {
	glp_add_rows(root, numberRows);
}

void glpk_interface::setRowName(int index, const char *str) {
	glp_set_row_name(root, index, str);
}

void
glpk_interface::setRowBnds(int index, glp_var_dir dir, double lbnds, double ubnds) {
	glp_set_row_bnds(root, index, dir, lbnds, ubnds);
}

void glpk_interface::addCols(int numberRows) {
	glp_add_cols(root, numberRows);
}

void glpk_interface::setColName(int index, const char *str) {
	glp_set_col_name(root, index, str);
}

void glpk_interface::setColBnds(int index, glp_var_dir dir, double lbnds, double ubnds) {
	glp_set_col_bnds(root, index, dir, lbnds, ubnds);
}

void glpk_interface::loadMatrix(int size,const int *ia, const int *ja,
                                const double *ar) {
	glp_load_matrix(root, size, ia, ja, ar);
}

void glpk_interface::simplex(const glp_smcp *ptr) {
	glp_simplex(root, ptr);
}

double glpk_interface::getObjVal() {
	return glp_get_obj_val(root);
}

double glpk_interface::getColPrim(int index) {
	return glp_get_col_prim(root, index);
}

glpk_interface::~glpk_interface() {
	//glp_delete_prob(root);
	glp_free_env();
}

void glpk_interface::createProblem() {
	root = glp_create_prob();
	glp_term_out(GLP_OFF);
}

void glpk_interface::writeMPS(const char *fname) {
	glp_write_mps(root, GLP_MPS_FILE, NULL, fname);
}

void glpk_interface::writeSol(const char *fname) {
	glp_write_sol(root, fname);
}

void glpk_interface::printSol(const char *fname) {
	glp_print_sol(root, fname);
}

double glpk_interface::getRowDual(int index) {
	return glp_get_row_dual(root, index);
}

void glpk_interface::deleteProb() {
	glp_delete_prob(root);
}

void glpk_interface::freeEnv() {
	glp_free_env();
}

void glpk_interface::housekeeping() {
	deleteProb();
	freeEnv();
}

void glpk_interface::int_opt(const glp_iocp *ptr) {
	glp_intopt(root, ptr);
}

void glpk_interface::setColKind(int index, int kind) {
	glp_set_col_kind(root, index, kind);
}

double glpk_interface::mipObjValue() {
	return glp_mip_obj_val(root);
}

double glpk_interface::mipColValue(int index) {
	return glp_mip_col_val(root, index);
}


