#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<memory.h>

#include"../util/util.h"
#include"database.h"
#include"../util/util.h"
#include"ekt.h"
#include"monster.h"

Database *Database::s_pInstance = nullptr;

Database::Database()
{
    ;
}

Database::~Database()
{
    ;
}

Database *Database::getInstance()
{
    if(s_pInstance == nullptr)
    {
        LOG(std::cout, "Database object created");
        s_pInstance = new Database();
    }
    return s_pInstance;
}