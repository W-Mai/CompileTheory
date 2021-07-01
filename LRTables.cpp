//
// Created by Esther on 2021/7/1.
//
#include "LRTables.h"

std::vector<GenExpr> gen_expressions{};
ACTIONTable_type action_table{};
GOTOTable_type goto_table{};

void init_lr_tables(){
    gen_expressions.push_back({"A", {{.token="s"}}});

    action_table[TOKEN_SYN::SYN_VERTICAL_LINE] = {};
}