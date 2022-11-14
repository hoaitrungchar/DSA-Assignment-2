#ifndef __CONCAT_STRING_TREE_H__
#define __CONCAT_STRING_TREE_H__

#include "main.h"

class NodeAVL {
public:
    NodeAVL* ptrleft;
    NodeAVL* ptrright;
    int height;
    int heightleft;
    int heightright;
    long long id;
public:
    NodeAVL() {
        id = 0;
        ptrleft = NULL;
        ptrright = NULL;
        height= 0;
        heightleft = heightright = 0;
    };
    NodeAVL(int otherid)
    {
        id = otherid;
        ptrleft = NULL;
        ptrright = NULL;
        height = 0;
        heightleft = heightright = 0;
    };
    void updateheight() {
        if (heightleft > heightright) height = heightleft;
        else height = heightright;
    };
    bool isnotbalance() {
        int n = this->heightright - this->heightleft;
        if (n > 1 || n < -1) return true;
        return false;
    }
};
class ParentsTree {
public:
    NodeAVL* root;
    int nodesize;
public:
    ParentsTree() {
        root = new NodeAVL();
        nodesize = 1;
    };
    NodeAVL* rightRotate(NodeAVL* y)
    {
        NodeAVL* x = y->ptrleft;
        NodeAVL* T2 = x->ptrright;

        x->ptrright = y;
        y->ptrleft = T2;
        
        y->heightleft =1+T2->height;
        y->updateheight();
        x->heightright = y->height+1;
        x->updateheight();
        return x;
    }
    NodeAVL* leftRotate(NodeAVL* x)
    {
        NodeAVL* y = x->ptrright;
        NodeAVL* T2 = y->ptrleft;

        y->ptrleft = x;
        x->ptrright = T2;

        x->heightright = T2->height + 1;
        x->updateheight();
        y->heightleft = x->height + 1;
        y->updateheight();
        
        return y;
    }
    void canbangAVL(NodeAVL* node) {
        if (node->heightleft - node->heightright > 1 && node->id < root->id) {
            rightRotate(node);
            return;
        }
        else if (node->heightleft - node->heightright <-1 && node->id > root->id) {
            leftRotate(node);
            return;
        }
        else if (node->heightleft - node->heightright > 1 && node->id >root->id) {
            NodeAVL*temp=rightRotate(node);
            leftRotate(temp);
            return;
        }
        else {
            NodeAVL* temp = leftRotate(node);
            rightRotate(node);
            return;
        }
        return;
    };
   
    
    void addNodeAVL(int id) {
        NodeAVL* cur = this->root;
        NodeAVL* temp = NULL;
        while (cur != NULL) {
            if (cur->id > id) {
                cur->heightleft = cur->heightleft + 1;
                cur->updateheight();
                if (cur->isnotbalance()) temp = cur;
                if (cur->ptrleft == NULL) {
                    cur->ptrleft = new NodeAVL(id);
                    break;
                }
                cur = cur->ptrleft;
            }
            else if (cur->id < id) {
                cur->heightright = cur->heightright + 1;
                cur->updateheight();
                if (cur->isnotbalance()) temp = cur;
                
                if (cur->ptrright == NULL) {
                    cur->ptrright = new NodeAVL(id);
                    break;
                }
                cur = cur->ptrright;
            }
        }
       
        if (temp != NULL) canbangAVL(temp);
        nodesize++;
    }; 
    
      
    
    void delNodeAVL(int othersid) {
        
        NodeAVL* cur = root;
        NodeAVL* precur = NULL;
        int checkright = -1;
        NodeAVL* temp = NULL;
        if (cur == NULL) return;
        while (cur->id != othersid) {
            if (cur->id > othersid) {
                cur->heightleft = cur->heightleft - 1;
                cur->updateheight();
                if (cur->isnotbalance()) temp = cur;
                precur = cur;
                checkright = 0;
                cur = cur->ptrleft;
            }
            else if (cur->id < othersid) {
                cur->heightright = cur->heightright - 1;
                cur->updateheight();
                if (cur->isnotbalance()) temp = cur;
                precur = cur;
                cur = cur->ptrright;
                checkright = 1;
            }
        }
        if (cur == NULL) return;
       if ((cur->ptrleft == NULL) || (cur->ptrright == NULL))
       {
            NodeAVL* temp1 = NULL;
            if (cur->ptrleft != NULL) {
                temp1 = cur->ptrleft;
                cur->id = temp1->id;
                cur->ptrleft = temp1->ptrleft;
                cur->ptrright = temp1->ptrright;
                delete temp1;
            }
            else {
                temp1 = cur->ptrright;
                if (temp1 != NULL) {
                    cur->id = temp1->id;
                    cur->ptrleft = temp1->ptrleft;
                    cur->ptrright = temp1->ptrright;
                    delete temp1;
                }
                else {
                    if (precur == NULL) {
                        root = NULL;
                        delete cur;
                    }
                    else {
                        if (checkright == 1) precur->ptrright = NULL;
                        else precur->ptrleft = NULL;
                        delete cur;
                        
                    }
                }
            }
        }
        else
        {

            NodeAVL* temp2 = root->ptrleft;
            NodeAVL* curtemp = root->ptrleft;
            while (curtemp != NULL)
            {
                curtemp->heightright = curtemp->heightright - 1;
                curtemp = curtemp->ptrright;
            }
            root->id = temp2->id;
            delete temp2;
            temp2 = NULL;
        }
        if (temp != NULL) canbangAVL(temp);
        nodesize--;

    };

    int size() const {
        if(root!=NULL)
        return nodesize;
        return 0;
    };
    string toStringPreOrderrec(NodeAVL* node) const {
        if (node == NULL) return "";
        string s = "";
        if (node != root) s += ",";
        s += "(id=";
        int x = node->id;
        stringstream ss1; ss1 << x;
        string tmp1; ss1 >> tmp1;
        s += tmp1;
        s += ")";
        s += toStringPreOrderrec(node->ptrleft);
        s += toStringPreOrderrec(node->ptrright);
        return s;

    };
    string toStringPreOrder() const {
        string res = "";
        res += '"'; res += "ParentsTree[";
        res += toStringPreOrderrec(this->root);
        res += "]";
        return res;
    };
    void deleteall(NodeAVL* node) {
        if (node == NULL) return;
        deleteall(node->ptrleft);
        deleteall(node->ptrright);
        delete node;

    }
    ~ParentsTree() {
        deleteall(root);
        root = NULL;
        nodesize = 0;
    };
};
static long long staticid = 0;
static int xoahet = 0;
class NodeBST {
public:
    int leftlengthdata;
    int lengthdata;
    string data;
    NodeBST* ptrleft;
    NodeBST* ptrright;
    int chuadata = 0;
    long long id = 0;
    ParentsTree* AVLtree = new ParentsTree();
public:
    NodeBST() {
        xoahet++;
        leftlengthdata = 0;
        lengthdata = 0;
        ptrleft = NULL;
        ptrright = NULL;
        chuadata = 0;
        staticid++;
        if (staticid > 10000000) throw overflow_error("Id is overflow!");
        id = staticid;
        AVLtree->root->id = staticid;
    };
    NodeBST(string s) {
        xoahet++;
        data = s;
        ptrleft = NULL;
        ptrright = NULL;
        lengthdata = data.length();
        leftlengthdata = 0;
        chuadata = 1;
        staticid++;
        if (staticid > 10000000) throw overflow_error("Id is overflow!");
        id = staticid;
        AVLtree->root->id = staticid;
    };
    NodeBST(const char* s) {
        xoahet++;
        data = s;
        ptrleft = NULL;
        ptrright = NULL;
        lengthdata = data.length();
        leftlengthdata = 0;
        chuadata = 1;
        staticid++;
        if (staticid > 10000000) throw overflow_error("Id is overflow!");
        id = staticid;
        AVLtree->root->id = staticid;
    };
    NodeBST(NodeBST* other)
    {
        xoahet++;
        this->data = other->data;
        this->lengthdata = other->lengthdata;
        this->leftlengthdata = other->leftlengthdata;
        this->chuadata = other->chuadata;
        ptrleft = ptrright = NULL;
        staticid++;
        if (staticid > 10000000) throw overflow_error("Id is overflow!");
        id = staticid;
        AVLtree->root->id = staticid;
    }
    ~NodeBST() {
        xoahet--;
        if(AVLtree!=NULL)
        AVLtree->~ParentsTree();
        AVLtree = NULL;
    };
};

class ConcatStringTree {
public:
    NodeBST* root;
    int lengthstr;
public:
    ConcatStringTree() {
        root = NULL;
        lengthstr = 0;
    }
    ConcatStringTree(const char* s) {
        root = new NodeBST(s);
        lengthstr = root->lengthdata;



    };
    void reset() {
        this->root = NULL;
        lengthstr = 0;
    }
    int length() const {
        return lengthstr;
    };

    char getrecur(int index, NodeBST* cur)
    {
        if (cur->chuadata == 1) return cur->data[index];
        if (index < cur->leftlengthdata) return getrecur(index, cur->ptrleft);
        return getrecur(index, cur->ptrright);
    };
    char get(int index) {
        if (index<0 || index>lengthstr - 1) throw out_of_range("Index of string is invalid!");
        return getrecur(index, root);
    };

    int indexOfrecur(char c, NodeBST* cur) {
        if (cur->chuadata == 1) {
            for (int i = 0; i < cur->data.length(); i++)
            {
                if (cur->data[i] == c) return i;
            }
            return -1;
        }
        int x, y; x = y = -1;
        if (cur->ptrleft != NULL) x = indexOfrecur(c, cur->ptrleft);
        if (cur->ptrright != NULL) y = indexOfrecur(c, cur->ptrright);
        if (x == -1 && y == -1) return -1;
        else if (x != -1) return x;
        else return y;
    };
    int indexOf(char c) {
        return indexOfrecur(c, root);
    };

    string toStringPreOrderrecur(NodeBST* cur) const {
        string res = "";
        if (cur != root)res += ";";
        res += "(";
        res += "LL=";
        int x = cur->leftlengthdata;
        int y = cur->lengthdata;
        stringstream ss1; ss1 << x;
        stringstream ss2; ss2 << y;
        string tmp1, tmp2; ss1 >> tmp1; ss2 >> tmp2;
        res += tmp1;
        res += ",L=";
        res += tmp2;
        res += ",";
        if (cur->chuadata == 0) res += "<NULL>)";
        else res += '"' + cur->data + '"' + ")";
        if (cur->ptrleft != NULL) res += toStringPreOrderrecur(cur->ptrleft);
        if (cur->ptrright != NULL)res += toStringPreOrderrecur(cur->ptrright);
        return res;
    };
    string toStringPreOrder() const {
        string res = ""; res += '"';
        res += "ConcatStringTree[";
        res += toStringPreOrderrecur(root);
        res += "]";
        res += '"';
        return res;
    };

    string toStringrecur(NodeBST* cur) const
    {
        string res = "";
        if (cur->ptrleft != NULL) res += toStringrecur(cur->ptrleft);
        if (cur->ptrright != NULL) res += toStringrecur(cur->ptrright);
        if (cur->chuadata == 1) res += cur->data;
        return res;
    };
    string toString() const {
        string res = ""; res += '"';
        res += "ConcatStringTree[";
        res += '"';
        res += toStringrecur(root);
        res += '"';
        res += "]";
        res += '"';
        return res;
    };

    ConcatStringTree concat(const ConcatStringTree& otherS) const {
        static ConcatStringTree res; res.reset();
        res.root = new NodeBST();
        res.lengthstr = this->lengthstr + otherS.lengthstr;
        res.root->ptrleft = this->root;
        res.root->ptrright = otherS.root;
        this->root->AVLtree->addNodeAVL(res.root->id);
        otherS.root->AVLtree->addNodeAVL(res.root->id);
        res.root->chuadata = 0;
        res.root->lengthdata = this->lengthstr + otherS.lengthstr;
        res.root->leftlengthdata = this->lengthstr;
        return res;
    };

    void subStringrecur(NodeBST* curcopy, NodeBST* curstart, int from, int to, int isroot, int cungphia, int huongtrai) {//cungphia=2=>lay het cac node o giua
        if (curstart == NULL) return;
        if (isroot == 1)
        {
            if (curstart->chuadata == 1) {
                curcopy->data = curstart->data.substr(from, to - from);
                curcopy->lengthdata = to - from;
                curcopy->leftlengthdata = 0;
                curcopy->ptrleft = curcopy->ptrright = 0;
                curcopy->chuadata = 1;
                return;
            }
            else {
                curcopy->chuadata = 0;
                curcopy->lengthdata = to - from;
                if (to <= curstart->leftlengthdata) {
                    curcopy->leftlengthdata = to - from;
                    curcopy->ptrleft = new NodeBST(curstart->ptrleft);
                    curcopy->ptrleft->AVLtree->addNodeAVL(curcopy->id);
                    curcopy->ptrright = NULL;
                    subStringrecur(curcopy->ptrleft, curstart->ptrleft, from, to, 0, 1, 0);
                }
                else if (from > curstart->leftlengthdata)
                {
                    curcopy->leftlengthdata = 0;
                    curcopy->ptrleft = NULL;
                    curcopy->ptrright = new NodeBST(curstart->ptrright);
                    curcopy->ptrright->AVLtree->addNodeAVL(curcopy->id);
                    subStringrecur(curcopy->ptrright, curstart->ptrright, from - curstart->leftlengthdata, to - curstart->leftlengthdata, 0, 1, 0);
                }
                else {
                    curcopy->leftlengthdata = curstart->leftlengthdata - from;
                    curcopy->ptrleft = new NodeBST(curstart->ptrleft);
                    curcopy->ptrleft->AVLtree->addNodeAVL(curcopy->id);

                    curcopy->ptrright = new NodeBST(curstart->ptrright);
                    curcopy->ptrright->AVLtree->addNodeAVL(curcopy->id);

                    subStringrecur(curcopy->ptrleft, curstart->ptrleft, from, to, 0, 0, 1);
                    subStringrecur(curcopy->ptrright, curstart->ptrright, from, to - curstart->leftlengthdata, 0, 0, 0);
                }
            }
            return;
        }
        else {
            if (cungphia == 1) {
                curcopy->chuadata = 0;
                curcopy->lengthdata = to - from;
                if (curstart->chuadata == 1) {
                    curcopy->data = curstart->data.substr(from, to - from);
                    curcopy->lengthdata = to - from;
                    curcopy->leftlengthdata = 0;
                    curcopy->ptrleft = curcopy->ptrright = 0;
                    curcopy->chuadata = 1;
                    return;
                }
                else {
                    if (to <= curstart->leftlengthdata) {
                        curcopy->leftlengthdata = to - from;
                        curcopy->ptrleft = new NodeBST(curstart->ptrleft);
                        curcopy->ptrleft->AVLtree->addNodeAVL(curcopy->id);
                        curcopy->ptrright = NULL;
                        subStringrecur(curcopy->ptrleft, curstart->ptrleft, from, to, 0, 1, 0);
                    }
                    else if (from > curstart->leftlengthdata)
                    {
                        curcopy->leftlengthdata = 0;
                        curcopy->ptrleft = NULL;
                        curcopy->ptrright = new NodeBST(curstart->ptrright);
                        curcopy->ptrright->AVLtree->addNodeAVL(curcopy->id);
                        subStringrecur(curcopy->ptrright, curstart->ptrright, from - curstart->leftlengthdata, to - curstart->leftlengthdata, 0, 1, 0);
                    }
                    else {
                        curcopy->ptrleft = new NodeBST(curstart->ptrleft);
                        curcopy->ptrleft->AVLtree->addNodeAVL(curcopy->id);
                        curcopy->ptrright = new NodeBST(curstart->ptrright);
                        curcopy->ptrright->AVLtree->addNodeAVL(curcopy->id);

                        subStringrecur(curcopy->ptrleft, curstart->ptrleft, from, to, 0, 0, 1);
                        subStringrecur(curcopy->ptrright, curstart->ptrright, from, to - curstart->leftlengthdata, 0, 0, 0);

                    }
                }
            }
            else {
                if (huongtrai == 1)
                {

                    if (cungphia == 2)//layhet
                    {
                        if (curstart->ptrleft != NULL)
                        {
                            curcopy->ptrleft = new NodeBST(curstart->ptrleft);
                            curcopy->ptrleft->AVLtree->addNodeAVL(curcopy->id);
                            subStringrecur(curcopy->ptrleft, curstart->ptrleft, from, to, 0, 2, 1);
                        }
                        if (curstart->ptrright != NULL)
                        {
                            curcopy->ptrright = new NodeBST(curstart->ptrright);
                            curcopy->ptrright->AVLtree->addNodeAVL(curcopy->id);
                            subStringrecur(curcopy->ptrright, curstart->ptrright, from, to, 0, 2, 1);
                        }
                        return;
                    }
                    curcopy->lengthdata = curstart->lengthdata - from;
                    if (curstart->chuadata == 1)
                    {
                        curcopy->data = curstart->data.substr(from, curstart->lengthdata - from);
                        curcopy->leftlengthdata = 0;
                        curcopy->ptrleft = curcopy->ptrright = NULL;
                        curcopy->chuadata = 1;
                        return;
                    }
                    if (from > curstart->leftlengthdata)
                    {
                        curcopy->chuadata = 0;
                        curcopy->leftlengthdata = 0;
                        curcopy->ptrleft = NULL;
                        curcopy->ptrright = new NodeBST(curstart->ptrright);
                        curcopy->ptrright->AVLtree->addNodeAVL(curcopy->id);

                        subStringrecur(curcopy->ptrright, curstart->ptrright, from - curstart->leftlengthdata, to, 0, 0, 1);
                    }
                    else {
                        curcopy->chuadata = 0;
                        curcopy->leftlengthdata = curstart->leftlengthdata - from;
                        curcopy->ptrleft = new NodeBST(curstart->ptrright);
                        curcopy->ptrleft->AVLtree->addNodeAVL(curcopy->id);

                        curcopy->ptrright = new NodeBST(curstart->ptrright);
                        curcopy->ptrright->AVLtree->addNodeAVL(curcopy->id);
                        subStringrecur(curcopy->ptrleft, curstart->ptrleft, from, to, 0, 0, 1);
                        subStringrecur(curcopy->ptrright, curstart->ptrright, from, to, 0, 2, 1);
                    }
                    }
                    else {
                        if (cungphia == 2)//layhet
                        {
                            if (curstart->ptrleft != NULL)
                            {
                                curcopy->ptrleft = new NodeBST(curstart->ptrleft);
                                curcopy->ptrleft->AVLtree->addNodeAVL(curcopy->id);
                                subStringrecur(curcopy->ptrleft, curstart->ptrleft, from, to, 0, 2, 0);
                            }
                            if (curstart->ptrright != NULL)
                            {
                                curcopy->ptrright = new NodeBST(curstart->ptrright);
                                curcopy->ptrright->AVLtree->addNodeAVL(curcopy->id);
                                subStringrecur(curcopy->ptrright, curstart->ptrright, from, to, 0, 2, 0);
                            }
                            return;
                        }
                        curcopy->lengthdata = to;
                        if (curstart->chuadata == 1)
                        {
                            curcopy->data = curstart->data.substr(0, to);
                            curcopy->lengthdata = to;
                            curcopy->leftlengthdata = 0;
                            curcopy->ptrleft = curcopy->ptrright = NULL;
                            curcopy->chuadata = 1;
                            return;
                        }
                        if (to <= curstart->leftlengthdata + 1)
                        {
                            curcopy->chuadata = 0;
                            curcopy->leftlengthdata = to;
                            curcopy->ptrleft = new NodeBST(curstart->ptrleft);
                            curcopy->ptrleft->AVLtree->addNodeAVL(curcopy->id);
                            curcopy->ptrright = NULL;
                            subStringrecur(curcopy->ptrleft, curstart->ptrleft, from, to, 0, 0, 0);
                        }
                        else {
                            curcopy->chuadata = 0;
                            curcopy->ptrleft = new NodeBST(curstart->ptrright);
                            curcopy->ptrleft->AVLtree->addNodeAVL(curcopy->id);
                            curcopy->ptrright = new NodeBST(curstart->ptrright);
                            curcopy->ptrright->AVLtree->addNodeAVL(curcopy->id);
                            subStringrecur(curcopy->ptrleft, curstart->ptrleft, from, to, 0, 2, 0);
                            subStringrecur(curcopy->ptrright, curstart->ptrright, from, to - curstart->leftlengthdata, 0, 2, 0);
                        }
                    }
                }
            }
            return;
        };
        
    ConcatStringTree subString(int from, int to) const {
        static ConcatStringTree res; res.reset();
        if (from<0 || from>lengthstr - 1) throw out_of_range("Index of string is invalid!");
        if (to<0 || to>lengthstr) throw out_of_range("Index of string is invalid!");
        if (from >= to) throw logic_error("Invalid range!");
        
        res.lengthstr = to - from;
        res.root = new NodeBST(this->root);
        res.subStringrecur(res.root, this->root, from, to, 1, 1, 0);

        return res;
    };

        void reverserecur(NodeBST * curcopy, NodeBST * curstart){
            if (curstart == NULL) return;
            if (curstart->chuadata == 1)
            {
                string s = "";
                int n = curstart->data.size();
                for (int i = 0; i < n; i++)
                {
                    s += curstart->data[n - 1 - i];
                }
                curcopy->data = s;
                return;
            }

            curcopy->leftlengthdata = curstart->lengthdata - curstart->leftlengthdata;
            if (curstart->ptrleft != NULL) {
                curcopy->ptrright = new NodeBST(curstart->ptrleft);
                curcopy->ptrright->AVLtree->addNodeAVL(curcopy->id);
                reverserecur(curcopy->ptrright, curstart->ptrleft);
            }
            if (curstart->ptrright != NULL) {
                curcopy->ptrleft = new NodeBST(curstart->ptrright);
                curcopy->ptrleft->AVLtree->addNodeAVL(curcopy->id);
                reverserecur(curcopy->ptrleft, curstart->ptrright);
            }
        };
        ConcatStringTree reverse() const {
            static ConcatStringTree res; res.reset();
            res.root = new NodeBST(this->root);
            res.lengthstr = this->lengthstr;
            res.root->lengthdata = this->root->lengthdata;
            res.reverserecur(res.root, this->root);
            return res;
        };

        int getParTreeSize(const string & query)const {

            int n = query.size();
            NodeBST* temp = this->root;
            if (temp == NULL)
            {
                throw runtime_error("Invalid character of query");
            }
            for (int i = 0; i < n; i++) {
                if (query[i] == 'l') {
                    temp = temp->ptrleft;
                }
                else if (query[i] == 'r')
                {
                    temp = temp->ptrright;
                }
                if (temp == NULL)
                {
                    throw runtime_error("Invalid character of query");
                }
            }
            return temp->AVLtree->nodesize;
        };
        string getParTreeStringPreOrder(const string & query) const {
            int n = query.size();
            NodeBST* temp = this->root;
            if (temp == NULL)
            {
                throw runtime_error("Invalid character of query");
            }
            for (int i = 0; i < n; i++) {
                if (query[i] == 'l') {
                    temp = temp->ptrleft;
                }
                else if (query[i] == 'r')
                {
                    temp = temp->ptrright;
                }
                if (temp == NULL)
                {
                    throw runtime_error("Invalid character of query");
                }
            }
            return temp->AVLtree->toStringPreOrder();

        };
       
        void deleteAVL(NodeBST* node) {
            if (node == NULL) return;

            node->AVLtree->delNodeAVL(node->id);
            if (node->ptrleft != NULL) {
                node->ptrleft->AVLtree->delNodeAVL(node->id);
            }
            if (node->ptrright != NULL) {
                node->ptrright->AVLtree->delNodeAVL(node->id);
            }
           
        }
        void deleteBST(NodeBST* node) {
            if (node == NULL) return;

            if (node->AVLtree->size() == 0)
            {
                if (node->ptrleft != NULL) {
                    deleteBST(node->ptrleft);
                }
                if (node->ptrright != NULL) {
                    deleteBST(node->ptrright);
                }
                delete node;
                node = NULL;
            }
            return;
        }

        ~ConcatStringTree() {
            if (root != NULL&&xoahet!=0)
            {
                deleteAVL(root);

                deleteBST(root);
                if (root->AVLtree==NULL)
                    root = NULL;
            }
            
        };
    
};

class ReducedConcatStringTree; // forward declaration

class HashConfig {
private:
    int p;
    double c1, c2;
    double lambda;
    double alpha;
    int initSize;

    friend class ReducedConcatStringTree;
public:
    HashConfig() {
    };
    int getsize() {
        return this->initSize;
    };
    int getc1() {
        return this->c1;
    };
    double getalpha() {
        return this->alpha;
    }
    int getc2() {
        return this->c2;
    };
    int getlambda() {
        return this->lambda;
    }
    void operator =(const HashConfig& other)
    {
        this->p = other.p;
        this->c1 = other.c1;
        this->c2 = other.c2;
        this->alpha = other.alpha;
        this->lambda = other.lambda;
        this->initSize = other.initSize;

    }
    int hashfunction(string s) {
        int res = 0;
        int luythua = 1;
        for (int i = 0; i < s.length(); i++)
        {
            res = res + int(s[i]) * luythua;
            res %= initSize;
            luythua %= initSize;
            luythua *= p;
        }
        return res;
    }
};

class LitStringHash {
public:
    HashConfig hashconfig;
    int sizehash;//size toidachua
    int sizecur;//size dachua
    int* hashpoint;//sonodechoden
    int* status;//1cochua,0kochua,-1moixoa
    string* hashtable;
    int lastinserted;
    int loadfactor;
    
public:
    LitStringHash() {
        sizehash = 0;
        lastinserted = -1;
    }
    LitStringHash(const HashConfig& hashConfig) {
        lastinserted = -1;
        this->hashconfig = hashConfig;
        sizehash = hashconfig.getsize();
        status = new int[sizehash];
        hashpoint = new int[sizehash];
        hashtable = new string[sizehash];
        for (int i = 0; i < sizehash; i++) {
            status[i] = 0;
            hashpoint[i] = 0;
        }
    };
    string* addressstring(string s) {
        int x = find(s);
        if (x!=-1)
        {
            hashpoint[x]++;
            lastinserted = x;
            return &hashtable[x];
        }
        else {
            
            if (sizecur >= sizehash)
                reaheasing();
            x = quadraticprobing(s, 1);
            hashtable[x] = s;
            status[x]=1;
            hashpoint[x]++;
            lastinserted = x;
            return &hashtable[x];
        }
    }
    int find(string s) {
        int x = quadraticprobing(s, 0);
        if (x == -1) return -1;
        return x;
    }
    void reaheasing(){
        if (loadfactor > hashconfig.getlambda()) {
            int* hashpointnew;
            int* statusnew;
            string* hashtablenew;
            int sizehashnew;
            sizehashnew = int(hashconfig.getalpha() * sizehash);
            hashpointnew = new int[sizehashnew];
            hashtablenew = new string[sizehashnew];
            statusnew = new int[sizehashnew];
            for (int i = 0; i < sizehash; i++)
            {
                if (status[i] == 1) {
                    lastinserted = i;
                }
                statusnew[i] = status[i];
                hashtablenew[i] = hashtable[i];
                hashpointnew[i] = hashpoint[i];
            }
            delete[] status; delete[] hashtable; delete[]  hashpoint;
            status = statusnew;
            hashtable = hashtablenew;
            hashpoint = hashpointnew;
            sizehash = sizehashnew;
        }
        return;
    }
    int quadraticprobing(string s,int them)
    {
        int c1 = hashconfig.getc1();
        int c2 = hashconfig.getc2();
        int hash = hashconfig.hashfunction(s);
        int hashprop = hash; hashprop% sizehash;
        int i = 0;
        if (them == 1) {
            while (i < this->sizehash)
            {
                hashprop = hash;
                int x = (c1 * i);
                int y = c2 * ((i * i) % sizehash);
                hashprop = x % sizehash + y;
                hashprop %= sizehash;
                if (status[sizehash] != 1) {
                    return i;
                }
                i++;
            }

            throw runtime_error("No possible slot");
        }
        else {
            while (i < this->sizehash)
            {
                hashprop = hash;
                int x = (c1 * i);
                int y = c2 * ((i * i) % sizehash);
                hashprop = x % sizehash + y;
                hashprop %= sizehash;
                if (status[sizehash] == 1&&hashtable[i]==s) {
                    return i;
                }
                i++;
            }
            return -1;
        }
        
    };
    
    int getLastInsertedIndex() const {
        return this->lastinserted;
    };
    string toString() const {
        string res = "LitStringHash[";
        for (int i = 0; i < sizehash; i++)
        {
            string temp = "";
            if (i != 0)temp += ";";
            temp+="(";
            if (hashpoint[i] == 1) {
                temp += "litS=";
                temp += '"';
                temp += hashtable[i];
                temp += '"';
            }
            temp += ")";
            res += temp;
        }
        res += "]";
        return res;
    };
    void deletestring(string s) {
        int x = find(s);
        
        hashpoint[x]--;
        if (hashpoint[x] == 0) {
            status[x] = 0;
            hashtable[x] = "";
        }
    }
};
class ReducedBSTnode {

};
class ReducedConcatStringTree /* */ {
public:
    ReducedConcatStringTree(const char* s, LitStringHash* litStringHash);
    LitStringHash* litStringHash;
};

#endif // __CONCAT_STRING_TREE_H__

