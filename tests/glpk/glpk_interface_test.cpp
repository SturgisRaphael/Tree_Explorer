//
// Created by raphael on 4/24/18.
//

#include <gtest/gtest.h>
#include <glpk.h>
#include "../../sources/glpk/glpk_interface.h"

TEST(glpk, glpk_no_interface_Test) {
/* declare variables */
	glp_prob *lp;
	int ia[1+1000], ja[1+1000];
	double ar[1+1000], z, x1, x2;
	/* create problem */
	lp = glp_create_prob();
	glp_set_prob_name(lp, "short");
	glp_set_obj_dir(lp, GLP_MAX);
	/* fill problem */
	glp_add_rows(lp, 2);
	glp_set_row_name(lp, 1, "p");
	glp_set_row_bnds(lp, 1, GLP_UP, 0.0, 1.0);
	glp_set_row_name(lp, 2, "q");
	glp_set_row_bnds(lp, 2, GLP_UP, 0.0, 2.0);
	glp_add_cols(lp, 2);
	glp_set_col_name(lp, 1, "x1");
	glp_set_col_bnds(lp, 1, GLP_LO, 0.0, 0.0);
	glp_set_obj_coef(lp, 1, 0.6);
	glp_set_col_name(lp, 2, "x2");
	glp_set_col_bnds(lp, 2, GLP_LO, 0.0, 0.0);
	glp_set_obj_coef(lp, 2, 0.5);
	ia[1] = 1, ja[1] = 1, ar[1] = 1.0; /* a[1,1] = 1 */
	ia[2] = 1, ja[2] = 2, ar[2] = 2.0; /* a[1,2] = 2 */
	ia[3] = 2, ja[3] = 1, ar[3] = 3.0; /* a[2,1] = 3 */
	ia[4] = 2, ja[4] = 2, ar[4] = 1.0; /* a[2,2] = 1 */
	glp_load_matrix(lp, 4, ia, ja, ar);
	/* solve problem */
	glp_simplex(lp, NULL);
	/* recover and display results */
	z = glp_get_obj_val(lp);
	x1 = glp_get_col_prim(lp, 1);
	x2 = glp_get_col_prim(lp, 2);
	printf("z = %g; x1 = %g; x2 = %g\n", z, x1, x2);
	/* housekeeping */
	glp_delete_prob(lp);
	glp_free_env();
}

TEST(glpk, glpk_with_interface_Test) {
	/* declare variables */
	glpk_interface lp;
	int ia[1+1000], ja[1+1000];
	double ar[1+1000], z, x1, x2;
	/* create problem */
	lp.createProblem();
	lp.setProbName("short");
	lp.setObjDir(glpk_interface::max);
	/* fill problem */
	lp.addRows(2);
	lp.setRowName(1, "p");
	lp.setRowBnds(1, glpk_interface::upper, 0.0, 1.0);
	lp.setRowName(2, "q");
	lp.setRowBnds(2, glpk_interface::upper, 0.0, 1.0);

	lp.addCols(2);
	lp.setColName(1, "x1");
	lp.setColBnds(1, glpk_interface::lower, 0.0, 0.0);
	lp.setObjCoef(1, 0.6);
	lp.setColName(2, "x2");
	lp.setColBnds(2, glpk_interface::lower, 0.0, 0.0);
	lp.setObjCoef(2, 0.5);
	ia[1] = 1, ja[1] = 1, ar[1] = 1.0; /* a[1,1] = 1 */
	ia[2] = 1, ja[2] = 2, ar[2] = 2.0; /* a[1,2] = 2 */
	ia[3] = 2, ja[3] = 1, ar[3] = 3.0; /* a[2,1] = 3 */
	ia[4] = 2, ja[4] = 2, ar[4] = 1.0; /* a[2,2] = 1 */
	lp.loadMatrix(4, ia, ja, ar);
	/* solve problem */
	lp.simplex(NULL);
	/* recover and display results */
	z = glp_get_obj_val(lp.getRoot());
	x1 = glp_get_col_prim(lp.getRoot(), 1);
	x2 = glp_get_col_prim(lp.getRoot(), 2);
	printf("z = %g; x1 = %g; x2 = %g\n", z, x1, x2);
	/* housekeeping */

}