//
// Created by Esther on 2021/7/1.
//

#ifndef COMPILETHEORY_LRTABLES_H
#define COMPILETHEORY_LRTABLES_H

#include "Constants.h"

extern std::vector<GenExpr> gen_expressions;
extern ACTIONTable_type action_table;
extern GOTOTable_type goto_table;

void init_lr_tables();
#endif //COMPILETHEORY_LRTABLES_H
