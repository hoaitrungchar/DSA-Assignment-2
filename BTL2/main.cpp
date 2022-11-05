#include "ConcatStringTree.h"
void tc1(){
    ConcatStringTree s3 =  ConcatStringTree("Hello");
    ConcatStringTree s4 =  ConcatStringTree(",_t");
    ConcatStringTree s5 =  ConcatStringTree("his_is");
    ConcatStringTree s6 = ConcatStringTree("_an");
    
    ConcatStringTree s1 = s3.concat(s4);
    ConcatStringTree s2 = s5.concat(s6);
    cout << "length of s1: " << s1.length() << endl;
    cout << "length of s2: " << s2.length() << endl;
    cout << "char at index 1 of s2: " << s2.get(1) << endl;
    try {
        cout << "char at index 14: " << s1.get(14) << endl;
    }
    catch (out_of_range& ofr) {
        cout << "Exception out_of_range: " << ofr.what() << endl;
    }
    cout << "index of i in s1: " << s1.indexOf('i') << endl;
    cout << "index of i in s2: " << s2.indexOf('i') << endl;
    cout << "s1 tostringpreorder: " << s1.toStringPreOrder()<< endl;
    cout << "s2 tostringpreorder: " << s2.toStringPreOrder() << endl;

    cout << "s1 tostring: " << s1.toString() << endl;
    cout << "s2 tostring: " << s2.toString() << endl;
    ConcatStringTree s7 = s1.concat(s2);
    cout << "s7 tostringpreorder: " << s7.toStringPreOrder() << endl;
    ConcatStringTree s8 = s7.subString(1,10);
    cout << "s8=s7.subString(1, 10) tostringpreorder: " << s8.toStringPreOrder() << endl;
    cout << "s8=s7.subString(1, 10) tostring: " << s8.toString() << endl;
    ConcatStringTree s9 = s8.reverse();
    cout << "s9 = s8.reverse() tostringpreorder: " << s9.toStringPreOrder() << endl;
    cout << "s9 = s8.reverse() tostring: " << s9.toString() << endl;
    
}
void tc2() {
    ConcatStringTree* s3 = new ConcatStringTree("Hello");
    ConcatStringTree* s4 = new ConcatStringTree(",_t");
    ConcatStringTree* s5 = new ConcatStringTree("his_is");
    ConcatStringTree* s6 = new ConcatStringTree("_an");

    ConcatStringTree* s1 = new ConcatStringTree(s3->concat(*s4));
    cout << "s1->root->AVLtree->size() " << s1->root->AVLtree->size() << endl;

    ConcatStringTree *s2 = new ConcatStringTree(s5->concat(*s6));
    ConcatStringTree *s7 = new ConcatStringTree(s1->concat(*s2));
    cout << "s7 tostring: " << s7->toString() << endl;
    cout << "s1.root->AVLtree->size() " << s1->root->AVLtree->size() << endl;
    cout << "s1.root->AVLtree->root->id " << s1->root->AVLtree->root->id << endl;
    cout << "s1.root->AVLtree->root->ptrright->id " << s1->root->AVLtree->root->ptrright->id << endl;

    cout << "s1.root->AVLtree->toStringPreOrder() " << s1->root->AVLtree->toStringPreOrder() << endl;

    cout << "s7.root->AVLtree->size() " << s7->root->AVLtree->size() << endl;
    cout << "s7.getParTreeStringPreOrder():" << s7->getParTreeStringPreOrder("lr")<< endl;

   

    //cout << "s3.root->AVLtree->size() " << s3.root->AVLtree->size() << endl;


}
int main() {
    //tc1();
    tc2();
    return 0;
}