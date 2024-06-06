#pragma once
struct TTreeNode {
	TRecord rec;
	TTreeNode* pLeft, * pRight;
	int bal;

	TTreeNode(const TRecord& _rec)
	{
		rec = _rec;
		pLeft = nullptrptr;
		pRight = nullptrptr;
		bal = H_OK;
	}
};

class TTreeTable :public TTable
{
protected:
	TTreeNode* pRoot, * pCurr, * pPrev;
	stack <TTreeNode*> st;
	int CurrPos, level = 0;
public:
	TTreeTable()
	{
		pRoot = pCurr = pPrev = nullptr;
	}
	bool Find(TKey k)
	{
		pPrev = nullptr;
		pCurr = pRoot;
		while (pCurr != nullptr)
		{
			eff++;
			if (pCurr->rec.key == k) break;
			else
			{
				pPrev = pCurr;
				if (pCurr->rec.key > k)
				{
					pCurr = pCurr->pLeft;
				}
				else pCurr = pCurr->pRight;

			}
		}
		if (pCurr != nullptr) return true;
		else { pCurr = pPrev; return false; }
	}
	void Insert(TRecord _rec)
	{
		bool res = Find(_rec.key);
		if (res == true) return;
		else
		{
			DataCount++;
			TTreeNode* pNew = new TTreeNode(_rec);

			if (pRoot == nullptr) pRoot = pNew;
			else
			{
				if (pCurr->rec.key > _rec.key)
					pCurr->pLeft = pNew;
				else pCurr->pRight = pNew;
			}
		}
	}
	void Delete(TKey k)
	{
		bool res = Find(k);
		TTreeNode* pDel;
		if (res == false) return;

		else

			if (pCurr->pRight == nullptr)
			{
				pDel = pCurr;
				if (pPrev == nullptr) pRoot = pCurr->pLeft;
				else
				{
					if (pPrev->rec.key > pCurr->rec.key)
					{
						pPrev->pLeft = pCurr->pLeft;
					}
					else
					{
						if (pPrev->rec.key < pCurr->rec.key)
						{
							pPrev->pRight = pCurr->pLeft;
						}
					}
				}

			}
			else

				if (pCurr->pLeft == nullptr)
				{
					pDel = pCurr;
					if (pPrev == nullptr) pRoot = pCurr->pRight;
					else
					{
						if (pPrev->rec.key > pCurr->rec.key)
						{
							pPrev->pLeft = pCurr->pRight;
						}
						else
						{
							if (pPrev->rec.key < pCurr->rec.key)
							{
								pPrev->pRight = pCurr->pRight;
							}
						}
					}
				}

				else
				{
					TTreeNode* pN = pCurr->pLeft;
					pPrev = pCurr;
					while (pN->pRight != nullptr)
					{
						pPrev = pN;
						pN = pN->pRight;
						eff++;
					}
					pCurr->rec = pN->rec;
					if (pPrev->pRight == pN)
					{
						pPrev->pRight = pN->pLeft;


					}
					else
					{
						pPrev->pLeft = pN->pLeft;
					}
					pDel = pN;
					eff++;

				}
		eff++;
		delete pDel;
		DataCount--;

	}
	bool IsFull() { return false; };
	int GetKey() { return pCurr->rec.key; };
	int GetValue() { return pCurr->rec.val; };
	void SetCurrentRecord(TRecord record)
	{
		pCurr->rec.key = record.key;
		pCurr->rec.val = record.val;
	};
	void Reset()
	{
		TTreeNode* pNode = pCurr = pRoot;
		while (!st.empty()) st.pop();
		CurrPos = 0;
		while (pNode != nullptr)
		{
			st.push(pNode);
			pCurr = pNode;
			pNode = pNode->pLeft;
		}
	}
	void GoNext()
	{
		if (pCurr != nullptr)
		{
			TTreeNode* pNode = pCurr = pCurr->pRight;
			st.pop();
			while (pNode != nullptr)
			{
				st.push(pNode);
				pCurr = pNode;
				pNode = pNode->pLeft;
			}
			if ((pCurr == nullptr) && !st.empty())
			{
				pCurr = st.top();
			}
			CurrPos++;
		}
	}
	bool IsEnd()
	{
		return CurrPos >= DataCount;
	}
	void DeleteTreeTab(TTreeNode* pNode)
	{
		if (pNode != nullptr)
		{
			DeleteTreeTab(pNode->pLeft);
			DeleteTreeTab(pNode->pRight);
			delete pNode;
		}
	}
	~TTreeTable() { DeleteTreeTab(pRoot); }
	void PrintTreeTab(ostream& os, TTreeNode* pNode)
	{
		if (pNode != nullptrptr)
		{
			for (int i = 0; i < level; i++)
			{
				os « " ";
			}
			os « pNode->rec.key « std::endl;
			level++;
			PrintTreeTab(os, pNode->pRight);
			PrintTreeTab(os, pNode->pLeft);
			level--;

		}
	}

	void PrintTreeTab_f(TTreeNode* pNode, ofstream& fout)
	{

		if (pNode != nullptr)
		{
			for (int i = 0; i < level; i++)
			{
				fout << " ";
			}
			fout << pNode->rec.key << std::endl;
			level++;
			PrintTreeTab_f(pNode->pRight, fout);
			PrintTreeTab_f(pNode->pLeft, fout);
			level--;

		}

	}
	void PrintTree_f()
	{
		ofstream fout("text.txt");
		level = 0; // Сбрасываем уровень перед началом печати дерева
		PrintTreeTab_f(pRoot, fout);
		fout.close();
		// Вызываем рекурсивную функцию для печати дерева, начиная с корневого узла
	}
	/*void PrintTreeTab(ostream& os, TTreeNode* pNode)
	{
	if (pNode != nullptrptr)
	{
	level++; // Увеличиваем уровень перед переходом к следующему узлу
	PrintTreeTab(os, pNode->pRight); // Рекурсивный вызов для правого поддерева
	for (int i = 0; i < level; i++)
	{
	os « "\t"; // Вывод отступов в соответствии с текущим уровнем
	}
	os « pNode->rec.key « endl; // Вывод ключа узла
	PrintTreeTab(os, pNode->pLeft); // Рекурсивный вызов для левого поддерева
	level--; // Уменьшаем уровень после обработки узла и его поддеревьев
	}
	}*/
	void PrintTree(ostream& os)
	{
		level = 0; // Сбрасываем уровень перед началом печати дерева
		PrintTreeTab(os, pRoot); // Вызываем рекурсивную функцию для печати дерева, начиная с корневого узла
	}
};

using namespace std;
typedef int TKey;
typedef int TValue;
struct TRecord {
	TKey key;
	TValue val;
	TRecord()
	{
		key = 0;
		val = 0;
	}

	TRecord(TKey key, TValue value)
	{
		this->key = key;
		this->val = value;
	}

	TRecord& operator=(const TRecord& other)
	{
		key = other.key;
		val = other.val;
		return *this;
	}

	void output()
	{
		std::cout « "( " « key « " " « val « " )" « std::endl;
	}
	bool operator == (TRecord other)
	{
		if (this->val == other.val)
			return true;
		else
			return false;
	}
	bool operator != (const TRecord& other)
	{
		return !(*this == other);
	}

};

class TTable
{
protected:
	int DataCount;
	int eff;
public:
	TTable()
	{
		DataCount = 0;
		eff = 0;
	}
	virtual ~TTable() {}
	int getDataCount()
	{
		return DataCount;
	}
	int getEff()
	{
		return eff;
	}
	void ClearEff()
	{
		eff = 0;
	}
	bool empty()
	{
		return(DataCount == 0);
	}
	virtual bool IsFull() = 0;
	virtual bool Find(TKey key) = 0;
	virtual void Insert(TRecord rec) = 0;
	virtual void Delete(TKey key) = 0;
	virtual void Reset() = 0;
	virtual void GoNext() = 0;
	virtual bool IsEnd() = 0;
	virtual int GetKey() = 0;
	virtual int GetValue() = 0;
	//virtual int GetRecord() = 0;
	friend ostream& operator«(ostream& os, TTable& t)
	{
		for (t.Reset(); !t.IsEnd(); t.GoNext())
		{
			os « "Key "«t.GetKey() «" " « "Val " « t.GetValue() « endl;
		}
		return os;
	}


};

class TBalTree :public TTreeTable
{
protected:
int InsBalTree(TTreeNode*& pNode, TRecord rec)
{
	int res = H_OK; eff++;
	if (pNode == nullptr)
	{
		pNode = new TTreeNode(rec);
		res = H_INC;
		DataCount++;
	}
	else if (pNode->rec.key > rec.key)
	{
		int tmp = InsBalTree(pNode->pLeft, rec);
		if (tmp == H_INC)
		{
			res = LeftBalanse(pNode);
		}
	}
	else if (pNode->rec.key < rec.key)
	{
		int tmp = InsBalTree(pNode->pRight, rec);
		if (tmp == H_INC)
		{
			res = RightBalanse(pNode);
		}
	}
	return res;
}
int LeftBalanse(TTreeNode*& pNode)
{
	eff++;
	int res = H_OK;
	switch (pNode->bal)
	{
	case BalRight:pNode->bal = BalOK;
		res = H_OK;
		break;

	case BalOK:pNode->bal = BalLeft;
		res = H_INC; break;
	case BalLeft:TTreeNode* p1; TTreeNode* p2;
		p1 = pNode->pLeft;

		if (p1->bal == BalLeft)
		{
			pNode->pLeft = p1->pRight;
			p1->pRight = pNode;
			pNode->bal = BalOK;
			pNode = p1;
			pNode->bal = BalOK;
		}
		else
		{
			p2 = p1->pRight;
			p1->pRight = p2->pLeft;
			pNode->pLeft = p2->pRight;
			p2->pLeft = p1;
			p2->pRight = pNode;

			if (p2->bal == BalRight)
			{
				p1->bal = BalLeft;
				pNode->bal = BalOK;
			}
			else
			{
				p1->bal = BalOK;
				pNode->bal = BalRight;
			}
			pNode = p2;
			pNode->bal = BalOK;
		}
		res = H_OK;
	}
	return res;
}
int RightBalanse(TTreeNode*& pNode)
{
	eff++;
	int res = H_OK;
	switch (pNode->bal)
	{
	case BalLeft:pNode->bal = BalOK;
		res = H_OK;
		break;

	case BalOK:pNode->bal = BalRight;
		res = H_INC; break;
	case BalRight:TTreeNode* p1, * p2;
		p1 = pNode->pRight;
		if (p1->bal == BalRight)
		{
			pNode->pRight = p1->pLeft;
			p1->pLeft = pNode;
			pNode->bal = BalOK;
			pNode = p1;
			pNode->bal = BalOK;
		}
		else
		{
			p2 = p1->pLeft;
			p1->pLeft = p2->pRight;
			pNode->pRight = p2->pLeft;
			p2->pRight = p1;
			p2->pLeft = pNode;

			if (p2->bal == BalRight)
			{
				p1->bal = BalLeft;
				pNode->bal = BalOK;
			}
			else
			{
				p1->bal = BalOK;
				pNode->bal = BalRight;
			}
			pNode = p2;
			pNode->bal = BalOK;
		}
		res = H_OK;
	}
	return res;
}

int DeleteRec(TTreeNode*& pNode, TKey key)
{
	int res = H_OK; eff++;
	if (pNode == nullptr) return H_OK;
	if (pNode->rec.key > key)
	{
		res = DeleteRec(pNode->pLeft, key);
		if (res != H_OK)
			res = RightBalanse(pNode);
	}
	else if (pNode->rec.key < key)
	{
		res = DeleteRec(pNode->pRight, key);
		if (res != H_OK) res = LeftBalanse(pNode);
	}
	else
	{
		DataCount--;
		if (pNode->pRight == nullptr && pNode->pLeft == nullptr)
		{
			delete pNode;
			pNode = nullptr;
			res = H_DEC;
		}
		else if (pNode->pRight == nullptr)
		{
			pNode->rec = pNode->pLeft->rec;
			delete pNode->pLeft;
			pNode->pLeft = nullptr;
			pNode->bal = BalOK;
			res = H_DEC;
		}
		else if (pNode->pLeft == nullptr)
		{
			pNode->rec = pNode->pRight->rec;
			delete pNode->pRight;
			pNode->pRight = nullptr;
			pNode->bal = BalOK;
			res = H_DEC;
		}
		else
		{
			TTreeNode* l, * r;
			l = pNode->pLeft; r = pNode->pRight;
			TTreeNode* min = FindMin(r);
			res = RemoveMin(r);
			pNode->rec = min->rec;
			delete min;
			pNode->pLeft = l; pNode->pRight = r;
			if (res != H_OK) res = LeftBalanse(pNode);

		}
	}
	return res;
}
TTreeNode* FindMin(TTreeNode* r)
{
	efficiency++;
	if (pRoot == nullptr) return nullptr;
	TTreeNode* curr = pRoot->pRight;
	while (curr->pLeft != nullptr) curr = curr->pLeft;
	return curr;
}
int RemoveMin(TTreeNode*& pNode)
{
	eff++;
	int res = H_OK;
	if (pNode->pLeft == nullptr)
	{
		pNode = pNode->pRight;
		res = H_DEC;
	}
	else
	{
		res = RemoveMin(pNode->pLeft);
		if (res != H_OK)
			res = RightBalanse(pNode);
	}
	return res;
}
public:
	void Insert(TRecord rec)
	{
		bool res = Find(rec.key);
		if (res == true) { return; }
		InsBalTree(pRoot, rec);
	}
	void Delete(TKey key)
	{
		if (!Find(key)) return;
		DeleteRec(pRoot, key);
	}
};

int InsBalTree(TTreeNode*& pNode, TRecord rec)
{
	int res = H_OK; eff++;
	if (pNode == NULL)
	{
		pNode = new TTreeNode(rec);
		res = H_INC;
		DataCount++;
	}
	else if (pNode->rec.key > rec.key)
	{
		int tmp = InsBalTree(pNode->pLeft, rec);
		if (tmp == H_INC)
		{
			res = LeftBalanse(pNode);
		}
	}
	else if (pNode->rec.key < rec.key)
	{
		int tmp = InsBalTree(pNode->pRight, rec);
		if (tmp == H_INC)
		{
			res = RightBalanse(pNode);
		}
	}
	return res;
}
int LeftBalanse(TTreeNode*& pNode)
{
	eff++;
	int res = H_OK;
	switch (pNode->bal)
	{
	case BalRight:pNode->bal = BalOK;
		res = H_OK;
		break;

	case BalOK:pNode->bal = BalLeft;
		res = H_INC; break;
	case BalLeft:TTreeNode* p1; TTreeNode* p2;
		p1 = pNode->pLeft;

		if (p1->bal == BalLeft)
		{
			pNode->pLeft = p1->pRight;
			p1->pRight = pNode;
			pNode->bal = BalOK;
			pNode = p1;
			pNode->bal = BalOK;
		}
		else
		{
			p2 = p1->pRight;
			p1->pRight = p2->pLeft;
			pNode->pLeft = p2->pRight;
			p2->pLeft = p1;
			p2->pRight = pNode;

			if (p2->bal == BalRight)
			{
				p1->bal = BalLeft;
				pNode->bal = BalOK;
			}
			else
			{
				p1->bal = BalOK;
				pNode->bal = BalRight;
			}
			pNode = p2;
			pNode->bal = BalOK;
		}
		res = H_OK;
	}
	return res;
}
int RightBalanse(TTreeNode*& pNode)
{
	eff++;
	int res = H_OK;
	switch (pNode->bal)
	{
	case BalLeft:pNode->bal = BalOK;
		res = H_OK;
		break;

	case BalOK:pNode->bal = BalRight;
		res = H_INC; break;
	case BalRight:TTreeNode* p1, * p2;
		p1 = pNode->pRight;
		if (p1->bal == BalRight)
		{
			pNode->pRight = p1->pLeft;
			p1->pLeft = pNode;
			pNode->bal = BalOK;
			pNode = p1;
			pNode->bal = BalOK;
		}
		else
		{
			p2 = p1->pLeft;
			p1->pLeft = p2->pRight;
			pNode->pRight = p2->pLeft;
			p2->pRight = p1;
			p2->pLeft = pNode;

			if (p2->bal == BalRight)
			{
				p1->bal = BalLeft;
				pNode->bal = BalOK;
			}
			else
			{
				p1->bal = BalOK;
				pNode->bal = BalRight;
			}
			pNode = p2;
			pNode->bal = BalOK;
		}
		res = H_OK;
	}
	return res;
}

int DeleteRec(TTreeNode*& pNode, TKey key)
{
	int res = H_OK; eff++;
	if (pNode == NULL) return H_OK;
	if (pNode->rec.key > key)
	{
		res = DeleteRec(pNode->pLeft, key);
		if (res != H_OK)
			res = RightBalanse(pNode);
	}
	else if (pNode->rec.key < key)
	{
		res = DeleteRec(pNode->pRight, key);
		if (res != H_OK) res = LeftBalanse(pNode);
	}
	else
	{
		DataCount--;
		if (pNode->pRight == NULL && pNode->pLeft == NULL)
		{
			delete pNode;
			pNode = NULL;
			res = H_DEC;
		}
		else if (pNode->pRight == NULL)
		{
			pNode->rec = pNode->pLeft->rec;
			delete pNode->pLeft;
			pNode->pLeft = NULL;
			pNode->bal = BalOK;
			res = H_DEC;
		}
		else if (pNode->pLeft == NULL)
		{
			pNode->rec = pNode->pRight->rec;
			delete pNode->pRight;
			pNode->pRight = NULL;
			pNode->bal = BalOK;
			res = H_DEC;
		}
		else
		{
			TTreeNode* l, * r;
			l = pNode->pLeft; r = pNode->pRight;
			TTreeNode* min = FindMin(r);
			res = RemoveMin(r);
			pNode->rec = min->rec;
			delete min;
			pNode->pLeft = l; pNode->pRight = r;
			if (res != H_OK) res = LeftBalanse(pNode);

		}
	}
	return res;
}
TTreeNode* FindMin(TTreeNode* r)
{
	eff++;
	if (pRoot == NULL) return NULL;
	TTreeNode* curr = pRoot->pRight;
	while (curr->pLeft != NULL) curr = curr->pLeft;
	return curr;
}
int RemoveMin(TTreeNode*& pNode)
{
	eff++;
	int res = H_OK;
	if (pNode->pLeft == NULL)
	{
		pNode = pNode->pRight;
		res = H_DEC;
	}
	else
	{
		res = RemoveMin(pNode->pLeft);
		if (res != H_OK)
			res = RightBalanse(pNode);
	}
	return res;
}
public:
	void Insert(TRecord rec)
	{
		bool res = Find(rec.key);
		if (res == true) { return; }
		InsBalTree(pRoot, rec);
	}
	void Delete(TKey key)
	{
		if (!Find(key)) return;
		DeleteRec(pRoot, key);
	}
};

