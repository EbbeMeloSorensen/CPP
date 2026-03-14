#include <list>
#include <vector>
#include <iostream>

namespace Containers
{
    enum QUADRANT{NW, NE, SW, SE};
    enum DIRECTION{LEFT, RIGHT, BOTH};
    enum AXIS{XA, YA};

    // Forward class declarations
    class CRectangle;
    class CBinNode;
    class CQuadNode;

    // Helper functions
    QUADRANT CIF_COMPARE(
        CRectangle* pP,
        const double CX,
        const double CY);

    DIRECTION BIN_COMPARE(
        CRectangle* pP,
        const double CV,
        const AXIS V);

    bool CIF_SEARCH(
        CRectangle* pP,
        CQuadNode* pQ,
        const double CX,
        const double CY,
        double LX,
        double LY);

    void CIF_SEARCH_ALL(
        CRectangle* pP,
        CQuadNode* pQ,
        const double CX,
        const double CY,
        double LX,
        double LY,
        std::list<CRectangle*>& intersectingRectangles,
        std::ostream& log);

    bool CROSS_AXIS(
        CRectangle* pP,
        CBinNode* pQ,
        const double CV,
        double LV,
        const AXIS V);

    void CROSS_AXIS_ALL(
        CRectangle* pP,
        CBinNode* pQ,
        const double CV,
        double LV,
        const AXIS V,
        std::list<CRectangle*>& intersectingRectangles,
        std::ostream& log);

    QUADRANT OPQUAD(
        const QUADRANT Q);

    QUADRANT CQUAD(
        const QUADRANT Q);

    QUADRANT CCQUAD(
        const QUADRANT Q);

    DIRECTION OPDIR(
        const DIRECTION D);

    AXIS OTHERAXIS(
        const AXIS V);    

    class CRectangle
    {
    public:
        CRectangle(
            double cx = 0.0,
            double cy = 0.0,
            double lx = 0.0,
            double ly = 0.0);

        CRectangle(
            const CRectangle& P);

        ~CRectangle();

        double GetCenterX() const;
        double GetCenterY() const;
        double GetHalfWidth() const;
        double GetHalfHeight() const;

        CRectangle& operator=(const CRectangle& P);

        bool Intersects(const CRectangle& P);

    private:
        double m_cx, m_cy;
        double m_lx, m_ly;

    friend QUADRANT  CIF_COMPARE(CRectangle*, const double, const double);
    friend DIRECTION BIN_COMPARE(CRectangle*, const double, const AXIS);
    friend std::ostream& operator<<(std::ostream& out, CRectangle& rect);

    friend class CMxCifQuadTree;
    };

    class CBinNode
    {
    private:
        CBinNode();
        ~CBinNode();

        void Insert(CRectangle* pP);
        bool Holds (CRectangle* pP);
        void Remove(CRectangle* pP);

        int GetSize();

        std::list<CRectangle*> m_Rectangles;
        CBinNode*              m_Child[2];

    friend bool CROSS_AXIS(
        CRectangle*,
        CBinNode*,
        const double,
        double,
        const AXIS);

    friend void CROSS_AXIS_ALL(
        CRectangle*,
        CBinNode*,
        const double,
        double,
        const AXIS,
        std::list<CRectangle*>&,
        std::ostream&);

    friend void CIF_SEARCH_ALL(
        CRectangle*,
        CQuadNode*, 
        const double,
        const double,
        double,
        double,
        std::list<CRectangle*>&,
        std::ostream&);

    friend class CQuadNode;
    friend class CMxCifQuadTree;
    };

    class CQuadNode
    {
    private:
        CQuadNode(std::ostream* pLog);
        ~CQuadNode();

        void InsertOnAxis(CRectangle* pP, double CV, double LV, AXIS V);
        void Log(std::string message);

        CBinNode*   m_Axis[2];
        CQuadNode*  m_Child[4];
        std::ostream* m_pLog;
 
    friend bool CIF_SEARCH(
        CRectangle*,
        CQuadNode*, 
        const double,
        const double,
        double,
        double);

    friend void CIF_SEARCH_ALL(
        CRectangle*,
        CQuadNode*, 
        const double,
        const double,
        double,
        double,
        std::list<CRectangle*>&,
        std::ostream&);

    friend class CMxCifQuadTree;
    };

    class CMxCifQuadTree
    {
    public:
        CMxCifQuadTree(
            const CRectangle& P,
            std::ostream* pLog);

        ~CMxCifQuadTree();

        void Insert(
            CRectangle* pP);

        void Remove(
            CRectangle* pP);

        bool IntersectsAny(
            CRectangle* pP);

        void GetAllIntersecting(
            CRectangle* pP,
            std::list<CRectangle*>& rectangles);

        void Clear();

    private:
        void Log(std::string message);

    private:
        CRectangle m_P;
        CQuadNode* m_Root;
        std::ostream* m_pLog;
    };
}