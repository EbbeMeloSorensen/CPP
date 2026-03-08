#include <iostream>
#include "Containers/MxCifQuadTree.h"

using namespace std;

namespace Containers
{
    // Globals
    const int g_XF[4] = {-1,  1, -1, 1};
    const int g_YF[4] = {-1, -1,  1, 1};
    const int g_VF[2] = {-1, 1};

    // Helper functions
    QUADRANT CIF_COMPARE(CRectangle* pP, const double CX, const double CY)
    {
        if(pP->m_cx < CX) 
            return pP->m_cy < CY ? NW : SW;
        else            
            return pP->m_cy < CY ? NE : SE;
    }

    DIRECTION BIN_COMPARE(CRectangle* pP, const double CV, const AXIS V)
    {
        if(V == XA)
        {
            if(pP->m_cx - pP->m_lx <= CV && CV <= pP->m_cx + pP->m_lx)
            return BOTH;

            if(CV > pP->m_cx)
            return LEFT;

            return RIGHT;
        }
        else
        {
            if(pP->m_cy - pP->m_ly <= CV && CV <= pP->m_cy + pP->m_ly)
            return BOTH;

            if(CV > pP->m_cy)
            return LEFT;

            return RIGHT;
        }
    }    

    bool CIF_SEARCH(CRectangle* pP, CQuadNode* pQ, 
                    const double CX, const double CY,
                    double LX, double LY)
    {
        // Is there a quadnode in the first place?
        if(!pQ)
            return false;

        // Is rectangle outside the rectangle of the very quadnode
        if(!pP->Intersects(CRectangle(CX, CY, LX, LY)))
            return false;

        // Does the rectangle intersect any rectangles in any of the two bintrees of the quadnode?
        if(CROSS_AXIS(pP, pQ->m_Axis[YA], CY, LY, YA))
            return true;

        if(CROSS_AXIS(pP, pQ->m_Axis[XA], CX, LX, XA))
            return true;

        LX /= 2;
        LY /= 2;

        if(CIF_SEARCH(pP, pQ->m_Child[NW], CX + g_XF[NW] * LX, CY + g_YF[NW] * LY, LX, LY) ||
            CIF_SEARCH(pP, pQ->m_Child[NE], CX + g_XF[NE] * LX, CY + g_YF[NE] * LY, LX, LY) ||
            CIF_SEARCH(pP, pQ->m_Child[SW], CX + g_XF[SW] * LX, CY + g_YF[SW] * LY, LX, LY) ||
            CIF_SEARCH(pP, pQ->m_Child[SE], CX + g_XF[SE] * LX, CY + g_YF[SE] * LY, LX, LY))
            return true;

        return false;
    }

    bool CROSS_AXIS(CRectangle* pP, CBinNode* pQ, const double CV, double LV, const AXIS V)
    {
        // Is there a binnode in the first place?
        if(!pQ)
            return false;

        // Does the rectangle intersect any of the rectangles of the binnode
        list<CRectangle*>::iterator it;
        for(it = pQ->m_Rectangles.begin(); it != pQ->m_Rectangles.end(); it++)
            if(pP->Intersects(**it))
            return true;

        LV /= 2;
        DIRECTION D = BIN_COMPARE(pP, CV, V);
        if(D == BOTH)
            return CROSS_AXIS(pP, pQ->m_Child[LEFT],  CV - LV, LV, V) ||
                CROSS_AXIS(pP, pQ->m_Child[RIGHT], CV + LV, LV, V);

        return CROSS_AXIS(pP, pQ->m_Child[D], CV + g_VF[D] * LV, LV, V);
    }

    // Opposite quadrant
    QUADRANT OPQUAD(const QUADRANT Q)
    {
        switch(Q)
        {
            case NW: { return SE; break; }
            case NE: { return SW; break; }
            case SW: { return NE; break; }
            default: { return NW; break; }
        }
    }

    // Next quadrant (clockwise)
    QUADRANT CQUAD(const QUADRANT Q)
    {
        switch(Q)
        {
            case NW: { return NE; break; }
            case NE: { return SE; break; }
            case SW: { return NW; break; }
            default: { return SW; break; }
        }
    }

    // Next quadrant (counterclockwise)
    QUADRANT CCQUAD(const QUADRANT Q)
    {
        switch(Q)
        {
            case NW: { return SW; break; }
            case NE: { return NW; break; }
            case SW: { return SE; break; }
            default: { return NE; break; }
        }
    }

    // Opposite direction
    DIRECTION OPDIR(const DIRECTION D)
    {
        return D == LEFT ? RIGHT : LEFT;
    }

    // Other axis
    AXIS OTHERAXIS(const AXIS V)
    {
        return V == XA ? YA : XA;
    }

    // Classes

    // Constructor
    CRectangle::CRectangle(double cx, 
                        double cy, 
                        double lx, 
                        double ly) : m_cx(cx), 
                                        m_cy(cy), 
                                        m_lx(lx), 
                                        m_ly(ly)
    {}

    // Copy constructor
    CRectangle::CRectangle(const CRectangle& P) : m_cx(P.m_cx),
                                                m_cy(P.m_cy),
                                                m_lx(P.m_lx),
                                                m_ly(P.m_ly)
    {}

    // Destructor
    CRectangle::~CRectangle()
    {}

    double CRectangle::GetCenterX() const
    {
        return m_cx;
    }

    double CRectangle::GetCenterY() const
    {
        return m_cy;
    }

    double CRectangle::GetHalfWidth() const
    {
        return m_lx;
    }

    double CRectangle::GetHalfHeight() const
    {
        return m_ly;
    }

    // Assignment operator
    CRectangle& CRectangle::operator=(const CRectangle& P)
    {
        if(this != &P)
        {
            m_cx = P.m_cx;
            m_cy = P.m_cy;
            m_lx = P.m_lx;
            m_ly = P.m_ly;
        }

        return(*this);
    }

    bool CRectangle::Intersects(const CRectangle& P)
    {
        double v0a, v1a, v0b, v1b;

        // Test for overlap on the X axis
        v0a = m_cx - m_lx;
        v1a = m_cx + m_lx;
        v0b = P.m_cx - P.m_lx;
        v1b = P.m_cx + P.m_lx;

        if((v0a <= v0b && v0b <= v1a) || 
            (v0b <= v0a && v0a <= v1b))
        {
            // Test for overlap on the Y axis
            v0a = m_cy - m_ly;
            v1a = m_cy + m_ly;
            v0b = P.m_cy - P.m_ly;
            v1b = P.m_cy + P.m_ly;

            if((v0a <= v0b && v0b <= v1a) || 
            (v0b <= v0a && v0a <= v1b))
            return true;
        }

        return false;
    }

    std::ostream& operator<<(ostream& out, CRectangle& rect)
    {
        // out << "(";
        // int index = 0;
        // if(index < ca.m_Size) 
        // {
        //     out << ca[index++];
        //     while(index < ca.m_Size)
        //     out << ", " << ca[index++];
        // }
        // out << ")";

        out << "Bamse";

        return out;
    }

    CBinNode::CBinNode()
    {
        m_Child[LEFT] = m_Child[RIGHT] = NULL;
    }

    CBinNode::~CBinNode()
    {
        if(m_Child[LEFT])  delete m_Child[LEFT];
        if(m_Child[RIGHT]) delete m_Child[RIGHT];
    }

    void CBinNode::Insert(CRectangle* pP) 
    { 
        m_Rectangles.push_back(pP); 
    }

    bool CBinNode::Holds(CRectangle* pP)
    {
        return find(m_Rectangles.begin(), m_Rectangles.end(), pP) != m_Rectangles.end();
    }

    void CBinNode::Remove(CRectangle* pP)
    {
        m_Rectangles.remove(pP);
    }

    int CBinNode::GetSize()
    {
        return m_Rectangles.size();
    }

    CQuadNode::CQuadNode()
    {
        m_Axis[0] = m_Axis[1] = NULL;
        m_Child[NW] = m_Child[NE] = m_Child[SW] = m_Child[SE] = NULL;
    }

    CQuadNode::~CQuadNode()
    {
        // Destroy BinTrees
        if(m_Axis[XA]) delete m_Axis[XA];
        if(m_Axis[YA]) delete m_Axis[YA];

        // Destroy quadnode children
        if(m_Child[NW]) delete m_Child[NW];
        if(m_Child[NE]) delete m_Child[NE];
        if(m_Child[SW]) delete m_Child[SW];
        if(m_Child[SE]) delete m_Child[SE];
    }

    void CQuadNode::InsertOnAxis(CRectangle* pP, double CV, double LV, AXIS V)
    {
        CBinNode*  pBinNode;
        DIRECTION  D;

        if(!m_Axis[V])
            m_Axis[V] = new CBinNode;

        pBinNode = m_Axis[V];
        D = BIN_COMPARE(pP, CV, V);

        while(D != BOTH)
        {
            if(!pBinNode->m_Child[D])
            pBinNode->m_Child[D] = new CBinNode;

            pBinNode = pBinNode->m_Child[D];
            LV /= 2;
            CV += LV * g_VF[D];
            D = BIN_COMPARE(pP, CV, V);
        }

        pBinNode->Insert(pP);
    }

    CMxCifQuadTree::CMxCifQuadTree(const CRectangle& P)
    {
        m_P    = P;
        m_Root = NULL;
    }

    CMxCifQuadTree::~CMxCifQuadTree()
    {
        Clear();
    }

    void CMxCifQuadTree::Insert(CRectangle* pP)
    {
        CQuadNode*  pQuadNode;
        DIRECTION   DX, DY;
        QUADRANT    Q;
        double      CX = m_P.m_cx;
        double      CY = m_P.m_cy;
        double      LX = m_P.m_lx;
        double      LY = m_P.m_ly;

        if(!m_Root)
            m_Root = new CQuadNode;

        pQuadNode = m_Root;
        DX = BIN_COMPARE(pP, CX, XA);
        DY = BIN_COMPARE(pP, CY, YA);

        while(DX != BOTH && DY != BOTH)
        {
            Q = CIF_COMPARE(pP, CX, CY);

            if(!pQuadNode->m_Child[Q])
            pQuadNode->m_Child[Q] = new CQuadNode;

            pQuadNode = pQuadNode->m_Child[Q];
            LX /= 2;
            LY /= 2;
            CX += LX * g_XF[Q];
            CY += LY * g_YF[Q];

            DX = BIN_COMPARE(pP, CX, XA);
            DY = BIN_COMPARE(pP, CY, YA);
        }

        if(DX == BOTH)
            pQuadNode->InsertOnAxis(pP, CY, LY, YA);
        else
            pQuadNode->InsertOnAxis(pP, CX, LX, XA);
    }

    void CMxCifQuadTree::Remove(CRectangle* pP)
    {
        if (!m_Root)
        {
            return;
        }

        double      CX = m_P.m_cx;
        double      CY = m_P.m_cy;
        double      LX = m_P.m_lx;
        double      LY = m_P.m_ly;
        double      CV, LV;
        CQuadNode*  T;
        CQuadNode*  FT;
        CQuadNode*  TT;
        CQuadNode*  TEMPC;
        CBinNode*   B;
        CBinNode*   FB;
        CBinNode*   TB;
        CBinNode*   TEMPB;
        AXIS        V;
        QUADRANT    Q, QF;
        DIRECTION   D, DF;

        T  = m_Root;
        FT = NULL;

        while(BIN_COMPARE(pP, CX, V = XA) != BOTH &&
            BIN_COMPARE(pP, CY, V = YA) != BOTH)
        {
            Q = CIF_COMPARE(pP, CX, CY);

            if(!T->m_Child[Q]) return;  // The rectangle is not in the tree

            if(T->m_Axis[LEFT]        ||
                T->m_Axis[RIGHT]      ||
                T->m_Child[OPQUAD(Q)] ||
                T->m_Child[CQUAD (Q)] ||
                T->m_Child[CCQUAD(Q)])
            {
                FT = T;
                QF = Q;
            }

            T = T->m_Child[Q];
            LX /= 2;
            LY /= 2;
            CX += LX * g_XF[Q];
            CY += LY * g_YF[Q];
        }

        V  = OTHERAXIS(V);
        B  = T->m_Axis[V];
        FB = NULL;

        if(V == XA)
        {
            CV = CX;
            LV = LX;
        }
        else{
            CV = CY;
            LV = LY;
        }

        D = BIN_COMPARE(pP, CV, V);

        while(B && D != BOTH)
        {
            if(B->m_Child[OPDIR(D)] || !B->m_Rectangles.empty())
            {
                FB = B;
                DF = D;
            }

            B = B->m_Child[D];
            LV /= 2;
            CV += LV * g_VF[D];
            D = BIN_COMPARE(pP, CV, V);
        }

        if(!B || !B->Holds(pP)) 
        {
            return;                                    // The rectangle is not in the tree
        }
        else if(B->m_Child[LEFT] || B->m_Child[RIGHT] || B->GetSize() > 1)
        {
            B->Remove(pP);                             // No collapsing is possible
        }
        else
        {
            // Attempt to collapse BinNodes
            TB = FB ? FB->m_Child[DF] : T->m_Axis[V];  // Get a link to the oldest dismissable BinNode

            D = LEFT;                                  // Initialize direction variable for scanning
            while(TB != B)                             // Destroy BinNodes
            {
                if(!TB->m_Child[D])                      // Determine the direction to the BinNode child
                D = OPDIR(D);                          //

                TEMPB = TB->m_Child[D];
                TB->m_Child[D] = NULL;                   // Detach in order to avoid premature destruction of children
                delete TB;
                TB = TEMPB;
            }

            delete B;

            if(FB)
                FB->m_Child[DF] = NULL;                  // Set pointer to oldest destroyed BinNode to NULL
            else                                       //
            {                                          //
                T->m_Axis[V] = NULL;                     // 

                if(T->m_Axis[OTHERAXIS(V)] ||
                T->m_Child[0]           || 
                T->m_Child[1]           ||
                T->m_Child[2]           ||
                T->m_Child[3])
                return;                                // No further collapsing is possible
                                                        // BEMAERK AT BOGEN IKKE HAR KRITERIET OM CHILDREN QUADNODES MED
                                                        // DET MAA VEL VAERE EN FEJL (det er jo helt parallelt til hvad
                                                        // der foregaar under kollaps af bintraeet)

                // Attempt to collapse QuadNodes
                TT = FT ? FT->m_Child[QF] : m_Root;      // Get a link to the oldest dismissable QuadNode

                Q = NW;                                  // Initialize quadrant variable for scanning
                while(TT != T)                           // Destroy QuadNodes
                {
                while(!TT->m_Child[Q])                 // Determine the direction to the QuadNode child
                    Q = CQUAD(Q);                        //

                TEMPC = TT->m_Child[Q];                // Get a link to the QuadNode child for the next iteration
                TT->m_Child[Q] = NULL;                 // Detach in order to avoid premature destruction of children
                delete TT;                             // Destroy the QuadNode
                TT = TEMPC;                            // Proceed to the QuadNode child
                }

                delete T;                                // Destroy the QuadNode

                if(FT)                                   // Set pointer to oldest destroyed QuadNode to NULL
                FT->m_Child[QF] = NULL;                //
                else                                     //
                m_Root = NULL;                         //
            }
        }
    }

    bool CMxCifQuadTree::Intersects(CRectangle* pP)
    {
        if(!m_Root)
            return false;

        return CIF_SEARCH(pP, m_Root, m_P.m_cx, m_P.m_cy, m_P.m_lx, m_P.m_ly);
    }

    void CMxCifQuadTree::Clear()
    {
        if(m_Root)
        {
            delete m_Root;
            m_Root = NULL;
        }
    }
}
