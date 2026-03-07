#include "Containers/BinTree.h"
#include <iostream>

using namespace std;

namespace Containers
{
    CBNode::CBNode(
        double   Key,
        CBNode*  Parent) : m_Key(Key),
                           m_Parent(Parent), 
                           m_Left(NULL), 
                           m_Right(NULL)
    {}

    CBNode::~CBNode()
    {}

    CBinTree::CBinTree() : m_Root(NULL)
    {}

    CBinTree::~CBinTree()
    {}

    void CBinTree::Insert(double Key)
    {
        CBNode* pBNode_f = m_Root; // forward
        CBNode* pBNode_t = NULL;   // trailing

        while(pBNode_f != NULL)
        {
            pBNode_t = pBNode_f;
            pBNode_f = Key < pBNode_f->m_Key ? pBNode_f->m_Left : pBNode_f->m_Right;
        }

        if(pBNode_t == NULL)
            m_Root = new CBNode(Key);
        else
        {
            if(Key < pBNode_t->m_Key) pBNode_t->m_Left  = new CBNode(Key, pBNode_t);
            else                      pBNode_t->m_Right = new CBNode(Key, pBNode_t);
        }
    }

    void CBinTree::Delete(double Key)
    {
        CBNode* pBNode = TreeSearch(m_Root, Key);

        // Does the binary tree hold the key in the first place?
        if(pBNode)
        {
            CBNode* pBNode_x;
            CBNode* pBNode_y;

            // Determine the node to splice out (y)
            if(pBNode->m_Left == NULL || pBNode->m_Right == NULL)
            pBNode_y = pBNode;
            else
            pBNode_y = TreeSuccessor(pBNode);

            // Set x to the non-NULL child of y, or NULL if y has no children
            if(pBNode_y->m_Left)
            pBNode_x = pBNode_y->m_Left;
            else
            pBNode_x = pBNode_y->m_Right;

            // Splice out y
            if(pBNode_x)
            pBNode_x->m_Parent = pBNode_y->m_Parent;

            if(!pBNode_y->m_Parent)
            m_Root = pBNode_x;
            else
            {
            if(pBNode_y == pBNode_y->m_Parent->m_Left)
                pBNode_y->m_Parent->m_Left = pBNode_x;
            else
                pBNode_y->m_Parent->m_Right = pBNode_x;
            }

            if(pBNode_y != pBNode)
            pBNode->m_Key = pBNode_y->m_Key;

            delete pBNode_y;
        }
    }

    bool CBinTree::Empty()
    {
    return m_Root == NULL;
    }

    bool CBinTree::Holds(double Key)
    {
        return TreeSearch(m_Root, Key) != NULL;
    }

    double CBinTree::Minimum()
    {
        return TreeMinimum(m_Root)->m_Key;
    }

    double CBinTree::Maximum()
    {
        return TreeMaximum(m_Root)->m_Key;
    }

    ostream& CBinTree::Display(ostream& Out, int Style)
    {
        switch(Style)
        {
            case 0: { TreeWalk_InOrder  (Out, m_Root); break; }
            case 1: { TreeWalk_PreOrder (Out, m_Root); break; }
            case 2: { TreeWalk_PostOrder(Out, m_Root); break; }
        }

        Out << endl;

        return Out;
    }

    void CBinTree::TreeWalk_InOrder(ostream& Out, CBNode* pBNode)
    {
        if(pBNode)
        {
            TreeWalk_InOrder(Out, pBNode->m_Left);
            Out << pBNode->m_Key << " ";
            TreeWalk_InOrder(Out, pBNode->m_Right);
        }
    }

    void CBinTree::TreeWalk_PreOrder(ostream& Out, CBNode* pBNode)
    {
        if(pBNode)
        {
            Out << pBNode->m_Key << " ";
            TreeWalk_PreOrder(Out, pBNode->m_Left);
            TreeWalk_PreOrder(Out, pBNode->m_Right);
        }
    }

    void CBinTree::TreeWalk_PostOrder(ostream& Out, CBNode* pBNode)
    {
        if(pBNode)
        {
            TreeWalk_PostOrder(Out, pBNode->m_Left);
            TreeWalk_PostOrder(Out, pBNode->m_Right);
            Out << pBNode->m_Key << " ";
        }
    }

    CBNode* CBinTree::TreeSearch(CBNode* pBNode, double Key)
    {
        if(pBNode == NULL || pBNode->m_Key == Key)
            return pBNode;

        if(Key < pBNode->m_Key) return TreeSearch(pBNode->m_Left,  Key);
        else                    return TreeSearch(pBNode->m_Right, Key);
    }

    CBNode* CBinTree::TreeMinimum(CBNode* pBNode)
    {
        while(pBNode->m_Left != NULL)
            pBNode = pBNode->m_Left;

        return pBNode;
    }

    CBNode* CBinTree::TreeMaximum(CBNode* pBNode)
    {
        while(pBNode->m_Right)
            pBNode = pBNode->m_Right;

        return pBNode;
    }

    CBNode* CBinTree::TreeSuccessor(CBNode* pBNode)
    {
        if(pBNode->m_Right)
            return TreeMinimum(pBNode->m_Right);

        CBNode* pBNode_f = pBNode->m_Parent;
        while(pBNode_f && pBNode == pBNode_f->m_Right)
        {
            pBNode = pBNode_f;
            pBNode_f = pBNode_f->m_Parent;
        }

        return pBNode_f;
    }

    CBNode* CBinTree::TreePredecessor(CBNode* pBNode)
    {
        if(pBNode->m_Left)
            return TreeMaximum(pBNode->m_Left);

        CBNode* pBNode_f = pBNode->m_Parent;
        while(pBNode_f && pBNode == pBNode_f->m_Left)
        {
            pBNode = pBNode_f;
            pBNode_f = pBNode_f->m_Parent;
        }

        return pBNode_f;
    }
}
