#include "TScanTable.h"
#include"TTable.h"
#include"TTreeTable.h"
#include<iostream>




int main()
{
	
	TTreeTable tree;
	TRecord rec1(1, "1");
	TRecord rec2(2, "2");
	TRecord rec3(3, "3");
	tree.Insert(rec1);
	tree.Insert(rec2);
	tree.Insert(rec3);
	tree.PrintTable('file.txt',*tree);
}