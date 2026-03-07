#include <iostream>

namespace Containers
{
    class CBNode
    {
    private:
        CBNode(
            double  Key    = 0.0,
            CBNode* Parent = NULL);
            
        ~CBNode();

	    double  m_Key;
        CBNode* m_Parent;
        CBNode* m_Left;
        CBNode* m_Right;

    friend class CBinTree;        
    };

    class CBinTree
    {
        public:
            CBinTree();
            ~CBinTree();

            void Insert(double Key);
            void Delete(double Key);

            bool Empty();
            bool Holds(double Key);

            double Minimum();
            double Maximum();

            std::ostream& Display(std::ostream& Out, int Style = 0); 

        private:
            CBNode* m_Root;

            CBNode* TreeMinimum(CBNode* pBNode);
            CBNode* TreeMaximum(CBNode* pBNode);

            CBNode* TreeSuccessor  (CBNode* pBNode);
            CBNode* TreePredecessor(CBNode* pBNode);

            CBNode* TreeSearch(CBNode* pBNode, double Key);

            void TreeWalk_InOrder  (std::ostream& Out, CBNode* pBNode);
            void TreeWalk_PreOrder (std::ostream& Out, CBNode* pBNode);
            void TreeWalk_PostOrder(std::ostream& Out, CBNode* pBNode);        
    };
}